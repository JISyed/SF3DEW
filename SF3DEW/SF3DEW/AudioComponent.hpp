// Audio Component
// Responsible for playing from an AudioSource
//
// Written by Jibran Syed (4-16-2014)

#ifndef SFEW_AUDIO_COMPONENT_H
#define SFEW_AUDIO_COMPONENT_H

#include <memory>

#include "Component.hpp"
#include "AudioSource.hpp"

namespace sfew
{
	class AudioComponent : public Component
	{
	public:

		// Ctor/Dtor ======================

		AudioComponent(std::weak_ptr<GameObject> owningGameObject);
		virtual ~AudioComponent();

		// Routines =======================

		virtual void Start();
		virtual void Update();

		// Properties =====================

		std::weak_ptr<AudioSource> GetAudioSource() const;
		void SetAudioSource(std::weak_ptr<AudioSource> newAudioSource);

	private:

		// Data ===========================

		std::weak_ptr<AudioSource> _audioSource;	// The audio source
		
	};

	
} // namespace sfew

#endif