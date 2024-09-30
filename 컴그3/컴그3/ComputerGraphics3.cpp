#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <random>
#include <math.h>
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Motion(int x, int y);
#define WIDTH 800
#define HEIGHT 600

bool left_button = false;

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
	std::uniform_int_distribution<int> dis(0, 6);

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
		r = 0.0;
		g = 0.0;
		b = 0.0;
		break;
	}
}

float bGCr = 1.0, bGCg = 1.0, bGCb = 1.0;

struct Rect
{
	float x1;
	float y1;
	float x2;
	float y2;
	float x11;
	float y11;
	float x12;
	float y12;
	float r;
	float g;
	float b;
	bool state;
	bool Break;
	int stack = 1;
};

Rect rect[20];

bool Crash(const Rect rec1, const Rect rec2)
{
	if (rec1.x1 < rec2.x2 && rec1.y1 < rec2.y2 && rec1.x2 > rec2.x1 && rec1.y2 > rec2.y1)
		return true;
	else
		return false;
}


void main(int argc, char** argv)
{
	left_button = false;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Example3");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	glutKeyboardFunc(Keyboard);
	glutDisplayFunc(drawScene);
	glutMotionFunc(Motion);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid drawScene()
{
	glClearColor(bGCr, bGCg, bGCb, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < 10; i++)
	{
		if (rect[i].state)
		{
			glColor3f(rect[i].r, rect[i].g, rect[i].b);
			glRectf(rect[i].x1, rect[i].y1, rect[i].x2, rect[i].y2);
		}
	}
	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid Motion(int x, int y)
{
	left_button = true;
	int count = 0;
	float fx = 0.0, fy = 0.0;
	if (left_button == true)
	{
		convertXY(x, y, fx, fy);
		for (int i = 0; i < 10; i++)
		{
			if (rect[i].x1 < fx && rect[i].x2 > fx && rect[i].y1 < fy && rect[i].y2 > fy && rect[i].state)
			{
				rect[i].x1 = fx - (0.125 * rect[i].stack);
				rect[i].x2 = fx + (0.125 * rect[i].stack);
				rect[i].y1 = fy - (0.125 * rect[i].stack);
				rect[i].y2 = fy + (0.125 * rect[i].stack);
				bool on = false;
				for (int j = 0; j < 10; j++)
				{
					if (i != j && Crash(rect[j], rect[i]))

					{
						on = true;
						rect[i].x1 = std::min(rect[i].x1, rect[j].x1);
						rect[i].y1 = std::min(rect[i].y1, rect[j].y1);
						rect[i].x2 = std::max(rect[i].x2, rect[j].x2);
						rect[i].y2 = std::max(rect[i].y2, rect[j].y2);
						rect[j].state = false;
						if (!rect[i].Break)
						{
							change(rect[i].r, rect[i].g, rect[i].b);
							rect[i].Break = true;
						}
						
					}
				}
				if (!on) {
					rect[i].Break = false;
					for (int j = 0; j < 10; j++)
					{
						rect[j].state = true;
					}
				}
				break;
			}
		}
	}
	glutPostRedisplay();
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	float fx = 0.0, fy = 0.0;
	switch (key)
	{
	case 'a':
		for (int i = 0; i < 10; i++)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<int> random1(0, WIDTH);
			std::uniform_int_distribution<int> random2(0, HEIGHT);
			convertXY(random1(gen), random2(gen), fx, fy);
			rect[i].x1 = fx;
			rect[i].y1 = fy;
			for (int i = 0; i < 10; i++)
			{
				change(rect[i].r, rect[i].g, rect[i].b);
				rect[i].state = true;
				rect[i].Break = false;
			}
			rect[i].x2 = rect[i].x1 + 0.25;
			rect[i].y2 = rect[i].y1 + 0.25;
		}
		break;
	}
	glutPostRedisplay();
}