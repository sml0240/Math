#pragma once
#include <cmath>
#include <type_traits>

//#include "includes/mat4.h"

//class Mat4;

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

    template <typename T>
    class Vector3
    {
        typedef T  Type;
        typedef T* p_Type;
        typedef T& r_Type;

    public:
        Vector3() : x(0), y(0), z(0) {}
        Vector3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
        Vector3(Vector3 &vec) : x(vec.x), y(vec.y), z(vec.z) {}
        virtual ~Vector3() {}

        /////////////////////////////// OPS /////////////////////////////////////
        virtual Vector3 operator+ (Vector3& other) { return Vector3(this->x + other.x, this->y + other.y, this->z + other.z); }
        virtual Vector3 operator- (Vector3& other) { return Vector3(this->x - other.x, this->y - other.y, this->z - other.z); }

    	virtual void operator+= (Vector3& other) { this->x += other.x; this->y += other.y; this->z += other.z; }
        virtual void operator-= (Vector3& other) { this->x -= other.x; this->y -= other.y; this->z -= other.z; }

        Vector3 operator* (Vector3& other) { return Vector3(this->x * other.x, this->y * other.y, this->z * other.z); }
        Vector3 operator* (int mag) { return Vector3(this->x * mag, this->y * mag, this->z * mag); }
        Vector3 operator* (float mag) { return Vector3(this->x * mag, this->y * mag, this->z * mag); }

        Vector3 operator*= (Vector3& other) { return Vector3(this->x = this->x * other.x, this->y = this->y * other.y, this->y = this->z * other.z); }
        Vector3 operator*= (int mag) { return Vector3(this->x = this->x * mag, this->y = this->y * mag, this->z = this->z * mag); }
        Vector3 operator*= (float mag) { return Vector3(this->x = this->x * mag, this->y = this->y * mag, this->z = this->z * mag); }

        /////////////////////////////// FUNCS /////////////////////////////////////
        Vector3<Type> Lerp(Vector3& to, float t)
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
            ret.x = this->y * rVec2.z - this->z - rVec2.y;
            ret.y = this->z * rVec2.x - this->x - rVec2.z;
            ret.z = this->x * rVec2.y - this->y - rVec2.x;
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

        static Vector3<int> DirToVec(Direction dir)
        {
            Vector3<int> vec;
            switch (dir)
            {
            case Direction::BACKWARD:
            {
                vec.z = -1;
                break;
            }
            case Direction::FORWARD:
            {
                vec.z = 1;
                break;
            }
            case Direction::UP:
            {
                vec.y = 1;
                break;
            }
            case Direction::DOWN:
            {
                vec.y = -1;
                break;
            }
            case Direction::LEFT:
            {
                vec.x = 1;
                break;
            }case Direction::RIGHT:
            {
                vec.x = -1;
                break;
            }
            }
            return vec;
        }

        // components
        Type x, y, z;
    };

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
        Vector3f(int _x, int _y, int _z) : Vector3((float)_x, (float)_y, (float)_z) {}

        Vector3f(Vector3<float> &fvec) :Vector3(fvec.x, fvec.y, fvec.z){}
        Vector3f(const Vector3<float> &fvec) :Vector3(fvec.x, fvec.y, fvec.z){}
        Vector3f(Vector3f &fvec) :Vector3(fvec.x, fvec.y, fvec.z){}
        Vector3f(const Vector3<int> &fvec) :Vector3(fvec.x, fvec.y, fvec.z){}
        Vector3f(Vector3<int> &fvec) :Vector3(fvec.x, fvec.y, fvec.z){}
        ~Vector3f() {}
    };