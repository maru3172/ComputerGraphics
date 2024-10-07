#include "GLmain.h"

bool states1 = false;
bool states2 = false;
bool states3 = false;
bool states4 = false;
bool call = false;
bool call2 = false;

void initializeShapes() {
	for (int i = 0; i < 4; i++) {
		shape[i].shapecoord[0][0] = 1.0;
		shape[i].shapecoord[0][1] = 1.0;
		shape[i].shapecoord[1][0] = 0.9;
		shape[i].shapecoord[1][1] = 0.7;
		shape[i].shapecoord[2][0] = 1.1;
		shape[i].shapecoord[2][1] = 0.7;
		shape[i].Way = 0;
		shape[i].speed = 0.01 + (i * 0.03); // 각 삼각형마다 다른 속도 설정
	}
}

void initializeShapes2() {
	for (int i = 0; i < 4; i++) {
		shape[i].shapecoord[0][0] = 0.0;
		shape[i].shapecoord[0][1] = 0.0;
		shape[i].shapecoord[1][0] = -0.1;
		shape[i].shapecoord[1][1] = -0.3;
		shape[i].shapecoord[2][0] = 0.1;
		shape[i].shapecoord[2][1] = -0.3;
		shape[i].r = 0.1;  // 초기 반지름
		shape[i].theta = i * (PI / 2);  // 각 삼각형의 시작 각도를 다르게 설정
		shape[i].speed = 0.05 + (i * 0.02);  // 각 삼각형마다 다른 속도 설정
	}
}

void moveTriangle(Shape& s, float dx, float dy) {
	for (int j = 0; j < 3; j++) {
		s.shapecoord[j][0] += dx;
		s.shapecoord[j][1] += dy;
	}
}
float centerX, centerY;

void rotateTriangle(Shape& s, float angle) {
	float centerX = (s.shapecoord[0][0] + s.shapecoord[1][0] + s.shapecoord[2][0]) / 3;
	float centerY = (s.shapecoord[0][1] + s.shapecoord[1][1] + s.shapecoord[2][1]) / 3;
	float radians = angle * PI / 180;
	for (int j = 0; j < 3; j++) {
		float x = s.shapecoord[j][0] - centerX;
		float y = s.shapecoord[j][1] - centerY;
		s.shapecoord[j][0] = x * cos(radians) - y * sin(radians) + centerX;
		s.shapecoord[j][1] = x * sin(radians) + y * cos(radians) + centerY;
	}
}

GLvoid drawScene()
{
	glClearColor(bGCr, bGCg, bGCb, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shaderProgramID);
	UpdateBuffer();
	glBindVertexArray(vao);

	if (frame)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLES, i * 3 , 3);
	}
	glutSwapBuffers();
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		frame = false;
		break;
	case 'b':
		frame = true;
		break;
	case '1':
		states1 = true;
		states2 = false;
		states3 = false;
		states4 = false;
		call = false;
		call2 = false;
		break;
	case '2':
		states1 = false;
		states2 = true;
		states3 = false;
		states4 = false;
		call = false;
		call2 = false;
		break;
	case '3':
		states1 = false;
		states2 = false;
		states3 = true;
		states4 = false;
		break;
	case '4':
		states1 = false;
		states2 = false;
		states3 = false;
		states4 = true;
		call = false;
		break;
	case 't':
		states1 = false;
		states2 = false;
		states3 = false;
		states4 = false;
		call = false;
		call = false;
		break;
	case 'q':
		glutLeaveMainLoop();
		break;
	}
	glutPostRedisplay();
	if (states1 || states2 || states3 || states4)
	{
		glutTimerFunc(100, TimerFunction, 1);
	}
}


