#include "GLmain.h"
bool starter = false, mouse = false, mode = false, path = false;
bool starts = false;

Box box;

GLvoid drawScene()
{
	glClearColor(bGCr, bGCg, bGCb, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shaderProgramID);
	UpdateBuffer();

	glBindVertexArray(vao);
	if (mode)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	for (int i = 0; i < SHAPECOUNT; i++)
	{
		if (shape[i].view)
		{
			if (shape[i].shapetype == 0)
			{
				glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(i * 5 * sizeof(GLuint)));
			}
			else if (shape[i].shapetype == 1)
			{
				glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, (void*)(i * 5 * sizeof(GLuint)));
			}
			else if (shape[i].shapetype == 2)
			{
				glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, (void*)(i * 5 * sizeof(GLuint)));
			}
		}
	}
	if (mouse)
	{
		glBindVertexArray(Linearvao);
		glDrawArrays(GL_LINES, 0, 2);
	}
	glBindVertexArray(BoxVao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	
	if (path)
	{
		glBindVertexArray(LinearPathVao);
		for (int i = 0; i < 3; i++)
		{
			if (shape[i].path && Path[i].show)
			{
				glDrawArrays(GL_LINES, i * 2, 2);
			}
		}
	}
	
	glutSwapBuffers();
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'm':
		if (!mode)
			mode = true;
		else
			mode = false;
		break;
	case 'p':
		if (!path)
			path = true;
		else
			path = false;
		break;
	case '+':
		for (int i = 0; i < SHAPECOUNT; i++)
		{
			shape[i].speedUp();
		}
		break;
	case '-':
		for (int i = 0; i < SHAPECOUNT; i++)
		{
			shape[i].speedDown();
		}
		break;
	case 'q':
		glutLeaveMainLoop();
		break;
	}
}

