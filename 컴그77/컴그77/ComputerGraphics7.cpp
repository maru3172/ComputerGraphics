#include "GLbasic.h"
#include "GLMain.h"

struct Shape
{
	GLfloat shapecoord[4][3] = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, { 0, 0, 0} };
	int state = 0;
	bool states = false;
};

Shape shape[10];
int count = 0;

GLvoid drawScene()
{
	glClearColor(bGCr, bGCg, bGCb, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shaderProgramID);
	UpdateBuffer();
	glBindVertexArray(vao);
	for (int i = 0; i < 10; i++)
	{
		if (shape[i].states)
		{
			if (shape[i].state == 1)
			{
				glPointSize(5.0);
				glDrawElements(GL_POINTS, 1, GL_UNSIGNED_INT, (void*)(i * 4 * sizeof(GLuint)));
			}
			else if (shape[i].state == 2)
			{
				glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (void*)(i * 4 * sizeof(GLuint)));
			}
			else if (shape[i].state == 3)
			{
				glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(i * 4 * sizeof(GLuint)));
			}
			else if (shape[i].state == 4)
			{
				glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, (void*)(i * 4 * sizeof(GLuint)));
			}
		}
	}
	glutSwapBuffers();
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	int a = random();
	switch (key)
	{
	case 'p':
		shape[count].state = 1;
		break;
	case 'l':
		shape[count].state = 2;
		break;
	case 't':
		shape[count].state = 3;
		break;
	case 'r':
		shape[count].state = 4;
		break;
	case 'w':
		switch (shape[a].state)
		{
		case 1:
			shape[a].shapecoord[0][1] += 0.05;
			break;
		case 2:
			shape[a].shapecoord[0][1] += 0.05;
			shape[a].shapecoord[1][1] += 0.05;
			break;
		case 3:
			shape[a].shapecoord[0][1] += 0.05;
			shape[a].shapecoord[1][1] += 0.05;
			shape[a].shapecoord[2][1] += 0.05;
			break;
		case 4:
			shape[a].shapecoord[0][1] += 0.05;
			shape[a].shapecoord[1][1] += 0.05;
			shape[a].shapecoord[2][1] += 0.05;
			shape[a].shapecoord[3][1] += 0.05;
			break;
		}
		break;
	case 'a':
		switch (shape[a].state)
		{
		case 1:
			shape[a].shapecoord[0][0] -= 0.05;
			break;
		case 2:
			shape[a].shapecoord[0][0] -= 0.05;
			shape[a].shapecoord[1][0] -= 0.05;
			break;
		case 3:
			shape[a].shapecoord[0][0] -= 0.05;
			shape[a].shapecoord[1][0] -= 0.05;
			shape[a].shapecoord[2][0] -= 0.05;
			break;
		case 4:
			shape[a].shapecoord[0][0] -= 0.05;
			shape[a].shapecoord[1][0] -= 0.05;
			shape[a].shapecoord[2][0] -= 0.05;
			shape[a].shapecoord[3][0] -= 0.05;
			break;
		}
		break;
	case 's':
		switch (shape[a].state)
		{
		case 1:
			shape[a].shapecoord[0][1] -= 0.05;
			break;
		case 2:
			shape[a].shapecoord[0][1] -= 0.05;
			shape[a].shapecoord[1][1] -= 0.05;
			break;
		case 3:
			shape[a].shapecoord[0][1] -= 0.05;
			shape[a].shapecoord[1][1] -= 0.05;
			shape[a].shapecoord[2][1] -= 0.05;
			break;
		case 4:
			shape[a].shapecoord[0][1] -= 0.05;
			shape[a].shapecoord[1][1] -= 0.05;
			shape[a].shapecoord[2][1] -= 0.05;
			shape[a].shapecoord[3][1] -= 0.05;
			break;
		}
		break;
	case 'd':
		switch (shape[a].state)
		{
		case 1:
			shape[a].shapecoord[0][0] += 0.05;
			break;
		case 2:
			shape[a].shapecoord[0][0] += 0.05;
			shape[a].shapecoord[1][0] += 0.05;
			break;
		case 3:
			shape[a].shapecoord[0][0] += 0.05;
			shape[a].shapecoord[1][0] += 0.05;
			shape[a].shapecoord[2][0] += 0.05;
			break;
		case 4:
			shape[a].shapecoord[0][0] += 0.05;
			shape[a].shapecoord[1][0] += 0.05;
			shape[a].shapecoord[2][0] += 0.05;
			shape[a].shapecoord[3][0] += 0.05;
			break;
		}
		break;
	case 'c':
		count = 0;
		for (int i = 0; i < 10; i++)
		{
			shape[i].state = 0;
			shape[i].states = false;
		}
		break;
	case 'q':
		glutLeaveMainLoop();
		break;
	}
	glutPostRedisplay();
}

