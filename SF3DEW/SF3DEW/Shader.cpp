#include "Shader.hpp"

#include <iostream>
#include <fstream>
#include <functional>	// For reference_wrapper

#define SFEW_LOG_SIZE 512

namespace sfew
{
	// Ctor/Dtor ========================================

	Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) :
		INameable("Unnamed Shader"),
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

		// Format the vertex attribute data sent from VBOs
		formatVertexAttributes();
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

	// Make current active shader for OpenGL
	void Shader::UseShader()
	{
		if (!_flaggedAsLinked)
		{
			// Can't use unlinked shaders
			std::cout << "Warning: Cannot use shader \"" << _name << "\" unlinked." << std::endl;
			return;
		}

		glUseProgram(_shaderProgram);
	}
	
	// STATIC: Assigns no shader to OpenGL rendering
	void Shader::StopUsingShaders()
	{
		glUseProgram(NULL);
	}

	// STATIC: Use vertex attributes to draw 3D
	void Shader::EnableVertexAttributes()
	{
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
	}

	// STATIC: Stop using vertex attributes to draw 2D
	void Shader::DisableVertexAttributes()
	{
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}

	// Does uniform name exist in shader program?
	bool Shader::HasUniform(const std::string& uniformName)
	{
		// Is the shader linked?
		if(!verifyShaderIsLinkedForUniforms())
		{
			return false;
		}

		// Make active shader
		glUseProgram(_shaderProgram);

		// Attempt to get the uniform handle from the name
		GLint uniformHandle = glGetUniformLocation(_shaderProgram, uniformName.c_str());
		
		// Return false if uniform does not exist
		if(uniformHandle == -1)
		{
			return false;
		}

		// The uniform exists
		return true;
	}

	// Uniform Setters =======================================

	// Pass in uniform data to shader
	void Shader::SetUniform(const std::string& uniformName, float x)
	{
		// Get uniform variable handle from graphics card
		if(!verifyUniformLegitimacy(uniformName)) return;
		GLint uniformHandle = glGetUniformLocation(_shaderProgram, uniformName.c_str());

		// Send the uniform value to shader in graphics card, if uniform exists
		glUniform1f(uniformHandle, x);
	}

	void Shader::SetUniform(const std::string& uniformName, float x, float y)
	{
		// Get uniform variable handle from graphics card
		if(!verifyUniformLegitimacy(uniformName)) return;
		GLint uniformHandle = glGetUniformLocation(_shaderProgram, uniformName.c_str());

		// Send the uniform value to shader in graphics card, if uniform exists
		glUniform2f(uniformHandle, x, y);
	}

	void Shader::SetUniform(const std::string& uniformName, float x, float y, float z)
	{
		// Get uniform variable handle from graphics card
		if(!verifyUniformLegitimacy(uniformName)) return;
		GLint uniformHandle = glGetUniformLocation(_shaderProgram, uniformName.c_str());

		// Send the uniform value to shader in graphics card, if uniform exists
		glUniform3f(uniformHandle, x, y, z);
	}

	void Shader::SetUniform(const std::string& uniformName, float x, float y, float z, float w)
	{
		// Get uniform variable handle from graphics card
		if(!verifyUniformLegitimacy(uniformName)) return;
		GLint uniformHandle = glGetUniformLocation(_shaderProgram, uniformName.c_str());

		// Send the uniform value to shader in graphics card, if uniform exists
		glUniform4f(uniformHandle, x, y, z, w);
	}

	void Shader::SetUniform(const std::string& uniformName, Vector2 vector)
	{
		// Get uniform variable handle from graphics card
		if(!verifyUniformLegitimacy(uniformName)) return;
		GLint uniformHandle = glGetUniformLocation(_shaderProgram, uniformName.c_str());

		// Send the uniform value to shader in graphics card, if uniform exists
		glUniform2fv(uniformHandle, 1, glm::value_ptr(vector));
	}

	void Shader::SetUniform(const std::string& uniformName, Vector3 vector)
	{
		// Get uniform variable handle from graphics card
		if(!verifyUniformLegitimacy(uniformName)) return;
		GLint uniformHandle = glGetUniformLocation(_shaderProgram, uniformName.c_str());

		// Send the uniform value to shader in graphics card, if uniform exists
		glUniform3fv(uniformHandle, 1, glm::value_ptr(vector));
	}

	void Shader::SetUniform(const std::string& uniformName, Vector4 vector)
	{
		// Get uniform variable handle from graphics card
		if(!verifyUniformLegitimacy(uniformName)) return;
		GLint uniformHandle = glGetUniformLocation(_shaderProgram, uniformName.c_str());

		// Send the uniform value to shader in graphics card, if uniform exists
		glUniform4fv(uniformHandle, 1, glm::value_ptr(vector));
	}

	void Shader::SetUniform(const std::string& uniformName, Matrix2 matrix)
	{
		// Get uniform variable handle from graphics card
		if(!verifyUniformLegitimacy(uniformName)) return;
		GLint uniformHandle = glGetUniformLocation(_shaderProgram, uniformName.c_str());

		// Send the uniform value to shader in graphics card, if uniform exists
		glUniformMatrix2fv(uniformHandle, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Shader::SetUniform(const std::string& uniformName, Matrix3 matrix)
	{
		// Get uniform variable handle from graphics card
		if(!verifyUniformLegitimacy(uniformName)) return;
		GLint uniformHandle = glGetUniformLocation(_shaderProgram, uniformName.c_str());

		// Send the uniform value to shader in graphics card, if uniform exists
		glUniformMatrix3fv(uniformHandle, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Shader::SetUniform(const std::string& uniformName, Matrix4 matrix)
	{
		// Get uniform variable handle from graphics card
		if(!verifyUniformLegitimacy(uniformName)) return;
		GLint uniformHandle = glGetUniformLocation(_shaderProgram, uniformName.c_str());

		// Send the uniform value to shader in graphics card, if uniform exists
		glUniformMatrix4fv(uniformHandle, 1, GL_FALSE, glm::value_ptr(matrix));
	}


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

	// Format vertex data for shaders to use
	void Shader::formatVertexAttributes()
	{
		// Make current shader the active shader
		UseShader();

		// Format the vertex attribute data for the shaders to process
		GLint posAttrib = glGetAttribLocation(_shaderProgram, "position");
		glEnableVertexAttribArray(posAttrib);
		glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE,
							   8*sizeof(float), 0);

		GLint colAttrib = glGetAttribLocation(_shaderProgram, "color");
		glEnableVertexAttribArray(colAttrib);
		glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE,
							   8*sizeof(float), (void*)(3*sizeof(float)));

		GLint texAttrib = glGetAttribLocation(_shaderProgram, "texcoord");
		glEnableVertexAttribArray(texAttrib);
		glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE,
							   8*sizeof(float), (void*)(6*sizeof(float)));

		// Stop this shader from being the current active
		Shader::StopUsingShaders();
	}

	// Verify shader is linked for uniform assignment
	bool Shader::verifyShaderIsLinkedForUniforms()
	{
		if(!_flaggedAsLinked)
		{
			std::cout << "Warning: Trying to assign a uniform to an unlinked shader!" << std::endl;
			return false;
		}

		return true;
	}

	// Verify that the uniform variable is valid
	bool Shader::verifyUniformLegitimacy(const std::string& uniformName)
	{
		if(!HasUniform(uniformName))
		{
			std::cout << "Warning: Uniform \"" << uniformName << "\" does not exist in shader \"" << _name << "\"!" << std::endl;
			return false;
		}

		return true;
	}

} // namespace sfew