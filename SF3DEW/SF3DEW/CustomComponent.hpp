// Custom Component
// Base class for all custom made component scripts
// Similar in concept to Unity's MonoBehavior
//
// Written by Jibran Syed (4-16-2014)

#ifndef SFEW_CUSTOM_COMPONENT
#define SFEW_CUSTOM_COMPONENT

#include "Component.hpp"
#include "PhysicsEntity.hpp"

namespace sfew
{
	class CustomComponent : public Component
	{
	public:

		// Ctor/Dtor ======================

		CustomComponent(std::weak_ptr<GameObject> owningGameObject);
		virtual ~CustomComponent();

		// Routines =======================

		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void Cleanup() = 0;
		virtual void OnCollision(PhysicsCollisionGroups otherGroup, 
								 std::weak_ptr<PhysicsEntity> otherEntity) = 0;
		
	};

	
} // namespace sfew

#endif