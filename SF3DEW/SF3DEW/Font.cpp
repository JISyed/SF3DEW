#include "Font.hpp"

#include <iostream>
#include <SFML/System.hpp>

namespace sfew
{
	// Ctor/Dtor ========================================

	Font::Font(const std::string& fontFilePath) : INameable("Unnamed Font")
	{
		if(!_font.loadFromFile(fontFilePath))
		{
			std::cout << "Warning! Font not found at \"" << fontFilePath << "\"\n";
			std::cout << "Quitting in 11 seconds..." << std::endl;
			sf::sleep(sf::seconds(11.0f));
		}
	}

	Font::~Font()
	{
		
	}

	// Routines =========================================

	// Properties =========================================

	sf::Font& Font::GetReference()
	{
		return _font;
	}

	// Helpers =========================================

} // namespace sfew