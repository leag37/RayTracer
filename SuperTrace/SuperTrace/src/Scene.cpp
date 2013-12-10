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
					color = light->compute(obj);
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
		PointLight* pl = new PointLight(Vector3(), Vector3(0.0f, 0.1f, 0.0f), 100.0f, 
			Vector4(0.5f, 0.5f, 0.5f, 1.0f), Vector4(), Vector4());
		_lights.push_back(pl);
	}

	/** Add objects to the scene
	*/
	void Scene::createObjects()
	{
		// Create spheres
		Matrix44 i;
		i.setIdentity();
		
		Material m = Material(Vector4(0.5f, 0.5f, 0.5f, 1.0f), Vector4(), Vector4());
		Sphere* s = new Sphere(i, Vector3(0.0f, 0.0f, -10.0f), 2.5f);
		s->setMaterial(m);
		_objects.push_back(s);

		s = new Sphere(i, Vector3(4.0f, 0.0f, -12.0f), 1.5f);
		s->setMaterial(m);
		_objects.push_back(s);

		s = new Sphere(i, Vector3(-4.0f, 2.0f, -10.0f), 2.0f);
		s->setMaterial(m);
		_objects.push_back(s);

		s = new Sphere(i, Vector3(0.0f, 6.0f, -10.0f), 3.0f);
		s->setMaterial(m);
		_objects.push_back(s);
	}

}	// Namespace