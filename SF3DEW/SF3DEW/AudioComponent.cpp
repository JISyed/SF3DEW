#include "AudioComponent.hpp"

#include <iostream>

#include "GameObject.hpp"

namespace sfew
{
	// Ctor/Dtor ========================================

	AudioComponent::AudioComponent(std::weak_ptr<GameObject> owningGameObject) :
		Component(owningGameObject)
	{
		
	}

	AudioComponent::~AudioComponent()
	{
		
	}

	// Routines =========================================

	// Properties =========================================

	ComponentType AudioComponent::GetType() const
	{
		return ComponentType::Audio;
	}

	// Helpers =========================================

} // namespace sfew