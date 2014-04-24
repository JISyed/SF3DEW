// Font
// Reference wrapper for SFML Font objects
//
// Written by Jibran Syed (4-15-2014)

#ifndef SFEW_FONT_H
#define SFEW_FONT_H

#include <string>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/NonCopyable.hpp>

#include "INameable.hpp"

namespace sfew
{
	class Font : sf::NonCopyable, public INameable
	{
	public:

		// Ctor/Dtor ======================

		Font(const std::string& fontFilePath);
		virtual ~Font();

		// Properties =====================

		sf::Font& GetReference();

	private:

		// Data ===========================

		sf::Font _font;					// The font data itself
		
	};

	
} // namespace sfew

#endif