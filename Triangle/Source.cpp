#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include "ShaderLoader.h"

void Setup();
void Update();
void Render();
void CleanUp();

// Create an GLFW controlled context window
GLFWwindow* Window = nullptr;

// Shader Program Reference
GLuint shaderProgram;

// Create reference containers for the Vartex Array Object and the Vertex Buffer Object
GLuint VAO, VBO;

// Vertices coordinates
GLfloat vertices[] =
{
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Upper corner
};

int main()
{
	// Setup the initial elements of the program
	Setup();

	// Main loop
	while (glfwWindowShouldClose(Window) == false)
	{
		// Updates all objects and run the processes
		Update();

		// Render all the objects
		Render();
	}

	// Cleaning up objects and windows
	CleanUp();
	return 0;
}

// Setup the initial elements of the program
void Setup()
{

	// Initializing GLFW and setting the version to 4.6 with only Core functionality available
	glfwInit();

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	Window = glfwCreateWindow(800, 800, "First OpenGL Window", NULL, NULL);
	if (Window == NULL)
	{
		std::cout << "GLFW failed to initialize properly. Terminating program." << std::endl;
		system("pause");
		glfwTerminate();
		return;
	}glfwMakeContextCurrent(Window);

	// Initializing GLEW
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
	}
	std::cerr << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;

	// Set the color of the window for when the buffer is cleared
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	// Maps the range of window size to ndc (-1 -> to 1)
	glViewport(0, 0, 800, 800);

	GLuint shaderProgram = ShaderLoader::CreateProgram("Resources/Shaders/FixedTriangle.vs", "Resources/Shaders/FixedColor.fs");

	// Generate the VAO and VBO with only 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(VAO);

	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// Enable the Vertex Attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(0);

	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

// Renders all the objects
void Render()
{
	// Specify the color of the background
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

	// Clean the back buffer and assign the new color to it
	glClear(GL_COLOR_BUFFER_BIT);

	// Tell OpenGL which Shader Program we want to use
	glUseProgram(shaderProgram);

	// Bind the VAO so OpenGL knows to use it
	glBindVertexArray(VAO);

	// Draw the triangle using the GL_TRIANGLES primitive
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// Swap the back buffer with the front buffer
	glfwSwapBuffers(Window);

}

// Update all objects and run the processes
void Update()
{
	// Take care of all GLFW events
	glfwPollEvents();
}

void CleanUp()
{
	// Delete all the objects we've created
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	// Delete window before ending the program
	glfwDestroyWindow(Window);

	// Terminate GLFW before ending the program
	glfwTerminate();
}