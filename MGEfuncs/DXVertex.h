#pragma once

#define WIN32_LEAN_AND_MEAN
#include "../3rdparty/niflib/include/nif_math.h"

struct DXVertex {
    Niflib::Vector3 Position;
    Niflib::Vector3 Normal;
    unsigned char Diffuse[4];
    Niflib::TexCoord texCoord;
};

struct DXCompressedVertex {
    unsigned short Position[4];
    unsigned char Normal[4];
    unsigned char Diffuse[4];
    unsigned short texCoord[2];
};

struct DXCompressedLandVertex {
    Niflib::Vector3 Position;
    short texCoord[2];
};
