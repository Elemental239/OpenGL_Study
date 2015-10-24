// Possible OpenGL tutorials: http://www.learnopengl.com/#!Getting-started/Creating-a-window  - now it is the main course
//							  https://open.gl/
// OpenGL main site links:    https://www.opengl.org/sdk/docs/tutorials/

/* quick and dirty GLSL code loader:
string getGLSLCode(string fname)
{
	string ret;
	ifstream ifs(fname.c_str());
	if(ifs)
	{
		string line;
		while( getline(ifs, line) )
		{
			ret = ret + line + "\n"; 
		}
	ifs.close();
	}
	else
	{
		return "";
	}
	return ret;
}

USAGE:
string source = getGLSLCode("vertexshader.txt");
if (source=="") exit(1);
const GLchar* vertexShaderSource = (GLchar*)source.c_str();
*/

#include "HelloWorldTestWindow.h"
#include "Logger.h"
#include <functional>


#include "glfw-3.1.1/include/GLFW/glfw3.h"

void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // When a user presses the escape key, we set the WindowShouldClose property to true, 
    // closing the application
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    	glfwSetWindowShouldClose(window, GL_TRUE);
}    

CHelloWorldTestWindow::CHelloWorldTestWindow()
{
	MARKER("CHelloWorldTestWindow::CHelloWorldTestWindow()");
}

CHelloWorldTestWindow::~CHelloWorldTestWindow()
{
	MARKER("CHelloWorldTestWindow::~CHelloWorldTestWindow()");
}

void CHelloWorldTestWindow::InitOpenGL()
{
	MARKER("CHelloWorldTestWindow::InitOpenGL()");

	//Init GLFW
	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint (GLFW_SAMPLES, 16);
	glfwSetErrorCallback(error_callback);
	
	CreateNewWindow(1000, 800, "LearnOpenGL");

	// Init GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		LOGE("Failed to initialize GLEW");
	}
}

void CHelloWorldTestWindow::CreateNewWindow(int nWidth, int nHeight, CString strTitle)
{
	MARKER("CHelloWorldTestWindow::CreateNewWindow()");

	m_window = glfwCreateWindow(nWidth, nHeight, strTitle.c_str(), nullptr, nullptr);
	if (m_window == nullptr)
	{
		LOGE("Failed to create GLFW window");
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(m_window);
	
	//Set ViewPort
	glViewport(0, 0, nWidth, nHeight);

	//Set window-specific callback
	glfwSetKeyCallback(m_window, key_callback);
}

void CHelloWorldTestWindow::CreateVertexShader()
{
	MARKER("CHelloWorldTestWindow::CreateVertexShader()");
	
	m_vertexShader = glCreateShader(GL_VERTEX_SHADER);

	std::string vertexShaderSource =
		"#version 330 core\n"
		"layout (location = 0) in vec3 position;\n"
		"void main()\n"
		"{\n"
			"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
		"}";
	const GLchar* GLvertexShaderSource = (GLchar*)vertexShaderSource.c_str();

	glShaderSource(m_vertexShader, 1, &GLvertexShaderSource, NULL);	// Set shader source string
	glCompileShader(m_vertexShader);		// Apply shader to OpenGL

	//Check for shader compilation errors 
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &success);

	if(!success)
	{
		glGetShaderInfoLog(m_vertexShader, 512, NULL, infoLog);
		LOG("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n %s", infoLog);
	}
}

void CHelloWorldTestWindow::CreateFragmentShader()
{
	MARKER("CHelloWorldTestWindow::CreateFragmentShader()");

	m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	std::string fragmentShaderSource =
		"#version 330 core\n"
		"out vec4 color;\n"
		"void main()\n"
		"{"
			"color = vec4(0.8f, 0.2f, 0.2f, 1.0f);\n"
		"}";
	const GLchar* GLfragmentShaderSource = (GLchar*)fragmentShaderSource.c_str();

	glShaderSource(m_fragmentShader, 1, &GLfragmentShaderSource, NULL);
	glCompileShader(m_fragmentShader);

	//Check for shader compilation errors 
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(m_fragmentShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(m_fragmentShader, 512, NULL, infoLog);
		LOG("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n %s", infoLog);
	}
}

