#include "GLmain.h"

std::uniform_int_distribution<int> randoms(1, 2);
bool starter = false;

GLvoid drawScene()
{
	glClearColor(bGCr, bGCg, bGCb, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shaderProgramID);
	UpdateBuffer();
	glBindVertexArray(vao);
	for (int i = 0; i < 15; i++)
	{
		if (shape[i].ShapeState)
		{
			if (shape[i].shapetype == 1 && shape[i].ShapeState)
			{
				glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, (void*)(i * 5 * sizeof(GLuint)));
			}
			if (shape[i].shapetype == 2 && shape[i].ShapeState)
			{
				glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (void*)(i * 5 * sizeof(GLuint)));
			}
			else if (shape[i].shapetype == 3 && shape[i].ShapeState)
			{
				glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(i * 5 * sizeof(GLuint)));
			}
			else if (shape[i].shapetype == 4 && shape[i].ShapeState)
			{
				glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, (void*)(i * 5 * sizeof(GLuint)));
			}
			else if (shape[i].shapetype == 5 && shape[i].ShapeState)
			{
				glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, (void*)(i * 5 * sizeof(GLuint)));
			}
		}
	}
	glutSwapBuffers();
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
		glutLeaveMainLoop();
		break;
	}
}

int count = 0;

