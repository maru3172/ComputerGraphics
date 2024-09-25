#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <random>
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
#define WIDTH 800
#define HEIGHT 600

void convertXY(int x, int y, float& fx, float& fy)
{
	int w = WIDTH;
	int h = HEIGHT;
	fx = (float)((x - (float)w / 2.0) * (float)(1.0 / (float)(w / 2.0)));
	fy = -(float)((y - (float)h / 2.0) * (float)(1.0 / (float)(h / 2.0)));
}

void change(float& r, float& g, float& b)
{
	std::random_device  rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 7);

	switch (dis(gen))
	{
	case 0:
		r = 1.0;
		g = 0.0;
		b = 0.0;
		break;
	case 1:
		r = 0.0;
		g = 1.0;
		b = 0.0;
		break;
	case 2:
		r = 0.0;
		g = 0.0;
		b = 1.0;
		break;
	case 3:
		r = 0.0;
		g = 1.0;
		b = 1.0;
		break;
	case 4:
		r = 1.0;
		g = 0.0;
		b = 1.0;
		break;
	case 5:
		r = 1.0;
		g = 1.0;
		b = 0.0;
		break;
	case 6:
		r = 1.0;
		g = 1.0;
		b = 1.0;
		break;
	case 7:
		r = 0.0;
		g = 0.0;
		b = 0.0;
		break;
	}
}

float bGCr = 1.0, bGCg = 1.0, bGCb = 1.0;
int stack = 0;

struct Rect
{
	float x1;
	float y1;
	float x2;
	float y2;
	float r;
	float g;
	float b; 
};

Rect rect[4];



void main(int argc, char** argv)
{
	rect[0].x1 = -1.0;
	rect[0].y1 = 1.0;
	rect[0].x2 = 0.0;
	rect[0].y2 = 0.0;

	rect[1].x1 = 0.0;
	rect[1].y1 = 0.0;
	rect[1].x2 = 1.0;
	rect[1].y2 = 1.0;

	rect[2].x1 = -1.0;
	rect[2].y1 = -1.0;
	rect[2].x2 = 0.0;
	rect[2].y2 = 0.0;

	rect[3].x1 = 0.0;
	rect[3].y1 = 0.0; 
	rect[3].x2 = 1.0;
	rect[3].y2 = -1.0;

	for (int i = 0; i < 4; i++)
	{
		change(rect[i].r, rect[i].g, rect[i].b);
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Example2");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	glutDisplayFunc(drawScene);
	glutMouseFunc(Mouse);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid drawScene()
{
	glClearColor(bGCr, bGCg, bGCb, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < 4; i++)
	{
		glColor3f(rect[i].r, rect[i].g, rect[i].b);
		glRectf(rect[i].x1, rect[i].y1, rect[i].x2, rect[i].y2);
	}
	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void Mouse(int button, int state, int x, int y)
{
	float fx = 0.0, fy = 0.0;
	convertXY(x, y, fx, fy);
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && rect[0].x1 < fx && rect[0].x2 > fx && rect[0].y1 > fy && rect[0].y2 < fy)
	{
		change(rect[0].r, rect[0].g, rect[0].b);
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && rect[1].x1 < fx && rect[1].x2 > fx && rect[1].y1 < fy && rect[1].y2 > fy)
	{
		change(rect[1].r, rect[1].g, rect[1].b);
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && rect[2].x1 < fx && rect[2].x2 > fx && rect[2].y1 < fy && rect[2].y2 > fy)
	{
		change(rect[2].r, rect[2].g, rect[2].b);
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && rect[3].x1 < fx && rect[3].x2 > fx && rect[3].y1 > fy && rect[3].y2 < fy)
	{
		change(rect[3].r, rect[3].g, rect[3].b);
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && rect[0].x1 < fx && rect[0].x2 > fx && rect[0].y1 > fy && rect[0].y2 < fy)
	{
		if (rect[0].x1 < -0.7 && rect[0].x2 > -0.3 && rect[0].y1 > 0.7 && rect[0].y2 < 0.3)
		{
			rect[0].x1 += 0.01;
			rect[0].y1 -= 0.01;
			rect[0].x2 -= 0.01;
			rect[0].y2 += 0.01;
		}
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && rect[1].x1 < fx && rect[1].x2 > fx && rect[1].y1 < fy && rect[1].y2 > fy)
	{
		if (rect[1].x1 < 0.3 && rect[1].x2 > 0.7 && rect[1].y1 < 0.3 && rect[1].y2 > 0.7)
		{
			rect[1].x1 += 0.01;
			rect[1].y1 += 0.01;
			rect[1].x2 -= 0.01;
			rect[1].y2 -= 0.01;
		}
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && rect[2].x1 < fx && rect[2].x2 > fx && rect[2].y1 < fy && rect[2].y2 > fy)
	{
		if (rect[2].x2 > -0.3 && rect[2].x1 < -0.7 && rect[2].y2 > -0.3 && rect[2].y1 < -0.7)
		{
			rect[2].x1 += 0.01;
			rect[2].y1 += 0.01;
			rect[2].x2 -= 0.01;
			rect[2].y2 -= 0.01;
		}
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && rect[3].x1 < fx && rect[3].x2 > fx && rect[3].y1 > fy && rect[3].y2 < fy)
	{
		if (rect[3].x1 < 0.3 && rect[3].x2 > 0.7 && rect[3].y1 > -0.3 && rect[3].y2 < -0.7)
		{
			rect[3].x1 += 0.01;
			rect[3].y1 -= 0.01;
			rect[3].x2 -= 0.01;
			rect[3].y2 += 0.01;
		}
	}
	else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		change(bGCr, bGCg, bGCb);
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		rect[0].x1 -= 0.01;
		rect[0].y1 += 0.01;
		rect[0].x2 += 0.01;
		rect[0].y2 -= 0.01;
		rect[1].x1 -= 0.01;
		rect[1].y1 -= 0.01;
		rect[1].x2 += 0.01;
		rect[1].y2 += 0.01;
		rect[2].x1 -= 0.01;
		rect[2].y1 -= 0.01;
		rect[2].x2 += 0.01;
		rect[2].y2 += 0.01;
		rect[3].x1 -= 0.01;
		rect[3].y1 += 0.01;
		rect[3].x2 += 0.01;
		rect[3].y2 -= 0.01;
	}
	glutPostRedisplay();
}