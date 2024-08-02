#pragma once

#include "support/winheader.h"
#include "ipc/iter.h"
#include "ipc/vec.h"
#include "mge/configuration.h"
#include "mge/dlformat.h"
#include "mge/quadtree.h"

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class membuf_reader {
    char* ptr;

public:
    membuf_reader(char* buf) : ptr(buf) {}

    template <typename T>
    inline void read(T* dest, size_t size) {
        memcpy((char*)dest, ptr, size);
        ptr += size;
    }

    inline char* get() {
        return ptr;
    }

    inline void advance(size_t size) {
        ptr += size;
    }
};

class DistantLandShare {
public:
    struct WorldSpace {
        std::unique_ptr<QuadTree> NearStatics;
        std::unique_ptr<QuadTree> FarStatics;
        std::unique_ptr<QuadTree> VeryFarStatics;
        std::unique_ptr<QuadTree> GrassStatics;
    };

    static std::vector<std::vector<QuadTreeMesh*>> dynamicVisGroupsServer;
	static std::unordered_map<std::string, WorldSpace> mapWorldSpaces;
    static const WorldSpace* currentWorldSpace;
    static bool hasCurrentWorldSpace;
	static QuadTree LandQuadTree;

    static bool initDistantStaticsServer(IPC::Vec<DistantStatic>& distantStatics, IPC::Vec<DistantSubset>& distantSubsets);
    static void loadVisGroupsServer(HANDLE h);
    static HANDLE beginReadStatics();

    template<class T, class U, class V>
    static void readDistantStatics(HANDLE h, T& distantStatics, U& distantSubsets, V& dynamicVisGroups) {
        DWORD unused;

        // Load statics references
        const DWORD UsedDistantStaticRecordSize = 34;
        const DWORD UsedDistantStaticChunkCount = 250000;
        size_t worldvis_memory_use = 0;
        auto UsedDistantStaticData = std::make_unique<char[]>(UsedDistantStaticChunkCount * UsedDistantStaticRecordSize);

        mapWorldSpaces.clear();
        for (DWORD nWorldSpace = 0; true; ++nWorldSpace) {
            std::vector<UsedDistantStatic> worldSpaceStatics;
            WorldSpace* currentWorldSpace;
            DWORD UsedDistantStaticCount;

            ReadFile(h, &UsedDistantStaticCount, 4, &unused, 0);
            if (nWorldSpace != 0 && UsedDistantStaticCount == 0) {
                break;
            }

            if (nWorldSpace == 0) {
                auto iterWS = mapWorldSpaces.insert(make_pair(std::string(), WorldSpace())).first;
                currentWorldSpace = &iterWS->second;
                if (UsedDistantStaticCount == 0) {
                    continue;
                }
            }
            else {
                char cellname[64];
                ReadFile(h, &cellname, 64, &unused, 0);
                auto iterWS = mapWorldSpaces.insert(make_pair(std::string(cellname), WorldSpace())).first;
                currentWorldSpace = &iterWS->second;
            }

            worldSpaceStatics.reserve(UsedDistantStaticCount);

            while (UsedDistantStaticCount > 0) {
                DWORD staticsToRead = std::min(UsedDistantStaticChunkCount, UsedDistantStaticCount);
                UsedDistantStaticCount -= staticsToRead;

                ReadFile(h, UsedDistantStaticData.get(), static_cast<DWORD>(staticsToRead * UsedDistantStaticRecordSize), &unused, 0);
                membuf_reader udsReader(UsedDistantStaticData.get());

                for (DWORD i = 0; i < staticsToRead; ++i) {
                    UsedDistantStatic NewUsedStatic;
                    float yaw, pitch, roll, scale;

                    udsReader.read(&NewUsedStatic.staticRef, 4);
                    udsReader.read(&NewUsedStatic.visIndex, 2);
                    udsReader.read(&NewUsedStatic.pos, 12);
                    udsReader.read(&yaw, 4);
                    udsReader.read(&pitch, 4);
                    udsReader.read(&roll, 4);
                    udsReader.read(&scale, 4);
                    NewUsedStatic.scale = scale;

                    D3DXMATRIX transmat, rotmatx, rotmaty, rotmatz, scalemat;
                    D3DXMatrixTranslation(&transmat, NewUsedStatic.pos.x, NewUsedStatic.pos.y, NewUsedStatic.pos.z);
                    D3DXMatrixRotationX(&rotmatx, -yaw);
                    D3DXMatrixRotationY(&rotmaty, -pitch);
                    D3DXMatrixRotationZ(&rotmatz, -roll);
                    D3DXMatrixScaling(&scalemat, scale, scale, scale);

                    const DistantStatic* stat = &distantStatics[NewUsedStatic.staticRef];
                    NewUsedStatic.transform = scalemat * rotmatz * rotmaty * rotmatx * transmat;
                    NewUsedStatic.sphere = NewUsedStatic.GetBoundingSphere(stat->sphere);
                    NewUsedStatic.box = NewUsedStatic.GetBoundingBox(stat->aabbMin, stat->aabbMax);

                    worldSpaceStatics.push_back(NewUsedStatic);
                }
            }

            worldvis_memory_use += initDistantStaticsQT(*currentWorldSpace, distantStatics, distantSubsets, worldSpaceStatics, dynamicVisGroups);
        }

        // Log approximate memory use
        LOG::logline("-- Distant worldspaces memory use: %d MB", worldvis_memory_use / (1 << 20));
    }

