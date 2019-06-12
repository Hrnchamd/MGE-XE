
#include "pngsave.h"

#include "support/winheader.h"
#include <algorithm>
#include <array>
#include <cstdint>
#include <vector>



struct CRC32 {
    static std::array<uint32_t, 256> table;
    uint32_t crc;

    CRC32() {
        initTable();
        reset();
    }

    void reset() {
        crc = UINT32_C(0xFFFFFFFF);
    }

    void update(const uint8_t* buffer, size_t length) {
        uint32_t c = crc;
        for (size_t n = 0; n < length; n++) {
            c = table[(c ^ buffer[n]) & 0xFF] ^ (c >> 8);
        }
        crc = c;
    }

    uint32_t get() const {
        return ~crc;
    }

    static void initTable() {
        uint32_t c;

        for (int n = 0; n < 256; n++) {
            c = uint32_t(n);
            for (int k = 0; k < 8; k++) {
                if (c & 1) {
                    c = UINT32_C(0xEDB88320) ^ (c >> 1);
                } else {
                    c = c >> 1;
                }
            }
            table[n] = c;
        }
    }
};

std::array<uint32_t, 256> CRC32::table;

struct Adler {
    const uint32_t mod_adler = 65521;
    uint32_t adler;

    Adler() : adler(1) {}

    void reset() {
        adler = 1;
    }

    void update(const uint8_t* buffer, size_t length) {
        uint32_t a = adler & 0xFFFF, b = adler >> 16;
        for (size_t n = 0; n < length; ++n) {
            a = (a + buffer[n]) % mod_adler;
            b = (b + a) % mod_adler;
        }
        adler = (b << 16) | a;
    }

    uint32_t get() const {
        return adler;
    }
};

void writeUint32BE(uint8_t* dest, uint32_t x) {
    dest[0] = uint8_t(x >> 24);
    dest[1] = uint8_t(x >> 16);
    dest[2] = uint8_t(x >> 8);
    dest[3] = uint8_t(x >> 0);
}

const std::array<uint8_t, 0x8> PNGheader = { 0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A };
const std::array<uint8_t, 0x19> IHDRunfilled = { 0, 0, 0, 0x0D, 0x49, 0x48, 0x44, 0x52, 0, 0, 0, 0, 0, 0, 0, 0, 8, 2, 0, 0, 0, 0, 0, 0, 0 };
const std::array<uint8_t, 0xA> IDATunfilled = { 0, 0, 0, 0, 0x49, 0x44, 0x41, 0x54, 0x08, 0x1D };
const std::array<uint8_t, 0xC> IENDfilled = { 0, 0, 0, 0, 0x49, 0x45, 0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82 };


