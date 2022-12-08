#ifndef __MYGL_H__
#define __MYGL_H__

#include "../Window.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"
#include "Texture.hpp"

namespace myGL {

void triangle(vec4f* verts, Window* window, float* zbuffer, vec2f* uv, Texture& texture);

void line(vec3f p1, vec3f p2, Window* window);

}

#endif // __MYGL_H__