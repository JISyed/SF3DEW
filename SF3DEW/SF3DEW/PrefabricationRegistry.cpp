#include "PrefabricationRegistry.hpp"

#include <iostream>
#include <SFML/System.hpp>

namespace sfew
{
	// Static data ========================================

	PrefabricationRegistry* PrefabricationRegistry::_instance = NULL;

	// Ctor/Dtor ========================================

	// Ctor
	PrefabricationRegistry::PrefabricationRegistry()
	{
		if(PrefabricationRegistry::_instance != NULL)
		{
			std::cout << "ERROR: PrefabricationRegistry being instantiated more than once!\n";
			std::cout << "Aborting in 11 seconds...";

			sf::sleep(sf::seconds(11.0f));

			exit(1);
		}

		// Assign the internal singleton
		PrefabricationRegistry::_instance = this;
	}

	// Dtor
	PrefabricationRegistry::~PrefabricationRegistry()
	{
		// Clear the internal singleton
		PrefabricationRegistry::_instance = NULL;
	}

	// Routines =========================================

	// Load all the resources
	bool PrefabricationRegistry::Load()
	{
		// Assumes that the resources were successfully loaded
		_resourcesLoaded = true;

		return true;
	}

	// Unload all the resources
	void PrefabricationRegistry::Unload()
	{


		// Mark the resources as unloaded
		_resourcesLoaded = false;
	}

	// Properties =========================================

	// STATIC: Returns a weak reference to an object by name
	/*
	std::weak_ptr<Prefabrication> PrefabricationRegistry::GetByName()
	{
		std::weak_ptr<Prefabrication> empty = std::weak_ptr<Prefabrication>();

		if(!PrefabricationRegistry::verifyInstantiation()) return empty;

		return empty;
	}
	//*/

	// Helpers =========================================

	// Was this object instantiated?
	bool PrefabricationRegistry::verifyInstantiation()
	{
		if(PrefabricationRegistry::_instance == NULL)
		{
			std::cout << "ERROR: PrefabricationRegistry not instantiated!" << std::endl;
			return false;
		}

		return true;
	}

} // namespace sfew