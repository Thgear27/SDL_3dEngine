#ifndef __COLOR_H__
#define __COLOR_H__

#include <SDL2/SDL.h>

struct Color {
    union {
        struct {
            unsigned char r, g, b, a;
        };
        unsigned char rawArr[4] {};
        Uint32 raw;
    };

    Color(float l_r, float l_g, float l_b, float l_a) {
        a = static_cast<unsigned char>(l_a * 255.f);
        b = static_cast<unsigned char>(l_b * 255.f);
        g = static_cast<unsigned char>(l_g * 255.f);
        r = static_cast<unsigned char>(l_r * 255.f);
    }

    Color(unsigned char l_r, unsigned char l_g, unsigned char l_b) {
        a = 255;
        b = l_b;
        g = l_g;
        r = l_r;
    }
};

#endif // __COLOR_H__