// Transform
// Holds position, rotation and scale data
//
// Written by Jibran Syed (4-4-2014)

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "LinearAlgebraTypes.hpp"

namespace sfew
{

	class Transform
	{
	public:

		// Ctor/Dtor ======================

		Transform();
		~Transform();

		// Routines =======================

		void Translate(Vector3 relativePosition);	// Apply relative translation
		void Scale(Vector3 relativeScaling);		// Apply relative scaling
		void Rotate(Vector3 relativeRotation);		// Apply relative rotation
		Matrix4 GenerateModelMatrix() const;		// Get the matrix based on transform

		// Static Routines ================

		static Vector3 WorldUp();			// Get the world's up vector
		static Vector3 WorldForward();		// Get the world's forward vector
		static Vector3 WorldRight();		// Get the world's right vector

		// Properties =====================

		Vector3 GetPosition() const;
		Vector3 GetScale() const;
		Vector3 GetEulerAngles() const;
		void SetPosition(Vector3 newPosition);
		void SetScale(Vector3 newScale);
		void SetEulerAngles(Vector3 newEulerAngles);
		Vector3 Forward() const;
		Vector3 Up() const;
		Vector3 Right() const;

	private:

		// Data ===========================

		Vector3 _position;			// Spacial location as a vector
		Vector3 _scale;				// Scaling as a vector
		Vector3 _eulerAngles;		// Orientation as a vector
		Vector3 _forward;			// Normalized forward direction
		Vector3 _up;				// Normalized up direction
		Vector3 _right;				// Normalized right direction

	};

} // namespace sfew

#endif