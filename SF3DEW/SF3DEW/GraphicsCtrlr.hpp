// Graphics Controller (GraphicsCtrlr)
// Helps delegate OpenGL tasks
//
// Written by Jibran Syed (4-3-2014)
// Stack-allocated singleton from Edward Keenan

#ifndef GRAPHICS_CTRLR_H
#define GRAPHICS_CTRLR_H

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include "LinearAlgebraTypes.hpp"
#include "Shader.hpp"

namespace sfew
{
	//class TextureCtrlr;

	class GraphicsCtrlr
	{
	public:
		// Singleton Access ===============

		static GraphicsCtrlr* GetInstance();		// Public singleton instance getter

		// Game Structures ================

		void InitializeGraphics();					// Create objects before the main loop
		void LoopGraphics();						// The main loop itself
		void ReleaseGraphics();						// Delete objects after the main loop

		// Routines =======================

		void PrintOpenGLVersion();					// Prints OpenGL version on console
		void StartGLEW();							// Initializes GLEW
		void SetWindowSize(int width, int height);	// Set the width and height of the window
		void CreateGLBuffers();						// Generates all needed OpenGL buffers (VAOs, VBOs, etc.)
		void DeleteGLBuffers();						// Free all the created OpenGL buffers (VAOs, VBOs, etc.)
		//void DeleteTextures();						// Deletes all textures

		// Creates a new texture given the image file into OpenGL
		//void CreateNewTexture(GLuint textureUnit, const char* textureFilePath, const char* nameInShader);

		// Sets up the texture unit's wrapping and min/mag filters
		//void SetupTextueProperties(GLuint textureUnit, GLenum wrapping, GLenum filtering);

		// Loads and compiles a shader from file given a shader type (GL_VERTEX_SHADER, etc.)
		void LoadShader(GLenum shaderType, const char* shaderFilePath);	

		void LinkShaders();							// Creates a shader program and links the shaders
		void DeleteShaders();						// Deletes all shaders and the shader program
		void FormatAttributeData();					// Format the inputted vertex attribute data for shaders to use
		void UploadUniformData();					// Upload all the uniforms to the GPU for shaders to use
		GLuint GetShaderProgramID();				// Getter for shaderProgram

		// Send a matrix uniform to the shaders
		void SetUniform(glm::mat4 matrix, const char* nameInShader);

		// Send a int uniform to the shaders
		void SetUniform(int numberValue, const char* nameInShader);

		// Send a float uniform to the shaders
		void SetUniform(float numberValue, const char* nameInShader);

		// Send a vector (of size 3) to the shaders
		void SetUniform(glm::vec3 vector, const char* nameInShader);

		// Send a vector (of size 4) to the shaders
		void SetUniform(glm::vec4 vector, const char* nameInShader);

		// Draw triangles given the number of vertices (doesn't use EBOs)
		void DrawTriangles(int numberOfVertices);

	private:

		// Singleton Access ===============

		static GraphicsCtrlr* privGetInstance();	// Private singleton handler
		GraphicsCtrlr();							// Private constructor

		// Helpers ========================

		const char* loadShaderFile(const char* filePath);	// Read shader files into memory
		bool isCorrectShaderType(GLenum shaderType);		// Checks if the shaderType enum is correct
		bool compileShader(GLenum shaderType, const char* shaderBuffer);	// Compiles shader of given type

		// Housekeeping ===================

		bool _wasGeometryShaderLoaded;				// Flag to indicate if geometry shaders were used or not.

		// Data ===========================

		//TextureCtrlr* _textures;						// All the textures managed by an object
	
		int _winWidth;								// Width of the window in pixels
		int _winHeight;								// Height of the window in pixels
		GLuint _shaderProgram;						// The vertex and fragment shader combined into a program
		GLuint _vertexShader;						// The shader that processes vertices
		GLuint _fragmentShader;						// The shader that processes pixels (fragments)
		GLuint _geometryShader;						// The shader that processes geometry assembled from verts
		GLuint _vbo;									// Vertex Buffer Objects - point to data in graphics card
		GLuint _ebo;									// Element Buffer Object - gives each vertex a number identification
		GLuint _vao;									// Vertex Array Object - stores the links between vertex data and formats
													// Vertex data is set in VBOs and vertex formats are set with glVertexAttribPointer()
													// VAOs don't store vertex data; they need VBOs to reference data
	
	};

} // namespace sfew

#endif