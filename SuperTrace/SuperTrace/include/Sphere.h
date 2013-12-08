//*************************************************************************************************
// Title: Sphere.h
// Author: Gael Huber
// Description: Defines a sphere.
//*************************************************************************************************
#ifndef __STSPHERE_H__
#define __STSPHERE_H__

#include "Vector3.h"
#include "Object.h"

namespace SuperTrace
{
	/** \addtogroup Object
	*	@{
	*/

	class Sphere : public Object
	{
	public:
		Sphere(const Matrix44& world, const Vector3& center, float radius);

		bool intersect(const Ray& ray) const;

	private:
		Vector3 _center;

		float _radius;
	};

	/** @} */

}	// Namespace

#endif	// __STSPHERE_H__