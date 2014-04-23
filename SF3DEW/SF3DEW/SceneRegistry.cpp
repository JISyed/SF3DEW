#include "SceneRegistry.hpp"

#include <iostream>
#include <SFML/System.hpp>

namespace sfew
{
	// Static data ========================================

	SceneRegistry* SceneRegistry::_instance = NULL;

	// Ctor/Dtor ========================================

	// Ctor
	SceneRegistry::SceneRegistry() :
		_sceneLoadingRequested(false),
		_loadSceneAdditively(false),
		_requestedScene(typeid(Scene)),
		_currentScene(typeid(Scene))
	{
		if(SceneRegistry::_instance != NULL)
		{
			std::cout << "ERROR: SceneRegistry being instantiated more than once!\n";
			std::cout << "Aborting in 11 seconds...";

			sf::sleep(sf::seconds(11.0f));

			exit(1);
		}

		// Assign the internal singleton
		SceneRegistry::_instance = this;
	}

	// Dtor
	SceneRegistry::~SceneRegistry()
	{
		// Clear the internal singleton
		SceneRegistry::_instance = NULL;
	}

	// Routines =========================================

	// Load all the resources
	bool SceneRegistry::Load()
	{
		// Add all the scenes to the registry
		addScene<scene::ExampleScene>();
		addScene<scene::DemoScene>();

		// Chose one of the scenes as the first scene to load
		SceneRegistry::LoadScene<scene::DemoScene>();

		// Loading successful
		_resourcesLoaded = true;
		return _resourcesLoaded;
	}

	// Loads scene at end of loop if requested
	void SceneRegistry::loadSceneIfRequested()
	{
		// Skip if there wasn't a requested scene to load
		if(!_sceneLoadingRequested) return;

		// Load the requested scene
		std::shared_ptr<Scene> sceneToBeLoaded = _resourceList.at(_requestedScene);
		if(_loadSceneAdditively)
			sceneToBeLoaded->LoadAdditive();
		else
			sceneToBeLoaded->Load();

		// Once scene is loaded, clear scene loading flags
		_sceneLoadingRequested = false;
		_loadSceneAdditively = false;
	}

	// Unload all the resources
	void SceneRegistry::Unload()
	{
		// Mark the resources as unloaded
		_resourcesLoaded = false;

		// Skip unloading of list if empty
		if(_resourceList.empty()) return;

		// Empty the list
		_resourceList.clear();
	}

	// Properties =========================================

	// STATIC:
	int SceneRegistry::NumberOfScenes()
	{
		// Make sure this exists
		if(!SceneRegistry::verifyInstantiation()) return 0;
		if(SceneRegistry::_instance->_resourceList.empty()) return 0;

		return SceneRegistry::_instance->_resourceList.size();
	}

	// Helpers =========================================

	// STATIC: Was this object instantiated?
	bool SceneRegistry::verifyInstantiation()
	{
		if(SceneRegistry::_instance == NULL)
		{
			std::cout << "ERROR: SceneRegistry not instantiated!" << std::endl;
			return false;
		}

		return true;
	}

} // namespace sfew