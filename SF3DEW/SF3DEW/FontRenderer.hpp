// Font Renderer
//
// Wrapper for SFML's Text class that allows
// font drawing to coexist with 3D rendering
//
// Written by Jibran Syed (4-12-2014)

#ifndef FONT_RENDERER_H
#define FONT_RENDERER_H

#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>

#include "LinearAlgebraTypes.hpp"

namespace sfew
{
	class FontRenderer : sf::NonCopyable
	{
	public:

		// Ctor/Dtor ======================

		FontRenderer(const sf::Font& font);
		~FontRenderer();

		// Routines =======================

		void Draw();								// Render the text as 2D overlay
		void Move(float offsetX, float offsetY);	// Move relatively
		void Move(const sf::Vector2f& offset);		// Move relatively
		void Scale(float factorX, float factorY);	// Scale relatively
		void Scale(const sf::Vector2f& factor);		// Scale relatively
		void Rotate(float angle);					// Rotate relatively

		// Properties =====================

		void SetTextString(const std::string& newText);
		const std::string GetTextString() const;
		void SetFont(const sf::Font& newFont);
		const sf::Font* GetFont() const;
		void SetFontSize(unsigned int newSize);
		unsigned int GetFontSize() const;
		void SetStyle(sf::Uint32 newStyle);
		sf::Uint32 GetStyle() const;
		void SetColor(const sf::Color& newColor);
		void SetColor(Vector4 newColor);
		void SetColor(float red, float green, float blue, float alpha);
		void SetColor(sf::Uint8 red, sf::Uint8 green, sf::Uint8 blue, sf::Uint8 alpha);
		const sf::Color& GetColor() const;
		void SetPosition(const sf::Vector2f& newPosition);
		void SetPosition(float newX, float newY);
		const sf::Vector2f& GetPosition() const;
		void SetScale(const sf::Vector2f& newScale);
		void SetScale(float newX, float newY);
		const sf::Vector2f& GetScale() const;
		void SetRotation(float newRotation);
		float GetRotation() const;
		void SetOrigin(const sf::Vector2f& newOrigin);
		void SetOrigin(float newX, float newY);
		const sf::Vector2f& GetOrigin() const;
		void SetPersistance(bool willBePersistant);
		bool IsPersistant() const;


	private:

		// Data ===========================

		sf::Text _textLabel;		// Container to font rendering properties
		bool _isPersistant;			// Will object persist between scene loads?

	};

	
} // namespace sfew

#endif