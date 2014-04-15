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
		// Load a blank texture
		std::shared_ptr<Texture> blankTexture(new Texture());
		blankTexture->SetName("Blank");
		_resourceList.push_front(blankTexture);

		// Load the Patches Texture
		std::shared_ptr<Texture> patchesTexture(new Texture("./Textures/texPatches.png"));
		patchesTexture->SetName("Patches");
		_resourceList.push_front(patchesTexture);

		// Load the Game Over Texture
		std::shared_ptr<Texture> gameOverTexture(new Texture("./Textures/texGameOver.png"));
		gameOverTexture->SetName("GameOver");
		_resourceList.push_front(gameOverTexture);

		// Assumes that the resources were successfully loaded
		_resourcesLoaded = true;

		return _resourcesLoaded;
	}

	// Unload all the resources
	void TextureRegistry::Unload()
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
	std::weak_ptr<Texture> TextureRegistry::GetByName(const std::string& name)
	{
		// Make sure this registry exists
		std::weak_ptr<Texture> empty = std::weak_ptr<Texture>();
		if(!TextureRegistry::verifyInstantiation()) return empty;
		if(TextureRegistry::_instance->_resourceList.empty()) return empty;

		// Search through the list for an object with the same name as queried
		std::weak_ptr<Texture> foundObject = std::weak_ptr<Texture>();
		for(auto& resource : TextureRegistry::_instance->_resourceList)
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