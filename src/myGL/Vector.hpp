#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <iostream>

template <int size, typename type>
struct vec {
    type data[size] {};

    vec() {};

    vec(const vec& cpyvec) {
        for (int i = 0; i < size; i++) {
            data[i] = cpyvec[i];
        }
    }

    vec& operator=(const vec& cpyvec) {
        if (this == &cpyvec) return *this;

        for (int i = 0; i < size; i++) {
            data[i] = cpyvec[i];
        }
        return *this;
    }

    inline type& operator[](const int index) { return data[index]; };
    inline type operator[](const int index) const { return data[index]; };

    friend std::ostream& operator<<(std::ostream& out, const vec<size, type>& vec) {
        out << "v( ";
        for (int i = 0; i < size; i++) {
            out << vec.data[i] << ", ";
        }
        out << "\b\b )";
        return out;
    }

    inline void normalize() {
        float modulo = std::sqrt((*this) * (*this));
        *this        = (*this) / modulo;
    }
};

template <typename type>
struct vec<4, type> {
    union {
        struct {
            type x {}, y {}, z {}, w {};
        };
        type data[4];
    };

    vec() {};

    vec(type l_x, type l_y, type l_z, type l_w)
        : x { l_x }
        , y { l_y }
        , z { l_z }
        , w { l_w } {};

    vec(const vec& cpyvec) {
        for (int i = 0; i < 4; i++) {
            data[i] = cpyvec[i];
        }
    }

    vec& operator=(const vec& cpyvec) {
        if (this == &cpyvec) return *this;

        for (int i = 0; i < 4; i++) {
            data[i] = cpyvec[i];
        }
        return *this;
    }

    inline type& operator[](const int index) { return data[index]; };
    inline type operator[](const int index) const { return data[index]; };

    friend std::ostream& operator<<(std::ostream& out, const vec<4, type>& vec) {
        out << "v4( ";
        for (int i = 0; i < 4; i++) {
            out << vec.data[i] << ", ";
        }
        out << "\b\b )";
        return out;
    }

    inline void normalize() {
        float modulo = std::sqrt((*this) * (*this));
        *this        = (*this) / modulo;
    }
};

template <typename type>
struct vec<3, type> {
    union {
        struct {
            type x {}, y {}, z {};
        };
        type data[3];
    };

    vec() {};

    vec(type l_x, type l_y, type l_z)
        : x { l_x }
        , y { l_y }
        , z { l_z } {};

    vec(const vec& cpyvec) {
        for (int i = 0; i < 3; i++) {
            data[i] = cpyvec[i];
        }
    }

    vec& operator=(const vec& cpyvec) {
        if (this == &cpyvec) return *this;

        for (int i = 0; i < 3; i++) {
            data[i] = cpyvec[i];
        }
        return *this;
    }

    inline type& operator[](const int index) { return data[index]; };
    inline type operator[](const int index) const { return data[index]; };

    friend std::ostream& operator<<(std::ostream& out, const vec<3, type>& vec) {
        out << "v3( ";
        for (int i = 0; i < 3; i++) {
            out << vec.data[i] << ", ";
        }
        out << "\b\b )";
        return out;
    }

    inline void normalize() {
        float modulo = std::sqrt((*this) * (*this));
        *this        = (*this) / modulo;
    }
};

template <typename type>
struct vec<2, type> {
    union {
        struct {
            type x {}, y {};
        };
        type data[2];
    };

    vec() {};

    vec(type l_x, type l_y)
        : x { l_x }
        , y { l_y } {};

    vec(const vec& cpyvec) {
        for (int i = 0; i < 2; i++) {
            data[i] = cpyvec[i];
        }
    }

    vec& operator=(const vec& cpyvec) {
        if (this == &cpyvec) return *this;

        for (int i = 0; i < 2; i++) {
            data[i] = cpyvec[i];
        }
        return *this;
    }

    inline type& operator[](const int index) { return data[index]; };
    inline type operator[](const int index) const { return data[index]; };

    friend std::ostream& operator<<(std::ostream& out, const vec<2, type>& vec) {
        out << "v2( ";
        for (int i = 0; i < 2; i++) {
            out << vec.data[i] << ", ";
        }
        out << "\b\b )";
        return out;
    }

