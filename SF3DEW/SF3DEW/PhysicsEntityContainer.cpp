#include "PhysicsEntityContainer.hpp"

#include <iostream>
#include <SFML/System.hpp>

#include "GameObject.hpp"
#include "Transform.hpp"

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
		// Does nothing
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
			PhysicsCollisionGroups firstGroup = firstEntity._Get()->GetCollisionGroup();
			for(auto& secondEntity : _listOfContainedObjects)
			{
				PhysicsCollisionGroups secondGroup = secondEntity._Get()->GetCollisionGroup();
				// Skip if they are the same entity
				if(firstEntity._Get()->GetID() == secondEntity._Get()->GetID())
				{
					continue;
				}
				// Skip if they are the same collision group
				else if(firstGroup == secondGroup)
				{
					continue;
				}
				// Skip if not colliding
				else if(!PhysicsEntityContainer::doEntitiesOverlap(firstEntity, secondEntity))
				{
					continue;
				}
				// If you're here, there was a collision
				else
				{
					// Message first entity of collision only
					// A future loop will message the second entity about this collision.
					firstEntity._Get()->OnCollision(secondGroup, secondEntity);
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

	// STATIC: Removes every object except persistant objects
	void PhysicsEntityContainer::RemoveEverything()
	{
		// Was this initalized
		if(!PhysicsEntityContainer::verifyInstantiation()) return;

		// Check if container is already empty
		auto& objList = PhysicsEntityContainer::_instance->_listOfContainedObjects;
		if(objList.empty()) return;

		// Remove everything not flagged as persistant
		auto back_itr = objList.before_begin();
		auto front_itr = objList.begin();
		while(front_itr != objList.end())
		{
			// Check for null ptr
			if(front_itr->expired())
			{
				// Delete the pointer at front_itr
				front_itr = objList.erase_after(back_itr);
			}
			// Check if not persistant
			else if(!(*front_itr)._Get()->IsPersistant())
			{
				// Delete the pointer at front_itr
				front_itr = objList.erase_after(back_itr);
			}
			// Iterate
			else
			{
				front_itr++;
				back_itr++;
			}
		}
	}

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

	// STATIC:
	float PhysicsEntityContainer::getSquaredDistance(std::weak_ptr<PhysicsEntity> e1, 
													 std::weak_ptr<PhysicsEntity> e2)
	{
		// Abort if null pointers
		if(e1.expired() || e2.expired()) return 0;

		// Set the difference between positions in each dimension
		float deltaX = e1._Get()->GetTransform()._Get()->GetPosition().x
			- e2._Get()->GetTransform()._Get()->GetPosition().x;
		float deltaY = e1._Get()->GetTransform()._Get()->GetPosition().y
			- e2._Get()->GetTransform()._Get()->GetPosition().y;
		float deltaZ = e1._Get()->GetTransform()._Get()->GetPosition().z
			- e2._Get()->GetTransform()._Get()->GetPosition().z;

		// Squared distance formula (doesn't use square root)
		return deltaX*deltaX + deltaY*deltaY + deltaZ*deltaZ;
	}

	// STATIC:
	bool PhysicsEntityContainer::doEntitiesOverlap(std::weak_ptr<PhysicsEntity> e1, 
												   std::weak_ptr<PhysicsEntity> e2)
	{
		float bothRadiiCombined = e1._Get()->GetRadius() + e2._Get()->GetRadius();
		float squaredDistance = PhysicsEntityContainer::getSquaredDistance(e1, e2);

		// Compare distance^2 with bothRadii^2
		return squaredDistance < (bothRadiiCombined*bothRadiiCombined);
	}

} // namespace sfew