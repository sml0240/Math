#pragma once

#include <cmath>
#include <type_traits>
#include <typeinfo>
#include <inttypes.h>
#include <string>

template <typename T>
class Vector4
{
    typedef T  Type;
    typedef T* p_Type;
    typedef T& r_Type;

public:

    // components
    Type x, y, z, w;

     ///////////////////////////// CONSTR ////////////////////////////////////

    Vector4() : x(0), y(0), z(0), w(0) {}
    Vector4(const T &_x, const T &_y, const T &_z, const T&_w) : x(_x), y(_y), z(_z), w(_w) {}
    
    //Vector4(const r_Type _x, const r_Type _y, const r_Type _z, const r_Type _w) : x(_x), y(_y), z(_z), w(_w) {}
    Vector4(p_Type _x, p_Type _y, p_Type _z, p_Type _w) : x(_x), y(_y), z(_z), w(_w) {}
    Vector4(const Vector4 &vec) : x(vec.x), y(vec.y), z(vec.z), w(vec.w) {}
    static uint8_t GetPropertyCount(){return 4; }

    // T Into()
    // {
    //     //T arr[] = {x, y, z, w};
    //     return [x, y, z ,w];
    // }

    // Vector4(Direction dir)
    // {
    //     switch (dir)
    //     {
    //     case Direction::BACKWARD:
    //     {
    //         z = -1;
    //         break;
    //     }
    //     case Direction::FORWARD:
    //     {
    //         z = 1;
    //         break;
    //     }
    //     case Direction::UP:
    //     {
    //         y = 1;
    //         break;
    //     }
    //     case Direction::DOWN:
    //     {
    //         y = -1;
    //         break;
    //     }
    //     case Direction::LEFT:
    //     {
    //         x = 1;
    //         break;
    //     }case Direction::RIGHT:
    //     {
    //         x = -1;
    //         break;
    //     }
    //     }
    // }
    
    /////////////////////////////// DEST ////////////////////////////////////
    ~Vector4() {}

    /////////////////////////////// OPS /////////////////////////////////////
    Vector4 operator+ (const Vector4& other) const { return Vector4(this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w); }
    Vector4 operator- (const Vector4& other) const { return Vector4(this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w); }
    r_Type operator[] (int idx)
    {
        int count = GetPropertyCount();
        
        switch (idx)
        {
            case 0:
                return x;
                break;
            case 1:
                return y;
                break;
            case 2:
                return z;
                break;
            case 3:
                return w;
                break;
        }
    }
    //virtual void operator+= (Vector4& other) { this->x += other.x; this->y += other.y; this->z += other.z; }
    //virtual void operator+= (Vector4 other) { this->x += other.x; this->y += other.y; this->z += other.z; }
    void operator+= (const Vector4& other) { this->x += other.x; this->y += other.y; this->z += other.z; this->w += other.w; }
    
    //virtual void operator-= (Vector4& other) { this->x -= other.x; this->y -= other.y; this->z -= other.z; }
    void operator-= (const Vector4& other) { this->x -= other.x; this->y -= other.y; this->z -= other.z; this->w -= other.w; }
    

    // r_Type operator x(){return x; }

    virtual bool operator== (const Vector4& other) const
    {
        if (std::is_floating_point_v<Type>)
            return (abs(this->x) - abs(other.x) <0.01f && abs(this->y) - abs(other.y) <0.01f && abs(this->z) - abs(other.z) <0.01f && abs(this->w) - abs(other.w) <0.01f);

        if (std::is_integral_v<Type>)
            return (this->x == other.x && this->y == other.y && this->z == other.z && this->w == other.w);
    }

    bool operator!= (const Vector4& other)
    {
        if (std::is_floating_point_v<Type>)
            return (abs(this->x) - abs(other.x) > 0.01f || abs(this->y) - abs(other.y) <0.01f || abs(this->z) - abs(other.z) <0.01f || abs(this->z) - abs(other.z) <0.01f);
        else if (std::is_integral_v<Type>)
            return (this->x != other.x || this->y != other.y || this->z != other.z || this->w != other.w);
        else
            return (this->x != other.x || this->y != other.y || this->z != other.z || this->w != other.w);
    }
    
    Vector4 operator* (const Vector4& other) { return Vector4(this->x * other.x, this->y * other.y, this->z * other.z, this->w * other.w); }
    Vector4 operator* (int scalar) { return Vector4(this->x * scalar, this->y * scalar, this->z * scalar, this->w * scalar); }
    Vector4 operator* (float scalar) { return Vector4(this->x * scalar, this->y * scalar, this->z * scalar, this->w * scalar); }

    Vector4 operator*= (const Vector4& other) { return Vector4(this->x = this->x * other.x, this->y = this->y * other.y, this->y = this->z * other.z); }
    Vector4 operator*= (int scalar) { return Vector4(this->x = this->x * scalar, this->y = this->y * scalar, this->z = this->z * scalar); }
    Vector4 operator*= (float scalar) { return Vector4(this->x = this->x * scalar, this->y = this->y * scalar, this->z = this->z * scalar); }

