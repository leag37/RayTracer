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

		/** Calculate the surface normal for a given contact point
		* @param
		*	surfacePoint The surface point at which to construct a normal
		* @return
		*	Vector3 A vector representing a surface normal
		*/
		Vector3 getSurfaceNormal(const Vector3& surfacePoint) const;

	private:
		Vector3 _center;

		float _radius;
	};

	/** @} */

}	// Namespace

#endif	// __STSPHERE_H__