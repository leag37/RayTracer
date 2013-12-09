//*************************************************************************************************
// Title: Scene.h
// Author: Gael Huber
// Description: A scene object, which has the ability to trace a ray for a given position.
//*************************************************************************************************
#ifndef __STSCENE_H__
#define __STSCENE_H__

#include <list>

namespace SuperTrace
{
	/** \addtogroup Scene
	*	@{
	*/

	// Forward declarations
	class Camera;
	class Color;
	class Light;
	class Object;

	class Scene
	{
	public:
		/** Default constructor
		*/
		Scene();

		/** Create the scene
		*/
		void createScene();

		/** Create the camera for the scene
		*/
		void setCamera(Camera* camera);

		/** Trace a given rasterized position
		* @param
		*	x The rasterized x position
		* @param
		*	y The rasterized y position
		*/
		Color trace(unsigned int x, unsigned int y);

	private:
		/** Create lights
		*/
		void createLights();

		/** Add objects to the scene
		*/
		void createObjects();

	private:
		/** List of objects in the scene
		*/
		std::list<Object*> _objects;

		/** List of lights in the scene
		*/
		std::list<Light*> _lights; 

		/** Scene camera
		*/
		Camera* _camera;
	};

	/** @} */

}	// Namespace

#endif