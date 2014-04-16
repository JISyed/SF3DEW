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
		// Load the Player Laser Sound
		std::shared_ptr<Font> marsFont(new Font("./Fonts/Mars_1_0_0_6.otf") );
		marsFont->SetName("Mars");
		_resourceList.push_front(marsFont);

		// Assumes that the resources were successfully loaded
		_resourcesLoaded = true;

		return _resourcesLoaded;
	}

	// Unload all the resources
	void FontRegistry::Unload()
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
	std::weak_ptr<Font> FontRegistry::GetByName(const std::string& name)
	{
		// Make sure this registry exists
		std::weak_ptr<Font> empty = std::weak_ptr<Font>();
		if(!FontRegistry::verifyInstantiation()) return empty;
		if(FontRegistry::_instance->_resourceList.empty()) return empty;

		// Search through the list for an object with the same name as queried
		std::weak_ptr<Font> foundObject = std::weak_ptr<Font>();
		for(auto& resource : FontRegistry::_instance->_resourceList)
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