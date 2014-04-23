// Audio Registry
// A registry for store all AudioSource objects
//
// Written by Jibran Syed (4-14-2014)

#ifndef SFEW_AUDIO_REGISTRY_H
#define SFEW_AUDIO_REGISTRY_H

#include "Registry.hpp"
#include "AudioSource.hpp"

namespace sfew
{
	class AudioRegistry : public Registry
	{
	public:

		// Ctor/Dtor ======================

		AudioRegistry();
		virtual ~AudioRegistry();

		// Routines =======================

		virtual bool Load();			// Load all the resources
		virtual void Unload();			// Unload all the resources
		static void StopEverything();	// Stop all AudioSources from playing

		// Properties =====================

		static std::weak_ptr<AudioSource> GetByName(const std::string& name);		// Returns a weak reference to an object by name

	private:

		// Helpers ========================

		static bool verifyInstantiation();	// Was this object instantiated?

		// Data ===========================

		static AudioRegistry* _instance;	// Internal singleton instance
		std::forward_list<std::shared_ptr<AudioSource>> _resourceList;		// List of all the resource this registry can handle
		
	};

	
} // namespace sfew

#endif