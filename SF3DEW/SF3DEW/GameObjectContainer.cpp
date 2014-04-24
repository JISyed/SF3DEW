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
		// Does nothing
		return true;
	}

	bool GameObjectContainer::Update()
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

	bool GameObjectContainer::Cleanup()
	{
		// Clear the list
		if(!_listOfContainedObjects.empty())
		{
			_listOfContainedObjects.clear();
		}

		return true;
	}

	// STATIC: Factory method for GameObjects
	std::weak_ptr<GameObject> GameObjectContainer::Create()
	{
		// Was this initalized?
		std::weak_ptr<GameObject> empty;
		if(!GameObjectContainer::verifyInstantiation()) return empty;

		// Create new GameObject
		std::shared_ptr<GameObject> newObject(new GameObject());

		// Pass it into GameObjectContainer
		GameObjectContainer::add(newObject);

		// Return weak pointer
		return newObject;
	}

	// STATIC: Removes every object except persistant objects
	void GameObjectContainer::RemoveEverything()
	{
		// Was this initalized
		if(!GameObjectContainer::verifyInstantiation()) return;

		// Check if container is already empty
		auto& objList = GameObjectContainer::_instance->_listOfContainedObjects;
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

	// Properties =========================================

	// STATIC:
	std::weak_ptr<GameObject> GameObjectContainer::GetByName(const std::string& name)
	{
		auto empty = std::weak_ptr<GameObject>();

		// Was this initalized
		if(!GameObjectContainer::verifyInstantiation()) return empty;
		
		// Check if the list is empty
		if(GameObjectContainer::_instance->_listOfContainedObjects.empty()) return empty;

		// Loop through all GameObjects
		for (auto& go : GameObjectContainer::_instance->_listOfContainedObjects)
		{
			// Make sure GameObject is not null
			if(go._Expired()) continue;

			// Compare GameObject's name with queried name
			if(go->GetName().compare(name) == 0)
			{
				return go;
			}
		}

		// Couldn't find with the queried name
		return empty;
	}

	// Helpers =========================================

	// STATIC:
	void GameObjectContainer::add(std::shared_ptr<GameObject> newObject)
	{
		// Was this initalized
		if(!GameObjectContainer::verifyInstantiation()) return;
		
		// Check if the pointer is empty
		if(newObject._Expired()) return;

		// Add it
		GameObjectContainer::_instance->_listOfContainedObjects.push_front(newObject);
	}

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