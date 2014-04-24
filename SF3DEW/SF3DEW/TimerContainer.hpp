// TimerContainer
// Container to update Timer objects
//
// Written by Jibran Syed (4-18-2013)

#ifndef SFEW_TIMER_CONTAINER_H
#define SFEW_TIMER_CONTAINER_H

#include "Container.hpp"
#include "Timer.hpp"

namespace sfew
{
	class TimerContainer : public Container
	{
	public:

		// Ctor/Dtor ======================

		TimerContainer();
		virtual ~TimerContainer();

		// Routines =======================

		virtual bool Setup();
		virtual bool Update();
		virtual bool Cleanup();
		
		static std::weak_ptr<Timer> Create(sf::Time setTime, Callback function); // Factory method for Timers

		static void RemoveEverything();		// Removes every object except persistant objects

	private:

		// Helpers ========================

		static void add(std::shared_ptr<Timer> newObject);
		static bool verifyInstantiation();	// Was this object instantiated?

		// Data ===========================

		static TimerContainer* _instance;	// Internal singleton reference
		std::forward_list<std::shared_ptr<Timer>> _listOfContainedObjects;
		
	};

	
} // namespace sfew

#endif