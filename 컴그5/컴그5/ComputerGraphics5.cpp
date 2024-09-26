#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <random>
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Motion(int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
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

struct Rect
{
	float x1;
	float y1;
	float x2;
	float y2;
	float r;
	float g;
	float b;
	bool state;
};
Rect rect[20];

bool left_button = false, left_button_move = false;
int count;

float bGCr = 1.0, bGCg = 1.0, bGCb = 1.0;

void main(int argc, char** argv)
{
	left_button = false;
	left_button_move = false;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Example5");

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
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

bool Crash(const Rect rec1, const Rect rec2)
{
	if (rec1.x1 < rec2.x2 && rec1.y1 < rec2.y2 && rec1.x2 > rec2.x1 && rec1.y2 > rec2.y1)
		return true;
	else
		return false;
}

GLvoid drawScene()
{
	glClearColor(bGCr, bGCg, bGCb, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < 20; i++)
	{
		if (rect[i].state == true)
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

GLvoid Mouse(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		left_button = true;
}

GLvoid Motion(int x, int y)
{
	left_button_move = true;
	float fx = 0.0, fy = 0.0;
	if (left_button == true && left_button_move == true)
	{
		convertXY(x, y, fx, fy);
		for (int i = 0; i < 20; i++)
		{
			if (rect[i].x1 < fx && rect[i].x2 > fx && rect[i].y1 < fy && rect[i].y2 > fy)
			{
				rect[i].x1 = fx - 0.3;
				rect[i].y1 = fy - 0.3;
				rect[i].x2 = fx + 0.3;
				rect[i].y2 = fy + 0.3;
				count = i;
				for (int j = 0; j < 20; j++)
				{
					if (Crash(rect[i], rect[j]))
					{
						if (j != i)
						{
							rect[j].state = false;
							rect[i].r = rect[j].r;
							rect[i].g = rect[j].g;
							rect[i].b = rect[j].b;
							break;
						}
					}
				}
				break;
			}
		}
	}
	else
	{
		rect[count].x1 += 0.15;
		rect[count].y1 += 0.15;
		rect[count].x2 -= 0.15;
		rect[count].y2 -= 0.15;
	}
	glutPostRedisplay();
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	float fx = 0.0, fy = 0.0;
	switch (key)
	{
	case 'r':
		for (int i = 0; i < 20; i++)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<int> random1(0, WIDTH);
			std::uniform_int_distribution<int> random2(0, HEIGHT);
			convertXY(random1(gen), random2(gen), fx, fy);
			rect[i].x1 = fx;
			rect[i].y1 = fy;
			for (int i = 0; i < 20; i++)
			{
				change(rect[i].r, rect[i].g, rect[i].b);
				rect[i].state = true;
			}
			rect[i].x2 = rect[i].x1 + 0.15;
			rect[i].y2 = rect[i].y1 + 0.15;
		}
		break;
	}
	glutPostRedisplay();
}