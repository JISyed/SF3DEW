#include <iostream>	// For cout
#include <memory>	// For unique_ptr

#include "Application.hpp"

int main()
{
	// Construct the Application and all subsystems
	std::unique_ptr<sfew::Application> app(new sfew::Application());

	// Setup the Application and all subsystems
	app->Setup();

	// Print setup time on console
	std::cout << "Load Time: " 
		<< sfew::SystemTime::GetGameRunTime().asSeconds()
		<< std::endl;

	// Start the Application's loop
	bool runSuccess = app->MainLoop();

	// Clean up all the engine subsystems in Application
	app->Cleanup();

	return 0;
}