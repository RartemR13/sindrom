#include "../SindromPicture/SindromPicture.hpp"

#include <algorithm>
#include <cmath>

void SindromPicture::ReplaceColor(RGBquad from, RGBquad to) {
    for (std::size_t i = 0; i < storage_.size(); ++i) {
        for (std::size_t j = 0; j < storage_[i].size(); ++j) {
            if (storage_[i][j] == from) {
                storage_[i][j] = to;
            }
        }
    }
}

void SindromPicture::Negative() {
    for (std::size_t i = 0; i < storage_.size(); ++i) {
        for (std::size_t j = 0; j < storage_[i].size(); ++j) {
            auto curPixel = storage_[i][j];

            curPixel.rgbBlue = 255 - curPixel.rgbBlue;
            curPixel.rgbGreen = 255 - curPixel.rgbGreen;
            curPixel.rgbRed = 255 - curPixel.rgbRed;
            storage_[i][j] = curPixel;
        }
    }
}

void SindromPicture::AddBoards() {
    PasteRow(SizeY() - 1, SizeY());
    PasteRow(0, 0);

    PasteColumn(SizeX() - 1, SizeX());
    PasteColumn(0, 0);
}

void SindromPicture::RemBoards() {
    DeleteRow(SizeY() - 1);
    DeleteRow(0);

    DeleteColumn(SizeX() - 1);
    DeleteColumn(0);
}

void SindromPicture::ScaleX(std::size_t new_x) {
    if (new_x == 0) {
        throw std::invalid_argument("new_x == 0");
    }

    if (new_x < SizeX()) {
        std::size_t need_delete = SizeX() - new_x;
        std::size_t delta = SizeX() / need_delete;
        std::size_t mod = SizeX() % need_delete;
        std::size_t mod_delta = need_delete / mod + (need_delete % mod * 2 > mod);
        std::size_t cur_number_del = SizeX() - 1;

        for (std::size_t i = 0; i < need_delete; ++i) {
            DeleteColumn(cur_number_del);

            cur_number_del -= delta;
            if (mod > 0 && i % mod_delta == 0) {
                cur_number_del--;
                mod--;
            }
        }
    } else {
        while (SizeX() < new_x) {
            std::size_t need_to_add = (new_x - SizeX() > SizeX() ? SizeX() : new_x - SizeX());
            std::size_t delta = SizeX() / need_to_add;
            std::size_t cur_add_pos = SizeX();

            for (std::size_t i = 0; i < need_to_add; ++i) {
                PasteColumn(cur_add_pos - 1, cur_add_pos);
                cur_add_pos -= delta;
            }
        }
    }
}

void SindromPicture::ScaleY(std::size_t new_y) {
    Transposition();
    ScaleX(new_y);
    Transposition();
}

void SindromPicture::Scale(std::size_t new_x, std::size_t new_y) {
    ScaleX(new_x);
    ScaleY(new_y);
}

template<typename T>
std::vector<Matrix<T>> MakeChanelsMatrixes(const Matrix<RGBquad>& to_parse) {
    std::vector<Matrix<T>> ret(4);

    for (std::size_t c = 0; c < 4; ++c) {
        std::vector<std::vector<T>> to_cur_chanel(to_parse.SizeY(), std::vector<T>(to_parse.SizeX()));

        for (std::size_t i = 0; i < to_parse.SizeY(); ++i) {
            for (std::size_t j = 0; j < to_parse.SizeX(); ++j) {
                to_cur_chanel[i][j] = static_cast<T>(to_parse[i][j][c]);
            }
        }

        ret[c] = to_cur_chanel;
    }

    return ret;
}

Matrix<RGBquad> MakeRGBquadMatrix(const std::vector<Matrix<std::uint8_t>>& to_parse) {
    auto ret = std::vector<std::vector<RGBquad>>(to_parse.front().SizeY(), std::vector<RGBquad>(to_parse.front().SizeX()));

    for (std::size_t c = 0; c < 4; ++c) {
        for (std::size_t i = 0; i < to_parse.front().SizeY(); ++i) {
            for (std::size_t j = 0; j < to_parse.front().SizeX(); ++j) {
                ret[i][j][c] = to_parse[c][i][j];
            }
        }
    }

    return ret;
}

