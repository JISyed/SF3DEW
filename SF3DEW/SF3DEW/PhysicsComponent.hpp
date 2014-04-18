// Physics Component
// Component that gives GameObjects physics properties
//
// Written by Jibran Syed (4-16-2014)

#ifndef SFEW_PHYSICS_COMPONENT_H
#define SFEW_PHYSICS_COMPONENT_H

#include <memory>

#include "Component.hpp"

namespace sfew
{
	class PhysicsComponent : public Component
	{
	public:

		// Ctor/Dtor ======================

		PhysicsComponent(std::weak_ptr<GameObject> owningGameObject);
		virtual ~PhysicsComponent();

		// Routines =======================

		virtual void Start();
		virtual void Update();

		// Properties =====================

		virtual ComponentType GetType() const;

	private:

		// Helpers ========================

		

		// Data ===========================
		
	};

	
} // namespace sfew

#endif