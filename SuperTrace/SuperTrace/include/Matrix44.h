//*************************************************************************************************
// Title: Matrix44.h
// Author: Gael Huber
// Description: Define a 4x4 matrix
//*************************************************************************************************
#ifndef __STMATRIX44_H__
#define __STMATRIX44_H__

namespace SuperTrace
{
	/** \addtogroup Math
	*	@{
	*/

	class Matrix44
	{
	public:
		/** Default constructor
		*/
		Matrix44();

		/** Constructor from array
		* @param
		*	f An array of 16 floating point values
		*/
		Matrix44(const float* f);

		/** Constructor from individual values
		* @param
		*	m00..m33 -> floating point values for each row-column value
		*/
		Matrix44(	float m00, float m01, float m02, float m03,
					float m10, float m11, float m12, float m13,
					float m20, float m21, float m22, float m23,
					float m30, float m31, float m32, float m33);

		/** Copy constructor
		* @param
		*	m The matrix to copy
		*/
		Matrix44(const Matrix44& m);

		/** Destructor
		*/
		~Matrix44();

		/** Assignment operator
		* @param
		*	m The matrix to copy over
		* @return
		*	Matrix44& The reference to the assigned matrix
		*/
		Matrix44& operator=(const Matrix44& m);

		/** Multiplication operator
		* @param
		*	m The right-hand matrix in the multiplication
		* @return
		*	Matrix44 The resultant matrix
		*/
		Matrix44 operator*(const Matrix44& m);

		/** Multiplication operator
		* @param
		*	m The right-hand matrix in the multiplication
		* @return
		*	Matrix44& The resultant matrix
		*/
		Matrix44& operator*=(const Matrix44& m);

	private:
		/** The union between the different matrix representations
		*/
		union
		{
			// Standard notation
			struct
			{
				float _m00, _m01, _m02, _m03;
				float _m10, _m11, _m12, _m13;
				float _m20, _m21, _m22, _m23;
				float _m30, _m31, _m32, _m33;
			};

			// 4x4 array representation
			float _m[4][4];

			// Array representation
			float _f[16];
		};
	};

	/** @} */

}	// Namespace

#endif // __STMATRIX44_H__