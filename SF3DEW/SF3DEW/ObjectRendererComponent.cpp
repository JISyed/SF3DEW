#include "ObjectRendererComponent.hpp"

#include <iostream>

#include "GameObject.hpp"

namespace sfew
{
	// Ctor/Dtor ========================================

	ObjectRendererComponent::ObjectRendererComponent(std::weak_ptr<GameObject> owningGameObject) :
		Component(owningGameObject)
	{
		
	}

	ObjectRendererComponent::~ObjectRendererComponent()
	{
		
	}

	// Routines =========================================

	// Properties =========================================

	ComponentType ObjectRendererComponent::GetType() const
	{
		return ComponentType::ObjectRenderer;
	}

	// Helpers =========================================

} // namespace sfew