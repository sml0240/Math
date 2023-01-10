#pragma once

#include <typeinfo>

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

#include "vector2.h"
#include "vector3.h"
#include "vector4.h"
#include "mat4.h"
#include "random.h"

// template <typename T>
// struct MidVec
// {
// 	uint8_t property_count;
// 	T* properties;
// };

// namespace Vector
// {
// 	template<typename FromType, typename ToType>
// 	ToType To(const FromType &from)
// 	{
// 		if (from > FromType::)
// 	// 	switch (typeid(ToType).hash_code())
// 	// 	{
// 	// 		case typeid(FromType).hash_code():
// 	// 		{
				
// 	// 		}
// 	// 	}
// 	}
// }

#define M_RADPI        57.295779513082
#define PI            3.14159265358979323846
#define DEG2RAD(x)    ((float)(x) * (float)((float)(PI) / 180.0f))
#define RAD2DEG(x)    ((float)(x) * (float)(180.0f / (float)(PI)))

float Lerp(float from, float to)
{
	return from + to * (to - from);
}
