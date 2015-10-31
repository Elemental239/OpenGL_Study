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
#include "Globals.h"

#include "glfw-3.1.1/include/GLFW/glfw3.h"
#include "OpenGL.h"

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

	if (GLFW_KEY_UP == key && (GLFW_PRESS == action || GLFW_REPEAT == action))
	{
		CGlobals::Instance().m_spHelloWorldTestWindow->ChangeTextureMixValue(0.1f);
	}

	if (GLFW_KEY_DOWN == key && (GLFW_PRESS == action || GLFW_REPEAT == action))
	{
		CGlobals::Instance().m_spHelloWorldTestWindow->ChangeTextureMixValue(-0.1f);
	}

	LOG("key_callback key = %d and action = %d", key, action);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

CHelloWorldTestWindow::CHelloWorldTestWindow() : m_fTexturesMixValue(0.2f)
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
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 16);

	glfwSetErrorCallback(error_callback);
	
	CreateNewWindow(m_window, 1000, 800, "LearnOpenGL");

	// Init GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		LOGE("Failed to initialize GLEW");
	}
}

void CHelloWorldTestWindow::CreateNewWindow(GLFWwindow*& pTargetWindow, int nWidth, int nHeight, CString strTitle)
{
	MARKER("CHelloWorldTestWindow::CreateNewWindow()");

	pTargetWindow = glfwCreateWindow(nWidth, nHeight, strTitle.c_str(), nullptr, nullptr);
	if (pTargetWindow == nullptr)
	{
		LOGE("Failed to create GLFW window");
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(pTargetWindow);
	
	//Set ViewPort
	glViewport(0, 0, nWidth, nHeight);

	//Set window-specific callback
	glfwSetKeyCallback(pTargetWindow, key_callback);
	glfwSetFramebufferSizeCallback(pTargetWindow, framebuffer_size_callback);
}

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

	CString vertexShaderSourceWithTexture =
		"#version 330 core\n"
		"layout (location = 0) in vec3 position;\n"
		"layout (location = 1) in vec3 colour;\n"
		"layout (location = 2) in vec2 textureCoord;\n"
		"\n"
		"out vec3 vertexColour;\n"
		"out vec2 TexCoord;\n"
		"\n"
		"void main()\n"
		"{\n"
			"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
			"vertexColour = colour;\n"
			"TexCoord = textureCoord;"
		"}";

	CString fragmentShaderSourceWithTexture =
		"#version 330 core\n"
		"in vec3 vertexColour;\n"
		"in vec2 TexCoord;\n"
		"out vec4 color;\n"
		"\n"
		"uniform sampler2D inputTexture;\n"
		"uniform sampler2D inputTexture2;\n"
		"\n"
		"uniform float mixValue;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	//color = texture(inputTexture, TexCoord) * vec4(vertexColour, 1.0f);\n"
		"	color = mix(texture(inputTexture, TexCoord / 2), texture(inputTexture2, TexCoord), mixValue);"
		"}";

	{
		CVertexShader vertexShader(vertexShaderSource);
		CFragmentShader fragmentShader(fragmentShaderSource);
		m_shaderProgram = CShaderProgram(vertexShader, fragmentShader);
	}

	{
		CVertexShader vertexShader(vertexShaderSourceWithTexture);
		CFragmentShader fragmentShader(fragmentShaderSourceWithTexture);
		m_shaderProgramWithTexture = CShaderProgram(vertexShader, fragmentShader);
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

	for (int i = 0; i < 3*6*6; i++)
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

void CHelloWorldTestWindow::CreateGLObjects()
{
	MARKER("CHelloWorldTestWindow::CreateGLObjects()");

	//GLfloat vertices[] = {
	//	-0.5f, -0.5f, 0.0f, 0.1f,  0.1f, 0.8f, // Bottom Left
	//	 0.5f, -0.5f, 0.0f, 0.1f,  0.8f, 0.1f, // Bottom Right
	//	 0.0f,  0.5f, 0.0f, 0.8f,  0.1f, 0.1f, // Top
	//};

	//GLuint indices[] = {  // Note that we start from 0!
	//	0, 1, 2
	//};

	//GLfloat texCoords[] = {		// NB! Texture coordinate system starts from left bottom corner for right and top, all ranges are [0..1]
	//	0.0f, 0.0f,  // Lower-left corner  
	//	1.0f, 0.0f,  // Lower-right corner
	//	0.5f, 1.0f   // Top-center corner
	//};

	GLfloat vertices[] = {
		// Positions          // Colors           // Texture Coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f,   // Top Right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f,   // Bottom Right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Bottom Left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f    // Top Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3,
		1, 2, 3,
	};


	GLuint EBO;
	glGenBuffers(1, &EBO);

	GLuint VBO;
	glGenBuffers(1, &VBO); //Create a Vertex Buffer Object 

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
	
		// Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		// Color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		//Texture attribute
		glVertexAttribPointer(2, 2, GL_FLOAT,GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
	
	//5. Unbind the VAO
	glBindVertexArray(0);

    // Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);	// GL_CLAMP_TOEDGE, GL_CLAMP_TO_BORDER, GL_REPEAT, GL_MIRRORED_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Load image, create texture and generate mipmaps

	// Load and create a texture
	glGenTextures(1, &m_texture);
	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
	int width, height;
    unsigned char* image = SOIL_load_image(".//..//..//Resources//Textures//wooden_container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	glGenTextures(1, &m_texture2);
	glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_texture2); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
	/*int */width, height;
    /*unsigned char**/ image = SOIL_load_image(".//..//..//Resources//Textures//awesomeface.png", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
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
	glDeleteVertexArrays(1, &m_VAO);
	glfwTerminate();
}

void CHelloWorldTestWindow::Render()
{
	m_shaderProgramWithTexture.Use();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	m_shaderProgramWithTexture.SetUniform("inputTexture", 0);
	
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_texture2);
	m_shaderProgramWithTexture.SetUniform("inputTexture2", 1);

	m_shaderProgramWithTexture.SetUniform("mixValue", m_fTexturesMixValue);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	/*glBindVertexArray(m_MedmVAO);
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);	// = 8 * 3
	glBindVertexArray(0);

	/*glBindVertexArray(m_MedmVAO18Vertex);
	glDrawElements(GL_TRIANGLES, 18*3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);*/

	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void CHelloWorldTestWindow::Draw()
{
	MARKER("CHelloWorldTestWindow::Draw()");

	InitOpenGL();
	CreateShaderProgram();
	CreateGLObjects();
	//CreateMedmLogoObject(0.0f, 0.4f, m_MedmVAO);
	//CreateMedmLogoObject(0.2f, 0.0f, m_MedmVAOConstantBlue);
	//CreateMedmLogo18Vertex(0.0f, 0.0f, m_MedmVAO18Vertex); //40 65

	StartRenderCycle();
}

float CHelloWorldTestWindow::IntColorPart2Float(int nColor)
{
	return (1.0f * nColor) / 0xFF;
}
