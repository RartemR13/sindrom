#pragma once

#include <vector>
#include <stdexcept>

template<typename T>
class Matrix {
public:
    Matrix() = default;
    Matrix(const Matrix& to_copy) = default;
    Matrix(const Matrix& to_copy, std::size_t x, std::size_t y, std::size_t dx, std::size_t dy) {storage_ = to_copy.Cut(x, y, dx, dy).GetStorage();}
    Matrix(const std::vector<std::vector<T>>& from) { storage_ = from;}
    ~Matrix() = default;

    void SetStorage(const std::vector<std::vector<T>>& from) {storage_ = from;};

    std::vector<T>& operator[] (std::size_t row_number) {return storage_[row_number];}
    const std::vector<T>& operator[] (std::size_t row_number) const {return storage_[row_number];}

    std::size_t SizeY() const {return storage_.size();};
    std::size_t SizeX() const {return (SizeY() > 0 ? storage_[0].size() : 0);};

    T Sum() {
        T res = 0;
        for (std::size_t i = 0; i < SizeY(); ++i) {
            for (std::size_t j = 0; j < SizeX(); ++j) {
                res += storage_[i][j];
            }
        }

        return res;
    };

    Matrix<T> Cut(std::size_t x, std::size_t y, std::size_t dx, std::size_t dy) {
        if (x + dx > SizeX() || y + dy > SizeY()) {
            throw std::invalid_argument("matrix limits overflow");
        }

        std::vector<std::vector<T>> res(dy);
        for (std::size_t i = y; i < y + dy; ++i) {
            res[i - y].insert(res[i - y].begin(), storage_[y].begin() + x, storage_[y].begin() + x + dx);
        }

        return Matrix<T>(res);
    }

    const std::vector<std::vector<T>>& GetStorage() const {return storage_;}

    template<typename Tf>
    friend Matrix<Tf> CoefMult(const Matrix<Tf>& lhs, const Matrix<Tf>& rhs);
protected:
    std::vector<std::vector<T>> storage_;
};

template<typename T>
Matrix<T> CoefMult(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    if (lhs.SizeX() != rhs.SizeX() || lhs.SizeY() != rhs.SizeY()) {
        throw std::invalid_argument("different sizes of matrixes");
    }

    auto res = lhs;
    for (std::size_t i = 0; i < res.SizeY(); ++i) {
        for (std::size_t j = 0; j < res.SizeX(); ++j) {
            res[i][j] *= rhs[i][j];
        }
    }

    return res;
}