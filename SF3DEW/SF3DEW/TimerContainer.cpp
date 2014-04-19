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

	bool TimerContainer::Start()
	{
		return true;
	}

	bool TimerContainer::Update()
	{
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

	// STATIC:
	void TimerContainer::Add(std::shared_ptr<Timer> newObject)
	{
		// Was this initalized
		if(!TimerContainer::verifyInstantiation()) return;
		
		// Check if the pointer is empty
		if(newObject._Expired()) return;

		// Add it
		TimerContainer::_instance->_listOfContainedObjects.push_front(newObject);
	}

	// Properties =========================================

	// Helpers =========================================

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