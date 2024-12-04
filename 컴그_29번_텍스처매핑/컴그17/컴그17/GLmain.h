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
    std::vector<glm::vec2> texcoords;
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
            perror("파일 열기 오류");
            return;
        }

        // 기존 데이터 초기화
        vertices.clear();
        faces.clear();
        normal.clear();

        // 파일 파싱
        while (fgets(line, sizeof(line), file)) {
            if (line[0] == '#' || line[0] == 'g' || strlen(line) == 0)
                continue;

            if (line[0] == 'v' && line[1] == ' ') {
                // 버텍스 파싱
                if (sscanf_s(line + 2, "%f %f %f", &x, &y, &z) == 3) {
                    vertices.push_back(glm::vec3(x, y, z));
                }
            }
            else if (line[0] == 'v' && line[1] == 'n' && line[2] == ' ') {
                // 노멀 벡터 파싱
                if (sscanf_s(line + 2, "%f %f %f", &x, &y, &z) == 3) {
                    normal.push_back(glm::vec3(x, y, z));
                }
            }
            
            if (filename == "Cube.obj.txt")
            {
                if (line[0] == 'f' && line[1] == ' ') {
                    // 노멀 벡터 파싱
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
                    // 노멀 벡터 파싱
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
            shape[1].shapetype = 1;

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
            shape[2].shapetype = 2;

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
            shape[3].shapetype = 3;

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
            shape[5].shapetype = 1;

            shape[6].vertices.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
            shape[6].vertices.push_back(glm::vec3(-0.5f, 0.0f, 0.5f));
            shape[6].vertices.push_back(glm::vec3(0.5f, 0.0f, 0.5f));
            shape[6].faces.push_back(0);
            shape[6].faces.push_back(1);
            shape[6].faces.push_back(2);
            shape[6].shapetype = 2;

            shape[7].vertices.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
            shape[7].vertices.push_back(glm::vec3(0.5f, 0.0f, -0.5f));
            shape[7].vertices.push_back(glm::vec3(0.5f, 0.0f, 0.5f));
            shape[7].faces.push_back(0);
            shape[7].faces.push_back(1);
            shape[7].faces.push_back(2);
            shape[7].shapetype = 3;

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
            shape[9].shapetype = 1;

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
            shape[10].shapetype = 2;

            // 앞면 (shape[0])
            shape[0].texcoords.push_back(glm::vec2(0.0f, 0.0f));
            shape[0].texcoords.push_back(glm::vec2(1.0f, 0.0f));
            shape[0].texcoords.push_back(glm::vec2(1.0f, 1.0f));
            shape[0].texcoords.push_back(glm::vec2(0.0f, 1.0f));

            // 뒷면 (shape[1])
            shape[1].texcoords.push_back(glm::vec2(0.0f, 0.0f));
            shape[1].texcoords.push_back(glm::vec2(1.0f, 0.0f));
            shape[1].texcoords.push_back(glm::vec2(1.0f, 1.0f));
            shape[1].texcoords.push_back(glm::vec2(0.0f, 1.0f));

            // 왼쪽면 (shape[2])
            shape[2].texcoords.push_back(glm::vec2(0.0f, 0.0f));
            shape[2].texcoords.push_back(glm::vec2(1.0f, 0.0f));
            shape[2].texcoords.push_back(glm::vec2(1.0f, 1.0f));
            shape[2].texcoords.push_back(glm::vec2(0.0f, 1.0f));

            // 오른쪽면 (shape[3])
            shape[3].texcoords.push_back(glm::vec2(0.0f, 0.0f));
            shape[3].texcoords.push_back(glm::vec2(1.0f, 0.0f));
            shape[3].texcoords.push_back(glm::vec2(1.0f, 1.0f));
            shape[3].texcoords.push_back(glm::vec2(0.0f, 1.0f));

            // 윗면 (shape[4])
            shape[4].texcoords.push_back(glm::vec2(0.0f, 0.0f));
            shape[4].texcoords.push_back(glm::vec2(1.0f, 0.0f));
            shape[4].texcoords.push_back(glm::vec2(1.0f, 1.0f));
            shape[4].texcoords.push_back(glm::vec2(0.0f, 1.0f));

            // 아랫면 (shape[5])
            shape[5].texcoords.push_back(glm::vec2(0.0f, 0.0f));
            shape[5].texcoords.push_back(glm::vec2(1.0f, 0.0f));
            shape[5].texcoords.push_back(glm::vec2(1.0f, 1.0f));
            shape[5].texcoords.push_back(glm::vec2(0.0f, 1.0f));

            // 피라미드 텍스처 좌표 (6-9번 삼각형 면)
            // 앞쪽 피라미드 면 (shape[6])
            shape[6].texcoords.push_back(glm::vec2(0.5f, 1.0f)); // 꼭대기
            shape[6].texcoords.push_back(glm::vec2(0.0f, 0.0f)); // 왼쪽 아래
            shape[6].texcoords.push_back(glm::vec2(1.0f, 0.0f)); // 오른쪽 아래

            // 오른쪽 피라미드 면 (shape[7])
            shape[7].texcoords.push_back(glm::vec2(0.5f, 1.0f)); // 꼭대기
            shape[7].texcoords.push_back(glm::vec2(0.0f, 0.0f)); // 왼쪽 아래
            shape[7].texcoords.push_back(glm::vec2(1.0f, 0.0f)); // 오른쪽 아래

            // 뒤쪽 피라미드 면 (shape[8])
            shape[8].texcoords.push_back(glm::vec2(0.5f, 1.0f)); // 꼭대기
            shape[8].texcoords.push_back(glm::vec2(0.0f, 0.0f)); // 왼쪽 아래
            shape[8].texcoords.push_back(glm::vec2(1.0f, 0.0f)); // 오른쪽 아래

            // 왼쪽 피라미드 면 (shape[9])
            shape[9].texcoords.push_back(glm::vec2(0.5f, 1.0f)); // 꼭대기
            shape[9].texcoords.push_back(glm::vec2(0.0f, 0.0f)); // 왼쪽 아래
            shape[9].texcoords.push_back(glm::vec2(1.0f, 0.0f)); // 오른쪽 아래

            // 바닥면 (shape[10])
            shape[10].texcoords.push_back(glm::vec2(0.0f, 0.0f));
            shape[10].texcoords.push_back(glm::vec2(0.0f, 1.0f));
            shape[10].texcoords.push_back(glm::vec2(1.0f, 1.0f));
            shape[10].texcoords.push_back(glm::vec2(1.0f, 0.0f));
        }
        for (int i = 0; i < 11; i++)
        {
            shape[i].normal.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
            shape[i].normal.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
            shape[i].normal.push_back(glm::vec3(-0.5f, 0.5f, 0.5f));
            shape[i].normal.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
            if (i < 6)
            {
                shape[i].ShapeState = true;
            }
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
    InitTexture();
    InitBuffer();
    glutTimerFunc(10, TimerFunction, 1);
    glutDisplayFunc(display);
    glutKeyboardFunc(Keyboard);
    glutReshapeFunc(Reshape);
    glutMainLoop();
}