//*************************************************************************************************
// Title: PointLight.cpp
//*************************************************************************************************
#include "PointLight.h"
#include "Color.h"
#include "Object.h"

namespace SuperTrace
{
	/** Constructor
	*/
	PointLight::PointLight()
		: Light()
	{ }

	/** Constructor
	* @param
	*	ambient Light ambient properties
	* @param
	*	diffuse Light diffuse property
	* @param
	*	specular Light specular property
	*/
	PointLight::PointLight(const Vector3& position, const Vector3& attenuation, float range,
		const Vector4& ambient, const Vector4& diffuse, const Vector4& specular)
		:	Light(ambient, diffuse, specular),
			_position(position), _attenuation(attenuation), _range(range)
	{ }

	/** Destructor
	*/
	PointLight::~PointLight()
	{ }

	/** Determine the color based on the object's properties
	*/
	Color PointLight::compute(const Object* obj)
	{
		return obj->getColor();
	}

}	// Namespace