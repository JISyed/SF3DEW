#include <GL/glew.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>				// For ifstream
#include <iostream>				// For cout
#include <string>

const char* loadShaderFile(const char* filePath);

int main()
{
	sf::Window window(sf::VideoMode(800, 600), "Hello Luka", sf::Style::Close | sf::Style::Titlebar);
	window.setVerticalSyncEnabled(true);

	glewExperimental = GL_TRUE;
	glewInit();

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);

	float vertices[] = {
		 0.0f,  0.5f, // Vertex 1 (X, Y)
		 0.5f, -0.5f, // Vertex 2 (X, Y)
		-0.5f, -0.5f  // Vertex 3 (X, Y)
	};

	GLuint vbo;
	glGenBuffers(1, &vbo); // Generate 1 buffer

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	std::string vertexShaderSource(loadShaderFile("./Shaders/basic.vert"));
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* vss = vertexShaderSource.c_str();
	glShaderSource(vertexShader, 1, &vss, NULL);

	bool isRunning = true;
	while(isRunning)
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			switch(event.type)
			{
			case sf::Event::Closed:
				isRunning = false; break;
			case sf::Event::KeyPressed:
				if(event.key.code == sf::Keyboard::Escape) isRunning = false; break;
			default:
				break;
			}
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		window.display();
	}

	return 0;
}

// Read shader files into memory
const char* loadShaderFile(const char* filePath)
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