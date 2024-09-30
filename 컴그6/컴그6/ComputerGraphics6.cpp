#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <random>
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid TimerFunction(int value);
#define WIDTH 800
#define HEIGHT 600

int count = 0;

void ColorCopy(float r, float g, float b, float& cr, float& cg, float& cb)
{
	cr = r;
	cg = g;
	cb = b;
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
	bool state = false;
};

struct Rect2 : public Rect
{
	int rectShape = 0;
};
Rect rect[10];

Rect2 recter[80];

float bGCr = 1.0, bGCb = 1.0, bGCg = 1.0;

void convertXY(int x, int y, float& fx, float& fy)
{
	int w = WIDTH;
	int h = HEIGHT;
	fx = (float)((x - (float)w / 2.0) * (float)(1.0 / (float)(w / 2.0)));
	fy = -(float)((y - (float)h / 2.0) * (float)(1.0 / (float)(h / 2.0)));
}

void start()
{
	for (int i = 0; i < 10; i++)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> random(0, WIDTH - 100);
		std::uniform_int_distribution<int> random2(0, HEIGHT - 100);
		std::uniform_real_distribution<float> random3(0, 1);

		float fx, fy;
		convertXY(random(gen), random2(gen), fx, fy);
		rect[i].x1 = fx;
		rect[i].y1 = fy;
		rect[i].x2 = rect[i].x1 + 0.25;
		rect[i].y2 = rect[i].y1 + 0.25;

		rect[i].r = random3(gen);
		rect[i].g = random3(gen);
		rect[i].b = random3(gen);
		rect[i].state = true;
	}
}

bool Start = false;

