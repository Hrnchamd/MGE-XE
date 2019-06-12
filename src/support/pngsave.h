#pragma once

// pngSaveBGRA - Non-compressing PNG encoder. Accepts BGRA data but does not save alpha.
bool pngSaveBGRA(const char* path, const void* data, unsigned int width, unsigned int height, unsigned int stride);
