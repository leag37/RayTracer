//*************************************************************************************************
// Title: Scene.cpp
// Author: Gael Huber
// Description: A scene object, which has the ability to trace a ray for a given position.
//*************************************************************************************************
#include "Scene.h"

#include "Camera.h"
#include "Color.h"
#include "Object.h"
#include "Ray.h"
#include "Sphere.h"
#include "STMath.h"

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

		bool intersect = false;
		std::list<Object*>::iterator end = _objects.end();
		for(std::list<Object*>::iterator itr = _objects.begin(); itr != end; ++itr)
		{
			Object* obj = *itr;
			if(obj->intersect(ray) == true)
			{
				intersect = true;
				color = obj->getColor();
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
	
	}

	/** Add objects to the scene
	*/
	void Scene::createObjects()
	{
		// Create spheres
		Matrix44 i;
		i.setIdentity();
		
		_objects.push_back(new Sphere(i, Vector3(0.0f, 0.0f, -10.0f), 2.5f));
		_objects.push_back(new Sphere(i, Vector3(4.0f, 0.0f, -12.0f), 1.5f));
		_objects.push_back(new Sphere(i, Vector3(-4.0f, 2.0f, -10.0f), 2.0f));
		_objects.push_back(new Sphere(i, Vector3(0.0f, 6.0f, -10.0f), 3.0f));
	}

}	// Namespace