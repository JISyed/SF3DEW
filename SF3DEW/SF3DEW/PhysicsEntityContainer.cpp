#include "PhysicsEntityContainer.hpp"

#include <iostream>
#include <SFML/System.hpp>

namespace sfew
{
	// Static Data =======================================

	PhysicsEntityContainer* PhysicsEntityContainer::_instance = NULL;

	// Ctor/Dtor ========================================

	// Ctor
	PhysicsEntityContainer::PhysicsEntityContainer()
	{
		if(PhysicsEntityContainer::_instance != NULL)
		{
			std::cout << "ERROR: PhysicsEntityContainer being instantiated more than once!\n";
			std::cout << "Aborting in 11 seconds...";

			sf::sleep(sf::seconds(11.0f));

			exit(1);
		}

		// Assign the internal singleton
		PhysicsEntityContainer::_instance = this;
	}

	// Dtor
	PhysicsEntityContainer::~PhysicsEntityContainer()
	{
		// Clear the internal singleton
		PhysicsEntityContainer::_instance = NULL;
	}

	// Routines =========================================

	bool PhysicsEntityContainer::Setup()
	{
		return true;
	}

	bool PhysicsEntityContainer::Update()
	{
		return true;
	}

	bool PhysicsEntityContainer::Cleanup()
	{
		// Clear the list
		if(!_listOfContainedObjects.empty())
		{
			_listOfContainedObjects.clear();
		}

		return true;
	}

	// STATIC:
	void PhysicsEntityContainer::Add(std::weak_ptr<PhysicsEntity> newObject)
	{
		// Was this initalized
		if(!PhysicsEntityContainer::verifyInstantiation()) return;
		
		// Check if the pointer is empty
		if(newObject.expired()) return;

		// Add it
		PhysicsEntityContainer::_instance->_listOfContainedObjects.push_front(newObject);
	}

	// Properties =========================================

	// Helpers =========================================

	// STATIC: Was this object instantiated?
	bool PhysicsEntityContainer::verifyInstantiation()
	{
		if(PhysicsEntityContainer::_instance == NULL)
		{
			std::cout << "ERROR: PhysicsEntityContainer not instantiated!" << std::endl;
			return false;
		}

		return true;
	}

} // namespace sfew