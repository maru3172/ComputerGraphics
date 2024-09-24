#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <random>
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
bool state = false;

float change()
{
	float a = 1.0;
	return a;
}

float dchange()
{
	float a = 0.0;
	return a;
}

float r = 1.0, g = 1.0, b = 1.0;

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Example1");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
}

GLvoid drawScene()
{
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 7);

	switch (key)
	{
	case 'c':
		r = dchange();
		g = change();
		b = change();
		break;
	case 'm':
		r = change();
		g = dchange();
		b = change();
		break;
	case 'y':
		r = change();
		g = change();
		b = dchange();
		break;
	case 'a':
		switch (dis(gen))
		{
		case 0:
			r = change();
			g = dchange();
			b = dchange();
			break;
		case 1:
			r = dchange();
			g = change();
			b = dchange();
			break;
		case 2:
			r = dchange();
			g = dchange();
			b = change();
			break;
		case 3:
			r = dchange();
			g = change();
			b = change();
			break;
		case 4:
			r = change();
			g = dchange();
			b = change();
			break;
		case 5:
			r = change();
			g = change();
			b = dchange();
			break;
		case 6:
			r = change();
			g = change();
			b = change();
			break;
		case 7:
			r = dchange();
			g = dchange();
			b = dchange();
			break;
		}
		break;
	case 'w':
		r = change();
		g = change();
		b = change();
		break;
	case 'k':
		r = dchange();
		g = dchange();
		b = dchange();
		break;
	case 't':
		state = true;
		glutTimerFunc(100, TimerFunction, 1);
		break;
	case 's':
		state = false;
		glutTimerFunc(100, TimerFunction, 1);
		break;
	case 'q':
		glutLeaveMainLoop();
		break;
	}
	glutPostRedisplay();
}

void TimerFunction(int value)
{
	if (state == true)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(0, 7);
		switch (dis(gen))
		{
		case 0:
			r = change();
			g = dchange();
			b = dchange();
			break;
		case 1:
			r = dchange();
			g = change();
			b = dchange();
			break;
		case 2:
			r = dchange();
			g = dchange();
			b = change();
			break;
		case 3:
			r = dchange();
			g = change();
			b = change();
			break;
		case 4:
			r = change();
			g = dchange();
			b = change();
			break;
		case 5:
			r = change();
			g = change();
			b = dchange();
			break;
		case 6:
			r = change();
			g = change();
			b = change();
			break;
		case 7:
			r = dchange();
			g = dchange();
			b = dchange();
			break;
		}
		glutPostRedisplay();
		glutTimerFunc(100, TimerFunction, 1);
	}
}