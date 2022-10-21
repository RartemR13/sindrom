#pragma once

#include <cstdint>
#include <vector>

struct RGBquad {
    std::uint8_t rgbBlue;
    std::uint8_t rgbGreen;
    std::uint8_t rgbRed;
    std::uint8_t rgbReserved;

    std::uint32_t Value() const;
    RGBquad(std::uint32_t);
    RGBquad() = default;
    RGBquad(const RGBquad&) = default;
    ~RGBquad() = default;
    RGBquad(std::uint8_t, std::uint8_t, std::uint8_t, std::uint8_t);
} __attribute__((__packed__));

typedef std::vector<RGBquad> Palette;