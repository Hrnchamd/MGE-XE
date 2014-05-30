
struct RetData {
    void* ptr;
    unsigned int size;

    RetData(void* _ptr, unsigned int _size) { ptr = _ptr; size = _size; }
};

void InitBSAs();
IDirect3DTexture9* BSALoadTexture(IDirect3DDevice9 *dev, const char* filename);
void BSAClearTextureCache();
void BSACacheStats(int *total, int *memuse);
