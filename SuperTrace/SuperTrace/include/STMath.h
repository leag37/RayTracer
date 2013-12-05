//*************************************************************************************************
// Title: STMath.h
// Author: Gael Huber
// Description: General include for math classes and cross-type functions.
//*************************************************************************************************
#ifndef __STMATH_H__
#define __STMATH_H__

#include "Matrix44.h"
#include "Vector3.h"

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
	Vector3 Vector3TransformPoint(const Vector3& vec, const Matrix44& mat);

	/** Transform a vector by a matrix
	* @param
	*	vec The vector3 to transform
	* @param
	*	mat The matrix44 by which to transform
	* @return
	*	Vector3 The resultant vector
	*/
	Vector3 Vector3Transform(const Vector3& vec, const Matrix44& mat);

}	// Namespace

#endif // __STMATH_H__