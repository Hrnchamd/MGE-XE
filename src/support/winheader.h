#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// Remove annoying defines from windows.h
#undef near
#undef far
#undef NEAR
#undef FAR
#define NEAR
#define FAR