#pragma once
#include "../vector2.h"

template<typename T>
class Rect2
{
public:
    Rect2()
    : position({0, 0}), size({1, 1})
    {}
    Rect2(const Vector2<T> &pos, const Vector2<T> &_size)
    : position(pos), size(_size)
    {}
    ~Rect2()
    {}
    
    Vector2<T> &Position() { return position; };
    Vector2<T> &Size() { return size; };
    Vector2<T> Middle() { return position + (size/2); }

private:
    Vector2<T> position, size;
};

typedef Rect2<float> Rect2f;
typedef Rect2<int> Rect2i;
