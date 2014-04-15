// Shader
// Abstraction for a single OpenGL shader program
//
// Written by Jibran Syed (4-4-2014)

#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <GL/glew.h>
#include <SFML/System/NonCopyable.hpp>
#include <string>

#include "LinearAlgebraTypes.hpp"
#include "INameable.hpp"

namespace sfew
{
	enum class ShaderType : char
	{
		Vertex,
		Fragment
	};

	class Shader : sf::NonCopyable, public INameable
	{
	public:

		// Ctor/Dtor ======================

		Shader();
		Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		virtual ~Shader();

		// Routines =======================

		void UseShader();				// Make current active shader for OpenGL
		static void StopUsingShaders();	// Assigns no shader to OpenGL rendering
		static void EnableVertexAttributes();	// Use vertex attributes to draw 3D
		static void DisableVertexAttributes();	// Stop using vertex attributes to draw 2D
		bool HasUniform(const std::string& uniformName);	// Does uniform name exist in shader program?
		void FormatVertexAttributes();			// Format vertex data for shaders to use

		// Properties =====================

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

	private:

		// Helpers ========================

		void loadShaderFile(const std::string& filePath, ShaderType type);	// Loads shader from text file
		void compileShader(ShaderType type);	// Compiles specified shader for OpenGL
		void linkShaders();						// Link the vertex and fragment shaders together
		bool verifyShaderIsLinkedForUniforms();	// Verify shader is linked for uniform assignment
		bool verifyUniformLegitimacy(const std::string& uniformName);	// Verify that the uniform variable is valid
		void loadBlankShaderPlaceholder();		// Load the shader that loads by default
		void loadMissingShaderPlaceholder();	// Load the shader that serves as a placeholder to a missing shader

		// Data ===========================

		GLuint _shaderProgram;		// Handle to the shader program (vertex + fragment shader combined)
		GLuint _vertexShader;		// Handle to the vertex shader (processes vertices)
		GLuint _fragmentShader;		// Handle to the fragment shader (processes pixels)
		std::string _vertexCode;	// Code for the vertex shader
		std::string _fragmentCode;	// Code for the fragment shader

		// Instance flags =================

		bool _flaggedAsLinked;		// Were the shaders linked?
		bool _flaggedVertAsLoaded;	// Was the vertex shader loaded?
		bool _flaggedFragAsLoaded;	// Was the fragment shader loaded?
		bool _flaggedAsLoadFailed;	// Did either shader fail to load?
		
	};

	
} // namespace sfew

#endif