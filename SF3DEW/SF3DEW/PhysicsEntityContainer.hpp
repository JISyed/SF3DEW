// PhysicsEntityContainer
// Container to update PhysicsEntity objects
//
// Written by Jibran Syed (4-18-2013)

#ifndef SFEW_PHYSICS_CONTAINER_H
#define SFEW_PHYSICS_CONTAINER_H

#include "Container.hpp"
#include "PhysicsEntity.hpp"

namespace sfew
{
	class PhysicsEntityContainer : public Container
	{
	public:

		// Ctor/Dtor ======================

		PhysicsEntityContainer();
		virtual ~PhysicsEntityContainer();

		// Routines =======================

		virtual bool Setup();
		virtual bool Update();
		virtual bool Cleanup();
		static void Add(std::weak_ptr<PhysicsEntity> newObject);
		static void RemoveEverything();		// Removes every object except persistant objects

	private:

		// Helpers ========================

		static bool verifyInstantiation();	// Was this object instantiated?
		static float getSquaredDistance(std::weak_ptr<PhysicsEntity> e1, std::weak_ptr<PhysicsEntity> e2);
		static bool doEntitiesOverlap(std::weak_ptr<PhysicsEntity> e1, std::weak_ptr<PhysicsEntity> e2);

		// Data ===========================

		static PhysicsEntityContainer* _instance;	// Internal singleton reference
		std::forward_list<std::weak_ptr<PhysicsEntity>> _listOfContainedObjects;
		
	};

	
} // namespace sfew

#endif