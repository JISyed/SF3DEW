#include "Camera.hpp"

#include <iostream>
#include "Transform.hpp"	// For Transform::WorldUp()

namespace sfew
{
	// Static Data ========================================

	std::shared_ptr<Camera> Camera::_instance = std::shared_ptr<Camera>();

	// Ctor/Dtor ========================================

	// Ctor
	Camera::Camera() : INameable("Unnamed Camera"),
		_position(20.0f, 0.0f, 13.0f),
		_screenCenterPoint(0.0f, 0.0f, 13.0f),
		_upDirection(Transform::WorldUp()),
		_fov(75.0f),
		_aspectRatio(0.75f),
		_nearClip(0.5f),
		_farClip(50.0f),
		_flaggedAsViewChanged(true),
		_flaggedAsProjectionChanged(true)
	{
		
	}

	// Dtor
	Camera::~Camera()
	{
		// Clear instance pointer
		Camera::_instance = nullptr;
	}

	// Routines =========================================

	// Make a view matrix representing camera transform data
	Matrix4 Camera::GenerateViewMatrix()
	{
		return glm::lookAt(_position, _screenCenterPoint, _upDirection);
	}

	// Make a projection matrix representing camera lens properties
	Matrix4 Camera::GenerateProjectionMatrix()
	{
		return glm::perspective(_fov, _aspectRatio, _nearClip, _farClip);
	}

	// Change screen's center point
	void Camera::LookAtPoint(Vector3 newLookingPoint)
	{
		_screenCenterPoint = newLookingPoint;
		_flaggedAsViewChanged = true;
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
		_flaggedAsViewChanged = true;
	}

	// STATIC: Get Singleton
	std::weak_ptr<Camera> Camera::GetInstance()
	{
		// If doesn't exist, create one
		if(Camera::_instance.get() == nullptr)
		{
			Camera::_instance = std::shared_ptr<Camera>(new Camera());
		}

		// Return a weak pointer of the instance
		std::weak_ptr<Camera> weakPointer = Camera::_instance;
		return weakPointer;
	}

	// Properties =========================================

	void Camera::SetAspectRatio(unsigned int windowWidth, unsigned int windowHeight)
	{
		// Calculate new aspect ratio from the window size
		_aspectRatio = (float) windowWidth / (float) windowHeight;
		_flaggedAsProjectionChanged = true;
	}
	
	void Camera::SetAspectRatio(float newAspectRatio)
	{
		// Assign aspect ratio from a precalculated aspect ratio
		_aspectRatio = newAspectRatio;
		_flaggedAsProjectionChanged = true;
	}

	void Camera::SetPosition(Vector3 newPosition)
	{
		_position = newPosition;
		_flaggedAsViewChanged = true;
	}

	void Camera::SetUpDirection(Vector3 newUpDirection)
	{
		_upDirection = newUpDirection;
		_flaggedAsViewChanged = true;
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
		_flaggedAsProjectionChanged = true;
	}

	float Camera::GetFieldOfView() const
	{
		return _fov;
	}

	void Camera::SetNearClippingPlane(float newNearClip)
	{
		_nearClip = newNearClip;
		_flaggedAsProjectionChanged = true;
	}

	float Camera::GetNearClippingPlane() const
	{
		return _nearClip;
	}

	void Camera::SetFarClippingPlane(float newFarClip)
	{
		_farClip = newFarClip;
		_flaggedAsProjectionChanged = true;
	}

	float Camera::GetFarClippingPlane() const
	{
		return _farClip;
	}

	bool Camera::DidViewMatrixChange() const
	{
		return _flaggedAsViewChanged;
	}

	bool Camera::DidProjectionMatrixChange() const
	{
		return _flaggedAsProjectionChanged;
	}

	void Camera::DeclareViewMatrixAsUnchanged()
	{
		_flaggedAsViewChanged = false;
	}

	void Camera::DeclareProjectionMatrixAsUnchanged()
	{
		_flaggedAsProjectionChanged = false;
	}

	// Helpers =========================================
}