void main(int argc, char** argv)
{
	if (Start == false)
	{
		start();
		Start = true;
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Example6");

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
	for (int i = 0; i < 10; i++)
	{
		if (rect[i].state == true)
		{
			glColor3f(rect[i].r, rect[i].g, rect[i].b);
			glRectf(rect[i].x1, rect[i].y1, rect[i].x2, rect[i].y2);
		}
	}
	for (int i = 0; i < 80; i++)
	{
		if (recter[i].state == true)
		{
			glColor3f(recter[i].r, recter[i].g, recter[i].b);
			glRectf(recter[i].x1, recter[i].y1, recter[i].x2, recter[i].y2);
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
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> random2(1, 8);
	float fx = 0.0, fy = 0.0;
	int ran = random2(gen);
	convertXY(x, y, fx, fy);
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		for (int i = 0; i < 10; i++)
		{
			if (rect[i].x1 < fx && rect[i].x2 > fx && rect[i].y1 < fy && rect[i].y2 > fy && rect[i].state)
			{
				std::uniform_int_distribution<int> random(0, 3);
				rect[i].state = false;
				switch (random(gen))
				{
				case 0:
					for (int j = 0; j < 4; j++)
					{
						if (count < 80)
						{
							if (j == 0)
							{
								recter[count].x1 = rect[i].x1;
								recter[count].x2 = rect[i].x1 + 0.125;
								recter[count].y1 = rect[i].y1;
								recter[count].y2 = rect[i].y1 + 0.125;
							}
							else if (j == 1)
							{
								recter[count].x1 = rect[i].x1 + 0.125;
								recter[count].x2 = rect[i].x2;
								recter[count].y1 = rect[i].y1;
								recter[count].y2 = rect[i].y1 + 0.125;
							}
							else if (j == 2)
							{
								recter[count].x1 = rect[i].x1;
								recter[count].x2 = rect[i].x1 + 0.125;
								recter[count].y1 = rect[i].y1 + 0.125;
								recter[count].y2 = rect[i].y2;
							}
							else if (j == 3)
							{
								recter[count].x1 = rect[i].x1 + 0.125;
								recter[count].x2 = rect[i].x2;
								recter[count].y1 = rect[i].y1 + 0.125;
								recter[count].y2 = rect[i].y2;
							}

							ColorCopy(rect[i].r, rect[i].g, rect[i].b, recter[count].r, recter[count].g, recter[count].b);
							recter[count].state = true;
							recter[count].rectShape = j + 1;

							count++;
						}
					}
					break;
				case 1:
					for (int j = 0; j < 4; j++)
					{
						if (count < 80)
						{
							if (j == 0)
							{
								recter[count].x1 = rect[i].x1;
								recter[count].x2 = rect[i].x1 + 0.125;
								recter[count].y1 = rect[i].y1;
								recter[count].y2 = rect[i].y1 + 0.125;
							}
							else if (j == 1)
							{
								recter[count].x1 = rect[i].x1 + 0.125;
								recter[count].x2 = rect[i].x2;
								recter[count].y1 = rect[i].y1;
								recter[count].y2 = rect[i].y1 + 0.125;
							}
							else if (j == 2)
							{
								recter[count].x1 = rect[i].x1;
								recter[count].x2 = rect[i].x1 + 0.125;
								recter[count].y1 = rect[i].y1 + 0.125;
								recter[count].y2 = rect[i].y2;
							}
							else if (j == 3)
							{
								recter[count].x1 = rect[i].x1 + 0.125;
								recter[count].x2 = rect[i].x2;
								recter[count].y1 = rect[i].y1 + 0.125;
								recter[count].y2 = rect[i].y2;
							}

							ColorCopy(rect[i].r, rect[i].g, rect[i].b, recter[count].r, recter[count].g, recter[count].b);
							recter[count].state = true;
							recter[count].rectShape = 4 + j + 1;

							count++;
						}
					}
					break;
				case 2:
					for (int j = 0; j < 4; j++)
					{
						if (count < 80)
						{
							if (j == 0)
							{
								recter[count].x1 = rect[i].x1;
								recter[count].x2 = rect[i].x1 + 0.125;
								recter[count].y1 = rect[i].y1;
								recter[count].y2 = rect[i].y1 + 0.125;
							}
							else if (j == 1)
							{
								recter[count].x1 = rect[i].x1 + 0.125;
								recter[count].x2 = rect[i].x2;
								recter[count].y1 = rect[i].y1;
								recter[count].y2 = rect[i].y1 + 0.125;
							}
							else if (j == 2)
							{
								recter[count].x1 = rect[i].x1;
								recter[count].x2 = rect[i].x1 + 0.125;
								recter[count].y1 = rect[i].y1 + 0.125;
								recter[count].y2 = rect[i].y2;
							}
							else if (j == 3)
							{
								recter[count].x1 = rect[i].x1 + 0.125;
								recter[count].x2 = rect[i].x2;
								recter[count].y1 = rect[i].y1 + 0.125;
								recter[count].y2 = rect[i].y2;
							}

							ColorCopy(rect[i].r, rect[i].g, rect[i].b, recter[count].r, recter[count].g, recter[count].b);
							recter[count].state = true;
							recter[count].rectShape = ran;

							count++;
						}
					}
					break;
				case 3:
					for (int j = 0; j < 8; j++)
					{
						if (count < 80)
						{
							if (j == 0)
							{
								recter[count].x1 = rect[i].x1;
								recter[count].x2 = rect[i].x1 + 0.0625;
								recter[count].y1 = rect[i].y1;
								recter[count].y2 = rect[i].y1 + 0.125;
							}
							else if (j == 1)
							{
								recter[count].x1 = rect[i].x1 + 0.0625;
								recter[count].x2 = rect[i].x1 + 0.125;
								recter[count].y1 = rect[i].y1;
								recter[count].y2 = rect[i].y1 + 0.125;
							}
							else if (j == 2)
							{
								recter[count].x1 = rect[i].x1 + 0.125;
								recter[count].x2 = rect[i].x1 + 0.1875;
								recter[count].y1 = rect[i].y1;
								recter[count].y2 = rect[i].y1 + 0.125;
							}
							else if (j == 3)
							{
								recter[count].x1 = rect[i].x1 + 0.1875;
								recter[count].x2 = rect[i].x2;
								recter[count].y1 = rect[i].y1;
								recter[count].y2 = rect[i].y1 + 0.125;
							}
							else if (j == 4)
							{
								recter[count].x1 = rect[i].x1;
								recter[count].x2 = rect[i].x1 + 0.0625;
								recter[count].y1 = rect[i].y1 + 0.125;
								recter[count].y2 = rect[i].y2;
							}
							else if (j == 5)
							{
								recter[count].x1 = rect[i].x1 + 0.0625;
								recter[count].x2 = rect[i].x1 + 0.125;
								recter[count].y1 = rect[i].y1 + 0.125;
								recter[count].y2 = rect[i].y2;
							}
							else if (j == 6)
							{
								recter[count].x1 = rect[i].x1 + 0.125;
								recter[count].x2 = rect[i].x1 + 0.1875;
								recter[count].y1 = rect[i].y1 + 0.125;
								recter[count].y2 = rect[i].y2;
							}
							else if (j == 7)
							{
								recter[count].x1 = rect[i].x1 + 0.1875;
								recter[count].x2 = rect[i].x2;
								recter[count].y1 = rect[i].y1 + 0.125;
								recter[count].y2 = rect[i].y2;
							}
							ColorCopy(rect[i].r, rect[i].g, rect[i].b, recter[count].r, recter[count].g, recter[count].b);
							recter[count].state = true;
							recter[count].rectShape = j + 1;

							count++;
						}
					}
					break;
				}
				break;
			}
		}
	}
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}

GLvoid TimerFunction(int value)
{
	for (int i = 0; i < 80; i++)
	{
		if (recter[i].rectShape == 1)
		{
			recter[i].x1 -= 0.01;
			recter[i].y1 += 0.01;
			recter[i].x2 -= 0.01;
			recter[i].y2 += 0.01;
		}
		else if (recter[i].rectShape == 2)
		{
			recter[i].x1 += 0.01;
			recter[i].y1 += 0.01;
			recter[i].x2 += 0.01;
			recter[i].y2 += 0.01;
		}
		else if (recter[i].rectShape == 3)
		{
			recter[i].x1 -= 0.01;
			recter[i].y1 -= 0.01;
			recter[i].x2 -= 0.01;
			recter[i].y2 -= 0.01;
		}
		else if (recter[i].rectShape == 4)
		{
			recter[i].x1 += 0.01;
			recter[i].y1 -= 0.01;
			recter[i].x2 += 0.01;
			recter[i].y2 -= 0.01;
		}
		else if (recter[i].rectShape == 5)
		{
			recter[i].x1 -= 0.01;
			recter[i].x2 -= 0.01;
		}
		else if (recter[i].rectShape == 6)
		{
			recter[i].y1 += 0.01;
			recter[i].y2 += 0.01;
		}
		else if (recter[i].rectShape == 7)
		{
			recter[i].x1 += 0.01;
			recter[i].x2 += 0.01;
		}
		else if (recter[i].rectShape == 8)
		{
			recter[i].y1 -= 0.01;
			recter[i].y2 -= 0.01;
		}
		
		recter[i].x1 += 0.001;
		recter[i].y1 += 0.001;
		recter[i].x2 -= 0.001;
		recter[i].y2 -= 0.001;
		if (recter[i].x1 > recter[i].x2)
		{
			recter[i].x1 = 2;
			recter[i].y1 = 2;
			recter[i].x2 = 2;
			recter[i].y2 = 2;
			recter[i].rectShape = false;
			recter[i].rectShape = 0;
		}
	}
	glutPostRedisplay();
	if (count > 0)
		glutTimerFunc(100, TimerFunction, 1);
	if (count > 79)
	{
		count = 0;
	}
}