#include "Material.hpp"

#include <iostream>

namespace sfew
{
	// Ctor/Dtor ========================================

	// Ctor without texture
	Material::Material(std::weak_ptr<Shader> shader) : 
		INameable("Unnamed Material"),
		_color(1.0f, 1.0f, 1.0f, 1.0f),
		_shader(shader),
		_flaggedAsColorChanged(false)
	{
		// Make a blank texture
		_blankTexture = std::shared_ptr<Texture>(new Texture());

		// Assign it to internal texture pointer
		_texture = _blankTexture;
	}

	// Ctor with texture
	Material::Material(std::weak_ptr<Shader> shader, std::weak_ptr<Texture> texture) :
		INameable("Unnamed Material"),
		_color(1.0f, 1.0f, 1.0f, 1.0f),
		_shader(shader),
		_texture(texture),
		_flaggedAsColorChanged(false)
	{

	}

	// Dtor
	Material::~Material()
	{
		
	}

	// Routines =========================================

	// Makes the active material for drawing
	void Material::Use()
	{
		// Make sure pointers are still valid
		if(!validateShader()) return;
		if(!validateTexture()) return;

		// Make the shader and texture active
		_shader._Get()->UseShader();
		_texture._Get()->UseTexture();

		// Send color into the shader if changed
		if(_flaggedAsColorChanged)
		{
			_flaggedAsColorChanged = false;
			_shader._Get()->SetUniform("meshColor", _color);
		}
	}

	// Does uniform exist in shader?
	bool Material::HasUniform(const std::string& uniformName)
	{
		// Make sure pointers are still valid
		if(!validateShader()) return false;

		return _shader._Get()->HasUniform(uniformName);
	}

	// Properties =========================================

	void Material::SetTexture(std::weak_ptr<Texture> newTexture)
	{
		_texture = newTexture;
	}

	std::weak_ptr<Texture> Material::GetTexture() const
	{
		return _texture;
	}

	void Material::SetShader(std::weak_ptr<Shader> newShader)
	{
		_shader = newShader;
	}

	std::weak_ptr<Shader> Material::GetShader() const
	{
		return _shader;
	}

	void Material::SetColor(Vector4 newColor)
	{
		_color = newColor;
		_flaggedAsColorChanged = true;
	}

	Vector4 Material::GetColor() const
	{
		return _color;
	}


	// Pass in uniform data to shader
	void Material::SetUniform(const std::string& uniformName, float x)
	{
		// Make sure pointers are still valid
		if(!validateShader()) return;

		// Set uniform
		_shader._Get()->SetUniform(uniformName, x);
	}

	void Material::SetUniform(const std::string& uniformName, float x, float y)
	{
		// Make sure pointers are still valid
		if(!validateShader()) return;

		// Set uniform
		_shader._Get()->SetUniform(uniformName, x, y);
	}

	void Material::SetUniform(const std::string& uniformName, float x, float y, float z)
	{
		// Make sure pointers are still valid
		if(!validateShader()) return;

		// Set uniform
		_shader._Get()->SetUniform(uniformName, x, y, z);
	}

	void Material::SetUniform(const std::string& uniformName, float x, float y, float z, float w)
	{
		// Make sure pointers are still valid
		if(!validateShader()) return;

		// Set uniform
		_shader._Get()->SetUniform(uniformName, x, y, z, w);
	}

	void Material::SetUniform(const std::string& uniformName, Vector2 vector)
	{
		// Make sure pointers are still valid
		if(!validateShader()) return;

		// Set uniform
		_shader._Get()->SetUniform(uniformName, vector);
	}

	void Material::SetUniform(const std::string& uniformName, Vector3 vector)
	{
		// Make sure pointers are still valid
		if(!validateShader()) return;

		// Set uniform
		_shader._Get()->SetUniform(uniformName, vector);
	}

	void Material::SetUniform(const std::string& uniformName, Vector4 vector)
	{
		// Make sure pointers are still valid
		if(!validateShader()) return;

		// Set uniform
		_shader._Get()->SetUniform(uniformName, vector);
	}

	void Material::SetUniform(const std::string& uniformName, Matrix2 matrix)
	{
		// Make sure pointers are still valid
		if(!validateShader()) return;

		// Set uniform
		_shader._Get()->SetUniform(uniformName, matrix);
	}

	void Material::SetUniform(const std::string& uniformName, Matrix3 matrix)
	{
		// Make sure pointers are still valid
		if(!validateShader()) return;

		// Set uniform
		_shader._Get()->SetUniform(uniformName, matrix);
	}

	void Material::SetUniform(const std::string& uniformName, Matrix4 matrix)
	{
		// Make sure pointers are still valid
		if(!validateShader()) return;

		// Set uniform
		_shader._Get()->SetUniform(uniformName, matrix);
	}


	// Getters only
	const std::string& Material::GetShaderName() const
	{
		// Make sure pointers are still valid
		if(!validateShader()) return std::string();

		// Get name string
		return _shader._Get()->GetName();
	}

	const std::string& Material::GetTextureName() const
	{
		// Make sure pointers are still valid
		if(!validateTexture()) return std::string();

		// Get name string
		return _texture._Get()->GetName();
	}


	// Helpers =========================================

	// Does shader pointer still exist?
	bool Material::validateShader() const
	{
		if(_shader.expired())
		{
			std::cout << "Error: Material \"" << _name << "\" doesn't have a shader!" << std::endl;
			return false;
		}

		return true;
	}

	// Does texture pointer still exist?
	bool Material::validateTexture() const
	{
		if(_texture.expired())
		{
			std::cout << "Error: Material \"" << _name << "\" doesn't have a texture!" << std::endl;
			return false;
		}

		return true;
	}

} // namespace sfew