#include "AudioRegistry.hpp"

#include <iostream>
#include <SFML/System.hpp>

namespace sfew
{
	// Static data ========================================

	AudioRegistry* AudioRegistry::_instance = NULL;

	// Ctor/Dtor ========================================

	// Ctor
	AudioRegistry::AudioRegistry()
	{
		if(AudioRegistry::_instance != NULL)
		{
			std::cout << "ERROR: AudioRegistry being instantiated more than once!\n";
			std::cout << "Aborting in 11 seconds...";

			sf::sleep(sf::seconds(11.0f));

			exit(1);
		}

		// Assign the internal singleton
		AudioRegistry::_instance = this;
	}

	// Dtor
	AudioRegistry::~AudioRegistry()
	{
		// Clear the internal singleton
		AudioRegistry::_instance = NULL;
	}

	// Routines =========================================

	// Load all the resources
	bool AudioRegistry::Load()
	{
		// Assumes that the resources were successfully loaded
		_resourcesLoaded = true;

		return true;
	}

	// Unload all the resources
	void AudioRegistry::Unload()
	{


		// Mark the resources as unloaded
		_resourcesLoaded = false;
	}

	// Properties =========================================

	// STATIC: Returns a weak reference to an object by name
	std::weak_ptr<AudioSource> AudioRegistry::GetByName()
	{
		std::weak_ptr<AudioSource> empty = std::weak_ptr<AudioSource>();

		if(!AudioRegistry::verifyInstantiation()) return empty;

		return empty;
	}

	// Helpers =========================================

	// Was this object instantiated?
	bool AudioRegistry::verifyInstantiation()
	{
		if(AudioRegistry::_instance == NULL)
		{
			std::cout << "ERROR: AudioRegistry not instantiated!" << std::endl;
			return false;
		}

		return true;
	}

} // namespace sfew