    /////////////////////////////// FUNCS /////////////////////////////////////
    Vector4 Lerp(Vector4& to, float t)
    {
        Vector4 ret;
        ret.x = this->x + (to.x - this->x) * t;
        ret.y = this->y +(to.y - this->y) * t;
        ret.z = this->z +(to.z - this->z) * t;
        ret.w = this->w +(to.w - this->w) * t;
        return ret;
    }

    float Dot(Vector4& other)
    {
        return this->x * other.x + this->y * other.y + this->z * other.z + this->w * other->w;
    }
    float Dot()
    {
        return x * x + y * y + z * z + w * w;
    }
    Vector4 Project(Vector4& other)
    {
        return other * (this->Dot(other) / other.Dot());
    }
    // Returns a normalized vector
    Vector4 Normalized()
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
            return sqrtf(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2));
        }
        if (std::is_integral_v<T>)
        {
            return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2));
        }
    }
    // BLARGHHHHH
    // returns a new vector that represents cross product
    Vector4 Cross(Vector4& rVec2)
    {
        Vector4 ret;
        ret.x = this->y * rVec2.z - this->z * rVec2.y;
        ret.y = this->z * rVec2.x - this->x * rVec2.z;
        ret.z = this->x * rVec2.y - this->y * rVec2.x;
    }
    float AngleTo(Vector4& other)
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

    std::string ToString() { return std::string("Vector4(%f, %f, %f %f)", x, y, z, w); }
    static Vector4 ZERO() { return Vector4(0, 0, 0, 0); }
    static Vector4 ONE() { return Vector4(1, 1, 1, 1); }
    // Right hand Directions
    static Vector4 UP() { return Vector4(0, 1, 0, 0); }
    static Vector4 DOWN() { return Vector4(0, -1, 0, 0); }
    static Vector4 LEFT() { return Vector4(1, 0, 0, 0); }
    static Vector4 RIGHT() { return Vector4(-1, 0, 0, 0); }
    static Vector4 FORWARD() { return Vector4(0, 0, 1, 0); }
    static Vector4 BACKWARD() { return Vector4(0, 0, -1, 0); }

};

// defines for ease of use
typedef Vector4<float> Vector4f;
typedef Vector4<int> Vector4i;

/////////////////////////////// Vector4I ////////////////////////////////////

// class Vector4i : public Vector4<int>
// {
// public:
//     Vector4i() : Vector4(0, 0, 0) {}
//     Vector4i(int _z, int _y, int _x) : Vector4(_x, _y, _z) {}
//     Vector4i(Vector4i &vec) :Vector4(vec.x, vec.y, vec.z) { }
//     Vector4i(const Vector4i &vec) :Vector4(vec.x, vec.y, vec.z) { }
//     Vector4i(Vector4<float> &vec) :Vector4(vec.x, vec.y, vec.z) { }
//     Vector4i(const Vector4<float> &vec) :Vector4(vec.x, vec.y, vec.z) { }
//     Vector4i(float _z, float _y, float _x) : Vector4((int)_x, (int)_y, (int)_z) {}

//     ~Vector4i() {}
// };

// /////////////////////////////// Vector4F ////////////////////////////////////

// class Vector4f : public Vector4<float>
// {
// public:
//     Vector4f() : Vector4(0.0f, 0.0f, 0.0f) {}
//     Vector4f(float _x, float _y, float _z) : Vector4(_x, _y, _z) {}
    
//     //Vector4f(const float &_x, const float &_y, const float &_z) : Vector4(_x, _y, _z) {}
//     //Vector4f(float &_x, float &_y, float &_z) : Vector4(_x, _y, _z) {}
    
//     Vector4f(int _x, int _y, int _z) : Vector4((float)_x, (float)_y, (float)_z) {}
//     Vector4f(const int &_x, const int &_y, const int &_z) : Vector4((float)_x, (float)_y, (float)_z) {}

//     Vector4f(Vector4<float> &fvec) :Vector4(fvec.x, fvec.y, fvec.z){}
//     Vector4f(const Vector4<float> &fvec) :Vector4(fvec.x, fvec.y, fvec.z){}
//     Vector4f(Vector4f &fvec) :Vector4(fvec.x, fvec.y, fvec.z){}
//     Vector4f(const Vector4<int> &fvec) :Vector4(fvec.x, fvec.y, fvec.z){}
//     Vector4f(Vector4<int> &fvec) :Vector4(fvec.x, fvec.y, fvec.z){}

//     // void operator+= (Vector4f other) override { this->x += other.x; this->y += other.y; this->z += other.z; }
//     // void operator+= (Vector4f &other) override  { this->x += other.x; this->y += other.y; this->z += other.z; }
//     // void operator+= (const Vector4f &other) override { this->x += other.x; this->y += other.y; this->z += other.z; }

//     ~Vector4f() {}
// };