GLvoid Mouse(int button, int state, int x, int y)
{
	float fx = 0.0, fy = 0.0;
	convertXY(x, y, fx, fy);
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (count < 10)
		{
			switch (shape[count].state)
			{
			case 1:
				shape[count].shapecoord[0][0] = fx;
				shape[count].shapecoord[0][1] = fy;
				break;
			case 2:
				shape[count].shapecoord[0][0] = fx - 0.25;
				shape[count].shapecoord[0][1] = fy - 0.25;
				shape[count].shapecoord[1][0] = fx + 0.25;
				shape[count].shapecoord[1][1] = fy + 0.25;
				break;
			case 3:
				shape[count].shapecoord[0][0] = fx;
				shape[count].shapecoord[0][1] = fy;
				shape[count].shapecoord[1][0] = fx - 0.1;
				shape[count].shapecoord[1][1] = fy - 0.3;
				shape[count].shapecoord[2][0] = fx + 0.1;
				shape[count].shapecoord[2][1] = fy - 0.3;
				break;
			case 4:
				shape[count].shapecoord[0][0] = fx - 0.25;
				shape[count].shapecoord[0][1] = fy - 0.25;
				shape[count].shapecoord[1][0] = fx + 0.25;
				shape[count].shapecoord[1][1] = fy - 0.25;
				shape[count].shapecoord[2][0] = fx - 0.25;
				shape[count].shapecoord[2][1] = fy + 0.25;
				shape[count].shapecoord[3][0] = fx + 0.25;
				shape[count].shapecoord[3][1] = fy + 0.25;
				break;
			}
			shape[count].states = true;
			count++;
			shape[count].state = shape[count - 1].state;
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
	glBufferData(GL_ARRAY_BUFFER, SHAPES * 12 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	//--- 좌표값을 attribute 인덱스 0번에 명시한다: 버텍스 당 3* float
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//--- attribute 인덱스 0번을 사용가능하게 함
	glEnableVertexAttribArray(0);

	//--- 2번째 VBO를 활성화 하여 바인드 하고, 버텍스 속성 (색상)을 저장
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	//--- 변수 colors에서 버텍스 색상을 복사한다.
	//--- colors 배열의 사이즈: 9 *float
	glBufferData(GL_ARRAY_BUFFER, SHAPES * 12 * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
	for (int i = 0; i < SHAPES; i++)
	{
		for (int z = 0; z < 3; z++)
		{
			for (int j = 0; j < 3; j++)
			{
				Color(colors[z][j]);
			}
		}
		glBufferSubData(GL_ARRAY_BUFFER, i * 12 * sizeof(GLfloat), 12 * sizeof(GLfloat), colors);
	}
	//--- 색상값을 attribute 인덱스 1번에 명시한다: 버텍스 당 3*float
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//--- attribute 인덱스 1번을 사용 가능하게 함.
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	GLuint indices[SHAPES * 4];
	for (int i = 0; i < SHAPES; i++)
	{
		indices[i * 4] = i * 4;
		indices[i * 4 + 1] = i * 4 + 1;
		indices[i * 4 + 2] = i * 4 + 2;
		indices[i * 4 + 3] = i * 4 + 3;
	}
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void UpdateBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	for (int i = 0; i < SHAPES; i++)
	{
		glBufferSubData(GL_ARRAY_BUFFER, i * 12 * sizeof(GLfloat), 12 * sizeof(GLfloat), shape[i].shapecoord);
	}
}