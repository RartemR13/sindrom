#pragma once

#include <cstdint>
#include <vector>
#include <string>

#include "../BMPHelpers/BMPHelpers.hpp"

class Picture {
public:
    Picture() = delete;
    Picture(const Picture&) = default;
    ~Picture() = default;
    Picture(const std::string&);

    void Load(const std::string&);
    void Save(const std::string&);
    std::vector<RGBquad>& operator[] (std::size_t);

protected:
    std::vector<std::vector<RGBquad>> storage_;

    std::uint32_t XPelsPerMeter_;
    std::uint32_t YPelsPerMeter_;
};

bool operator== (const RGBquad& lhs, const RGBquad& rhs);