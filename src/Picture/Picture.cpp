#include "Picture.hpp"

#include <fstream>

void Picture::Load(const std::string& file_path) {
    std::ifstream file_input(file_path, std::ios::binary);

    BitMapFileHeader bmfh;
    BitMapInfoHeader bmih;

    file_input.read(reinterpret_cast<char*>(&bmfh), sizeof(bmfh));
    file_input.read(reinterpret_cast<char*>(&bmih), sizeof(bmih));

    XPelsPerMeter_ = bmih.biXPelsPerMeter;
    YPelsPerMeter_ = bmih.biYPelsPerMeter;
    
    Palette palette;
    palette.resize(bmih.biClrUsed);
    for (std::size_t i = 0; i < palette.size(); ++i) {
        file_input.read(reinterpret_cast<char*>(&palette[i]), sizeof(palette[i]));
    }

    storage_.resize(bmih.biHeight);
    file_input.seekg(bmfh.bfOffBits, file_input.beg);
    
    if (bmih.biBitCount == 32) {
        for (std::size_t i = 0; i < storage_.size(); ++i) {
            storage_[i].resize(bmih.biWidth);
            for (std::size_t j = 0; j < storage_[i].size(); ++j) {
                file_input.read(reinterpret_cast<char*>(&storage_[i][j]), sizeof(storage_[i][j]));
            }
        }
    } else if (bmih.biBitCount == 24) {
        for (std::size_t i = 0; i < storage_.size(); ++i) {
            storage_[i].resize(bmih.biWidth);
            for (std::size_t j = 0; j < storage_[i].size(); ++j) {
                file_input.read(reinterpret_cast<char*>(&storage_[i][j]), sizeof(storage_[i][j]) - 1);
                storage_[i][j].rgbReserved = 0;
            }
        }
    } else if (bmih.biBitCount == 8) {
        std::uint8_t palette_color_number;
        for (std::size_t i = 0; i < storage_.size(); ++i) {
            storage_[i].resize(bmih.biWidth);
            for (std::size_t j = 0; j < storage_[i].size(); ++j) {
                file_input.read(reinterpret_cast<char*>(&palette_color_number), sizeof(palette_color_number));
                storage_[i][j] = palette[palette_color_number];
            }
        }
    }
}

void Picture::Save(const std::string& file_path) {
    std::ofstream file_output(file_path, std::ios::binary);

    BitMapFileHeader bmfh = {
        .bfType = static_cast<std::uint16_t>(0x4D42),
        .bfSize = sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader) + 4 * storage_.size() * storage_.front().size(),
        .bfReserved1 = static_cast<std::uint16_t>(0),
        .bfReserved2 = static_cast<std::uint16_t>(0),
        .bfOffBits = sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader)
    };
    file_output.write(reinterpret_cast<char*>(&bmfh), sizeof(bmfh));

    BitMapInfoHeader bmih = {
        .biSize = sizeof(BitMapInfoHeader),
        .biWidth = storage_.front().size(),
        .biHeight = storage_.size(),
        .biPlanes = 1,
        .biBitCount = 32,
        .biCompression = 0,
        .biSizeImage = bmfh.bfSize - sizeof(BitMapFileHeader) - sizeof(BitMapInfoHeader),
        .biXPelsPerMeter = XPelsPerMeter_,
        .biYPelsPerMeter = YPelsPerMeter_,
        .biClrUsed = 0,
        .biClrImportant = 0
    };
    file_output.write(reinterpret_cast<char*>(&bmih), sizeof(bmih));

    for (std::size_t i = 0; i < storage_.size(); ++i) {
        for (std::size_t j = 0; j < storage_[i].size(); ++j) {
            file_output.write(reinterpret_cast<char*>(&storage_[i][j]), sizeof(storage_[i][j]));
        }
    }
}

Picture::Picture(const std::string& file_path) {
    Load(file_path);
}

std::vector<RGBquad>& Picture::operator[] (std::size_t row_number) {
    return storage_[row_number];
}

bool operator== (const RGBquad& lhs, const RGBquad& rhs) {
    return lhs.Value() == 
           rhs.Value();
}

std::uint32_t RGBquad::Value() const {
    std::uint32_t ret = *reinterpret_cast<const std::uint32_t*>(this);
    return ret;
}

RGBquad::RGBquad(std::uint32_t val) {
    *reinterpret_cast<std::uint32_t*>(this) = val;
}

RGBquad::RGBquad(std::uint8_t b, std::uint8_t g, std::uint8_t r, std::uint8_t a) {
    rgbBlue = b;
    rgbGreen = g;
    rgbRed = r;
    rgbReserved = a;
}