GLvoid Mouse(int button, int state, int x, int y)
{
	convertXY(x, y, fx, fy);
	for (int i = 0; i < 15; i++)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			convertXY(x, y, bfx, bfy);
			switch (shape[i].shapetype)
			{
			case 1:
				if (shape[i].shapecoord[0][0] < fx && shape[i].shapecoord[3][0] > fx && shape[i].shapecoord[0][1] > fy && shape[i].shapecoord[3][1] < fy)
				{
					shape[i].MouseState = true;
					count = i;
				}
				break;
			case 2:
				if (shape[i].shapecoord[0][0] < fx && shape[i].shapecoord[1][0] > fx && shape[i].shapecoord[0][1] < fy && shape[i].shapecoord[1][1] > fy)
				{
					shape[i].MouseState = true;
					count = i;
				}
				break;
			case 3:
				if (shape[i].shapecoord[1][0] < fx && shape[i].shapecoord[2][0] > fx && shape[i].shapecoord[0][1] > fy && shape[i].shapecoord[1][1] < fy)
				{
					shape[i].MouseState = true;
					count = i;
				}
				break;
			case 4:
				if (shape[i].shapecoord[0][0] < fx && shape[i].shapecoord[3][0] > fx && shape[i].shapecoord[0][1] > fy && shape[i].shapecoord[3][1] < fy)
				{
					shape[i].MouseState = true;
					count = i;
				}
				break;
			case 5:
				if (shape[i].shapecoord[2][0] < fx && shape[i].shapecoord[3][0] > fx && shape[i].shapecoord[0][1] > fy && shape[i].shapecoord[3][1] < fy)
				{
					shape[i].MouseState = true;
					count = i;
				}
				break;
			}
		}
		if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		{
			for (int j = 0; j < 15; j++)
			{
				switch (shape[count].shapetype)
				{
				case 1:
					switch (shape[j].shapetype)
					{
					case 1:
						if (Crash(shape[count].shapecoord[0][0], shape[count].shapecoord[3][0], shape[j].shapecoord[0][0], shape[j].shapecoord[3][0], shape[count].shapecoord[3][1], shape[count].shapecoord[0][1], shape[j].shapecoord[3][1], shape[j].shapecoord[0][1]) && shape[j].ShapeState && j != count)
						{
							shape[count].shapetype += shape[j].shapetype;
							shape[j].ShapeState = false;
							shape[count].shapecoord[0][0] = fx - 0.15;
							shape[count].shapecoord[0][1] = fy - 0.15;
							shape[count].shapecoord[1][0] = fx + 0.15;
							shape[count].shapecoord[1][1] = fy + 0.15;
							shape[count].run = randoms(gen);
						}
						break;
					case 2:
						if (Crash(shape[count].shapecoord[0][0], shape[count].shapecoord[3][0], shape[j].shapecoord[0][0], shape[j].shapecoord[1][0], shape[count].shapecoord[3][1], shape[count].shapecoord[0][1], shape[j].shapecoord[0][1], shape[j].shapecoord[1][1]) && shape[j].ShapeState && j != count)
						{
							shape[count].shapetype += shape[j].shapetype;
							shape[j].ShapeState = false;
							shape[count].shapecoord[0][0] = fx;
							shape[count].shapecoord[0][1] = fy + 0.15;
							shape[count].shapecoord[1][0] = fx - 0.15;
							shape[count].shapecoord[1][1] = fy - 0.15;
							shape[count].shapecoord[2][0] = fx + 0.15;
							shape[count].shapecoord[2][1] = fy - 0.15;
							shape[count].run = randoms(gen);
						}
						break;
					case 3:
						if (Crash(shape[count].shapecoord[0][0], shape[count].shapecoord[3][0], shape[j].shapecoord[1][0], shape[j].shapecoord[2][0], shape[count].shapecoord[3][1], shape[count].shapecoord[0][1], shape[j].shapecoord[1][1], shape[j].shapecoord[0][1]) && shape[j].ShapeState && j != count)
						{
							shape[count].shapetype += shape[j].shapetype;
							shape[j].ShapeState = false;
							shape[count].shapecoord[0][0] = fx - 0.15;
							shape[count].shapecoord[0][1] = fy + 0.15;
							shape[count].shapecoord[1][0] = fx + 0.15;
							shape[count].shapecoord[1][1] = fy + 0.15;
							shape[count].shapecoord[2][0] = fx - 0.15;
							shape[count].shapecoord[2][1] = fy - 0.15;
							shape[count].shapecoord[3][0] = fx + 0.15;
							shape[count].shapecoord[3][1] = fy - 0.15;
							shape[count].run = randoms(gen);
						}
						break;
					case 4:
						if (Crash(shape[count].shapecoord[0][0], shape[count].shapecoord[3][0], shape[j].shapecoord[0][0], shape[j].shapecoord[3][0], shape[count].shapecoord[3][1], shape[count].shapecoord[0][1], shape[j].shapecoord[3][1], shape[j].shapecoord[0][1]) && shape[j].ShapeState && j != count)
						{
							shape[count].shapetype += shape[j].shapetype;
							shape[j].ShapeState = false;
							shape[count].shapecoord[0][0] = fx;
							shape[count].shapecoord[0][1] = fy + 0.075;
							shape[count].shapecoord[1][0] = fx - 0.15;
							shape[count].shapecoord[1][1] = fy;
							shape[count].shapecoord[2][0] = fx - 0.075;
							shape[count].shapecoord[2][1] = fy - 0.075;
							shape[count].shapecoord[3][0] = fx + 0.075;
							shape[count].shapecoord[3][1] = fy - 0.075;
							shape[count].shapecoord[4][0] = fx + 0.15;
							shape[count].shapecoord[4][1] = fy;
							shape[count].run = randoms(gen);
						}
						break;
					case 5:
						if (Crash(shape[count].shapecoord[0][0], shape[count].shapecoord[3][0], shape[j].shapecoord[2][0], shape[j].shapecoord[3][0], shape[count].shapecoord[3][1], shape[count].shapecoord[0][1], shape[j].shapecoord[3][1], shape[j].shapecoord[0][1]) && shape[j].ShapeState && j != count)
						{
							shape[count].shapetype += shape[j].shapetype;
							if (shape[count].shapetype > 5)
							{
								shape[count].shapetype -= 5;
							}
							shape[j].ShapeState = false;
							shape[count].shapecoord[0][0] = fx - 0.015;
							shape[count].shapecoord[0][1] = fy + 0.015;
							shape[count].shapecoord[1][0] = fx + 0.015;
							shape[count].shapecoord[1][1] = fy + 0.015;
							shape[count].shapecoord[2][0] = fx - 0.015;
							shape[count].shapecoord[2][1] = fy - 0.015;
							shape[count].shapecoord[3][0] = fx + 0.015;
							shape[count].shapecoord[3][1] = fy - 0.015;
							shape[count].run = randoms(gen);
						}
						break;
					}
					break;
				case 2:
					switch (shape[j].shapetype)
					{
					case 1:
						if (Crash(shape[count].shapecoord[0][0], shape[count].shapecoord[1][0], shape[j].shapecoord[0][0], shape[j].shapecoord[3][0], shape[count].shapecoord[0][1], shape[count].shapecoord[1][1], shape[j].shapecoord[3][1], shape[j].shapecoord[0][1]) && shape[j].ShapeState && j != count)
						{
							shape[count].shapetype += shape[j].shapetype;
							shape[j].ShapeState = false;
							shape[count].shapecoord[0][0] = fx;
							shape[count].shapecoord[0][1] = fy + 0.15;
							shape[count].shapecoord[1][0] = fx - 0.15;
							shape[count].shapecoord[1][1] = fy - 0.15;
							shape[count].shapecoord[2][0] = fx + 0.15;
							shape[count].shapecoord[2][1] = fy - 0.15;
							shape[count].run = randoms(gen);
						}
						break;
					case 2:
						if (Crash(shape[count].shapecoord[0][0], shape[count].shapecoord[1][0], shape[j].shapecoord[0][0], shape[j].shapecoord[1][0], shape[count].shapecoord[0][1], shape[count].shapecoord[1][1], shape[j].shapecoord[0][1], shape[j].shapecoord[1][1]) && shape[j].ShapeState && j != count)
						{
							shape[count].shapetype += shape[j].shapetype;
							shape[j].ShapeState = false;
							shape[count].shapecoord[0][0] = fx - 0.15;
							shape[count].shapecoord[0][1] = fy + 0.15;
							shape[count].shapecoord[1][0] = fx + 0.15;
							shape[count].shapecoord[1][1] = fy + 0.15;
							shape[count].shapecoord[2][0] = fx - 0.15;
							shape[count].shapecoord[2][1] = fy - 0.15;
							shape[count].shapecoord[3][0] = fx + 0.15;
							shape[count].shapecoord[3][1] = fy - 0.15;
							shape[count].run = randoms(gen);
						}
						break;
					case 3:
						if (Crash(shape[count].shapecoord[0][0], shape[count].shapecoord[1][0], shape[j].shapecoord[1][0], shape[j].shapecoord[2][0], shape[count].shapecoord[0][1], shape[count].shapecoord[1][1], shape[j].shapecoord[1][1], shape[j].shapecoord[0][1]) && shape[j].ShapeState && j != count)
						{
							shape[count].shapetype += shape[j].shapetype;
							shape[j].ShapeState = false;
							shape[count].shapecoord[0][0] = fx;
							shape[count].shapecoord[0][1] = fy + 0.075;
							shape[count].shapecoord[1][0] = fx - 0.15;
							shape[count].shapecoord[1][1] = fy;
							shape[count].shapecoord[2][0] = fx - 0.075;
							shape[count].shapecoord[2][1] = fy - 0.075;
							shape[count].shapecoord[3][0] = fx + 0.075;
							shape[count].shapecoord[3][1] = fy - 0.075;
							shape[count].shapecoord[4][0] = fx + 0.15;
							shape[count].shapecoord[4][1] = fy;
							shape[count].run = randoms(gen);
						}
						break;
					case 4:
						if (Crash(shape[count].shapecoord[0][0], shape[count].shapecoord[1][0], shape[j].shapecoord[0][0], shape[j].shapecoord[3][0], shape[count].shapecoord[0][1], shape[count].shapecoord[1][1], shape[j].shapecoord[3][1], shape[j].shapecoord[0][1]) && shape[j].ShapeState && j != count)
						{
							shape[count].shapetype += shape[j].shapetype;
							shape[j].ShapeState = false;
							if (shape[count].shapetype > 5)
							{
								shape[count].shapetype -= 5;
							}
							shape[count].shapecoord[0][0] = fx - 0.015;
							shape[count].shapecoord[0][1] = fy + 0.015;
							shape[count].shapecoord[1][0] = fx + 0.015;
							shape[count].shapecoord[1][1] = fy + 0.015;
							shape[count].shapecoord[2][0] = fx - 0.015;
							shape[count].shapecoord[2][1] = fy - 0.015;
							shape[count].shapecoord[3][0] = fx + 0.015;
							shape[count].shapecoord[3][1] = fy - 0.015;
							shape[count].run = randoms(gen);
						}
						break;
					case 5:
						if (Crash(shape[count].shapecoord[0][0], shape[count].shapecoord[1][0], shape[j].shapecoord[2][0], shape[j].shapecoord[3][0], shape[count].shapecoord[0][1], shape[count].shapecoord[1][1], shape[j].shapecoord[3][1], shape[j].shapecoord[0][1]) && shape[j].ShapeState && j != count)
						{
							shape[count].shapetype += shape[j].shapetype;
							if (shape[count].shapetype > 5)
							{
								shape[count].shapetype -= 5;
							}
							shape[j].ShapeState = false;
							shape[count].shapecoord[0][0] = fx - 0.15;
							shape[count].shapecoord[0][1] = fy - 0.15;
							shape[count].shapecoord[1][0] = fx + 0.15;
							shape[count].shapecoord[1][1] = fy + 0.15;
							shape[count].run = randoms(gen);
						}
						break;
					}
					break;
				case 3:
					switch (shape[j].shapetype)
					{
					case 1:
						if (Crash(shape[count].shapecoord[1][0], shape[count].shapecoord[2][0], shape[j].shapecoord[0][0], shape[j].shapecoord[3][0], shape[count].shapecoord[1][1], shape[count].shapecoord[0][1], shape[j].shapecoord[3][1], shape[j].shapecoord[0][1]) && shape[j].ShapeState && j != count)
						{
							shape[count].shapetype += shape[j].shapetype;
							shape[j].ShapeState = false;
							shape[count].shapecoord[0][0] = fx - 0.15;
							shape[count].shapecoord[0][1] = fy + 0.15;
							shape[count].shapecoord[1][0] = fx + 0.15;
							shape[count].shapecoord[1][1] = fy + 0.15;
							shape[count].shapecoord[2][0] = fx - 0.15;
							shape[count].shapecoord[2][1] = fy - 0.15;
							shape[count].shapecoord[3][0] = fx + 0.15;
							shape[count].shapecoord[3][1] = fy - 0.15;
							shape[count].run = randoms(gen);
						}
						break;
					case 2:
						if (Crash(shape[count].shapecoord[1][0], shape[count].shapecoord[2][0], shape[j].shapecoord[0][0], shape[j].shapecoord[1][0], shape[count].shapecoord[1][1], shape[count].shapecoord[0][1], shape[j].shapecoord[0][1], shape[j].shapecoord[1][1]) && shape[j].ShapeState && j != count)
						{
							shape[count].shapetype += shape[j].shapetype;
							shape[j].ShapeState = false;
							shape[count].shapecoord[0][0] = fx;
							shape[count].shapecoord[0][1] = fy + 0.075;
							shape[count].shapecoord[1][0] = fx - 0.15;
							shape[count].shapecoord[1][1] = fy;
							shape[count].shapecoord[2][0] = fx - 0.075;
							shape[count].shapecoord[2][1] = fy - 0.075;
							shape[count].shapecoord[3][0] = fx + 0.075;
							shape[count].shapecoord[3][1] = fy - 0.075;
							shape[count].shapecoord[4][0] = fx + 0.15;
							shape[count].shapecoord[4][1] = fy;
							shape[count].run = randoms(gen);
						}
						break;
					case 3:
						if (Crash(shape[count].shapecoord[1][0], shape[count].shapecoord[2][0], shape[j].shapecoord[1][0], shape[j].shapecoord[2][0], shape[count].shapecoord[1][1], shape[count].shapecoord[0][1], shape[j].shapecoord[1][1], shape[j].shapecoord[0][1]) && shape[j].ShapeState && j != count)
						{
							shape[count].shapetype += shape[j].shapetype;
							shape[j].ShapeState = false;
							if (shape[count].shapetype > 5)
							{
								shape[count].shapetype -= 5;
							}
							shape[count].shapecoord[0][0] = fx - 0.015;
							shape[count].shapecoord[0][1] = fy + 0.015;
							shape[count].shapecoord[1][0] = fx + 0.015;
							shape[count].shapecoord[1][1] = fy + 0.015;
							shape[count].shapecoord[2][0] = fx - 0.015;
							shape[count].shapecoord[2][1] = fy - 0.015;
							shape[count].shapecoord[3][0] = fx + 0.015;
							shape[count].shapecoord[3][1] = fy - 0.015;
							shape[count].run = randoms(gen);
						}
						break;
					case 4:
						if (Crash(shape[count].shapecoord[1][0], shape[count].shapecoord[2][0], shape[j].shapecoord[0][0], shape[j].shapecoord[3][0], shape[count].shapecoord[1][1], shape[count].shapecoord[0][1], shape[j].shapecoord[3][1], shape[j].shapecoord[0][1]) && shape[j].ShapeState && j != count)
						{
							shape[count].shapetype += shape[j].shapetype;
							shape[j].ShapeState = false;
							if (shape[count].shapetype > 5)
							{
								shape[count].shapetype -= 5;
							}
							shape[count].shapecoord[0][0] = fx - 0.15;
							shape[count].shapecoord[0][1] = fy - 0.15;
							shape[count].shapecoord[1][0] = fx + 0.15;
							shape[count].shapecoord[1][1] = fy + 0.15;
							shape[count].run = randoms(gen);
						}
						break;
					case 5:
						if (Crash(shape[count].shapecoord[1][0], shape[count].shapecoord[2][0], shape[j].shapecoord[2][0], shape[j].shapecoord[3][0], shape[count].shapecoord[1][1], shape[count].shapecoord[0][1], shape[j].shapecoord[3][1], shape[j].shapecoord[0][1]) && shape[j].ShapeState && j != count)
						{
							shape[count].shapetype += shape[j].shapetype;
							if (shape[count].shapetype > 5)
							{
								shape[count].shapetype -= 5;
							}
							shape[j].ShapeState = false;
							shape[count].shapecoord[0][0] = fx;
							shape[count].shapecoord[0][1] = fy + 0.15;
							shape[count].shapecoord[1][0] = fx - 0.15;
							shape[count].shapecoord[1][1] = fy - 0.15;
							shape[count].shapecoord[2][0] = fx + 0.15;
							shape[count].shapecoord[2][1] = fy - 0.15;
							shape[count].run = randoms(gen);
						}
						break;
					}
					break;
				case 4:
					switch (shape[j].shapetype)
					{
					case 1:
						if (Crash(shape[count].shapecoord[0][0], shape[count].shapecoord[3][0], shape[j].shapecoord[0][0], shape[j].shapecoord[3][0], shape[count].shapecoord[3][1], shape[count].shapecoord[0][1], shape[j].shapecoord[3][1], shape[j].shapecoord[0][1]) && shape[j].ShapeState && j != count)
						{
							shape[count].shapetype += shape[j].shapetype;
							shape[j].ShapeState = false;
							shape[count].shapecoord[0][0] = fx;
							shape[count].shapecoord[0][1] = fy + 0.075;
							shape[count].shapecoord[1][0] = fx - 0.15;
							shape[count].shapecoord[1][1] = fy;
							shape[count].shapecoord[2][0] = fx - 0.075;
							shape[count].shapecoord[2][1] = fy - 0.075;
							shape[count].shapecoord[3][0] = fx + 0.075;
							shape[count].shapecoord[3][1] = fy - 0.075;
							shape[count].shapecoord[4][0] = fx + 0.15;
							shape[count].shapecoord[4][1] = fy;
							shape[count].run = randoms(gen);
						}
						break;
					case 2:
						if (Crash(shape[count].shapecoord[0][0], shape[count].shapecoord[3][0], shape[j].shapecoord[0][0], shape[j].shapecoord[1][0], shape[count].shapecoord[3][1], shape[count].shapecoord[0][1], shape[j].shapecoord[0][1], shape[j].shapecoord[1][1]) && shape[j].ShapeState && j != count)
						{
							shape[count].shapetype += shape[j].shapetype;
							shape[j].ShapeState = false;
							if (shape[count].shapetype > 5)
							{
								shape[count].shapetype -= 5;
							}
							shape[count].shapecoord[0][0] = fx - 0.015;
							shape[count].shapecoord[0][1] = fy + 0.015;
							shape[count].shapecoord[1][0] = fx + 0.015;
							shape[count].shapecoord[1][1] = fy + 0.015;
							shape[count].shapecoord[2][0] = fx - 0.015;
							shape[count].shapecoord[2][1] = fy - 0.015;
							shape[count].shapecoord[3][0] = fx + 0.015;
							shape[count].shapecoord[3][1] = fy - 0.015;
							shape[count].run = randoms(gen);
						}
						break;
					case 3:
						if (Crash(shape[count].shapecoord[0][0], shape[count].shapecoord[3][0], shape[j].shapecoord[1][0], shape[j].shapecoord[2][0], shape[count].shapecoord[3][1], shape[count].shapecoord[0][1], shape[j].shapecoord[1][1], shape[j].shapecoord[0][1]) && shape[j].ShapeState && j != count)
						{
							shape[count].shapetype += shape[j].shapetype;
							shape[j].ShapeState = false;
							if (shape[count].shapetype > 5)
							{
								shape[count].shapetype -= 5;
							}
							shape[count].shapecoord[0][0] = fx - 0.15;
							shape[count].shapecoord[0][1] = fy - 0.15;
							shape[count].shapecoord[1][0] = fx + 0.15;
							shape[count].shapecoord[1][1] = fy + 0.15;
							shape[count].run = randoms(gen);
						}
						break;
					case 4:
						if (Crash(shape[count].shapecoord[0][0], shape[count].shapecoord[3][0], shape[j].shapecoord[0][0], shape[j].shapecoord[3][0], shape[count].shapecoord[3][1], shape[count].shapecoord[0][1], shape[j].shapecoord[3][1], shape[j].shapecoord[0][1]) && shape[j].ShapeState && j != count)
						{
							shape[count].shapetype += shape[j].shapetype;
							shape[j].ShapeState = false;
							if (shape[count].shapetype > 5)
							{
								shape[count].shapetype -= 5;
							}
							shape[count].shapecoord[0][0] = fx;
							shape[count].shapecoord[0][1] = fy + 0.15;
							shape[count].shapecoord[1][0] = fx - 0.15;
							shape[count].shapecoord[1][1] = fy - 0.15;
							shape[count].shapecoord[2][0] = fx + 0.15;
							shape[count].shapecoord[2][1] = fy - 0.15;
							shape[count].run = randoms(gen);
						}
						break;
					case 5:
						if (Crash(shape[count].shapecoord[0][0], shape[count].shapecoord[3][0], shape[j].shapecoord[2][0], shape[j].shapecoord[3][0], shape[count].shapecoord[3][1], shape[count].shapecoord[0][1], shape[j].shapecoord[3][1], shape[j].shapecoord[0][1]) && shape[j].ShapeState && j != count)
						{
							shape[count].shapetype += shape[j].shapetype;
							if (shape[count].shapetype > 5)
							{
								shape[count].shapetype -= 5;
							}
							shape[j].ShapeState = false;
							shape[count].shapecoord[0][0] = fx - 0.15;
							shape[count].shapecoord[0][1] = fy + 0.15;
							shape[count].shapecoord[1][0] = fx + 0.15;
							shape[count].shapecoord[1][1] = fy + 0.15;
							shape[count].shapecoord[2][0] = fx - 0.15;
							shape[count].shapecoord[2][1] = fy - 0.15;
							shape[count].shapecoord[3][0] = fx + 0.15;
							shape[count].shapecoord[3][1] = fy - 0.15;
							shape[count].run = randoms(gen);
						}
						break;
					}
					break;
				case 5:
					switch (shape[j].shapetype)
					{
					case 1:
						if (Crash(shape[count].shapecoord[2][0], shape[count].shapecoord[3][0], shape[j].shapecoord[0][0], shape[j].shapecoord[3][0], shape[count].shapecoord[3][1], shape[count].shapecoord[0][1], shape[j].shapecoord[3][1], shape[j].shapecoord[0][1]) && shape[j].ShapeState && j != count)
						{
							shape[count].shapetype += shape[j].shapetype;
							shape[j].ShapeState = false;
							if (shape[count].shapetype > 5)
							{
								shape[count].shapetype -= 5;
							}
							shape[count].shapecoord[0][0] = fx - 0.015;
							shape[count].shapecoord[0][1] = fy + 0.015;
							shape[count].shapecoord[1][0] = fx + 0.015;
							shape[count].shapecoord[1][1] = fy + 0.015;
							shape[count].shapecoord[2][0] = fx - 0.015;
							shape[count].shapecoord[2][1] = fy - 0.015;
							shape[count].shapecoord[3][0] = fx + 0.015;
							shape[count].shapecoord[3][1] = fy - 0.015;
							shape[count].run = randoms(gen);
						}
						break;
					case 2:
						if (Crash(shape[count].shapecoord[2][0], shape[count].shapecoord[3][0], shape[j].shapecoord[0][0], shape[j].shapecoord[1][0], shape[count].shapecoord[3][1], shape[count].shapecoord[0][1], shape[j].shapecoord[0][1], shape[j].shapecoord[1][1]) && shape[j].ShapeState && j != count)
						{
							shape[count].shapetype += shape[j].shapetype;
							shape[j].ShapeState = false;
							if (shape[count].shapetype > 5)
							{
								shape[count].shapetype -= 5;
							}
							shape[count].shapecoord[0][0] = fx - 0.15;
							shape[count].shapecoord[0][1] = fy - 0.15;
							shape[count].shapecoord[1][0] = fx + 0.15;
							shape[count].shapecoord[1][1] = fy + 0.15;
							shape[count].run = randoms(gen);
						}
						break;
					case 3:
						if (Crash(shape[count].shapecoord[2][0], shape[count].shapecoord[3][0], shape[j].shapecoord[1][0], shape[j].shapecoord[2][0], shape[count].shapecoord[3][1], shape[count].shapecoord[0][1], shape[j].shapecoord[1][1], shape[j].shapecoord[0][1]) && shape[j].ShapeState && j != count)
						{
							shape[count].shapetype += shape[j].shapetype;
							shape[j].ShapeState = false;
							if (shape[count].shapetype > 5)
							{
								shape[count].shapetype -= 5;
							}
							shape[count].shapecoord[0][0] = fx;
							shape[count].shapecoord[0][1] = fy + 0.15;
							shape[count].shapecoord[1][0] = fx - 0.15;
							shape[count].shapecoord[1][1] = fy - 0.15;
							shape[count].shapecoord[2][0] = fx + 0.15;
							shape[count].shapecoord[2][1] = fy - 0.15;
							shape[count].run = randoms(gen);
						}
						break;
					case 4:
						if (Crash(shape[count].shapecoord[2][0], shape[count].shapecoord[3][0], shape[j].shapecoord[0][0], shape[j].shapecoord[3][0], shape[count].shapecoord[3][1], shape[count].shapecoord[0][1], shape[j].shapecoord[3][1], shape[j].shapecoord[0][1]) && shape[j].ShapeState && j != count)
						{
							shape[count].shapetype += shape[j].shapetype;
							shape[j].ShapeState = false;
							if (shape[count].shapetype > 5)
							{
								shape[count].shapetype -= 5;
							}
							shape[count].shapecoord[0][0] = fx - 0.15;
							shape[count].shapecoord[0][1] = fy + 0.15;
							shape[count].shapecoord[1][0] = fx + 0.15;
							shape[count].shapecoord[1][1] = fy + 0.15;
							shape[count].shapecoord[2][0] = fx - 0.15;
							shape[count].shapecoord[2][1] = fy - 0.15;
							shape[count].shapecoord[3][0] = fx + 0.15;
							shape[count].shapecoord[3][1] = fy - 0.15;
							shape[count].run = randoms(gen);
						}
						break;
					case 5:
						if (Crash(shape[count].shapecoord[2][0], shape[count].shapecoord[3][0], shape[j].shapecoord[2][0], shape[j].shapecoord[3][0], shape[count].shapecoord[3][1], shape[count].shapecoord[0][1], shape[j].shapecoord[3][1], shape[j].shapecoord[0][1]) && shape[j].ShapeState && j != count)
						{
							shape[count].shapetype += shape[j].shapetype;
							if (shape[count].shapetype > 5)
							{
								shape[count].shapetype -= 5;
							}
							shape[j].ShapeState = false;
							shape[count].shapecoord[0][0] = fx;
							shape[count].shapecoord[0][1] = fy + 0.075;
							shape[count].shapecoord[1][0] = fx - 0.15;
							shape[count].shapecoord[1][1] = fy;
							shape[count].shapecoord[2][0] = fx - 0.075;
							shape[count].shapecoord[2][1] = fy - 0.075;
							shape[count].shapecoord[3][0] = fx + 0.075;
							shape[count].shapecoord[3][1] = fy - 0.075;
							shape[count].shapecoord[4][0] = fx + 0.15;
							shape[count].shapecoord[4][1] = fy;
							shape[count].run = randoms(gen);
						}
						break;
					}
					break;
				}
			}
			if (shape[i].MouseState)
			{
				shape[i].MouseState = false;
				count = 0;
			}
			if (!starter)
			{
				glutTimerFunc(10, TimerFunction, 1);
				starter = true;
			}
		}
	}
	glutPostRedisplay();
}

