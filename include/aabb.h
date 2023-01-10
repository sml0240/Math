#pragma once
#include "../vector3.h"
template<typename T>
class AABB
{
public:
    AABB()
    : position({0, 0}), size({1, 1})
    {}
    AABB(const Vector3<T> &pos, const Vector3<T> &_size)
    : position(pos), size(_size)
    {}
    ~AABB()
    {}
    Vector3<T> &Position() { return position; };
    Vector3<T> &Size() { return size; };
    Vector3<T> Middle() { return position + (size/2); }

private:
    Vector3<T> position, size;
};