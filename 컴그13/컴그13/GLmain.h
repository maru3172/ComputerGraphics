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
	glm::vec3 vertices[4];
	glm::vec3 colors[4];
	int shapetype;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	Shape() : shapetype{ 2 }, ShapeState{ false }, position(0.0f), rotation(glm::radians(glm::vec3(10.0f, 10.0f, 0.0f))), scale(1.0f)
	{
		setRandomColor();
	}

	void setColor(const glm::vec3& color)
	{
		for (int i = 0; i < 4; i++)
		{
			colors[i] = color;
		}
	}

	void setRandomColor()
	{
		glm::vec3 randomColor(random(gen), random(gen), random(gen));
		setColor(randomColor);
	}

	void setVertex(int shapetype);
};

Shape shape[10];

void Shape::setVertex(int shapetype)
{
	if (shapetype == 1)
	{
		float height = sqrt(3.0f) / 2.0f;
		vertices[0] = glm::vec3(0.0f, 1.0f, 0.0f);
		vertices[1] = glm::vec3(-0.5f, 0.0f, -0.5f);
		vertices[2] = glm::vec3(0.5f, 0.0f, -0.5f);
		vertices[3] = glm::vec3(0.0, 0.0f, -0.5f);
	}
	else if (shapetype == 2)
	{
		vertices[0] = glm::vec3(-0.5f, -0.5f, 0.0f);
		vertices[1] = glm::vec3(0.5f, -0.5f, 0.0f);
		vertices[2] = glm::vec3(0.5f, 0.5f, 0.0f);
		vertices[3] = glm::vec3(-0.5f, 0.5f, 0.0f);
	}
}

bool start = false;

void main(int argc, char** argv)
{
	if (!start) {
		for (int i = 0; i < 10; i++) {
			if (i < 6) {
				shape[i].setVertex(2); // 정육면체
			}
			else {
				shape[i].setVertex(1); // 정사면체
			}
		}
		glm::mat4 rot(1.0f);
		shape[1].vertices[0] = glm::vec3(-0.5, -0.5, -0.5);
		shape[1].vertices[1] = glm::vec3(0.5, -0.5, -0.5);
		shape[1].vertices[2] = glm::vec3(0.5, 0.5, -0.5);
		shape[1].vertices[3] = glm::vec3(-0.5, 0.5, -0.5);

		shape[2].vertices[0] = glm::vec3(-0.5, -0.5, -0.5);
		shape[2].vertices[1] = glm::vec3(-0.5, 0.5, -0.5);
		shape[2].vertices[2] = glm::vec3(-0.5, 0.5, 0.5);
		shape[2].vertices[3] = glm::vec3(-0.5, -0.5, 0.5);

		shape[3].vertices[0] = glm::vec3(0.5, -0.5, -0.5);
		shape[3].vertices[1] = glm::vec3(0.5, 0.5, -0.5);
		shape[3].vertices[2] = glm::vec3(0.5, 0.5, 0.5);
		shape[3].vertices[3] = glm::vec3(0.5, -0.5, 0.5);

		shape[4].vertices[0] = glm::vec3(-0.5, 0.5, -0.5);
		shape[4].vertices[1] = glm::vec3(0.5, 0.5, -0.5);
		shape[4].vertices[2] = glm::vec3(0.5, 0.5, 0.5);
		shape[4].vertices[3] = glm::vec3(-0.5, 0.5, 0.5);

		shape[5].vertices[0] = glm::vec3(-0.5, -0.5, -0.5);
		shape[5].vertices[1] = glm::vec3(0.5, -0.5, -0.5);
		shape[5].vertices[2] = glm::vec3(0.5, -0.5, 0.5);
		shape[5].vertices[3] = glm::vec3(-0.5, -0.5, 0.5);

		shape[7].vertices[0] = glm::vec3(0.0f, 1.0f, 0.0f);
		shape[7].vertices[1] = glm::vec3(0.5f, 0.0f, -0.5f);
		shape[7].vertices[2] = glm::vec3(0.0f, 0.0f, 0.5f);
		shape[7].vertices[3] = glm::vec3(0.0, 0.0f, 0.5f);

		shape[8].vertices[0] = glm::vec3(0.0f, 1.0f, 0.0f);
		shape[8].vertices[1] = glm::vec3(0.0f, 0.0f, 0.5f);
		shape[8].vertices[2] = glm::vec3(-0.5f, 0.0f, -0.5f);
		shape[8].vertices[3] = glm::vec3(0.0, 0.0f, -0.5f);

		shape[9].vertices[0] = glm::vec3(-0.5f, 0.0f, -0.5f);
		shape[9].vertices[1] = glm::vec3(0.5f, 0.0f, -0.5f);
		shape[9].vertices[2] = glm::vec3(0.0f, 0.0f, 0.5f);
		shape[9].vertices[3] = glm::vec3(0.0, 0.0f, 0.5f);
		start = true;
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Example13");

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