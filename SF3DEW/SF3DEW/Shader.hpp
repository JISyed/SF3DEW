// Shader
// Abstraction for a single OpenGL shader program
//
// Written by Jibran Syed (4-4-2014)

#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <string>

#include "INameable.hpp"

namespace sfew
{
	enum class ShaderType : char
	{
		Vertex,
		Fragment
	};

	class Shader : sf::NonCopyable, INameable
	{
	public:

		// Ctor/Dtor ======================

		Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		virtual ~Shader();

		// Routines =======================

		void UseShader();				// Make current active shader for OpenGL
		static void StopUsingShaders();	// Assigns no shader to OpenGL rendering

		// Properties =====================

	private:

		// Helpers ========================

		void loadShaderFile(const std::string& filePath, ShaderType type);	// Loads shader from text file
		void compileShader(ShaderType type);	// Compiles specified shader for OpenGL
		void linkShaders();						// Link the vertex and fragment shaders together
		void formatVertexAttributes();			// Format vertex data for shaders to use

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
		
	};

	
} // namespace sfew

#endif