void SindromPicture::UseKoefMatrix(const Matrix<double>& koef_matrix) {
    for (std::size_t i = 0; i < koef_matrix.SizeY() / 2; ++i) {
        AddBoards();
    }

    auto chanels_matrixes = MakeChanelsMatrixes<std::int32_t>(*this);
    std::vector<Matrix<std::uint8_t>> result_chanels_matrixes(4);

    for (std::size_t c = 0; c < 4; ++c) {        
        std::vector<std::vector<std::uint8_t>> cur_chanel_res_matrix(SizeY(),std::vector<std::uint8_t>(SizeX()));
        for (std::size_t i = koef_matrix.SizeY() - 1; i < SizeY() - 1; ++i) {
            for (std::size_t j = koef_matrix.SizeY() - 1; j < SizeX() - 1; ++j) {
                auto cur_pixels = chanels_matrixes[c].Cut(j + 1 - koef_matrix.SizeY(), i + 1 - koef_matrix.SizeY(), koef_matrix.SizeY(), koef_matrix.SizeY());
                auto koef_multi_pixels = CoefMult(Matrix<double>(cur_pixels), koef_matrix);

                std::int64_t pixels_sum = static_cast<std::int64_t>(koef_multi_pixels.Sum());
                pixels_sum = std::max(static_cast<std::int64_t>(0), pixels_sum);
                pixels_sum = std::min(pixels_sum, static_cast<std::int64_t>(255));

                cur_chanel_res_matrix[i - koef_matrix.SizeY() / 2][j - koef_matrix.SizeY() / 2] = static_cast<std::uint8_t>(pixels_sum);
            }
        }
        result_chanels_matrixes[c] = cur_chanel_res_matrix;
    }

    storage_ = MakeRGBquadMatrix(result_chanels_matrixes).GetStorage();

    for (std::size_t i = 0; i < koef_matrix.SizeY() / 2; ++i) {
        RemBoards();
    }
}

void SindromPicture::ImproveDefinition() {
    Matrix<double> koef_matrix = std::vector<std::vector<double>>
                                 {{-1, -1, -1},
                                  {-1, 9, -1},
                                  {-1, -1, -1}};
    UseKoefMatrix(koef_matrix);
}

void SindromPicture::Gauss() {
    Matrix<double> koef_matrix = std::vector<std::vector<double>>
                                 {{0.000789, 0.006581, 0.013347, 0.006581, 0.000789},
                                  {0.006581, 0.054901, 0.111345, 0.054901, 0.006581},
                                  {0.013347, 0.111345, 0.255821, 0.111345, 0.013347},
                                  {0.006581, 0.054901, 0.111345, 0.054901, 0.006581},
                                  {0.000789, 0.006581, 0.013347, 0.006581, 0.000789}};
    UseKoefMatrix(koef_matrix);
}

void SindromPicture::Median() {
    AddBoards();

    auto chanels_matrixes = MakeChanelsMatrixes<std::int32_t>(*this);
    std::vector<Matrix<std::uint8_t>> result_chanels_matrixes(4);

    for (std::size_t c = 0; c < 4; ++c) {
        std::vector<std::vector<std::uint8_t>> cur_chanel_res_matrix(SizeY(),std::vector<std::uint8_t>(SizeX()));

        for (std::size_t i = 2; i < SizeY(); ++i) {
            for (std::size_t j = 2; j < SizeX(); ++j) {
                auto cur_pixels = chanels_matrixes[c].Cut(j - 2, i - 2, 3, 3);
                auto cur_pixels_dump = cur_pixels.Dump();

                std::sort(cur_pixels_dump.begin(), cur_pixels_dump.end());
                cur_chanel_res_matrix[i][j] = cur_pixels_dump[5];
            }
        }

        result_chanels_matrixes[c] = cur_chanel_res_matrix;
    }

    storage_ = MakeRGBquadMatrix(result_chanels_matrixes).GetStorage();
    RemBoards();
}

void SindromPicture::MakeGrey() {
    std::vector<double> chanels_coefs = {0.114, 0.587, 0.299, 1.0};

    for (std::size_t i = 0; i < SizeY(); ++i) {
        for (std::size_t j = 0; j < SizeX(); ++j) {
            double cur_pixel_sum = 0;
            for (std::size_t c = 0; c < 4; ++c) {
                cur_pixel_sum += storage_[i][j][c] * chanels_coefs[c];
            }

            for (std::size_t c = 0; c < 4; ++c) {
                storage_[i][j][c] = static_cast<std::uint8_t>(cur_pixel_sum); 
            }
        }
    }
}

void SindromPicture::EdgeDetection(std::uint8_t thres_hold) {
    MakeGrey();

    Matrix<double> koef_matrix = std::vector<std::vector<double>>
                                 {{0, -1, 0},
                                  {-1, 4, -1},
                                  {0, -1, 0}};
    UseKoefMatrix(koef_matrix);

    for (std::size_t i = 0; i < SizeY(); ++i) {
        for (std::size_t j = 0; j < SizeX(); ++j) {
            for (std::size_t c = 0; c < 4; ++c) {
                storage_[i][j][c] = (storage_[i][j][c] > thres_hold ? 255 : 0);
            }
        }
    }
}

double PseudoDist(std::int64_t x1, std::int64_t y1, std::int64_t x2, std::int64_t y2) {
    return std::sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void SindromPicture::Viniet(std::size_t viniet_koef) {
    std::size_t centre_X = SizeX() / 2;
    std::size_t centre_Y = SizeY() / 2;

    for (std::size_t i = 0; i < SizeY(); ++i) {
        for (std::size_t j = 0; j < SizeX(); ++j) {
            if (PseudoDist(j, i, centre_X, centre_Y)  / viniet_koef < 1.0) {
                continue;
            }

            for (std::size_t c = 0; c < 4; ++c) {
                storage_[i][j][c] = static_cast<std::uint8_t>(storage_[i][j][c] * (1.0 / (PseudoDist(j, i, centre_X, centre_Y) / viniet_koef)));
            }
        }
    }
}