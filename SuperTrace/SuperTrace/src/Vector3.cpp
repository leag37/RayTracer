//*************************************************************************************************
// Title: Vector3.cpp
// Author: Gael Huber
// Description: Define a 3D vector
//*************************************************************************************************
#include <assert.h>
#include <math.h>
#include "Vector3.h"

namespace SuperTrace
{
	/** Default constructor
	*/
	Vector3::Vector3()
		:	_x(0.0f),
			_y(0.0f), 
			_z(0.0f)
	{ }


	/** Constructor
	* @param
	*   x The x coordinate
	* @param
	*   y The y coordinate
	* @param
	*   z The z coordinate
	*/
	Vector3::Vector3(float x, float y, float z)
		:	_x(x),
			_y(y),
			_z(z)
	{ }

	/** Constructor
	* @param
	*	v An array of three floats
	*/
	Vector3::Vector3(float* v)
		:	_x(v[0]),
			_y(v[1]),
			_z(v[2])
	{ }

	/** Copy constructor
	*/
	Vector3::Vector3(const Vector3& v)
		:	_x(v._x),
			_y(v._y),
			_z(v._z)
	{ }

	/** Destructor
	*/
	Vector3::~Vector3()
	{ }

	/** Assignment operator
	*/
	Vector3& Vector3::operator=(const Vector3& v)
	{
		// Copy and return
		_x = v._x;
		_y = v._y;
		_z = v._z;
		return *this;
	}

	/** Equivalence operator
	*/
	bool Vector3::operator==(const Vector3& v) const
	{
		return _x == v._x && _y == v._y && _z == v._z;
	}

	/** Non equivalence operator
	*/
	bool Vector3::operator!=(const Vector3& v) const
	{
		return _x != v._x || _y != v._y || _z != v._z;
	}

	/** Addition operator
	* @param
	*   vec The vector to add
	* @return
	*   Vector3 The sum of two vectors
	*/
	Vector3 Vector3::operator+(const Vector3& v) const
	{
		return Vector3(_x + v._x, _y + v._y, _z + v._z);
	}

	/** Addition operator
	* @param
	*   vec The vector to add
	* @return
	*   Vector3& The sum of two vectors
	*/
	Vector3& Vector3::operator+=(const Vector3& v)
	{
		_x += v._x;
		_y += v._y;
		_z += v._z;
		return *this;
	}

	/** Subtraction operator
	* @param
	*   vec The vector to subtract
	* @return
	*   Vector3 The difference of two vectors
	*/
	Vector3 Vector3::operator-(const Vector3& v) const
	{
		return Vector3(_x - v._x, _y - v._y, _z - v._z);
	}

	/** Subtraction operator
	* @param
	*   vec The vector to subtract
	* @return
	*   Vector3& The difference of two vectors
	*/
	Vector3& Vector3::operator-=(const Vector3& v)
	{
		_x -= v._x;
		_y -= v._y;
		_z -= v._z;
		return *this;
	}

	/** Scale operator
	* @param
	*	scale The value by which to scale
	* @return
	*	Vector3 The scaled vector
	*/
	Vector3 Vector3::operator*(float scale) const
	{
		return Vector3(_x * scale, _y * scale, _z * scale);
	}

	/** Scale operator
	* @param
	*	scale The value by which to scale
	* @param
	*	vec The vector to scale
	* @return
	*	Vector3 The scaled vector
	*/
	Vector3 operator*(float scale, const Vector3& v)
	{
		return Vector3(v._x * scale, v._y * scale, v._z * scale);
	}

	/** Scale operator
	* @param
	*	scale The value by which to scale
	* @return
	*	Vector3& The scaled vector
	*/
	Vector3& Vector3::operator*=(float scale)
	{
		_x *= scale;
		_y *= scale;
		_z *= scale;
		return *this;
	}

	/** Scale operator
	* @param
	*	scale The value by which to scale
	* @return
	*	Vector3 The scaled vector
	*/
	Vector3 Vector3::operator/(float scale) const
	{
		float mScale = 1.0f / scale;
		return Vector3(_x * mScale, _y * mScale, _z * mScale);
	}

	/** Scale operator
	* @param
	*	scale The value by which to scale
	* @return
	*	Vector3& The scaled vector
	*/
	Vector3& Vector3::operator/=(float scale)
	{
		float mScale = 1.0f / scale;
		_x *= mScale;
		_y *= mScale;
		_z *= mScale;
		return *this;
	}

	/** Scale operator
	* @param
	*	scale The value by which to scale
	* @return
	*	Vector3 The scaled vector
	*/
	Vector3 Vector3::operator/(const Vector3& scale) const
	{
		return Vector3(_x / scale._x, _y / scale._y, _z / scale._z);
	}

	/** Scale operator
	* @param
	*	scale The value by which to scale
	* @return
	*	Vector3& The scaled vector
	*/
	Vector3& Vector3::operator/=(const Vector3& scale)
	{
		_x /= scale._x;
		_y /= scale._y;
		_z /= scale._z;
		return *this;
	}

	/** Scale operator
	* @param
	*	base The base value (identical across vector)
	* @param
	*	scale The value by which to scale
	* @return
	*	Vector3 The scaled vector
	*/
	Vector3 operator/(float base, const Vector3& scale)
	{
		return Vector3(base / scale._x, base / scale._y, base / scale._z);
	}

	/** Dot product
	* @param
	*	v The vector with which to take the dot product
	* @return 
	*	float The dot product
	*/
	float Vector3::dot(const Vector3& v) const
	{
		return (_x * v._x) + (_y * v._y) + (_z * v._z);
	}

	/** Cross product
	* @param
	*	v The vector with which to cross
	* @return
	*	Vector3 The cross product
	*/
	Vector3 Vector3::cross(const Vector3& v) const
	{
		return Vector3(_y*v._z - _z*v._y, _z*v._x - _x*v._z, _x*v._y - _y*v._x);
	}

	/** The squared length of the vector
	* @return
	*	float The squared length of the vector
	*/
	float Vector3::lengthSqr() const
	{
		return _x*_x + _y*_y + _z*_z;
	}

	/** The length of the vector
	* @return
	*	float The length of the vector
	*/
	float Vector3::length() const
	{
		return sqrt(_x*_x + _y*_y + _z*_z);
	}

	/** Normalize the vector
	*/
	void Vector3::normalize()
	{
		float len = length();
		*this /= len;
	}

	/** Return a normalized version of the vector
	* @return
	*	Vector3 A normalized copy of this vector
	*/
	Vector3 Vector3::normal() const
	{
		Vector3 v = *this;
		v.normalize();
		return v;
	}
	
	/** Get the x value
	* @return
	*	float The x value of the vector
	*/
	float Vector3::getX() const
	{
		return _x;
	}

	/** Get the y value
	* @return
	*	float The y value of the vector
	*/
	float Vector3::getY() const
	{
		return _y;
	}

	/** Get the z value
	* @return
	*	float The z value of the vector
	*/
	float Vector3::getZ() const
	{
		return _z;
	}

	/** Get a value from the vector by index
	* @param
	*	index The index of the desired value, in the order 0=>x, 1=>y, 2=>z
	* @return
	*	float The value corresponding to the specified index
	*/
	float Vector3::operator[](unsigned int i) const
	{
		assert(i < 3);
		return _f[i];
	}

	/** Get a value from the vector by index
	* @param
	*	index The index of the desired value, in the order 0=>x, 1=>y, 2=>z
	* @return
	*	float The value corresponding to the specified index
	*/
	float Vector3::operator[](int i) const
	{
		assert(i < 3 && i > -1);
		return _f[i];
	}

}	// Namespace
