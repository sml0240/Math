#pragma once
#include <cmath>
#include <type_traits>
#include <typeinfo>
#include <inttypes.h>

template <typename T>
class Vector3
{
    typedef T  Type;
    typedef T* p_Type;
    typedef T& r_Type;

public:
    Vector3() : x(0), y(0), z(0) {}
    Vector3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
    //Vector3(const T &_x, const T &_y, const T &_z) : x(_x), y(_y), z(_z) {}

    Vector3(Vector3 &vec) : x(vec.x), y(vec.y), z(vec.z) {}

    Vector3(Direction dir)
    {
        Vector3<int> vec;
        switch (dir)
        {
        case Direction::BACKWARD:
        {
            z = -1;
            break;
        }
        case Direction::FORWARD:
        {
            z = 1;
            break;
        }
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
    virtual ~Vector3() {}

    /////////////////////////////// OPS /////////////////////////////////////
    virtual Vector3 operator+ (Vector3& other) { return Vector3(this->x + other.x, this->y + other.y, this->z + other.z); }
    virtual Vector3 operator- (Vector3& other) { return Vector3(this->x - other.x, this->y - other.y, this->z - other.z); }

    virtual void operator+= (Vector3& other) { this->x += other.x; this->y += other.y; this->z += other.z; }
    //virtual void operator+= (Vector3 other) { this->x += other.x; this->y += other.y; this->z += other.z; }
    virtual void operator+= (const Vector3& other) { this->x += other.x; this->y += other.y; this->z += other.z; }
    
    virtual void operator-= (Vector3& other) { this->x -= other.x; this->y -= other.y; this->z -= other.z; }
    virtual void operator-= (const Vector3& other) { this->x -= other.x; this->y -= other.y; this->z -= other.z; }
    virtual bool operator== (Vector3& other)
    {
        if (std::is_floating_point_v<Type>)
            return (abs(this->x) - abs(other.x) <0.01f && abs(this->y) - abs(other.y) <0.01f && abs(this->z) - abs(other.z) <0.01f);

        if (std::is_integral_v<Type>)
            return (this->x == other.x && this->y == other.y && this->z == other.z);
    
    }

    virtual bool operator!= (Vector3& other)
    {
        if (std::is_floating_point_v<Type>)
            return (abs(this->x) - abs(other.x) > 0.01f || abs(this->y) - abs(other.y) <0.01f || abs(this->z) - abs(other.z) <0.01f);
        else if (std::is_integral_v<Type>)
            return (this->x != other.x || this->y != other.y && this->z != other.z);
        else
            return (this->x != other.x || this->y != other.y && this->z != other.z);
    }
    
    Vector3 operator* (Vector3& other) { return Vector3(this->x * other.x, this->y * other.y, this->z * other.z); }
    Vector3 operator* (int scalar) { return Vector3(this->x * scalar, this->y * scalar, this->z * scalar); }
    Vector3 operator* (float scalar) { return Vector3(this->x * scalar, this->y * scalar, this->z * scalar); }

    Vector3 operator*= (Vector3& other) { return Vector3(this->x = this->x * other.x, this->y = this->y * other.y, this->y = this->z * other.z); }
    Vector3 operator*= (int scalar) { return Vector3(this->x = this->x * scalar, this->y = this->y * scalar, this->z = this->z * scalar); }
    Vector3 operator*= (float scalar) { return Vector3(this->x = this->x * scalar, this->y = this->y * scalar, this->z = this->z * scalar); }

    /////////////////////////////// FUNCS /////////////////////////////////////
    Vector3 Lerp(Vector3& to, float t)
    {
        Vector3 ret;
        ret.x = this->x + (to.x - this->x) * t;
        ret.y = this->y +(to.y - this->y) * t;
        ret.z = this->z +(to.z - this->z) * t;
        return ret;
    }

    float Dot(Vector3& other)
    {
        return x * other.x + y * other.y + z * other.z;
    }
    float Dot()
    {
        return x * x + y * y + z * z;
    }
    Vector3 Project(Vector3& other)
    {
        return other * (this->Dot(other) / other.Dot());
    }
    // Returns a normalized vector
    Vector3 Normalized()
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
        if (std::is_floating_point_v<T>)
        {
            return sqrtf(pow(x, 2) + pow(y, 2) + pow(z, 2));
        }
        if (std::is_integral_v<T>)
        {
            return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
        }
    }
    // returns a new vector that represents cross product
    Vector3 Cross(Vector3& rVec2)
    {
        Vector3 ret;
        ret.x = this->y * rVec2.z - this->z * rVec2.y;
        ret.y = this->z * rVec2.x - this->x * rVec2.z;
        ret.z = this->x * rVec2.y - this->y * rVec2.x;
    }
    float AngleTo(Vector3& other)
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
        //std::cout << "Vector3( " << this->x << ", " << this->y << ", " << this->z << ")" << std::endl;
    }
    
