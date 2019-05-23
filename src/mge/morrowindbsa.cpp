
#include "morrowindbsa.h"
#include "proxydx/d3d8header.h"

#include <cstdio>
#include <cstring>
#include <unordered_map>



using std::unordered_map;

struct BSAEntry {
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
    void* ptr;
    unsigned int size;

    EntryData() : ptr(0), size(0) {}
    EntryData(void* _ptr, unsigned int _size) : ptr(_ptr), size(_size) {}
    void release() {
        if (ptr) {
            delete [] (char*)ptr;
        }
    }
};

static unordered_map<__int64, BSAEntry> BSAEntries;
static unordered_map<__int64, IDirect3DTexture9*> BSALoadedTextures;



static BSAHash3 BSAHashString(const char* str) {
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

static void BSAOpen(const char* path) {
    HANDLE bsa = CreateFile(path, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
    if (bsa == INVALID_HANDLE_VALUE) {
        return;
    }

    DWORD hashoffset, numfiles, bytesread, unused;
    ReadFile(bsa, &hashoffset, 4, &bytesread, 0);
    if (bytesread != 4 || hashoffset != 0x100) {
        CloseHandle(bsa);
        return;
    }

    ReadFile(bsa, &hashoffset, 4, &unused, 0);
    ReadFile(bsa, &numfiles, 4, &unused, 0);
    for (DWORD i = 0; i < numfiles; i++) {
        BSAEntry entry;
        __int64 hash;

        entry.file = bsa;
        SetFilePointer(bsa, 12 + i*8, 0, FILE_BEGIN);
        ReadFile(bsa, &entry.size, 4, &unused, 0);
        ReadFile(bsa, &entry.position, 4, &unused, 0);
        entry.position += 12 + hashoffset + numfiles*8;
        SetFilePointer(bsa, 12+hashoffset + i*8, 0, FILE_BEGIN);
        ReadFile(bsa, &hash, 8, &unused, 0);
        BSAEntries[hash] = entry;
    }
}

void BSAInit() {
    char path[MAX_PATH];
    WIN32_FIND_DATA data;
    HANDLE h = FindFirstFile("Data Files\\*.bsa", &data);
    if (h == INVALID_HANDLE_VALUE) {
        return;
    }

    do {
        std::snprintf(path, sizeof(path), "Data Files\\%s", data.cFileName);
        BSAOpen(path);
    } while (FindNextFile(h, &data));

    FindClose(h);
}

static EntryData BSAGetEntry(BSAHash3 hash) {
    unordered_map<__int64, BSAEntry>::const_iterator it = BSAEntries.find(hash.LValue);
    if (it == BSAEntries.end()) {
        return EntryData();
    }

    BSAEntry entry = it->second;
    char* buf = new char[entry.size];
    DWORD read;

    SetFilePointer(entry.file, entry.position, 0, FILE_BEGIN);
    ReadFile(entry.file, buf, entry.size, &read, 0);

    if (read == entry.size) {
        return EntryData(buf, entry.size);
    } else {
        delete[] buf;
        return EntryData();
    }
}

static IDirect3DTexture9* BSALoadTexture2(IDirect3DDevice9* dev, const char* filename) {
    char pathbuf[MAX_PATH];
    BSAHash3 hash = BSAHashString(filename);
    IDirect3DTexture9* tex = 0;

    // First check if the texture is already loaded
    unordered_map<__int64, IDirect3DTexture9*>::const_iterator it = BSALoadedTextures.find(hash.LValue);
    if (it != BSALoadedTextures.end()) {
        it->second->AddRef();
        return it->second;
    }

    // Next check the distant land folder
    std::snprintf(pathbuf, sizeof(pathbuf), "Data Files\\distantland\\statics\\%s", filename);
    if (GetFileAttributes(pathbuf) != INVALID_FILE_ATTRIBUTES) {
        HRESULT hr = D3DXCreateTextureFromFileEx(dev, pathbuf, D3DX_FROM_FILE, D3DX_FROM_FILE, D3DX_FROM_FILE, 0, D3DFMT_UNKNOWN,
                     D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, 0, 0, &tex);
        if (hr == D3D_OK) {
            BSALoadedTextures[hash.LValue] = tex;
            return tex;
        }
    }

    // Then check the normal folder
    std::snprintf(pathbuf, sizeof(pathbuf), "Data Files\\%s", filename);
    if (GetFileAttributes(pathbuf) != INVALID_FILE_ATTRIBUTES) {
        HRESULT hr = D3DXCreateTextureFromFileEx(dev, pathbuf, D3DX_FROM_FILE, D3DX_FROM_FILE, D3DX_FROM_FILE, 0, D3DFMT_UNKNOWN,
                     D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, 0, 0, &tex);
        if (hr == D3D_OK) {
            BSALoadedTextures[hash.LValue] = tex;
            return tex;
        }
    }

    // Finally check the BSAs
    EntryData ed = BSAGetEntry(hash);
    if (ed.ptr) {
        D3DXCreateTextureFromFileInMemoryEx(dev, ed.ptr, ed.size, D3DX_FROM_FILE, D3DX_FROM_FILE, D3DX_FROM_FILE, 0, D3DFMT_UNKNOWN,
                                            D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, 0, 0, &tex);

        // Cache even if the texture load failed
        BSALoadedTextures[hash.LValue] = tex;
        return tex;
    }
    ed.release();

    // File not found
    return nullptr;
}

IDirect3DTexture9* BSALoadTexture(IDirect3DDevice9* dev, const char* filename) {
    char pathbuf[MAX_PATH];

    // Prefer loading file with DDS extension first
    std::snprintf(pathbuf, sizeof(pathbuf), "textures\\%s", filename);
    std::strcpy(pathbuf + strlen(pathbuf) - 3, "dds");

    IDirect3DTexture9* ret = BSALoadTexture2(dev, pathbuf);
    if (ret) {
        return ret;
    }

    // Load file with original extension
    std::snprintf(pathbuf, sizeof(pathbuf), "textures\\%s", filename);
    return BSALoadTexture2(dev, pathbuf);
}

void BSAClearTextureCache() {
    BSALoadedTextures.clear();
}

void BSACacheStats(int* total, int* memuse) {
    __int64 texMemUsage = 0;

    const auto& BSALoadedTextures_const = BSALoadedTextures;
    for (const auto& i : BSALoadedTextures_const) {
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

    *total = BSALoadedTextures.size();
    *memuse = (int)(texMemUsage / 1048576.0);
}
