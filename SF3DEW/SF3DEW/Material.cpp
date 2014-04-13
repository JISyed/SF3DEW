#include "Material.hpp"

// SYSTEM INCLUDES HERE

namespace sfew
{
	// Ctor/Dtor ========================================

	// Ctor without material
	Material::Material(std::weak_ptr<Shader> shader) : 
		INameable("Unnamed Material"),
		_color(1.0f, 1.0f, 1.0f, 1.0f),
		_shader(shader)
	{
		// Make a blank texture
		_blankTexture = std::shared_ptr<Texture>(new Texture());

		// Assign it to internal texture pointer
		_texture = _blankTexture;
	}

	// Ctor with material
	Material::Material(std::weak_ptr<Shader> shader, std::weak_ptr<Texture> texture) :
		INameable("Unnamed Material"),
		_color(1.0f, 1.0f, 1.0f, 1.0f),
		_shader(shader),
		_texture(texture)
	{

	}

	// Dtor
	Material::~Material()
	{
		
	}

	// Routines =========================================

	// Properties =========================================

	// Helpers =========================================

} // namespace sfew