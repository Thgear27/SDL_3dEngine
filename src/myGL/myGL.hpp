#ifndef __MYGL_H__
#define __MYGL_H__

#include "../Window.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"

namespace myGL {

void triangle(vec4f* verts, Window* window);

void line(vec3f p1, vec3f p2, Window* window);

}

#endif // __MYGL_H__