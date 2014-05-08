#include "MaterialRegistry.hpp"

#include <iostream>
#include <SFML/System.hpp>

#include "ShaderRegistry.hpp"
#include "TextureRegistry.hpp"

namespace sfew
{
	// Static data ========================================

	MaterialRegistry* MaterialRegistry::_instance = NULL;

	// Ctor/Dtor ========================================

	// Ctor
	MaterialRegistry::MaterialRegistry()
	{
		if(MaterialRegistry::_instance != NULL)
		{
			std::cout << "ERROR: MaterialRegistry being instantiated more than once!\n";
			std::cout << "Aborting in 11 seconds...";

			sf::sleep(sf::seconds(11.0f));

			exit(1);
		}

		// Assign the internal singleton
		MaterialRegistry::_instance = this;
	}

	// Dtor
	MaterialRegistry::~MaterialRegistry()
	{
		// Clear the internal singleton
		MaterialRegistry::_instance = NULL;
	}

	// Routines =========================================

	// Load all the resources
	bool MaterialRegistry::Load()
	{
		// Load a blank texture
		addMaterial("BasicShader", "Blank", "Blank");

		// Load White Patches Material
		addMaterial("BasicShader", "Patches", "WhitePatches");

		// Load Orange Patches Material
		addMaterial("BasicShader", "Patches", "OrangePatches", Vector4(1.0f, 0.5f, 0.0f, 1.0f));

		// Load Game Over Material
		addMaterial("BasicShader", "GameOver", "GameOver");

		// Assumes that the resources were successfully loaded
		_resourcesLoaded = true;

		return _resourcesLoaded;
	}

	// Unload all the resources
	void MaterialRegistry::Unload()
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
	std::weak_ptr<Material> MaterialRegistry::GetByName(const std::string& name)
	{
		// Make sure this registry exists
		std::weak_ptr<Material> empty = std::weak_ptr<Material>();
		if(!MaterialRegistry::verifyInstantiation()) return empty;
		if(MaterialRegistry::_instance->_resourceList.empty()) return empty;

		// Search through the list for an object with the same name as queried
		std::weak_ptr<Material> foundObject = std::weak_ptr<Material>();
		for(auto& resource : MaterialRegistry::_instance->_resourceList)
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
	bool MaterialRegistry::verifyInstantiation()
	{
		if(MaterialRegistry::_instance == NULL)
		{
			std::cout << "ERROR: MaterialRegistry not instantiated!" << std::endl;
			return false;
		}

		return true;
	}

	void MaterialRegistry::addMaterial(
		const std::string& shaderName, 
		const std::string& textureName, 
		const std::string name
	)
	{
		std::shared_ptr<Material> newMaterial(
			new Material(
				ShaderRegistry::GetByName(shaderName),
				TextureRegistry::GetByName(textureName)
			)
		);
		newMaterial->SetName(name);
		_resourceList.push_front(newMaterial);
	}

	void MaterialRegistry::addMaterial(
		const std::string& shaderName, 
		const std::string& textureName, 
		const std::string name, 
		Vector4 color
	)
	{
		std::shared_ptr<Material> newMaterial(
			new Material(
				ShaderRegistry::GetByName(shaderName),
				TextureRegistry::GetByName(textureName)
			)
		);
		newMaterial->SetName(name);
		_resourceList.push_front(newMaterial);
		newMaterial->SetColor(color);
	}

} // namespace sfew