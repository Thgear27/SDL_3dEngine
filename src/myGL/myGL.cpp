#include "myGL.hpp"

namespace myGL {

void triangle(vec4f* verts, Window* window, float* zbuffer) {
    vec3f v3verts[3] {};
    for (int i = 0; i < 3; i++) {
        v3verts[i] = divW(verts[i]);
    }

    vec2f boxMin = vec2f { (float)window->m_width, (float)window->m_height };
    vec2f boxMax = vec2f { 0, 0 };
    for (int i = 0; i < 3; i++) {
        boxMin.x = std::max(0.0f, std::min(boxMin.x, verts[i].x));
        boxMin.y = std::max(0.0f, std::min(boxMin.y, verts[i].y));

        boxMax.x = std::min((float)window->m_width, std::max(boxMax.x, verts[i].x));
        boxMax.y = std::min((float)window->m_height, std::max(boxMax.y, verts[i].y));
    }

    vec3f light_dir = vec3f { 0, 0, -1 };
    vec3f normal    = crossProduct(v3verts[0] - v3verts[2], v3verts[1] - v3verts[2]);
    light_dir.normalize();
    normal.normalize();
    float intensidad = light_dir * normal;

    for (int x = boxMin.x; x < boxMax.x; x++) {
        for (int y = boxMin.y; y < boxMax.y; y++) {
            vec3f bcoord = toBarycentricCoord(v3verts, vec2f { (float)x, (float)y });
            //    r  g  b  a
            // Color color { bcoord.x, bcoord.y, bcoord.z, 1 };
            Color color { intensidad, intensidad, intensidad, 1 };
            if (bcoord.x < 0.0f || bcoord.y < 0.0f || bcoord.z < 0.0f) continue;
            float currentZ = v3verts[0].z * bcoord.x + v3verts[1].z * bcoord.y + v3verts[2].z * bcoord.z;
            if (currentZ > zbuffer[x + y * window->m_width]) {
                zbuffer[x + y * window->m_width] = currentZ;
                window->drawPixel(x, y, color);
            }
        }
    }
}

void line(vec3f p1, vec3f p2, Window* window) {
    bool inverted_plane = false;
    if (std::abs(p2.y - p1.y) > std::abs(p2.x - p1.x)) { // Triangulo con pendiente mayor a 1
        std::swap(p1.x, p1.y);
        std::swap(p2.x, p2.y);
        inverted_plane = true;
    }

    if (p1.x > p2.x) {
        std::swap(p1, p2);
    }

    // Bresenham's algorithm
    int dx  = p2.x - p1.x;
    int dy  = p2.y - p1.y;
    int dxe = std::abs(dy) - std::abs(dx);
    int y   = p1.y; // punto inicial que ira aumentando
    for (int x = p1.x; x <= p2.x; x++) {
        if (!inverted_plane) window->drawPixel(x, y, Color { 1, 1, 1, 1 });
        else window->drawPixel(y, x, Color { 1, 1, 1, 1 });

        dxe += std::abs(dy);

        if (dxe > 0) {
            dxe -= dx;
            y += (p2.y > p1.y) ? 1 : -1;
        }
    }
}

} // namespace myGL