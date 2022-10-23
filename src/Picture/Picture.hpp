#pragma once

#include <cstdint>
#include <vector>
#include <string>

#include "../BMPHelpers/BMPHelpers.hpp"
#include "../Matrix/Matrix.hpp"

class Picture : public Matrix<RGBquad> {
public:
    Picture() = delete;
    Picture(const Picture&) = default;
    ~Picture() = default;
    Picture(const std::string&);

    void Load(const std::string&);
    void Save(const std::string&);

protected:
    std::uint32_t XPelsPerMeter_;
    std::uint32_t YPelsPerMeter_;
};
