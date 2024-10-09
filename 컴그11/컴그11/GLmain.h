#pragma once
#include "GLbasic.h"

bool start = false;

class Shape
{
public:
	GLfloat shapecoord[5][3];
	GLfloat color[5][3];
	int shapetype;
	bool done;
	bool Process[6];
	Shape() : shapetype{ 0 }, done{ true }
	{
		for (int i = 0; i < 6; i++)
		{
			Color(color[0][i]);
			Process[i] = true;
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

Shape shape[4];

void main(int argc, char** argv)
{
	if (!start)
	{
		// 처음 시작 - 선
		shape[0].shapecoord[0][0] = -0.5 + 0.25;
		shape[0].shapecoord[0][1] = 0.5 + 0.25;
		shape[0].shapecoord[1][0] = -0.5 - 0.25;
		shape[0].shapecoord[1][1] = 0.5 - 0.25;
		shape[0].shapetype = 1;

		// 처음 시작 - 삼각형
		shape[1].shapecoord[0][0] = 0.5;
		shape[1].shapecoord[0][1] = 0.5 + 0.25;
		shape[1].shapecoord[1][0] = 0.5 - 0.25;
		shape[1].shapecoord[1][1] = 0.5 - 0.25;
		shape[1].shapecoord[2][0] = 0.5 + 0.25;
		shape[1].shapecoord[2][1] = 0.5 - 0.25;
		shape[1].shapetype = 2;


		// 처음 시작 - 사각형
		shape[2].shapecoord[0][0] = -0.5 - 0.25;
		shape[2].shapecoord[0][1] = -0.5 + 0.25;
		shape[2].shapecoord[1][0] = -0.5 + 0.25;
		shape[2].shapecoord[1][1] = -0.5 + 0.25;
		shape[2].shapecoord[2][0] = -0.5 - 0.25;
		shape[2].shapecoord[2][1] = -0.5 - 0.25;
		shape[2].shapecoord[3][0] = -0.5 + 0.25;
		shape[2].shapecoord[3][1] = -0.5 - 0.25;
		shape[2].shapetype = 3;

		// 처음 시작 - 오각형
		shape[3].shapecoord[0][0] = 0.5;
		shape[3].shapecoord[0][1] = -0.5 + 0.25;
		shape[3].shapecoord[1][0] = 0.5 - 0.25;
		shape[3].shapecoord[1][1] = -0.5;
		shape[3].shapecoord[2][0] = 0.5 - 0.15;
		shape[3].shapecoord[2][1] = -0.5 - 0.25;
		shape[3].shapecoord[3][0] = 0.5 + 0.15;
		shape[3].shapecoord[3][1] = -0.5 - 0.25;
		shape[3].shapecoord[4][0] = 0.5 + 0.25;
		shape[3].shapecoord[4][1] = -0.5;
		shape[3].shapetype = 4;
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
	glutReshapeFunc(Reshape);
	glutMainLoop();
}