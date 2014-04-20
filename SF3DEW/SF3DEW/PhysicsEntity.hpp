// Physics Entity
// Handles simple physics movement and sphere colliders
//
// Written by Jibran Syed (4-18-2014)

#ifndef SFEW_PHYSICS_ENTITY_H
#define SFEW_PHYSICS_ENTITY_H

#include <memory>

// PERSONAL HEADERS HERE

namespace sfew
{
	// GameObject forward declare
	class GameObject;

	// Enumeration for different collision groups
	enum PhysicsCollisionGroups
	{
		GroupA,		// Define the type of object that belong in this group
		GroupB,		// Define the type of object that belong in this group
		GroupC,		// Define the type of object that belong in this group
		GroupD,		// Define the type of object that belong in this group
		GroupE,		// Define the type of object that belong in this group
		GroupF,		// Define the type of object that belong in this group
		GroupG,		// Define the type of object that belong in this group
		GroupH		// Define the type of object that belong in this group
	};

	class PhysicsEntity
	{
	public:

		// Ctor/Dtor ======================

		PhysicsEntity(std::weak_ptr<GameObject> gameObject);
		~PhysicsEntity();

		// Routines =======================

		void Update();
		void OnCollision(PhysicsCollisionGroups otherGroup, 
						 std::weak_ptr<PhysicsEntity> otherEntity);


		// Properties =====================

		void SetCollisionGroup(PhysicsCollisionGroups newGroup);
		PhysicsCollisionGroups GetCollisionGroup() const;
		std::weak_ptr<GameObject> GetGameObject() const;

	private:

		// Helpers ========================

		

		// Data ===========================

		PhysicsCollisionGroups _collisionGroup;	// The entity's collision group
		std::weak_ptr<GameObject> _gameObject;	// Owner GameObject

	};

	
} // namespace sfew

#endif