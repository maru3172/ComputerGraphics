#pragma once
#include "GLbasic.h"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> randoms(0, 2);
std::uniform_int_distribution<int> randomss(0, 2);

int count = 0;

#define SHAPECOUNT 100

class Linear
{
public:
	GLfloat L[2][3];
	GLfloat rgb[2][3];
	bool show;
	Linear() : show(false)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				L[i][j] = 0.0f;
				Color(rgb[0][j]);
			}
		}

		for (int i = 0; i < 2; i++)
		{
			rgb[i][0] = rgb[0][0];
			rgb[i][1] = rgb[0][1];
			rgb[i][2] = rgb[0][2];
		}
	}
};

class Shape
{
public:
	GLfloat shapecoord[5][3];
	GLfloat colors[5][3];
	GLfloat speed;
	GLfloat velocity;
	int shapetype;
	bool state, view, Slice, normal, path;
	Shape() : speed{ 0.01f }, view{ false }, state{ false }, Slice( false ), normal(false), path(false), velocity(0.0f)
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				shapecoord[i][j] = 0.0f;
				Color(colors[0][j]);
			}
		}

		for (int i = 0; i < 5; i++)
		{
			colors[i][0] = colors[0][0];
			colors[i][1] = colors[0][1];
			colors[i][2] = colors[0][2];
		}
		switch (randoms(gen))
		{
		case 0:
			state = true;
			break;
		case 1:
			state = false;
			break;
		}
	}

	void speedUp()
	{
		if (speed < 0.05)
		{
			speed += 0.001;
		}
	}
	void speedDown()
	{
		if (speed > 0.001)
		{
			speed -= 0.001;
		}
	}

	void RandomSet()
	{
		shapetype = randoms(gen);

		if (!state)
		{
			state = true;
		}
		else
		{
			state = false;
		}

		if (state)  // ¡¬√¯ ªÛ¥‹
		{
			switch (shapetype)
			{
			case 0:  // ªÔ∞¢«¸
				shapecoord[0][0] = -1.25f; // ¿Œµ¶Ω∫ 0
				shapecoord[0][1] = 1.5f;  // ¿Œµ¶Ω∫ 1
				shapecoord[1][0] = -1.5f;  // ¿Œµ¶Ω∫ 2
				shapecoord[1][1] = 1.0f;
				shapecoord[2][0] = -1.0f;  // ¿Œµ¶Ω∫ 3
				shapecoord[2][1] = 1.0f;
				break;
			case 1:  // ªÁ∞¢«¸
				shapecoord[0][0] = -1.5f; // ¿Œµ¶Ω∫ 0
				shapecoord[0][1] = 1.0f;  // ¿Œµ¶Ω∫ 1
				shapecoord[1][0] = -1.0f;  // ¿Œµ¶Ω∫ 2
				shapecoord[1][1] = 1.0f;
				shapecoord[2][0] = -1.5f;  // ¿Œµ¶Ω∫ 3
				shapecoord[2][1] = 1.25f;
				shapecoord[3][0] = -1.0f;  // ¿Œµ¶Ω∫ 4
				shapecoord[3][1] = 1.25f;
				break;

			case 2:  // ø¿∞¢«¸
				shapecoord[0][0] = -1.25f; // ¿Œµ¶Ω∫ 0
				shapecoord[0][1] = 1.5f;
				shapecoord[1][0] = -1.5f;
				shapecoord[1][1] = 1.25f;
				shapecoord[2][0] = -1.3f;
				shapecoord[2][1] = 1.0f;
				shapecoord[3][0] = -1.2f;
				shapecoord[3][1] = 1.0f;
				shapecoord[4][0] = -1.0f;
				shapecoord[4][1] = 1.25f;
				break;
			}
		}
		else  // øÏ√¯ ªÛ¥‹
		{
			switch (shapetype)
			{
			case 0:  // ªÔ∞¢«¸
				shapecoord[0][0] = 1.25f; // ¿Œµ¶Ω∫ 0
				shapecoord[0][1] = 1.5f;  // ¿Œµ¶Ω∫ 1
				shapecoord[1][0] = 1.5f;  // ¿Œµ¶Ω∫ 2
				shapecoord[1][1] = 1.0f;
				shapecoord[2][0] = 1.0f;  // ¿Œµ¶Ω∫ 3
				shapecoord[2][1] = 1.0f;
				break;
			case 1:  // ªÁ∞¢«¸
				shapecoord[0][0] = 1.5f; // ¿Œµ¶Ω∫ 0
				shapecoord[0][1] = 1.0f;  // ¿Œµ¶Ω∫ 1
				shapecoord[1][0] = 1.0f;  // ¿Œµ¶Ω∫ 2
				shapecoord[1][1] = 1.0f;
				shapecoord[2][0] = 1.5f;  // ¿Œµ¶Ω∫ 3
				shapecoord[2][1] = 1.25f;
				shapecoord[3][0] = 1.0f;  // ¿Œµ¶Ω∫ 4
				shapecoord[3][1] = 1.25f;
				break;

			case 2:  // ø¿∞¢«¸
				shapecoord[0][0] = 1.25f; // ¿Œµ¶Ω∫ 0
				shapecoord[0][1] = 1.5f;
				shapecoord[1][0] = 1.5f;
				shapecoord[1][1] = 1.25f;
				shapecoord[2][0] = 1.3f;
				shapecoord[2][1] = 1.0f;
				shapecoord[3][0] = 1.2f;
				shapecoord[3][1] = 1.0f;
				shapecoord[4][0] = 1.0f;
				shapecoord[4][1] = 1.25f;
				break;
			}
		}
		for (int j = 0; j < 3; j++)
		{
			Color(colors[0][j]);
		}
		for (int i = 0; i < 5; i++)
		{
			colors[i][0] = colors[0][0];
			colors[i][1] = colors[0][1];
			colors[i][2] = colors[0][2];
		}
	}
};

