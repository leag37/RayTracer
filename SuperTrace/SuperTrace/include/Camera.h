//*************************************************************************************************
// Title: Camera.h
// Author: Gael Huber
// Description: A camera in the world.
//*************************************************************************************************
#ifndef __STCAMERA_H__
#define __STCAMERA_H__

#include "Ray.h"

namespace SuperTrace
{
	/** \addtogroup Scene
	*	@{
	*/

	class Camera
	{
	public:
		/** Constructor
		*/
		Camera();

		/** Constructor
		* @param
		*	width The view plane width
		* @param
		*	height The view plane height
		* @param
		*	fov The viewing angle for this camera
		*/
		Camera(unsigned int width, unsigned int height, float fov);

		/** Set the position of the camera
		* @param
		*	v The new position
		*/
		void setPosition(const Vector3& v);

		/** Get the position of the camera
		* @return
		*	Vector3 The position vector
		*/
		const Vector3& getPosition() const;

		/** Set the forward direction of the camera
		* @param
		*	v The new forward direction
		*/
		void setForward(const Vector3& v);

		/** Get the forward for the camera
		* @return
		*	Vector3 The forward for the camera
		*/
		const Vector3& getForward() const;

		/** Given a raster position on the screen, return a view ray
		* @param
		*	x The x raster position
		* @param
		*	y The y raster position
		* @return
		*	Ray The ray that goes from the camera's origin through the specified raster position
		*/
		Ray rasterToRay(unsigned int x, unsigned int y) const;

	private:
		/** Width of the view plane
		*/
		unsigned int _width;

		/** Height of the view plane
		*/
		unsigned int _height;

		/** Aspect ratio
		*/
		float _aspectRatio;

		/** Field of view
		*/
		float _fov;

		/** Position of the camera
		*/
		Vector3 _position;

		/** Forward view direction of the camera
		*/
		Vector3 _forward;
	};

	/** @} */

}	// Namespace

#endif	// __STCAMERA_H__