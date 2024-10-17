#pragma once
#include "GLbasic.h"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> random1(0, 5);
std::uniform_int_distribution<int> random2(6, 9);
std::uniform_real_distribution<float> random(0, 1);

class Shape
{
public:
	bool ShapeState;
	glm::vec3 vertices[8];
	glm::vec3 colors[8];
	int shapetype;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	Shape() : shapetype{ 2 }, ShapeState{ true }, position(0.0f), rotation(glm::radians(glm::vec3(30.0f, -30.0f, 0.0f))), scale(1.0f)
	{
		setRandomColor();
	}

	void setRandomColor()
	{
		for (int i = 0; i < 8; i++)
		{
			glm::vec3 randomColor(random(gen), random(gen), random(gen));
			colors[i] = randomColor;
		}
	}

	void setVertex()
	{
		if (this->shapetype == 1)
		{
			this->vertices[0] = glm::vec3(-0.5, -0.5, 0.5);
			this->vertices[1] = glm::vec3(0.5, -0.5, 0.5);
			this->vertices[2] = glm::vec3(0.5, 0.5, 0.5);
			this->vertices[3] = glm::vec3(-0.5, 0.5, 0.5);
			this->vertices[4] = glm::vec3(-0.5, -0.5, -0.5);
			this->vertices[5] = glm::vec3(0.5, -0.5, -0.5);
			this->vertices[6] = glm::vec3(0.5, 0.5, -0.5);
			this->vertices[7] = glm::vec3(-0.5, 0.5, -0.5);
		}
		else if (this->shapetype == 2)
		{
			this->vertices[0] = glm::vec3(-0.5, -0.5, 0.5);
			this->vertices[1] = glm::vec3(0.5, -0.5, 0.5);
			this->vertices[2] = glm::vec3(0.5, -0.5, -0.5);
			this->vertices[3] = glm::vec3(-0.5, -0.5, -0.5);
			this->vertices[4] = glm::vec3(0, 0.5, 0);
		}
	}
};

Shape shape[2];

bool start = false;

void main(int argc, char** argv)
{
	if (!start) {
		shape[0].shapetype = 1;
		shape[1].shapetype = 2;
		for (int i = 0; i < 2; i++)
		{
			shape[i].setVertex();
		}
		start = true;
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Example14");

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
	glutSpecialFunc(SpecialKeyboard);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}