class Box
{
public:
	GLfloat BoxCoord[4][3];
	GLfloat BoxColor[4][3];
	bool state;
	Box() : state(false)
	{
		BoxCoord[0][0] = 0 - 0.15;
		BoxCoord[0][1] = -0.75 + 0.075;
		BoxCoord[1][0] = 0 - 0.15;
		BoxCoord[1][1] = -0.75 - 0.075;
		BoxCoord[2][0] = 0 + 0.15;
		BoxCoord[2][1] = -0.75 - 0.075;
		BoxCoord[3][0] = 0 + 0.15;
		BoxCoord[3][1] = -0.75 + 0.075;

		for (int i = 0; i < 3; i++)
		{
			Color(BoxColor[0][i]);
		}
		for (int i = 0; i < 4; i++)
		{
			BoxColor[i][0] = BoxColor[0][0];
			BoxColor[i][1] = BoxColor[0][1];
			BoxColor[i][2] = BoxColor[0][2];
		}
	}
};

Shape shape[SHAPECOUNT];

Linear linear;

Linear Path[SHAPECOUNT];

bool start = false;

void main(int argc, char** argv)
{
	if (!start)
	{
		for (int i = 0; i < 3; i++)
		{
			shape[i].RandomSet();
			shape[i].view = true;
			shape[i].normal = true;
			shape[i].path = true;
			count++;
			switch (shape[i].shapetype)
			{
			case 0:
				Path[i].L[1][0] = shape[i].shapecoord[2][0];
				Path[i].L[1][1] = shape[i].shapecoord[2][1];
				break;
			case 1:
				Path[i].L[1][0] = shape[i].shapecoord[1][0];
				Path[i].L[1][1] = shape[i].shapecoord[1][1];
				break;
			case 2:
				Path[i].L[1][0] = shape[i].shapecoord[3][0];
				Path[i].L[1][1] = shape[i].shapecoord[3][1];
				break;
			}

			if (shape[i].state)
			{
				Path[i].L[0][0] = 1.0f;
				Path[i].L[0][1] = -1.0f;
			}
			else
			{
				Path[i].L[0][0] = -1.0f;
				Path[i].L[0][1] = -1.0f;
			}
			Path[i].show = true;
		}
		start = true;
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("ComputerGraphics_Homework");

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
	glutTimerFunc(10, TimerFunction, 1);
	glutMotionFunc(Motion);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}