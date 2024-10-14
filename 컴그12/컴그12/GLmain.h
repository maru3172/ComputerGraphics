#pragma once
#pragma once
#include "GLbasic.h"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> random(0, WIDTH);
std::uniform_int_distribution<int> random2(0, HEIGHT);

bool start = false;
int cnt = 1;

class Shape
{
public:
	GLfloat shapecoord[5][3];
	GLfloat color[5][3];
	int shapetype;
	int run;
	bool MouseState;
	bool ShapeState;
	bool up;
	bool down;
	bool way;
	Shape() : shapetype{ 0 }, run{ 0 }, MouseState{ false }, ShapeState{ true }, up { false }, down { false }, way{ false }
	{
		for (int i = 0; i < 6; i++)
		{
			Color(color[0][i]);
		}
		for (int j = 0; j < 5; j++)
		{
			for (int i = 0; i < 3; i++)
			{
				shapecoord[j][i] = 0.0;
			}
			color[j][0] = color[0][0];
			color[j][1] = color[0][1];
			color[j][2] = color[0][2];
		}
	};

	void Colors()
	{
		for (int i = 0; i < 3; i++)
		{
			Color(color[0][i]);
		}
		for (int j = 0; j < 5; j++)
		{
			color[j][0] = color[0][0];
			color[j][1] = color[0][1];
			color[j][2] = color[0][2];
		}
	}
};

Shape shape[15];
float rx, ry;

void main(int argc, char** argv)
{
	if (!start)
	{
		for (int i = 0; i < 15; i++)
		{
			convertXY(random(gen), random2(gen), rx, ry);
			if (i < 3)
			{
				shape[i].shapetype = 1;
			}
			else if (i > 2 && i < 6)
			{
				shape[i].shapetype = 2;
			}
			else if (i > 5 && i < 9)
			{
				shape[i].shapetype = 3;
			}
			else if (i > 8 && i < 12)
			{
				shape[i].shapetype = 4;
			}
			else if (i > 11 && i < 15)
			{
				shape[i].shapetype = 5;
			}
			if (shape[i].shapetype == 1)
			{
				shape[i].shapecoord[0][0] = rx - 0.015;
				shape[i].shapecoord[0][1] = ry + 0.015;
				shape[i].shapecoord[1][0] = rx + 0.015;
				shape[i].shapecoord[1][1] = ry + 0.015;
				shape[i].shapecoord[2][0] = rx - 0.015;
				shape[i].shapecoord[2][1] = ry - 0.015;
				shape[i].shapecoord[3][0] = rx + 0.015;
				shape[i].shapecoord[3][1] = ry - 0.015;
			}
			else if (shape[i].shapetype == 2)
			{
				shape[i].shapecoord[0][0] = rx - 0.15;
				shape[i].shapecoord[0][1] = ry - 0.15;
				shape[i].shapecoord[1][0] = rx + 0.15;
				shape[i].shapecoord[1][1] = ry + 0.15;
			}
			else if (shape[i].shapetype == 3)
			{
				shape[i].shapecoord[0][0] = rx;
				shape[i].shapecoord[0][1] = ry + 0.15;
				shape[i].shapecoord[1][0] = rx - 0.15;
				shape[i].shapecoord[1][1] = ry - 0.15;
				shape[i].shapecoord[2][0] = rx + 0.15;
				shape[i].shapecoord[2][1] = ry - 0.15;
			}
			else if (shape[i].shapetype == 4)
			{
				shape[i].shapecoord[0][0] = rx - 0.15;
				shape[i].shapecoord[0][1] = ry + 0.15;
				shape[i].shapecoord[1][0] = rx + 0.15;
				shape[i].shapecoord[1][1] = ry + 0.15;
				shape[i].shapecoord[2][0] = rx - 0.15;
				shape[i].shapecoord[2][1] = ry - 0.15;
				shape[i].shapecoord[3][0] = rx + 0.15;
				shape[i].shapecoord[3][1] = ry - 0.15;
			}
			else if (shape[i].shapetype == 5)
			{
				shape[i].shapecoord[0][0] = rx;
				shape[i].shapecoord[0][1] = ry + 0.075;
				shape[i].shapecoord[1][0] = rx - 0.15;
				shape[i].shapecoord[1][1] = ry;
				shape[i].shapecoord[2][0] = rx - 0.075;
				shape[i].shapecoord[2][1] = ry - 0.075;
				shape[i].shapecoord[3][0] = rx + 0.075;
				shape[i].shapecoord[3][1] = ry - 0.075;
				shape[i].shapecoord[4][0] = rx + 0.15;
				shape[i].shapecoord[4][1] = ry;
			}
		}
		start = true;
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Example10");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	make_shaderProgram();
	InitBuffer();
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}