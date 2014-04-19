#include "GameObjectContainer.hpp"

#include <iostream>
#include <SFML/System.hpp>

namespace sfew
{
	// Static Data =======================================

	GameObjectContainer* GameObjectContainer::_instance = NULL;

	// Ctor/Dtor ========================================

	// Ctor
	GameObjectContainer::GameObjectContainer()
	{
		if(GameObjectContainer::_instance != NULL)
		{
			std::cout << "ERROR: GameObjectContainer being instantiated more than once!\n";
			std::cout << "Aborting in 11 seconds...";

			sf::sleep(sf::seconds(11.0f));

			exit(1);
		}

		// Assign the internal singleton
		GameObjectContainer::_instance = this;
	}

	// Dtor
	GameObjectContainer::~GameObjectContainer()
	{
		// Clear the internal singleton
		GameObjectContainer::_instance = NULL;
	}

	// Routines =========================================

	bool GameObjectContainer::Setup()
	{
		return true;
	}

	bool GameObjectContainer::Update()
	{
		return true;
	}

	bool GameObjectContainer::Cleanup()
	{
		// Clear the list
		if(!_listOfContainedObjects.empty())
		{
			_listOfContainedObjects.clear();
		}

		return true;
	}

	// STATIC:
	void GameObjectContainer::Add(std::shared_ptr<GameObject> newObject)
	{
		// Was this initalized
		if(!GameObjectContainer::verifyInstantiation()) return;
		
		// Check if the pointer is empty
		if(newObject._Expired()) return;

		// Add it
		GameObjectContainer::_instance->_listOfContainedObjects.push_front(newObject);
	}

	// Properties =========================================

	// Helpers =========================================

	// STATIC: Was this object instantiated?
	bool GameObjectContainer::verifyInstantiation()
	{
		if(GameObjectContainer::_instance == NULL)
		{
			std::cout << "ERROR: GameObjectContainer not instantiated!" << std::endl;
			return false;
		}

		return true;
	}

} // namespace sfew