GLvoid Mouse(int button, int state, int x, int y)
{
	convertXY(x, y, fx, fy);
	for (int i = 0; i < 15; i++)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			linear.L[0][0] = fx;
			linear.L[0][1] = fy;
			linear.L[1][0] = fx;
			linear.L[1][1] = fy;
			mouse = true;
		}
		if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		{
			mouse = false;
			for (int i = 0; i < SHAPECOUNT; i++)
			{
				if (shape[i].view)
				{
					switch (shape[i].shapetype)
					{
					case 0:
						if (Crash(shape[i].shapecoord[1][0], shape[i].shapecoord[2][0], linear.L[0][0], linear.L[1][0], shape[i].shapecoord[0][1], shape[i].shapecoord[1][1], linear.L[0][1], linear.L[1][1]))
						{
							shape[i].view = false;
							shape[count].shapecoord[0][0] = shape[i].shapecoord[0][0] - 0.01;
							shape[count].shapecoord[1][0] = shape[i].shapecoord[1][0] - 0.01;
							shape[count].shapecoord[2][0] = shape[i].shapecoord[1][0] - 0.25 + 0.01;
							shape[count].shapecoord[0][1] = shape[i].shapecoord[0][1];
							shape[count].shapecoord[1][1] = shape[i].shapecoord[1][1];
							shape[count].shapecoord[2][1] = shape[i].shapecoord[2][1];
							shape[count].shapetype = 0;
							shape[count].view = true;
							shape[count].Slice = true;
							count++;

							shape[count].shapecoord[0][0] = shape[i].shapecoord[0][0] + 0.01;
							shape[count].shapecoord[1][0] = shape[i].shapecoord[1][0] + 0.25 + 0.01;
							shape[count].shapecoord[2][0] = shape[i].shapecoord[2][0] + 0.01;
							shape[count].shapecoord[0][1] = shape[i].shapecoord[0][1];
							shape[count].shapecoord[1][1] = shape[i].shapecoord[1][1];
							shape[count].shapecoord[2][1] = shape[i].shapecoord[2][1];
							shape[count].shapetype = 0;
							shape[count].view = true;
							shape[count].Slice = true;
							count++;
							shape[i].path = false;
						}
						break;
					case 1:
						if (Crash(shape[i].shapecoord[2][0], shape[i].shapecoord[1][0], linear.L[0][0], linear.L[1][0], shape[i].shapecoord[2][1], shape[i].shapecoord[1][1], linear.L[0][1], linear.L[1][1]))
						{
							shape[i].view = false;
							shape[count].shapecoord[0][0] = shape[i].shapecoord[0][0] - 0.01;
							shape[count].shapecoord[1][0] = shape[i].shapecoord[1][0] - 0.01;
							shape[count].shapecoord[2][0] = shape[i].shapecoord[2][0] - 0.01;
							shape[count].shapecoord[0][1] = shape[i].shapecoord[0][1];
							shape[count].shapecoord[1][1] = shape[i].shapecoord[1][1];
							shape[count].shapecoord[2][1] = shape[i].shapecoord[2][1];
							shape[count].shapetype = 0;
							shape[count].view = true;
							shape[count].Slice = true;
							count++;

							shape[count].shapecoord[0][0] = shape[i].shapecoord[2][0] + 0.01;
							shape[count].shapecoord[1][0] = shape[i].shapecoord[1][0] + 0.01;
							shape[count].shapecoord[2][0] = shape[i].shapecoord[3][0] + 0.01;
							shape[count].shapecoord[0][1] = shape[i].shapecoord[2][1];
							shape[count].shapecoord[1][1] = shape[i].shapecoord[1][1];
							shape[count].shapecoord[2][1] = shape[i].shapecoord[3][1];
							shape[count].shapetype = 0;
							shape[count].view = true;
							shape[count].Slice = true;
							count++;
							shape[i].path = false;
						}
						break;
					case 2:
						if (Crash(shape[i].shapecoord[1][0], shape[i].shapecoord[4][0], linear.L[0][0], linear.L[1][0], shape[i].shapecoord[0][1], shape[i].shapecoord[3][1], linear.L[0][1], linear.L[1][1]))
						{
							shape[i].view = false;
							shape[count].shapecoord[0][0] = shape[i].shapecoord[0][0] - 0.01;
							shape[count].shapecoord[1][0] = shape[i].shapecoord[2][0] - 0.01;
							shape[count].shapecoord[2][0] = shape[i].shapecoord[1][0] - 0.01;
							shape[count].shapecoord[0][1] = shape[i].shapecoord[0][1];
							shape[count].shapecoord[1][1] = shape[i].shapecoord[2][1];
							shape[count].shapecoord[2][1] = shape[i].shapecoord[1][1];
							shape[count].shapetype = 0;
							shape[count].view = true;
							shape[count].Slice = true;
							count++;

							shape[count].shapecoord[0][0] = shape[i].shapecoord[0][0];
							shape[count].shapecoord[1][0] = shape[i].shapecoord[3][0];
							shape[count].shapecoord[2][0] = shape[i].shapecoord[2][0];
							shape[count].shapecoord[0][1] = shape[i].shapecoord[0][1];
							shape[count].shapecoord[1][1] = shape[i].shapecoord[3][1];
							shape[count].shapecoord[2][1] = shape[i].shapecoord[2][1];
							shape[count].shapetype = 0;
							shape[count].view = true;
							shape[count].Slice = true;
							count++;

							shape[count].shapecoord[0][0] = shape[i].shapecoord[0][0] + 0.01;
							shape[count].shapecoord[1][0] = shape[i].shapecoord[4][0] + 0.01;
							shape[count].shapecoord[2][0] = shape[i].shapecoord[3][0] + 0.01;
							shape[count].shapecoord[0][1] = shape[i].shapecoord[0][1];
							shape[count].shapecoord[1][1] = shape[i].shapecoord[4][1];
							shape[count].shapecoord[2][1] = shape[i].shapecoord[3][1];
							shape[count].shapetype = 0;
							shape[count].view = true;
							shape[count].Slice = true;
							count++;
							shape[i].path = false;
						}
						break;
					}
				}
			}
		}
	}
	glutPostRedisplay();
}

