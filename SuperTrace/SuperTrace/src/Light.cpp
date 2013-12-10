//*************************************************************************************************
// Title: Light.cpp
//*************************************************************************************************
#include "Light.h"

namespace SuperTrace
{
	/** Constructor
	*/
	Light::Light()
	{ }

	/** Constructor
	* @param
	*	ambient Light ambient properties
	* @param
	*	diffuse Light diffuse property
	* @param
	*	specular Light specular property
	*/
	Light::Light(const Vector4& ambient, const Vector4& diffuse, const Vector4& specular)
		:	_ambient(ambient), _diffuse(diffuse), _specular(specular)
	{ }

	/** Destructor
	*/
	Light::~Light()
	{ }

}	// Namespace