    template<class T, class U, class V>
    static size_t initDistantStaticsQT(DistantLandShare::WorldSpace& worldSpace, T& distantStatics, U& distantSubsets, std::vector<UsedDistantStatic>& uds, V& dynamicVisGroups) {
        // Initialize quadtrees
        worldSpace.NearStatics = std::make_unique<QuadTree>();
        worldSpace.FarStatics = std::make_unique<QuadTree>();
        worldSpace.VeryFarStatics = std::make_unique<QuadTree>();
        worldSpace.GrassStatics = std::make_unique<QuadTree>();
        QuadTree* NQTR = worldSpace.NearStatics.get();
        QuadTree* FQTR = worldSpace.FarStatics.get();
        QuadTree* VFQTR = worldSpace.VeryFarStatics.get();
        QuadTree* GQTR = worldSpace.GrassStatics.get();

        // Calclulate optimal initial quadtree size
        D3DXVECTOR2 aabbMax = D3DXVECTOR2(-FLT_MAX, -FLT_MAX);
        D3DXVECTOR2 aabbMin = D3DXVECTOR2(FLT_MAX, FLT_MAX);

        // Find xyz bounds
        for (const auto& i : uds) {
            float x = i.pos.x, y = i.pos.y, r = i.sphere.radius;

            aabbMax.x = std::max(x + r, aabbMax.x);
            aabbMax.y = std::max(y + r, aabbMax.y);
            aabbMin.x = std::min(aabbMin.x, x - r);
            aabbMin.y = std::min(aabbMin.y, y - r);
        }

        size_t total_instances = 0;
        float box_size = std::max(aabbMax.x - aabbMin.x, aabbMax.y - aabbMin.y);
        D3DXVECTOR2 box_center = 0.5 * (aabbMax + aabbMin);

        NQTR->SetBox(box_size, box_center);
        FQTR->SetBox(box_size, box_center);
        VFQTR->SetBox(box_size, box_center);
        GQTR->SetBox(box_size, box_center);

        for (const auto& i : uds) {
            DistantStatic* stat = &distantStatics[i.staticRef];
            QuadTree* targetQTR;

            // Use post-transform (include scale) radius
            float radius = i.sphere.radius;

            // Buildings are treated as larger objects, as they are typically
            // smaller component meshes combined to make a single building
            if (stat->type == STATIC_BUILDING) {
                radius *= 2.0f;
            }

            // Select quadtree to place object in
            switch (stat->type) {
            case STATIC_AUTO:
            case STATIC_TREE:
            case STATIC_BUILDING:
                if (radius <= Configuration.DL.FarStaticMinSize) {
                    targetQTR = NQTR;
                }
                else if (radius <= Configuration.DL.VeryFarStaticMinSize) {
                    targetQTR = FQTR;
                }
                else {
                    targetQTR = VFQTR;
                }
                break;

            case STATIC_GRASS:
                targetQTR = GQTR;
                break;

            case STATIC_NEAR:
                targetQTR = NQTR;
                break;

            case STATIC_FAR:
                targetQTR = FQTR;
                break;

            case STATIC_VERY_FAR:
                targetQTR = VFQTR;
                break;

            default:
                continue;
            }

            // Add sub-meshes to appropriate quadtree
            auto endIndex = stat->firstSubsetIndex + stat->numSubsets;
            for (std::uint32_t subsetIndex = stat->firstSubsetIndex; subsetIndex < endIndex; subsetIndex++) {
                DistantSubset& s = distantSubsets[subsetIndex];
                BoundingSphere boundSphere;
                BoundingBox boundBox;

                if (stat->type == STATIC_BUILDING) {
                    // Use model bound so that all building parts have coherent visibility
                    boundSphere = i.sphere;
                    boundBox = i.box;
                }
                else {
                    // Use individual mesh bounds
                    boundSphere = i.GetBoundingSphere(s.sphere);
                    boundBox = i.GetBoundingBox(s.aabbMin, s.aabbMax);
                }

                auto mesh = targetQTR->AddMesh(
                    boundSphere,
                    boundBox,
                    i.transform,
                    s.hasAlpha,
                    s.hasUVController,
                    (ptr32<IDirect3DTexture9>)s.tex,
                    s.verts,
                    (ptr32<IDirect3DVertexBuffer9>)s.vbuffer,
                    s.faces,
                    (ptr32<IDirect3DIndexBuffer9>)s.ibuffer
                );
                if (i.visIndex > 0) {
                    dynamicVisGroups[i.visIndex].push_back(mesh);
                }
            }

            total_instances += stat->numSubsets;
        }

        NQTR->Optimize();
        NQTR->CalcVolume();
        FQTR->Optimize();
        FQTR->CalcVolume();
        VFQTR->Optimize();
        VFQTR->CalcVolume();
        GQTR->Optimize();
        GQTR->CalcVolume();

        // Return total memory use of leaves only, non-leaf nodes barely use much memory
        return total_instances * sizeof(QuadTreeMesh);
    }

    static bool initLandscapeServer(IPC::Vec<IPC::LandscapeBuffers>& landscapeBuffers, ptr32<IDirect3DTexture9> texWorldColour);
    static bool setCurrentWorldSpace(const char* name);
    static void getVisibleMeshesCoarse(IPC::Vec<RenderMesh>& output, const ViewFrustum& viewFrustum, VisibleSetSort sort, DWORD setFlags);
    static void getVisibleMeshes(IPC::Vec<RenderMesh>& output, const ViewFrustum& viewFrustum, const D3DXVECTOR4& viewSphere, VisibleSetSort sort, DWORD setFlags);
    static void sortVisibleSet(IPC::Vec<RenderMesh>& vec, VisibleSetSort sort);
};