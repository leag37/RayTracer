//*************************************************************************************************
// Title: PointLight.cpp
//*************************************************************************************************
#include "PointLight.h"
#include "Color.h"
#include "Object.h"
#include "Ray.h"
#include <algorithm>

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
	Color PointLight::compute(const Object* obj, const Ray& ray)
	{
		// Default the color to black
		Color color;

		// Calculate the intersection point
		Vector3 contactPoint = ray(ray.getTMax());

		// Get the surface normal for the given ray.
		Vector3 normal = obj->getSurfaceNormal(contactPoint);

		// Calculate the "eye" position
		Vector3 toEye = ray.getOrigin() - contactPoint;
		toEye.normalize();

		// Vector from contact point to light source
		Vector3 lightDirection = _position - contactPoint;

		// Get the distance from the contact point to the light
		float distance = lightDirection.length();

		if(distance > _range)
		{
			return color;
		}

		// Normalize the light vector
		lightDirection.normalize();

		// Get the object's material
		const Material& m = obj->getMaterial();

		// Calculate ambient term
		Vector4 ambient = m.getAmbient() * _ambient;
		Vector4 diffuse;
		Vector4 specular;

		// Calculate diffuse term
		float diffuseFactor = lightDirection.dot(normal);

		if(diffuseFactor > 0.0f)
		{
			// Calculate the diffuse value
			diffuse = diffuseFactor * (m.getDiffuse() * _diffuse);

			// If we have a positive diffuse value, we can also calculate our specular value
			// Given an incident vector and a normal, calculate the reflection vector with the following formula:
			//	v = i - 2 * n * dot(i•n)
			Vector3 reflect = -lightDirection - (2.0f * normal * lightDirection.dot(normal));
			float specFactor = powf(std::max<float>(reflect.dot(toEye), 0.0f), m.getSpecular().getW());
			specular = specFactor * (m.getSpecular() * _specular);
		}

		// Calculate attenuation
		float attenuation = 1.0f / _attenuation.dot(Vector3(1.0f, distance, distance * distance));
		diffuse *= attenuation;
		specular *= attenuation;

		Vector4 litColor = ambient + diffuse + specular;

		color = Color(litColor.getX(), litColor.getY(), litColor.getZ());

		return color;
	}

}	// Namespace