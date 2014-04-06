#include "Transform.hpp"

namespace sfew
{
	// Ctor/Dtor ========================================

	// Ctor
	Transform::Transform()
	{
		_position = Vector3(0.0f, 0.0f, 0.0f);
		_scale = Vector3(1.0f, 1.0f, 1.0f);
		_eulerAngles = Vector3(0.0f, 0.0f, 0.0f);
	}

	// Dtor
	Transform::~Transform()
	{

	}

	// Routines =========================================

	// Apply relative translation
	void Transform::Translate(Vector3 relativePosition)
	{
		_position += relativePosition;
	}

	// Apply relative scaling
	void Transform::Scale(Vector3 relativeScaling)
	{
		_scale += relativeScaling;
	}

	// Apply relative rotation
	void Transform::Rotate(Vector3 relativeRotation)
	{
		_eulerAngles += relativeRotation;
	}

	// Static Routines =========================================

	// Get the world's up vector
	Vector3 Transform::WorldUp()
	{
		return Vector3(0.0f, 1.0f, 0.0f);
	}
	
	// Get the world's forward vector
	Vector3 Transform::WorldForward()
	{
		return Vector3(0.0f, 0.0f, 1.0f);
	}
	
	// Get the world's right vector
	Vector3 Transform::WorldRight()
	{
		return Vector3(1.0f, 0.0f, 0.0f);
	}

	// Properties =========================================

	Vector3 Transform::GetPosition() const
	{
		return _position;
	}

	Vector3 Transform::GetScale() const
	{
		return _scale;
	}

	Vector3 Transform::GetEulerAngles() const
	{
		return _eulerAngles;
	}

	void Transform::SetPosition(Vector3 newPosition)
	{
		_position = newPosition;
	}

	void Transform::SetScale(Vector3 newScale)
	{
		_scale = newScale;
	}

	void Transform::SetEulerAngles(Vector3 newEulerAngles)
	{
		_eulerAngles = newEulerAngles;
	}


} // namespace sfew