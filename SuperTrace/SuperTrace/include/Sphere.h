//*************************************************************************************************
// Title: Sphere.h
// Author: Gael Huber
// Description: Defines a sphere.
//*************************************************************************************************
#ifndef __STSPHERE_H__
#define __STSPHERE_H__

#include "Vector3.h"

namespace SuperTrace
{
	/** \addtogroup Object
	*	@{
	*/
	
	class Ray;

	class Sphere
	{
	public:
		Sphere(const Vector3& center, float radius);

		bool testIntersect(const Ray& ray) const;

	private:
		Vector3 _center;

		float _radius;
	};

	/** @} */

}	// Namespace

#endif	// __STSPHERE_H__