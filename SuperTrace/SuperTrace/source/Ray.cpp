//*************************************************************************************************
// Title: Ray.cpp
// Author: Gael Huber
// Description: This class defines a ray used for projecting light and intersection tests
//*************************************************************************************************
#include "Ray.h"
#include <limits>

namespace SuperTrace
{
	/** Contructor
	*/
	Ray::Ray(	const Vector3& origin, 
				const Vector3& direction, 
				RayType type = RAY_TYPE_UNKNOWN, 
				float tMin = 0.0f, 
				float tMax = std::numeric_limits<float>::max())
		:	_origin(origin),
			_direction(direction),
			_type(type),
			_tMin(tMin),
			_tMax(tMax)
	{ 
		// Calculate inverse direction and sign
		_invDirection = 1.0f / _direction;
		sign[0] = _invDirection[0] < 0;
		sign[1] = _invDirection[1] < 0;
		sign[2] = _invDirection[2] < 0;
	}

	/** Parametric operator
	* @param
	*	t Find the endpoint at the corresponding time
	* @return
	*	Vector3 The vector to the end point
	*/
	Vector3 Ray::operator() (float t) const
	{
		return _origin + (_direction * t);
	}

}	// Namespace