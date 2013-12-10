//*************************************************************************************************
// Title: Material.h
//*************************************************************************************************
#ifndef __STMATERIAL_H__
#define __STMATERIAL_H__

#include "Vector4.h"

namespace SuperTrace
{
	/** \addtogroup Effects
	*	@{
	*/

	class Material
	{
	public:
		/** Constructor
		*/
		Material();

		/** Constructor
		* @param
		*	ambient Material ambient properties
		* @param
		*	diffuse Material diffuse property
		* @param
		*	specular Material specular property
		*/
		Material(const Vector4& ambient, const Vector4& diffuse, const Vector4& specular);

		/** Destructor
		*/
		virtual ~Material();

		/** Get the ambient property
		* @return
		*	const Vector4& The ambient property
		*/
		const Vector4& getAmbient() const;

		/** Get the diffuse property
		* @return
		*	const Vector4& The diffuse property
		*/
		const Vector4& getDiffuse() const;

		/** Get the specular property
		* @return
		*	const Vector4& The specular property
		*/
		const Vector4& getSpecular() const;

	private:
		/** Ambient properties
		*/
		Vector4 _ambient;

		/** Diffuse properties
		*/
		Vector4 _diffuse;

		/** Specular properties
		*/
		Vector4 _specular;
	};

	/** @} */

}	// Namespace

#endif	// __STMATERIAL_H__