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

namespace sfew
{
	class SceneRegistry : public Registry
	{
	public:

		// Ctor/Dtor ======================

		SceneRegistry();
		virtual ~SceneRegistry();

		// Routines =======================

		virtual bool Load();						// Load all the resources
		virtual void Unload();						// Unload all the resources

		// Properties =====================

		template<typename T> static std::weak_ptr<T> Get(); 

	private:

		// Helpers ========================

		static bool verifyInstantiation();	// Was this object instantiated?
		template <typename T> bool addScene();

		// Data ===========================

		static SceneRegistry* _instance;	// Internal singleton instance
		
		// Hash table of custom prefabs stored by type
		std::unordered_map<std::type_index, std::shared_ptr<Scene>> _resourceList;
		
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

	// Get custom scene from registry
	template<typename T> std::weak_ptr<T> SceneRegistry::Get()
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

	
} // namespace sfew

#endif