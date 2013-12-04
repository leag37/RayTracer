//*************************************************************************************************
// Title: Matrix44.cpp
// Author: Gael Huber
// Description: Define a 4x4 matrix
//*************************************************************************************************
#include "Matrix44.h"
#include <algorithm>

namespace SuperTrace
{
	/** Default constructor
	*/
	Matrix44::Matrix44()
		:	_m00(0.0f), _m01(0.0f), _m02(0.0f), _m03(0.0f),
			_m10(0.0f), _m11(0.0f), _m12(0.0f), _m13(0.0f),
			_m20(0.0f), _m21(0.0f), _m22(0.0f), _m23(0.0f),
			_m30(0.0f), _m31(0.0f), _m32(0.0f), _m33(0.0f)
	{ }

	/** Constructor from array
	* @param
	*	f An array of 16 floating point values
	*/
	Matrix44::Matrix44(const float* f)
		:	_m00(f[0]), _m01(f[1]), _m02(f[2]), _m03(f[3]),
			_m10(f[4]), _m11(f[5]), _m12(f[6]), _m13(f[7]),
			_m20(f[8]), _m21(f[9]), _m22(f[10]), _m23(f[11]),
			_m30(f[12]), _m31(f[13]), _m32(f[14]), _m33(f[15])
	{ }

	/** Constructor from individual values
	* @param
	*	m00..m33 -> floating point values for each row-column value
	*/
	Matrix44::Matrix44(	float m00, float m01, float m02, float m03,
				float m10, float m11, float m12, float m13,
				float m20, float m21, float m22, float m23,
				float m30, float m31, float m32, float m33)
		:	_m00(m00), _m01(m01), _m02(m02), _m03(m03),
			_m10(m10), _m11(m11), _m12(m12), _m13(m13),
			_m20(m20), _m21(m21), _m22(m22), _m23(m23),
			_m30(m30), _m31(m31), _m32(m32), _m33(m33)
	{ }

	/** Copy constructor
	* @param
	*	m The matrix to copy
	*/
	Matrix44::Matrix44(const Matrix44& m)
		:	_m00(m._m00), _m01(m._m01), _m02(m._m02), _m03(m._m03),
			_m10(m._m10), _m11(m._m11), _m12(m._m12), _m13(m._m13),
			_m20(m._m20), _m21(m._m21), _m22(m._m22), _m23(m._m23),
			_m30(m._m30), _m31(m._m31), _m32(m._m32), _m33(m._m33)
	{ }

	/** Destructor
	*/
	Matrix44::~Matrix44()
	{ }

	/** Assignment operator
	* @param
	*	m The matrix to copy over
	* @return
	*	Matrix44& The reference to the assigned matrix
	*/
	Matrix44& Matrix44::operator=(const Matrix44& m)
	{
		if(this == &m)
		{
			return *this;
		}

		_m00 = m._m00; _m01 = m._m01; _m02 = m._m02; _m03 = m._m03;
		_m10 = m._m10; _m11 = m._m11; _m12 = m._m12; _m13 = m._m13;
		_m20 = m._m20; _m21 = m._m21; _m22 = m._m22; _m23 = m._m23;
		_m30 = m._m30; _m31 = m._m31; _m32 = m._m32; _m33 = m._m33;
		return *this;
	}

	/** Multiplication operator
	* @param
	*	m The right-hand matrix in the multiplication
	* @return
	*	Matrix44 The resultant matrix
	*/
	Matrix44 Matrix44::operator*(const Matrix44& m)
	{
		Matrix44 r;
		for(unsigned int i = 0; i < 4; ++i)
		{
			for(unsigned int j = 0; j < 4; ++j)
			{
				r._m[i][j] =	_m[i][0] * m._m[0][j] +
								_m[i][1] * m._m[1][j] +
								_m[i][2] * m._m[2][j] +
								_m[i][3] * m._m[3][j];
			}
		}
		return r;
	}

	/** Multiplication operator
	* @param
	*	m The right-hand matrix in the multiplication
	* @return
	*	Matrix44& The resultant matrix
	*/
	Matrix44& Matrix44::operator*=(const Matrix44& m)
	{
		// Save a copy of the array
		float r[4][4];
		std::memcpy(r, _f, 16);

		// Perform multiplication on copy
		for(unsigned int i = 0; i < 4; ++i)
		{
			for(unsigned int j = 0; j < 4; ++j)
			{
				_m[i][j] =	r[i][0] * m._m[0][j] +
							r[i][1] * m._m[1][j] +
							r[i][2] * m._m[2][j] +
							r[i][3] * m._m[3][j];
			}
		}
		return *this;
	}

}	// Namespace