#include "TextureRegistry.hpp"

#include <iostream>
#include <SFML/System.hpp>

namespace sfew
{
	// Static data ========================================

	TextureRegistry* TextureRegistry::_instance = NULL;

	// Ctor/Dtor ========================================

	// Ctor
	TextureRegistry::TextureRegistry()
	{
		if(TextureRegistry::_instance != NULL)
		{
			std::cout << "ERROR: TextureRegistry being instantiated more than once!\n";
			std::cout << "Aborting in 11 seconds...";

			sf::sleep(sf::seconds(11.0f));

			exit(1);
		}

		// Assign the internal singleton
		TextureRegistry::_instance = this;
	}

	// Dtor
	TextureRegistry::~TextureRegistry()
	{
		// Clear the internal singleton
		TextureRegistry::_instance = NULL;
	}

	// Routines =========================================

	// Load all the resources
	bool TextureRegistry::Load()
	{
		// Assumes that the resources were successfully loaded
		_resourcesLoaded = true;

		return true;
	}

	// Unload all the resources
	void TextureRegistry::Unload()
	{


		// Mark the resources as unloaded
		_resourcesLoaded = false;
	}

	// Properties =========================================

	// STATIC: Returns a weak reference to an object by name
	std::weak_ptr<Texture> TextureRegistry::GetByName(const std::string& name)
	{
		std::weak_ptr<Texture> empty = std::weak_ptr<Texture>();

		if(!TextureRegistry::verifyInstantiation()) return empty;

		return empty;
	}

	// Helpers =========================================

	// STATIC: Was this object instantiated?
	bool TextureRegistry::verifyInstantiation()
	{
		if(TextureRegistry::_instance == NULL)
		{
			std::cout << "ERROR: TextureRegistry not instantiated!" << std::endl;
			return false;
		}

		return true;
	}

} // namespace sfew