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

///////////////////////////////////////////////////////////////////////
//// GL MATRIXES

inline Matrix<4, 4> translate(int x, int y, int z) {
    Matrix mat = MatrixIdentity<4>();
    mat[0][3]  = x;
    mat[1][3]  = y;
    mat[2][3]  = z;
    return mat;
}

inline Matrix<4, 4> rotatex(float angle) {
    Matrix mat = MatrixIdentity<4>();
    mat[1][1]  = std::cos(angle);
    mat[1][2]  = -std::sin(angle);
    mat[2][1]  = std::sin(angle);
    mat[2][2]  = std::cos(angle);
    return mat;
}

inline Matrix<4, 4> rotatey(float angle) {
    Matrix mat = MatrixIdentity<4>();
    mat[0][0]  = std::cos(angle);
    mat[0][2]  = std::sin(angle);
    mat[2][0]  = -std::sin(angle);
    mat[2][2]  = std::cos(angle);
    return mat;
}

inline Matrix<4, 4> rotatez(float angle) {
    Matrix mat = MatrixIdentity<4>();
    mat[0][0]  = std::cos(angle);
    mat[0][1]  = -std::sin(angle);
    mat[1][0]  = std::sin(angle);
    mat[1][1]  = std::cos(angle);
    return mat;
}

inline Matrix<4, 4> shear(float x, float y) {
    Matrix mat = MatrixIdentity<4>();
    mat[0][1]  = x;
    mat[1][0]  = y;
    return mat;
}

inline Matrix<4, 4> viewport(int x, int y, int w, int h) {
    Matrix mat = MatrixIdentity<4>();
    mat[0][0]  = w / 2;
    mat[1][1]  = -h / 2; // Negativo para hacer un flip vertical
    mat[2][2]  = 255 / 4;

    mat[0][3] = w / 2 + x;
    mat[1][3] = h / 2 + y;
    mat[2][3] = 255 / 4;
    return mat;
}

// inline Matrix<4, 4> perpective(float fovDegree, float aspectRatio, float znear, float zfar) {
//     Matrix mat    = MatrixIdentity<4>();
//     float tanHalf = 1.0f / std::tan(fovDegree * (3.1416f / 180.0f));

//     // mat[0][0] = 1.0f / (aspectRatio * tanHalf);
//     // mat[1][1] = 1.0f / tanHalf;
//     // mat[2][2] = -((zfar + znear) / (zfar - znear));

//     // mat[3][2] = -(2.0f * zfar * znear) / (zfar - znear);
//     // mat[2][3] = -1.0f;

//     mat[0][0] = 1.0f / (aspectRatio * tanHalf);
//     mat[1][1] = 1.0f / tanHalf;
//     mat[2][2] = (zfar) / (zfar - znear);

//     mat[2][3] = -(zfar * znear) / (zfar - znear);
//     mat[3][2] = 1.0f;
//     return mat;
// }

inline Matrix<4, 4> simpleProjection(float fovDegree, float aspectRatio, int zDistance) {
    Matrix mat = MatrixIdentity<4>();
    float tanHalf = std::tan(fovDegree * (3.1416f / 180.0f) / 2);
    mat[0][0] = 1.0f / (aspectRatio * tanHalf);
    mat[1][1] = 1.0f / tanHalf;
    mat[3][2]  = -1 / (float)zDistance;
    return mat;
}

#endif // __MATRIX_H__