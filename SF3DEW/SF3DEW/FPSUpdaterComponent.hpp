// FPS Updater Component
// Example custom component that updates the FPS text display
//
// Written by Jibran Syed (4-22-2014)

// Required Headers
#ifndef SFEW_CUSTOM_COMPONENT_FPS_UPDATER
#define SFEW_CUSTOM_COMPONENT_FPS_UPDATER
#include "CustomComponent.hpp"
#include <memory>

// System Headers
#include <sstream>

// SFEW Headers
#include "FontRendererComponent.hpp"

namespace sfew
{
	namespace component
	{
		class FpsUpdaterCmpt : public CustomComponent
		{
		public:

			// Ctor/Dtor ======================

			FpsUpdaterCmpt(std::weak_ptr<GameObject> owningGameObject);
			virtual ~FpsUpdaterCmpt();

			// Required Routines ==============

			virtual void Start();		// Runs at contruction of component
			virtual void Update();		// Runs every frame
			virtual void Cleanup();		// Runs at destruction of component

			// Run if there is a collision with an object of a different group
			virtual void OnCollision(PhysicsCollisionGroups otherGroup, 
								 std::weak_ptr<PhysicsEntity> otherEntity);

		private:

			// Data ===========================

			std::weak_ptr<FontRenderer> _fontRenderer;
			std::stringstream _fpsStringWriter;
			
		};	// End of custom component class header

	} // namespace sfew::component
} // namespace sfew

#endif