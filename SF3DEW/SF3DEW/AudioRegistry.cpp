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
		// Load the Player Laser Sound
		std::shared_ptr<AudioSource> playerLaserSound(new AudioSource("./Audio/sndPlayerLaser.wav", AudioType::Sound) );
		playerLaserSound->SetName("PlayerLaserSnd");
		_resourceList.push_front(playerLaserSound);

		// Load the Item Get Sound
		std::shared_ptr<AudioSource> itemGetSound(new AudioSource("./Audio/sndItemGet.wav", AudioType::Sound) );
		itemGetSound->SetName("ItemGetSnd");
		_resourceList.push_front(itemGetSound);

		// Load the Rolling Music
		std::shared_ptr<AudioSource> rollingMus(new AudioSource("./Audio/rolling_by_madgarden.ogg", AudioType::Music) );
		rollingMus->SetName("RollingMus");
		_resourceList.push_front(rollingMus);

		// Assumes that the resources were successfully loaded
		_resourcesLoaded = true;

		return _resourcesLoaded;
	}

	// Unload all the resources
	void AudioRegistry::Unload()
	{
		// Mark the resources as unloaded
		_resourcesLoaded = false;

		// Skip unloading of list if empty
		if(_resourceList.empty()) return;

		// Stop all AudioSources
		for(auto& audio : AudioRegistry::_instance->_resourceList)
		{
			audio->Stop();
		}

		// Empty the list
		_resourceList.clear();
	}

	// STATIC: Stop all AudioSources from playing
	void AudioRegistry::StopEverything()
	{
		// Make sure this exists and is not empty
		if(!AudioRegistry::verifyInstantiation()) return;
		if(AudioRegistry::_instance->_resourceList.empty()) return;

		// Stop all AudioSources if interuptable
		for(auto& audio : AudioRegistry::_instance->_resourceList)
		{
			if(audio->IsInteruptable())
			{
				audio->Stop();
			}
		}
	}

	// Properties =========================================

	// STATIC: Returns a weak reference to an object by name
	std::weak_ptr<AudioSource> AudioRegistry::GetByName(const std::string& name)
	{
		// Make sure this registry exists
		std::weak_ptr<AudioSource> empty = std::weak_ptr<AudioSource>();
		if(!AudioRegistry::verifyInstantiation()) return empty;
		if(AudioRegistry::_instance->_resourceList.empty()) return empty;

		// Search through the list for an object with the same name as queried
		std::weak_ptr<AudioSource> foundObject = std::weak_ptr<AudioSource>();
		for(auto& resource : AudioRegistry::_instance->_resourceList)
		{
			// Are the two name string the same?
			if(resource->GetName().compare(name) == 0)
			{
				foundObject = resource;
				return foundObject;
			}
		}

		// Couldn't find the queried name
		return empty;
	}

	// Helpers =========================================

	// STATIC: Was this object instantiated?
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