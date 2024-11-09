#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <random>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
GLuint vao, vbo[2], ebo, Linearvao, Linearvbo[2], BoxVao, BoxVbo[2], BoxEbo, LinearPathVao, LinearPathVbo[2];
GLvoid drawScene(GLvoid);
GLvoid TimerFunction(int value);
GLvoid Mouse(int button, int state, int x, int y);
void convertXY(int x, int y, float& fx, float& fy);
void UpdateBuffer();
void Color(float& color);
void InitBuffer();
GLvoid Motion(int x, int y);
void make_vertexShaders();
void make_fragmentShaders();
void make_shaderProgram();
void LinearBuffer();
void BoxBuffer();
void PathBuffer();
GLchar* vertexSource, * fragmentSource; //--- 소스코드 저장 변수
GLuint vertexShader, fragmentShader; //--- 세이더 객체
GLuint shaderProgramID; //--- 셰이더 프로그램
GLvoid Keyboard(unsigned char key, int x, int y);
float bGCr = 1.0, bGCg = 1.0, bGCb = 1.0;
GLuint shaderPID;
GLvoid Reshape(int w, int h);
#define WIDTH 800
#define HEIGHT 600
#define PI 3.14159265359
float fx = 0.0, fy = 0.0, bfx = 0.0, bfy = 0.0, fx2 = 0.0, fy2 = 0.0;

void LinearBuffer()
{
	glGenVertexArrays(1, &Linearvao);
	glBindVertexArray(Linearvao);

	glGenBuffers(2, Linearvbo);
	glBindBuffer(GL_ARRAY_BUFFER, Linearvbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 2 * 3 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	// 색상 속성
	glBindBuffer(GL_ARRAY_BUFFER, Linearvbo[1]);
	glBufferData(GL_ARRAY_BUFFER, 2 * 3 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
}

void PathBuffer()
{
	glGenVertexArrays(1, &LinearPathVao);
	glBindVertexArray(LinearPathVao);

	glGenBuffers(2, LinearPathVbo);
	glBindBuffer(GL_ARRAY_BUFFER, LinearPathVbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 3 * 2 * 3 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	// 색상 속성
	glBindBuffer(GL_ARRAY_BUFFER, LinearPathVbo[1]);
	glBufferData(GL_ARRAY_BUFFER, 3 * 2 * 3 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
}

void BoxBuffer()
{
	glGenVertexArrays(1, &BoxVao);
	glBindVertexArray(BoxVao);

	glGenBuffers(2, BoxVbo);
	glBindBuffer(GL_ARRAY_BUFFER, BoxVbo[0]);

	glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	// 색상 속성
	glBindBuffer(GL_ARRAY_BUFFER, BoxVbo[1]);
	glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &BoxEbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BoxEbo);
	GLuint indices[] = {
		0, 1, 2,
		0, 2, 3
	};
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);
}

bool Crash(float shape1X1, float shape1X2, float shape2XX1, float shape2XX2, float shape1Y1, float shape1Y2, float shape2YY1, float shape2YY2)
{
	if (shape1X1 <= shape2XX2 && shape2XX1 <= shape1X2 && shape1Y1 <= shape2YY2 && shape2YY1 <= shape1Y2)
		return true;
	return false;
}


void Color(float& color)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> random(0, 1);
	color = random(gen);
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

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void convertXY(int x, int y, float& fx, float& fy)
{
	int w = WIDTH;
	int h = HEIGHT;
	fx = (2.0f * x / w) - 1.0f;
	fy = 1.0f - (2.0f * y / h);
}

void make_shaderProgram()
{
	make_vertexShaders(); //--- 버텍스 세이더 만들기
	make_fragmentShaders(); //--- 프래그먼트 세이더 만들기
	//-- shader Program
	shaderProgramID = glCreateProgram();
	glAttachShader(shaderProgramID, vertexShader);
	glAttachShader(shaderProgramID, fragmentShader);
	glLinkProgram(shaderProgramID);
	//--- 세이더 삭제하기
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//--- Shader Program 사용하기
	glUseProgram(shaderProgramID);
}

void make_vertexShaders()
{
	vertexSource = filetobuf("vertex.glsl");
	//--- 버텍스 세이더 객체 만들기
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//--- 세이더 코드를 세이더 객체에 넣기
	glShaderSource(vertexShader, 1, (const GLchar**)&vertexSource, 0);
	//--- 버텍스 세이더 컴파일하기
	glCompileShader(vertexShader);
	//--- 컴파일이 제대로 되지 않은 경우: 에러 체크
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
}

void make_fragmentShaders()
{
	fragmentSource = filetobuf("fragment.glsl");
	//--- 프래그먼트 세이더 객체 만들기
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//--- 세이더 코드를 세이더 객체에 넣기
	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, 0);
	//--- 프래그먼트 세이더 컴파일
	glCompileShader(fragmentShader);
	//--- 컴파일이 제대로 되지 않은 경우: 컴파일 에러 체크
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR: fragment shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
}