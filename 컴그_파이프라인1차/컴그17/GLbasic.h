#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <random>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#define M_PI 3.14
GLuint vao, vbo[2], ebo, axesVAO, axesVBO, spiralVAO, spiralVBO;
GLvoid drawScene(GLvoid);
GLvoid TimerFunction(int value);
GLvoid Keyboard(unsigned char key, int x, int y);
void convertXY(int x, int y, float& fx, float& fy);
void InitBuffer();
void drawAxes();
void make_vertexShaders();
void make_fragmentShaders();
void display();
void make_shaderProgram();
GLchar* vertexSource, * fragmentSource; //--- �ҽ��ڵ� ���� ����
GLuint vertexShader, fragmentShader; //--- ���̴� ��ü
GLuint shaderProgramID; //--- ���̴� ���α׷�
float bGCr = 0.0, bGCg = 0.0, bGCb = 0.0;
GLuint shaderPID;
GLvoid Reshape(int w, int h);
#define WIDTH 1024
#define HEIGHT 1080
float fx = 0.0, fy = 0.0, bfx = 0.0, bfy = 0.0, fx2 = 0.0, fy2 = 0.0;
#define MAX_LINE_LENGTH 1000
GLint g_window_w, g_window_h;

glm::vec3 cameraPos1 = glm::vec3(0.0f, 0.0f, 3.0f); // ���ʿ��� ī�޶�
glm::vec3 cameraDirection1 = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraUp1 = glm::vec3(0.0f, 1.0f, 0.0f); // ������ Y������ ����

glm::vec3 cameraPos2 = glm::vec3(0.0f, 0.0f, -3.0f); // �Ʒ��ʿ��� ī�޶�
glm::vec3 cameraDirection2 = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraUp2 = glm::vec3(0.0f, 1.0f, 0.0f); // ������ Y������ ����

glm::vec3 cameraPos3 = glm::vec3(0.0f, 0.0f, -5.0f); // �����ʿ��� ī�޶�
glm::vec3 cameraDirection3 = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraUp3 = glm::vec3(0.0f, 1.0f, 0.0f); // ������ Y������ ����

glm::vec3 cameraPos4 = glm::vec3(0.0f, 0.0f, 5.0f); // ���ʿ��� ī�޶�
glm::vec3 cameraDirection4 = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraUp4 = glm::vec3(0.0f, 1.0f, 0.0f); // ������ Y������ ����

void drawAxes()
{
	glm::vec3 axesVertices[] = {
		glm::vec3(-1.0f,  0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), // x�� ������ (������)
		glm::vec3(1.0f,  0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), // x�� ����
		glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), // y�� ������ (���)
		glm::vec3(0.0f,  1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),  // y�� ����
		glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), // z�� ������ (�Ķ���)
		glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)  // z�� ����
	};

	glGenVertexArrays(1, &axesVAO);
	glGenBuffers(1, &axesVBO);
	glBindVertexArray(axesVAO);
	glBindBuffer(GL_ARRAY_BUFFER, axesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(axesVertices), axesVertices, GL_STATIC_DRAW);

	// ��ġ �Ӽ�
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// ���� �Ӽ�
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

char* filetobuf(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;
	fptr = fopen(file, "rb"); // Open file for reading
	if (!fptr) // Return NULL on failure
		return NULL;
	fseek(fptr, 0, SEEK_END); // Seek to the end of the file
	length = ftell(fptr); // Find out how many bytes into the file we are
	buf = (char*)malloc(length + 1); // Allocate a buffer for the entire length of the file and a null terminator
	fseek(fptr, 0, SEEK_SET); // Go back to the beginning of the file
	fread(buf, length, 1, fptr); // Read the contents of the file in to the buffer
	fclose(fptr); // Close the file
	buf[length] = 0; // Null terminator
	return buf; // Return the buffer
}

GLvoid Reshape(int w, int h) {
	display();  // �ʿ��� ��쿡�� ȣ��
}

