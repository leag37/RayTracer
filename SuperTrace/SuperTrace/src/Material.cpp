//*************************************************************************************************
// Title: Material.cpp
//*************************************************************************************************
#include "Material.h"

namespace SuperTrace
{
	/** Constructor
	*/
	Material::Material()
	{ }

	/** Constructor
	* @param
	*	ambient Material ambient properties
	* @param
	*	diffuse Material diffuse property
	* @param
	*	specular Material specular property
	*/
	Material::Material(const Vector4& ambient, const Vector4& diffuse, const Vector4& specular)
		:	_ambient(ambient), _diffuse(diffuse), _specular(specular)
	{ }

	/** Destructor
	*/
	Material::~Material()
	{ }

	/** Get the ambient property
	* @return
	*	const Vector4& The ambient property
	*/
	const Vector4& Material::getAmbient() const
	{
		return _ambient;
	}

	/** Get the diffuse property
	* @return
	*	const Vector4& The diffuse property
	*/
	const Vector4& Material::getDiffuse() const
	{
		return _diffuse;
	}

	/** Get the specular property
	* @return
	*	const Vector4& The specular property
	*/
	const Vector4& Material::getSpecular() const
	{
		return _specular;
	}

}	// Namespace