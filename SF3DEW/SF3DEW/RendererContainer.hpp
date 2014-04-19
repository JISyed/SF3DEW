// RendererContainer
// Container to update Renderer objects
//
// Written by Jibran Syed (4-18-2013)

#ifndef SFEW_RENDERER_CONTAINER_H
#define SFEW_RENDERER_CONTAINER_H

#include "Container.hpp"
#include "ObjectRenderer.hpp"
#include "FontRenderer.hpp"

namespace sfew
{
	class RendererContainer : public Container
	{
	public:

		// Ctor/Dtor ======================

		RendererContainer();
		virtual ~RendererContainer();

		// Routines =======================

		virtual bool Start();
		virtual bool Update();
		virtual bool Cleanup();
		static void Add(std::weak_ptr<ObjectRenderer> newObjectRenderer);
		static void Add(std::weak_ptr<FontRenderer> newFontRenderer);

		// Properties =====================

	private:

		// Helpers ========================

		static bool verifyInstantiation();	// Was this object instantiated?

		// Data ===========================

		static RendererContainer* _instance;	// Internal singleton reference
		std::forward_list<std::weak_ptr<ObjectRenderer>> _listOfObjectRenderers;
		std::forward_list<std::weak_ptr<FontRenderer>> _listOfFontRenderers;

	};

	
} // namespace sfew

#endif