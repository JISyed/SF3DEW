#include "Timer.hpp"

#include <iostream>

namespace sfew
{
	// Ctor/Dtor ========================================

	// Ctor
	Timer::Timer(sf::Time setTime, Callback function) :
		_triggerTime(setTime),
		_triggerEvent(function),
		_loops(false),
		_alreadyTriggered(false)
	{
		
	}

	// Dtor
	Timer::~Timer()
	{
		
	}

	// Routines =========================================

	// Update timer in game loop
	void Timer::Update()
	{
		// Skip if already triggered
		if(_alreadyTriggered) return;

		// Check if time's up
		if(GetTimeRemaining().asSeconds() <= 0.0f)
		{
			// Run callback
			executeCallback();

			// Restart if looping
			if(_loops)
			{
				Reset();
			}
		}
	}

	// Adds time to make timer trigger later
	void Timer::AddTime(float addedSeconds)
	{
		sf::Time addedTime(sf::seconds(addedSeconds));
		_triggerTime += addedTime;
	}

	// Adds time to make timer trigger later
	void Timer::AddTime(sf::Time addedTime)
	{
		_triggerTime += addedTime;
	}

	// Resets the clock to countdown the trigger
	void Timer::Reset()
	{
		_alreadyTriggered = false;
		_countdown.restart();
	}

	// Properties =========================================

	void Timer::SetCallback(Callback newCallback)
	{
		_triggerEvent = newCallback;
	}

	void Timer::SetLooping(bool loop)
	{
		if(loop == true)
		{
			_alreadyTriggered = false;
			
			if(_triggerTime.asSeconds() < 0.0f)
			{
				Reset();
			}
		}

		_loops = loop;
	}

	bool Timer::IsLooping() const
	{
		return _loops;
	}

	void Timer::SetTime(sf::Time newTime)
	{
		_triggerTime = newTime;
	}

	void Timer::SetTime(float newSeconds)
	{
		sf::Time newTime(sf::seconds(newSeconds));
		_triggerTime = newTime;
	}

	sf::Time Timer::GetTime() const
	{
		return _triggerTime;
	}

	bool Timer::AlreadyTriggered() const
	{
		return _alreadyTriggered;
	}

	sf::Time Timer::GetTimeElapsed() const
	{
		return _countdown.getElapsedTime();
	}

	sf::Time Timer::GetTimeRemaining() const
	{
		sf::Time elapsed = _countdown.getElapsedTime();
		sf::Time remaining = _triggerTime - elapsed;
		if(remaining.asSeconds() < 0.0f)
		{
			remaining = sf::Time::Zero;
		}

		return remaining;
	}

	// Helpers =========================================

	// Fire the triggered event
	void Timer::executeCallback()
	{
		// Mark as already triggered
		_alreadyTriggered = true;

		// Check if target is valid
		/*
		if(_triggerEvent.target<Callback>() == nullptr)
		{
			std::cout << "Error! Timer's callback has no target!" << std::endl;
			return;
		}
		*/

		// Fire the callback
		_triggerEvent();
	}

} // namespace sfew