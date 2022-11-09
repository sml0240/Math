#pragma once

enum class Direction
{
	UP = 0,
	DOWN,
	LEFT,
	RIGHT,
	FORWARD,
	BACKWARD,
};
enum class Axis
{
	X,
	Y,
	Z,
};

#include "vector3.h"
#include "vector2.h"
#include "mat4.h"
#include "random.h"

#define M_RADPI        57.295779513082
#define PI            3.14159265358979323846
#define DEG2RAD(x)    ((float)(x) * (float)((float)(PI) / 180.0f))
#define RAD2DEG(x)    ((float)(x) * (float)(180.0f / (float)(PI)))

float Lerp(float from, float to)
{
	return from + to * (to - from);
}
