#include "PhysicsEntity.hpp"

#include <iostream>

#include "GameObject.hpp"
#include "Transform.hpp"
#include "SystemTime.hpp"

namespace sfew
{
	// Static data

	unsigned int PhysicsEntity::_idSource = 0;

	// Ctor/Dtor ========================================

	PhysicsEntity::PhysicsEntity(std::weak_ptr<GameObject> gameObject) :
		_radius(1.0f),
		_velocity(0.0f, 0.0f, 0.0f),
		_acceleration(0.0f, 0.0f, 0.0f),
		_rotationalVelocity(0.0f, 0.0f, 0.0f),
		_rotationalAcceleration(0.0f, 0.0f, 0.0f),
		_linearDrag(0.0f),
		_angularDrag(0.0f),
		_gameObject(gameObject),
		_transform(gameObject._Get()->GetTransform())
	{
		_uniqueID = _idSource++;
	}

	PhysicsEntity::~PhysicsEntity()
	{
		
	}

	// Routines =========================================

	void PhysicsEntity::Update()
	{
		// Update transform based on motion properties

		// Position integration
		Vector3 oldPosition = _transform._Get()->GetPosition();
		float dt = SystemTime::GetDeltaTime().asSeconds();
		_velocity = _velocity + (_acceleration * dt);
		Vector3 newPosition = oldPosition + (_velocity * dt);
		_transform._Get()->SetPosition(newPosition);
	}

	void PhysicsEntity::OnCollision(PhysicsCollisionGroups otherGroup, 
									std::weak_ptr<PhysicsEntity> otherEntity)
	{
		// Relay to GameObject that a collision occured
		_gameObject._Get()->OnCollision(otherGroup, otherEntity);
	}

	// Properties =========================================

	void PhysicsEntity::SetCollisionGroup(PhysicsCollisionGroups newGroup)
	{
		_collisionGroup = newGroup;
	}

	PhysicsCollisionGroups PhysicsEntity::GetCollisionGroup() const
	{
		return _collisionGroup;
	}

	std::weak_ptr<GameObject> PhysicsEntity::GetGameObject() const
	{
		return _gameObject;
	}

	std::weak_ptr<Transform> PhysicsEntity::GetTransform() const
	{
		return _transform;
	}

	unsigned int PhysicsEntity::GetID() const
	{
		return _uniqueID;
	}

	void PhysicsEntity::SetRadius(float newRadius)
	{
		_radius = newRadius;
	}

	float PhysicsEntity::GetRadius() const
	{
		return _radius;
	}

	void PhysicsEntity::SetVelocity(Vector3 newVelocity)
	{
		_velocity = newVelocity;
	}

	Vector3 PhysicsEntity::GetVelocity() const
	{
		return _velocity;
	}

	void PhysicsEntity::SetAcceleration(Vector3 newAcceleration)
	{
		_acceleration = newAcceleration;
	}

	Vector3 PhysicsEntity::GetAcceleration() const
	{
		return _acceleration;
	}

	void PhysicsEntity::SetRotationalVelocity(Vector3 newOmega)
	{
		_rotationalVelocity = newOmega;
	}

	Vector3 PhysicsEntity::GetRotationalVelocity() const
	{
		return _rotationalVelocity;
	}

	void PhysicsEntity::SetRotationalAcceleration(Vector3 newAlpha)
	{
		_rotationalAcceleration = newAlpha;
	}

	Vector3 PhysicsEntity::GetRotationalAcceleration() const
	{
		return _rotationalAcceleration;
	}

	void PhysicsEntity::SetLinearDrag(float newDrag)
	{
		_linearDrag = newDrag;
	}

	float PhysicsEntity::GetLinearDrag() const
	{
		return _linearDrag;
	}

	void PhysicsEntity::SetAngularDrag(float newDrag)
	{
		_angularDrag = newDrag;
	}

	float PhysicsEntity::GetAngularDrag() const
	{
		return _angularDrag;
	}


	// Helpers =========================================

} // namespace sfew