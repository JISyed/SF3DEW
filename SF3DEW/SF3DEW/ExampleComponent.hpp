// [EXAMPLE] Component
// [PUT DESCRIPTION OF COMPONENT HERE]
//
// Written by [NAME] ([MONTH]-[DAY]-[YEAR])

// Required Headers
#ifndef SFEW_CUSTOM_COMPONENT__EXAMPLE
#define SFEW_CUSTOM_COMPONENT__EXAMPLE
#include "CustomComponent.hpp"
#include <memory>

// System Headers


// SFEW Headers


namespace sfew
{
	namespace component
	{
		class ExampleCmpt : public CustomComponent
		{
		public:

			// Ctor/Dtor ======================

			ExampleCmpt(std::weak_ptr<GameObject> owningGameObject);
			virtual ~ExampleCmpt();

			// Required Routines ==============

			virtual void Start();		// Runs at contruction of component
			virtual void Update();		// Runs every frame
			virtual void Cleanup();		// Runs at destruction of component

			// Run if there is a collision with an object of a different group
			virtual void OnCollision(PhysicsCollisionGroups otherGroup, 
								 std::weak_ptr<PhysicsEntity> otherEntity);

			// Custom Routines ================



			// Properties =====================

			

		private:

			// Private Routines ========================

			

			// Data ===========================


			
		};	// End of custom component class header

	} // namespace sfew::component
} // namespace sfew

#endif