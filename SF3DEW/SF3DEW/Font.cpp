#include "Font.hpp"

#include <iostream>

namespace sfew
{
	// Ctor/Dtor ========================================

	Font::Font(const std::string& fontFilePath) : INameable("Unnamed Font")
	{
		if(!_font.loadFromFile(fontFilePath))
		{
			std::cout << "Warning! Font not found at \"" << fontFilePath << "\"\n";
		}
	}

	Font::~Font()
	{
		
	}

	// Routines =========================================

	// Properties =========================================

	// Helpers =========================================

} // namespace sfew