    inline void normalize() {
        float modulo = std::sqrt((*this) * (*this));
        *this        = (*this) / modulo;
    }
};

//////////////////////////////////////////////////////////////////////////
// OPERACIONES BASICAS CON VECTORES

template <int size, typename type>
inline const vec<size, type> operator+(const vec<size, type>& lhs, const vec<size, type>& rhs) {
    vec<size, type> ret;
    for (int i = 0; i < size; i++) {
        ret[i] = lhs[i] + rhs[i];
    }
    return ret;
}

template <int size, typename type>
inline const vec<size, type> operator-(const vec<size, type>& lhs, const vec<size, type>& rhs) {
    vec<size, type> ret;
    for (int i = 0; i < size; i++) {
        ret[i] = lhs[i] - rhs[i];
    }
    return ret;
}

template <int size, typename type>
inline const vec<size, type> operator*(const vec<size, type>& lhs, const type rhs) {
    vec<size, type> ret;
    for (int i = 0; i < size; i++) {
        ret[i] = lhs[i] * rhs;
    }
    return ret;
}

template <int size, typename type>
inline const vec<size, type> operator/(const vec<size, type>& lhs, const type rhs) {
    vec<size, type> ret;
    for (int i = 0; i < size; i++) {
        ret[i] = lhs[i] / rhs;
    }
    return ret;
}

template <int size, typename type>
inline type operator*(const vec<size, type>& lhs, const vec<size, type>& rhs) {
    type ret = type();
    for (int i = 0; i < size; i++) {
        ret += lhs[i] * rhs[i];
    }
    return ret;
}

template <typename T>
inline const vec<3, T> crossProduct(const vec<3, T>& v1, const vec<3, T>& v2) {
    return vec<3, T> { v1.y * v2.z - v2.y * v1.z, v2.x * v1.z - v1.x * v2.z, v1.x * v2.y - v2.x * v1.y };
}

using vec2i = vec<2, int>;
using vec2f = vec<2, float>;
using vec3i = vec<3, int>;
using vec3f = vec<3, float>;
using vec4i = vec<4, int>;
using vec4f = vec<4, float>;

////////////////////////////////////////////////////////////////////////////
//// CALCULO DE COORDENADAS BARICENTRICAS

inline vec3f toBarycentricCoord(vec3f* verts, vec2f point) {
    vec3f pointv3 = vec3f { point.x, point.y, 0 };

    // Asumiendo r1, r2, r3 los vertices del triangulo, y p el punto
    // Variables que representan vectores matematicos
    vec3f r1_r2 = verts[1] - verts[0];
    vec3f r1_r3 = verts[2] - verts[0];
    vec3f p_r1  = verts[0] - pointv3;

    // vec3f x_values { r1_r2.x, r1_r3.x, p_r1.x };
    // vec3f y_values { r1_r2.y, r1_r3.y, p_r1.y };
    vec3f vecRes = crossProduct(vec3f { r1_r2.x, r1_r3.x, p_r1.x }, vec3f { r1_r2.y, r1_r3.y, p_r1.y });

    if (std::abs(vecRes.z) < 1e-2) return vec3f { -1, 1, 1 };

    vecRes = vecRes / vecRes.z;
    return (vec3f { 1.0f - (vecRes.x + vecRes.y), vecRes.x, vecRes.y });
}

////////////////////////////////////////////////////////////////////////////
//// HOMOGENEOUSR COORDINATES

// Apply perpective division
inline vec3f divW(const vec4f& vec) {
    if (vec.w == 0) {
        std::cout << "WTF" << '\n';
        return vec3f { vec.x, vec.y, vec.z };
    }
    return vec3f {
        vec.x / vec.w, //
        vec.y / vec.w, //
        vec.z / vec.w  //
    };
}

// To homogeneous coordinates
inline vec4f toHmgcoord(const vec3f& vec) {
    return vec4f {
        vec.x, //
        vec.y, //
        vec.z, //
        1.f    //
    };
}

#endif // __VECTOR_H__