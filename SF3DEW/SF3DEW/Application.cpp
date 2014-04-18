#include "Application.hpp"

#include <iostream>
#include <SFML/System.hpp>

namespace sfew
{
	// Static Data ======================================

	Application* Application::_instance = NULL;

	// Ctor/Dtor ========================================

	Application::Application()
	{
		if(Application::_instance != NULL)
		{
			std::cout << "ERROR: Application being instantiated more than once!\n";
			std::cout << "Aborting in 11 seconds...";

			sf::sleep(sf::seconds(11.0f));

			exit(1);
		}

		// Assign the internal singleton
		Application::_instance = this;
	}

	Application::~Application()
	{
		// Clear the internal singleton
		Application::_instance = NULL;
	}

	// System Routines ====================================

	bool Application::Setup()
	{
		// Make the window
		_window = std::shared_ptr<sf::RenderWindow>(
			new sf::RenderWindow(
				sf::VideoMode(800, 600), 
				"SF3DEW Test", 
				sf::Style::Close | sf::Style::Titlebar
			)
		);
		_window->setVerticalSyncEnabled(true);
		_windowSize = _window->getSize();

		return true;
	}

	bool Application::Update()
	{
		return true;
	}

	bool Application::Cleanup()
	{
		return true;
	}

	// Routines =========================================

	// STATIC:
	std::weak_ptr<sf::RenderWindow> Application::GetWindow()
	{
		if(!Application::verifyInstantiation()) 
			return std::weak_ptr<sf::RenderWindow>();

		return Application::_instance->_window;
	}

	// STATIC:
	sf::Vector2u Application::GetWindowSize()
	{
		if(!Application::verifyInstantiation()) 
			return sf::Vector2u();

		return Application::_instance->_windowSize;
	}

	// Properties =========================================

	// Helpers =========================================

	// STATIC: Was this object instantiated?
	bool Application::verifyInstantiation()
	{
		if(Application::_instance == NULL)
		{
			std::cout << "ERROR: SystemTime not instantiated!" << std::endl;
			return false;
		}

		return true;
	}

} // namespace sfew