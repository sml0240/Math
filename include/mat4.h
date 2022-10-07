#pragma once
//#include "vector3.h"
#include <assert.h>
#include <inttypes.h>
#include "vector3.h"

// class Vector3f;
// class Vector3i;

class Vector4
{
public:
	Vector4()
		: x(0.0f), y(0.0f), z(0.0f), w(1.0f)
	{}
	Vector4(float _x, float _y, float _z, float _w)
		: x(_x), y(_y), z(_z), w(_w)
	{}
	Vector4(Vector3f &vec)
		: x(vec.x), y(vec.y), z(vec.z), w(1.0f)
	{}
	~Vector4() {}

	Vector4 operator* (Vector4 &other)
	{
		return Vector4(this->x * other.x, this->y * other.y, this->z * other.z, this->w * other.w);
	}

	float Dot(Vector4& other)
	{
		return x * other.x + y * other.y + z * other.z + w * other.w;
	}

	float x, y, z, w;
};

// vector * matrix
// not matrix * vector

class Mat4
{
public:
	Mat4()
	{
		Identity();
	}
	~Mat4(){}

	void PrintSelf()
	{
		for (int row = 0; row < 4; row++)
		{
			//std::cout << std::endl;
			/*for (int col = 0; col < 4; col++)
			{
				std::cout << " | " << mat[row][col];
			}*/
		}
		/*std::cout << std::endl;
		std::cout << std::endl;*/
	}

	struct Row
	{
		Row(Mat4* _mat, int row) : mat(_mat), mrow(row) {}
		int mrow;
		Mat4* mat;
		float& operator[](int col) { return mat->mat[mrow][col]; }
		int operator-> () { return this->mrow; }
	};

