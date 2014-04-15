#include "Camera.hpp"

#include <iostream>
#include "Transform.hpp"	// For Transform::WorldUp()

namespace sfew
{
	// Ctor/Dtor ========================================

	// Ctor
	Camera::Camera() : INameable("Unnamed Camera"),
		_position(20.0f, 0.0f, 13.0f),
		_screenCenterPoint(0.0f, 0.0f, 13.0f),
		_upDirection(Transform::WorldUp()),
		_fov(75.0f),
		_aspectRatio(0.75f),
		_nearClip(0.5f),
		_farClip(50.0f)
	{
		
	}

	// Dtor
	Camera::~Camera()
	{

	}

	// Routines =========================================

	// Make a view matrix representing camera transform data
	Matrix4 Camera::GenerateViewMatrix() const
	{
		return glm::lookAt(_position, _screenCenterPoint, _upDirection);
	}

	// Make a projection matrix representing camera lens properties
	Matrix4 Camera::GenerateProjectionMatrix() const
	{
		return glm::perspective(_fov, _aspectRatio, _nearClip, _farClip);
	}

	// Change screen's center point
	void Camera::LookAtPoint(Vector3 newLookingPoint)
	{
		_screenCenterPoint = newLookingPoint;
	}

	// Get screen's center point
	Vector3 Camera::GetLookAtPoint() const
	{
		return _screenCenterPoint;
	}

	// Resets camera's up direction to world's
	void Camera::RealignUpDirection()
	{
		_upDirection = Transform::WorldUp();
	}

	// Properties =========================================

	void Camera::SetAspectRatio(unsigned int windowWidth, unsigned int windowHeight)
	{
		// Calculate new aspect ratio from the window size
		_aspectRatio = (float) windowWidth / (float) windowHeight;
	}
	
	void Camera::SetAspectRatio(float newAspectRatio)
	{
		// Assign aspect ratio from a precalculated aspect ratio
		_aspectRatio = newAspectRatio;
	}

	void Camera::SetPosition(Vector3 newPosition)
	{
		_position = newPosition;
	}

	void Camera::SetUpDirection(Vector3 newUpDirection)
	{
		_upDirection = newUpDirection;
	}

	Vector3 Camera::GetPosition() const
	{
		return _position;
	}

	Vector3 Camera::GetUpDirection() const
	{
		return _upDirection;
	}

	void Camera::SetFieldOfView(float newFOV)
	{
		_fov = newFOV;
	}

	float Camera::GetFieldOfView() const
	{
		return _fov;
	}

	void Camera::SetNearClippingPlane(float newNearClip)
	{
		_nearClip = newNearClip;
	}

	float Camera::GetNearClippingPlane() const
	{
		return _nearClip;
	}

	void Camera::SetFarClippingPlane(float newFarClip)
	{
		_farClip = newFarClip;
	}

	float Camera::GetFarClippingPlane() const
	{
		return _farClip;
	}

	// Helpers =========================================
}