GLvoid Mouse(int button, int state, int x, int y)
{
	float fx = 0.0, fy = 0.0;
	convertXY(x, y, fx, fy);
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (-1 < fx && fx < 0 && 1 > fy && fy > 0)
		{
			shape[0].shapecoord[0][0] = fx;
			shape[0].shapecoord[0][1] = fy;
			shape[0].shapecoord[1][0] = fx - (0.1 * shape[0].size);
			shape[0].shapecoord[1][1] = fy - (0.3 * shape[0].size);
			shape[0].shapecoord[2][0] = fx + (0.1 * shape[0].size);
			shape[0].shapecoord[2][1] = fy - (0.3 * shape[0].size);
			shape[0].Colors();
			shape[0].size += 0.1;
		}
		else if (1 > fx && 0 < fx && 1 > fy && 0 < fy)
		{
			shape[1].shapecoord[0][0] = fx;
			shape[1].shapecoord[0][1] = fy;
			shape[1].shapecoord[1][0] = fx - (0.1 * shape[1].size);
			shape[1].shapecoord[1][1] = fy - (0.3 * shape[1].size);
			shape[1].shapecoord[2][0] = fx + (0.1 * shape[1].size);
			shape[1].shapecoord[2][1] = fy - (0.3 * shape[1].size);
			shape[1].Colors();
			shape[1].size += 0.1;
		}
		else if (-1 < fx && fx < 0 && -1 < fy && fy < 0)
		{
			shape[2].shapecoord[0][0] = fx;
			shape[2].shapecoord[0][1] = fy;
			shape[2].shapecoord[1][0] = fx - (0.1 * shape[2].size);
			shape[2].shapecoord[1][1] = fy - (0.3 * shape[2].size);
			shape[2].shapecoord[2][0] = fx + (0.1 * shape[2].size);
			shape[2].shapecoord[2][1] = fy - (0.3 * shape[2].size);
			shape[2].Colors();
			shape[2].size += 0.1;
		}
		else if (1 > fx && 0 < fx && -1 < fy && 0 > fy)
		{
			shape[3].shapecoord[0][0] = fx;
			shape[3].shapecoord[0][1] = fy;
			shape[3].shapecoord[1][0] = fx - (0.1 * shape[3].size);
			shape[3].shapecoord[1][1] = fy - (0.3 * shape[3].size);
			shape[3].shapecoord[2][0] = fx + (0.1 * shape[3].size);
			shape[3].shapecoord[2][1] = fy - (0.3 * shape[3].size);
			shape[3].Colors();
			shape[3].size += 0.1;
		}
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		if (-1 < fx && fx < 0 && 1 > fy && fy > 0)
		{
			shape[0].shapecoord[0][0] = fx;
			shape[0].shapecoord[0][1] = fy;
			shape[0].shapecoord[1][0] = fx - 0.1;
			shape[0].shapecoord[1][1] = fy - 0.3;
			shape[0].shapecoord[2][0] = fx + 0.1;
			shape[0].shapecoord[2][1] = fy - 0.3;
			shape[0].size = 1.0;
		}
		else if (1 > fx && 0 < fx && 1 > fy && 0 < fy)
		{
			shape[1].shapecoord[0][0] = fx;
			shape[1].shapecoord[0][1] = fy;
			shape[1].shapecoord[1][0] = fx - 0.1;
			shape[1].shapecoord[1][1] = fy - 0.3;
			shape[1].shapecoord[2][0] = fx + 0.1;
			shape[1].shapecoord[2][1] = fy - 0.3;
			shape[1].size = 1.0;
		}
		else if (-1 < fx && fx < 0 && -1 < fy && fy < 0)
		{
			shape[2].shapecoord[0][0] = fx;
			shape[2].shapecoord[0][1] = fy;
			shape[2].shapecoord[1][0] = fx - 0.1;
			shape[2].shapecoord[1][1] = fy - 0.3;
			shape[2].shapecoord[2][0] = fx + 0.1;
			shape[2].shapecoord[2][1] = fy - 0.3;
			shape[2].size = 1.0;
		}
		else if (1 > fx && 0 < fx && -1 < fy && 0 > fy)
		{
			shape[3].shapecoord[0][0] = fx;
			shape[3].shapecoord[0][1] = fy;
			shape[3].shapecoord[1][0] = fx - 0.1;
			shape[3].shapecoord[1][1] = fy - 0.3;
			shape[3].shapecoord[2][0] = fx + 0.1;
			shape[3].shapecoord[2][1] = fy - 0.3;
			shape[3].size = 1.0;
		}
	}
	glutPostRedisplay();
}

