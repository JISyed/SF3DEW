#include "Component.hpp"

#include <iostream>

#include "GameObject.hpp"

namespace sfew
{
	// Ctor/Dtor ========================================

	// Ctor
	Component::Component(std::weak_ptr<GameObject> owningGameObject) : 
		_gameObject(owningGameObject)
	{
		
	}

	// Dtor
	Component::~Component()
	{
		
	}

	// Routines =========================================

	// Properties =========================================

	std::weak_ptr<GameObject> Component::GetGameObject() const
	{
		return _gameObject;
	}

	ComponentType Component::GetType() const
	{
		return ComponentType::Invalid;
	}

	// Helpers =========================================

} // namespace sfew