#pragma once
#include "GLbasic.h"

#define MAX_VERTICES 1000
#define PI 0.314

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> random1(0, 5);
std::uniform_int_distribution<int> random2(6, 9);
std::uniform_real_distribution<float> random(0, 1);
std::uniform_int_distribution<int> random3(0, 2);

class Shape
{
public:
    bool ShapeState;
    std::vector<glm::vec3> vertices;
    std::vector<float> colors;
    std::vector<glm::vec3> normal;
    std::vector<unsigned int> faces;
    int shapetype;
    int theta;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    GLfloat radian, thetas;
    bool Front, Side;
    GLfloat speed;
    Shape() : shapetype(2), ShapeState(false), position(0.0f),
        rotation(glm::vec3(30.0f, -30.0f, 0.0f)),
        scale(0.5f, 0.5f, 0.5f), Front(false), Side(false), theta(0)
    {
        speed = 0.1 + (2 * 0.3);
        setRandomColor();
    }

    void setRandomColor()
    {
        colors.clear();
        for (int i = 0; i < 3; i++)
        {
            colors.push_back(random(gen));
        }
    }
};

Shape shape[11];

void UpdateBuffer(const Shape& shape);

bool start = false;

void main(int argc, char** argv)
{
    if (!start) {
        for (int i = 0; i < 6; i++)
        {
            shape[i].ShapeState = true;
        }
        shape[0].vertices.push_back(glm::vec3(-0.5f, -0.5f, 0.5f));
        shape[0].vertices.push_back(glm::vec3(0.5f, -0.5f, 0.5f));
        shape[0].vertices.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
        shape[0].vertices.push_back(glm::vec3(-0.5f, 0.5f, 0.5f));
        shape[0].faces.push_back(0);
        shape[0].faces.push_back(1);
        shape[0].faces.push_back(2);
        shape[0].faces.push_back(0);
        shape[0].faces.push_back(2);
        shape[0].faces.push_back(3);

        shape[1].vertices.push_back(glm::vec3(-0.5f, -0.5f, -0.5f));
        shape[1].vertices.push_back(glm::vec3(0.5f, -0.5f, -0.5f));
        shape[1].vertices.push_back(glm::vec3(0.5f, 0.5f, -0.5f));
        shape[1].vertices.push_back(glm::vec3(-0.5f, 0.5f, -0.5f));
        shape[1].faces.push_back(0);
        shape[1].faces.push_back(2);
        shape[1].faces.push_back(1);
        shape[1].faces.push_back(0);
        shape[1].faces.push_back(3);
        shape[1].faces.push_back(2);

        shape[2].vertices.push_back(glm::vec3(-0.5f, -0.5f, -0.5f));
        shape[2].vertices.push_back(glm::vec3(-0.5f, 0.5f, -0.5f));
        shape[2].vertices.push_back(glm::vec3(-0.5f, 0.5f, 0.5f));
        shape[2].vertices.push_back(glm::vec3(-0.5f, -0.5f, 0.5f));
        shape[2].faces.push_back(0);
        shape[2].faces.push_back(2);
        shape[2].faces.push_back(1);
        shape[2].faces.push_back(0);
        shape[2].faces.push_back(3);
        shape[2].faces.push_back(2);

        shape[3].vertices.push_back(glm::vec3(0.5f, -0.5f, -0.5f));
        shape[3].vertices.push_back(glm::vec3(0.5f, 0.5f, -0.5f));
        shape[3].vertices.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
        shape[3].vertices.push_back(glm::vec3(0.5f, -0.5f, 0.5f));
        shape[3].faces.push_back(0);
        shape[3].faces.push_back(1);
        shape[3].faces.push_back(2);
        shape[3].faces.push_back(0);
        shape[3].faces.push_back(2);
        shape[3].faces.push_back(3);

        shape[4].vertices.push_back(glm::vec3(-0.5f, 0.5f, -0.5f));
        shape[4].vertices.push_back(glm::vec3(0.5f, 0.5f, -0.5f));
        shape[4].vertices.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
        shape[4].vertices.push_back(glm::vec3(-0.5f, 0.5f, 0.5f));
        shape[4].faces.push_back(0);
        shape[4].faces.push_back(2);
        shape[4].faces.push_back(1);
        shape[4].faces.push_back(0);
        shape[4].faces.push_back(3);
        shape[4].faces.push_back(2);

        shape[5].vertices.push_back(glm::vec3(-0.5f, -0.5f, -0.5f));
        shape[5].vertices.push_back(glm::vec3(0.5f, -0.5f, -0.5f));
        shape[5].vertices.push_back(glm::vec3(0.5f, -0.5f, 0.5f));
        shape[5].vertices.push_back(glm::vec3(-0.5f, -0.5f, 0.5f));
        shape[5].faces.push_back(0);
        shape[5].faces.push_back(2);
        shape[5].faces.push_back(1);
        shape[5].faces.push_back(0);
        shape[5].faces.push_back(3);
        shape[5].faces.push_back(2);

        shape[6].vertices.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
        shape[6].vertices.push_back(glm::vec3(-0.5f, 0.0f, 0.5f));
        shape[6].vertices.push_back(glm::vec3(0.5f, 0.0f, 0.5f));
        shape[6].faces.push_back(0);
        shape[6].faces.push_back(1);
        shape[6].faces.push_back(2);

        shape[7].vertices.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
        shape[7].vertices.push_back(glm::vec3(0.5f, 0.0f, -0.5f));
        shape[7].vertices.push_back(glm::vec3(0.5f, 0.0f, 0.5f));
        shape[7].faces.push_back(0);
        shape[7].faces.push_back(1);
        shape[7].faces.push_back(2);

        shape[8].vertices.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
        shape[8].vertices.push_back(glm::vec3(-0.5f, 0.0f, -0.5f));
        shape[8].vertices.push_back(glm::vec3(0.5f, 0.0f, -0.5f));
        shape[8].faces.push_back(0);
        shape[8].faces.push_back(1);
        shape[8].faces.push_back(2);

        shape[9].vertices.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
        shape[9].vertices.push_back(glm::vec3(-0.5f, 0.0f, 0.5f));
        shape[9].vertices.push_back(glm::vec3(-0.5f, 0.0f, -0.5f));
        shape[9].faces.push_back(0);
        shape[9].faces.push_back(1);
        shape[9].faces.push_back(2);

        shape[10].vertices.push_back(glm::vec3(-0.5f, 0.0f, -0.5f));
        shape[10].vertices.push_back(glm::vec3(-0.5f, 0.0f, 0.5f));
        shape[10].vertices.push_back(glm::vec3(0.5f, 0.0f, 0.5f));
        shape[10].vertices.push_back(glm::vec3(0.5f, 0.0f, -0.5f));
        shape[10].faces.push_back(0);
        shape[10].faces.push_back(1);
        shape[10].faces.push_back(2);
        shape[10].faces.push_back(0);
        shape[10].faces.push_back(2);
        shape[10].faces.push_back(3);
        for (int i = 0; i < 11; i++)
        {
            shape[i].setRandomColor();
            if (i >= 6 && i <= 9)
                shape[i].shapetype = 1;
        }
        for (int i = 0; i < 11; i++)
        {
            shape[i].normal.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
            shape[i].normal.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
            shape[i].normal.push_back(glm::vec3(-0.5f,0.5f, 0.5f));
            shape[i].normal.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
        }
        start = true;
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Example17");

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Unable to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
        std::cout << "GLEW Initialized\n";

    glEnable(GL_DEPTH_TEST);
    make_shaderProgram();
    InitBuffer();
    glutTimerFunc(10, TimerFunction, 1);
    glutDisplayFunc(display);
    glutKeyboardFunc(Keyboard);
    glutReshapeFunc(Reshape);
    glutMainLoop();
}