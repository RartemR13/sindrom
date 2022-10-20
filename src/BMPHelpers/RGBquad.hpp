#pragma once

#include <cstdint>

struct RGBquad {
    std::uint8_t rgbBlue;
    std::uint8_t rgbGreen;
    std::uint8_t rgbRed;
    std::uint8_t rgbReserved;
};

typedef std::vector<RGBquad> Palette;