// Application
// Delegates the life time of the game and loads everything
// Would have been ProgramCtrlr in BlockDodger
//
// Written by Jibran Syed (4-12-2014)

#ifndef SFEW_APP_H
#define SFEW_APP_H

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "ISystemObject.hpp"

namespace sfew
{
	class Application : sf::NonCopyable, public ISystemObject
	{
	public:

		// Ctor/Dtor ======================

		Application();
		virtual ~Application();

		// System Routines ================

		virtual bool Setup();		// Run at the begining of the program
		virtual bool Update();		// Run every loop
		virtual bool Cleanup();		// Run at the end of the program

		// Routines =======================



		// Static Routines ================



		// Properties =====================

	private:

		// Helpers ========================

		

		// Data ===========================

		sf::Vector2u _windowSize;		// Size of the window in pixels
		sf::RenderWindow _window;		// Represents a window on the desktop
		
	};

	
} // namespace sfew

#endif