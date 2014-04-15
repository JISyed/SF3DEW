#include "MeshRegistry.hpp"

#include <iostream>
#include <SFML/System.hpp>

namespace sfew
{
	// Static data ========================================

	MeshRegistry* MeshRegistry::_instance = NULL;

	// Ctor/Dtor ========================================

	// Ctor
	MeshRegistry::MeshRegistry()
	{
		if(MeshRegistry::_instance != NULL)
		{
			std::cout << "ERROR: MeshRegistry being instantiated more than once!\n";
			std::cout << "Aborting in 11 seconds...";

			sf::sleep(sf::seconds(11.0f));

			exit(1);
		}

		// Assign the internal singleton
		MeshRegistry::_instance = this;
	}

	// Dtor
	MeshRegistry::~MeshRegistry()
	{
		// Clear the internal singleton
		MeshRegistry::_instance = NULL;
	}

	// Routines =========================================

	// Load all the resources
	bool MeshRegistry::Load()
	{
		// Assumes that the resources were successfully loaded
		_resourcesLoaded = true;

		return true;
	}

	// Unload all the resources
	void MeshRegistry::Unload()
	{


		// Mark the resources as unloaded
		_resourcesLoaded = false;
	}

	// Properties =========================================

	// STATIC: Returns a weak reference to an object by name
	std::weak_ptr<Mesh> MeshRegistry::GetByName()
	{
		std::weak_ptr<Mesh> empty = std::weak_ptr<Mesh>();

		if(!MeshRegistry::verifyInstantiation()) return empty;

		return empty;
	}

	// Helpers =========================================

	// Was this object instantiated?
	bool MeshRegistry::verifyInstantiation()
	{
		if(MeshRegistry::_instance == NULL)
		{
			std::cout << "ERROR: MeshRegistry not instantiated!" << std::endl;
			return false;
		}

		return true;
	}

} // namespace sfew