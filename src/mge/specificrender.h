#pragma once

#include "proxydx/d3d9header.h"



class VendorSpecificRendering {
    static const D3DFORMAT D3DFMT_ATOC = (D3DFORMAT)MAKEFOURCC('A','T','O','C');
    static const D3DFORMAT D3DFMT_A2M0 = (D3DFORMAT)MAKEFOURCC('A','2','M','0');
    static const D3DFORMAT D3DFMT_A2M1 = (D3DFORMAT)MAKEFOURCC('A','2','M','1');

    enum { ATOC_NONE, ATOC_ADAPTIVETESS, ATOC_POINTSIZE } alphaToCoverageMode;

public:
    void init(IDirect3DDevice9* device);
    void beginAlphaToCoverage(IDirect3DDevice9* device);
    void endAlphaToCoverage(IDirect3DDevice9* device);
};
