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
    bool model;
    int shapetype;
    int theta;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    GLfloat radian, thetas;
    bool Front, Side;
    GLfloat speed;
    Shape() : shapetype(2), ShapeState(false), position(0),
        rotation(glm::vec3(30.0f, -30.0f, 0.0f)),
        scale(1.0f, 1.0f, 1.0f), Front(false), Side(false), theta(0), model(false)
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

    void loadFromObjFile(const char* filename)
    {
        FILE* file;
        char line[1000];
        float x, y, z, x1, y1, z1;
        unsigned int v1, v2, v3;        // vertex indices
        unsigned int n1, n2, n3;        // normal indices

        fopen_s(&file, filename, "r");
        if (!file) {
            perror("ÆÄÀÏ ¿­±â ¿À·ù");
            return;
        }

        // ±âÁ¸ µ¥ÀÌÅÍ ÃÊ±âÈ­
        vertices.clear();
        faces.clear();
        normal.clear();

        // ÆÄÀÏ ÆÄ½Ì
        while (fgets(line, sizeof(line), file)) {
            if (line[0] == '#' || line[0] == 'g' || strlen(line) == 0)
                continue;

            if (line[0] == 'v' && line[1] == ' ') {
                // ¹öÅØ½º ÆÄ½Ì
                if (sscanf_s(line + 2, "%f %f %f", &x, &y, &z) == 3) {
                    vertices.push_back(glm::vec3(x, y, z));
                }
            }
            else if (line[0] == 'v' && line[1] == 'n' && line[2] == ' ') {
                // ³ë¸Ö º¤ÅÍ ÆÄ½Ì
                if (sscanf_s(line + 2, "%f %f %f", &x, &y, &z) == 3) {
                    normal.push_back(glm::vec3(x, y, z));
                }
            }
            
            if (filename == "Cube.obj.txt")
            {
                if (line[0] == 'f' && line[1] == ' ') {
                    // ³ë¸Ö º¤ÅÍ ÆÄ½Ì
                    if (sscanf_s(line + 2, "%f//%f %f//%f %f//%f", &x, &y, &z, &x1, &y1, &z1) == 6) {
                        faces.push_back(x - 1);
                        faces.push_back(y - 1);
                        faces.push_back(z - 1);
                        faces.push_back(x1 - 1);
                        faces.push_back(y1 - 1);
                        faces.push_back(z1 - 1);
                    }
                }
            }
            else
            {
                if (line[0] == 'f' && line[1] == ' ') {
                    // ³ë¸Ö º¤ÅÍ ÆÄ½Ì
                    if (sscanf_s(line + 2, "%f %f %f", &x, &y, &z) == 3) {
                        faces.push_back(x - 1);
                        faces.push_back(y - 1);
                        faces.push_back(z - 1);
                    }
                }
            }
        }

        fclose(file);
        setRandomColor();
    }
};

Shape shape[11];

void UpdateBuffer(const Shape& shape);

bool start = false, model = false;

void main(int argc, char** argv)
{
    if (!start) {
        for (int i = 0; i < 11; i++)
        {
            if (model)
            {
                shape[i].loadFromObjFile("Cube.obj.txt");
                shape[i].model = true;
                shape[0].ShapeState = true;
            }
        }
        if (!model)
        {
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
        }
        for (int i = 0; i < 6; i++)
        {
            shape[i].normal.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
            shape[i].normal.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
            shape[i].normal.push_back(glm::vec3(-0.5f, 0.5f, 0.5f));
            shape[i].normal.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
            shape[i].ShapeState = true;
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