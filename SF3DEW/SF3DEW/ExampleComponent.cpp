#include "ExampleComponent.hpp"
#include <iostream>
#include "GameObject.hpp"

// System Headers not needed in header


// SFEW Headers not needed in header
#include "Random.hpp"

namespace sfew
{
	namespace component
	{
		// Ctor/Dtor ========================================

		// Constructor
		ExampleCmpt::ExampleCmpt(std::weak_ptr<GameObject> owningGameObject) :
			CustomComponent(owningGameObject)
		{
			Start();
		}

		// Destructor
		ExampleCmpt::~ExampleCmpt()
		{
			Cleanup();
		}

		// Required Routines =========================================

		// Runs at contruction of component
		void ExampleCmpt::Start()
		{
			
		}

		// Runs every frame
		void ExampleCmpt::Update()
		{
			
		}

		// Runs at destruction of component
		void ExampleCmpt::Cleanup()
		{

		}

		// Run if there is a collision with an object of a different group
		void ExampleCmpt::OnCollision(PhysicsCollisionGroups otherGroup, 
										 std::weak_ptr<PhysicsEntity> otherEntity)
		{
			
		}

		// Custom Routines =========================================

		// Properties =========================================

		// Private Routines =========================================

	} // namespace sfew::component
} // namespace sfew