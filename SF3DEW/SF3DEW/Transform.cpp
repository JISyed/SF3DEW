#include "Transform.hpp"

#include <glm/gtx/rotate_vector.hpp>

namespace sfew
{
	// Static Data ======================================

	static Vector3 s_worldUp = Vector3(0.0f, 1.0f, 0.0f);
	static Vector3 s_worldForward = Vector3(0.0f, 0.0f, 1.0f);
	static Vector3 s_worldRight = Vector3(1.0f, 0.0f, 0.0f);

	// Ctor/Dtor ========================================

	// Ctor
	Transform::Transform() :
		_position(0.0f, 0.0f, 0.0f),
		_scale(1.0f, 1.0f, 1.0f),
		_eulerAngles(0.0f, 0.0f, 0.0f),
		_forward(0.0f, 0.0f, 1.0f),
		_up(0.0f, 1.0f, 0.0f),
		_right(1.0f, 0.0f, 0.0f)
	{

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
		// Rotate forward orientation
		_forward = glm::rotateX(_forward, relativeRotation.x);
		_forward = glm::rotateY(_forward, relativeRotation.y);
		_forward = glm::rotateZ(_forward, relativeRotation.z);
		_forward = glm::normalize(_forward);

		// Rotate up orientation
		_up = glm::rotateX(_up, relativeRotation.x);
		_up = glm::rotateY(_up, relativeRotation.y);
		_up = glm::rotateZ(_up, relativeRotation.z);
		_up = glm::normalize(_up);

		// Rotate right orientation
		_right = glm::rotateX(_right, relativeRotation.x);
		_right = glm::rotateY(_right, relativeRotation.y);
		_right = glm::rotateZ(_right, relativeRotation.z);
		_right = glm::normalize(_right);

		_eulerAngles += relativeRotation;
	}

	// Get the matrix based on transform
	Matrix4 Transform::GenerateModelMatrix() const
	{
		Matrix4 translationMatrix = glm::translate(_position);
		Matrix4 scalingMatrix = glm::scale(_scale);
		Matrix4 rotationMatrix = glm::rotate(_eulerAngles.x, 1.0f, 0.0f, 0.0f);
		rotationMatrix = glm::rotate(rotationMatrix, _eulerAngles.y, 0.0f, 1.0f, 0.0f);
		rotationMatrix = glm::rotate(rotationMatrix, _eulerAngles.z, 0.0f, 0.0f, 1.0f);

		return translationMatrix * rotationMatrix * scalingMatrix;
	}

	// Static Routines =========================================

	// Get the world's up vector
	Vector3 Transform::WorldUp()
	{
		return s_worldUp;
	}
	
	// Get the world's forward vector
	Vector3 Transform::WorldForward()
	{
		return s_worldForward;
	}
	
	// Get the world's right vector
	Vector3 Transform::WorldRight()
	{
		return s_worldRight;
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
		// Rotate forward orientation
		_forward = glm::rotateX(s_worldForward, newEulerAngles.x);
		_forward = glm::rotateY(_forward, newEulerAngles.y);
		_forward = glm::rotateZ(_forward, newEulerAngles.z);
		_forward = glm::normalize(_forward);

		// Rotate up orientation
		_up = glm::rotateX(s_worldUp, newEulerAngles.x);
		_up = glm::rotateY(_up, newEulerAngles.y);
		_up = glm::rotateZ(_up, newEulerAngles.z);
		_up = glm::normalize(_up);

		// Rotate right orientation
		_right = glm::rotateX(s_worldRight, newEulerAngles.x);
		_right = glm::rotateY(_right, newEulerAngles.y);
		_right = glm::rotateZ(_right, newEulerAngles.z);
		_right = glm::normalize(_right);

		_eulerAngles = newEulerAngles;
	}

	Vector3 Transform::Forward() const
	{
		return _forward;
	}

	Vector3 Transform::Up() const
	{
		return _up;
	}

	Vector3 Transform::Right() const
	{
		return _right;
	}


} // namespace sfew