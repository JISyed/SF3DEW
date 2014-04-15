#include "ShaderRegistry.hpp"

#include <iostream>
#include <SFML/System.hpp>

#include "MeshRegistry.hpp"

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
		// Load the Basic Shader
		std::shared_ptr<Shader> basicShader(new Shader("./Shaders/basic.vert", 
													   "./Shaders/basic.frag") );
		basicShader->SetName("BasicShader");
		_resourceList.push_front(basicShader);

		// Load the Brightness Shader
		std::shared_ptr<Shader> brightnessShader(new Shader("./Shaders/brightness.vert", 
															"./Shaders/brightness.frag") );
		brightnessShader->SetName("BrightnessShader");
		_resourceList.push_front(brightnessShader);

		// Assumes that the resources were successfully loaded
		_resourcesLoaded = true;

		return _resourcesLoaded;
	}

	// Unload all the resources
	void ShaderRegistry::Unload()
	{
		// Skip unloading of list if empty
		if(_resourceList.empty()) return;

		// Empty the list
		_resourceList.clear();

		// Mark the resources as unloaded
		_resourcesLoaded = false;
	}

	// Sends down view and projection matrix if changed
	void ShaderRegistry::UpdateCameraDataInShaders()
	{
		// Check if view or projection matrices changed
		bool viewChanged = Camera::GetInstance()._Get()->DidViewMatrixChange();
		bool projChanged = Camera::GetInstance()._Get()->DidProjectionMatrixChange();
		if(!viewChanged && !projChanged) return;

		// For all shaders...
		for(auto& shader : _resourceList)
		{
			// ... update view matrix if changed
			if(viewChanged)
			{
				shader->SetUniform("view", Camera::GetInstance()._Get()->GenerateViewMatrix() );
			}

			// ... and update projection matrix if changed
			if(projChanged)
			{
				shader->SetUniform("projection", Camera::GetInstance()._Get()->GenerateProjectionMatrix() );
			}
		}

		// Flag matrices as unchanged
		Camera::GetInstance()._Get()->DeclareViewMatrixAsUnchanged();
		Camera::GetInstance()._Get()->DeclareProjectionMatrixAsUnchanged();
	}

	// Properties =========================================

	// STATIC: Returns a weak reference to an object by name
	std::weak_ptr<Shader> ShaderRegistry::GetByName(const std::string& name)
	{
		// Make sure this registry exists
		std::weak_ptr<Shader> empty = std::weak_ptr<Shader>();
		if(!ShaderRegistry::verifyInstantiation()) return empty;
		if(ShaderRegistry::_instance->_resourceList.empty()) return empty;

		// Search through the list for an object with the same name as queried
		std::weak_ptr<Shader> foundObject = std::weak_ptr<Shader>();
		for(auto& resource : ShaderRegistry::_instance->_resourceList)
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