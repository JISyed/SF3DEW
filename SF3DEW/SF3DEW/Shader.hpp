// Shader
// Abstraction for a single OpenGL shader program
//
// Written by Jibran Syed (4-4-2014)

#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

namespace sfew
{
	enum class ShaderType : char
	{
		Vertex,
		Fragment
	};

	class Shader
	{
	public:

		// Ctor/Dtor ======================

		Shader(const char* vertexShaderPath, const char * fragmentShaderPath);
		~Shader();

		// Routines =======================

		// Properties =====================

	private:

		// Helpers ========================

		// Data ===========================

		GLuint _shaderProgram;		// Handle to the shader program (vertex + fragment shader combined)
		GLuint _vertexShader;		// Handle to the vertex shader (processes vertices)
		GLuint _fragmentShader;		// Handle to the fragment shader (processes pixels)
	};

	
} // namespace sfew

#endif