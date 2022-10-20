#pragma once

#include <cstdint>

struct BitMapInfoHeader {
    std::uint32_t biSize;
    std::uint32_t biWidth;
    std::uint32_t biHeight;
    std::uint16_t biPlanes;
    std::uint16_t biBitCount;
    std::uint32_t biCompression;
    std::uint32_t biSizeImage;
    std::uint32_t biXPelsPerMeter;
    std::uint32_t biYPelsPerMeter;
    std::uint32_t biClrUsed;
    std::uint32_t biClrImportant;
} __attribute__((__packed__));