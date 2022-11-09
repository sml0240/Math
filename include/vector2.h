#pragma once
#include <cmath>
#include <type_traits>
#include <typeinfo>
#include <inttypes.h>

template <typename T>
class Vector2
{
    typedef T  Type;
    typedef T* p_Type;
    typedef T& r_Type;

public:
    Vector2() : x(0), y(0) {}
    Vector2(const T &_x, const T &_y) : x(_x), y(_y) {}
    Vector2(int _x, int _y) : x(_x), y(_y) {}
    Vector2(const Vector2 &vec) : x(vec.x), y(vec.y) {}

    Vector2(Direction dir)
    {
        switch (dir)
        {
        case Direction::UP:
        {
            y = 1;
            break;
        }
        case Direction::DOWN:
        {
            y = -1;
            break;
        }
        case Direction::LEFT:
        {
            x = 1;
            break;
        }case Direction::RIGHT:
        {
            x = -1;
            break;
        }
        }
    }
    
    /////////////////////////////// DEST ////////////////////////////////////
    virtual ~Vector2() {}

    /////////////////////////////// OPS /////////////////////////////////////
    Vector2 operator+ (const Vector2& other) const { return Vector2(this->x + other.x, this->y + other.y); }
    Vector2 operator- (const Vector2& other) const { return Vector2(this->x - other.x, this->y - other.y); }

    //virtual void operator+= (Vector2& other) { this->x += other.x; this->y += other.y; this->z += other.z; }
    //virtual void operator+= (Vector2 other) { this->x += other.x; this->y += other.y; this->z += other.z; }
    void operator+= (const Vector2& other) { this->x += other.x; this->y += other.y; }
    
    //virtual void operator-= (Vector2& other) { this->x -= other.x; this->y -= other.y; this->z -= other.z; }
    void operator-= (const Vector2& other) { this->x -= other.x; this->y -= other.y; }
    virtual bool operator== (const Vector2& other) const
    {
        if (std::is_floating_point_v<Type>)
            return (abs(this->x) - abs(other.x) <0.01f && abs(this->y) - abs(other.y) <0.01f <0.01f);

        if (std::is_integral_v<Type>)
            return (this->x == other.x && this->y == other.y);
    }

    bool operator!= (const Vector2& other)
    {
        if (std::is_floating_point_v<Type>)
            return (abs(this->x) - abs(other.x) > 0.01f || abs(this->y) - abs(other.y) <0.01f <0.01f);
        else if (std::is_integral_v<Type>)
            return (this->x != other.x || this->y != other.y);
        else
            return (this->x != other.x || this->y != other.y);
    }
    
    Vector2 operator* (const Vector2& other) { return Vector2(this->x * other.x, this->y * other.y); }
    Vector2 operator* (int scalar) { return Vector2(this->x * scalar, this->y * scalar); }
    Vector2 operator* (float scalar) { return Vector2(this->x * scalar, this->y * scalar); }

    Vector2 operator*= (const Vector2& other) { return Vector2(this->x = this->x * other.x, this->y = this->y * other.y); }
    Vector2 operator*= (int scalar) { return Vector2(this->x = this->x * scalar, this->y = this->y * scalar); }
    Vector2 operator*= (float scalar) { return Vector2(this->x = this->x * scalar, this->y = this->y * scalar); }

    /////////////////////////////// FUNCS /////////////////////////////////////
    Vector2 Lerp(Vector2& to, float t)
    {
        Vector2 ret;
        ret.x = this->x + (to.x - this->x) * t;
        ret.y = this->y +(to.y - this->y) * t;
        return ret;
    }

    float Dot(Vector2& other)
    {
        return x * other.x + y * other.y;
    }
    float Dot()
    {
        return x * x + y * y;
    }
    Vector2 Project(Vector2& other)
    {
        return other * (this->Dot(other) / other.Dot());
    }
    // Returns a normalized vector
    Vector2 Normalized()
    {
        return *this * (1.0f / this->Length());
    }
    // Normalizes this vector in place
    void Normalize()
    {
        *this = *this * (1.0f / this->Length());
    }
    // returns length
    Type Length()
    {
        if (std::is_floating_point_v<Type>)
        {
            return sqrtf(pow(x, 2) + pow(y, 2));
        }
        if (std::is_integral_v<Type>)
        {
            return sqrt(pow(x, 2) + pow(y, 2));
        }
    }

    float AngleTo(Vector2& other)
    {
        return acos(this->Dot(other) / (this->Length() * other.Length()));
    }
    ////////////// type checking //////////////
    bool IsFloat()
    {
        return std::is_floating_point_v<Type>;
    }
    bool IsInt()
    {
        return std::is_integral_v<Type>;
    }
    template <typename Other>
    bool IsType()
    {
        return typeid(T) == typeid(Other);
    }

    void PrintSelf()
    {
        //std::cout << "Vector2( " << this->x << ", " << this->y << ", " << this->z << ")" << std::endl;
    }
    
    static Vector2 ZERO() { return Vector2(0, 0); }
    static Vector2 ONE() { return Vector2(1, 1); }
    // Right hand Directions
    static Vector2 UP() { return Vector2(0, 1); }
    static Vector2 DOWN() { return Vector2(0, -1); }
    static Vector2 LEFT() { return Vector2(1, 0); }
    static Vector2 RIGHT() { return Vector2(-1, 0); }

    // components
    Type x, y;
};

typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;
