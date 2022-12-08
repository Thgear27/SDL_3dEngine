#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "Color.hpp"
#include "Vector.hpp"
#include "stb_image.hpp"
#include <string>

struct Texture {
    unsigned char* data = nullptr;
    int m_width;
    int m_height;
    int nrChanels;

    Texture(const std::string& filename) {
        stbi_set_flip_vertically_on_load(true);
        data = stbi_load(filename.c_str(), &m_width, &m_height, &nrChanels, 0);
        std::cout << "Imagen cargada: \n";
        std::cout << "Width: " << m_width << '\n';
        std::cout << "Height: " << m_height << '\n';
        std::cout << "nrChanels: " << nrChanels << '\n';
    }

    ~Texture() { stbi_image_free(data); }

    Color getColor(vec2f* uv, vec3f& bcoord) {
        vec2f point = uv[0] * bcoord.x + uv[1] * bcoord.y + uv[2] * bcoord.z;
        int x       = m_width * point.x;
        int y       = m_height * point.y;
        // float r, g, b;

        // r = data[(x * nrChanels) + (y * m_width * nrChanels) + 0] / 255.0f;
        // g = data[(x * nrChanels) + (y * m_width * nrChanels) + 1] / 255.0f;
        // b = data[(x * nrChanels) + (y * m_width * nrChanels) + 2] / 255.0f;
        return Color { data[(x * nrChanels) + (y * m_width * nrChanels) + 0], //
                       data[(x * nrChanels) + (y * m_width * nrChanels) + 1], //
                       data[(x * nrChanels) + (y * m_width * nrChanels) + 2] };
    }
};

#endif // __TEXTURE_H__