    static Vector3 ZERO() { return Vector3(0, 0, 0); }
    static Vector3 ONE() { return Vector3(1, 1, 1); }
    static Vector3 UP() { return Vector3(0, 1, 0); }
    static Vector3 DOWN() { return Vector3(0, -1, 0); }
    static Vector3 LEFT() { return Vector3(1, 0, 0); }
    static Vector3 RIGHT() { return Vector3(-1, 0, 0); }
    static Vector3 FORWARD() { return Vector3(0, 0, 1); }
    static Vector3 BACKWARD() { return Vector3(0, 0, -1); }

    // components
    Type x, y, z;
};

// typedef Vector3<float> Vector3f;
// typedef Vector3<int> Vector3i;

/////////////////////////////// VECTOR3I ////////////////////////////////////

class Vector3i : public Vector3<int>
{
public:
    Vector3i() : Vector3(0, 0, 0) {}
    Vector3i(int _z, int _y, int _x) : Vector3(_x, _y, _z) {}
    Vector3i(Vector3i &vec) :Vector3(vec.x, vec.y, vec.z) { }
    Vector3i(const Vector3i &vec) :Vector3(vec.x, vec.y, vec.z) { }
    Vector3i(Vector3<float> &vec) :Vector3(vec.x, vec.y, vec.z) { }
    Vector3i(const Vector3<float> &vec) :Vector3(vec.x, vec.y, vec.z) { }
    Vector3i(float _z, float _y, float _x) : Vector3((int)_x, (int)_y, (int)_z) {}

    ~Vector3i() {}
};

/////////////////////////////// VECTOR3F ////////////////////////////////////

class Vector3f : public Vector3<float>
{
public:
    Vector3f() : Vector3(0.0f, 0.0f, 0.0f) {}
    Vector3f(float _x, float _y, float _z) : Vector3(_x, _y, _z) {}
    
    //Vector3f(const float &_x, const float &_y, const float &_z) : Vector3(_x, _y, _z) {}
    //Vector3f(float &_x, float &_y, float &_z) : Vector3(_x, _y, _z) {}
    
    Vector3f(int _x, int _y, int _z) : Vector3((float)_x, (float)_y, (float)_z) {}
    Vector3f(const int &_x, const int &_y, const int &_z) : Vector3((float)_x, (float)_y, (float)_z) {}

    Vector3f(Vector3<float> &fvec) :Vector3(fvec.x, fvec.y, fvec.z){}
    Vector3f(const Vector3<float> &fvec) :Vector3(fvec.x, fvec.y, fvec.z){}
    Vector3f(Vector3f &fvec) :Vector3(fvec.x, fvec.y, fvec.z){}
    Vector3f(const Vector3<int> &fvec) :Vector3(fvec.x, fvec.y, fvec.z){}
    Vector3f(Vector3<int> &fvec) :Vector3(fvec.x, fvec.y, fvec.z){}

    // void operator+= (Vector3f other) override { this->x += other.x; this->y += other.y; this->z += other.z; }
    // void operator+= (Vector3f &other) override  { this->x += other.x; this->y += other.y; this->z += other.z; }
    // void operator+= (const Vector3f &other) override { this->x += other.x; this->y += other.y; this->z += other.z; }

    ~Vector3f() {}
};
