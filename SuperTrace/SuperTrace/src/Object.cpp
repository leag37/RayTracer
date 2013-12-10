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
		_color = Color(	static_cast<float>(rand()) / static_cast<float>(RAND_MAX),
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
	const Color& Object::getColor() const
	{
		return _color;
	}

	/** Get the material
	* @return
	*	Material The material attached to this object
	*/
	const Material& Object::getMaterial() const
	{
		return _material;
	}

	/** Set the material for this object
	* @param
	*	Material The new material for the object
	*/
	void Object::setMaterial(const Material& material)
	{
		_material = material;
	}

}	// Namespace