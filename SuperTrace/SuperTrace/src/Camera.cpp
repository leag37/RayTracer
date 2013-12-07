//*************************************************************************************************
// Title: Camera.cpp
// Author: Gael Huber
// Description: A camera in the world.
//*************************************************************************************************
#include "Camera.h"
#include "STMath.h"

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

		// First map fX and fY from raster space to NDC space
		float sX = (fX + 0.5f) / fWidth;
		float sY = (fY + 0.5f) / fHeight;

		// Next, map from NDC to screen space
		sX = (2.0f * sX) - 1.0f;
		sY = 1.0f - (2.0f * sY);

		// Apply aspect ratio to X coordinate
		sX *= _aspectRatio;

		// TEST - y aspect ratio
		// As y deviates from the center line, scale it by a fraction of the inverse aspect ratio
		//float invAspect = 1.0f / _aspectRatio;
		//sY *= invAspect;
		// END TEST

		// Multiply by field of view
		sX *= _fov;
		sY *= _fov;

		// Now we can get the position of the point in camera space as (sX, sY, -1)
		Vector3 pCamera = Vector3(sX, sY, -1.0f);
		Vector3 rayDirection = pCamera - _position;
		
		// Build the perspective matrix
		float f = 1.0f / _fov;
		float near = 1.0f;
		float far = 1000.0f;
		Matrix44 persp = Matrix44(
			f, 0.0f, 0.0f, 0.0f,
			0.0f, f, 0.0f, 0.0f,
			0.0f, 0.0f, far/(far-near), 1.0f,
			0.0f, 0.0f, -(far*near)/(far-near), 0.0f);
		Vector3 temp = rayDirection;
		rayDirection = Vector3Transform(rayDirection, persp);
		
		rayDirection.normalize();

		return Ray(_position, rayDirection);
	}

}	// Namespace