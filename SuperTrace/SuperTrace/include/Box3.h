//*************************************************************************************************
// Title: Box3.h
// Author: Gael Huber
// Description: Describes a simple axis aligned box
//*************************************************************************************************
#ifndef __STBOX3_H__
#define __STBOX3_H__

#include "Vector3.h"
#include "Object.h"

namespace SuperTrace
{
	/** \addtogroup Objects
	*	@{
	*/

	class Box3 : public Object
	{
	public:
		/** Constructor
		*/
		Box3(const Matrix44& world, const Vector3& min, const Vector3& max);

		/** Test for an intersection between a ray and this box
		* @param
		*	ray The ray to test against intersection
		* @return
		*	bool True if intersection is found, false otherwise
		*/
		bool intersect(const Ray& ray) const;

	private:
		/** Bounds of our box
		*/
		Vector3 _bounds[2];
	};

	/** @} */

}	// Namespace

#endif	// __STBOX3_H__