#include "SceneRegistry.hpp"

#include <iostream>
#include <SFML/System.hpp>

namespace sfew
{
	// Static data ========================================

	SceneRegistry* SceneRegistry::_instance = NULL;

	// Ctor/Dtor ========================================

	// Ctor
	SceneRegistry::SceneRegistry()
	{
		if(SceneRegistry::_instance != NULL)
		{
			std::cout << "ERROR: SceneRegistry being instantiated more than once!\n";
			std::cout << "Aborting in 11 seconds...";

			sf::sleep(sf::seconds(11.0f));

			exit(1);
		}

		// Assign the internal singleton
		SceneRegistry::_instance = this;
	}

	// Dtor
	SceneRegistry::~SceneRegistry()
	{
		// Clear the internal singleton
		SceneRegistry::_instance = NULL;
	}

	// Routines =========================================

	// Load all the resources
	bool SceneRegistry::Load()
	{
		// Assumes that the resources were successfully loaded
		_resourcesLoaded = true;

		return true;
	}

	// Unload all the resources
	void SceneRegistry::Unload()
	{


		// Mark the resources as unloaded
		_resourcesLoaded = false;
	}

	// Properties =========================================

	// STATIC: Returns a weak reference to an object by name
	/*
	std::weak_ptr<Scene> SceneRegistry::GetByName()
	{
		std::weak_ptr<Scene> empty = std::weak_ptr<Scene>();

		if(!SceneRegistry::verifyInstantiation()) return empty;

		return empty;
	}
	//*/

	// Helpers =========================================

	// Was this object instantiated?
	bool SceneRegistry::verifyInstantiation()
	{
		if(SceneRegistry::_instance == NULL)
		{
			std::cout << "ERROR: SceneRegistry not instantiated!" << std::endl;
			return false;
		}

		return true;
	}

} // namespace sfew