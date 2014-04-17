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
	class PhysicsComponent
	{
	public:

		// Ctor/Dtor ======================

		PhysicsComponent();
		virtual ~PhysicsComponent();

		// Routines =======================

		

		// Properties =====================

		virtual ComponentType GetType() const;

	private:

		// Helpers ========================

		

		// Data ===========================
		
	};

	
} // namespace sfew

#endif