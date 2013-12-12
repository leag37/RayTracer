//*************************************************************************************************
// Title: Object.h
// Author: Gael Huber
// Description: A basic object from which other obects can inheric
//*************************************************************************************************
#ifndef __STOBJECT_H__
#define __STOBJECT_H__

#include "STMath.h"
#include "Color.h"
#include "Material.h"

namespace SuperTrace
{
	/** \addtogroup Object
	*	@{
	*/

	class Ray;
	class Vector3;

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
		const Color& getColor() const;

		/** Get the material
		* @return
		*	Material The material attached to this object
		*/
		const Material& getMaterial() const;

		/** Set the material for this object
		* @param
		*	Material The new material for the object
		*/
		void setMaterial(const Material& material);

		/** Calculate the surface normal for a given contact point
		* @param
		*	surfacePoint The surface point at which to construct a normal
		* @return
		*	Vector3 A vector representing a surface normal
		*/
		virtual Vector3 getSurfaceNormal(const Vector3& surfacePoint) const = 0;

	protected:
		/** World matrix
		*/
		Matrix44 _world;

		/** Object color
		*/
		Color _color;

		/** Object material
		*/
		Material _material;
	};

	/** @} */

}	// Namespace

#endif // __STOBJECT_H__