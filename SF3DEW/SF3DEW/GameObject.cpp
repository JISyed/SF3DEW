#include "GameObject.hpp"

#include <iostream>

namespace sfew
{
	// Custom shared_ptr deleter that does nothing
	struct shared_un_deleter
	{
		void operator()(void const*) const{}
	};

	// Ctor/Dtor ========================================

	// Ctor
	GameObject::GameObject() : 
		INameable("Unnamed GameObject"),
		_flaggedForDestruction(false)
	{
		// Prevent ownership of this object by the shared pointer
		_self = std::shared_ptr<GameObject>(this, shared_un_deleter() );
	}

	// Dtor
	GameObject::~GameObject()
	{
		
	}

	// Routines =========================================

	// Add a new component of the given type
	bool GameObject::AddComponent(ComponentType type)
	{
		// Check if the component type was already added
		switch (type)
		{
		case sfew::ComponentType::Audio:
			if(_audio) return false;
			break;
		case sfew::ComponentType::ObjectRenderer:
			if(_renderer) return false;
			break;
		case sfew::ComponentType::FontRenderer:
			if(_fontRenderer) return false;
			break;
		case sfew::ComponentType::Physics:
			if(_physics) return false;
			break;
		case sfew::ComponentType::Custom:
			// Cannot add custom components with this method
			return false;
			break;
		}

		// Add the specified component
		_testComponent = std::shared_ptr<Component>(new Component(std::weak_ptr<GameObject>(_self)));

		return true;
	}

	std::weak_ptr<Component> GameObject::GetTestComponent() const
	{
		return _testComponent;
	}

	// Properties =========================================

	// Helpers =========================================

} // namespace sfew