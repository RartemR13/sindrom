#pragma once

#include <cstdint>
#include <vector>
#include <stdexcept>

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

    operator std::uint32_t() const {
        return Value();
    }

    const std::uint8_t& operator[] (std::size_t byte_num) const {
        switch (byte_num)
        {
        case 0:
            return rgbBlue;
            break;
        case 1:
            return rgbGreen;
            break;
        case 2:
            return rgbRed;
        case 3:
            return rgbReserved;
            break;
        default:
            throw std::runtime_error("error byte");
            break;
        }
    }

    std::uint8_t& operator[] (std::size_t byte_num) {
        switch (byte_num)
        {
        case 0:
            return rgbBlue;
            break;
        case 1:
            return rgbGreen;
            break;
        case 2:
            return rgbRed;
        case 3:
            return rgbReserved;
            break;
        default:
            throw std::runtime_error("error byte");
            break;
        }
    }
} __attribute__((__packed__));

typedef std::vector<RGBquad> Palette;

bool operator== (const RGBquad& lhs, const RGBquad& rhs);
std::istream& operator>>(std::istream& in, RGBquad& to_read);
