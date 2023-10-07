#include <glew.h>
#include <glfw3.h>
#include <iostream>

void InitialSetup();
void Update();
void Render();

// Create an GLFW controlled context window
GLFWwindow* Window = nullptr;

int main()
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
		return -1;
	}glfwMakeContextCurrent(Window);

	// Setup the initial elements of the program
	InitialSetup();

	// Main loop
	while (glfwWindowShouldClose(Window) == false)
	{
		// Updates all objects and run the processes
		Update();

		// Render all the objects
		Render();
	}

	// Ensuring correct shutdown of GLFW
	glfwTerminate();
	return 0;
}

// Setup the initial elements of the program
void InitialSetup()
{
	// Set the color of the window for when the buffer is cleared
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	// Maps the range of window size to ndc (-1 -> to 1)
	glViewport(0, 0, 800, 800);
}

// Renders all the objects
void Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(Window);
}

// Update all objects and run the processes
void Update()
{
	glfwPollEvents();
}