GLvoid Motion(int x, int y)
{
	convertXY(x, y, fx2, fy2);
	if (mouse)
	{
		linear.L[1][0] = fx2;
		linear.L[1][1] = fy2;
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
	glBufferData(GL_ARRAY_BUFFER, SHAPECOUNT * 5 * 3 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	//--- 좌표값을 attribute 인덱스 0번에 명시한다: 버텍스 당 3* float
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//--- attribute 인덱스 0번을 사용가능하게 함
	glEnableVertexAttribArray(0);

	//--- 2번째 VBO를 활성화 하여 바인드 하고, 버텍스 속성 (색상)을 저장
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	//--- 변수 colors에서 버텍스 색상을 복사한다.
	//--- colors 배열의 사이즈: 9 *float
	glBufferData(GL_ARRAY_BUFFER, SHAPECOUNT * 5 * 3 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	//--- 색상값을 attribute 인덱스 1번에 명시한다: 버텍스 당 3*float
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//--- attribute 인덱스 1번을 사용 가능하게 함.
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	GLuint indices[SHAPECOUNT * 5];
	for (int i = 0; i < SHAPECOUNT * 5; i++)
	{
		indices[i] = i;
	}
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * SHAPECOUNT * 5, indices, GL_DYNAMIC_DRAW);
	LinearBuffer();
	BoxBuffer();
	PathBuffer();
}

void UpdateBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, Linearvbo[0]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 6 * sizeof(GLfloat), linear.L);
	glBindBuffer(GL_ARRAY_BUFFER, Linearvbo[1]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 6 * sizeof(GLfloat), linear.rgb);

	glBindBuffer(GL_ARRAY_BUFFER, LinearPathVbo[0]);
	for (int i = 0; i < 3; i++)
	{
		glBufferSubData(GL_ARRAY_BUFFER, i * 6 * sizeof(GLfloat), 6 * sizeof(GLfloat), Path[i].L);
	}

	glBindBuffer(GL_ARRAY_BUFFER, LinearPathVbo[1]);
	for (int i = 0; i < 3; i++)
	{
		glBufferSubData(GL_ARRAY_BUFFER, i * 6 * sizeof(GLfloat), 6 * sizeof(GLfloat), Path[i].rgb);
	}

	glBindBuffer(GL_ARRAY_BUFFER, BoxVbo[0]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * 3 * sizeof(GLfloat), box.BoxCoord);
	glBindBuffer(GL_ARRAY_BUFFER, BoxVbo[1]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * 3 * sizeof(GLfloat), box.BoxColor);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	for (int i = 0; i < SHAPECOUNT; i++)
	{
		glBufferSubData(GL_ARRAY_BUFFER, i * (5 * 3 * sizeof(GLfloat)), 5 * 3 * sizeof(GLfloat), shape[i].shapecoord);
	}

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	for (int i = 0; i < SHAPECOUNT; i++)
	{
		glBufferSubData(GL_ARRAY_BUFFER, i * (5 * 3 * sizeof(GLfloat)), 5 * 3 * sizeof(GLfloat), shape[i].colors);
	}
}

