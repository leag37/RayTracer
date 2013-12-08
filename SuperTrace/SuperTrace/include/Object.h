//*************************************************************************************************
// Title: Object.h
// Author: Gael Huber
// Description: A basic object from which other obects can inheric
//*************************************************************************************************
#ifndef __STOBJECT_H__
#define __STOBJECT_H__

#include "STMath.h"

namespace SuperTrace
{
	/** \addtogroup Object
	*	@{
	*/

	class Ray;

	class Object
	{
	public:
		/** Constructor
		* @param
		*	world The world matrix
		*/
		Object(const Matrix44& world);

		/** Destructor
		*/
		virtual ~Object();

		/** Intersect test
		* @param
		*	ray The ray to test intersection again
		* @param
		*	intersectData The object that holds intersection data (point of contact, etc)
		*/
		virtual bool intersect(const Ray& ray) const = 0;

		/** Get the color
		* @return
		*	Vector3 The color vector for this object
		*/
		const Vector3& getColor() const;

	protected:
		/** World matrix
		*/
		Matrix44 _world;

		/** Object color
		*/
		Vector3 _color;
	};

	/** @} */

}	// Namespace

#endif // __STOBJECT_H__