// pngSaveBGRA - Non-compressing PNG encoder. Accepts BGRA data but does not save alpha.
bool pngSaveBGRA(const char* path, const void* imageData, unsigned int width, unsigned int height, unsigned int stride) {
    // Write new file.
    HANDLE hFile = CreateFile(path, GENERIC_WRITE, 0, 0, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, 0);
    if (hFile == INVALID_HANDLE_VALUE) {
        return false;
    }

    CRC32 crc;
    Adler adler;

    // PNG header.
    if (!WriteFile(hFile, PNGheader.data(), PNGheader.size(), NULL, NULL)) {
        CloseHandle(hFile);
        return false;
    }

    // IHDR chunk.
    auto IHDR = IHDRunfilled;
    writeUint32BE(&IHDR[0x8], width);
    writeUint32BE(&IHDR[0xC], height);
    crc.reset();
    crc.update(&IHDR[4], 0x11);
    writeUint32BE(&IHDR[0x15], crc.get());

    if (!WriteFile(hFile, IHDR.data(), IHDR.size(), NULL, NULL)) {
        CloseHandle(hFile);
        return false;
    }

    // IDAT chunk start. Reserve writing the size until the end.
    // Start with the size of the zlib header included in IDATstart.
    auto IDATstart = IDATunfilled;
    size_t IDATsize = 2;
    crc.reset();
    crc.update(&IDATstart[4], 0x6);

    DWORD fileOffsetIDAT = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);
    if (fileOffsetIDAT == INVALID_SET_FILE_POINTER) {
        CloseHandle(hFile);
        return false;
    }
    if (!WriteFile(hFile, IDATstart.data(), IDATstart.size(), NULL, NULL)) {
        CloseHandle(hFile);
        return false;
    }

    // Convert one scanline at a time.
    std::vector<uint8_t> scanline(3 * width + 1);
    std::array<uint8_t, 5> deflateBlockHeader = { 0, 0xFF, 0xFF, 0, 0 };
    std::vector<uint8_t> deflateBlock(deflateBlockHeader.size() + 0xFFFF);
    std::copy(deflateBlockHeader.begin(), deflateBlockHeader.end(), deflateBlock.begin());
    auto deflateBlockWriteIter = deflateBlock.begin() + deflateBlockHeader.size();

    auto pScanline = reinterpret_cast<const uint8_t*>(imageData);
    for (unsigned int y = 0; y < height; y++, pScanline += stride) {
        auto p = pScanline;
        auto it = scanline.begin();

        // Use filter type None.
        *it++ = 0;

        // Convert BGRA -> RGB while copying.
        for (unsigned int x = 0; x < width; x++, p += 4) {
            *it++ = p[2];
            *it++ = p[1];
            *it++ = p[0];
        }

        // Write scanline into deflate blocks.
        it = scanline.begin();
        while (it != scanline.end()) {
            size_t remain = scanline.end() - it;
            size_t blockRemain = deflateBlock.end() - deflateBlockWriteIter;

            if (remain <= blockRemain) {
                // Deflate block has space for all data.
                std::copy(it, it + remain, deflateBlockWriteIter);
                it += remain;
                deflateBlockWriteIter += remain;
            }
            else {
                // New deflate block is required.
                std::copy(it, it + blockRemain, deflateBlockWriteIter);
                it += blockRemain;

                crc.update(deflateBlock.data(), deflateBlock.size());
                adler.update(&deflateBlock[deflateBlockHeader.size()], deflateBlock.size() - deflateBlockHeader.size());
                deflateBlockWriteIter = deflateBlock.begin() + deflateBlockHeader.size();

                if (!WriteFile(hFile, deflateBlock.data(), deflateBlock.size(), NULL, NULL)) {
                    CloseHandle(hFile);
                    return false;
                }
                IDATsize += deflateBlock.size();
            }
        }
    }

    // Write last deflate block.
    size_t bytesRemain = deflateBlockWriteIter - deflateBlock.begin();
    size_t blockRemain = bytesRemain - deflateBlockHeader.size();
    deflateBlock[0] = 1;
    deflateBlock[1] = uint8_t(blockRemain);
    deflateBlock[2] = uint8_t(blockRemain >> 8);
    deflateBlock[3] = ~uint8_t(blockRemain);
    deflateBlock[4] = ~uint8_t(blockRemain >> 8);

    crc.update(deflateBlock.data(), bytesRemain);
    adler.update(&deflateBlock[deflateBlockHeader.size()], blockRemain);

    if (!WriteFile(hFile, deflateBlock.data(), bytesRemain, NULL, NULL)) {
        CloseHandle(hFile);
        return false;
    }
    IDATsize += bytesRemain;

    // Write deflate and IDAT chunk checksums.
    std::array<uint8_t, 8> IDATchecksums;
    writeUint32BE(&IDATchecksums[0], adler.get());
    crc.update(&IDATchecksums[0], 4);
    IDATsize += 4;
    writeUint32BE(&IDATchecksums[4], crc.get());

    if (!WriteFile(hFile, IDATchecksums.data(), IDATchecksums.size(), NULL, NULL)) {
        CloseHandle(hFile);
        return false;
    }

    // Write IDAT chunk size.
    writeUint32BE(&IDATstart[0], IDATsize);

    if (SetFilePointer(hFile, fileOffsetIDAT, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) {
        CloseHandle(hFile);
        return false;
    }
    if (!WriteFile(hFile, IDATstart.data(), sizeof(uint32_t), NULL, NULL)) {
        CloseHandle(hFile);
        return false;
    }
    if (SetFilePointer(hFile, 0, NULL, FILE_END) == INVALID_SET_FILE_POINTER) {
        CloseHandle(hFile);
        return false;
    }

    // Write IEND chunk.
    if (!WriteFile(hFile, IENDfilled.data(), IENDfilled.size(), NULL, NULL)) {
        CloseHandle(hFile);
        return false;
    }

    CloseHandle(hFile);
    return true;
}
