//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
//
//// source code for fragment and vertex shaders (stored here for simplicity)
//const char* vertexShaderSource = "#version 460 core\n"
//"layout (location = 0) in vec3 aPos;\n"
//"out vec4 vertexColor;" // specify a colour output to the fragment shader
//"void main()\n"
//"{\n"
//"   gl_Position = vec4(aPos, 1.0);\n"
//"	vertexColor = vec4(0.5f, 0.0f, 0.0f, 1.0f);\n"
//"}\0";
//
//const char* fragmentShaderSource = "#version 460 core\n"
//"out vec4 FragColor;\n"
//"uniform vec4 ourColour;\n"
//"void main()\n"
//"{\n"
//"   FragColor = ourColour;\n"
//"}\n\0";
//
//const char* vertexShaderSource2 = "#version 460 core\n"
//"layout (location = 0) in vec3 aPos;\n"
//"void main()\n"
//"{\n"
//"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//"}\0";
//
//const char* fragmentShaderSource2 = "#version 460 core\n"
//"out vec4 FragColor;\n"
//"void main()\n"
//"{\n"
//"	FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
//"}\n\0";
//
//
//// function forward declarations
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow* window);
//
//int main()
//{
//	// set OpenGL version (4.6) and set the profile to 'core'
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	GLFWwindow* window = glfwCreateWindow(1280, 800, "Learn OpenGL", NULL, NULL);
//
//	if (window == NULL)
//	{
//		std::cout << "failed to create window." << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//
//	glfwMakeContextCurrent(window);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "failed to initialise GLAD" << std::endl;
//		return -1;
//	}
//
//	// build and compile shader program
//	// initialise a vertex shader
//	// vertex shader is compiled at runtime from source code
//	// in this basic case, we store the source code as a char* above main. As such, we pass NULL into the source code argument
//	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//	glCompileShader(vertexShader);
//
//	// verify that the vertex shader was created successfully. 
//	int success;
//	char infoLog[512];
//	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//
//	if (!success)
//	{
//		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::VERTEX::COMPILATION::FAILED" << infoLog << std::endl;
//	}
//
//	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//	glCompileShader(fragmentShader);
//
//	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//	if (!success)
//	{
//		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION::FAILED" << infoLog << std::endl;
//	}
//
//	unsigned int shaderProgram = glCreateProgram();
//	glAttachShader(shaderProgram, vertexShader);
//	glAttachShader(shaderProgram, fragmentShader);
//	glLinkProgram(shaderProgram);
//
//	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//	if (!success)
//	{
//		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION::FAILED" << infoLog << std::endl;
//	}
//
//	glUseProgram(shaderProgram);
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//
//
//	// create the second shader program to render shapes in a lovely yellow colouration
//	unsigned int vertexShader2 = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vertexShader2, 1, &vertexShaderSource2, NULL);
//	glCompileShader(vertexShader2);
//
//	glGetShaderiv(vertexShader2, GL_COMPILE_STATUS, &success);
//
//	if (!success)
//	{
//		glGetShaderInfoLog(vertexShader2, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::VERTEX::COMPILATION::FAILED" << infoLog << std::endl;
//	}
//
//	unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
//	glCompileShader(fragmentShader2);
//
//	glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
//	if (!success)
//	{
//		glGetShaderInfoLog(fragmentShader2, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION::FAILED" << infoLog << std::endl;
//	}
//
//	unsigned int shaderProgram2 = glCreateProgram();
//	glAttachShader(shaderProgram2, vertexShader2);
//	glAttachShader(shaderProgram2, fragmentShader2);
//	glLinkProgram(shaderProgram2);
//
//	glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
//	if (!success)
//	{
//		glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION::FAILED" << infoLog << std::endl;
//	}
//
//	glUseProgram(shaderProgram2);
//	glDeleteShader(vertexShader2);
//	glDeleteShader(fragmentShader2);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	unsigned int VAO1, VAO2;
//	glGenVertexArrays(1, &VAO1);
//	glGenVertexArrays(1, &VAO2);
//
//
//
//	// set up vertex data and buffer(s) and configure vertex attributes
//	// equilateral triangle vertices
//	//float vertices[] = {
//	//-0.5f, -0.5f, 0.0f,	// bottom left
//	//0.5f, -0.5f, 0.0f,	// bottom right
//	//-0.5f, 0.5f, 0.0f,	// top left
//	//0.5f, 0.5f, 0.0f	// top right
//	//};
//	float vertices1[] = {
//		// triangle 1
//		-0.8f, 0.0f, 0.0f,	// bottom left
//		-0.4f, 0.0f, 0.0f,	// bottom right
//		-0.6f, 0.2f, 0.0f,	// centre
//	};
//
//	float vertices2[] = {
//		// triangle 2
//		0.4f, 0.0f, 0.0f,
//		0.8f, 0.0f, 0.0f,
//		0.6f, 0.2f, 0.0f
//	};
//
//	unsigned int triangles[] = {
//		0, 1, 2,
//		3, 4, 5,
//	};
//
//
//
//	// initialise the memory buffer that stores the vertices. Array type: GL_ARRAY_BUFFER
//	unsigned int VBO1;
//	glGenBuffers(1, &VBO1);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
//
//	unsigned int VBO2;
//	glGenBuffers(1, &VBO2);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
//
//	// 1. Bind vertex array object
//	glBindVertexArray(VAO1);
//
//	// 2. copy vertices into a buffer for OpenGL to use
//	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
//
//	// 3. set vertex attributes pointers
//	glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	glBindVertexArray(VAO2);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//
//	//unsigned int EBO;
//	//glGenBuffers(1, &EBO);
//
//	//// 3 copy indices into a buffer that OpenGL can use
//	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triangles), triangles, GL_STATIC_DRAW);
//	////glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//	glViewport(0, 0, 1280, 800);
//
//	while (!glfwWindowShouldClose(window))
//	{
//		processInput(window);
//
//		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		glUseProgram(shaderProgram);
//		glBindVertexArray(VAO1);
//		float timeValue = glfwGetTime();
//		float greenValue = sin(timeValue) / 2.0f + 0.5f;
//		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColour");
//		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//
//		glUseProgram(shaderProgram2);
//		glBindVertexArray(VAO2);
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//		glBindVertexArray(0);
//
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//	return 0;
//}
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	glViewport(0, 0, width, height);
//}
//
//void processInput(GLFWwindow* window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//	{
//		glfwSetWindowShouldClose(window, true);
//	}
//}