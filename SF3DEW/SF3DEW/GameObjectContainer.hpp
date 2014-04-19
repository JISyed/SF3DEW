// GameObjectContainer
// Container to update GameObject objects
//
// Written by Jibran Syed (4-18-2013)

#ifndef SFEW_GAMEOBJECT_CONTAINER_H
#define SFEW_GAMEOBJECT_CONTAINER_H

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

		virtual bool Start();
		virtual bool Update();
		virtual bool Cleanup();
		static void Add(std::shared_ptr<GameObject> newObject);

		// Properties =====================

	private:

		// Helpers ========================

		static bool verifyInstantiation();	// Was this object instantiated?

		// Data ===========================

		static GameObjectContainer* _instance;	// Internal singleton reference
		std::forward_list<std::shared_ptr<GameObject>> _listOfContainedObjects;
		
	};

	
} // namespace sfew

#endif