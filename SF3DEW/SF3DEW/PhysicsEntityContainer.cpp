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
		// Check if the list is empty
		if(_listOfContainedObjects.empty()) return true;

		// Loop through all objects in list for motion updating
		auto back_itr = _listOfContainedObjects.before_begin();
		auto front_itr = _listOfContainedObjects.begin();
		while(front_itr != _listOfContainedObjects.end())
		{
			// Check for null ptr
			if(front_itr->expired())
			{
				// Delete the pointer at front_itr
				front_itr = _listOfContainedObjects.erase_after(back_itr);
			}
			// Update and iterate
			else
			{
				(*front_itr)._Get()->Update();
				front_itr++;
				back_itr++;
			}
		}

		// Loop again for collision detection
		for(auto& firstEntity : _listOfContainedObjects)
		{
			for(auto& secondEntity : _listOfContainedObjects)
			{
				// Skip if they are the same entity
				if(firstEntity._Get()->GetID() == secondEntity._Get()->GetID())
				{
					continue;
				}
				// Skip if they are the same collision group
				if(firstEntity._Get()->GetCollisionGroup() == secondEntity._Get()->GetCollisionGroup())
				{
					continue;
				}

			}
		}

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