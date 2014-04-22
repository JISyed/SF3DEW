#include "CustomComponent.hpp"

#include <iostream>

#include "GameObject.hpp"

namespace sfew
{
	// Ctor/Dtor ========================================

	CustomComponent::CustomComponent(std::weak_ptr<GameObject> owningGameObject) :
		Component(owningGameObject)
	{
		
	}

	CustomComponent::~CustomComponent()
	{
		
	}

	// Routines =========================================


	// Properties =========================================


	// Helpers =========================================

} // namespace sfew