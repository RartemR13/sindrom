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
    void UseKoefMatrix(const Matrix<double>& koef_matrix);
    void ImproveDefinition();
    void Gauss();

    void AddBoards();
    void RemBoards();

    void Median();
    void MakeGrey();

    void EdgeDetection(std::uint8_t thres_hold);
    void Viniet(std::size_t viniet_koef);
};