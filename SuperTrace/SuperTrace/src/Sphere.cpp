//*************************************************************************************************
// Title: Sphere.cpp
// Author: Gael Huber
// Description: Defines a sphere.
//*************************************************************************************************
#include "Sphere.h"
#include "Ray.h"
#include "STMath.h"

namespace SuperTrace
{
	Sphere::Sphere(const Vector3& center, float radius)
		:	_center(center), _radius(radius)
	{ }

	bool Sphere::testIntersect(const Ray& ray) const
	{
		// Solution for t if the ray intersects
		float t0, t1;

		// Use the analytic solution
		Vector3 L = ray.getOrigin() - _center;

		// Calculate a, b, and c for quadratic
		float a = ray.getDirection().dot(ray.getDirection());
		float b = 2.0f * ray.getDirection().dot(L);
		float c = L.dot(L) - (_radius * _radius);
		
		// Attempt to solve the quadratic
		if(SolveQuadratic(a, b, c, t0, t1) == false)
		{
			return false;
		}

		// If t0 is greater than the max extent of the ray, no intersect
		if(t0 > ray.getTMax())
		{
			return false;
		}
		else
		{
			ray.setTMax(t0);
		}
		return true;
	}

}	// Namespace