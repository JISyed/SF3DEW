#include "PhysicsComponent.hpp"

#include <iostream>

#include "GameObject.hpp"

namespace sfew
{
	// Ctor/Dtor ========================================

	PhysicsComponent::PhysicsComponent(std::weak_ptr<GameObject> owningGameObject) :
		Component(owningGameObject)
	{
		
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