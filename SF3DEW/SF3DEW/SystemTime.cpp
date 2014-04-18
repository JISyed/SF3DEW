#include "SystemTime.hpp"

#include <iostream>
#include <SFML/System.hpp>

namespace sfew
{
	// Static data ========================================

	SystemTime* SystemTime::_instance = NULL;

	// Ctor/Dtor ========================================

	SystemTime::SystemTime() : _frameCount(0L)
	{
		if(SystemTime::_instance != NULL)
		{
			std::cout << "ERROR: SystemTime being instantiated more than once!\n";
			std::cout << "Aborting in 11 seconds...";

			sf::sleep(sf::seconds(11.0f));

			exit(1);
		}

		// Assign the internal singleton
		SystemTime::_instance = this;
	}

	SystemTime::~SystemTime()
	{
		// Clear the internal singleton
		SystemTime::_instance = NULL;
	}

	// System Routines =====================================

	// Run at the begining of the program
	bool SystemTime::Setup()
	{
		// Doesn't do anything
		return true;
	}

	// Run every loop
	bool SystemTime::Update()
	{
		// Update the delta time value
		_deltaTime = _gameFrameTime.restart();

		// Increment the frame count
		_frameCount++;

		// Update the FPS value
		_fps = 1.0f / _deltaTime.asSeconds();

		return true;
	}

	// Run at the end of the program
	bool SystemTime::Cleanup()
	{
		// Doesn't do anything
		return true;
	}

	// Routines =========================================

	// STATIC: Get the time since program launched
	sf::Time SystemTime::GetGameRunTime()
	{
		if(!SystemTime::verifyInstantiation())
		{
			return sf::Time::Zero;
		}

		return SystemTime::_instance->_gameRunTime.getElapsedTime();
	}

	// STATIC: Get the time between frames
	sf::Time SystemTime::GetDeltaTime()
	{
		if(!SystemTime::verifyInstantiation())
		{
			return sf::Time::Zero;
		}

		return SystemTime::_instance->_deltaTime;
	}

	// STATIC: Get number of frames since game started
	unsigned long SystemTime::GetFrameCount()
	{
		if(!SystemTime::verifyInstantiation())
		{
			return 0L;
		}

		return SystemTime::_instance->_frameCount;
	}

	// STATIC: Get the frames per second
	float SystemTime::GetFPS()
	{
		if(!SystemTime::verifyInstantiation())
		{
			return 0.0f;
		}

		return SystemTime::_instance->_fps;
	}

	// Helpers =========================================

	// STATIC: Was this object instantiated?
	bool SystemTime::verifyInstantiation()
	{
		if(SystemTime::_instance == NULL)
		{
			std::cout << "ERROR: SystemTime not instantiated!" << std::endl;
			return false;
		}

		return true;
	}

} // namespace sfew