//*************************************************************************************************
// Title: STMath.cpp
// Author: Gael Huber
// Description: General include for math classes and cross-type functions.
//*************************************************************************************************
#include "STMath.h"
#include <math.h>
#include <algorithm>

namespace SuperTrace
{
	/** Transform a vector by a matrix
	* @param
	*	vec The vector3 to transform
	* @param
	*	mat The matrix44 by which to transform
	* @return
	*	Vector3 The resultant vector
	*/
	Vector3 Vector3TransformPoint(const Vector3& vec, const Matrix44& mat)
	{
		// Perform the multiplicative calculations to transform the vector
		float x = vec.getX()*mat(0,0) + vec.getY()*mat(1,0) + vec.getZ()*mat(2,0) + mat(3,0);
		float y = vec.getX()*mat(0,1) + vec.getY()*mat(1,1) + vec.getZ()*mat(2,1) + mat(3,1);
		float z = vec.getX()*mat(0,2) + vec.getY()*mat(1,2) + vec.getZ()*mat(2,2) + mat(3,2);
		float w = vec.getX()*mat(0,3) + vec.getY()*mat(1,3) + vec.getZ()*mat(2,3) + mat(3,3);

		// If w is either not 0 or not 1, normalize
		if(w != 0.0f && w != 1.0f)
		{
			w = 1.0f / w;
			x *= w;
			y *= w;
			z *= w;
		}

		// Return the corresponding vector
		return Vector3(x, y, z);
	}

	/** Transform a vector by a matrix
	* @param
	*	vec The vector3 to transform
	* @param
	*	mat The matrix44 by which to transform
	* @return
	*	Vector3 The resultant vector
	*/
	Vector3 Vector3Transform(const Vector3& vec, const Matrix44& mat)
	{
		// Perform the multiplicative calculations to transform the vector
		float x = vec.getX()*mat(0,0) + vec.getY()*mat(1,0) + vec.getZ()*mat(2,0);
		float y = vec.getX()*mat(0,1) + vec.getY()*mat(1,1) + vec.getZ()*mat(2,1);
		float z = vec.getX()*mat(0,2) + vec.getY()*mat(1,2) + vec.getZ()*mat(2,2);

		// Return the corresponding vector
		return Vector3(x, y, z);
	}

	/** Solve a quadratic equation
	* @param
	*	a, b, c Values from quadratic equation
	* @param
	*	x0, x1 The resultant roots (if any)
	* @return
	*	bool If at least one root is found
	*/
	bool SolveQuadratic(float a, float b, float c, float& x0, float& x1)
	{
		// Find the discriminant
		float disc = (b * b) - (4.0f * a * c);
		// No roots
		if(disc < 0)
		{
			return false;
		}
		// One root
		else if(disc == 0)
		{
			x0 = x1 = -0.5f * b / a;
		}
		// Two roots
		else
		{
			float q = 0.0f;
			if(b > 0)
			{
				q = -0.5f * (b + sqrt(disc));
			}
			else
			{
				q = -0.5f * (b - sqrt(disc));
			}
			x0 = q / a;
			x1 = c / q;
		}

		if(x0 > x1)
		{
			std::swap(x0, x1);
		}
		return true;
	}

}	// Namespace