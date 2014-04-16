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
		// Skip unloading of list if empty
		if(_resourceList.empty()) return;

		// Empty the list
		_resourceList.clear();

		// Mark the resources as unloaded
		_resourcesLoaded = false;
	}

	// Properties =========================================

	// STATIC: Returns a weak reference to an object by name
	std::weak_ptr<Prefabrication> PrefabricationRegistry::GetByName(const std::string& name)
	{
		// Make sure this registry exists
		std::weak_ptr<Prefabrication> empty = std::weak_ptr<Prefabrication>();
		if(!PrefabricationRegistry::verifyInstantiation()) return empty;
		if(PrefabricationRegistry::_instance->_resourceList.empty()) return empty;

		// Search through the list for an object with the same name as queried
		std::weak_ptr<Prefabrication> foundObject = std::weak_ptr<Prefabrication>();
		for(auto& resource : PrefabricationRegistry::_instance->_resourceList)
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