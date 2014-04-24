#include "AudioComponent.hpp"

#include <iostream>

#include "GameObject.hpp"
#include "AudioRegistry.hpp"

namespace sfew
{
	// Ctor/Dtor ========================================

	// Ctor
	AudioComponent::AudioComponent(std::weak_ptr<GameObject> owningGameObject) :
		Component(owningGameObject)
	{
		// Set up defaults
		_audioSource = AudioRegistry::GetByName("ItemGetSnd");

		// Run start
		Start();
	}

	// Dtor
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

	std::weak_ptr<AudioSource> AudioComponent::GetAudioSource() const
	{
		return _audioSource;
	}

	void AudioComponent::SetAudioSource(std::weak_ptr<AudioSource> newAudioSource)
	{
		_audioSource = newAudioSource;
	}

} // namespace sfew