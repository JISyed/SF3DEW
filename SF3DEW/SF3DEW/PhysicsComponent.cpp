#include "PhysicsComponent.hpp"

#include <iostream>

#include "GameObject.hpp"
#include "PhysicsEntityContainer.hpp"

namespace sfew
{
	// Ctor/Dtor ========================================

	PhysicsComponent::PhysicsComponent(std::weak_ptr<GameObject> owningGameObject) :
		Component(owningGameObject)
	{
		// Make physics entity with defaults
		_physicsData = std::shared_ptr<PhysicsEntity>(new PhysicsEntity());

		// Add the entity to the PhysicsEntityContainer
		PhysicsEntityContainer::Add(_physicsData);

		// Run Start
		Start();
	}

	PhysicsComponent::~PhysicsComponent()
	{
		
	}

	// Routines =========================================

	void PhysicsComponent::Start()
	{

	}
	
	void PhysicsComponent::Update()
	{
		
	}

	// Properties =========================================

	ComponentType PhysicsComponent::GetType() const
	{
		return ComponentType::Physics;
	}

	// Helpers =========================================

} // namespace sfew