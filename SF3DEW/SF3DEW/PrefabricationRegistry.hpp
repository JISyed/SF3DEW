// Prefabrication Registry
// A registry for store all Prefabrication objects
//
// Written by Jibran Syed (4-14-2014)

#ifndef SFEW_PREFABRICATION_REGISTRY_H
#define SFEW_PREFABRICATION_REGISTRY_H

#include <unordered_map>
#include <typeindex>
#include <iostream>
#include <memory>

#include "Registry.hpp"
#include "Prefabrication.hpp"
#include "AllPrefabrications.hpp"

namespace sfew
{
	class PrefabricationRegistry : public Registry
	{
	public:

		// Ctor/Dtor ======================

		PrefabricationRegistry();
		virtual ~PrefabricationRegistry();

		// Routines =======================

		virtual bool Load();						// Load all the resources
		virtual void Unload();						// Unload all the resources

		// Properties =====================
		
		template<typename T> static std::weak_ptr<T> Get(); 

	private:

		// Helpers ========================

		static bool verifyInstantiation();	// Was this object instantiated?
		template <typename T> bool addPrefab();

		// Data ===========================

		static PrefabricationRegistry* _instance;	// Internal singleton instance
		
		// Hash table of custom prefabs stored by type
		std::unordered_map<std::type_index, std::shared_ptr<Prefabrication>> _resourceList;
	};

	// Template Implementations ===========================================

	// Adds a custom prefab to the registry
	template <typename T> bool PrefabricationRegistry::addPrefab()
	{
		// Get the resources class type
		std::type_index resourceType(typeid(T));

		// Check if custom resource already exists
		if(_resourceList.count(resourceType) != 0)
		{
			std::cout << "Prefabrication \"" << resourceType.name() <<
				"\" already added!" << std::endl;
			return false;
		}

		// Make new resource of type
		std::shared_ptr<T> newResource(new T());

		// Add it to the hash table
		_resourceList[std::type_index(typeid(*newResource))] = newResource;

		return true;
	}

	// STATIC: Get custom prefab from registry
	template<typename T> std::weak_ptr<T> PrefabricationRegistry::Get()
	{
		// Make sure this registry exists
		std::weak_ptr<T> empty = std::weak_ptr<T>();
		if(!PrefabricationRegistry::verifyInstantiation()) return empty;
		if(PrefabricationRegistry::_instance->_resourceList.empty()) return empty;

		// Get queried type
		std::type_index index(typeid(T));

		// Return a weak pointer if found
		if(PrefabricationRegistry::_instance->_resourceList.count(index) != 0)
		{
			return std::static_pointer_cast<T>(
				PrefabricationRegistry::_instance->_resourceList.at(index)
			);
		}

		// If you're here, no resource was found
		return empty;
	}

} // namespace sfew

#endif