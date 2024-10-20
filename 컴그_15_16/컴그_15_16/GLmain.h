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
    std::vector<glm::vec3> colors;
    std::vector<unsigned int> faces;
    int shapetype;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    GLfloat radian, thetas;
    bool XPRot, YPRot, XMRot, YMRot, Swap, Scale, Circle, SwapUnD, UpDown;
    GLfloat speed;
    Shape() : shapetype(2), ShapeState(true), position(0.5f, 0.5f, 0.5f),
        rotation(glm::vec3(30.0f, -30.0f, 0.0f)),
        scale(0.2f, 0.2f, 0.2f), XPRot(false), YPRot(false), XMRot(false), YMRot(false), Swap(false), Scale(false), Circle(false), radian(0.0), thetas(0.0), SwapUnD(false), UpDown(false)
    {
        speed = 0.1 + (2 * 0.3);
        setRandomColor();
    }

    void setRandomColor()
    {
        colors.clear();
        for (size_t i = 0; i < vertices.size(); i++)
        {
            colors.push_back(glm::vec3(random(gen), random(gen), random(gen)));
        }
    }

    void loadFromObjFile(const char* filename)
    {
        FILE* file;
        char line[1000];
        float x, y, z;
        unsigned int v1, v2, v3;
        char* token;
        char* nextToken;

        fopen_s(&file, filename, "r");
        if (!file) {
            perror("파일 열기 오류");
            return;
        }

        // 기존 데이터 초기화
        vertices.clear();
        faces.clear();

        while (fgets(line, sizeof(line), file)) {
            // 줄 끝의 개행 문자 제거
            char* newline = strchr(line, '\n');
            if (newline) *newline = '\0';

            if (line[0] == 'v' && line[1] == ' ') {
                // 버텍스 파싱
                sscanf_s(line + 2, "%f %f %f", &x, &y, &z);
                glm::vec3 vertex = { x, y, z };
                vertices.push_back(vertex);
            }
            else if (line[0] == 'f' && line[1] == ' ') {
                // 페이스 파싱
                token = strtok_s(line + 2, " ", &nextToken);
                if (token) {
                    v1 = (unsigned int)atoi(token);
                    token = strtok_s(NULL, " ", &nextToken);
                    if (token) {
                        v2 = (unsigned int)atoi(token);
                        token = strtok_s(NULL, " ", &nextToken);
                        if (token) {
                            v3 = (unsigned int)atoi(token);
                            faces.push_back(v1 - 1);
                            faces.push_back(v2 - 1);
                            faces.push_back(v3 - 1);
                        }
                    }
                }
            }
        }
        fclose(file);
        setRandomColor();
    }
};

Shape shape[2];

void UpdateBuffer(const Shape& shape);

bool start = false;

void main(int argc, char** argv)
{
    if (!start) {
        shape[0].shapetype = 2;
        shape[1].shapetype = 1;
        shape[1].speed = 0.1 + (3 * 0.3);
        shape[1].position = glm::vec3(-0.5f, -0.5f, -0.5f);
        for (int i = 0; i < 2; i++)
        {
            if (shape[i].shapetype == 0)
            {
                shape[i].loadFromObjFile("Sphere.obj.txt");
            }
            else if (shape[i].shapetype == 1)
            {
                shape[i].loadFromObjFile("Cone.obj.txt");
            }
            else if (shape[i].shapetype == 2)
            {
                shape[i].loadFromObjFile("Cube.obj.txt");
            }
        }
        start = true;
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Example15 & 16");

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
    glutDisplayFunc(drawScene);
    glutKeyboardFunc(Keyboard);
    glutReshapeFunc(Reshape);
    glutMainLoop();
}