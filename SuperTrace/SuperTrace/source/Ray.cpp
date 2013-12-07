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
	Ray::Ray(const Vector3& origin, const Vector3& direction, RayType type, 
			float tMin, float tMax)
		:	_origin(origin),
			_direction(direction),
			_type(type),
			_tMin(tMin),
			_tMax(tMax)
	{ 
		// Calculate inverse direction and sign
		_invDirection = 1.0f / _direction;
		_sign[0] = _invDirection[0] < 0;
		_sign[1] = _invDirection[1] < 0;
		_sign[2] = _invDirection[2] < 0;
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

	/** Get the origin of the ray
	* @return
	*	Vector3 Origin of the ray
	*/
	const Vector3& Ray::getOrigin() const
	{
		return _origin;
	}

	/** Get the direction of the ray
	* @return
	*	Vector3 The direction of the ray
	*/
	const Vector3& Ray::getDirection() const
	{
		return _direction;
	}

	/** Return the type
	* @return 
	*	RayType The ray type
	*/
	RayType Ray::getType() const
	{
		return _type;
	}

	/** Return the current tMin value
	* @return
	*	float tMin
	*/
	float Ray::getTMin() const
	{
		return _tMin;
	}

	/** Set tMin
	* @param 
	*	tMin The new tMin value
	*/
	void Ray::setTMin(float tMin) const
	{
		_tMin = tMin;
	}

	/** Return the current tMax value
	* @return
	*	float tMax
	*/
	float Ray::getTMax() const
	{
		return _tMax;
	}

	/** Set tMax
	* @param 
	*	tMax The new tMax value
	*/
	void Ray::setTMax(float tMax) const
	{
		_tMax = tMax;
	}

	/** Get the inverse direction
	* @return
	*	Vector3 The inverse direction
	*/
	const Vector3& Ray::getInvDirection() const
	{
		return _invDirection;
	}

	/** Get the array of signs
	* @return
	*	const int* The pointer to the signs
	*/
	const int* Ray::getSign() const
	{
		return _sign;
	}

}	// Namespace