#include "GraphicsCtrlr.hpp"
//#include "TextureCtrlr.h"
//#include "GameObjectCtrlr.h"

//#include "GameGeometry.h"

#include <iostream>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

using namespace std;

namespace sfew
{

	// All vertex data for a cube
	GLfloat cubeVertices[] = {
		// X      Y      Z     R     G     B     U     V
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
 		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
	};

	// Element Array: gives each vertex a number identification
	GLuint squareElements[] = {
		0, 1, 2,
		2, 3, 0
	};

	// Game Structures ==========================================

	// Create objects before the main loop
	void GraphicsCtrlr::InitializeGraphics()
	{
		// Print OpenGL version on console
		this->PrintOpenGLVersion();

		// Start GLEW
		this->StartGLEW();

		// Create the VAO, VBO, and EBO
		this->CreateGLBuffers();

		// Create textures
		// Cat texture
		//this->CreateNewTexture(0, "./Images/gameTexture.png", "texTexture");
		//this->SetupTextueProperties(0, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST);
		// Dog texture
		//this->CreateNewTexture(1, "./Images/gameOver.png", "texGameOver");
		//this->SetupTextueProperties(1, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST);


		// Create shader program and link shaders
		std::cout << "Loading Vertex Shader...\n";
		this->LoadShader(GL_VERTEX_SHADER, "./Shaders/firstVert.glsl");
		std::cout << "Loading Fragment Shader...\n";
		this->LoadShader(GL_FRAGMENT_SHADER, "./Shaders/firstFrag.glsl");

		// Create shader program and link shaders
		this->LinkShaders();
		this->FormatAttributeData();
		this->UploadUniformData();
	}

	// The main loop itself
	void GraphicsCtrlr::LoopGraphics()
	{
		// Clear the screen to black
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw all the GameObjects
		//GameObjectCtrlr::GetInstance()->DrawAll();
	}

	// Delete objects after the main loop
	void GraphicsCtrlr::ReleaseGraphics()
	{
		// Detach and delete shaders and shader program
		this->DeleteShaders();

		// Delete textures
		//this->DeleteTextures();

		// Delete VBOs, EBOs, and VAOs
		this->DeleteGLBuffers();
	}

	// Routines ==========================================

	// Constructor
	GraphicsCtrlr::GraphicsCtrlr()
	{
		this->_wasGeometryShaderLoaded = false;

		// Create Texture Controller
		//this->textures = new TextureCtrlr();

		// Enable depth testing by default
		glEnable(GL_DEPTH_TEST);
	}

	// Public singleton instance getter
	GraphicsCtrlr* GraphicsCtrlr::GetInstance()
	{
		return GraphicsCtrlr::privGetInstance();
	}

	// Private singleton handler
	GraphicsCtrlr* GraphicsCtrlr::privGetInstance()
	{
		// Static object only initializes once
		static GraphicsCtrlr graphicsCtrlrInstance;
		return &graphicsCtrlrInstance;
	}

	// Read shader files into memory
	const char* GraphicsCtrlr::loadShaderFile(const char* filePath)
	{
		const char * shaderFileBuffer = NULL;

		std::ifstream inSdrFileStream(filePath);
		if(inSdrFileStream)
		{
			// Get length of shader file by seeking and telling (offset of 0)
			inSdrFileStream.seekg(0, inSdrFileStream.end);
			unsigned long fileLength = (unsigned long) inSdrFileStream.tellg() + 1;
			inSdrFileStream.seekg(0, inSdrFileStream.beg);

			std::cout << "Shader File: Reading " << fileLength << " chars...\n";

			// Read shader file into a memory buffer (array)
			char * inputFileBuffer = new char[fileLength];
			memset(inputFileBuffer, 0, fileLength);
			inSdrFileStream.read(inputFileBuffer, fileLength);
			inputFileBuffer[fileLength-1] = 0;

			// Close file and print status
			if(inputFileBuffer)
			{
				std::cout << "... Read successfully.\n\n";
				std::cout << "---------------------------------\n";
				std::cout << inputFileBuffer << std::endl;
				std::cout << "---------------------------------\n";
				std::cout << std::endl;
				inSdrFileStream.close();
			}
			else
			{
				std::cout << "... Error: Only " << inSdrFileStream.gcount() << " could be read!\n";
				inSdrFileStream.close();
				delete [] inputFileBuffer;
				return NULL;
			}

			// Hand over file contents to a const pointer
			shaderFileBuffer = inputFileBuffer;
			inputFileBuffer = NULL;
		}
		else
		{
			std::cout << "Shader File: Error. Not found!" << std::endl;
			return NULL;
		}

		return shaderFileBuffer;
	}

