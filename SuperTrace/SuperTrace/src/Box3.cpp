//*************************************************************************************************
// Title: Box3.cpp
// Author: Gael Huber
// Description: Describes a simple axis aligned box
//*************************************************************************************************
#include "Box3.h"
#include "Ray.h"

namespace SuperTrace
{
	/** Constructor
	*/
	Box3::Box3(const Vector3& min, const Vector3& max)
	{
		_bounds[0] = min;
		_bounds[1] = max;
	}

	/** Test for an intersection between a ray and this box
	* @param
	*	ray The ray to test against intersection
	* @return
	*	bool True if intersection is found, false otherwise
	*/
	bool Box3::testIntersect(const Ray& ray) const
	{
		float tMin, tMax, tyMin, tyMax, tzMin, tzMax;

		tMin = (_bounds[ray.getSign()[0]].getX() - ray.getOrigin().getX()) * ray.getInvDirection().getX();
		tMax = (_bounds[1 - ray.getSign()[0]].getX() - ray.getOrigin().getX()) * ray.getInvDirection().getX();
		tyMin = (_bounds[ray.getSign()[1]].getY() - ray.getOrigin().getY()) * ray.getInvDirection().getY();
		tyMax = (_bounds[1 - ray.getSign()[1]].getY() - ray.getOrigin().getY()) * ray.getInvDirection().getY();

		// Check x and y bounds
		if((tMin > tyMax) || (tyMin > tMax))
		{
			return false;
		}

		// Calculate tMin and tMax
		if(tyMin > tMin)
		{
			tMin = tyMin;
		}
		if(tyMax < tMax)
		{
			tMax = tyMax;
		}

		// Calculate tzmin and max
		tzMin = (_bounds[ray.getSign()[2]].getZ() - ray.getOrigin().getZ()) * ray.getInvDirection().getZ();
		tzMax = (_bounds[1 - ray.getSign()[2]].getZ() - ray.getOrigin().getZ()) * ray.getInvDirection().getZ();

		if((tMin > tzMax) || (tzMin > tMax))
		{
			return false;
		}

		// Calculate new tMin and tMax
		if(tzMin > tMin)
		{
			tMin = tzMin;
		}
		if(tzMax < tMax)
		{
			tMax = tzMax;
		}

		// Check tMin and tMax against the ray's distances
		if(tMin > ray.getTMin())
		{
			ray.setTMin(tMin);
		}
		if(tMax < ray.getTMax())
		{
			ray.setTMax(tMax);
		}
	}

}	// Namespace