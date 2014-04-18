#include "AudioComponent.hpp"

#include <iostream>

#include "GameObject.hpp"
#include "AudioRegistry.hpp"

namespace sfew
{
	// Ctor/Dtor ========================================

	AudioComponent::AudioComponent(std::weak_ptr<GameObject> owningGameObject) :
		Component(owningGameObject)
	{
		// Set up defaults
		_audioSource = AudioRegistry::GetByName("ItemGetSnd");

		// Run start
		Start();
	}

	AudioComponent::~AudioComponent()
	{
		
	}

	// Routines =========================================

	void AudioComponent::Start()
	{
		// Does nothing
	}

	void AudioComponent::Update()
	{
		// Does nothing
	}

	// Properties =========================================

	ComponentType AudioComponent::GetType() const
	{
		return ComponentType::Audio;
	}

	std::weak_ptr<AudioSource> AudioComponent::GetAudioSource() const
	{
		return _audioSource;
	}

	void AudioComponent::GetAudioSource(std::weak_ptr<AudioSource> newAudioSource)
	{
		_audioSource = newAudioSource;
	}

	// Helpers =========================================

} // namespace sfew