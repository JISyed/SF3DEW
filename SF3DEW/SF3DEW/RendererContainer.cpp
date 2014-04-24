#include "RendererContainer.hpp"

#include <iostream>
#include <SFML/System.hpp>
#include <GL/glew.h>

#include "Application.hpp"

namespace sfew
{
	// Static Data =======================================

	RendererContainer* RendererContainer::_instance = NULL;

	// Ctor/Dtor ========================================

	// Ctor
	RendererContainer::RendererContainer() :
		_clearColor(0.0f, 0.0f, 0.0f, 1.0f)
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

	bool RendererContainer::Setup()
	{
		// Activate OpenGL extentions
		glewExperimental = GL_TRUE;
		glewInit();

		// Enable render culling to increase draw performance
		glEnable(GL_CULL_FACE); 
		glCullFace(GL_BACK);

		// Enable depth buffer to draw 3D objects at correct depths
		glEnable(GL_DEPTH_TEST);

		// Set initial background color
		glClearColor(_clearColor.r, 
					 _clearColor.g, 
					 _clearColor.b, 
					 _clearColor.a
		);

		return true;
	}

	bool RendererContainer::Update()
	{
		// Does nothing
		return Draw();
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

	// STATIC:
	void RendererContainer::Add(std::weak_ptr<FontRenderer> newFontRenderer)
	{
		// Was this initalized
		if(!RendererContainer::verifyInstantiation()) return;
		
		// Check if the pointer is empty
		if(newFontRenderer.expired()) return;

		// Add it
		RendererContainer::_instance->_listOfFontRenderers.push_front(newFontRenderer);
	}

	bool RendererContainer::Draw()
	{
		// Clear the render buffer with the clear color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// Loop through all ObjectRenderers
		auto o_back_itr = _listOfObjectRenderers.before_begin();
		auto o_front_itr = _listOfObjectRenderers.begin();
		while(o_front_itr != _listOfObjectRenderers.end())
		{
			// Check for null ptr
			if(o_front_itr->expired())
			{
				// Delete the pointer at front_itr
				o_front_itr = _listOfObjectRenderers.erase_after(o_back_itr);
			}
			// Draw object and iterate
			else
			{
				(*o_front_itr)._Get()->Draw();
				o_front_itr++;
				o_back_itr++;
			}
		}

		// Loop through all FontRenderers
		auto f_back_itr = _listOfFontRenderers.before_begin();
		auto f_front_itr = _listOfFontRenderers.begin();
		while(f_front_itr != _listOfFontRenderers.end())
		{
			// Check for null ptr
			if(f_front_itr->expired())
			{
				// Delete the pointer at front_itr
				f_front_itr = _listOfFontRenderers.erase_after(f_back_itr);
			}
			// Draw font and iterate
			else
			{
				(*f_front_itr)._Get()->Draw();
				f_front_itr++;
				f_back_itr++;
			}
		}

		// Display final rendered framebuffer
		Application::GetWindow()._Get()->display();

		return true;
	}

	// STATIC:
	void RendererContainer::PrintOpenGLVersion()
	{
		std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	}

	// STATIC: Removes every object except persistant objects
	void RendererContainer::RemoveEverything()
	{
		// Was this initalized
		if(!RendererContainer::verifyInstantiation()) return;

		// Get references to both lists
		auto& o_objList = RendererContainer::_instance->_listOfObjectRenderers;
		auto& f_objList = RendererContainer::_instance->_listOfFontRenderers;

		// Remove every object renderer not flagged as persistant
		if(!o_objList.empty())
		{
			auto o_back_itr = o_objList.before_begin();
			auto o_front_itr = o_objList.begin();
			while(o_front_itr != o_objList.end())
			{
				// Check for null ptr
				if(o_front_itr->expired())
				{
					// Delete the pointer at front_itr
					o_front_itr = o_objList.erase_after(o_back_itr);
				}
				// Check if not persistant
				else if(!(*o_front_itr)._Get()->IsPersistant())
				{
					// Delete the pointer at front_itr
					o_front_itr = o_objList.erase_after(o_back_itr);
				}
				// Iterate
				else
				{
					o_front_itr++;
					o_back_itr++;
				}
			}
		}

		// Remove every font not flagged as persistant
		if(!f_objList.empty())
		{
			auto f_back_itr = f_objList.before_begin();
			auto f_front_itr = f_objList.begin();
			while(f_front_itr != f_objList.end())
			{
				// Check for null ptr
				if(f_front_itr->expired())
				{
					// Delete the pointer at front_itr
					f_front_itr = f_objList.erase_after(f_back_itr);
				}
				// Check if not persistant
				else if(!(*f_front_itr)._Get()->IsPersistant())
				{
					// Delete the pointer at front_itr
					f_front_itr = f_objList.erase_after(f_back_itr);
				}
				// Iterate
				else
				{
					f_front_itr++;
					f_back_itr++;
				}
			}
		}

	}

	// Properties =========================================

	// STATIC:
	void RendererContainer::SetClearColor(Vector4 newClearColor)
	{
		// Was this initalized
		if(!RendererContainer::verifyInstantiation()) return;

		// Set clear color in RenderContainer
		RendererContainer::_instance->_clearColor = newClearColor;

		// Set clear color in OpenGL
		glClearColor(newClearColor.r, 
					 newClearColor.g, 
					 newClearColor.b, 
					 newClearColor.a
		);
	}
	
	// STATIC:
	Vector4 RendererContainer::GetClearColor()
	{
		// Was this initalized
		if(!RendererContainer::verifyInstantiation()) return Vector4();

		return RendererContainer::_instance->_clearColor;
	}

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