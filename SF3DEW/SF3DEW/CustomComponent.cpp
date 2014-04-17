#include "CustomComponent.hpp"

#include <iostream>

#include "GameObject.hpp"

namespace sfew
{
	// Ctor/Dtor ========================================

	CustomComponent::CustomComponent(std::weak_ptr<GameObject> owningGameObject) : 
		INameable("Unnamed Custom Component"),
		Component(owningGameObject)
	{
		
	}

	CustomComponent::~CustomComponent()
	{
		
	}

	// Routines =========================================

	// Properties =========================================

	ComponentType CustomComponent::GetType() const
	{
		return ComponentType::Custom;
	}

	// Helpers =========================================

} // namespace sfew