	// Checks if the shaderType enum if correct
	bool GraphicsCtrlr::isCorrectShaderType(GLenum shaderType)
	{
		if(shaderType == GL_VERTEX_SHADER || shaderType == GL_FRAGMENT_SHADER || shaderType == GL_GEOMETRY_SHADER)
		{
			return true;
		}

		// Invalid shader type
		return false;
	}

	bool GraphicsCtrlr::compileShader(GLenum shaderType, const char* shaderBuffer)
	{
		GLuint* shaderToCompile = NULL;

		// Determine the correct shader ID
		switch (shaderType)
		{
			case GL_VERTEX_SHADER: shaderToCompile = &(this->_vertexShader); break;
			case GL_GEOMETRY_SHADER: shaderToCompile = &(this->_geometryShader); this->_wasGeometryShaderLoaded = true; break;
			case GL_FRAGMENT_SHADER: shaderToCompile = &(this->_fragmentShader); break;
	
		}

		*shaderToCompile = glCreateShader(shaderType);
		glShaderSource(*shaderToCompile, 1, &shaderBuffer, NULL);
		glCompileShader(*shaderToCompile);

		// Check for vertex shader errors
		GLint sdrCompileStatus;
		glGetShaderiv(*shaderToCompile, GL_COMPILE_STATUS, &sdrCompileStatus);
		if(sdrCompileStatus != GL_TRUE)
		{
			std::cout << "Error Compiling:\n";
			char errorLogBuffer[512];
			glGetShaderInfoLog(*shaderToCompile, 512, NULL, errorLogBuffer);
			std::cout << errorLogBuffer << std::endl;
			glDeleteShader(*shaderToCompile);
			*shaderToCompile = 0;	// Zero is an invalid ID
			return false;
		}

		// Everything went well
		shaderToCompile = NULL;
		return true;
	}

	// Prints OpenGL version on console
	void GraphicsCtrlr::PrintOpenGLVersion()
	{
		cout << "OpenGL Version: " << glGetString(GL_VERSION) << endl << endl << endl;
	}

	// Initalizes GLEW
	void GraphicsCtrlr::StartGLEW()
	{
		glewExperimental = GL_TRUE;
		glewInit();
	}

	// Set the width and height of the window
	void GraphicsCtrlr::SetWindowSize(int width, int height)
	{
		this->_winWidth = width;
		this->_winHeight = height;
	}

	// Generates all needed OpenGL buffers (VBOs, VAOs, etc.)
	void GraphicsCtrlr::CreateGLBuffers()
	{
		// Create a Vertex Array Object (VAO) to store the links between 
		// vertex data (in VBOs) and vertex formats (set with glVertexAttribPointer())
		// VAOs don't store vertex data; they need VBOs to reference data
		glGenVertexArrays(1, &(this->_vao));
		glBindVertexArray(this->_vao);


		// Generate GL vertex buffer object (VBOs)
		glGenBuffers(1, &(this->_vbo));

		// Make vertex buffer active by binding it
		glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);

