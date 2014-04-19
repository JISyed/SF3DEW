#include "RendererContainer.hpp"

#include <iostream>
#include <SFML/System.hpp>

namespace sfew
{
	// Static Data =======================================

	RendererContainer* RendererContainer::_instance = NULL;

	// Ctor/Dtor ========================================

	// Ctor
	RendererContainer::RendererContainer()
	{
		if(RendererContainer::_instance != NULL)
		{
			std::cout << "ERROR: RendererContainer being instantiated more than once!\n";
			std::cout << "Aborting in 11 seconds...";

			sf::sleep(sf::seconds(11.0f));

			exit(1);
		}

		// Assign the internal singleton
		RendererContainer::_instance = this;
	}

	// Dtor
	RendererContainer::~RendererContainer()
	{
		// Clear the internal singleton
		RendererContainer::_instance = NULL;
	}

	// Routines =========================================

	bool RendererContainer::Start()
	{
		return true;
	}

	bool RendererContainer::Update()
	{
		return true;
	}

	bool RendererContainer::Cleanup()
	{
		// Clear the ObjectRenderer list
		if(!_listOfObjectRenderers.empty())
		{
			_listOfObjectRenderers.clear();
		}

		// Clear the FontRenderer list
		if(!_listOfFontRenderers.empty())
		{
			_listOfFontRenderers.clear();
		}

		return true;
	}

	// STATIC:
	void RendererContainer::Add(std::weak_ptr<ObjectRenderer> newObjectRenderer)
	{
		// Was this initalized
		if(!RendererContainer::verifyInstantiation()) return;
		
		// Check if the pointer is empty
		if(newObjectRenderer.expired()) return;

		// Add it
		RendererContainer::_instance->_listOfObjectRenderers.push_front(newObjectRenderer);
	}

	void RendererContainer::Add(std::weak_ptr<FontRenderer> newFontRenderer)
	{
		// Was this initalized
		if(!RendererContainer::verifyInstantiation()) return;
		
		// Check if the pointer is empty
		if(newFontRenderer.expired()) return;

		// Add it
		RendererContainer::_instance->_listOfFontRenderers.push_front(newFontRenderer);
	}

	// Properties =========================================

	// Helpers =========================================

	// STATIC: Was this object instantiated?
	bool RendererContainer::verifyInstantiation()
	{
		if(RendererContainer::_instance == NULL)
		{
			std::cout << "ERROR: RendererContainer not instantiated!" << std::endl;
			return false;
		}

		return true;
	}

} // namespace sfew