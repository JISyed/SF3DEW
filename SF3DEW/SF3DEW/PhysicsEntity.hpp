// Physics Entity
// Handles simple physics movement and sphere colliders
//
// Written by Jibran Syed (4-18-2014)

#ifndef SFEW_PHYSICS_ENTITY_H
#define SFEW_PHYSICS_ENTITY_H

#include <memory>

#include "LinearAlgebraTypes.hpp"

namespace sfew
{
	// GameObject and Transform forward declare
	class GameObject;
	class Transform;

	// Enumeration for different generic collision groups
	// These groups are defined how ever you want.
	// Define the types of objects that belong in these groups.
	enum PhysicsCollisionGroups
	{
		GroupA,		// Define the type of object that belong in this group
		GroupB,		// Define the type of object that belong in this group
		GroupC,		// Define the type of object that belong in this group
		GroupD,		// Define the type of object that belong in this group
		GroupE,		// Define the type of object that belong in this group
		GroupF,		// Define the type of object that belong in this group
		GroupG,		// Define the type of object that belong in this group
		GroupH		// Define the type of object that belong in this group
	};

	class PhysicsEntity
	{
	public:

		// Ctor/Dtor ======================

		PhysicsEntity(std::weak_ptr<GameObject> gameObject);
		~PhysicsEntity();

		// Routines =======================

		void Update();
		void OnCollision(PhysicsCollisionGroups otherGroup, 
						 std::weak_ptr<PhysicsEntity> otherEntity);


		// Properties =====================

		void SetCollisionGroup(PhysicsCollisionGroups newGroup);
		PhysicsCollisionGroups GetCollisionGroup() const;
		std::weak_ptr<GameObject> GetGameObject() const;
		std::weak_ptr<Transform> GetTransform() const;
		unsigned int GetID() const;
		void SetRadius(float newRadius);
		float GetRadius() const;
		void SetVelocity(Vector3 newVelocity);
		Vector3 GetVelocity() const;
		void SetAcceleration(Vector3 newAcceleration);
		Vector3 GetAcceleration() const;
		void SetRotationalVelocity(Vector3 newOmega);
		Vector3 GetRotationalVelocity() const;
		void SetRotationalAcceleration(Vector3 newAlpha);
		Vector3 GetRotationalAcceleration() const;
		void SetLinearDrag(float newDrag);
		float GetLinearDrag() const;
		void SetAngularDrag(float newDrag);
		float GetAngularDrag() const;
		void SetPersistance(bool willBePersistant);
		bool IsPersistant() const;

	private:

		// Data ===========================

		PhysicsCollisionGroups _collisionGroup;	// The entity's collision group
		std::weak_ptr<GameObject> _gameObject;	// Owner GameObject
		std::weak_ptr<Transform> _transform;	// Owner Transform
		unsigned int _uniqueID;					// Identify the entity with a number
		float _radius;							// Radius of the collision sphere
		Vector3 _velocity;						// Change in position of entity
		Vector3 _acceleration;					// Change in velocity of entity
		Vector3 _rotationalVelocity;			// Change in angular orientation
		Vector3 _rotationalAcceleration;		// Change in rotational velocity
		float _linearDrag;						// Friction against linear motion
		float _angularDrag;						// Friction against angular motion
		bool _isPersistant;						// Will object persist between scene loads?

		// Static Data ====================

		static unsigned int _idSource;			// Where IDs get generated from

	};

	
} // namespace sfew

#endif