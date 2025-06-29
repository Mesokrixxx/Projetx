#pragma once

#include <cglm/struct/vec2.h>
#include <cglm/types-struct.h>

typedef vec2s Vec2;
typedef ivec2s IVec2;

static inline Vec2 vec2_of(float x, float y) {
	return ((Vec2){{ x, y }});
}

static inline IVec2 ivec2_of(int x, int y) {
	return ((IVec2){{ x, y }});
}
