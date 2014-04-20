#include "PhysicsEntity.hpp"

#include <iostream>

#include "GameObject.hpp"

namespace sfew
{
	// Ctor/Dtor ========================================

	PhysicsEntity::PhysicsEntity(std::weak_ptr<GameObject> gameObject)
	{
		
	}

	PhysicsEntity::~PhysicsEntity()
	{
		
	}

	// Routines =========================================

	void PhysicsEntity::Update()
	{

	}

	void PhysicsEntity::OnCollision(PhysicsCollisionGroups otherGroup, 
									std::weak_ptr<PhysicsEntity> otherEntity)
	{
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

	// Helpers =========================================

} // namespace sfew