#include "FontRendererComponent.hpp"

#include <iostream>

#include "GameObject.hpp"

namespace sfew
{
	// Ctor/Dtor ========================================

	FontRendererComponent::FontRendererComponent(std::weak_ptr<GameObject> owningGameObject) :
		Component(owningGameObject)
	{
		
	}

	FontRendererComponent::~FontRendererComponent()
	{
		
	}

	// Routines =========================================

	void FontRendererComponent::Start()
	{

	}

	void FontRendererComponent::Update()
	{

	}

	// Properties =========================================

	ComponentType FontRendererComponent::GetType() const
	{
		return ComponentType::FontRenderer;
	}

	// Helpers =========================================

} // namespace sfew