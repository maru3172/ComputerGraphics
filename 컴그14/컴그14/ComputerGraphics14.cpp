#include "GLmain.h"

bool HSurface = false, Wire = false, XPRot = false, YPRot = false, XMRot = false, YMRot = false;

GLvoid drawScene()
{
	glClearColor(bGCr, bGCg, bGCb, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shaderProgramID);

	glBindVertexArray(axesVAO);
	glm::mat4 axesTransform = glm::mat4(1.0f);
	GLuint transformLoc = glGetUniformLocation(shaderProgramID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(axesTransform));
	glDrawArrays(GL_LINES, 0, 4);

	glBindVertexArray(vao);
	for (int i = 0; i < 2; i++)
	{
		if (shape[i].ShapeState)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, shape[i].position);
			model = glm::rotate(model, shape[i].rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, shape[i].rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, shape[i].rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, shape[i].scale);
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));

			UpdateBuffer(i);

			if (Wire)
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			else 
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			if (shape[i].shapetype == 1)  // 육면체
			{
				glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
			}
			else if (shape[i].shapetype == 2)  // 사각뿔
			{
				glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, (void*)(36 * sizeof(GLuint)));
			}
		}
	}
	glutSwapBuffers();
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'c':
		shape[0].ShapeState = true;
		shape[0].shapetype = 1;  // 육면체
		shape[1].ShapeState = false;
		break;
	case 'p':
		shape[1].ShapeState = true;
		shape[1].shapetype = 2;  // 사각뿔
		shape[0].ShapeState = false;
		break;
	case 'h':
		if (HSurface)
		{
			glDisable(GL_CULL_FACE);
			HSurface = false;
		}
		else
		{
			glEnable(GL_CULL_FACE);
			HSurface = true;
		}
		break;
	case 'w':
		if (Wire)
		{
			Wire = false;
		}
		else
		{
			Wire = true;
		}
		break;
	case 'x':
		XPRot = true;
		XMRot = false;
		break;
	case 'X':
		XPRot = false;
		XMRot = true;
		break;
	case 'y':
		YPRot = true;
		YMRot = false;
		break;
	case 'Y':
		YPRot = false;
		YMRot = true;
		break;
	case 's':
		shape[0].shapetype = 1;
		shape[1].shapetype = 2;
		for (int i = 0; i < 2; i++)
		{
			shape[i].setVertex();
			shape[i].rotation[0] = glm::radians(30.0f);
			shape[i].rotation[1] = glm::radians(-30.0f);
			shape[i].position[0] = 0.0f;
			shape[i].position[1] = 0.0f;
		}
		XPRot = false;
		XMRot = false;
		YPRot = false;
		YMRot = false;
		break;
	case 'q':
		glutLeaveMainLoop();
		break;
	}
	glutPostRedisplay();
	if (XPRot || XMRot || YPRot || YMRot)
	{
		glutTimerFunc(100, TimerFunction, 1);
	}
}

GLvoid SpecialKeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		for (int i = 0; i < 2; i++)
		{
			shape[i].position[1] += 0.1;
		}
		break;
	case GLUT_KEY_DOWN:
		for (int i = 0; i < 2; i++)
		{
			shape[i].position[1] -= 0.1;
		}
		break;
	case GLUT_KEY_LEFT:
		for (int i = 0; i < 2; i++)
		{
			shape[i].position[0] -= 0.1;
		}
		break;
	case GLUT_KEY_RIGHT:
		for (int i = 0; i < 2; i++)
		{
			shape[i].position[0] += 0.1;
		}
		break;
	}
	glutPostRedisplay();
}

void InitBuffer()
{
	glGenVertexArrays(1, &vao); // VAO 할당 및 바인딩
	glBindVertexArray(vao);

	glGenBuffers(2, vbo); // 2개의 VBO 할당

	// 버텍스 좌표 데이터 처리
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, (8 + 5) * 3 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	// 색상 데이터 처리
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, (8 + 5) * 3 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	// 인덱스 데이터 처리
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	// 육면체와 사각뿔의 인덱스 데이터
	GLuint indices[] = {
		// 육면체 인덱스
		0, 1, 2, 2, 3, 0,
		1, 5, 6, 6, 2, 1,
		5, 4, 7, 7, 6, 5,
		4, 0, 3, 3, 7, 4,
		3, 2, 6, 6, 7, 3,
		4, 5, 1, 1, 0, 4,
		// 사각뿔 인덱스 (육면체 정점 이후부터 시작)
		8, 9, 12,
		9, 10, 12,
		10, 11, 12,
		11, 8, 12,
		10, 9, 8, 10, 8, 11
	};

	// 인덱스 데이터 EBO에 복사
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

	// 초기 도형 상태 설정
	shape[0].ShapeState = false;
	shape[1].ShapeState = false;
	shape[0].shapetype = 1;  // 육면체
	shape[1].shapetype = 2;  // 사각뿔

	drawAxes();
}

void UpdateBuffer(int shapeIndex)
{
	if (shape[shapeIndex].shapetype == 1)  // 육면체
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, 8 * 3 * sizeof(GLfloat), shape[shapeIndex].vertices);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, 8 * 3 * sizeof(GLfloat), shape[shapeIndex].colors);
	}
	else if (shape[shapeIndex].shapetype == 2)  // 사각뿔
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferSubData(GL_ARRAY_BUFFER, 8 * 3 * sizeof(GLfloat), 5 * 3 * sizeof(GLfloat), shape[shapeIndex].vertices);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferSubData(GL_ARRAY_BUFFER, 8 * 3 * sizeof(GLfloat), 5 * 3 * sizeof(GLfloat), shape[shapeIndex].colors);
	}
}

GLvoid TimerFunction(int value)
{
	for (int i = 0; i < 2; i++)
	{
		if (XPRot)
		{
			shape[i].rotation[0] += 0.005;
		}
		else if (XMRot)
		{
			shape[i].rotation[0] -= 0.005;
		}
		if (shape[i].rotation[0] < 0)
		{
			shape[i].rotation[0] = 360.0;
		}
		else if (shape[i].rotation[0] > 360)
		{
			shape[i].rotation[0] = 0;
		}

		if (YPRot)
		{
			shape[i].rotation[1] += 0.005;
		}
		else if (YMRot)
		{
			shape[i].rotation[1] -= 0.005;
		}
		if (shape[i].rotation[1] > 0)
		{
			shape[i].rotation[1] = -360.0;
		}
		else if (shape[i].rotation[1] < -360)
		{
			shape[i].rotation[1] = 0;
		}
	}
	
	glutPostRedisplay();
	if (XPRot || XMRot || YPRot || YMRot)
	{
		glutTimerFunc(10, TimerFunction, 1);
	}
}