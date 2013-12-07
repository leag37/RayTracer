//*************************************************************************************************
// Title: Ray.h
// Author: Gael Huber
// Description: This class defines a ray used for projecting light and intersection tests
//*************************************************************************************************
#ifndef __STRAY_H__
#define __STRAY_H__

#include "Vector3.h"
#include <limits>

namespace SuperTrace
{
	/** \addtogroup Math
	*	@{
	*/

	// Enum for different ray types
	enum RayType
	{
		RAY_TYPE_UNKNOWN = 0,
		RAY_TYPE_CAMERA,
		RAY_TYPE_SHADOW
	};

	class Ray
	{
	public:
		/** Contructor
		*/
		Ray(const Vector3& origin,
			const Vector3& direction,
			RayType type = RAY_TYPE_UNKNOWN, 
			float tMin = 0.0f, 
			float tMax = FLT_MAX);

		/** Parametric operator
		* @param
		*	t Find the endpoint at the corresponding time
		* @return
		*	Vector3 The vector to the end point
		*/
		Vector3 operator() (float t) const;

		/** Get the origin of the ray
		* @return
		*	Vector3 Origin of the ray
		*/
		const Vector3& getOrigin() const;

		/** Get the direction of the ray
		* @return
		*	Vector3 The direction of the ray
		*/
		const Vector3& getDirection() const;

		/** Return the type
		* @return 
		*	RayType The ray type
		*/
		RayType getType() const;

		/** Return the current tMin value
		* @return
		*	float tMin
		*/
		float getTMin() const;

		/** Set tMin
		* @param 
		*	tMin The new tMin value
		*/
		void setTMin(float tMin) const;

		/** Return the current tMax value
		* @return
		*	float tMax
		*/
		float getTMax() const;

		/** Set tMax
		* @param 
		*	tMax The new tMax value
		*/
		void setTMax(float tMax) const;

		/** Get the inverse direction
		* @return
		*	Vector3 The inverse direction
		*/
		const Vector3& getInvDirection() const;

		/** Get the array of signs
		* @return
		*	const int* The pointer to the signs
		*/
		const int* getSign() const;

	private:
		/** Origin point
		*/
		Vector3 _origin;

		/** Ray direction
		*/
		Vector3 _direction;

		/** The ray type
		*/
		RayType _type;

		/** Ray minimum distance
		*/
		mutable float _tMin;

		/** Ray maximum distance
		*/
		mutable float _tMax;

		/** Inverted direction
		*/
		Vector3 _invDirection;

		/** Signs for inverted direction
		*/
		int _sign[3];
	};

	/** @} */

}	// Namespace

#endif // __STRAY_H__