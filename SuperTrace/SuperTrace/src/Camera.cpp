//*************************************************************************************************
// Title: Camera.cpp
// Author: Gael Huber
// Description: A camera in the world.
//*************************************************************************************************
#include "Camera.h"

namespace SuperTrace
{
	/** Constructor
	*/
	Camera::Camera()
		:	_width(0), _height(0), _aspectRatio(0.0f), _fov(0.0f), 
			_position(Vector3()), _forward(Vector3(0.0f, 0.0f, -1.0f))
	{ }

	/** Constructor
	* @param
	*	width The view plane width
	* @param
	*	height The view plane height
	* @param
	*	fov The viewing angle for this camera
	*/
	Camera::Camera(unsigned int width, unsigned int height, float fov)
		:	_width(width), _height(height), _fov(fov),
			_position(Vector3()), _forward(Vector3(0.0f, 0.0f, -1.0f))
	{
		_aspectRatio = static_cast<float>(width) / static_cast<float>(height);
	}

	/** Set the position of the camera
	* @param
	*	v The new position
	*/
	void Camera::setPosition(const Vector3& v)
	{
		_position = v;
	}

	/** Get the position of the camera
	* @return
	*	Vector3 The position vector
	*/
	const Vector3& Camera::getPosition() const
	{
		return _position;
	}

	/** Set the forward direction of the camera
	* @param
	*	v The new forward direction
	*/
	void Camera::setForward(const Vector3& v)
	{
		_forward = v;
	}

	/** Get the forward for the camera
	* @return
	*	Vector3 The forward for the camera
	*/
	const Vector3& Camera::getForward() const
	{
		return _forward;
	}

	/** Given a raster position on the screen, return a view ray
	* @param
	*	x The x raster position
	* @param
	*	y The y raster position
	* @return
	*	Ray The ray that goes from the camera's origin through the specified raster position
	*/
	Ray Camera::rasterToRay(unsigned int x, unsigned int y) const
	{
		// First, remap from raster space to screen space
		float fX = static_cast<float>(x);
		float fY = static_cast<float>(y);
		float fWidth = static_cast<float>(_width);
		float fHeight = static_cast<float>(_height);

		float sX = (2.0f * (fX + 0.5f) / fWidth) - 1.0f;
		sX *= _fov * _aspectRatio;
		float sY = 1.0f - (2.0f * (fY + 0.5f) / fHeight);
		sY *= _fov;

		Vector3 direction = Vector3(sX, sY, -1.0f);
		direction.normalize();

		// Create the ray direction by traveling from (0,0,0) to (sX, sY, -1)
		return Ray(_position, direction);
	}

}	// Namespace