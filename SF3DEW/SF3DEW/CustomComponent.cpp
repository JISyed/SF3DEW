#include "CustomComponent.hpp"

#include <iostream>

#include "GameObject.hpp"

namespace sfew
{
	// Ctor/Dtor ========================================

	// Ctor
	CustomComponent::CustomComponent(std::weak_ptr<GameObject> owningGameObject) :
		Component(owningGameObject)
	{
		
	}

	// Dtor
	CustomComponent::~CustomComponent()
	{
		
	}

} // namespace sfew