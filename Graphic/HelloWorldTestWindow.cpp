// Possible OpenGL tutorials: http://www.learnopengl.com/#!Getting-started/Creating-a-window  - now it is the main course
//							  https://open.gl/
// OpenGL main site links:    https://www.opengl.org/sdk/docs/tutorials/
//
// GLFW documentation: http://www.glfw.org/docs/latest/window.html

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

//void CHelloWorldTestWindow::CreateVertexShader()
//{
//	//MARKER("CHelloWorldTestWindow::CreateVertexShader()");
//	//
//	//m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
//
//	//std::string vertexShaderSource =
//	//	"#version 330 core\n"
//	//	"layout (location = 0) in vec3 position;\n"
//	//	"void main()\n"
//	//	"{\n"
//	//		"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
//	//	"}";
//	//const GLchar* GLvertexShaderSource = (GLchar*)vertexShaderSource.c_str();
//
//	//glShaderSource(m_vertexShader, 1, &GLvertexShaderSource, NULL);	// Set shader source string
//	//glCompileShader(m_vertexShader);		// Apply shader to OpenGL
//
//	////Check for shader compilation errors 
//	//GLint success;
//	//GLchar infoLog[512];
//	//glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &success);
//
//	//if(!success)
//	//{
//	//	glGetShaderInfoLog(m_vertexShader, 512, NULL, infoLog);
//	//	LOG("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n %s", infoLog);
//	//}
//}
//
//void CHelloWorldTestWindow::CreateFragmentShader()
//{
//	//MARKER("CHelloWorldTestWindow::CreateFragmentShader()");
//
//	//m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//
//	//std::string fragmentShaderSource =
//	//	"#version 330 core\n"
//	//	"out vec4 color;\n"
//	//	"void main()\n"
//	//	"{"
//	//		"color = vec4(0.8f, 0.2f, 0.2f, 1.0f);\n"
//	//	"}";
//	//const GLchar* GLfragmentShaderSource = (GLchar*)fragmentShaderSource.c_str();
//
//	//glShaderSource(m_fragmentShader, 1, &GLfragmentShaderSource, NULL);
//	//glCompileShader(m_fragmentShader);
//
//	////Check for shader compilation errors 
//	//GLint success;
//	//GLchar infoLog[512];
//	//glGetShaderiv(m_fragmentShader, GL_COMPILE_STATUS, &success);
//	//if(!success)
//	//{
//	//	glGetShaderInfoLog(m_fragmentShader, 512, NULL, infoLog);
//	//	LOG("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n %s", infoLog);
//	//}
//}

void CHelloWorldTestWindow::CreateShaderProgram()
{
	MARKER("CHelloWorldTestWindow::CreateShaderProgram()");

	CString vertexShaderSource =
		"#version 330 core\n"
		"layout (location = 0) in vec3 position;\n"
		"layout (location = 1) in vec3 colour;\n"
		"\n"
		"out vec3 vertexColour;"
		"\n"
		"void main()\n"
		"{\n"
			"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
			"vertexColour = colour;\n"
		"}";

	CString fragmentShaderSource =
		"#version 330 core\n"
		"in vec3 vertexColour;"
		"out vec4 color;\n"
		"void main()\n"
		"{"
			"color = vec4(vertexColour, 1.0f);\n"
		"}";

	CString fragmentShaderSourceFixedColourBlue =
		"#version 330 core\n"
		"in vec3 vertexColour;"
		"out vec4 color;\n"
		"void main()\n"
		"{"
			"color = vec4(0.1f, 0.1f, 0.8f, 1.0f);\n"
		"}";

	{
		CVertexShader vertexShader(vertexShaderSource);
		CFragmentShader fragmentShader(fragmentShaderSource);
		m_shaderProgram = CShaderProgram(vertexShader, fragmentShader);
	}

	{
		CVertexShader vertexShader(vertexShaderSource);
		CFragmentShader fragmentShader(fragmentShaderSourceFixedColourBlue);
		m_shaderProgramFixedColorBlue = CShaderProgram(vertexShader, fragmentShader);
	}
}

