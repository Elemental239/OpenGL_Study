#include <iostream>
#include <windows.h>
#include <glut.h>
#include "Logger.h"
#include "UtilityMacros.h"
#include <Globals.h>

GLenum g_OpenGLError;

#define OPENGL_CALL(expression) { expression; \
    if ((g_OpenGLError = glGetError()) != GL_NO_ERROR) \
      LOG_ERROR("OpenGL expression \"" #expression "\" error 0x%X", (unsigned)g_OpenGLError); }

#define OPENGL_CHECK_FOR_ERRORS() if ((g_OpenGLError = glGetError()) != GL_NO_ERROR) LOGE("OpenGL error 0x%X\n", (unsigned)g_OpenGLError);

void renderScene(void) 
{
 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
	glBegin(GL_TRIANGLES);
		glVertex3f(-0.5,-0.5,0.0);
		glVertex3f(0.0,0.5,0.0);
		glVertex3f(0.5,-0.5,0.0);

		glVertex3f(1.5,1.5,0.0);
		glVertex3f(2.0,2.5,0.0);
		glVertex3f(1.5,1.5,0.0);
	glEnd();
	OPENGL_CHECK_FOR_ERRORS()

	glutSwapBuffers();
}

void InitMainWindow()
{
	LOG("InitMainWindow()");

	int ar = 1;
	char* pCh = "Nothing";

	glutInit(&ar, &pCh);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(400,400);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("Урок 1");
	
	// main render scene call register
	glutDisplayFunc(renderScene);
	
	// Main cycle GLUT
	glutMainLoop();
}

//void main(void)
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
	LOG("WinMain");	
	
	GLOBALS.Init();
	InitMainWindow();

	return 0;
}

