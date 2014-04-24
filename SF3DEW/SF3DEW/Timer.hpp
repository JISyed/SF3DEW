// Timer
// Counts down a certain time and then 
// triggers a callback from the timer's delegate object
// Setting callbacks must be done with std::bind()
//
// Written by Jibran Syed (4-12-2014)

#ifndef SFEW_TIMER_H
#define SFEW_TIMER_H

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/NonCopyable.hpp>

#include "Callback.hpp"

namespace sfew
{
	class Timer : sf::NonCopyable
	{
	public:

		// Ctor/Dtor ======================

		Timer(sf::Time setTime, Callback function);
		~Timer();

		// Routines =======================

		void Update();						// Update timer in game loop
		void AddTime(float addedSeconds);	// Adds time to make timer trigger later
		void AddTime(sf::Time addedTime);	// Adds time to make timer trigger later
		void Reset();						// Resets the clock to countdown the trigger
		void Destroy();						// Mark the timer to be destoryed by TimerContainer

		// Properties =====================

		void SetCallback(Callback newCallback);
		void SetLooping(bool loop);
		bool IsLooping() const;
		void SetTime(sf::Time newTime);
		void SetTime(float newSeconds);
		sf::Time GetTime() const;
		bool AlreadyTriggered() const;
		sf::Time GetTimeElapsed() const;
		sf::Time GetTimeRemaining() const;
		bool IsToBeDestroyed() const;
		void SetPersistance(bool willBePersistant);
		bool IsPersistant() const;

	private:

		// Helpers ========================

		void executeCallback();		// Fire the triggered event

		// Data ===========================

		bool _loops;				// Does the timer trigger in repeated intervals?
		sf::Clock _countdown;		// Increments time until the trigger time
		sf::Time _triggerTime;		// Total amount of time to elapse since creation
		Callback _triggerEvent;		// Function to call when timer has triggered
		bool _alreadyTriggered;		// Did the timer already trigger?
		bool _flaggedForDestruction;// It this to be destroyed?
		bool _isPersistant;			// Will object persist between scene loads?

	};

	
} // namespace sfew

#endif