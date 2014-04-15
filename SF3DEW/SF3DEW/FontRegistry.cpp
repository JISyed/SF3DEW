#include "FontRegistry.hpp"

#include <iostream>
#include <SFML/System.hpp>

namespace sfew
{
	// Static data ========================================

	FontRegistry* FontRegistry::_instance = NULL;

	// Ctor/Dtor ========================================

	// Ctor
	FontRegistry::FontRegistry()
	{
		if(FontRegistry::_instance != NULL)
		{
			std::cout << "ERROR: FontRegistry being instantiated more than once!\n";
			std::cout << "Aborting in 11 seconds...";

			sf::sleep(sf::seconds(11.0f));

			exit(1);
		}

		// Assign the internal singleton
		FontRegistry::_instance = this;
	}

	// Dtor
	FontRegistry::~FontRegistry()
	{
		// Clear the internal singleton
		FontRegistry::_instance = NULL;
	}

	// Routines =========================================

	// Load all the resources
	bool FontRegistry::Load()
	{
		// Assumes that the resources were successfully loaded
		_resourcesLoaded = true;

		return true;
	}

	// Unload all the resources
	void FontRegistry::Unload()
	{


		// Mark the resources as unloaded
		_resourcesLoaded = false;
	}

	// Properties =========================================

	// STATIC: Returns a weak reference to an object by name
	std::weak_ptr<sf::Font> FontRegistry::GetByName()
	{
		std::weak_ptr<sf::Font> empty = std::weak_ptr<sf::Font>();

		if(!FontRegistry::verifyInstantiation()) return empty;

		return empty;
	}

	// Helpers =========================================

	// Was this object instantiated?
	bool FontRegistry::verifyInstantiation()
	{
		if(FontRegistry::_instance == NULL)
		{
			std::cout << "ERROR: FontRegistry not instantiated!" << std::endl;
			return false;
		}

		return true;
	}

} // namespace sfew