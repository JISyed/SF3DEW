#include "Shader.hpp"

#include <iostream>
#include <fstream>
#include <functional>	// For reference_wrapper

#define SFEW_LOG_SIZE 512

namespace sfew
{
	// Ctor/Dtor ========================================

	Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) :
		_flaggedAsLinked(false),
		_flaggedVertAsLoaded(false),
		_flaggedFragAsLoaded(false)
	{
		// Load the shaders
		loadShaderFile(vertexShaderPath, ShaderType::Vertex);
		_flaggedVertAsLoaded = true;
		loadShaderFile(fragmentShaderPath, ShaderType::Fragment);
		_flaggedFragAsLoaded = true;

		// Compile the shaders
		compileShader(ShaderType::Vertex);
		compileShader(ShaderType::Fragment);

		// Link the shaders
		linkShaders();
	}

	Shader::~Shader()
	{
		// Detach shaders and delete program if link was successful
		if(_flaggedAsLinked)
		{
			glDetachShader(_shaderProgram, _vertexShader);
			glDetachShader(_shaderProgram, _fragmentShader);

			glDeleteProgram(_shaderProgram);
		}

		// Delete vertex shader if loaded successfully
		if(_flaggedVertAsLoaded)
		{
			glDeleteShader(_vertexShader);
		}

		// Delete fragment shader if loaded successfully
		if(_flaggedFragAsLoaded)
		{
			glDeleteShader(_fragmentShader);
		}
	}

	// Routines =========================================

	// Properties =========================================

	// Helpers =========================================

	// Loads shader from text file
	void Shader::loadShaderFile(const std::string& filePath, ShaderType type)
	{
		std::ifstream inSdrFileStream(filePath);
		if(inSdrFileStream.is_open())
		{
			std::reference_wrapper<std::string> shaderBuffer = std::ref(_vertexCode);

			if(type == ShaderType::Vertex)
			{
				std::cout << "Shader File: Loading vertex shader..." << std::endl;
			}
			else if(type == ShaderType::Fragment)
			{
				std::cout << "Shader File: Loading fragment shader..." << std::endl;
				shaderBuffer = std::ref(_fragmentCode);
			}
				
			// Read shader file into a memory buffer (array)
			shaderBuffer.get() = std::string( (std::istreambuf_iterator<char>(inSdrFileStream)), 
											   std::istreambuf_iterator<char>() );

			// Close file and print status
			if(!shaderBuffer.get().empty())
			{
				std::cout << "... Read successfully.\n\n";
				std::cout << "---------------------------------\n";
				std::cout << shaderBuffer.get() << std::endl;
				std::cout << "---------------------------------\n";
				std::cout << std::endl;
				inSdrFileStream.close();
			}
			else
			{
				std::cout << "... Error: Only " << inSdrFileStream.gcount() << " chars could be read!\n";
				inSdrFileStream.close();
				std::cout << "Quitting in 11 seconds..." << std::endl;
				Sleep(11000);
				exit(1);
			}
		}
		else
		{
			std::cout << "Shader File: Error. Not found!" << std::endl;
			std::cout << "Quitting in 11 seconds..." << std::endl;
			Sleep(11000);
			exit(1);
		}
	}

	// Compiles specified shader for OpenGL
	void Shader::compileShader(ShaderType type)
	{
		std::reference_wrapper<std::string> shaderBuffer = std::ref(_vertexCode);
		std::reference_wrapper<GLuint> shaderHandle = std::ref(_vertexShader);
		GLenum oglShaderEnumType = GL_VERTEX_SHADER;

		if(type == ShaderType::Vertex)
		{
			std::cout << "Compiling vertex shader..." << std::endl;
		}
		else if(type == ShaderType::Fragment)
		{
			std::cout << "Compiling fragment shader..." << std::endl;
			shaderBuffer = std::ref(_fragmentCode);
			shaderHandle = std::ref(_fragmentShader);
			oglShaderEnumType = GL_FRAGMENT_SHADER;
		}

		// Create handle in graphics card, put source in, and compile
		shaderHandle.get() = glCreateShader(oglShaderEnumType);
		const char* buffer = shaderBuffer.get().c_str();
		glShaderSource(shaderHandle.get(), 1, &buffer, NULL);
		glCompileShader(shaderHandle.get());

		// Check for compile errors
		GLint compilingSuccessful;
		glGetShaderiv(shaderHandle.get(), GL_COMPILE_STATUS, &compilingSuccessful);
		if(compilingSuccessful != GL_TRUE)
		{
			// Complain
			std::cout << "Error:" << std::endl;
			char errorLog[SFEW_LOG_SIZE];
			glGetShaderInfoLog(shaderHandle.get(), SFEW_LOG_SIZE, NULL, errorLog);
			std::cout << errorLog << std::endl;
			std::cout << "Quitting in 11 seconds..." << std::endl;
			Sleep(11000);
			exit(1);
		}

		// If you're here, everything went successfully
		std::cout << "...success!" << std::endl;
	}

	// Link the vertex and fragment shaders together
	void Shader::linkShaders()
	{
		// Creating the OpenGL shader "program"
		_shaderProgram = glCreateProgram();

		// Add vertex and fragment shaders to program
		glAttachShader(_shaderProgram, _vertexShader);
		glAttachShader(_shaderProgram, _fragmentShader);

		// Hard code fragment shader color output's name for shaders
		glBindFragDataLocation(_shaderProgram, 0, "outColor");

		// Link the shaders
		std::cout << "Linking shaders..." << std::endl;
		glLinkProgram(_shaderProgram);

		// Check status of linking
		GLint linkingSuccessful;
		glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &linkingSuccessful);
		if(linkingSuccessful != GL_TRUE)
		{
			std::cout << "Error:" << std::endl;
			char errorLog[SFEW_LOG_SIZE];
			glGetProgramInfoLog(_shaderProgram, SFEW_LOG_SIZE, NULL, errorLog);
			std::cout << errorLog << std::endl;
			std::cout << "Quitting in 11 seconds..." << std::endl;
			Sleep(11000);
			exit(1);
		}

		// If you're here, everything was successful
		std::cout << "...success!" << std::endl;
		_flaggedAsLinked = true;
	}

} // namespace sfew