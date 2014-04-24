// GameObjectContainer
// Container to update GameObject objects
//
// Written by Jibran Syed (4-18-2013)

#ifndef SFEW_GAMEOBJECT_CONTAINER_H
#define SFEW_GAMEOBJECT_CONTAINER_H

#include <string>

#include "Container.hpp"
#include "GameObject.hpp"

namespace sfew
{
	class GameObjectContainer : public Container
	{
	public:

		// Ctor/Dtor ======================

		GameObjectContainer();
		virtual ~GameObjectContainer();

		// Routines =======================

		virtual bool Setup();
		virtual bool Update();
		virtual bool Cleanup();
		
		static std::weak_ptr<GameObject> Create();	// Factory method for GameObjects

		static void RemoveEverything();		// Removes every object except persistant objects

		// Properties =====================

		static std::weak_ptr<GameObject> GetByName(const std::string& name);

	private:

		// Helpers ========================

		static void add(std::shared_ptr<GameObject> newObject);
		static bool verifyInstantiation();	// Was this object instantiated?

		// Data ===========================

		static GameObjectContainer* _instance;	// Internal singleton reference
		std::forward_list<std::shared_ptr<GameObject>> _listOfContainedObjects;
		
	};

	
} // namespace sfew

#endif