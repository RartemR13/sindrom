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

    void ScaleX(std::size_t);
    void ScaleY(std::size_t);

    void Scale(std::size_t, std::size_t);
    void ImproveDefinition();

    void AddBoards();
    void RemBoards();
};