#include "OpenGL.h"
#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include "ShaderLoader.h"
#include "VAO.h"
#include "VBO.h"

OpenGL::OpenGL()
{
	Window = nullptr;
	shaderProgram = 0;
	VAOID = 0;
	VBOID = 0;

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

}

void OpenGL::Setup()
{
	// Vertices coordinates
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Upper corner
	};

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
	VAO vao = VAO(VAOID);
	VBO vbo = VBO(VBOID, vertices, sizeof(vertices));

	// Make the VAO the current Vertex Array Object by binding it
	vao.Bind();

	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	// Enable the Vertex Attribute so that OpenGL knows to use it
	vao.LinkVBO(vbo, 0);

	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
	vao.Unbind();
	vbo.Unbind();
}

void OpenGL::Update()
{
	// Take care of all GLFW events
	glfwPollEvents();
}

void OpenGL::Render()
{
	// Specify the color of the background
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

	// Clean the back buffer and assign the new color to it
	glClear(GL_COLOR_BUFFER_BIT);

	// Tell OpenGL which Shader Program we want to use
	glUseProgram(shaderProgram);

	// Bind the VAO so OpenGL knows to use it
	glBindVertexArray(VAOID);

	// Draw the triangle using the GL_TRIANGLES primitive
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// Swap the back buffer with the front buffer
	glfwSwapBuffers(Window);
}

void OpenGL::CleanUp()
{
	// Delete all the objects we've created
	glDeleteVertexArrays(1, &VAOID);
	glDeleteBuffers(1, &VBOID);
	glDeleteProgram(shaderProgram);

	// Delete window before ending the program
	glfwDestroyWindow(Window);

	// Terminate GLFW before ending the program
	glfwTerminate();
}