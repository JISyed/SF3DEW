#include "ShaderRegistry.hpp"

#include <iostream>
#include <SFML/System.hpp>

namespace sfew
{
	// Static data ========================================

	ShaderRegistry* ShaderRegistry::_instance = NULL;

	// Ctor/Dtor ========================================

	// Ctor
	ShaderRegistry::ShaderRegistry()
	{
		if(ShaderRegistry::_instance != NULL)
		{
			std::cout << "ERROR: ShaderRegistry being instantiated more than once!\n";
			std::cout << "Aborting in 11 seconds...";

			sf::sleep(sf::seconds(11.0f));

			exit(1);
		}

		// Assign the internal singleton
		ShaderRegistry::_instance = this;
	}

	// Dtor
	ShaderRegistry::~ShaderRegistry()
	{
		// Clear the internal singleton
		ShaderRegistry::_instance = NULL;
	}

	// Routines =========================================

	// Load all the resources
	bool ShaderRegistry::Load()
	{
		// Assumes that the resources were successfully loaded
		_resourcesLoaded = true;

		return true;
	}

	// Unload all the resources
	void ShaderRegistry::Unload()
	{


		// Mark the resources as unloaded
		_resourcesLoaded = false;
	}

	// Properties =========================================

	// STATIC: Returns a weak reference to an object by name
	std::weak_ptr<Shader> ShaderRegistry::GetByName()
	{
		std::weak_ptr<Shader> empty = std::weak_ptr<Shader>();

		if(!ShaderRegistry::verifyInstantiation()) return empty;

		return empty;
	}

	// Helpers =========================================

	// Was this object instantiated?
	bool ShaderRegistry::verifyInstantiation()
	{
		if(ShaderRegistry::_instance == NULL)
		{
			std::cout << "ERROR: ShaderRegistry not instantiated!" << std::endl;
			return false;
		}

		return true;
	}

} // namespace sfew