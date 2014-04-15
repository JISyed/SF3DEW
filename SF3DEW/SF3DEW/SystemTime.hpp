// System Time
// Calculates program runtime and deltatime
//
// Written by Jibran Syed (4-12-2104)

#ifndef SYSTEM_TIME_H
#define SYSTEM_TIME_H

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include "ISystemObject.hpp"

namespace sfew
{
	class SystemTime : public ISystemObject
	{
	public:

		// Ctor/Dtor ======================

		SystemTime();
		~SystemTime();

		// System Routines ================

		virtual bool Setup();		// Run at the begining of the program
		virtual bool Update();		// Run every loop
		virtual bool Cleanup();		// Run at the end of the program

		// Routines =======================

		static sf::Time GetGameRunTime();		// Get the time since program launched
		static sf::Time GetDeltaTime();			// Get the time between frames
		static unsigned long GetFrameCount();	// Get number of frames since game started
		static float GetFPS();					// Get the frames per second

	private:

		// Helpers ========================

		static bool verifyInstantiation();	// Was this object instantiated?

		// Data ===========================

		static SystemTime* _instance;	// Internal singleton instance
		sf::Clock _gameRunTime;			// Measures how much time elapsed
		sf::Clock _gameFrameTime;		// Measures time between game loops
		sf::Time _deltaTime;			// How much time elapsed between loops?
		unsigned long _frameCount;		// Number of frames since game's start
		float _fps;						// Frames per second
	};

	
} // namespace sfew

#endif