void display() {
	glClearColor(bGCr, bGCg, bGCb, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shaderProgramID);
	GLuint viewTransformLoc = glGetUniformLocation(shaderProgramID, "view");
	glm::mat4 vTransform1 = glm::mat4(1.0f);
	glm::mat4 vTransform2 = glm::mat4(1.0f);
	glm::mat4 vTransform3 = glm::mat4(1.0f);
	glm::mat4 vTransform4 = glm::mat4(1.0f);

	unsigned int viewPosLocation = glGetUniformLocation(shaderProgramID, "viewPos"); //--- viewPos �� ����: ī�޶� ��ġ

	// ù ��° ����Ʈ
	glViewport(0, 0, WIDTH / 2, HEIGHT / 2);
	vTransform1 = glm::lookAt(cameraPos1, cameraDirection1, cameraUp1);
	glUniform3f(viewPosLocation, cameraPos1.x, cameraPos1.y, cameraPos1.z);
	glUniformMatrix4fv(viewTransformLoc, 1, GL_FALSE, &vTransform1[0][0]);
	drawScene();

	// �� ��° ����Ʈ
	glViewport(WIDTH / 2, 0, WIDTH / 2, HEIGHT / 2);
	vTransform2 = glm::lookAt(cameraPos2, cameraDirection2, cameraUp2);
	glUniform3f(viewPosLocation, cameraPos2.x, cameraPos2.y, cameraPos2.z);
	glUniformMatrix4fv(viewTransformLoc, 1, GL_FALSE, &vTransform2[0][0]);
	drawScene();

	glViewport(0, HEIGHT / 2, WIDTH / 2, HEIGHT / 2);
	vTransform3 = glm::lookAt(cameraPos3, cameraDirection3, cameraUp3);
	glUniform3f(viewPosLocation, cameraPos4.x, cameraPos4.y, cameraPos4.z);
	glUniformMatrix4fv(viewTransformLoc, 1, GL_FALSE, &vTransform3[0][0]);
	drawScene();

	glViewport(WIDTH / 2, HEIGHT / 2, WIDTH / 2, HEIGHT / 2);
	vTransform4 = glm::lookAt(cameraPos4, cameraDirection4, cameraUp4);
	glUniform3f(viewPosLocation, cameraPos4.x, cameraPos4.y, cameraPos4.z);
	glUniformMatrix4fv(viewTransformLoc, 1, GL_FALSE, &vTransform4[0][0]);
	drawScene();

	glutSwapBuffers();
}

void convertXY(int w, int h, float& fx, float& fy)
{
	float x = WIDTH;
	float y = HEIGHT;
	float g_window_w = w;
	float g_window_h = h;
	fx = (2.0f * x / w) - 1.0f;
	fy = 1.0f - (2.0f * y / h);
}

void make_shaderProgram()
{
	make_vertexShaders(); //--- ���ؽ� ���̴� �����
	make_fragmentShaders(); //--- �����׸�Ʈ ���̴� �����
	//-- shader Program
	shaderProgramID = glCreateProgram();
	glAttachShader(shaderProgramID, vertexShader);
	glAttachShader(shaderProgramID, fragmentShader);
	glLinkProgram(shaderProgramID);
	//--- ���̴� �����ϱ�
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//--- Shader Program ����ϱ�
	glUseProgram(shaderProgramID);
}

void make_vertexShaders()
{
	vertexSource = filetobuf("vertex.glsl");
	//--- ���ؽ� ���̴� ��ü �����
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//--- ���̴� �ڵ带 ���̴� ��ü�� �ֱ�
	glShaderSource(vertexShader, 1, (const GLchar**)&vertexSource, 0);
	//--- ���ؽ� ���̴� �������ϱ�
	glCompileShader(vertexShader);
	//--- �������� ����� ���� ���� ���: ���� üũ
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cerr << "ERROR: vertex shader ������ ����\n" << errorLog << std::endl;
		return;
	}
}

void make_fragmentShaders()
{
	fragmentSource = filetobuf("fragment.glsl");
	//--- �����׸�Ʈ ���̴� ��ü �����
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//--- ���̴� �ڵ带 ���̴� ��ü�� �ֱ�
	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, 0);
	//--- �����׸�Ʈ ���̴� ������
	glCompileShader(fragmentShader);
	//--- �������� ����� ���� ���� ���: ������ ���� üũ
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR: fragment shader ������ ����\n" << errorLog << std::endl;
		return;
	}
}