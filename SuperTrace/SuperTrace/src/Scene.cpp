//*************************************************************************************************
// Title: Scene.cpp
// Author: Gael Huber
// Description: A scene object, which has the ability to trace a ray for a given position.
//*************************************************************************************************
#include "Scene.h"

#include "Material.h"
#include "Camera.h"
#include "Color.h"
#include "Object.h"
#include "Ray.h"
#include "Sphere.h"
#include "STMath.h"
#include "PointLight.h"
#include <ctime>

namespace SuperTrace
{
	/** Default constructor
	*/
	Scene::Scene()
		:	_camera(0)
	{ }

	/** Create the scene
	*/
	void Scene::createScene()
	{
		srand(time(0));

		createLights();
		createObjects();
	}

	/** Trace a given rasterized position
	* @param
	*	x The rasterized x position
	* @param
	*	y The rasterized y position
	*/
	Color Scene::trace(unsigned int x, unsigned int y)
	{
		// Resultant color
		Color color;

		// Get the direction ray
		Ray ray = _camera->rasterToRay(x, y);

		std::list<Object*>::iterator end = _objects.end();
		// Iterate through the list of objects to see if this ray will need to return a color
		for(std::list<Object*>::iterator itr = _objects.begin(); itr != end; ++itr)
		{
			Object* obj = *itr;
			if(obj->intersect(ray) == true)
			{
				// We passed the intersection test for this object, now we need to locate a light source to determine the color
				
				// For now, just iterate through lights and cast shadow rays
				std::list<Light*>::iterator lEnd = _lights.end();
				for(std::list<Light*>::iterator lItr = _lights.begin(); lItr != lEnd; ++lItr)
				{
					Light* light = *lItr;
					color = light->compute(obj, ray);
				}
			}
		}
		return color;
	}

	/** Create the camera for the scene
	*/
	void Scene::setCamera(Camera* camera)
	{
		_camera = camera;

	}

	/** Create lights
	*/
	void Scene::createLights()
	{
		// Setup light components
		Vector4 ambient;
		Vector4 diffuse;
		Vector4 specular;

		// Generate 10 random lights
		for(int i = 0; i < 40; ++i)
		{
			// Generate base light features
			ambient = Vector4(Randf(), Randf(), Randf(), 1.0f);
			diffuse = Vector4(Randf(), Randf(), Randf(), 1.0f);
			specular = Vector4(Randf(), Randf(), Randf(), 1.0f);

			int lightType = rand() % 3;

			// Point
			if(lightType == 0)
			{
				Vector3 position = Vector3(Randf(-25.0f, 25.0f), Randf(-25.0f, 25.0f), Randf(-2.0f, 90.0f));
				Vector3 attenuation = Vector3(Randf(0.0f, 0.2f), Randf(0.0f, 0.2f), Randf(0.0f, 0.2f));

				PointLight* pl = new PointLight(position, attenuation, 1000.0f,
												ambient, diffuse, specular);
				_lights.push_back(pl);
			}
			// Directional
			else if(lightType == 1)
			{

			}
			// Spotlight
			else if(lightType == 2)
			{
			}
		}
	}

	/** Add objects to the scene
	*/
	void Scene::createObjects()
	{
		// Create spheres
		Matrix44 identity;
		identity.setIdentity();
		
		Vector4 ambient;
		Vector4 diffuse;
		Vector4 specular;
		Material m;
		Vector3 position;

		for(int i = 0; i < 60; ++i)
		{
			// Generate material properties
			ambient = Vector4(Randf(), Randf(), Randf(), 1.0f);
			diffuse = Vector4(Randf(), Randf(), Randf(), 1.0f);
			specular = Vector4(Randf(), Randf(), Randf(), Randf(2.0f, 8.0f));
			m = Material(ambient, diffuse, specular);

			// Generate position
			position = Vector3(Randf(-25.0f, 25.0f), Randf(-25.0f, 25.0f), Randf(-2.0f, 90.0f));

			Sphere* s = new Sphere(identity, position, Randf(0.5f, 3.0f));
			s->setMaterial(m);
			_objects.push_back(s);
		}
	}

}	// Namespace