	void operator+= (Mat4 &other)
	{
		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				this->mat[row][col] = this->mat[row][col] + other.mat[row][col];
			}
		}
	}
	
	Vector3f operator* (const Vector3f& other)
	{	
		Vector3f ret;
		ret.x = (this->mat[0][0] * other.x) + (this->mat[0][1] * other.y) + (this->mat[0][2] * other.z);
		ret.y = (this->mat[1][0] * other.x) + (this->mat[1][1] * other.y) + (this->mat[1][2] * other.z);
		ret.z = (this->mat[2][0] * other.x) + (this->mat[2][1] * other.y) + (this->mat[2][2] * other.z);
		return ret;
	}

	Vector3i operator* (const Vector3i& other)
	{
		Vector3i ret;
		ret.x = (this->mat[0][0] * other.x) + (this->mat[0][1] * other.y) + (this->mat[0][2] * other.z);
		ret.y = (this->mat[1][0] * other.x) + (this->mat[1][1] * other.y) + (this->mat[1][2] * other.z);
		ret.z = (this->mat[2][0] * other.x) + (this->mat[2][1] * other.y) + (this->mat[2][2] * other.z);

		return ret;
	}
	Vector4 operator* (const Vector4& other)
	{
		Vector4 ret;
		ret.x = (this->mat[0][0] * other.x) + (this->mat[0][1] * other.y) + (this->mat[0][2] * other.z);
		ret.y = (this->mat[1][0] * other.x) + (this->mat[1][1] * other.y) + (this->mat[1][2] * other.z);
		ret.z = (this->mat[2][0] * other.x) + (this->mat[2][1] * other.y) + (this->mat[2][2] * other.z);
		ret.w = (this->mat[3][0] * other.x) + (this->mat[3][1] * other.y) + (this->mat[3][2] * other.z);

		return ret;
	}

	Mat4 operator* (const Mat4 &other)
	{
		Mat4 ret;

		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				ret[row][col] =
					(other.mat[row][0] * this->mat[0][col]) +
					(other.mat[row][1] * this->mat[1][col]) +
					(other.mat[row][2] * this->mat[2][col]) +
					(other.mat[row][3] * this->mat[3][col]);
			}
		}
		return ret;
	}
	
	void operator*= (const Mat4& other)
	{
		Mat4 im;

		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				im[row][col] =
					(other.mat[row][0] * this->mat[0][col]) +
					(other.mat[row][1] * this->mat[1][col]) +
					(other.mat[row][2] * this->mat[2][col]) +
					(other.mat[row][3] * this->mat[3][col]);
			}
		}
		*this = im;
	}
	static Mat4 Mult (const Mat4& m1, const Mat4& m2)
	{
		Mat4 result;
		// only pre
		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				result[row][col] =
					(m2.mat[row][0] * m1.mat[0][col]) +
					(m2.mat[row][1] * m1.mat[1][col]) +
					(m2.mat[row][2] * m1.mat[2][col]) +
					(m2.mat[row][3] * m1.mat[3][col]);
			}
		}
		return result;
	}
	
	Vector3f Xform(Vector3f& vec)
	{
		Vector3f ret;
		ret.x = ((this->mat[0][0] * vec.x) + (this->mat[1][0] * vec.y) + (this->mat[2][0] * vec.z) + this->mat[3][0]);
		ret.y = ((this->mat[0][1] * vec.x) + (this->mat[1][1] * vec.y) + (this->mat[2][1] * vec.z) + this->mat[3][1]);
		ret.z = ((this->mat[0][2] * vec.x) + (this->mat[1][2] * vec.y) + (this->mat[2][2] * vec.z) + this->mat[3][2]);
		return ret;
	}

	Vector3f XformInv(Vector3f& vec)
	{
		Vector3f ret;
		ret.x = (this->mat[0][0] * vec.x) + (this->mat[1][0] * vec.y) + (this->mat[2][0] * vec.z);
		ret.y = (this->mat[0][1] * vec.x) + (this->mat[1][1] * vec.y) + (this->mat[2][1] * vec.z);
		ret.z = (this->mat[0][2] * vec.x) + (this->mat[1][2] * vec.y) + (this->mat[2][2] * vec.z);
		ret -= this->GetTranslation();
		return ret;
	}
	Vector4 Xform(Vector4& vec)
	{
		Vector4 ret;
		ret.x = ((this->mat[0][0] * vec.x) + (this->mat[1][0] * vec.y) + (this->mat[2][0] * vec.z) + this->mat[3][0]);
		ret.y = ((this->mat[0][1] * vec.x) + (this->mat[1][1] * vec.y) + (this->mat[2][1] * vec.z) + this->mat[3][1]);
		ret.z = ((this->mat[0][2] * vec.x) + (this->mat[1][2] * vec.y) + (this->mat[2][2] * vec.z) + this->mat[3][2]);
		ret.w = ((this->mat[0][2] * vec.x) + (this->mat[1][2] * vec.y) + (this->mat[2][2] * vec.z) + this->mat[3][3]);
		return ret;
	}
	Row operator[] (const int idx)
	{
		return Row(this, idx);
	}

	void Rotate(Axis axis, float angle)
	{
		switch (axis)
		{
			case Axis::X:
				RotateX(angle);
				break;
			case Axis::Y:
				RotateY(angle);
				break;
			case Axis::Z:
				RotateZ(angle);
				break;
		}
	}
	void RotateX(float radians)
	{
		Mat4 rot = CreateRotatedX(radians);
		*this *= rot;
	}
	void RotateY(float radians)
	{
		Mat4 rot = CreateRotatedY(radians);
		*this *= rot;
	}
	void RotateZ(float radians)
	{
		Mat4 rot = CreateRotatedZ(radians);
		*this *= rot;
	}

	Mat4 Scaled(const Vector3f& scale)
	{
		Mat4 ret;

		ret[0][0] = scale.x;
		ret[1][1] = scale.y;
		ret[2][2] = scale.z;
		ret[3][3] = 1.0f;
	}
	
	void Scale(float scale) {
		Mat4 scaled = CreateScaled(scale);
		(*this) *= scaled;
	}

	void SetDiagonal()
	{
		this->mat[0][0] = 1.0f;
		this->mat[1][1] = 1.0f;
		this->mat[2][2] = 1.0f;
		this->mat[3][3] = 1.0f;
	}
	void Identity()
	{
		mat[0][0] = 1.0f;
		mat[1][1] = 1.0f;
		mat[2][2] = 1.0f;
		mat[3][3] = 1.0f;
	}
	void Translate(const Vector3f& translation)
	{
		SetTranslation(translation);
	}
	Vector3f GetTranslation()
	{
		return Vector3f(this->mat[3][0], this->mat[3][1], this->mat[3][2]);
	}
	Vector3f GetRow(uint8_t row)
	{
		return Vector3f(this->mat[row][0], this->mat[row][1], this->mat[row][2]);
	}
	Vector3f GetCol(uint8_t col)
	{
		return Vector3f(this->mat[0][col], this->mat[1][col], this->mat[2][col]);
	}
	Vector4 GetRow4(uint8_t row)
	{
		return Vector4(this->mat[row][0], this->mat[row][1], this->mat[row][2] , this->mat[row][3]);
	}
	Vector4 GetCol4(uint8_t col)
	{
		return Vector4(this->mat[0][col], this->mat[1][col], this->mat[2][col], this->mat[3][col]);
	}

	void SetRow(uint8_t row, Vector3f& to)
	{
		this->mat[row][0] = to.x;
		this->mat[row][1] = to.y;
		this->mat[row][2] = to.z;
	}
	void SetCol(uint8_t col, Vector3f& to)
	{
		this->mat[0][col] = to.x;
		this->mat[1][col] = to.y;
		this->mat[2][col] = to.z;
	}
	void SetRow4(uint8_t row, Vector4& to)
	{
		this->mat[row][0] = to.x;
		this->mat[row][1] = to.y;
		this->mat[row][2] = to.z;
		this->mat[row][3] = to.w;
	}
	void SetCol4(uint8_t col, Vector4& to)
	{
		this->mat[0][col] = to.x;
		this->mat[1][col] = to.y;
		this->mat[2][col] = to.z;
		this->mat[3][col] = to.w;
	}
	// sets the fourth vector to pos
	void SetTranslation(const Vector3f& pos)
	{
		mat[3][0] = pos.x;
		mat[3][1] = pos.y;
		mat[3][2] = pos.z;
	}
	// returns a rotationMatrix with values set on x
	static Mat4 CreateRotatedX(float radians)
	{
		Mat4 rot;
		rot.mat[1][1] = cos(radians);
		rot.mat[1][2] = -sin(radians);
		rot.mat[2][1] = sin(radians);
		rot.mat[2][2] = cos(radians);
		return rot;
	}
	// returns a rotationMatrix with values set on y
	static Mat4 CreateRotatedY(float radians)
	{
		Mat4 rot;
		rot.mat[0][0] = cos(radians);
		rot.mat[0][2] = sin(radians);
		rot.mat[2][0] = -sin(radians);
		rot.mat[2][2] = cos(radians);
		return rot;
	}
	// returns a rotationMatrix with values set on z
	static Mat4 CreateRotatedZ(float radians)
	{
		Mat4 rot;
		rot.mat[0][0] = cos(radians);
		rot.mat[0][1] = -sin(radians);
		rot.mat[1][0] = sin(radians);
		rot.mat[1][1] = cos(radians);
		return rot;
	}
	static Mat4 CreateScaled(float scale)
	{
		Mat4 scaled;
		scaled.mat[0][0] = scale;
		scaled.mat[1][1] = scale;
		scaled.mat[2][2] = scale;
		scaled.mat[3][3] = 1.0f;
		return scaled;
	}
	// transposes this mat in place
	void Transpose()
	{
		Mat4 result;
		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				this->mat[row][col] = this->mat[col][row];
			}
		}
	}
	// returns a new transposed mat
	Mat4 Transposed() const
	{
		Mat4 result;
		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				result.mat[row][col] = this->mat[col][row];
			}
		}
		return result;
	}
	
	void To1DArray(float* arr)
	{
		for (size_t row = 0; row < 4; row++)
		{
			for (size_t col = 0; col < 4; col++)
			{
				size_t idx = (row * 4) + col;

				arr[idx] = mat[row][col];
			}
		}
	}
	// prop
	float mat[4][4] = {0.0f};
};