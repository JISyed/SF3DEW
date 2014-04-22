#include "ExampleComponent.hpp"
#include <iostream>

// System Headers not needed in header


// SFEW Headers not needed in header
#include "GameObject.hpp"

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
			std::cout << "Collision with \"" << GetGameObject()._Get()->GetName()
				<< "\"" << std::endl;
		}

		// Custom Routines =========================================

		// Properties =========================================

		// Private Routines =========================================

	} // namespace sfew::component
} // namespace sfew