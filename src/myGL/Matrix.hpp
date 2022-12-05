#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <array>
#include <iostream>

#include "Vector.hpp"

template <int rows, int columns>
struct Matrix {
    std::array<std::array<float, columns>, rows> data;

    Matrix() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++)
                data[i][j] = 0.0f;
        }
    }

    Matrix(const Matrix<rows, columns>& cpymat) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++)
                data[i][j] = cpymat[i][j];
        }
    }

    Matrix& operator=(const Matrix& cpymat) {
        if (this == &cpymat) return *this;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++)
                data[i][j] = cpymat[i][j];
        }

        return *this;
    }

    ~Matrix() {}

    std::array<float, columns>& operator[](int index) { return data[index]; };
    const std::array<float, columns>& operator[](int index) const { return data[index]; };

    friend std::ostream& operator<<(std::ostream& out, const Matrix& mat) {
        for (int i = 0; i < rows; i++) {
            out << "[ ";
            for (int j = 0; j < columns; j++) {
                out << mat[i][j] << " ";
            }
            out << "]\n";
        }
        return out;
    }

    template <int mat2Columns>
    Matrix<rows, columns> operator*(const Matrix<columns, mat2Columns>& rhs) {
        Matrix<rows, mat2Columns> res;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < mat2Columns; j++) {
                for (int item = 0; item < columns; item++) {
                    res[i][j] += data[i][item] * rhs[item][j];
                }
            }
        }
        return res;
    }

    vec<rows, float> operator*(const vec<columns, float>& rhs) {
        vec<rows, float> res {};
        for (int i = 0; i < rows; i++) {
            for (int item = 0; item < columns; item++) {
                res[i] += data[i][item] * rhs[item];
            }
        }
        return res;
    }

    friend const Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
        Matrix<rows, columns> res;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                res[i][j] = lhs[i][j] + rhs[i][j];
            }
        }
        return res;
    }

    friend const Matrix operator-(const Matrix& lhs, const Matrix& rhs) {
        Matrix<rows, columns> res;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                res[i][j] = lhs[i][j] - rhs[i][j];
            }
        }
        return res;
    }
};

template <int size>
static Matrix<size, size> MatrixIdentity() {
    Matrix<size, size> mat;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            mat[i][j] = (i == j) ? 1 : 0;
        }
    }
    return mat;
}



#endif // __MATRIX_H__