void CHelloWorldTestWindow::CreateShaderProgram(GLuint vertexShader, GLuint fragmentShader)
{
	MARKER("CHelloWorldTestWindow::CreateShaderProgram()");

	m_shaderProgram = glCreateProgram();
	glAttachShader(m_shaderProgram, vertexShader);
	glAttachShader(m_shaderProgram, fragmentShader);
	glLinkProgram(m_shaderProgram);

	//Check for errors
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);
		LOG("ERROR::SHADER::FULL::LINKING_FAILED\n %s", infoLog);
	}

	//After linking cleanup
	glDeleteShader(vertexShader);	
	glDeleteShader(fragmentShader);
}

void CHelloWorldTestWindow::CreateMedmLogoObject()
{
	GLfloat vertices[] = {
		 0.50f,  0.25f, 0.0f,  // Top Right			*   *   *
		 0.50f, -0.25f, 0.0f,  // Bottom Right      |-*---*-|
		 0.25f,  0.00f, 0.0f,  // Center Right      *---*---*
		 0.00f,  0.25f, 0.0f,  // Center Top           
		 0.00f, -0.25f, 0.0f,  // Center Bottom       /|\ Y
		-0.25f,  0.00f, 0.0f,  // Center Left          |
		-0.50f,  0.25f, 0.0f,  // Top Left	    	---*---> X
		-0.50f, -0.25f, 0.0f,  // Bottom Left          |
	};

	for (int i = 0; i < 24; i++)
	{
		LOG("vertices[%d] = %f", i, vertices[i]);
		if ((i % 3) == 1)
		{
			vertices[i] += 0.4f;
			LOG("corrected vertices[%d] = %f", i, vertices[i]);
		}
	}

	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 2,   // Right-Right Triangle
		2, 1, 4,   // Right Bottom Triangle
		2, 4, 3,   // Right Center Triangle
		3, 4, 5,   // Left Center Triangle
		5, 4, 7,   // Left Bottom Triangle
		5, 7, 6,   // Left-Left Triangle
	};

	GLuint EBO;
	glGenBuffers(1, &EBO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	GLuint VBO;
	glGenBuffers(1, &VBO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Copy triangle into VBO memory => triangle in graphic card memory

	//Form target VAO
	glGenVertexArrays(1, &m_MedmVAO);
	glBindVertexArray(m_MedmVAO);	//Start work with this object

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	
	glBindVertexArray(0);
}

void CHelloWorldTestWindow::CreateGLObjects()
{
	MARKER("CHelloWorldTestWindow::CreateGLObjects()");

	GLfloat vertices[] = {
		 0.5f,  0.5f, 0.0f,  // Top Right
		 0.5f, -0.5f, 0.0f,  // Bottom Right
		-0.5f, -0.5f, 0.0f,  // Bottom Left
	    -0.5f,  0.5f, 0.0f   // Top Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3,   // First Triangle
		1, 2, 3    // Second Triangle
	};  

	GLuint EBO;
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Create Vertex Buffer
	GLuint VBO;
	glGenBuffers(1, &VBO); //Create a Vertex Buffer Object 
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // Bind VBO to GL_ARRAY_BUFFER type
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Copy triangle into VBO memory => triangle in graphic card memory

	//Tell OpenGL that vertex data is 12 bytes array (3 axes * 4 byte float value size)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Create Vertex Array Object (compound of VBO && Vertex attributes)
	glGenVertexArrays(1, &m_VAO);

	// 1. Bind Vertex Array Object
	glBindVertexArray(m_VAO);

		// 2. Copy our vertices array in a buffer for OpenGL to use
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// 3. Copy our index array in a element buffer for OpenGL to use
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
		// 4. Then set our vertex attributes pointers
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
	
	//5. Unbind the VAO
	glBindVertexArray(0);
}

void CHelloWorldTestWindow::StartRenderCycle()
{
	MARKER("CHelloWorldTestWindow::StartRenderCycle()");

	while(!glfwWindowShouldClose(m_window))
	{
		glfwPollEvents();

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Render();

		glfwSwapBuffers(m_window);
	}

	// End of all
	glfwTerminate();
}

void CHelloWorldTestWindow::Render()
{
	//glDrawArrays(GL_TRIANGLES, 0, 3);

	glUseProgram(m_shaderProgram); // tell OpenGL to use our new shader program
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glBindVertexArray(m_VAO);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(m_MedmVAO);
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void CHelloWorldTestWindow::Draw()
{
	MARKER("CHelloWorldTestWindow::Draw()");

	InitOpenGL();
	CreateVertexShader();
	CreateFragmentShader();
	CreateShaderProgram(m_vertexShader, m_fragmentShader);
	CreateGLObjects();
	CreateMedmLogoObject();

	StartRenderCycle();
}
