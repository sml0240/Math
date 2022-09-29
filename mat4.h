#pragma once
//#include "vector3.h"
#include <assert.h>
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

	//Vector3 operator* (Vector3& other) { return Vector3(this->x * other.x, this->y * other.y, this->z * other.z); }
	/*float Dot()
	{
		return x * x + y * y + z * z + w * w;
	}

	float Dot(Vector3f& other)
	{
		return x * other.x + y * other.y + z * other.z + w * w;
	}*/
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

	Vector3f operator* (Vector3f& vec)
	{
		Vector4 other(vec)
		;
		Vector3f ret;
		ret.x = (this->mat[0][0] * other.x) + (this->mat[0][1] * other.y) + (this->mat[0][2] * other.z) +(this->mat[0][3] * other.w);
		ret.y = (this->mat[1][0] * other.x) + (this->mat[1][1] * other.y) + (this->mat[1][2] * other.z) + (this->mat[1][3] * other.w);
		ret.z = (this->mat[2][0] * other.x) + (this->mat[2][1] * other.y) + (this->mat[2][2] * other.z) + (this->mat[2][3] * other.w);
		//ret.w = (this->mat[3][0] * other.x) + (this->mat[3][1] * other.y) + (this->mat[3][2] * other.z) + (this->mat[3][3] * other.w);

		return ret;
	}
	Vector3i operator* (Vector3i& other)
	{
		//other.PrintSelf();
		//this->PrintSelf();

		Vector3f ret;
		ret.x = (this->mat[0][0] * other.x) + (this->mat[0][1] * other.y) + (this->mat[0][2] * other.z);
		ret.y = (this->mat[1][0] * other.x) + (this->mat[1][1] * other.y) + (this->mat[1][2] * other.z);
		ret.z = (this->mat[2][0] * other.x) + (this->mat[2][1] * other.y) + (this->mat[2][2] * other.z);

		return ret;
	}
	Vector4 operator* (Vector4& other)
	{
		Vector4 ret;
		ret.x = (this->mat[0][0] * other.x) + (this->mat[0][1] * other.y) + (this->mat[0][2] * other.z) + (this->mat[0][3] * other.w);
		ret.y = (this->mat[1][0] * other.x) + (this->mat[1][1] * other.y) + (this->mat[1][2] * other.z) + (this->mat[1][3] * other.w);
		ret.z = (this->mat[2][0] * other.x) + (this->mat[2][1] * other.y) + (this->mat[2][2] * other.z) + (this->mat[2][3] * other.w);
		ret.w = (this->mat[3][0] * other.x) + (this->mat[3][1] * other.y) + (this->mat[3][2] * other.z) + (this->mat[3][3] * other.w);

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
		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				this->mat[row][col] =
					(other.mat[row][0] * this->mat[0][col]) +
					(other.mat[row][1] * this->mat[1][col]) +
					(other.mat[row][2] * this->mat[2][col]) +
					(other.mat[row][3] * this->mat[3][col]);
			}
		}
	}
	
	Vector3f Xform(Vector3f& vec)
	{
		Vector3f ret;
		ret.x = (this->mat[0][0] * vec.x) + (this->mat[1][0] * vec.y) + (this->mat[2][0] * vec.z);
		ret.y = (this->mat[0][1] * vec.x) + (this->mat[1][1] * vec.y) + (this->mat[2][1] * vec.z);
		ret.z = (this->mat[0][2] * vec.x) + (this->mat[1][2] * vec.y) + (this->mat[2][2] * vec.z);
		ret += this->GetTranslation();

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
	void Scale(const Vector3f& scale) {
		this->mat[0][0] *= scale.x;
		this->mat[0][1] *= scale.x;
		this->mat[0][2] *= scale.x;
		this->mat[1][0] *= scale.y;
		this->mat[1][1] *= scale.y;
		this->mat[1][2] *= scale.y;
		this->mat[2][0] *= scale.z;
		this->mat[2][1] *= scale.z;
		this->mat[2][2] *= scale.z;
	}
	void Scale(float scale) {
		this->mat[0][0] = scale;
		this->mat[1][1] = scale;
		this->mat[2][2] = scale;
		this->mat[3][3] = 1.0f;
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
		return Vector3f{ this->mat[3][0], this->mat[3][1], this->mat[3][2] };
	}
	Vector3f GetRow(uint8_t row)
	{
		return Vector3f{ this->mat[row][0], this->mat[row][1], this->mat[row][2] };
	}
	Vector4 GetRow4(uint8_t row)
	{
		return Vector4{ this->mat[row][0], this->mat[row][1], this->mat[row][2] , this->mat[row][3] };
	}
	Vector3f GetCol(uint8_t col)
	{
		return Vector3f{ this->mat[0][col], this->mat[1][col], this->mat[2][col]};
	}
	Vector4 GetCol4(uint8_t col)
	{
		return Vector4{ this->mat[0][col], this->mat[1][col], this->mat[2][col], this->mat[3][col] };
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
	// returns a rotationMatrix with values set on x
	static Mat4 CreateRotatedY(float radians)
	{
		Mat4 rot;
		rot.mat[0][0] = cos(radians);
		rot.mat[0][2] = sin(radians);
		rot.mat[2][0] = -sin(radians);
		rot.mat[2][2] = cos(radians);
		return rot;
	}
	// returns a rotationMatrix with values set on x
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