// Material
// Container class for shaders, textures, and common uniforms
//
// Written by Jibran Syed (4-13-2014)

#ifndef SFEW_MATERIAL_H
#define SFEW_MATERIAL_H

#include <SFML/System/NonCopyable.hpp>
#include <memory>

#include "LinearAlgebraTypes.hpp"
#include "INameable.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

namespace sfew
{
	class Material : sf::NonCopyable, public INameable
	{
	public:

		// Ctor/Dtor ======================

		Material();
		Material(std::weak_ptr<Texture> texture);
		Material(std::weak_ptr<Shader> shader);
		Material(std::weak_ptr<Shader> shader, std::weak_ptr<Texture> texture);
		virtual ~Material();

		// Routines =======================

		void Use();					// Makes the active material for drawing
		bool HasUniform(const std::string& uniformName);	// Does uniform exist in shader?

		// Properties =====================

		void SetTexture(std::weak_ptr<Texture> newTexture);
		std::weak_ptr<Texture> GetTexture() const;
		void SetShader(std::weak_ptr<Shader> newShader);
		std::weak_ptr<Shader> GetShader() const;
		void SetColor(Vector4 newColor);
		Vector4 GetColor() const;

		// Pass in uniform data to shader
		void SetUniform(const std::string& uniformName, float x);
		void SetUniform(const std::string& uniformName, float x, float y);
		void SetUniform(const std::string& uniformName, float x, float y, float z);
		void SetUniform(const std::string& uniformName, float x, float y, float z, float w);
		void SetUniform(const std::string& uniformName, Vector2 vector);
		void SetUniform(const std::string& uniformName, Vector3 vector);
		void SetUniform(const std::string& uniformName, Vector4 vector);
		void SetUniform(const std::string& uniformName, Matrix2 matrix);
		void SetUniform(const std::string& uniformName, Matrix3 matrix);
		void SetUniform(const std::string& uniformName, Matrix4 matrix);

		const std::string& GetShaderName() const;
		const std::string& GetTextureName() const;

	private:

		// Helpers ========================

		bool validateShader() const;		// Does shader pointer still exist?
		bool validateTexture() const;		// Does texture pointer still exist?

		// Data ===========================

		std::weak_ptr<Shader> _shader;			// The shader being referenced
		std::weak_ptr<Texture> _texture;		// The texture being referenced
		std::shared_ptr<Texture> _blankTexture;	// Strong reference to blank texture
		std::shared_ptr<Shader> _blankShader;	// Strong reference to blank shader
		Vector4 _color;							// The color tint
	};

	
} // namespace sfew

#endif