// Camera
// Abstraction view and projection matrix
// For now only supports perspective projection 
//
// Written by Jibran Syed (4-7-2014)

#ifndef CAMERA_H
#define CAMERA_H

#include <memory>
#include <SFML/System/NonCopyable.hpp>

#include "LinearAlgebraTypes.hpp"
#include "INameable.hpp"

class ShaderRegistry;

namespace sfew
{
	class Camera : sf::NonCopyable, public INameable
	{
	public:
		
		// Ctor/Dtor ======================
		
		Camera();
		virtual ~Camera();

		// Routines =======================

		Matrix4 GenerateViewMatrix();				// Make a view matrix representing camera transform data
		Matrix4 GenerateProjectionMatrix();			// Make a projection matrix representing camera lens properties
		void LookAtPoint(Vector3 newLookingPoint);	// Change screen's center point
		Vector3 GetLookAtPoint() const;				// Get screen's center point
		void RealignUpDirection();					// Resets camera's up direction to world's
		static std::weak_ptr<Camera> GetInstance();		// Get Singleton

		// Properties =====================

		void SetAspectRatio(unsigned int windowWidth, unsigned int windowHeight);
		void SetAspectRatio(float newAspectRatio);
		void SetPosition(Vector3 newPosition);
		void SetUpDirection(Vector3 newUpDirection);
		Vector3 GetPosition() const;
		Vector3 GetUpDirection() const;
		void SetFieldOfView(float newFOV);
		float GetFieldOfView() const;
		void SetNearClippingPlane(float newNearClip);
		float GetNearClippingPlane() const;
		void SetFarClippingPlane(float newFarClip);
		float GetFarClippingPlane() const;

		bool DidViewMatrixChange() const;
		bool DidProjectionMatrixChange() const;
		void DeclareViewMatrixAsUnchanged();
		void DeclareProjectionMatrixAsUnchanged();

	private:

		// Data ===========================

		Vector3 _position;				// World position of camera
		Vector3 _screenCenterPoint;		// World point to center on screen
		Vector3 _upDirection;			// World up direction
		float _fov;						// Vertical field of view angle (in degrees)
		float _aspectRatio;				// Width-to-height ratio of the rendering canvas
		float _nearClip;				// Near clipping plane (nearest camera can see)
		float _farClip;					// Far clipping plane (furthest camera can see)
		static std::shared_ptr<Camera> _instance;	// Singleton instance

		// Flags ==========================

		bool _flaggedAsViewChanged;			// Did properties of the view matrix change?
		bool _flaggedAsProjectionChanged;	// Did properties of the projection matrix change?

	};
	
} // namespace sfew

#endif