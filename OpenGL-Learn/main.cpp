#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <custom/shader.h>
#include "stb_image.h"


// function forward declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
	// set OpenGL version (4.6) and set the profile to 'core'
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1280, 800, "Learn OpenGL", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "failed to create window." << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "failed to initialise GLAD" << std::endl;
		return -1;
	}

	Shader shaderProgram("shader.vs", "shader.fs");

	unsigned int VAO1;
	glGenVertexArrays(1, &VAO1);

	float vertices[] = {
		// position			// colour
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,	// bottom left
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,		// bottom right
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f		// middle
	};

	// initialise the memory buffer that stores the vertices. Array type: GL_ARRAY_BUFFER
	unsigned int VBO1;
	glGenBuffers(1, &VBO1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 1. Bind vertex array object
	glBindVertexArray(VAO1);

	// 2. copy vertices into a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 3. set vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// ------------------------------------
	// TEXTURE CODE
	// ------------------------------------


	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set texture wrapping/filtering options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} 
	else {
		std::cout << "Failed to load texture :)" << std::endl;
	}


	stbi_image_free(data);



	glViewport(0, 0, 1280, 800);

	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// render the triangle
		// -------------------
		shaderProgram.use();

		int vertexOffsetLocation = glGetUniformLocation(shaderProgram.ID, "offset");
		glUniform4f(vertexOffsetLocation, -0.5f, 0.2f, 0.0f, 1.0f);

		glBindVertexArray(VAO1);

		int vertexColorLocation = glGetUniformLocation(shaderProgram.ID, "ourColour");
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) 
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}