void InitBuffer()
{
	glGenVertexArrays(1, &vao); //--- VAO 를 지정하고 할당하기
	glBindVertexArray(vao); //--- VAO를 바인드하기

	glGenBuffers(2, vbo); //--- 2개의 VBO를 지정하고 할당하기
	//--- 1번째 VBO를 활성화하여 바인드하고, 버텍스 속성 (좌표값)을 저장
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	//--- 변수 diamond 에서 버텍스 데이터 값을 버퍼에 복사한다.
	//--- triShape 배열의 사이즈: 9 * float
	glBufferData(GL_ARRAY_BUFFER, 4 * 9 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	//--- 좌표값을 attribute 인덱스 0번에 명시한다: 버텍스 당 3* float
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//--- attribute 인덱스 0번을 사용가능하게 함
	glEnableVertexAttribArray(0);

	//--- 2번째 VBO를 활성화 하여 바인드 하고, 버텍스 속성 (색상)을 저장
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	//--- 변수 colors에서 버텍스 색상을 복사한다.
	//--- colors 배열의 사이즈: 9 *float
	glBufferData(GL_ARRAY_BUFFER, 4 * 9 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	//--- 색상값을 attribute 인덱스 1번에 명시한다: 버텍스 당 3*float
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//--- attribute 인덱스 1번을 사용 가능하게 함.
	glEnableVertexAttribArray(1);
}

void UpdateBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	for (int i = 0; i < 4; i++)
	{
		glBufferSubData(GL_ARRAY_BUFFER, i * 9 * sizeof(GLfloat), 9 * sizeof(GLfloat), shape[i].shapecoord);
	}

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

	for (int i = 0; i < 4; i++)
	{
		glBufferSubData(GL_ARRAY_BUFFER, i * 9 * sizeof(GLfloat), 9 * sizeof(GLfloat), shape[i].color);
	}
}

GLvoid TimerFunction(int value)
{
	for (int i = 0; i < 4; i++)
	{
		if (states1)
		{
			switch (shape[i].Way)
			{
			case 0:
				moveTriangle(shape[i], 0.1, 0.1);
				break;
			case 1:
				moveTriangle(shape[i], -0.1, 0.1);
				break;
			case 2:
				moveTriangle(shape[i], -0.1, -0.1);
				break;
			case 3:
				moveTriangle(shape[i], 0.1, -0.1);
				break;
			}
			if (fabs(shape[i].shapecoord[0][0]) > 1 || fabs(shape[i].shapecoord[0][1]) > 1)
			{
				shape[i].Way = (shape[i].Way + 1) % 4;
				rotateTriangle(shape[i], 90);
			}
		}
		else if (states2)
		{
			switch (shape[i].Way)
			{
			case 0:
				moveTriangle(shape[i], 0.1, 0.0);
				break;
			case 1:
				moveTriangle(shape[i], -0.1, 0.0);
				break;
			}
			if (fabs(shape[i].shapecoord[0][0]) >= 1 && !shape[i].var)
			{
				shape[i].shapecoord[0][1] += 0.1;
				shape[i].shapecoord[1][1] += 0.1;
				shape[i].shapecoord[2][1] += 0.1;
				shape[i].Way = (shape[i].Way + 1) % 2;
				rotateTriangle(shape[i], 90);
			}
			else if (fabs(shape[i].shapecoord[0][0]) >= 1 && shape[i].var)
			{
				shape[i].shapecoord[0][1] -= 0.1;
				shape[i].shapecoord[1][1] -= 0.1;
				shape[i].shapecoord[2][1] -= 0.1;
				shape[i].Way = (shape[i].Way + 1) % 2;
				rotateTriangle(shape[i], 90);
			}
			if (fabs(shape[i].shapecoord[0][0]) > 1 && shape[i].shapecoord[0][1] > 1 || fabs(shape[i].shapecoord[1][0]) > 1 && shape[i].shapecoord[1][1] > 1 || fabs(shape[i].shapecoord[2][0]) > 1 && shape[i].shapecoord[2][1] > 1)
			{
				shape[i].var = true;
			}
			else if (fabs(shape[i].shapecoord[0][0]) > 1 && shape[i].shapecoord[0][1] < -1 || fabs(shape[i].shapecoord[1][0]) > 1 && shape[i].shapecoord[1][1] < -1 || fabs(shape[i].shapecoord[2][0]) > 1 && shape[i].shapecoord[2][1] < -1)
			{
				shape[i].var = false;
			}
		}
		else if (states3)
		{
			if (!call)
			{
				initializeShapes();
				call = true;
			}
			switch (shape[i].Way)
			{
			case 0: // 왼쪽으로 이동
				shape[i].shapecoord[0][0] -= shape[i].speed;
				if (shape[i].shapecoord[0][0] <= -0.7 + shape[i].spiralOffset)
				{
					shape[i].Way = 1;
					rotateTriangle(shape[i], 90);
				}
				break;
			case 1: // 아래로 이동
				shape[i].shapecoord[0][1] -= shape[i].speed;
				if (shape[i].shapecoord[0][1] <= -0.7 + shape[i].spiralOffset)
				{
					shape[i].Way = 2;
					rotateTriangle(shape[i], 90);
				}
				break;
			case 2: // 오른쪽으로 이동
				shape[i].shapecoord[0][0] += shape[i].speed;
				if (shape[i].shapecoord[0][0] >= 0.7 - shape[i].spiralOffset)
				{
					shape[i].Way = 3;
					rotateTriangle(shape[i], 90);
				}
				break;
			case 3: // 위로 이동
				shape[i].shapecoord[0][1] += shape[i].speed;
				if (shape[i].shapecoord[0][1] >= 0.7 - shape[i].spiralOffset)
				{
					shape[i].Way = 0;
					rotateTriangle(shape[i], 90);
					shape[i].spiralOffset += 0.1; // 한 사이클이 끝나면 스파이럴 오프셋 증가
				}
				break;
			}
			// 삼각형의 나머지 두 점 업데이트
			shape[i].shapecoord[1][0] = shape[i].shapecoord[0][0] - 0.1;
			shape[i].shapecoord[1][1] = shape[i].shapecoord[0][1] - 0.3;
			shape[i].shapecoord[2][0] = shape[i].shapecoord[0][0] + 0.1;
			shape[i].shapecoord[2][1] = shape[i].shapecoord[0][1] - 0.3;

			// 스파이럴이 중심에 도달하면 초기화
			if (shape[i].spiralOffset >= 0.8)
			{
				shape[i].shapecoord[0][0] = 0.9;
				shape[i].shapecoord[0][1] = 0.9;
				shape[i].Way = 0;
				shape[i].spiralOffset = 0.0;
			}
		}
		else if (states4)
		{
			if (!call2)
			{
				initializeShapes2();
				call2 = true;
			}
			shape[i].r += shape[i].speed * 0.1;
			shape[i].theta += shape[i].speed * 10 * PI;
			shape[i].shapecoord[0][0] += shape[i].r * cos(shape[i].theta);
			shape[i].shapecoord[0][1] += shape[i].r * sin(shape[i].theta);
			shape[i].shapecoord[1][0] += shape[i].r * cos(shape[i].theta);
			shape[i].shapecoord[1][1] += shape[i].r * sin(shape[i].theta);
			shape[i].shapecoord[2][0] += shape[i].r * cos(shape[i].theta);
			shape[i].shapecoord[2][1] += shape[i].r * sin(shape[i].theta);
			if (shape[i].r >= 1.0)
			{
				shape[i].r = 0.1;
				call2 = false;
			}
			rotateTriangle(shape[i], 90);
		}
	}
	glutPostRedisplay();
	if (states1 || states2 || states3 || states4)
	{
		glutTimerFunc(60, TimerFunction, 1);
	}
}