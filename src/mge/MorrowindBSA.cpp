
#include <map>
#include "proxydx/d3d8header.h"
#include "support/strsec.h"
#include "MorrowindBSA.h"

struct BSAEntry {
    HANDLE file;
    DWORD position;
    DWORD size;
};

struct BSAHash3 {
    union {
        struct {
            DWORD value1;
            DWORD value2;
        };
        __int64 LValue;
    };
};

static std::map<__int64, BSAEntry> BSAEntries;
static std::map<__int64, IDirect3DTexture9*> BSALoadedTextures;

static BSAHash3 HashString(const char* str) {
    BSAHash3 result;

    unsigned int len = (unsigned int)strlen(str);

    //Use GhostWheel's code to hash the string
    unsigned int l = (len>>1);
    unsigned int sum, off, temp, i, n;

    for(sum = off = i = 0; i < l; i++){
        sum ^= ((unsigned int)(str[i])) << (off&0x1F);
        off += 8;
    }
    result.value1 = sum;

    for(sum = off = 0; i < len; i++) {
        temp = ((unsigned int)(str[i])) << (off&0x1F);
        sum ^= temp;
        n = temp & 0x1F;
        sum = (sum << (32-n)) | (sum >> n);  // binary "rotate right"
        off += 8;
    }
    result.value2 = sum;
    return result;
}

static void OpenBSA(const char* path) {
    HANDLE bsa;
    bsa = CreateFile(path, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
    if(bsa == INVALID_HANDLE_VALUE) return;

    DWORD hashoffset, numfiles, unused;
    ReadFile(bsa, &hashoffset, 4, &unused, 0);
    if(unused !=4 || hashoffset != 0x100) {
        CloseHandle(bsa);
        return;
    }

    ReadFile(bsa, &hashoffset, 4, &unused, 0);
    ReadFile(bsa, &numfiles, 4, &unused, 0);
    for(DWORD i = 0; i < numfiles; i++) {
        BSAEntry entry;
        __int64 hash;

        entry.file = bsa;
        SetFilePointer(bsa, 12 + i*8, 0, FILE_BEGIN);
        ReadFile(bsa, &entry.size, 4, &unused, 0);
        ReadFile(bsa, &entry.position, 4, &unused, 0);
        entry.position += 12 + hashoffset + numfiles*8;
        SetFilePointer(bsa, 12+hashoffset + i*8, 0, FILE_BEGIN);
        ReadFile(bsa, &hash, 8, &unused, 0);
        BSAEntries[hash]=entry;
    }
}

void InitBSAs() {
    char path[MAX_PATH];
    WIN32_FIND_DATA data;
    HANDLE h = FindFirstFile("data files\\*.bsa", &data);
    if(h == INVALID_HANDLE_VALUE) return;

    strcpy(path, "data files\\");
    strcat(path, data.cFileName);
    OpenBSA(path);

    while(FindNextFile(h, &data)) {
        strcpy(path, "data files\\");
        strcat(path, data.cFileName);
        OpenBSA(path);
    }
    FindClose(h);
}

static RetData GetBSAEntry(BSAHash3 hash) {
    std::map<__int64, BSAEntry>::const_iterator it = BSAEntries.find(hash.LValue);
    if(it == BSAEntries.end()) return RetData(0, 0);
    BSAEntry entry = it->second;

    SetFilePointer(entry.file, entry.position, 0, FILE_BEGIN);
    char* buf = new char[entry.size];
    DWORD read;
    ReadFile(entry.file, buf, entry.size, &read, 0);
    if(read != entry.size) { delete[] buf; return RetData(0, 0); }
    return RetData(buf, entry.size);
}

static IDirect3DTexture9* BSALoadTexture2(IDirect3DDevice9 *dev, const char* filename) {
    char pathbuf[MAX_PATH];
    HANDLE file;
    BSAHash3 hash = HashString(filename);
    IDirect3DTexture9* tex = 0;

    // First check if the texture is already loaded
    std::map<__int64, IDirect3DTexture9*>::const_iterator it = BSALoadedTextures.find(hash.LValue);
    if(it != BSALoadedTextures.end()) {
        it->second->AddRef();
        return it->second;
    }
    // Next check the distant land folder
    strcpy(pathbuf, "data files\\distantland\\statics\\");
    strcat_s(pathbuf, MAX_PATH, filename);
    file = CreateFile(pathbuf, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
    if(file != INVALID_HANDLE_VALUE) {
        CloseHandle(file);
        HRESULT hr = D3DXCreateTextureFromFileEx(dev, pathbuf, 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, 0, 0, &tex);
        if(!FAILED(hr)) {
            BSALoadedTextures[hash.LValue] = tex; //Want to cache this even if the texture load failed;
            return tex;
        } else tex = 0;
    }
    // Then check the normal folder
    strcpy(pathbuf, "data files\\");
    strcat_s(pathbuf, MAX_PATH, filename);
    file = CreateFile(pathbuf, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
    if(file != INVALID_HANDLE_VALUE) {
        CloseHandle(file);
        HRESULT hr = D3DXCreateTextureFromFileEx(dev, pathbuf, 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, 0, 0, &tex);
        if(!FAILED(hr)) {
            BSALoadedTextures[hash.LValue] = tex; //Want to cache this even if the texture load failed;
            return tex;
        } else tex = 0;
    }
    // Finally check the BSAs
    RetData rd = GetBSAEntry(hash);
    if(rd.ptr) {
        D3DXCreateTextureFromFileInMemoryEx(dev, rd.ptr, rd.size, 0,0,0,0, D3DFMT_UNKNOWN,
                    D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0,0,0, &tex);
        delete [] (char *)rd.ptr;
        BSALoadedTextures[hash.LValue] = tex; //Want to cache this even if the texture load failed;
        return tex;
    }

    // File not found
    return 0;
}

IDirect3DTexture9* BSALoadTexture(IDirect3DDevice9 *dev, const char* filename) {
    char fname[MAX_PATH];
    strcpy(fname, "textures\\");
    strcat(fname, filename);

    // try loading dds first
    DWORD len = strlen(fname);
    if(fname[len-1] != 's' || fname[len-2] != 'd' || fname[len-3] != 'd') {
        char fname2[MAX_PATH];
        strcpy(fname2, fname);
        fname2[len-1] = 's';
        fname2[len-2] = 'd';
        fname2[len-3] = 'd';
        IDirect3DTexture9* ret = BSALoadTexture2(dev, fname2);
        if(ret) return ret;
    }

    return BSALoadTexture2(dev, fname);
}

void BSAClearTextureCache() {
    BSALoadedTextures.clear();
}

void BSACacheStats(int *total, int *memuse) {
    __int64 texMemUsage = 0;

    for(std::map<__int64, IDirect3DTexture9*>::const_iterator i = BSALoadedTextures.begin(); i != BSALoadedTextures.end(); ++i)
    {
        D3DSURFACE_DESC texdesc;
        i->second->GetLevelDesc(0, &texdesc);

        int bpp = 32;
        if(texdesc.Format == D3DFMT_DXT1) bpp = 4;
        if(texdesc.Format == D3DFMT_DXT3 || texdesc.Format == D3DFMT_DXT5) bpp = 8;

        texMemUsage += (texdesc.Width * texdesc.Height * bpp / 8) * 4 / 3;
    }

    *total = BSALoadedTextures.size();
    *memuse = (int)(texMemUsage / 1048576.0);
}
