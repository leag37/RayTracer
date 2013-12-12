//*************************************************************************************************
// Title: PointLight.h
//*************************************************************************************************
#ifndef __STPOINTLIGHT_H__
#define __STPOINTLIGHT_H___

#include "Vector3.h"
#include "Light.h"

namespace SuperTrace
{
	/** \addtogroup Effects
	*	@{
	*/

	class PointLight : public Light
	{
	public:
		/** Constructor
		*/
		PointLight();

		/** Constructor
		* @param
		*	ambient Light ambient properties
		* @param
		*	diffuse Light diffuse property
		* @param
		*	specular Light specular property
		*/
		PointLight(const Vector3& position, const Vector3& attenuation, float range,
			const Vector4& ambient, const Vector4& diffuse, const Vector4& specular);

		/** Destructor
		*/
		~PointLight();

		/** Determine the color based on the object's properties
		*/
		Color compute(const Object* obj, const Ray& ray);

	private:
		/** Position of the light
		*/
		Vector3 _position;

		/** Attenuation
		*/
		Vector3 _attenuation;

		/** Range
		*/
		float _range;
	};

	/** @} */

}	// Namespace

#endif	// __STLIGHT_H__