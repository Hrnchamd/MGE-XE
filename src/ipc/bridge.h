#pragma once

#include "proxydx/d3d9header.h"
#include "mge/dlmath.h"

#include <cstddef>
#include <cstdint>

#ifdef MGE64_HOST
template<typename T> using ptr32 = std::uint32_t;
template<typename T> using ptr64 = T*;
typedef std::uint32_t HANDLE32;
#define CONST32 
#else
template<typename T> using ptr32 = T*;
template<typename T> using ptr64 = std::uint64_t;
typedef HANDLE HANDLE32;
#define CONST32 const
#endif

constexpr DWORD VIS_NEAR =     0x01;
constexpr DWORD VIS_FAR =      0x02;
constexpr DWORD VIS_VERY_FAR = 0x04;
constexpr DWORD VIS_GRASS =    0x08;
constexpr DWORD VIS_LAND =     0x10;
constexpr DWORD VIS_STATIC = VIS_NEAR | VIS_FAR | VIS_VERY_FAR;

// ensure consistent layout between 32-bit and 64-bit processes
#pragma pack(push, 4)
struct RenderMesh {
    bool enabled, hasAlpha, animateUV;

    ptr32<IDirect3DTexture9> tex;
    D3DXMATRIX transform;
    int verts;
    ptr32<IDirect3DVertexBuffer9> vBuffer;
    int faces;
    ptr32<IDirect3DIndexBuffer9> iBuffer;
};

struct ViewFrustum {
    D3DXPLANE frustum[6];
    enum Containment { INSIDE, OUTSIDE, INTERSECTS };

    ViewFrustum(const D3DXMATRIX* viewProj);

    Containment ContainsSphere(const BoundingSphere& sphere) const;
    Containment ContainsBox(const BoundingBox& box) const;
};

enum VisibleSetSort : std::uint8_t {
    None,
    ByState,
    ByTexture,
};

namespace IPC {
    constexpr DWORD MaxWait = 60000;

    typedef std::uint32_t VecId;
    constexpr VecId InvalidVector = static_cast<VecId>(-1);

    static inline void CleanupHandle(HANDLE& h) {
        if (h != INVALID_HANDLE_VALUE && h != NULL) {
            CloseHandle(h);
        }
        h = INVALID_HANDLE_VALUE;
    }

    // these APIs aren't supported until Windows 8 or 10, so we load them dynamically
    typedef decltype(&::MapViewOfFileNuma2) MapViewOfFileNuma2_t;
    typedef decltype(&::MapViewOfFile3) MapViewOfFile3_t;
    typedef decltype(&::UnmapViewOfFileEx) UnmapViewOfFileEx_t;
    typedef decltype(&::UnmapViewOfFile2) UnmapViewOfFile2_t;
    typedef decltype(&::VirtualAlloc2) VirtualAlloc2_t;

    extern MapViewOfFileNuma2_t MapViewOfFileNuma2;
    extern MapViewOfFile3_t MapViewOfFile3;
    extern UnmapViewOfFileEx_t UnmapViewOfFileEx;
    extern UnmapViewOfFile2_t UnmapViewOfFile2;
    extern VirtualAlloc2_t VirtualAlloc2;

    extern bool initImports();

    class Client;
    class Server;

    union SharedHandle {
        HANDLE h;
        std::uint64_t u;
    };

    enum WakeReason {
        Update,
        Complete,
        ServerLost,
        Timeout,
        Error
    };

    enum Command: std::uint32_t {
        None,
        AllocVec,
        FreeVec,
        Exit,
        UpdateDynVis,
        InitDistantStatics,
        InitLandscape,
        SetWorldSpace,
        GetVisibleMeshesCoarse,
        GetVisibleMeshes,
        SortVisibleSet,
    };

    struct alignas(8) AllocVecParameters {
        IN std::uint32_t maxCapacityInElements;
        IN std::uint32_t windowSizeInElements;
        IN std::uint32_t elementSize;
        IN std::uint32_t initialCapacity;

        OUT std::uint32_t reservedBytes;
        OUT std::uint32_t windowBytes;
        OUT std::uint32_t headerBytes;
        OUT ptr32<void> header32;
        OUT VecId id;
    };

    struct alignas(8) FreeVecParameters {
        IN VecId id;

        OUT bool wasFreed;
    };

    struct alignas(8) DynVisParameters {
        IN std::uint16_t numUpdates;
        IN struct {
            std::uint16_t groupIndex;
            bool enable;
        } updates[100];
    };

    struct alignas(8) DistantStaticParameters {
        IN VecId distantStatics;
        IN VecId distantSubsets;
    };

    struct LandscapeBuffers {
        ptr32<IDirect3DVertexBuffer9> vb;
        ptr32<IDirect3DIndexBuffer9> ib;
    };

    struct alignas(8) InitLandscapeParameters {
        IN VecId buffers;
        IN ptr32<IDirect3DTexture9> texWorldColour;
    };

    struct alignas(8) SetWorldSpaceParameters {
        IN char cellname[64];

        OUT bool cellFound;
    };

    struct alignas(8) GetMeshesParameters {
        IN VecId visibleSet;
        IN VisibleSetSort sort;
        IN ViewFrustum viewFrustum;
        IN DWORD setFlags;
        IN D3DXVECTOR4 viewSphere;
    };

	struct Parameters {
        Command command;
        union {
            AllocVecParameters allocVecParams;
            FreeVecParameters freeVecParams;
            DynVisParameters dynVisParams;
            DistantStaticParameters distantStaticParams;
            InitLandscapeParameters initLandscapeParams;
            SetWorldSpaceParameters worldSpaceParams;
            GetMeshesParameters meshParams;
        } params;
	};
}
#pragma pack(pop)