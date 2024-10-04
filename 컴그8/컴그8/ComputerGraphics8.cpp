#include "GLmain.h"

class Shape
{
public:
	GLfloat shapecoord[3][3];
	bool states;
	float size;
	GLfloat color[3][3];
	Shape() : states{ false }, size { 1.0 }
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				shapecoord[i][j] = 0;
			}
		}
		for (int i = 0; i < 3; i++)
		{
			Color(color[0][i]);
		}
		for (int i = 1; i < 3; i++)
		{
			color[i][0] = color[0][0];
			color[i][1] = color[0][1];
			color[i][2] = color[0][2];
		}
	};

	void Colors()
	{
		for (int i = 0; i < 3; i++)
		{
			Color(color[0][i]);
		}
		for (int i = 1; i < 3; i++)
		{
			color[i][0] = color[0][0];
			color[i][1] = color[0][1];
			color[i][2] = color[0][2];
		}
	}
};

bool frame = false;

float size1 = 1.0, size2 = 1.0, size3 = 1.0, size4 = 1.0;

int count1 = 0, count2 = 0, count3 = 0, count4 = 0;

Shape shape[4][3];

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
		for (int j = 0; j < 3; j++)
		{
			if (shape[i][j].states)
			{
				glDrawArrays(GL_TRIANGLES, i * 9 + j * 3, 3);
			}
		}
	}
	glutSwapBuffers();
}

