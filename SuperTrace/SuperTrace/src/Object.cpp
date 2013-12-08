//*************************************************************************************************
// Title: Object.cpp
// Author: Gael Huber
// Description: A basic object from which other obects can inheric
//*************************************************************************************************
#include "Object.h"
#include <random>

namespace SuperTrace
{
	/** Constructor
	* @param
	*	world The world matrix
	*/
	Object::Object(const Matrix44& world)
		:	_world(world)
	{
		// Get random colors
		_color = Vector3(	static_cast<float>(rand()) / static_cast<float>(RAND_MAX),
							static_cast<float>(rand()) / static_cast<float>(RAND_MAX),
							static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
	}

	/** Destructor
	*/
	Object::~Object()
	{
	}

	/** Get the color
	* @return
	*	Vector3 The color vector for this object
	*/
	const Vector3& Object::getColor() const
	{
		return _color;
	}

}	// Namespace