#pragma once
#include <glew.h>
#include <glfw3.h>

class OpenGL
{
public:
	OpenGL();

	void Update();
	void Render();
	void CleanUp();

private:	
	// Create an GLFW controlled context window
	class GLFWwindow* Window;

	// Shader Program Reference
	GLuint shaderProgram;

	// Create reference containers for the Vartex Array Object and the Vertex Buffer Object
	GLuint VAOID;
	GLuint VBOID;

};

