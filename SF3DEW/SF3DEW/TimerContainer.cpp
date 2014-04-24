#include "TimerContainer.hpp"

#include <iostream>
#include <SFML/System.hpp>

namespace sfew
{
	// Static Data =======================================

	TimerContainer* TimerContainer::_instance = NULL;

	// Ctor/Dtor ========================================

	// Ctor
	TimerContainer::TimerContainer()
	{
		if(TimerContainer::_instance != NULL)
		{
			std::cout << "ERROR: TimerContainer being instantiated more than once!\n";
			std::cout << "Aborting in 11 seconds...";

			sf::sleep(sf::seconds(11.0f));

			exit(1);
		}

		// Assign the internal singleton
		TimerContainer::_instance = this;
	}

	// Dtor
	TimerContainer::~TimerContainer()
	{
		// Clear the internal singleton
		TimerContainer::_instance = NULL;
	}

	// Routines =========================================

	bool TimerContainer::Setup()
	{
		// Does nothing
		return true;
	}

	bool TimerContainer::Update()
	{
		// Check if the list is empty
		if(_listOfContainedObjects.empty()) return true;

		// Loop through all objects in list
		auto back_itr = _listOfContainedObjects.before_begin();
		auto front_itr = _listOfContainedObjects.begin();
		while(front_itr != _listOfContainedObjects.end())
		{
			// Check for null ptr
			if(front_itr->_Expired())
			{
				// Delete the pointer at front_itr
				front_itr = _listOfContainedObjects.erase_after(back_itr);
			}
			// Check for marked deletion
			else if((*front_itr)->IsToBeDestroyed())
			{
				// Delete the pointer at front_itr
				front_itr = _listOfContainedObjects.erase_after(back_itr);
			}
			// Update and iterate
			else
			{
				(*front_itr)->Update();
				front_itr++;
				back_itr++;
			}
		}

		return true;
	}

	bool TimerContainer::Cleanup()
	{
		// Clear the list
		if(!_listOfContainedObjects.empty())
		{
			_listOfContainedObjects.clear();
		}

		return true;
	}

	// STATIC: Factory method for Timers
	std::weak_ptr<Timer> TimerContainer::Create(sf::Time setTime, Callback function)
	{
		// Was this initalized?
		std::weak_ptr<Timer> empty;
		if(!TimerContainer::verifyInstantiation()) return empty;

		// Create new GameObject
		std::shared_ptr<Timer> newObject(new Timer(setTime, function));

		// Pass it into GameObjectContainer
		TimerContainer::add(newObject);

		// Return weak pointer
		return newObject;
	}

	// STATIC: Removes every object except persistant objects
	void TimerContainer::RemoveEverything()
	{
		// Was this initalized
		if(!TimerContainer::verifyInstantiation()) return;

		// Check if container is already empty
		auto& objList = TimerContainer::_instance->_listOfContainedObjects;
		if(objList.empty()) return;

		// Remove everything not flagged as persistant
		auto back_itr = objList.before_begin();
		auto front_itr = objList.begin();
		while(front_itr != objList.end())
		{
			// Check for null ptr
			if(front_itr->_Expired())
			{
				// Delete the pointer at front_itr
				front_itr = objList.erase_after(back_itr);
			}
			// Check if not persistant
			else if(!(*front_itr)->IsPersistant())
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

	// STATIC:
	void TimerContainer::add(std::shared_ptr<Timer> newObject)
	{
		// Was this initalized
		if(!TimerContainer::verifyInstantiation()) return;
		
		// Check if the pointer is empty
		if(newObject._Expired()) return;

		// Add it
		TimerContainer::_instance->_listOfContainedObjects.push_front(newObject);
	}

	// STATIC: Was this object instantiated?
	bool TimerContainer::verifyInstantiation()
	{
		if(TimerContainer::_instance == NULL)
		{
			std::cout << "ERROR: TimerContainer not instantiated!" << std::endl;
			return false;
		}

		return true;
	}

} // namespace sfew