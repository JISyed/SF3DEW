// Audio Component
// Responsible for playing from an AudioSource
//
// Written by Jibran Syed (4-16-2014)

#ifndef SFEW_AUDIO_COMPONENT_H
#define SFEW_AUDIO_COMPONENT_H

#include <memory>

#include "Component.hpp"

namespace sfew
{
	class AudioComponent : public Component
	{
	public:

		// Ctor/Dtor ======================

		AudioComponent(std::weak_ptr<GameObject> owningGameObject);
		virtual ~AudioComponent();

		// Routines =======================

		

		// Properties =====================

		virtual ComponentType GetType() const;

	private:

		// Helpers ========================

		

		// Data ===========================


		
	};

	
} // namespace sfew

#endif