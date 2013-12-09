//*************************************************************************************************
// 
//*************************************************************************************************
#ifndef __STLIGHT_H__
#define __STLIGHT_H___

#include "Vector4.h"

namespace SuperTrace
{
	class Light
	{
	public:
		/** Constructor
		*/
		Light();

		/** Constructor
		* @param
		*	ambient Light ambient properties
		* @param
		*	diffuse Light diffuse property
		* @param
		*	specular Light specular property
		*/
		Light(const Vector4& ambient, const Vector4& diffuse, const Vector4& specular);

	protected:
		/** Ambient properties
		*/
		Vector4 _ambient;

		/** Diffuse properties
		*/
		Vector4 _diffuse;

		/** Specular properties
		*/
		Vector4 _specular;
	}
}	// Namespace

#endif	// __STLIGHT_H__