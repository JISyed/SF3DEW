#include "ObjectRendererComponent.hpp"

#include <iostream>

#include "GameObject.hpp"

namespace sfew
{
	// Ctor/Dtor ========================================

	ObjectRendererComponent::ObjectRendererComponent(std::weak_ptr<GameObject> owningGameObject) :
		Component(owningGameObject)
	{
		Start();
	}

	ObjectRendererComponent::~ObjectRendererComponent()
	{
		
	}

	// Routines =========================================

	void ObjectRendererComponent::Start()
	{

	}

	void ObjectRendererComponent::Update()
	{

	}

	// Properties =========================================

	ComponentType ObjectRendererComponent::GetType() const
	{
		return ComponentType::ObjectRenderer;
	}

	// Helpers =========================================

} // namespace sfew