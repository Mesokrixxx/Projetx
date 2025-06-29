#pragma once

#include <cglm/struct/vec2.h>
#include <cglm/struct/vec3.h>
#include <cglm/struct/vec4.h>

typedef vec2s Vec2;
typedef ivec2s IVec2;
typedef vec3s Vec3;
typedef ivec3s IVec3;
typedef vec4s Vec4;
typedef ivec4s IVec4;

#define ivec2_add glms_ivec2_add

#define vec3_scale glms_vec3_scale
#define vec3_cross glms_vec3_cross
#define vec3_normalize glms_vec3_normalize
#define vec3_add glms_vec3_add
#define vec3_div glms_vec3_div
#define vec3_sub glms_vec3_sub

static inline Vec2 vec2_of(float x, float y) {
	return ((Vec2){{ x, y }});
}

static inline Vec2 vec2_from_ivec2(IVec2 v) {
	return ((Vec2){{ (float)v.x, (float)v.y }});
}

static inline IVec2 ivec2_of(int x, int y) {
	return ((IVec2){{ x, y }});
}

static inline IVec2 ivec2_add(IVec2 v1, IVec2 v2) {
	return ((IVec2){{ v1.x + v2.x, v1.y + v2.y }});
}

static inline Vec3 vec3_of(float x, float y, float z) {
	return ((Vec3){{ x, y, z }});
}

static inline Vec3 vec3_from_ivec3(IVec3 v) {
	return ((Vec3){{ (float)v.x, (float)v.y, (float)v.z }});
}

static inline IVec3 ivec3_of(int x, int y, int z) {
	return ((IVec3){{ x, y, z }});
}
