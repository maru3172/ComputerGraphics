#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <random>
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
void TimerFunction(int value);
#define WIDTH 800
#define HEIGHT 600

bool left_button = false;
bool move1 = false, move2 = false, SizeChange = false, ColorChange = false;

void convertXY(int x, int y, float& fx, float& fy)
{
	int w = WIDTH;
	int h = HEIGHT;
	fx = (float)((x - (float)w / 2.0) * (float)(1.0 / (float)(w / 2.0)));
	fy = -(float)((y - (float)h / 2.0) * (float)(1.0 / (float)(h / 2.0)));
}


void OnNOff(bool& change)
{
	if (change)
		change = false;
	else
		change = true;
}

struct Rect
{
	float x1;
	float y1;
	float x2;
	float y2;
	float retx1;
	float retx2;
	float rety1;
	float rety2;
	float r;
	float g;
	float b;
	bool state = false;
	bool UpinDown;
	bool Side;
	bool Size;
	bool Side2;
	bool UpinDown2;
};

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

float bGCr = 0.411765, bGCg = 0.411765, bGCb = 0.411765;

int count = 0;

Rect rect[5];

GLvoid Mouse(int button, int state, int x, int y)
{
	float fx, fy;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		convertXY(x, y, fx, fy);
		if (count < 5)
		{
			rect[count].x1 = fx - 0.15;
			rect[count].y1 = fy - 0.15;
			rect[count].x2 = fx + 0.15;
			rect[count].y2 = fy + 0.15;
			rect[count].retx1 = rect[count].x1;
			rect[count].rety1 = rect[count].y1;
			rect[count].retx2 = rect[count].x2;
			rect[count].rety2 = rect[count].y2;
			change(rect[count].r, rect[count].g, rect[count].b);
			rect[count].state = true;
			count++;
		}
	}
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Example4");

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
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid drawScene()
{
	glClearColor(bGCr, bGCg, bGCb, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < 5; i++)
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

GLvoid Keyboard(unsigned char key, int x, int y)
{
	float fx = 0.0, fy = 0.0;
	switch (key)
	{
	case '1':
		OnNOff(move1);
		glutTimerFunc(100, TimerFunction, 1);
		break;
	case '2':
		OnNOff(move2);
		glutTimerFunc(100, TimerFunction, 1);
		break;
	case '3':
		OnNOff(SizeChange);
		glutTimerFunc(100, TimerFunction, 1);
		break;
	case '4':
		OnNOff(ColorChange);
		glutTimerFunc(100, TimerFunction, 1);
		break;
	case 's':
		if(move1)
			OnNOff(move1);
		if(move2)
			OnNOff(move2);
		if(SizeChange)
			OnNOff(SizeChange);
		if(ColorChange)
			OnNOff(ColorChange);
		break;
	case 'm':
		for (int i = 0; i < 5; i++)
		{
			rect[i].x1 = rect[i].retx1;
			rect[i].y1 = rect[i].rety1;
			rect[i].x2 = rect[i].retx2;
			rect[i].y2 = rect[i].rety2;
		}
		break;
	case 'r':
		for (int i = 0; i < 5; i++)
		{
			if (rect[i].state)
			{
				OnNOff(rect[i].state);
			}
		}
		count = 0;
		break;
	case 'q':
		glutLeaveMainLoop();
		break;
	}
	glutPostRedisplay();
}

void TimerFunction(int value)
{
	for (int i = 0; i < 5; i++)
	{
		if (move1)
		{
			if (rect[i].state == true)
			{
				if (rect[i].Side)
				{
					rect[i].x1 += 0.05;
					rect[i].x2 += 0.05;
				}
				else if (rect[i].Side == false)
				{
					rect[i].x1 -= 0.05;
					rect[i].x2 -= 0.05;
				}
				if (rect[i].UpinDown)
				{
					rect[i].y1 += 0.05;
					rect[i].y2 += 0.05;
				}
				else if (rect[i].UpinDown == false)
				{
					rect[i].y1 -= 0.05;
					rect[i].y2 -= 0.05;
				}

				if (rect[i].x2 > 1)
				{
					rect[i].Side = false;
				}
				else if (rect[i].x1 < -1)
				{
					rect[i].Side = true;
				}
				if (rect[i].y2 > 1)
				{
					rect[i].UpinDown = false;
				}
				else if (rect[i].y1 < -1)
				{
					rect[i].UpinDown = true;
				}
			}
		}
		if (move2)
		{
			if (rect[i].state == true)
			{
				if (rect[i].Side2)
				{
					rect[i].x1 += 0.05;
					rect[i].x2 += 0.05;
				}
				else if (rect[i].Side2 == false)
				{
					rect[i].x1 -= 0.05;
					rect[i].x2 -= 0.05;
				}
				if (rect[i].UpinDown2)
				{
					rect[i].y1 += 0.01;
					rect[i].y2 += 0.01;
				}
				else if (rect[i].UpinDown2 == false)
				{
					rect[i].y1 -= 0.01;
					rect[i].y2 -= 0.01;
				}

				if (rect[i].x2 > 1)
				{
					rect[i].Side2 = false;
				}
				else if (rect[i].x1 < -1)
				{
					rect[i].Side2 = true;
				}
				if (rect[i].y2 > 1)
				{
					rect[i].UpinDown2 = false;
				}
				else if (rect[i].y1 < -1)
				{
					rect[i].UpinDown2 = true;
				}
			}
		}
		if (SizeChange)
		{
			if (rect[i].state == true)
			{
				if (rect[i].x2 - rect[i].x1 > 0.25 && rect[i].y2 - rect[i].y1 > 0.25)
				{
					rect[i].Size = false;
				}
				else if (rect[i].x2 - rect[i].x1 < 0.01 && rect[i].y2 - rect[i].y1 < 0.01)
				{
					rect[i].Size = true;
				}

				if (rect[i].Size)
				{
					rect[i].x1 -= 0.05;
					rect[i].y1 -= 0.05;
					rect[i].x2 += 0.05;
					rect[i].y2 += 0.05;
				}
				else if (rect[i].Size == false)
				{
					rect[i].x1 += 0.05;
					rect[i].y1 += 0.05;
					rect[i].x2 -= 0.05;
					rect[i].y2 -= 0.05;
				}
			}
		}
		if (ColorChange)
		{
			if (rect[i].state)
			{
				change(rect[i].r, rect[i].g, rect[i].b);
			}
		}
	}
	glutPostRedisplay();
	if (move1 || move2 || SizeChange || ColorChange)
	{
		glutTimerFunc(60, TimerFunction, 1);
	}
}