void CHelloWorldTestWindow::CreateMedmLogo18Vertex(float fHorizontalShift, float fVerticalShift, GLuint& VAO)
{
	//     *   *   *
	//     |-*---*-|
	//     *---*---*

		GLfloat vertices[] = {
		//Coordinates		  //Colors
		 0.50f,  0.25f, 0.0f, IntColorPart2Float(173), IntColorPart2Float(23), IntColorPart2Float(29), // Top Right
		 0.50f, -0.25f, 0.0f, IntColorPart2Float(173), IntColorPart2Float(23), IntColorPart2Float(29), // Bottom Right
		 0.25f,  0.00f, 0.0f, IntColorPart2Float(173), IntColorPart2Float(23), IntColorPart2Float(29), // Center Right

		 0.25f,  0.00f, 0.0f, IntColorPart2Float(117), IntColorPart2Float(2), IntColorPart2Float(3), // Center Right
		 0.50f, -0.25f, 0.0f, IntColorPart2Float(117), IntColorPart2Float(2), IntColorPart2Float(3), // Bottom Right
		 0.00f, -0.25f, 0.0f, IntColorPart2Float(117), IntColorPart2Float(2), IntColorPart2Float(3), // Center Bottom

		 0.25f,  0.00f, 0.0f, IntColorPart2Float(173), IntColorPart2Float(23), IntColorPart2Float(29), // Center Right
		 0.00f, -0.25f, 0.0f, IntColorPart2Float(173), IntColorPart2Float(23), IntColorPart2Float(29), // Center Bottom
		 0.00f,  0.25f, 0.0f, IntColorPart2Float(173), IntColorPart2Float(23), IntColorPart2Float(29), // Center Top

		 0.00f,  0.25f, 0.0f, IntColorPart2Float(202), IntColorPart2Float(22), IntColorPart2Float( 36), // Center Top
		 0.00f, -0.25f, 0.0f, IntColorPart2Float(202), IntColorPart2Float(22), IntColorPart2Float( 36), // Center Bottom
		-0.25f,  0.00f, 0.0f, IntColorPart2Float(202), IntColorPart2Float(22), IntColorPart2Float( 36), // Center Left

		-0.25f,  0.00f, 0.0f, IntColorPart2Float(173), IntColorPart2Float(8), IntColorPart2Float( 14), // Center Left
		 0.00f, -0.25f, 0.0f, IntColorPart2Float(173), IntColorPart2Float(8), IntColorPart2Float( 14), // Center Bottom
		-0.50f, -0.25f, 0.0f, IntColorPart2Float(173), IntColorPart2Float(8), IntColorPart2Float( 14), // Bottom Left

		-0.25f,  0.00f, 0.0f, IntColorPart2Float(218), IntColorPart2Float(91), IntColorPart2Float(101), // Center Left
		-0.50f, -0.25f, 0.0f, IntColorPart2Float(218), IntColorPart2Float(91), IntColorPart2Float(101), // Bottom Left
		-0.50f,  0.25f, 0.0f, IntColorPart2Float(218), IntColorPart2Float(91), IntColorPart2Float(101)  // Top Left
	};

	for (int i = 0; i < 48; i++)
	{
		if ((i % 6) == 0)
		{
			vertices[i] += fHorizontalShift;
		} 
		else if ((i % 6) == 1)
		{
			vertices[i] += fVerticalShift;
		}
	}

	GLuint indices[] = {  // Note that we start from 0!
		 0,  1,  2,   // Right-Right Triangle
		 3,  4,  5,   // Right Bottom Triangle
		 6,  7,  8,   // Right Center Triangle
		 9, 10, 11,   // Left Center Triangle
		12, 13, 14,   // Left Bottom Triangle
		15, 16, 17    // Left-Left Triangle
	};

	GLuint EBO;
	glGenBuffers(1, &EBO);

	GLuint VBO;
	glGenBuffers(1, &VBO);

	//Form target VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);	//Start work with this object

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	
	glBindVertexArray(0);
}

void CHelloWorldTestWindow::CreateMedmLogoObject(float fHorizontalShift, float fVerticalShift, GLuint& VAO)
{
	GLfloat vertices[] = {
		//Coordinates		  //Colors
		 0.50f,  0.25f, 0.0f, 0.8f, 0.2f, 0.2f, // Top Right		 *   *   *
		 0.50f, -0.25f, 0.0f, 0.8f, 0.2f, 0.2f, // Bottom Right      |-*---*-|
		 0.25f,  0.00f, 0.0f, 0.8f, 0.2f, 0.2f, // Center Right      *---*---*
		 0.00f,  0.25f, 0.0f, 0.8f, 0.2f, 0.2f, // Center Top           
		 0.00f, -0.25f, 0.0f, 0.8f, 0.2f, 0.2f, // Center Bottom       /|\ Y
		-0.25f,  0.00f, 0.0f, 0.8f, 0.2f, 0.2f, // Center Left          |
		-0.50f,  0.25f, 0.0f, 0.8f, 0.2f, 0.2f, // Top Left	      	 ---*---> X
		-0.50f, -0.25f, 0.0f, 0.8f, 0.2f, 0.2f, // Bottom Left          |
	};

	for (int i = 0; i < 48; i++)
	{
		if ((i % 6) == 0)
		{
			vertices[i] += fHorizontalShift;
		} 
		else if ((i % 6) == 1)
		{
			vertices[i] += fVerticalShift;
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
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);	//Start work with this object

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	
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
	m_shaderProgram.Use();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	/*glBindVertexArray(m_MedmVAO);
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);	// = 8 * 3
	glBindVertexArray(0);

	m_shaderProgramFixedColorBlue.Use();

	glBindVertexArray(m_MedmVAOConstantBlue);
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);*/

	glBindVertexArray(m_MedmVAO18Vertex);
	glDrawElements(GL_TRIANGLES, 18*3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void CHelloWorldTestWindow::Draw()
{
	MARKER("CHelloWorldTestWindow::Draw()");

	InitOpenGL();
	//CreateVertexShader();
	//CreateFragmentShader();
	CreateShaderProgram(/*m_vertexShader, m_fragmentShader*/);
	CreateGLObjects();
	CreateMedmLogoObject(0.0f, 0.4f, m_MedmVAO);
	CreateMedmLogoObject(0.2f, 0.0f, m_MedmVAOConstantBlue);
	CreateMedmLogo18Vertex(0.0f, 0.0f, m_MedmVAO18Vertex);

	StartRenderCycle();
}

float CHelloWorldTestWindow::IntColorPart2Float(int nColor)
{
	return (1.0f * nColor) / 0xFF;
}
