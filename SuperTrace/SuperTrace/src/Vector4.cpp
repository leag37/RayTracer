//*************************************************************************************************
// Title: Vector4.cpp
// Author: Gael Huber
// Description: Define a 3D vector
//*************************************************************************************************
#include <assert.h>
#include <math.h>
#include "Vector4.h"

namespace SuperTrace
{
	/** Default constructor
	*/
	Vector4::Vector4()
		:	_x(0.0f),
			_y(0.0f), 
			_z(0.0f),
			_w(0.0f)
	{ }


	/** Constructor
	* @param
	*   x The x coordinate
	* @param
	*   y The y coordinate
	* @param
	*   z The z coordinate
	* @param
	*	w The w coordinate
	*/
	Vector4::Vector4(float x, float y, float z, float w)
		:	_x(x),
			_y(y),
			_z(z),
			_w(w)
	{ }

	/** Constructor
	* @param
	*	v An array of three floats
	*/
	Vector4::Vector4(float* v)
		:	_x(v[0]),
			_y(v[1]),
			_z(v[2]),
			_w(v[3])
	{ }

	/** Copy constructor
	*/
	Vector4::Vector4(const Vector4& v)
		:	_x(v._x),
			_y(v._y),
			_z(v._z),
			_w(v._w)
	{ }

	/** Destructor
	*/
	Vector4::~Vector4()
	{ }

	/** Assignment operator
	*/
	Vector4& Vector4::operator=(const Vector4& v)
	{
		// Copy and return
		_x = v._x;
		_y = v._y;
		_z = v._z;
		_w = v._w;
		return *this;
	}

	/** Equivalence operator
	*/
	bool Vector4::operator==(const Vector4& v) const
	{
		return _x == v._x && _y == v._y && _z == v._z && _w == v._w;
	}

	/** Non equivalence operator
	*/
	bool Vector4::operator!=(const Vector4& v) const
	{
		return _x != v._x || _y != v._y || _z != v._z || _w != v._w;
	}

	/** Addition operator
	* @param
	*   vec The vector to add
	* @return
	*   Vector4 The sum of two vectors
	*/
	Vector4 Vector4::operator+(const Vector4& v) const
	{
		return Vector4(_x + v._x, _y + v._y, _z + v._z, _w + v._w);
	}

	/** Addition operator
	* @param
	*   vec The vector to add
	* @return
	*   Vector4& The sum of two vectors
	*/
	Vector4& Vector4::operator+=(const Vector4& v)
	{
		_x += v._x;
		_y += v._y;
		_z += v._z;
		_w += v._w;
		return *this;
	}

	/** Subtraction operator
	* @param
	*   vec The vector to subtract
	* @return
	*   Vector4 The difference of two vectors
	*/
	Vector4 Vector4::operator-(const Vector4& v) const
	{
		return Vector4(_x - v._x, _y - v._y, _z - v._z, _w - v._w);
	}

	/** Subtraction operator
	* @param
	*   vec The vector to subtract
	* @return
	*   Vector4& The difference of two vectors
	*/
	Vector4& Vector4::operator-=(const Vector4& v)
	{
		_x -= v._x;
		_y -= v._y;
		_z -= v._z;
		_w -= v._w;
		return *this;
	}

	/** Scale operator
	* @param
	*	scale The value by which to scale
	* @return
	*	Vector4 The scaled vector
	*/
	Vector4 Vector4::operator*(const Vector4& scale) const
	{
		return Vector4(_x * scale._x, _y * scale._y, _z * scale._z, _w * scale._w);
	}

	/** Scale operator
	* @param
	*	scale The value by which to scale
	* @return
	*	Vector4 The scaled vector
	*/
	Vector4 Vector4::operator*(float scale) const
	{
		return Vector4(_x * scale, _y * scale, _z * scale, _w * scale);
	}

	/** Scale operator
	* @param
	*	scale The value by which to scale
	* @param
	*	vec The vector to scale
	* @return
	*	Vector4 The scaled vector
	*/
	Vector4 operator*(float scale, const Vector4& v)
	{
		return Vector4(v._x * scale, v._y * scale, v._z * scale, v._w * scale);
	}

