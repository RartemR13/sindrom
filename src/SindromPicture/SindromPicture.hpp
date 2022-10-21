#pragma once

#include "../Picture/Picture.hpp"

class SindromPicture : public Picture {
public:
    SindromPicture() = delete;
    SindromPicture(const SindromPicture&) = default;
    ~SindromPicture() = default;

    SindromPicture(const std::string& file_path) :
        Picture(file_path)
    {}

    void ReplaceColor(RGBquad, RGBquad);
    void Negative();

private:
    void AddBoards();
    void RemBoards();
};