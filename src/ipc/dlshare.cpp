#include "dlshare.h"

#include "mge/configuration.h"
#include "mge/distantshader.h"
#include "mge/mgeversion.h"
#include "mge/quadtree.h"
#include "support/log.h"

using std::string;
using std::unordered_map;
using std::vector;

unordered_map<std::string, DistantLandShare::WorldSpace> DistantLandShare::mapWorldSpaces;
const DistantLandShare::WorldSpace* DistantLandShare::currentWorldSpace = nullptr;
bool DistantLandShare::hasCurrentWorldSpace = false;
QuadTree DistantLandShare::LandQuadTree;
vector<vector<QuadTreeMesh*>> DistantLandShare::dynamicVisGroupsServer;

void DistantLandShare::loadVisGroupsServer(HANDLE h) {
    DWORD unused;

    // skip distant statics count
    SetFilePointer(h, 4, 0, FILE_CURRENT);

    // Load dynamic vis groups
    DWORD dynamicVisGroupCount;
    ReadFile(h, &dynamicVisGroupCount, 4, &unused, 0);
    dynamicVisGroupsServer.clear();

    if (dynamicVisGroupCount > 0) {
        const size_t visGroupRecordSize = 130;
        size_t visDataSize = visGroupRecordSize * dynamicVisGroupCount;
        auto visData = std::make_unique<char[]>(visDataSize);
        ReadFile(h, visData.get(), static_cast<DWORD>(visDataSize), &unused, 0);

        // VisGroup indexes use a 1-based index, group 0 is reserved for testing
        dynamicVisGroupsServer.resize(dynamicVisGroupCount + 1);
    }
}

