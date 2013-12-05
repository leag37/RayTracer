//*************************************************************************************************
// Title: Matrix44.cpp
// Author: Gael Huber
// Description: Define a 4x4 matrix
//*************************************************************************************************
#include "Matrix44.h"
#include <algorithm>
#include <assert.h>

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

	/** Access operator
	* @param
	*	row	The row index
	* @param
	*	column The column index
	* @return
	*	float The corresponding value
	*/
	float Matrix44::operator()(int row, int column) const
	{
		assert(row > -1 && row < 4 && column > -1 && column < 4);
		return _m[row][column];
	}

	/** Access operator
	* @param
	*	row	The row index
	* @param
	*	column The column index
	* @return
	*	float The corresponding value
	*/
	float Matrix44::operator()(unsigned int row, unsigned int column) const
	{
		assert(row < 4 && column < 4);
		return _m[row][column];
	}

	/** Set this matrix to identity
	*/
	void Matrix44::setIdentity()
	{
		_m00 = 1.0f; _m01 = 0.0f; _m02 = 0.0f; _m03 = 0.0f;
		_m10 = 0.0f; _m11 = 1.0f; _m12 = 0.0f; _m13 = 0.0f;
		_m20 = 0.0f; _m21 = 0.0f; _m22 = 1.0f; _m23 = 0.0f;
		_m30 = 0.0f; _m31 = 0.0f; _m32 = 0.0f; _m33 = 1.0f;
	}

	/** Transpose this matrix
	*/
	void Matrix44::transpose()
	{
		// Temp storage value
		float t;
		for(unsigned int i = 0; i < 4; ++i)
		{
			for(unsigned int j = i; j < 4; ++j)
			{
				// Swap values
				t = _m[i][j];
				_m[i][j] = _m[j][i];
				_m[j][i] = t;
			}
		}
	}

	/** Return a transposed copy of this matrix
	* @return
	*	Matrix44 The transposed copy
	*/
	Matrix44 Matrix44::getTranspose() const
	{
		Matrix44 m;
		for(unsigned int i = 0; i < 4; ++i)
		{
			for(unsigned int j = 0; j < 4; ++j)
			{
				m._m[i][j] = _m[j][i];
			}
		}
		return m;
	}

	/** Invert this matrix
	*/
	void Matrix44::inverse()
	{
		// Prepare our augmented matrix
		Matrix44 aug;
		aug.setIdentity();

		// Our first operation is to make sure the pivot for each for is not 0
		for(unsigned int col = 0; col < 4; ++col)
		{
			// If the pivot is 0, swap
			if(_m[col][col] == 0.0f)
			{
				// We must find another row (in this we select the row with the absolute highest value
				unsigned int index = col;
				for(unsigned int row = 0; row < 4; ++row)
				{
					// Select if the value is bigger
					if(fabs(_m[row][col]) > fabs(_m[index][col]))
					{
						index = row;
					}
				}

				// If the index is not the column, swap the rows
				if(index != col)
				{
					for(unsigned int i = 0; i < 4; ++i)
					{
						float t = _m[col][col];
						_m[col][col] = _m[index][col];
						_m[index][col] = t;

						t = aug._m[col][col];
						aug._m[col][col] = aug._m[index][col];
						aug._m[index][col] = t;
					}
				}
			}

			// Now that we have a non-zero pivot, we must reduce each row in this column to zero
			for(unsigned int row = 0; row < 4; ++row)
			{
				// Don't reduce our row...
				if(row != col)
				{
					// The coefficient by which to reduce is row|column / col|col
					float coefficient = _m[row][col] / _m[col][col];
					if(coefficient != 0.0f)
					{
						// Reduce the row
						for(unsigned int i = 0; i < 4; ++i)
						{
							_m[row][i] -= coefficient * _m[col][i];
							aug._m[row][i] -= coefficient * aug._m[col][i];
						}

						// Set the current element to 0 to avoid rounding errors
						_m[row][col] = 0.0f;
					}
				}
			}
		}

		// Now, scale each element by it's own coefficient
		for(unsigned int row = 0; row < 4; ++row)
		{
			for(unsigned int col = 0; col < 4; ++col)
			{
				aug._m[row][col] /= _m[row][row];
			}
		}

		// Now our augmented matrix should be equal to the matrix we want to return, so set it to ourselves
		*this = aug;
	}

	/** Return the inverse of this matrix
	* @return
	*	Matrix44 The inverse of the matrix
	*/
	Matrix44 Matrix44::getInverse() const
	{
		// Prepare our augmented matrix
		Matrix44 aug;
		aug.setIdentity();

		// Keep a copy of our current matrix to avoid changing it
		Matrix44 m = *this;

		// Our first operation is to make sure the pivot for each for is not 0
		for(unsigned int col = 0; col < 4; ++col)
		{
			// If the pivot is 0, swap
			if(m._m[col][col] == 0.0f)
			{
				// We must find another row (in this we select the row with the absolute highest value
				unsigned int index = col;
				for(unsigned int row = 0; row < 4; ++row)
				{
					// Select if the value is bigger
					if(fabs(m._m[row][col]) > fabs(m._m[index][col]))
					{
						index = row;
					}
				}

				// If the index is not the column, swap the rows
				if(index != col)
				{
					for(unsigned int i = 0; i < 4; ++i)
					{
						float t = m._m[col][col];
						m._m[col][col] = m._m[index][col];
						m._m[index][col] = t;

						t = aug._m[col][col];
						aug._m[col][col] = aug._m[index][col];
						aug._m[index][col] = t;
					}
				}
			}

			// Now that we have a non-zero pivot, we must reduce each row in this column to zero
			for(unsigned int row = 0; row < 4; ++row)
			{
				// Don't reduce our row...
				if(row != col)
				{
					// The coefficient by which to reduce is row|column / col|col
					float coefficient = m._m[row][col] / m._m[col][col];
					if(coefficient != 0.0f)
					{
						// Reduce the row
						for(unsigned int i = 0; i < 4; ++i)
						{
							m._m[row][i] -= coefficient * m._m[col][i];
							aug._m[row][i] -= coefficient * aug._m[col][i];
						}

						// Set the current element to 0 to avoid rounding errors
						m._m[row][col] = 0.0f;
					}
				}
			}
		}

		// Now, scale each element by it's own coefficient
		for(unsigned int row = 0; row < 4; ++row)
		{
			for(unsigned int col = 0; col < 4; ++col)
			{
				aug._m[row][col] /= m._m[row][row];
			}
		}

		// Now our augmented matrix should be equal to the matrix we want to return, so set it to ourselves
		return aug;
	}

	/** Return an identity matrix
	* @return
	*	Matrix44 An identity matrix
	*/
	Matrix44 Matrix44Identity()
	{
		return Matrix44(1.0f, 0.0f, 0.0f, 0.0f,
						0.0f, 1.0f, 0.0f, 0.0f,
						0.0f, 0.0f, 1.0f, 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f);
	}

	/** Return a translation matrix
	* @param
	*	tx The x translation
	* @param
	*	ty The y translation
	* @param
	*	tz The z translation
	* @return
	*	Matrix44 A translation matrix
	*/
	Matrix44 Matrix44Translation(float tx, float ty, float tz)
	{
		return Matrix44(1.0f, 0.0f, 0.0f, 0.0f,
						0.0f, 1.0f, 0.0f, 0.0f,
						0.0f, 0.0f, 1.0f, 0.0f,
						tx, ty, tz, 1.0f);
	}

	/** Return a scaling matrix 
	* @param
	*	sx The x scale factor
	* @param
	*	sy The y scale factor
	* @param 
	*	sz The z scale factor
	* @return
	*	Matrix44 A scaling matrix
	*/
	Matrix44 Matrix44Scale(float sx, float sy, float sz)
	{
		return Matrix44(sx, 0.0f, 0.0f, 0.0f,
						0.0f, sy, 0.0f, 0.0f,
						0.0f, 0.0f, sz, 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f);
	}

	/** Return a x-axis rotation matrix
	* @param
	*	rot The rotation in radians
	* @return
	*	Matrix44 The rotation matrix
	*/
	Matrix44 Matrix44RotationX(float rot)
	{
		float cos = cosf(rot);
		float sin = sinf(rot);
		return Matrix44(1.0f, 0.0f, 0.0f, 0.0f,
						0.0f, cos, sin, 0.0f,
						0.0f, -sin, cos, 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f);
	}

	/** Return a y-axis rotation matrix
	* @param
	*	rot The rotation in radians
	* @return
	*	Matrix44 The rotation matrix
	*/
	Matrix44 Matrix44RotationY(float rot)
	{
		float cos = cosf(rot);
		float sin = sinf(rot);
		return Matrix44(cos, 0.0f, -sin, 0.0f,
						0.0f, 1.0f, 0.0f, 0.0f,
						sin, 0.0f, cos, 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f);
	}

	/** Return a z-axis rotation matrix
	* @param
	*	rot The rotation in radians
	* @return
	*	Matrix44 The rotation matrix
	*/
	Matrix44 Matrix44RotationZ(float rot)
	{
		float cos = cosf(rot);
		float sin = sinf(rot);
		return Matrix44(cos, sin, 0.0f, 0.0f,
						-sin, cos, 0.0f, 0.0f,
						0.0f, 0.0f, 1.0f, 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f);
	}

}	// Namespace