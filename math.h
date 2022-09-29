#pragma once

#define M_RADPI        57.295779513082
#define PI            3.14159265358979323846
#define DEG2RAD(x)    ((float)(x) * (float)((float)(PI) / 180.0f))
#define RAD2DEG(x)    ((float)(x) * (float)(180.0f / (float)(PI)))

float Lerp(float from, float to)
{
	return from + to * (to - from);
}
