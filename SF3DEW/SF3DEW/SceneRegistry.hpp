// Scene Registry
// A registry for store all Scene objects
//
// Written by Jibran Syed (4-14-2014)

#ifndef SFEW_SCENE_REGISTRY_H
#define SFEW_SCENE_REGISTRY_H

#include <unordered_map>
#include <typeindex>
#include <iostream>
#include <memory>

#include "Registry.hpp"
#include "Scene.hpp"
#include "AllScenes.hpp"

namespace sfew
{
	class SceneRegistry : public Registry
	{
	public:

		// Ctor/Dtor ======================

		SceneRegistry();
		virtual ~SceneRegistry();

		// Routines =======================

		virtual bool Load();			// Load all the resources
		virtual void Unload();			// Unload all the resources
		void loadSceneIfRequested();	// Loads scene at end of loop if requested

		template <typename T> static bool LoadScene();	// Marks given scene to be loaded
		template <typename T> static bool LoadSceneAdditive();	// Marks given scene to be loaded additively
		template <typename T> static bool IsSceneLoaded();	// Checks if given scene is current scene

		// Properties =====================

		static int NumberOfScenes();

	private:

		// Helpers ========================

		static bool verifyInstantiation();	// Was this object instantiated?
		template <typename T> bool addScene();
		template<typename T> static std::weak_ptr<T> get(); 

		// Data ===========================

		static SceneRegistry* _instance;	// Internal singleton instance
		
		// Hash table of custom prefabs stored by type
		std::unordered_map<std::type_index, std::shared_ptr<Scene>> _resourceList;

		bool _sceneLoadingRequested;		// Was a new scene load requested?
		bool _loadSceneAdditively;			// Will next scene load additively?
		std::type_index _requestedScene;	// The scene requested to load
		std::type_index _currentScene;		// The current scene loaded

	};

	// Template Implementations ===========================================

	// Adds a custom scene to the registry
	template <typename T> bool SceneRegistry::addScene()
	{
		// Get the resources class type
		std::type_index resourceType(typeid(T));

		// Check if custom resource already exists
		if(_resourceList.count(resourceType) != 0)
		{
			std::cout << "Scene \"" << resourceType.name() <<
				"\" already added!" << std::endl;
			return false;
		}

		// Make new resource of type
		std::shared_ptr<T> newResource(new T());

		// Add it to the hash table
		_resourceList[std::type_index(typeid(*newResource))] = newResource;

		return true;
	}

	// STATIC: Get custom scene from registry
	template<typename T> std::weak_ptr<T> SceneRegistry::get()
	{
		// Make sure this registry exists
		std::weak_ptr<T> empty = std::weak_ptr<T>();
		if(!SceneRegistry::verifyInstantiation()) return empty;
		if(SceneRegistry::_instance->_resourceList.empty()) return empty;

		// Get queried type
		std::type_index index(typeid(T));

		// Return a weak pointer if found
		if(SceneRegistry::_instance->_resourceList.count(index) != 0)
		{
			return std::static_pointer_cast<T>(
				SceneRegistry::_instance->_resourceList.at(index)
			);
		}

		// If you're here, no resource was found
		return empty;
	}

	// STATIC: Marks given scene to be loaded
	template <typename T> bool SceneRegistry::LoadScene()
	{
		// Make sure this registry exists
		if(!SceneRegistry::verifyInstantiation()) return false;
		if(SceneRegistry::_instance->_resourceList.empty()) return false;

		// Get queried type
		std::type_index requestedType(typeid(T));

		// Get queried scene
		std::weak_ptr<T> queriedScene = SceneRegistry::get<T>();

		// Abort if scene wasn't found
		if(queriedScene.expired())
		{
			std::cout << "Warning: Could not find scene \""
				<< requestedType.name() << "\"." << std::endl;
			SceneRegistry::_instance->_sceneLoadingRequested = false;
			SceneRegistry::_instance->_loadSceneAdditively = false;
			return false;
		}

		// Mark the scene to be loaded
		SceneRegistry::_instance->_sceneLoadingRequested = true;
		SceneRegistry::_instance->_loadSceneAdditively = false;
		SceneRegistry::_instance->_requestedScene = requestedType;

		return true;
	}

	// STATIC: Marks given scene to be loaded additively
	template <typename T> bool SceneRegistry::LoadSceneAdditive()
	{
		// Make sure this registry exists
		if(!SceneRegistry::verifyInstantiation()) return false;
		if(SceneRegistry::_instance->_resourceList.empty()) return false;

		// Get queried type
		std::type_index requestedType(typeid(T));

		// Get queried scene
		std::weak_ptr<T> queriedScene = SceneRegistry::get<T>();

		// Abort if scene wasn't found
		if(queriedScene.expired())
		{
			std::cout << "Warning: Could not find scene \""
				<< requestedType.name() << "\"." << std::endl;
			SceneRegistry::_instance->_sceneLoadingRequested = false;
			SceneRegistry::_instance->_loadSceneAdditively = false;
			return false;
		}

		// Mark the scene to be loaded additively
		SceneRegistry::_instance->_sceneLoadingRequested = true;
		SceneRegistry::_instance->_loadSceneAdditively = true;
		SceneRegistry::_instance->_requestedScene = requestedType;

		return true;
	}

	// STATIC: Checks if given scene is current scene
	template <typename T> bool SceneRegistry::IsSceneLoaded()
	{
		// Make sure this registry exists
		if(!SceneRegistry::verifyInstantiation()) return false;
		if(SceneRegistry::_instance->_resourceList.empty()) return false;

		// Get queried type
		std::type_index requestedType(typeid(T));

		// Compare if the requested scene is the current scene
		return requestedType == SceneRegistry::_instance->_currentScene;
	}
	
} // namespace sfew

#endif