GLvoid Motion(int x, int y)
{
	convertXY(x, y, fx2, fy2);
	float movex = fx2 - bfx;
	float movey = fy2 - bfy;
	bfx = fx2;
	bfy = fy2;
	for (int i = 0; i < 15; i++)
	{
		if (shape[i].MouseState)
		{
			switch (shape[i].shapetype)
			{
			case 1:
				for (int j = 0; j < 4; j++)
				{
					shape[i].shapecoord[j][0] += movex;
					shape[i].shapecoord[j][1] += movey;
				}
				break;
			case 2:
				for (int j = 0; j < 2; j++)
				{
					shape[i].shapecoord[j][0] += movex;
					shape[i].shapecoord[j][1] += movey;
				}
				break;
			case 3:
				for (int j = 0; j < 3; j++)
				{
					shape[i].shapecoord[j][0] += movex;
					shape[i].shapecoord[j][1] += movey;
				}
				break;
			case 4:
				for (int j = 0; j < 4; j++)
				{
					shape[i].shapecoord[j][0] += movex;
					shape[i].shapecoord[j][1] += movey;
				}
				break;
			case 5:
				for (int j = 0; j < 5; j++)
				{
					shape[i].shapecoord[j][0] += movex;
					shape[i].shapecoord[j][1] += movey;
				}
				break;
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
	glBufferData(GL_ARRAY_BUFFER, 15 * 5 * 3 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	//--- 좌표값을 attribute 인덱스 0번에 명시한다: 버텍스 당 3* float
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//--- attribute 인덱스 0번을 사용가능하게 함
	glEnableVertexAttribArray(0);

	//--- 2번째 VBO를 활성화 하여 바인드 하고, 버텍스 속성 (색상)을 저장
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	//--- 변수 colors에서 버텍스 색상을 복사한다.
	//--- colors 배열의 사이즈: 9 *float
	glBufferData(GL_ARRAY_BUFFER, 15 * 5 * 3 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	//--- 색상값을 attribute 인덱스 1번에 명시한다: 버텍스 당 3*float
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//--- attribute 인덱스 1번을 사용 가능하게 함.
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	GLuint indices[15 * 5];
	for (int i = 0; i < 15 * 5; i++)
	{
		indices[i] = i;
	}
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);
}

void UpdateBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	for (int i = 0; i < 15; i++)
	{
		glBufferSubData(GL_ARRAY_BUFFER, i * 15 * sizeof(GLfloat), 15 * sizeof(GLfloat), shape[i].shapecoord);
	}
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	for (int i = 0; i < 15; i++)
	{
		glBufferSubData(GL_ARRAY_BUFFER, i * 15 * sizeof(GLfloat), 15 * sizeof(GLfloat), shape[i].color);
	}
}

GLvoid TimerFunction(int value)
{
	for (int i = 0; i < 15; i++)
	{
		switch (shape[i].run)
		{
		case 1:
			switch (shape[i].shapetype)
			{
			case 1:
				if (shape[i].up)
				{
					for (int j = 0; j < 4; j++)
					{
						shape[i].shapecoord[j][0] += 0.01;
					}
				}
				else
				{
					for (int j = 0; j < 4; j++)
					{
						shape[i].shapecoord[j][0] -= 0.01;
					}
				}
				if (shape[i].down)
				{
					for (int j = 0; j < 4; j++)
					{
						shape[i].shapecoord[j][1] += 0.01;
					}
				}
				else
				{
					for (int j = 0; j < 4; j++)
					{
						shape[i].shapecoord[j][1] -= 0.01;
					}
				}
				if (shape[i].shapecoord[0][0] < -1)
				{
					shape[i].up = true;
				}
				else if (shape[i].shapecoord[3][0] > 1)
				{
					shape[i].up = false;
				}
				if (shape[i].shapecoord[0][1] < -1)
				{
					shape[i].down = true;
				}
				else if (shape[i].shapecoord[3][1] > 1)
				{
					shape[i].down = false;
				}
				// this start
				break;
			case 2:
				if (shape[i].up)
				{
					for (int j = 0; j < 2; j++)
					{
						shape[i].shapecoord[j][0] += 0.01;
					}
				}
				else
				{
					for (int j = 0; j < 2; j++)
					{
						shape[i].shapecoord[j][0] -= 0.01;
					}
				}
				if (shape[i].down)
				{
					for (int j = 0; j < 2; j++)
					{
						shape[i].shapecoord[j][1] += 0.01;
					}
				}
				else
				{
					for (int j = 0; j < 2; j++)
					{
						shape[i].shapecoord[j][1] -= 0.01;
					}
				}
				if (shape[i].shapecoord[0][0] < -1)
				{
					shape[i].up = true;
				}
				else if (shape[i].shapecoord[1][0] > 1)
				{
					shape[i].up = false;
				}
				if (shape[i].shapecoord[0][1] < -1)
				{
					shape[i].down = true;
				}
				else if (shape[i].shapecoord[1][1] > 1)
				{
					shape[i].down = false;
				}
				break;
			case 3:
				if (shape[i].up)
				{
					for (int j = 0; j < 3; j++)
					{
						shape[i].shapecoord[j][0] += 0.01;
					}
				}
				else
				{
					for (int j = 0; j < 3; j++)
					{
						shape[i].shapecoord[j][0] -= 0.01;
					}
				}
				if (shape[i].down)
				{
					for (int j = 0; j < 3; j++)
					{
						shape[i].shapecoord[j][1] += 0.01;
					}
				}
				else
				{
					for (int j = 0; j < 3; j++)
					{
						shape[i].shapecoord[j][1] -= 0.01;
					}
				}
				if (shape[i].shapecoord[1][0] < -1)
				{
					shape[i].up = true;
				}
				else if (shape[i].shapecoord[2][0] > 1)
				{
					shape[i].up = false;
				}
				if (shape[i].shapecoord[2][1] < -1)
				{
					shape[i].down = true;
				}
				else if (shape[i].shapecoord[0][1] > 1)
				{
					shape[i].down = false;
				}
				break;
			case 4:
				if (shape[i].up)
				{
					for (int j = 0; j < 4; j++)
					{
						shape[i].shapecoord[j][0] += 0.01;
					}
				}
				else
				{
					for (int j = 0; j < 4; j++)
					{
						shape[i].shapecoord[j][0] -= 0.01;
					}
				}
				if (shape[i].down)
				{
					for (int j = 0; j < 4; j++)
					{
						shape[i].shapecoord[j][1] += 0.01;
					}
				}
				else
				{
					for (int j = 0; j < 4; j++)
					{
						shape[i].shapecoord[j][1] -= 0.01;
					}
				}
				if (shape[i].shapecoord[0][0] < -1)
				{
					shape[i].up = true;
				}
				else if (shape[i].shapecoord[3][0] > 1)
				{
					shape[i].up = false;
				}
				if (shape[i].shapecoord[0][1] < -0.7)
				{
					shape[i].down = true;
				}
				else if (shape[i].shapecoord[3][1] > 0.7)
				{
					shape[i].down = false;
				}
				break;
			case 5:
				if (shape[i].up)
				{
					for (int j = 0; j < 5; j++)
					{
						shape[i].shapecoord[j][0] += 0.01;
					}
				}
				else
				{
					for (int j = 0; j < 5; j++)
					{
						shape[i].shapecoord[j][0] -= 0.01;
					}
				}
				if (shape[i].down)
				{
					for (int j = 0; j < 5; j++)
					{
						shape[i].shapecoord[j][1] += 0.01;
					}
				}
				else
				{
					for (int j = 0; j < 5; j++)
					{
						shape[i].shapecoord[j][1] -= 0.01;
					}
				}
				if (shape[i].shapecoord[1][0] < -1)
				{
					shape[i].up = true;
				}
				else if (shape[i].shapecoord[4][0] > 1)
				{
					shape[i].up = false;
				}
				if (shape[i].shapecoord[2][1] < -1)
				{
					shape[i].down = true;
				}
				else if (shape[i].shapecoord[0][1] > 1)
				{
					shape[i].down = false;
				}
				break;
			}
			break;
		case 2:
			switch (shape[i].shapetype)
			{
			case 1:
				if (shape[i].up)
				{
					for (int j = 0; j < 4; j++)
					{
						shape[i].shapecoord[j][0] += 0.01;
					}
				}
				else
				{
					for (int j = 0; j < 4; j++)
					{
						shape[i].shapecoord[j][0] -= 0.01;
					}
				}
				if (shape[i].shapecoord[0][0] < -1)
				{
					shape[i].up = true;
					if (shape[i].down)
					{
						for (int j = 0; j < 4; j++)
						{
							shape[i].shapecoord[j][1] += 0.05;
						}
					}
					else
					{
						for (int j = 0; j < 4; j++)
						{
							shape[i].shapecoord[j][1] -= 0.05;
						}
					}
				}
				else if (shape[i].shapecoord[3][0] > 1)
				{
					shape[i].up = false;
					if (shape[i].down)
					{
						for (int j = 0; j < 4; j++)
						{
							shape[i].shapecoord[j][1] += 0.05;
						}
					}
					else
					{
						for (int j = 0; j < 4; j++)
						{
							shape[i].shapecoord[j][1] -= 0.05;
						}
					}
				}
				if (shape[i].shapecoord[0][1] > 1)
				{
					shape[i].down = false;
				}
				else if (shape[i].shapecoord[3][1] < -1)
				{
					shape[i].down = true;
				}
				break;
			case 2:
				if (shape[i].up)
				{
					for (int j = 0; j < 2; j++)
					{
						shape[i].shapecoord[j][0] += 0.01;
					}
				}
				else
				{
					for (int j = 0; j < 2; j++)
					{
						shape[i].shapecoord[j][0] -= 0.01;
					}
				}
				if (shape[i].shapecoord[0][0] < -1)
				{
					shape[i].up = true;
					if (shape[i].down)
					{
						for (int j = 0; j < 2; j++)
						{
							shape[i].shapecoord[j][1] += 0.05;
						}
					}
					else
					{
						for (int j = 0; j < 2; j++)
						{
							shape[i].shapecoord[j][1] -= 0.05;
						}
					}
				}
				else if (shape[i].shapecoord[1][0] > 1)
				{
					shape[i].up = false;
					if (shape[i].down)
					{
						for (int j = 0; j < 2; j++)
						{
							shape[i].shapecoord[j][1] += 0.05;
						}
					}
					else
					{
						for (int j = 0; j < 2; j++)
						{
							shape[i].shapecoord[j][1] -= 0.05;
						}
					}
				}
				if (shape[i].shapecoord[1][1] > 1)
				{
					shape[i].down = false;
				}
				else if (shape[i].shapecoord[0][1] < -1)
				{
					shape[i].down = true;
				}
				break;
			case 3:
				if (shape[i].up)
				{
					for (int j = 0; j < 3; j++)
					{
						shape[i].shapecoord[j][0] += 0.01;
					}
				}
				else
				{
					for (int j = 0; j < 3; j++)
					{
						shape[i].shapecoord[j][0] -= 0.01;
					}
				}
				if (shape[i].shapecoord[1][0] < -1)
				{
					shape[i].up = true;
					if (shape[i].down)
					{
						for (int j = 0; j < 3; j++)
						{
							shape[i].shapecoord[j][1] += 0.05;
						}
					}
					else
					{
						for (int j = 0; j < 3; j++)
						{
							shape[i].shapecoord[j][1] -= 0.05;
						}
					}
				}
				else if (shape[i].shapecoord[2][0] > 1)
				{
					shape[i].up = false;
					if (shape[i].down)
					{
						for (int j = 0; j < 3; j++)
						{
							shape[i].shapecoord[j][1] += 0.05;
						}
					}
					else
					{
						for (int j = 0; j < 3; j++)
						{
							shape[i].shapecoord[j][1] -= 0.05;
						}
					}
				}
				if (shape[i].shapecoord[0][1] > 1)
				{
					shape[i].down = false;
				}
				else if (shape[i].shapecoord[2][1] < -1)
				{
					shape[i].down = true;
				}
				break;
			case 4:
				if (shape[i].up)
				{
					for (int j = 0; j < 4; j++)
					{
						shape[i].shapecoord[j][0] += 0.01;
					}
				}
				else
				{
					for (int j = 0; j < 4; j++)
					{
						shape[i].shapecoord[j][0] -= 0.01;
					}
				}
				if (shape[i].shapecoord[0][0] < -1)
				{
					shape[i].up = true;
					if (shape[i].down)
					{
						for (int j = 0; j < 4; j++)
						{
							shape[i].shapecoord[j][1] += 0.05;
						}
					}
					else
					{
						for (int j = 0; j < 4; j++)
						{
							shape[i].shapecoord[j][1] -= 0.05;
						}
					}
				}
				else if (shape[i].shapecoord[3][0] > 1)
				{
					shape[i].up = false;
					if (shape[i].down)
					{
						for (int j = 0; j < 4; j++)
						{
							shape[i].shapecoord[j][1] += 0.05;
						}
					}
					else
					{
						for (int j = 0; j < 4; j++)
						{
							shape[i].shapecoord[j][1] -= 0.05;
						}
					}
				}
				if (shape[i].shapecoord[0][1] > 1)
				{
					shape[i].down = false;
				}
				else if (shape[i].shapecoord[3][1] < -1)
				{
					shape[i].down = true;
				}
				break;
			case 5:
				if (shape[i].up)
				{
					for (int j = 0; j < 5; j++)
					{
						shape[i].shapecoord[j][0] += 0.01;
					}
				}
				else
				{
					for (int j = 0; j < 5; j++)
					{
						shape[i].shapecoord[j][0] -= 0.01;
					}
				}
				if (shape[i].shapecoord[1][0] < -1)
				{
					shape[i].up = true;
					if (shape[i].down)
					{
						for (int j = 0; j < 5; j++)
						{
							shape[i].shapecoord[j][1] += 0.05;
						}
					}
					else
					{
						for (int j = 0; j < 5; j++)
						{
							shape[i].shapecoord[j][1] -= 0.05;
						}
					}
				}
				else if (shape[i].shapecoord[4][0] > 1)
				{
					shape[i].up = false;
					if (shape[i].down)
					{
						for (int j = 0; j < 5; j++)
						{
							shape[i].shapecoord[j][1] += 0.05;
						}
					}
					else
					{
						for (int j = 0; j < 5; j++)
						{
							shape[i].shapecoord[j][1] -= 0.05;
						}
					}
				}
				if (shape[i].shapecoord[0][1] > 1)
				{
					shape[i].down = false;
				}
				else if (shape[i].shapecoord[2][1] < -1)
				{
					shape[i].down = true;
				}
				break;
			}
			break;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(10, TimerFunction, 1);
}