HANDLE DistantLandShare::beginReadStatics() {
    DWORD unused;
    HANDLE h;

    h = CreateFile("Data Files\\distantland\\version", GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
    if (h == INVALID_HANDLE_VALUE) {
        LOG::logline("!! Required distant statics files are missing, regeneration required - distantland/version");
        LOG::flush();
        return INVALID_HANDLE_VALUE;
    }
    BYTE version = 0;
    ReadFile(h, &version, sizeof(version), &unused, 0);
    if (version != MGE_DL_VERSION) {
        LOG::logline("!! Distant statics data is from an old version and needs to be regenerated");
        LOG::flush();
        return INVALID_HANDLE_VALUE;
    }
    CloseHandle(h);

    h = CreateFile("Data Files\\distantland\\statics\\usage.data", GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
    if (h == INVALID_HANDLE_VALUE) {
        LOG::logline("!! Required distant statics files are missing, regeneration required - distantland/statics/usage.data");
        LOG::flush();
        return INVALID_HANDLE_VALUE;
    }

    return h;
}

bool DistantLandShare::initDistantStaticsServer(IPC::Vec<DistantStatic>& distantStatics, IPC::Vec<DistantSubset>& distantSubsets) {
    if (GetFileAttributes("Data Files\\distantland\\statics") == INVALID_FILE_ATTRIBUTES) {
        LOG::logline("!! Distant statics have not been generated");
        LOG::flush();
        return !(Configuration.MGEFlags & USE_DISTANT_LAND);
    }

    auto h = beginReadStatics();
    if (h == INVALID_HANDLE_VALUE) {
        return false;
    }

    loadVisGroupsServer(h);
    readDistantStatics(h, distantStatics, distantSubsets, dynamicVisGroupsServer);

    CloseHandle(h);

    return true;
}

bool DistantLandShare::initLandscapeServer(IPC::Vec<IPC::LandscapeBuffers>& landscapeBuffers, ptr32<IDirect3DTexture9> texWorldColour) {
    HANDLE file = CreateFile("Data Files\\distantland\\world", GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
    if (file == INVALID_HANDLE_VALUE) {
        LOG::winerror("Server failed to open landscape data");
        return false;
    }

    DWORD file_size = GetFileSize(file, NULL);
    DWORD mesh_count, unused;
    ReadFile(file, &mesh_count, 4, &unused, 0);

    vector<LandMesh> meshesLand;
    meshesLand.resize(mesh_count);

    landscapeBuffers.start_read();
    auto it = landscapeBuffers.begin();
    if (!meshesLand.empty()) {
        D3DXVECTOR2 qtmin(FLT_MAX, FLT_MAX), qtmax(-FLT_MAX, -FLT_MAX);
        D3DXMATRIX world;
        D3DXMatrixIdentity(&world);

        // Load meshes and calculate max size of quadtree
        for (auto& i : meshesLand) {
            ReadFile(file, &i.sphere.radius, 4, &unused, 0);
            ReadFile(file, &i.sphere.center, 12, &unused, 0);

            D3DXVECTOR3 boxMin, boxMax;
            ReadFile(file, &boxMin, 12, &unused, 0);
            ReadFile(file, &boxMax, 12, &unused, 0);
            i.box.Set(boxMin, boxMax);

            ReadFile(file, &i.verts, 4, &unused, 0);
            ReadFile(file, &i.faces, 4, &unused, 0);

            bool large = (i.verts > 0xFFFF || i.faces > 0xFFFF);

            // skip info the client handles
            auto bufferSize = i.verts * SIZEOFLANDVERT + i.faces * (large ? 12 : 6);
            SetFilePointer(file, bufferSize, NULL, FILE_CURRENT);

            auto& buffers = *it;
            if (it.at_end()) {
                LOG::logline("Client landscape buffers ended while the server still has more meshes (%zu buffers found, expected %lu)", landscapeBuffers.size(), mesh_count);
                landscapeBuffers.end_read();
                return false;
            }
            ++it;

            i.vbuffer = buffers.vb;
            i.ibuffer = buffers.ib;

            qtmin.x = std::min(qtmin.x, i.sphere.center.x - i.sphere.radius);
            qtmin.y = std::min(qtmin.y, i.sphere.center.y - i.sphere.radius);
            qtmax.x = std::max(qtmax.x, i.sphere.center.x + i.sphere.radius);
            qtmax.y = std::max(qtmax.y, i.sphere.center.y + i.sphere.radius);
        }

        LandQuadTree.SetBox(std::max(qtmax.x - qtmin.x, qtmax.y - qtmin.y), 0.5 * (qtmax + qtmin));

        // Add meshes to the quadtree
        for (auto& i : meshesLand) {
            LandQuadTree.AddMesh(i.sphere, i.box, world, false, false, texWorldColour, i.verts, i.vbuffer, i.faces, i.ibuffer);
        }
    }

    landscapeBuffers.end_read();

    CloseHandle(file);
    LandQuadTree.CalcVolume();

    // Log approximate memory use
    LOG::logline("-- Distant landscape memory use: %d MB", file_size / (1 << 20));

    return true;
}

bool DistantLandShare::setCurrentWorldSpace(const char* name) {
    auto it = mapWorldSpaces.find(name);
    if (it != mapWorldSpaces.end()) {
        currentWorldSpace = &it->second;
        hasCurrentWorldSpace = true;
        return true;
    }

    currentWorldSpace = nullptr;
    hasCurrentWorldSpace = false;
    return false;
}

void DistantLandShare::getVisibleMeshesCoarse(IPC::Vec<RenderMesh>& output, const ViewFrustum& viewFrustum, VisibleSetSort sort, DWORD setFlags) {
    VisibleSet<IpcServerVector> visibleSet((IpcServerVector(output))); // extra parens for vexing parse

    // if we're not sorting, we can do parallel reads and writes where the client processes elements as we add them
    if (sort == VisibleSetSort::None) {
        visibleSet.startWrite();
    }

    if (setFlags & VIS_NEAR) {
        currentWorldSpace->NearStatics->GetVisibleMeshesCoarse(viewFrustum, visibleSet);
    }
    if (setFlags & VIS_FAR) {
        currentWorldSpace->FarStatics->GetVisibleMeshesCoarse(viewFrustum, visibleSet);
    }
    if (setFlags & VIS_VERY_FAR) {
        currentWorldSpace->VeryFarStatics->GetVisibleMeshesCoarse(viewFrustum, visibleSet);
    }
    if (setFlags & VIS_GRASS) {
        currentWorldSpace->GrassStatics->GetVisibleMeshesCoarse(viewFrustum, visibleSet);
    }
    if (setFlags & VIS_LAND) {
        LandQuadTree.GetVisibleMeshesCoarse(viewFrustum, visibleSet);
    }

    switch (sort) {
    case VisibleSetSort::ByState:
        visibleSet.SortByState();
        break;
    case VisibleSetSort::ByTexture:
        visibleSet.SortByTexture();
        break;
    case VisibleSetSort::None:
        visibleSet.endWrite();
        break;
    }
}

void DistantLandShare::getVisibleMeshes(IPC::Vec<RenderMesh>& output, const ViewFrustum& viewFrustum, const D3DXVECTOR4& viewSphere, VisibleSetSort sort, DWORD setFlags) {
    VisibleSet<IpcServerVector> visibleSet((IpcServerVector(output))); // extra parens for vexing parse

    // if we're not sorting, we can do parallel reads and writes where the client processes elements as we add them
    if (sort == VisibleSetSort::None) {
        visibleSet.startWrite();
    }

    if (setFlags & VIS_NEAR) {
        currentWorldSpace->NearStatics->GetVisibleMeshes(viewFrustum, viewSphere, visibleSet);
    }
    if (setFlags & VIS_FAR) {
        currentWorldSpace->FarStatics->GetVisibleMeshes(viewFrustum, viewSphere, visibleSet);
    }
    if (setFlags & VIS_VERY_FAR) {
        currentWorldSpace->VeryFarStatics->GetVisibleMeshes(viewFrustum, viewSphere, visibleSet);
    }
    if (setFlags & VIS_GRASS) {
        currentWorldSpace->GrassStatics->GetVisibleMeshes(viewFrustum, viewSphere, visibleSet);
    }
    if (setFlags & VIS_LAND) {
        LandQuadTree.GetVisibleMeshes(viewFrustum, viewSphere, visibleSet);
    }

    switch (sort) {
    case VisibleSetSort::ByState:
        visibleSet.SortByState();
        break;
    case VisibleSetSort::ByTexture:
        visibleSet.SortByTexture();
        break;
    case VisibleSetSort::None:
        visibleSet.endWrite();
        break;
    }
}

void DistantLandShare::sortVisibleSet(IPC::Vec<RenderMesh>& vec, VisibleSetSort sort) {
    VisibleSet<IpcServerVector> visibleSet((IpcServerVector(vec))); // extra parens for vexing parse

    switch (sort) {
    case VisibleSetSort::ByState:
        visibleSet.SortByState();
        break;
    case VisibleSetSort::ByTexture:
        visibleSet.SortByTexture();
        break;
    case VisibleSetSort::None:
        break;
    }
}