	/** Scale operator
	* @param
	*	scale The value by which to scale
	* @return
	*	Vector4& The scaled vector
	*/
	Vector4& Vector4::operator*=(float scale)
	{
		_x *= scale;
		_y *= scale;
		_z *= scale;
		_w *= scale;
		return *this;
	}

	/** Scale operator
	* @param
	*	scale The value by which to scale
	* @return
	*	Vector4 The scaled vector
	*/
	Vector4 Vector4::operator/(float scale) const
	{
		float mScale = 1.0f / scale;
		return Vector4(_x * mScale, _y * mScale, _z * mScale, _w * scale);
	}

	/** Scale operator
	* @param
	*	scale The value by which to scale
	* @return
	*	Vector4& The scaled vector
	*/
	Vector4& Vector4::operator/=(float scale)
	{
		float mScale = 1.0f / scale;
		_x *= mScale;
		_y *= mScale;
		_z *= mScale;
		_w *= mScale;
		return *this;
	}

	/** Scale operator
	* @param
	*	scale The value by which to scale
	* @return
	*	Vector4 The scaled vector
	*/
	Vector4 Vector4::operator/(const Vector4& scale) const
	{
		return Vector4(_x / scale._x, _y / scale._y, _z / scale._z, _w / scale._w);
	}

	/** Scale operator
	* @param
	*	scale The value by which to scale
	* @return
	*	Vector4& The scaled vector
	*/
	Vector4& Vector4::operator/=(const Vector4& scale)
	{
		_x /= scale._x;
		_y /= scale._y;
		_z /= scale._z;
		_w /= scale._w;
		return *this;
	}

	/** Scale operator
	* @param
	*	base The base value (identical across vector)
	* @param
	*	scale The value by which to scale
	* @return
	*	Vector4 The scaled vector
	*/
	Vector4 operator/(float base, const Vector4& scale)
	{
		return Vector4(base / scale._x, base / scale._y, base / scale._z, base / scale._w);
	}

	/** Dot product
	* @param
	*	v The vector with which to take the dot product
	* @return 
	*	float The dot product
	*/
	float Vector4::dot(const Vector4& v) const
	{
		return (_x * v._x) + (_y * v._y) + (_z * v._z) + (_w * v._w);
	}

	/** The squared length of the vector
	* @return
	*	float The squared length of the vector
	*/
	float Vector4::lengthSqr() const
	{
		return (_x*_x) + (_y*_y) + (_z*_z) + (_w*_w);
	}

	/** The length of the vector
	* @return
	*	float The length of the vector
	*/
	float Vector4::length() const
	{
		return sqrt((_x*_x) + (_y*_y) + (_z*_z) + (_w*_w));
	}

	/** Normalize the vector
	*/
	void Vector4::normalize()
	{
		float len = length();
		*this /= len;
	}

	/** Return a normalized version of the vector
	* @return
	*	Vector4 A normalized copy of this vector
	*/
	Vector4 Vector4::normal() const
	{
		Vector4 v = *this;
		v.normalize();
		return v;
	}
	
	/** Get the x value
	* @return
	*	float The x value of the vector
	*/
	float Vector4::getX() const
	{
		return _x;
	}

	/** Get the y value
	* @return
	*	float The y value of the vector
	*/
	float Vector4::getY() const
	{
		return _y;
	}

	/** Get the z value
	* @return
	*	float The z value of the vector
	*/
	float Vector4::getZ() const
	{
		return _z;
	}

	/** Get the w value
	* @return
	*	float The w value of the vector
	*/
	float Vector4::getW() const
	{
		return _w;
	}

	/** Get a value from the vector by index
	* @param
	*	index The index of the desired value, in the order 0=>x, 1=>y, 2=>z
	* @return
	*	float The value corresponding to the specified index
	*/
	float Vector4::operator[](unsigned int i) const
	{
		assert(i < 4);
		return _f[i];
	}

	/** Get a value from the vector by index
	* @param
	*	index The index of the desired value, in the order 0=>x, 1=>y, 2=>z
	* @return
	*	float The value corresponding to the specified index
	*/
	float Vector4::operator[](int i) const
	{
		assert(i < 4 && i > -1);
		return _f[i];
	}

}	// Namespace
