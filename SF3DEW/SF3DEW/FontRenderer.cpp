#include "FontRenderer.hpp"

#include <iostream>
#include "Application.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"

namespace sfew
{
	// Ctor/Dtor ========================================

	// Ctor
	FontRenderer::FontRenderer(const sf::Font& font) :
		_isPersistant(false)
	{
		_textLabel.setFont(font);
		_textLabel.setString("Example Text");
		_textLabel.setCharacterSize(30);
	}

	// Dtor
	FontRenderer::~FontRenderer()
	{
		
	}

	// Routines =========================================

	void FontRenderer::Draw()
	{
		Mesh::StopUsingMeshes();
		Shader::StopUsingShaders();
		Texture::StopUsingTextures();
		Shader::DisableVertexAttributes();

		auto window = Application::GetWindow();
		window._Get()->pushGLStates();
		window._Get()->draw(_textLabel);
		window._Get()->popGLStates();
		
		Shader::EnableVertexAttributes();
	}

	// Move relatively
	void FontRenderer::Move(float offsetX, float offsetY)
	{
		_textLabel.move(offsetX, offsetY);
	}

	// Move relatively
	void FontRenderer::Move(const sf::Vector2f& offset)
	{
		_textLabel.move(offset);
	}

	// Scale relatively
	void FontRenderer::Scale(float factorX, float factorY)
	{
		_textLabel.scale(factorX, factorY);
	}

	// Scale relatively
	void FontRenderer::Scale(const sf::Vector2f& factor)
	{
		_textLabel.scale(factor);
	}

	// Rotate relatively
	void FontRenderer::Rotate(float angle)
	{
		_textLabel.rotate(angle);
	}

	// Properties =========================================

	void FontRenderer::SetTextString(const std::string& newText)
	{
		_textLabel.setString(newText);
	}

	const std::string FontRenderer::GetTextString() const
	{
		return _textLabel.getString().toAnsiString();
	}

	void FontRenderer::SetFont(const sf::Font& newFont)
	{
		_textLabel.setFont(newFont);
	}

	const sf::Font* FontRenderer::GetFont() const
	{
		return _textLabel.getFont();
	}

	void FontRenderer::SetFontSize(unsigned int newSize)
	{
		_textLabel.setCharacterSize(newSize);
	}

	unsigned int FontRenderer::GetFontSize() const
	{
		return _textLabel.getCharacterSize();
	}

	void FontRenderer::SetStyle(sf::Uint32 newStyle)
	{
		_textLabel.setStyle(newStyle);
	}

	sf::Uint32 FontRenderer::GetStyle() const
	{
		return _textLabel.getStyle();
	}

	void FontRenderer::SetColor(const sf::Color& newColor)
	{
		_textLabel.setColor(newColor);
	}

	void FontRenderer::SetColor(Vector4 newColor)
	{
		sf::Uint8 uRed = (sf::Uint8)(newColor.r * 255);
		sf::Uint8 uGreen = (sf::Uint8)(newColor.g * 255);
		sf::Uint8 uBlue = (sf::Uint8)(newColor.b * 255);
		sf::Uint8 uAplha = (sf::Uint8)(newColor.a * 255);

		sf::Color color(uRed, uGreen, uBlue, uAplha);
		_textLabel.setColor(color);
	}

	void FontRenderer::SetColor(float red, float green, float blue, float alpha)
	{
		sf::Uint8 uRed = (sf::Uint8)(red * 255);
		sf::Uint8 uGreen = (sf::Uint8)(green * 255);
		sf::Uint8 uBlue = (sf::Uint8)(blue * 255);
		sf::Uint8 uAplha = (sf::Uint8)(alpha * 255);

		sf::Color color(uRed, uGreen, uBlue, uAplha);
		_textLabel.setColor(color);
	}

	void FontRenderer::SetColor(sf::Uint8 red, sf::Uint8 green, sf::Uint8 blue, sf::Uint8 alpha)
	{
		sf::Color color(red, green, blue, alpha);
		_textLabel.setColor(color);
	}

	const sf::Color& FontRenderer::GetColor() const
	{
		return _textLabel.getColor();
	}

	void FontRenderer::SetPosition(const sf::Vector2f& newPosition)
	{
		_textLabel.setPosition(newPosition);
	}

	void FontRenderer::SetPosition(float newX, float newY)
	{
		_textLabel.setPosition(newX, newY);
	}

	const sf::Vector2f& FontRenderer::GetPosition() const
	{
		return _textLabel.getPosition();
	}

	void FontRenderer::SetScale(const sf::Vector2f& newScale)
	{
		_textLabel.setScale(newScale);
	}

	void FontRenderer::SetScale(float newX, float newY)
	{
		_textLabel.setScale(newX, newY);
	}

	const sf::Vector2f& FontRenderer::GetScale() const
	{
		return _textLabel.getScale();
	}

	void FontRenderer::SetRotation(float newRotation)
	{
		_textLabel.setRotation(newRotation);
	}

	float FontRenderer::GetRotation() const
	{
		return _textLabel.getRotation();
	}

	void FontRenderer::SetOrigin(const sf::Vector2f& newOrigin)
	{
		_textLabel.setOrigin(newOrigin);
	}

	void FontRenderer::SetOrigin(float newX, float newY)
	{
		_textLabel.setOrigin(newX, newY);
	}

	const sf::Vector2f& FontRenderer::GetOrigin() const
	{
		return _textLabel.getOrigin();
	}

	void FontRenderer::SetPersistance(bool willBePersistant)
	{
		_isPersistant = willBePersistant;
	}

	bool FontRenderer::IsPersistant() const
	{
		return _isPersistant;
	}

} // namespace sfew