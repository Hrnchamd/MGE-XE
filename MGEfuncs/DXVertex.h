#pragma once

#define WIN32_LEAN_AND_MEAN
#include <nif_math.h>

using namespace Niflib;

struct DXVertex {
    Vector3 Position;
    Vector3 Normal;
    unsigned char Diffuse[4];
    TexCoord texCoord;
};

struct DXCompressedVertex {
    unsigned short Position[4];
    unsigned char Normal[4];
    unsigned char Diffuse[4];
    unsigned short texCoord[2];
};

struct DXCompressedLandVertex {
    Vector3 Position;
    short texCoord[2];
};