		// Copy triangle vertex data to current active (bound) vertex buffer object (VBO).
		// Static draw indicates that vert data is uploaded once and drawn many times.
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);


		// Create an Element Buffer Object (EBO) out of the element array
		glGenBuffers(1, &(this->_ebo));

		// Make the EBO the active element array
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ebo);

		// Copy element array data into the active EBO
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(squareElements), squareElements, GL_STATIC_DRAW);
	}

	// Free all the created OpenGL buffers (VAOs, VBOs, etc.)
	void GraphicsCtrlr::DeleteGLBuffers()
	{
		glDeleteBuffers(1, &(this->_vbo));
		glDeleteBuffers(1, &(this->_ebo));
		glDeleteVertexArrays(1, &(this->_vao));
	}

	/*
	void GraphicsCtrlr::DeleteTextures()
	{
		delete (this->textures);
	}
	*/

	/*
	// Creates a new texture given the image file into OpenGL
	void GraphicsCtrlr::CreateNewTexture(GLuint textureUnit, const char* textureFilePath, const char* nameInShader)
	{
		this->textures->CreateNewTexture(textureUnit, textureFilePath, nameInShader);
	}

	// Sets up the texture unit's wrapping and min/mag filters
	void GraphicsCtrlr::SetupTextueProperties(GLuint textureUnit, GLenum wrapping, GLenum filtering)
	{
		this->textures->SetupTextureProperties(textureUnit, wrapping, filtering);
	}
	*/
	// Loads and compiles a shader from file given a shader type (GL_VERTEX_SHADER, etc.)
	void GraphicsCtrlr::LoadShader(GLenum shaderType, const char* shaderFilePath)
	{
		// Check if the GLenum is valid (GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER)
		if( ! this->isCorrectShaderType(shaderType))
		{
			std::cout << "Error: GraphicsCtrlr::LoadShader(): Invalid shader type!\n";
			std::cout << "Quiting in 11 seconds...";
			Sleep(11000);
			exit(1);
		}

		// Load the given shader file
		const char * shaderFileBuffer = this->loadShaderFile(shaderFilePath);

		if(shaderFileBuffer == NULL)
		{
			std::cout << "Error: GraphicsCtrlr::LoadShader(): Shader failed to load!\n";
			std::cout << "Quiting in 11 seconds...";
			Sleep(11000);
			delete [] shaderFileBuffer;
			exit(1);
		}

		// Compile the loaded shader file
		bool compileSucceeded = this->compileShader(shaderType, shaderFileBuffer);

		if(!compileSucceeded)
		{
			std::cout << "Error: GraphicsCtrlr::LoadShader(): Shader failed to compile!\n";
			std::cout << "Quiting in 11 seconds...";
			Sleep(11000);
			delete [] shaderFileBuffer;
			exit(1);
		}

		// Delete shader file buffer, not needed anymore
		delete [] shaderFileBuffer;
	}

	// Creates a shader program and links the shaders
	void GraphicsCtrlr::LinkShaders()
	{
		// Create shader program
		_shaderProgram = glCreateProgram();

		// Attach shaders (geometry shader is optional)
		glAttachShader(_shaderProgram, _vertexShader);
		glAttachShader(_shaderProgram, _fragmentShader);
		if(this->_wasGeometryShaderLoaded)
		{
			glAttachShader(_shaderProgram, _geometryShader);
		}

		// Define the output of the fragment shader (not built-in)
		glBindFragDataLocation(_shaderProgram, 0, "outColor");

		// Link the shaders in the shader program
		std::cout << "Linking Shaders...\n";
		glLinkProgram(_shaderProgram);
		GLint progLinkStatus;
		glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &progLinkStatus);
		if(progLinkStatus != GL_TRUE)
		{
			std::cout << "Error Linking:\n";
			char errorLogBuffer[512];
			glGetProgramInfoLog(_shaderProgram, 512, NULL, errorLogBuffer);
			std::cout << errorLogBuffer << std::endl;
			glDeleteProgram(_shaderProgram);
			Sleep(11000);
			exit(1);
		}

		std::cout << "Linking successful.\n";
	}

	// Deletes all shaders and the shader program
	void GraphicsCtrlr::DeleteShaders()
	{
		// Detach shaders from the shader program
		glDetachShader(_shaderProgram, _vertexShader);
		glDeleteShader(_vertexShader);

		// Delete shaders
		glDetachShader(_shaderProgram, _fragmentShader);
		glDeleteShader(_fragmentShader);

		// Also handle the gemoetry shader if loaded
		if(this->_wasGeometryShaderLoaded)
		{
			glDetachShader(_shaderProgram, _geometryShader);
			glDeleteShader(_geometryShader);
		}

		// Delete shader program
		glDeleteProgram(_shaderProgram);
	}


	// Format the inputted vertex attribute data for shaders to use
	void GraphicsCtrlr::FormatAttributeData()
	{
		std::cout << "Formatting Vertex Attributes.\n";

		// Make the current shaders the active shaders
		glUseProgram(_shaderProgram);

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
	}

	// Upload all the uniforms to the GPU for shaders to use
	void GraphicsCtrlr::UploadUniformData()
	{
		std::cout << "Uploading Vertex Uniforms.\n";

		// Make the current shaders the active shaders
		glUseProgram(_shaderProgram);

		// Setup uniform data for shaders
		GLint uniflucScale = glGetUniformLocation(_shaderProgram, "flucScale");
		glUniform1f(uniflucScale, 1.0f);

		// View matrix (Camera transform)
		glm::mat4 view = glm::lookAt(
			glm::vec3(20.0f, 0.0f, 13.0f),	// Camera position
			glm::vec3(0.0f, 0.0f, 13.0f),	// Point centered on screen
			glm::vec3(0.0f, 0.0f, 1.0f)		// Up vector
		);
		GLint uniView = glGetUniformLocation(this->_shaderProgram, "view");
		glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

		// Projection matrix (Camera properties)
		float aspectRatio = (float) this->_winHeight / (float) this->_winHeight;
		glm::mat4 proj = glm::perspective(
			75.0f,							// vertical Field-Of-View (angle)
			aspectRatio,					// aspect ratio
			1.0f,							// near plane
			50.0f							// far plane
		);
		GLint uniProj = glGetUniformLocation(this->_shaderProgram, "proj");
		glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

		/*
		// Setup texture uniform data for every texture that exists
		for(int i=0; i < this->textures->GetNumberOfTextures(); i++)
		{
			const char* textureNameInShader = this->textures->GetTextureName(i);
			glUniform1i(glGetUniformLocation(shaderProgram, textureNameInShader), i);
		}
		*/
	}

	// Getter for shaderProgram
	GLuint GraphicsCtrlr::GetShaderProgramID()
	{
		return this->_shaderProgram;
	}

	// Send a matrix uniform to the shaders
	void GraphicsCtrlr::SetUniform(glm::mat4 matrix, const char* nameInShader)
	{
		GLint uniformLocation = glGetUniformLocation(this->_shaderProgram, nameInShader);
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	// Send a int uniform to the shaders
	void GraphicsCtrlr::SetUniform(int numberValue, const char* nameInShader)
	{
		GLint uniformLocation = glGetUniformLocation(this->_shaderProgram, nameInShader);
		glUniform1i(uniformLocation, numberValue);
	}

	// Send a float uniform to the shaders
	void GraphicsCtrlr::SetUniform(float numberValue, const char* nameInShader)
	{
		GLint uniformLocation = glGetUniformLocation(this->_shaderProgram, nameInShader);
		glUniform1f(uniformLocation, numberValue);
	}

	// Send a vector (of size 3) to the shaders
	void GraphicsCtrlr::SetUniform(glm::vec3 vector, const char* nameInShader)
	{
		GLint uniformLocation = glGetUniformLocation(this->_shaderProgram, nameInShader);
		glUniform3fv(uniformLocation, 1, glm::value_ptr(vector));
	}

	// Send a vector (of size 4) to the shaders
	void GraphicsCtrlr::SetUniform(glm::vec4 vector, const char* nameInShader)
	{
		GLint uniformLocation = glGetUniformLocation(this->_shaderProgram, nameInShader);
		glUniform4fv(uniformLocation, 1, glm::value_ptr(vector));
	}

	// Draw triangles given the number of vertices (doesn't use EBOs)
	void GraphicsCtrlr::DrawTriangles(int numberOfVertices)
	{
		glDrawArrays(GL_TRIANGLES, 0, numberOfVertices);
	}

} // namespace sfew