GLvoid TimerFunction(int value)
{
	for (int i = 0; i < SHAPECOUNT; i++)
	{
		if (!shape[i].Slice && shape[i].normal)
		{
			if (shape[i].state)
			{
				switch (shape[i].shapetype)
				{
				case 0:
					for (int j = 0; j < 3; j++)
					{
						shape[i].shapecoord[j][0] += shape[i].speed;
						shape[i].shapecoord[j][1] -= shape[i].speed;
					}
					break;
				case 1:
					for (int j = 0; j < 4; j++)
					{
						shape[i].shapecoord[j][0] += shape[i].speed;
						shape[i].shapecoord[j][1] -= shape[i].speed;
					}
					break;
				case 2:
					for (int j = 0; j < 5; j++)
					{
						shape[i].shapecoord[j][0] += shape[i].speed;
						shape[i].shapecoord[j][1] -= shape[i].speed;
					}
					break;
				}
			}
			else
			{
				switch (shape[i].shapetype)
				{
				case 0:
					for (int j = 0; j < 3; j++)
					{
						shape[i].shapecoord[j][0] -= shape[i].speed;
						shape[i].shapecoord[j][1] -= shape[i].speed;
					}
					break;
				case 1:
					for (int j = 0; j < 4; j++)
					{
						shape[i].shapecoord[j][0] -= shape[i].speed;
						shape[i].shapecoord[j][1] -= shape[i].speed;
					}
					break;
				case 2:
					for (int j = 0; j < 5; j++)
					{
						shape[i].shapecoord[j][0] -= shape[i].speed;
						shape[i].shapecoord[j][1] -= shape[i].speed;
					}
					break;
				}
			}
		}
		if (shape[i].view && shape[i].Slice)
		{
			if (!shape[i].normal)
			{
				for (int j = 0; j < 3; j++)
				{
					shape[i].shapecoord[j][1] -= 0.01;
				}
			}
		}

		if (shape[i].normal && shape[i].view)
		{
			if (shape[i].state)
			{
				Path[i].L[0][0] = 1.0f;
				Path[i].L[0][1] = -1.0f;
			}
			else
			{
				Path[i].L[0][0] = -1.0f;
				Path[i].L[0][1] = -1.0f;
			}

			switch (shape[i].shapetype)
			{
			case 0:
				Path[i].L[1][0] = shape[i].shapecoord[2][0];
				Path[i].L[1][1] = shape[i].shapecoord[2][1];
				break;
			case 1:
				Path[i].L[1][0] = shape[i].shapecoord[1][0];
				Path[i].L[1][1] = shape[i].shapecoord[1][1];
				break;
			case 2:
				Path[i].L[1][0] = shape[i].shapecoord[3][0];
				Path[i].L[1][1] = shape[i].shapecoord[3][1];
				break;
			}
		}

		if (shape[i].shapecoord[0][1] < -1 && !shape[i].Slice)
		{
			if (shape[i].normal)
			{
				shape[i].view = true;
				shape[i].path = true;
			}
			shape[i].RandomSet();
		}
		else if ((shape[i].shapecoord[0][1] < -1 && shape[i].Slice) ||
			(shape[i].Slice &&
				(shape[i].shapecoord[1][1] < box.BoxCoord[0][1] &&
				shape[i].shapecoord[2][1] < box.BoxCoord[0][1]) &&
				shape[i].shapecoord[0][0] > box.BoxCoord[0][0] &&
				shape[i].shapecoord[0][0] < box.BoxCoord[3][0]))
		{
			shape[i].shapecoord[0][0] = 0.0f;
			shape[i].shapecoord[1][0] = 0.0f;
			shape[i].shapecoord[2][0] = 0.0f;
			shape[i].shapecoord[0][1] = 0.0f;
			shape[i].shapecoord[1][1] = 0.0f;
			shape[i].shapecoord[2][1] = 0.0f;
			shape[i].view = false;
			shape[i].Slice = false;
			count--;
		}
	}

	if (!box.state)
	{
		for (int i = 0; i < 4; i++)
		{
			box.BoxCoord[i][0] -= 0.01;
		}
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			box.BoxCoord[i][0] += 0.01;
		}
	}

	if (box.BoxCoord[0][0] < -1)
	{
		box.state = true;
	}
	else if (box.BoxCoord[3][0] > 1)
	{
		box.state = false;
	}
	glutPostRedisplay();
	glutTimerFunc(10, TimerFunction, 1);
}