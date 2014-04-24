#include "PhysicsComponent.hpp"

#include <iostream>

#include "GameObject.hpp"
#include "PhysicsEntityContainer.hpp"

namespace sfew
{
	// Ctor/Dtor ========================================

	// Ctor
	PhysicsComponent::PhysicsComponent(std::weak_ptr<GameObject> owningGameObject) :
		Component(owningGameObject)
	{
		// Make physics entity with defaults
		_physicsData = std::shared_ptr<PhysicsEntity>(new PhysicsEntity(owningGameObject));
		_physicsData->SetCollisionGroup(PhysicsCollisionGroups::GroupA);

		// Make persistant, if owning GameObject is
		if(owningGameObject._Get()->IsPersistant())
		{
			_physicsData->SetPersistance(true);
		}

		// Add the entity to the PhysicsEntityContainer
		PhysicsEntityContainer::Add(_physicsData);

		// Run Start
		Start();
	}

	// Dtor
	PhysicsComponent::~PhysicsComponent()
	{
		
	}

	// Routines =========================================

	void PhysicsComponent::Start()
	{
		// Does nothing
	}
	
	void PhysicsComponent::Update()
	{
		// Does nothing
	}

	// Properties =========================================

	std::weak_ptr<PhysicsEntity> PhysicsComponent::GetPhysicsEntity() const
	{
		return _physicsData;
	}

} // namespace sfew