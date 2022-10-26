#include "../SindromPicture/SindromPicture.hpp"

#include <algorithm>

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
    std::cerr << SizeX() << " " << SizeY() << std::endl;

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


        std::cerr << mod_delta << std::endl;

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
    if (new_y == 0) {
        throw std::invalid_argument("new_y == 0");
    }

    if (new_y < SizeY()) {
        std::size_t need_delete = SizeY() - new_y;
        std::size_t delta = SizeY() / need_delete;
        std::size_t mod = SizeY() % need_delete;
        std::size_t mod_delta = need_delete / mod + (need_delete % mod * 2 > mod);
        std::size_t cur_number_del = SizeY() - 1;


        std::cerr << mod_delta << std::endl;

        for (std::size_t i = 0; i < need_delete; ++i) {
            DeleteRow(cur_number_del);

            cur_number_del -= delta;
            if (mod > 0 && i % mod_delta == 0) {
                cur_number_del--;
                mod--;
            }
        }
    } else {
        while (SizeY() < new_y) {
            std::size_t need_to_add = (new_y - SizeY() > SizeY() ? SizeY() : new_y - SizeY());
            std::size_t delta = SizeY() / need_to_add;
            std::size_t cur_add_pos = SizeY();

            for (std::size_t i = 0; i < need_to_add; ++i) {
                PasteRow(cur_add_pos - 1, cur_add_pos);
                cur_add_pos -= delta;
            }
        }
    }
}

void SindromPicture::Scale(std::size_t new_x, std::size_t new_y) {
    ScaleX(new_x);
    ScaleY(new_y);
}