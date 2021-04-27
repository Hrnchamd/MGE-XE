
#include "morrowindbsa.h"
#include "proxydx/d3d8header.h"

#include <cstdio>
#include <cstring>
#include <unordered_map>
#include <memory>



namespace BSA {

using std::unordered_map;

struct CacheEntry {
    HANDLE file;
    DWORD position;
    DWORD size;
};

struct BSAHash3 {
    union {
        struct {
            DWORD value1, value2;
        };
        __int64 LValue;
    };
};

struct EntryData {
    std::unique_ptr<char[]> data;
    unsigned int size;

    bool valid() const { return bool(data); }
};

// Note: loadedTextures would ideally store weakRefs, but COM doesn't support those.
static unordered_map<__int64, CacheEntry> cacheMap;
static unordered_map<__int64, IDirect3DTexture9*> loadedTextures;



// hashString - TES3 BSA Hash function
static BSAHash3 hashString(const char* str) {
    BSAHash3 result;

    unsigned int len = (unsigned int)strlen(str);

    // Use GhostWheel's code to hash the string
    unsigned int l = len >> 1;
    unsigned int sum, off, temp, i, n;

    for (sum = off = i = 0; i < l; i++) {
        sum ^= ((unsigned int)(str[i])) << (off & 0x1F);
        off += 8;
    }
    result.value1 = sum;

    for (sum = off = 0; i < len; i++) {
        temp = ((unsigned int)(str[i])) << (off & 0x1F);
        sum ^= temp;
        n = temp & 0x1F;
        sum = (sum << (32-n)) | (sum >> n);  // binary rotate right
        off += 8;
    }
    result.value2 = sum;
    return result;
}

// open - Read and store a BSA's index
static void open(const char* path) {
    HANDLE bsa = CreateFile(path, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
    if (bsa == INVALID_HANDLE_VALUE) {
        return;
    }

    DWORD hashOffset, numFiles, bytesRead, unused;
    ReadFile(bsa, &hashOffset, 4, &bytesRead, 0);
    if (bytesRead != 4 || hashOffset != 0x100) {
        CloseHandle(bsa);
        return;
    }

    ReadFile(bsa, &hashOffset, 4, &unused, 0);
    ReadFile(bsa, &numFiles, 4, &unused, 0);
    for (DWORD i = 0; i < numFiles; i++) {
        CacheEntry entry;
        __int64 hash;

        entry.file = bsa;
        SetFilePointer(bsa, 12 + i*8, 0, FILE_BEGIN);
        ReadFile(bsa, &entry.size, 4, &unused, 0);
        ReadFile(bsa, &entry.position, 4, &unused, 0);
        entry.position += 12 + hashOffset + numFiles*8;

        SetFilePointer(bsa, 12 + hashOffset + i*8, 0, FILE_BEGIN);
        ReadFile(bsa, &hash, 8, &unused, 0);
        cacheMap[hash] = entry;
    }
}

// init - Scan and index all BSA files
void init() {
    char path[MAX_PATH];
    WIN32_FIND_DATA data;

    HANDLE h = FindFirstFile("Data Files\\*.bsa", &data);
    if (h == INVALID_HANDLE_VALUE) {
        return;
    }

    do {
        std::snprintf(path, sizeof(path), "Data Files\\%s", data.cFileName);
        open(path);
    } while (FindNextFile(h, &data));

    FindClose(h);
}

// loadFile - Read a single file into memory, identified by hash only
static EntryData BSALoadFile(BSAHash3 hash) {
    auto it = cacheMap.find(hash.LValue);
    if (it == cacheMap.end()) {
        return EntryData();
    }

    const CacheEntry& entry = it->second;
    auto buf = std::make_unique<char[]>(entry.size);
    DWORD bytesRead;

    SetFilePointer(entry.file, entry.position, 0, FILE_BEGIN);
    ReadFile(entry.file, buf.get(), entry.size, &bytesRead, 0);

    if (bytesRead == entry.size) {
        return EntryData { std::move(buf), entry.size };
    } else {
        return EntryData();
    }
}

// loadTextureExact - Attempt to load a texture from a prioritized list of sources.
static IDirect3DTexture9* loadTextureExact(IDirect3DDevice9* dev, const char* filename) {
    char pathbuf[MAX_PATH];
    BSAHash3 hash = hashString(filename);
    IDirect3DTexture9* tex = nullptr;

    // First check if the texture is already loaded
    auto it = loadedTextures.find(hash.LValue);
    if (it != loadedTextures.end()) {
        it->second->AddRef();
        return it->second;
    }

    // Next check the distant land folder
    std::snprintf(pathbuf, sizeof(pathbuf), "Data Files\\distantland\\statics\\%s", filename);
    if (GetFileAttributes(pathbuf) != INVALID_FILE_ATTRIBUTES) {
        HRESULT hr = D3DXCreateTextureFromFileEx(dev, pathbuf, D3DX_FROM_FILE, D3DX_FROM_FILE, D3DX_FROM_FILE, 0, D3DFMT_UNKNOWN,
                     D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, 0, 0, &tex);

        if (hr == D3D_OK) {
            loadedTextures[hash.LValue] = tex;
            return tex;
        }
    }

    // Then check the normal folder
    std::snprintf(pathbuf, sizeof(pathbuf), "Data Files\\%s", filename);
    if (GetFileAttributes(pathbuf) != INVALID_FILE_ATTRIBUTES) {
        HRESULT hr = D3DXCreateTextureFromFileEx(dev, pathbuf, D3DX_FROM_FILE, D3DX_FROM_FILE, D3DX_FROM_FILE, 0, D3DFMT_UNKNOWN,
                     D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, 0, 0, &tex);

        if (hr == D3D_OK) {
            loadedTextures[hash.LValue] = tex;
            return tex;
        }
    }

    // Finally check the BSAs
    EntryData ed = BSALoadFile(hash);
    if (ed.valid()) {
        D3DXCreateTextureFromFileInMemoryEx(dev, ed.data.get(), ed.size, D3DX_FROM_FILE, D3DX_FROM_FILE, D3DX_FROM_FILE,
                                            0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, 0, 0, &tex);

        // Cache even if the texture load failed
        loadedTextures[hash.LValue] = tex;
        return tex;
    }

    // File not found
    return nullptr;
}

// loadTexture -  Attempt to load a texture from a prioritized list of sources, with extension substitution.
IDirect3DTexture9* loadTexture(IDirect3DDevice9* dev, const char* filename) {
    char pathbuf[MAX_PATH];

    // Prefer loading file with DDS extension first
    std::snprintf(pathbuf, sizeof(pathbuf), "textures\\%s", filename);
    std::strcpy(pathbuf + strlen(pathbuf) - 3, "dds");

    IDirect3DTexture9* tex = loadTextureExact(dev, pathbuf);
    if (tex) {
        return tex;
    }

    // Load file with original extension
    std::snprintf(pathbuf, sizeof(pathbuf), "textures\\%s", filename);
    return loadTextureExact(dev, pathbuf);
}

// clearTextureCache - Clear texture cache.
void clearTextureCache() {
    loadedTextures.clear();
}

// cacheStats - Returns number of textures cached, and approximate memory use in MB.
void cacheStats(int* total, int* memuse) {
    __int64 texMemUsage = 0;

    const auto& loadedTextures_const = loadedTextures;
    for (const auto& i : loadedTextures_const) {
        D3DSURFACE_DESC texdesc;
        i.second->GetLevelDesc(0, &texdesc);

        int bpp = 32;
        if (texdesc.Format == D3DFMT_DXT1) {
            bpp = 4;
        }
        if (texdesc.Format == D3DFMT_DXT3 || texdesc.Format == D3DFMT_DXT5) {
            bpp = 8;
        }

        texMemUsage += (texdesc.Width * texdesc.Height * bpp / 8) * 4 / 3;
    }

    *total = loadedTextures.size();
    *memuse = (int)(texMemUsage / 1048576.0);
}

}