GLvoid Keyboard(unsigned char key, int x, int y)
{	switch (key)
	{
	case 'a':
		frame = false;
		break;
	case 'b':
		frame = true;
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
		if (-1 < fx && fx < 0 && 1 > fy && fy > 0)
		{
			shape[0][count1].shapecoord[0][0] = fx;
			shape[0][count1].shapecoord[0][1] = fy;
			shape[0][count1].shapecoord[1][0] = fx - (0.1 * shape[0][count1].size);
			shape[0][count1].shapecoord[1][1] = fy - (0.3 * shape[0][count1].size);
			shape[0][count1].shapecoord[2][0] = fx + (0.1 * shape[0][count1].size);
			shape[0][count1].shapecoord[2][1] = fy - (0.3 * shape[0][count1].size);
			shape[0][count1].Colors();
			shape[0][count1].size += 0.1;
			shape[0][count1].states = true;
		}
		else if (1 > fx && 0 < fx && 1 > fy && 0 < fy)
		{
			shape[1][count2].shapecoord[0][0] = fx;
			shape[1][count2].shapecoord[0][1] = fy;
			shape[1][count2].shapecoord[1][0] = fx - (0.1 * shape[1][count2].size);
			shape[1][count2].shapecoord[1][1] = fy - (0.3 * shape[1][count2].size);
			shape[1][count2].shapecoord[2][0] = fx + (0.1 * shape[1][count2].size);
			shape[1][count2].shapecoord[2][1] = fy - (0.3 * shape[1][count2].size);
			shape[1][count2].Colors();
			shape[1][count2].size += 0.1;
			shape[1][count2].states = true;
		}
		else if (-1 < fx && fx < 0 && -1 < fy && fy < 0)
		{
			shape[2][count3].shapecoord[0][0] = fx;
			shape[2][count3].shapecoord[0][1] = fy;
			shape[2][count3].shapecoord[1][0] = fx - (0.1 * shape[2][count3].size);
			shape[2][count3].shapecoord[1][1] = fy - (0.3 * shape[2][count3].size);
			shape[2][count3].shapecoord[2][0] = fx + (0.1 * shape[2][count3].size);
			shape[2][count3].shapecoord[2][1] = fy - (0.3 * shape[2][count3].size);
			shape[2][count3].Colors();
			shape[2][count3].size += 0.1;
			shape[2][count3].states = true;
		}
		else if (1 > fx && 0 < fx && -1 < fy && 0 > fy)
		{
			shape[3][count4].shapecoord[0][0] = fx;
			shape[3][count4].shapecoord[0][1] = fy;
			shape[3][count4].shapecoord[1][0] = fx - (0.1 * shape[3][count4].size);
			shape[3][count4].shapecoord[1][1] = fy - (0.3 * shape[3][count4].size);
			shape[3][count4].shapecoord[2][0] = fx + (0.1 * shape[3][count4].size);
			shape[3][count4].shapecoord[2][1] = fy - (0.3 * shape[3][count4].size);
			shape[3][count4].Colors();
			shape[3][count4].size += 0.1;
			shape[3][count4].states = true;
		}
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		if (-1 < fx && fx < 0 && 1 > fy && fy > 0)
		{
			if (count1 < 3)
			{
				shape[0][count1].shapecoord[0][0] = fx;
				shape[0][count1].shapecoord[0][1] = fy;
				shape[0][count1].shapecoord[1][0] = fx - 0.1;
				shape[0][count1].shapecoord[1][1] = fy - 0.3;
				shape[0][count1].shapecoord[2][0] = fx + 0.1;
				shape[0][count1].shapecoord[2][1] = fy - 0.3;
				shape[0][count1].size= 1.0;
				shape[0][count1].states = true;
				count1++;
			}
			if (count1 == 3)
			{
				count1 = 0;
			}
		}
		else if (1 > fx && 0 < fx && 1 > fy && 0 < fy)
		{
			if (count2 < 3)
			{
				shape[1][count2].shapecoord[0][0] = fx;
				shape[1][count2].shapecoord[0][1] = fy;
				shape[1][count2].shapecoord[1][0] = fx - 0.1;
				shape[1][count2].shapecoord[1][1] = fy - 0.3;
				shape[1][count2].shapecoord[2][0] = fx + 0.1;
				shape[1][count2].shapecoord[2][1] = fy - 0.3;
				shape[1][count2].size = 1.0;
				shape[1][count2].states = true;
				count2++;
			}
			if (count2 == 3)
			{
				count2 = 0;
			}
		}
		else if (-1 < fx && fx < 0 && -1 < fy && fy < 0)
		{
			if (count3 < 3)
			{
				shape[2][count3].shapecoord[0][0] = fx;
				shape[2][count3].shapecoord[0][1] = fy;
				shape[2][count3].shapecoord[1][0] = fx - 0.1;
				shape[2][count3].shapecoord[1][1] = fy - 0.3;
				shape[2][count3].shapecoord[2][0] = fx + 0.1;
				shape[2][count3].shapecoord[2][1] = fy - 0.3;
				shape[2][count3].size = 1.0;
				shape[2][count3].states = true;
				count3++;
			}
			if (count3 == 3)
			{
				count3 = 0;
			}
		}
		else if (1 > fx && 0 < fx && -1 < fy && 0 > fy)
		{
			if (count4 < 3)
			{
				shape[3][count4].shapecoord[0][0] = fx;
				shape[3][count4].shapecoord[0][1] = fy;
				shape[3][count4].shapecoord[1][0] = fx - 0.1;
				shape[3][count4].shapecoord[1][1] = fy - 0.3;
				shape[3][count4].shapecoord[2][0] = fx + 0.1;
				shape[3][count4].shapecoord[2][1] = fy - 0.3;
				shape[3][count4].size = 1.0;
				shape[3][count4].states = true;
				count4++;
			}
			if (count4 == 3)
			{
				count4 = 0;
			}
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
	glBufferData(GL_ARRAY_BUFFER, 4 * 3 * 9 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	//--- 좌표값을 attribute 인덱스 0번에 명시한다: 버텍스 당 3* float
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//--- attribute 인덱스 0번을 사용가능하게 함
	glEnableVertexAttribArray(0);

	//--- 2번째 VBO를 활성화 하여 바인드 하고, 버텍스 속성 (색상)을 저장
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	//--- 변수 colors에서 버텍스 색상을 복사한다.
	//--- colors 배열의 사이즈: 9 *float
	glBufferData(GL_ARRAY_BUFFER, 4 * 3 * 9 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	//--- 색상값을 attribute 인덱스 1번에 명시한다: 버텍스 당 3*float
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//--- attribute 인덱스 1번을 사용 가능하게 함.
	glEnableVertexAttribArray(1);;
}

void UpdateBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			glBufferSubData(GL_ARRAY_BUFFER, (i * 3 + j) * 9 * sizeof(GLfloat), 9 * sizeof(GLfloat), shape[i][j].shapecoord);
		}
	}

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			glBufferSubData(GL_ARRAY_BUFFER, (i * 3 + j) * 9 * sizeof(GLfloat), 9 * sizeof(GLfloat), shape[i][j].color);
		}
	}
}