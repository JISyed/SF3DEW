#include "PhysicsComponent.hpp"

#include <iostream>

#include "GameObject.hpp"

namespace sfew
{
	// Ctor/Dtor ========================================

	PhysicsComponent::PhysicsComponent()
	{
		
	}

	PhysicsComponent::~PhysicsComponent()
	{
		
	}

	// Routines =========================================

	// Properties =========================================

	ComponentType PhysicsComponent::GetType() const
	{
		return ComponentType::Physics;
	}

	// Helpers =========================================

} // namespace sfew