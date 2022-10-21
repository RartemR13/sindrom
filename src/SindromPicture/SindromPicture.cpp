#include "../SindromPicture/SindromPicture.hpp"

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
    std::vector<std::vector<RGBquad>> new_storage(storage_.size() + 2, std::vector<RGBquad>(storage_.front().size() + 2));

    for (std::size_t i = 1; i <= storage_.size(); ++i) {
        for (std::size_t j = 1; j <= storage_.front().size(); ++j) {
            new_storage[i][j] = storage_[i-1][j-1];
        }
    }

    for (std::size_t i = 1; i <= storage_.size(); ++i) {
        new_storage[i][0] = new_storage[i][1];
        new_storage[i][new_storage[i].size() - 1] = new_storage[i][new_storage[i].size() - 2]; 
    }

    for (std::size_t j = 1; j <= storage_.front().size(); ++j) {
        new_storage[0][j] = new_storage[1][j];
        new_storage[new_storage.size() - 1][j] = new_storage[new_storage.size() - 2][j];
    }

    new_storage[0][0] = (1ll * new_storage[0][1].Value() + new_storage[1][0].Value()) / 2;
    new_storage[new_storage.size() - 1][0] = (1ll * new_storage[new_storage.size() - 1][1].Value() + new_storage[new_storage.size() - 2][0].Value()) / 2;
    new_storage[0][new_storage.front().size() - 1] = (1ll * new_storage[0][new_storage.front().size() - 2].Value() + new_storage[1][new_storage.front().size() - 1].Value()) / 2;
    new_storage[new_storage.size() - 1][new_storage.front().size() - 1] = (1ll * new_storage[new_storage.size() - 1][new_storage.front().size() - 2].Value() + new_storage[new_storage.size() - 2][new_storage.front().size() - 1].Value()) / 2;

    storage_ = new_storage;
}

void SindromPicture::RemBoards() {
    std::vector<std::vector<RGBquad>> new_storage(storage_.size() - 2, std::vector<RGBquad>(storage_.front().size() - 2));

    for (std::size_t i = 1; i < storage_.size() - 1; ++i) {
        for (std::size_t j = 1; j < storage_[i].size() - 1; ++j) {
            new_storage[i-1][j-1] = storage_[i][j];
        }
    }

    storage_ = new_storage;
}