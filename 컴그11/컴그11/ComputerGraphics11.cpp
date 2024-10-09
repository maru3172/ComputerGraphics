#include "GLmain.h"

int donecount = 0;

GLvoid drawScene()
{
	glClearColor(bGCr, bGCg, bGCb, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shaderProgramID);
	UpdateBuffer();
	glBindVertexArray(vao);
	for (int i = 0; i < 4; i++)
	{
		if (shape[i].shapetype == 1)
		{
			glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (void*)(i * 5 * sizeof(GLuint)));
		}
		else if (shape[i].shapetype == 2)
		{
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(i * 5 * sizeof(GLuint)));
		}
		else if (shape[i].shapetype == 3)
		{
			glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, (void*)(i * 5 * sizeof(GLuint)));
		}
		else if (shape[i].shapetype == 4 || shape[i].shapetype == 5)
		{
			glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, (void*)(i * 5 * sizeof(GLuint)));
		}
	}
	glutSwapBuffers();
}


GLvoid Keyboard(unsigned char key, int x, int y)
{
	donecount = 0;
	for (int i = 0; i < 4; i++)
	{
		switch (key)
		{
		case 'l':
			if (shape[i].shapetype == 1)
			{
				shape[i].shapetype = 2;
				shape[i].done = false;
				if (shape[i].shapecoord[0][0] < 0 && shape[i].shapecoord[0][1] > 0)
				{
					shape[i].shapecoord[0][0] = -0.5;
					shape[i].shapecoord[0][1] = 0.5 + 0.25;
					shape[i].shapecoord[1][0] = -0.5 - 0.25;
					shape[i].shapecoord[1][1] = 0.5 - 0.25;
				}
				else if (shape[i].shapecoord[0][0] > 0 && shape[i].shapecoord[0][1] > 0)
				{
					shape[i].shapecoord[0][0] = 0.5;
					shape[i].shapecoord[0][1] = 0.5 + 0.25;
					shape[i].shapecoord[1][0] = 0.5 - 0.25;
					shape[i].shapecoord[1][1] = 0.5 - 0.25;
				}
				else if (shape[i].shapecoord[0][0] < 0 && shape[i].shapecoord[0][1] < 0)
				{
					shape[i].shapecoord[0][0] = -0.5;
					shape[i].shapecoord[0][1] = -0.5 + 0.25;
					shape[i].shapecoord[1][0] = -0.5 - 0.25;
					shape[i].shapecoord[1][1] = -0.5 - 0.25;
				}
				else if (shape[i].shapecoord[0][0] > 0 && shape[i].shapecoord[0][1] < 0)
				{
					shape[i].shapecoord[0][0] = 0.5;
					shape[i].shapecoord[0][1] = -0.5 + 0.25;
					shape[i].shapecoord[1][0] = 0.5 - 0.25;
					shape[i].shapecoord[1][1] = -0.5 - 0.25;
				}
				shape[i].shapecoord[2][0] = shape[i].shapecoord[1][0];
				shape[i].shapecoord[2][1] = shape[i].shapecoord[1][1];
			}
			break;
		case 't':
			if (shape[i].shapetype == 2)
			{
				shape[i].shapetype = 3;
				shape[i].done = false;
				if (shape[i].shapecoord[0][0] < 0 && shape[i].shapecoord[0][1] > 0)
				{
					shape[i].shapecoord[0][0] = -0.5 - 0.25;
					shape[i].shapecoord[0][1] = 0.5 + 0.25;
					shape[i].shapecoord[1][0] = -0.5 + 0.25;
					shape[i].shapecoord[1][1] = 0.5 + 0.25;
					shape[i].shapecoord[2][0] = -0.5 - 0.25;
					shape[i].shapecoord[2][1] = 0.5 - 0.25;
				}
				else if (shape[i].shapecoord[0][0] > 0 && shape[i].shapecoord[0][1] > 0)
				{
					shape[i].shapecoord[0][0] = 0.5 - 0.25;
					shape[i].shapecoord[0][1] = 0.5 + 0.25;
					shape[i].shapecoord[1][0] = 0.5 + 0.25;
					shape[i].shapecoord[1][1] = 0.5 + 0.25;
					shape[i].shapecoord[2][0] = 0.5 - 0.25;
					shape[i].shapecoord[2][1] = 0.5 - 0.25;
				}
				else if (shape[i].shapecoord[0][0] < 0 && shape[i].shapecoord[0][1] < 0)
				{
					shape[i].shapecoord[0][0] = -0.5 - 0.25;
					shape[i].shapecoord[0][1] = -0.5 + 0.25;
					shape[i].shapecoord[1][0] = -0.5 + 0.25;
					shape[i].shapecoord[1][1] = -0.5 + 0.25;
					shape[i].shapecoord[2][0] = -0.5 - 0.25;
					shape[i].shapecoord[2][1] = -0.5 - 0.25;
				}
				else if (shape[i].shapecoord[0][0] > 0 && shape[i].shapecoord[0][1] < 0)
				{
					shape[i].shapecoord[0][0] = 0.5 - 0.25;
					shape[i].shapecoord[0][1] = -0.5 + 0.25;
					shape[i].shapecoord[1][0] = 0.5 + 0.25;
					shape[i].shapecoord[1][1] = -0.5 + 0.25;
					shape[i].shapecoord[2][0] = 0.5 - 0.25;
					shape[i].shapecoord[2][1] = -0.5 - 0.25;
				}
				shape[i].shapecoord[3][0] = shape[i].shapecoord[2][0];
				shape[i].shapecoord[3][1] = shape[i].shapecoord[2][1];
			}
			break;
		case 'r':
			if (shape[i].shapetype == 3)
			{
				shape[i].shapetype = 4;
				shape[i].done = false;
				shape[i].shapetype = 4;
				shape[i].done = false;
				shape[i].Process[0] = false;
				shape[i].Process[1] = false;
				shape[i].Process[2] = false;
				if (shape[i].shapecoord[0][0] < 0 && shape[i].shapecoord[0][1] > 0)
				{
					shape[i].shapecoord[0][0] = -0.5;
					shape[i].shapecoord[0][1] = 0.5;
					shape[i].shapecoord[1][0] = -0.5 - 0.25;
					shape[i].shapecoord[1][1] = 0.5;
					shape[i].shapecoord[2][0] = -0.5 - 0.25;
					shape[i].shapecoord[2][1] = 0.5 - 0.25;
					shape[i].shapecoord[3][0] = -0.5 + 0.25;
					shape[i].shapecoord[3][1] = 0.5 - 0.25;
					shape[i].shapecoord[4][0] = -0.5 + 0.25;
					shape[i].shapecoord[4][1] = 0.5;

				}
				else if (shape[i].shapecoord[0][0] > 0 && shape[i].shapecoord[0][1] > 0)
				{
					shape[i].shapecoord[0][0] = 0.5;
					shape[i].shapecoord[0][1] = 0.5;
					shape[i].shapecoord[1][0] = 0.5 - 0.25;
					shape[i].shapecoord[1][1] = 0.5;
					shape[i].shapecoord[2][0] = 0.5 - 0.25;
					shape[i].shapecoord[2][1] = 0.5 - 0.25;
					shape[i].shapecoord[3][0] = 0.5 + 0.25;
					shape[i].shapecoord[3][1] = 0.5 - 0.25;
					shape[i].shapecoord[4][0] = 0.5 + 0.25;
					shape[i].shapecoord[4][1] = 0.5;
				}
				else if (shape[i].shapecoord[0][0] < 0 && shape[i].shapecoord[0][1] < 0)
				{
					shape[i].shapecoord[0][0] = -0.5;
					shape[i].shapecoord[0][1] = -0.5;
					shape[i].shapecoord[1][0] = -0.5 - 0.25;
					shape[i].shapecoord[1][1] = -0.5;
					shape[i].shapecoord[2][0] = -0.5 - 0.25;
					shape[i].shapecoord[2][1] = -0.5 - 0.25;
					shape[i].shapecoord[3][0] = -0.5 + 0.25;
					shape[i].shapecoord[3][1] = -0.5 - 0.25;
					shape[i].shapecoord[4][0] = -0.5 + 0.25;
					shape[i].shapecoord[4][1] = -0.5;
				}
				else if (shape[i].shapecoord[0][0] > 0 && shape[i].shapecoord[0][1] < 0)
				{
					shape[i].shapecoord[0][0] = 0.5;
					shape[i].shapecoord[0][1] = -0.5;
					shape[i].shapecoord[1][0] = 0.5 - 0.25;
					shape[i].shapecoord[1][1] = -0.5;
					shape[i].shapecoord[2][0] = 0.5 - 0.25;
					shape[i].shapecoord[2][1] = -0.5 - 0.25;
					shape[i].shapecoord[3][0] = 0.5 + 0.25;
					shape[i].shapecoord[3][1] = -0.5 - 0.25;
					shape[i].shapecoord[4][0] = 0.5 + 0.25;
					shape[i].shapecoord[4][1] = -0.5;
				}
			}
			break;
		case 'p':
			if (shape[i].shapetype == 4)
			{
				shape[i].shapetype = 5;
				for (int j = 0; j < 6; j++)
				{
					shape[i].Process[j] = false;
				}
				shape[i].done = false;
				if (shape[i].shapecoord[0][0] < 0 && shape[i].shapecoord[0][1] > 0)
				{
					shape[i].shapecoord[0][0] = -0.5;
					shape[i].shapecoord[0][1] = 0.5 + 0.25;
					shape[i].shapecoord[1][0] = -0.5 - 0.25;
					shape[i].shapecoord[1][1] = 0.5;
					shape[i].shapecoord[2][0] = -0.5 - 0.15;
					shape[i].shapecoord[2][1] = 0.5 - 0.25;
					shape[i].shapecoord[3][0] = -0.5 + 0.15;
					shape[i].shapecoord[3][1] = 0.5 - 0.25;
					shape[i].shapecoord[4][0] = -0.5 + 0.25;
					shape[i].shapecoord[4][1] = 0.5;
				}
				else if (shape[i].shapecoord[0][0] > 0 && shape[i].shapecoord[0][1] > 0)
				{
					shape[i].shapecoord[0][0] = 0.5;
					shape[i].shapecoord[0][1] = 0.5 + 0.25;
					shape[i].shapecoord[1][0] = 0.5 - 0.25;
					shape[i].shapecoord[1][1] = 0.5;
					shape[i].shapecoord[2][0] = 0.5 - 0.15;
					shape[i].shapecoord[2][1] = 0.5 - 0.25;
					shape[i].shapecoord[3][0] = 0.5 + 0.15;
					shape[i].shapecoord[3][1] = 0.5 - 0.25;
					shape[i].shapecoord[4][0] = 0.5 + 0.25;
					shape[i].shapecoord[4][1] = 0.5;
				}
				else if (shape[i].shapecoord[0][0] < 0 && shape[i].shapecoord[0][1] < 0)
				{
					shape[i].shapecoord[0][0] = -0.5;
					shape[i].shapecoord[0][1] = -0.5 + 0.25;
					shape[i].shapecoord[1][0] = -0.5 - 0.25;
					shape[i].shapecoord[1][1] = -0.5;
					shape[i].shapecoord[2][0] = -0.5 - 0.15;
					shape[i].shapecoord[2][1] = -0.5 - 0.25;
					shape[i].shapecoord[3][0] = -0.5 + 0.15;
					shape[i].shapecoord[3][1] = -0.5 - 0.25;
					shape[i].shapecoord[4][0] = -0.5 + 0.25;
					shape[i].shapecoord[4][1] = -0.5;
				}
				else if (shape[i].shapecoord[0][0] > 0 && shape[i].shapecoord[0][1] < 0)
				{
					shape[i].shapecoord[0][0] = 0.5;
					shape[i].shapecoord[0][1] = -0.5 + 0.25;
					shape[i].shapecoord[1][0] = 0.5 - 0.25;
					shape[i].shapecoord[1][1] = -0.5;
					shape[i].shapecoord[2][0] = 0.5 - 0.15;
					shape[i].shapecoord[2][1] = -0.5 - 0.25;
					shape[i].shapecoord[3][0] = 0.5 + 0.15;
					shape[i].shapecoord[3][1] = -0.5 - 0.25;
					shape[i].shapecoord[4][0] = 0.5 + 0.25;
					shape[i].shapecoord[4][1] = -0.5;
				}
			}
			break;
		case 'a':
			if (shape[i].shapetype == 1)
			{
				shape[i].shapetype = 2;
				shape[i].done = false;
				if (shape[i].shapecoord[0][0] < 0 && shape[i].shapecoord[0][1] > 0)
				{
					shape[i].shapecoord[0][0] = -0.5;
					shape[i].shapecoord[0][1] = 0.5 + 0.25;
					shape[i].shapecoord[1][0] = -0.5 - 0.25;
					shape[i].shapecoord[1][1] = 0.5 - 0.25;
				}
				else if (shape[i].shapecoord[0][0] > 0 && shape[i].shapecoord[0][1] > 0)
				{
					shape[i].shapecoord[0][0] = 0.5;
					shape[i].shapecoord[0][1] = 0.5 + 0.25;
					shape[i].shapecoord[1][0] = 0.5 - 0.25;
					shape[i].shapecoord[1][1] = 0.5 - 0.25;
				}
				else if (shape[i].shapecoord[0][0] < 0 && shape[i].shapecoord[0][1] < 0)
				{
					shape[i].shapecoord[0][0] = -0.5;
					shape[i].shapecoord[0][1] = -0.5 + 0.25;
					shape[i].shapecoord[1][0] = -0.5 - 0.25;
					shape[i].shapecoord[1][1] = -0.5 - 0.25;
				}
				else if (shape[i].shapecoord[0][0] > 0 && shape[i].shapecoord[0][1] < 0)
				{
					shape[i].shapecoord[0][0] = 0.5;
					shape[i].shapecoord[0][1] = -0.5 + 0.25;
					shape[i].shapecoord[1][0] = 0.5 - 0.25;
					shape[i].shapecoord[1][1] = -0.5 - 0.25;
				}
				shape[i].shapecoord[2][0] = shape[i].shapecoord[1][0];
				shape[i].shapecoord[2][1] = shape[i].shapecoord[1][1];
			}
			else if (shape[i].shapetype == 2)
			{
				shape[i].shapetype = 3;
				shape[i].done = false;
				if (shape[i].shapecoord[0][0] < 0 && shape[i].shapecoord[0][1] > 0)
				{
					shape[i].shapecoord[0][0] = -0.5 - 0.25;
					shape[i].shapecoord[0][1] = 0.5 + 0.25;
					shape[i].shapecoord[1][0] = -0.5 + 0.25;
					shape[i].shapecoord[1][1] = 0.5 + 0.25;
					shape[i].shapecoord[2][0] = -0.5 - 0.25;
					shape[i].shapecoord[2][1] = 0.5 - 0.25;
				}
				else if (shape[i].shapecoord[0][0] > 0 && shape[i].shapecoord[0][1] > 0)
				{
					shape[i].shapecoord[0][0] = 0.5 - 0.25;
					shape[i].shapecoord[0][1] = 0.5 + 0.25;
					shape[i].shapecoord[1][0] = 0.5 + 0.25;
					shape[i].shapecoord[1][1] = 0.5 + 0.25;
					shape[i].shapecoord[2][0] = 0.5 - 0.25;
					shape[i].shapecoord[2][1] = 0.5 - 0.25;
				}
				else if (shape[i].shapecoord[0][0] < 0 && shape[i].shapecoord[0][1] < 0)
				{
					shape[i].shapecoord[0][0] = -0.5 - 0.25;
					shape[i].shapecoord[0][1] = -0.5 + 0.25;
					shape[i].shapecoord[1][0] = -0.5 + 0.25;
					shape[i].shapecoord[1][1] = -0.5 + 0.25;
					shape[i].shapecoord[2][0] = -0.5 - 0.25;
					shape[i].shapecoord[2][1] = -0.5 - 0.25;
				}
				else if (shape[i].shapecoord[0][0] > 0 && shape[i].shapecoord[0][1] < 0)
				{
					shape[i].shapecoord[0][0] = 0.5 - 0.25;
					shape[i].shapecoord[0][1] = -0.5 + 0.25;
					shape[i].shapecoord[1][0] = 0.5 + 0.25;
					shape[i].shapecoord[1][1] = -0.5 + 0.25;
					shape[i].shapecoord[2][0] = 0.5 - 0.25;
					shape[i].shapecoord[2][1] = -0.5 - 0.25;
				}
				shape[i].shapecoord[3][0] = shape[i].shapecoord[2][0];
				shape[i].shapecoord[3][1] = shape[i].shapecoord[2][1];
			}
			else if (shape[i].shapetype == 3)
			{
				shape[i].shapetype = 4;
				shape[i].done = false;
				shape[i].shapetype = 4;
				shape[i].done = false;
				shape[i].Process[0] = false;
				shape[i].Process[1] = false;
				shape[i].Process[2] = false;
				if (shape[i].shapecoord[0][0] < 0 && shape[i].shapecoord[0][1] > 0)
				{
					shape[i].shapecoord[0][0] = -0.5;
					shape[i].shapecoord[0][1] = 0.5;
					shape[i].shapecoord[1][0] = -0.5 - 0.25;
					shape[i].shapecoord[1][1] = 0.5;
					shape[i].shapecoord[2][0] = -0.5 - 0.25;
					shape[i].shapecoord[2][1] = 0.5 - 0.25;
					shape[i].shapecoord[3][0] = -0.5 + 0.25;
					shape[i].shapecoord[3][1] = 0.5 - 0.25;
					shape[i].shapecoord[4][0] = -0.5 + 0.25;
					shape[i].shapecoord[4][1] = 0.5;

				}
				else if (shape[i].shapecoord[0][0] > 0 && shape[i].shapecoord[0][1] > 0)
				{
					shape[i].shapecoord[0][0] = 0.5;
					shape[i].shapecoord[0][1] = 0.5;
					shape[i].shapecoord[1][0] = 0.5 - 0.25;
					shape[i].shapecoord[1][1] = 0.5;
					shape[i].shapecoord[2][0] = 0.5 - 0.25;
					shape[i].shapecoord[2][1] = 0.5 - 0.25;
					shape[i].shapecoord[3][0] = 0.5 + 0.25;
					shape[i].shapecoord[3][1] = 0.5 - 0.25;
					shape[i].shapecoord[4][0] = 0.5 + 0.25;
					shape[i].shapecoord[4][1] = 0.5;
				}
				else if (shape[i].shapecoord[0][0] < 0 && shape[i].shapecoord[0][1] < 0)
				{
					shape[i].shapecoord[0][0] = -0.5;
					shape[i].shapecoord[0][1] = -0.5;
					shape[i].shapecoord[1][0] = -0.5 - 0.25;
					shape[i].shapecoord[1][1] = -0.5;
					shape[i].shapecoord[2][0] = -0.5 - 0.25;
					shape[i].shapecoord[2][1] = -0.5 - 0.25;
					shape[i].shapecoord[3][0] = -0.5 + 0.25;
					shape[i].shapecoord[3][1] = -0.5 - 0.25;
					shape[i].shapecoord[4][0] = -0.5 + 0.25;
					shape[i].shapecoord[4][1] = -0.5;
				}
				else if (shape[i].shapecoord[0][0] > 0 && shape[i].shapecoord[0][1] < 0)
				{
					shape[i].shapecoord[0][0] = 0.5;
					shape[i].shapecoord[0][1] = -0.5;
					shape[i].shapecoord[1][0] = 0.5 - 0.25;
					shape[i].shapecoord[1][1] = -0.5;
					shape[i].shapecoord[2][0] = 0.5 - 0.25;
					shape[i].shapecoord[2][1] = -0.5 - 0.25;
					shape[i].shapecoord[3][0] = 0.5 + 0.25;
					shape[i].shapecoord[3][1] = -0.5 - 0.25;
					shape[i].shapecoord[4][0] = 0.5 + 0.25;
					shape[i].shapecoord[4][1] = -0.5;
				}
			}
			else if (shape[i].shapetype == 4)
			{
				shape[i].shapetype = 5;
				for (int j = 0; j < 6; j++)
				{
					shape[i].Process[j] = false;
				}
				shape[i].done = false;
				if (shape[i].shapecoord[0][0] < 0 && shape[i].shapecoord[0][1] > 0)
				{
					shape[i].shapecoord[0][0] = -0.5;
					shape[i].shapecoord[0][1] = 0.5 + 0.25;
					shape[i].shapecoord[1][0] = -0.5 - 0.25;
					shape[i].shapecoord[1][1] = 0.5;
					shape[i].shapecoord[2][0] = -0.5 - 0.15;
					shape[i].shapecoord[2][1] = 0.5 - 0.25;
					shape[i].shapecoord[3][0] = -0.5 + 0.15;
					shape[i].shapecoord[3][1] = 0.5 - 0.25;
					shape[i].shapecoord[4][0] = -0.5 + 0.25;
					shape[i].shapecoord[4][1] = 0.5;
				}
				else if (shape[i].shapecoord[0][0] > 0 && shape[i].shapecoord[0][1] > 0)
				{
					shape[i].shapecoord[0][0] = 0.5;
					shape[i].shapecoord[0][1] = 0.5 + 0.25;
					shape[i].shapecoord[1][0] = 0.5 - 0.25;
					shape[i].shapecoord[1][1] = 0.5;
					shape[i].shapecoord[2][0] = 0.5 - 0.15;
					shape[i].shapecoord[2][1] = 0.5 - 0.25;
					shape[i].shapecoord[3][0] = 0.5 + 0.15;
					shape[i].shapecoord[3][1] = 0.5 - 0.25;
					shape[i].shapecoord[4][0] = 0.5 + 0.25;
					shape[i].shapecoord[4][1] = 0.5;
				}
				else if (shape[i].shapecoord[0][0] < 0 && shape[i].shapecoord[0][1] < 0)
				{
					shape[i].shapecoord[0][0] = -0.5;
					shape[i].shapecoord[0][1] = -0.5 + 0.25;
					shape[i].shapecoord[1][0] = -0.5 - 0.25;
					shape[i].shapecoord[1][1] = -0.5;
					shape[i].shapecoord[2][0] = -0.5 - 0.15;
					shape[i].shapecoord[2][1] = -0.5 - 0.25;
					shape[i].shapecoord[3][0] = -0.5 + 0.15;
					shape[i].shapecoord[3][1] = -0.5 - 0.25;
					shape[i].shapecoord[4][0] = -0.5 + 0.25;
					shape[i].shapecoord[4][1] = -0.5;
				}
				else if (shape[i].shapecoord[0][0] > 0 && shape[i].shapecoord[0][1] < 0)
				{
					shape[i].shapecoord[0][0] = 0.5;
					shape[i].shapecoord[0][1] = -0.5 + 0.25;
					shape[i].shapecoord[1][0] = 0.5 - 0.25;
					shape[i].shapecoord[1][1] = -0.5;
					shape[i].shapecoord[2][0] = 0.5 - 0.15;
					shape[i].shapecoord[2][1] = -0.5 - 0.25;
					shape[i].shapecoord[3][0] = 0.5 + 0.15;
					shape[i].shapecoord[3][1] = -0.5 - 0.25;
					shape[i].shapecoord[4][0] = 0.5 + 0.25;
					shape[i].shapecoord[4][1] = -0.5;
				}
			}
			break;
		case 'q':
			glutLeaveMainLoop();
			break;
		}
		if (!shape[i].done)
		{
			donecount++;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(10, TimerFunction, 1);
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
	glBufferData(GL_ARRAY_BUFFER, 4 * 15 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	//--- 좌표값을 attribute 인덱스 0번에 명시한다: 버텍스 당 3* float
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//--- attribute 인덱스 0번을 사용가능하게 함
	glEnableVertexAttribArray(0);

	//--- 2번째 VBO를 활성화 하여 바인드 하고, 버텍스 속성 (색상)을 저장
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	//--- 변수 colors에서 버텍스 색상을 복사한다.
	//--- colors 배열의 사이즈: 9 *float
	glBufferData(GL_ARRAY_BUFFER, 4 * 15 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	//--- 색상값을 attribute 인덱스 1번에 명시한다: 버텍스 당 3*float
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//--- attribute 인덱스 1번을 사용 가능하게 함.
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	GLuint indices[4 * 5];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			indices[i * 5 + j] = i * 5 + j;
		}
	}
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);
}

void UpdateBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	for (int i = 0; i < 4; i++)
	{
		glBufferSubData(GL_ARRAY_BUFFER, i * 15 * sizeof(GLfloat), 15 * sizeof(GLfloat), shape[i].shapecoord);
	}
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	for (int i = 0; i < 4; i++)
	{
		glBufferSubData(GL_ARRAY_BUFFER, i * 15 * sizeof(GLfloat), 15 * sizeof(GLfloat), shape[i].color);
	}
}

GLvoid TimerFunction(int value)
{
	if (!shape[0].done && shape[0].shapetype == 2)
	{
		if (shape[0].shapecoord[2][0] > -0.25)
		{
			shape[0].done = true;
		}
		else
		{
			shape[0].shapecoord[2][0] += 0.01;
		}
	}
	if (!shape[1].done && shape[1].shapetype == 2)
	{
		if (shape[1].shapecoord[2][0] > 0.75)
		{
			shape[1].done = true;
		}
		else
		{
			shape[1].shapecoord[2][0] += 0.01;
		}
	}
	if (!shape[2].done && shape[2].shapetype == 2)
	{
		if (shape[2].shapecoord[2][0] > -0.25)
		{
			shape[2].done = true;
		}
		else
		{
			shape[2].shapecoord[2][0] += 0.01;
		}
	}
	if (!shape[3].done && shape[3].shapetype == 2)
	{
		if (shape[3].shapecoord[2][0] > 0.75)
		{
			shape[3].done = true;
		}
		else
		{
			shape[3].shapecoord[2][0] += 0.01;
		}
	}
	if (!shape[0].done && shape[0].shapetype == 3)
	{
		if (shape[0].shapecoord[3][0] > -0.25)
		{
			shape[0].done = true;
		}
		else
		{
			shape[0].shapecoord[3][0] += 0.01;
		}
	}
	if (!shape[1].done && shape[1].shapetype == 3)
	{
		if (shape[1].shapecoord[3][0] > 0.75)
		{
			shape[1].done = true;
		}
		else
		{
			shape[1].shapecoord[3][0] += 0.01;
		}
	}
	if (!shape[2].done && shape[2].shapetype == 3)
	{
		if (shape[2].shapecoord[3][0] > -0.25)
		{
			shape[2].done = true;
		}
		else
		{
			shape[2].shapecoord[3][0] += 0.01;
		}
	}
	if (!shape[3].done && shape[3].shapetype == 3)
	{
		if (shape[3].shapecoord[3][0] > 0.75)
		{
			shape[3].done = true;
		}
		else
		{
			shape[3].shapecoord[3][0] += 0.01;
		}
	}
	if (!shape[0].done && shape[0].shapetype == 4)
	{
		if (shape[0].shapecoord[2][0] > -0.5 - 0.15)
		{
			shape[0].Process[0] = true;
		}
		else
		{
			shape[0].shapecoord[2][0] += 0.01;
		}

		if (shape[0].shapecoord[3][0] < -0.5 + 0.15)
		{
			shape[0].Process[1] = true;
		}
		else
		{
			shape[0].shapecoord[3][0] -= 0.01;
		}

		if (shape[0].shapecoord[0][1] > 0.5 + 0.25)
		{
			shape[0].Process[2] = true;
		}
		else
		{
			shape[0].shapecoord[0][1] += 0.01;
		}

		if (shape[0].Process[0] && shape[0].Process[1] && shape[0].Process[2])
		{
			shape[0].done = true;
		}
	}
	if (!shape[1].done && shape[1].shapetype == 4)
	{
		if (shape[1].shapecoord[2][0] > 0.5 - 0.15)
		{
			shape[1].Process[0] = true;
		}
		else
		{
			shape[1].shapecoord[2][0] += 0.01;
		}

		if (shape[1].shapecoord[3][0] < 0.5 + 0.15)
		{
			shape[1].Process[1] = true;
		}
		else
		{
			shape[1].shapecoord[3][0] -= 0.01;
		}

		if (shape[1].shapecoord[0][1] > 0.5 + 0.25)
		{
			shape[1].Process[2] = true;
		}
		else
		{
			shape[1].shapecoord[0][1] += 0.01;
		}

		if (shape[1].Process[0] && shape[1].Process[1] && shape[1].Process[2])
		{
			shape[1].done = true;
		}
	}
	if (!shape[2].done && shape[2].shapetype == 4)
	{
		if (shape[2].shapecoord[2][0] > -0.5 - 0.15)
		{
			shape[2].Process[0] = true;
		}
		else
		{
			shape[2].shapecoord[2][0] += 0.01;
		}

		if (shape[2].shapecoord[3][0] < -0.5 + 0.15)
		{
			shape[2].Process[1] = true;
		}
		else
		{
			shape[2].shapecoord[3][0] -= 0.01;
		}

		if (shape[2].shapecoord[0][1] > -0.5 + 0.25)
		{
			shape[2].Process[2] = true;
		}
		else
		{
			shape[2].shapecoord[0][1] += 0.01;
		}

		if (shape[2].Process[0] && shape[2].Process[1] && shape[2].Process[2])
		{
			shape[2].done = true;
		}
	}
	if (!shape[3].done && shape[3].shapetype == 4)
	{
		if (shape[3].shapecoord[2][0] > 0.5 - 0.15)
		{
			shape[3].Process[0] = true;
		}
		else
		{
			shape[3].shapecoord[2][0] += 0.01;
		}

		if (shape[3].shapecoord[3][0] < 0.5 + 0.15)
		{
			shape[3].Process[1] = true;
		}
		else
		{
			shape[3].shapecoord[3][0] -= 0.01;
		}

		if (shape[3].shapecoord[0][1] > -0.5 + 0.25)
		{
			shape[3].Process[2] = true;
		}
		else
		{
			shape[3].shapecoord[0][1] += 0.01;
		}

		if (shape[3].Process[0] && shape[3].Process[1] && shape[3].Process[2])
		{
			shape[3].done = true;
		}
	}

	if (!shape[0].done && shape[0].shapetype == 5)
	{
		if (shape[0].shapecoord[1][0] > shape[0].shapecoord[2][0])
		{
			shape[0].Process[0] = true;
		}
		else
		{
			shape[0].shapecoord[2][0] -= 0.01;
		}
		if (shape[0].shapecoord[1][1] < shape[0].shapecoord[2][1])
		{
			shape[0].Process[1] = true;
		}
		else
		{
			shape[0].shapecoord[2][1] += 0.01;
		}

		if (shape[0].shapecoord[0][0] > shape[0].shapecoord[4][0])
		{
			shape[0].Process[2] = true;
		}
		else
		{
			shape[0].shapecoord[4][0] -= 0.01;
		}
		if (shape[0].shapecoord[0][1] < shape[0].shapecoord[4][1])
		{
			shape[0].Process[3] = true;
		}
		else
		{
			shape[0].shapecoord[4][1] += 0.01;
		}

		if (shape[0].shapecoord[0][0] > shape[0].shapecoord[3][0])
		{
			shape[0].Process[4] = true;
		}
		else
		{
			shape[0].shapecoord[3][0] -= 0.01;
		}
		if (shape[0].shapecoord[0][1] < shape[0].shapecoord[3][1])
		{
			shape[0].Process[5] = true;
		}
		else
		{
			shape[0].shapecoord[3][1] += 0.01;
		}

		if (shape[0].Process[0] && shape[0].Process[1] && shape[0].Process[2] && shape[0].Process[3] && shape[0].Process[4] && shape[0].Process[5])
		{
			shape[0].shapetype = 1;
			shape[0].done = true;
		}
	}

	if (!shape[1].done && shape[1].shapetype == 5)
	{
		if (shape[1].shapecoord[1][0] > shape[1].shapecoord[2][0])
		{
			shape[1].Process[0] = true;
		}
		else
		{
			shape[1].shapecoord[2][0] -= 0.01;
		}
		if (shape[1].shapecoord[1][1] < shape[1].shapecoord[2][1])
		{
			shape[1].Process[1] = true;
		}
		else
		{
			shape[1].shapecoord[2][1] += 0.01;
		}

		if (shape[1].shapecoord[0][0] > shape[1].shapecoord[4][0])
		{
			shape[1].Process[2] = true;
		}
		else
		{
			shape[1].shapecoord[4][0] -= 0.01;
		}
		if (shape[1].shapecoord[0][1] < shape[1].shapecoord[4][1])
		{
			shape[1].Process[3] = true;
		}
		else
		{
			shape[1].shapecoord[4][1] += 0.01;
		}

		if (shape[1].shapecoord[0][0] > shape[1].shapecoord[3][0])
		{
			shape[1].Process[4] = true;
		}
		else
		{
			shape[1].shapecoord[3][0] -= 0.01;
		}
		if (shape[1].shapecoord[0][1] < shape[1].shapecoord[3][1])
		{
			shape[1].Process[5] = true;
		}
		else
		{
			shape[1].shapecoord[3][1] += 0.01;
		}

		if (shape[1].Process[0] && shape[1].Process[1] && shape[1].Process[2] && shape[1].Process[3] && shape[1].Process[4] && shape[1].Process[5])
		{
			shape[1].shapetype = 1;
			shape[1].done = true;
		}
	}

	if (!shape[2].done && shape[2].shapetype == 5)
	{
		if (shape[2].shapecoord[1][0] > shape[2].shapecoord[2][0])
		{
			shape[2].Process[0] = true;
		}
		else
		{
			shape[2].shapecoord[2][0] -= 0.01;
		}
		if (shape[2].shapecoord[1][1] < shape[2].shapecoord[2][1])
		{
			shape[2].Process[1] = true;
		}
		else
		{
			shape[2].shapecoord[2][1] += 0.01;
		}

		if (shape[2].shapecoord[0][0] > shape[2].shapecoord[4][0])
		{
			shape[2].Process[2] = true;
		}
		else
		{
			shape[2].shapecoord[4][0] -= 0.01;
		}
		if (shape[2].shapecoord[0][1] < shape[2].shapecoord[4][1])
		{
			shape[2].Process[3] = true;
		}
		else
		{
			shape[2].shapecoord[4][1] += 0.01;
		}

		if (shape[2].shapecoord[0][0] > shape[2].shapecoord[3][0])
		{
			shape[2].Process[4] = true;
		}
		else
		{
			shape[2].shapecoord[3][0] -= 0.01;
		}
		if (shape[2].shapecoord[0][1] < shape[2].shapecoord[3][1])
		{
			shape[2].Process[5] = true;
		}
		else
		{
			shape[2].shapecoord[3][1] += 0.01;
		}

		if (shape[2].Process[0] && shape[2].Process[1] && shape[2].Process[2] && shape[2].Process[3] && shape[2].Process[4] && shape[2].Process[5])
		{
			shape[2].shapetype = 1;
			shape[2].done = true;
		}
	}

	if (!shape[3].done && shape[3].shapetype == 5)
	{
		if (shape[3].shapecoord[1][0] > shape[3].shapecoord[2][0])
		{
			shape[3].Process[0] = true;
		}
		else
		{
			shape[3].shapecoord[2][0] -= 0.01;
		}
		if (shape[3].shapecoord[1][1] < shape[3].shapecoord[2][1])
		{
			shape[3].Process[1] = true;
		}
		else
		{
			shape[3].shapecoord[2][1] += 0.01;
		}

		if (shape[3].shapecoord[0][0] > shape[3].shapecoord[4][0])
		{
			shape[3].Process[2] = true;
		}
		else
		{
			shape[3].shapecoord[4][0] -= 0.01;
		}
		if (shape[3].shapecoord[0][1] < shape[3].shapecoord[4][1])
		{
			shape[3].Process[3] = true;
		}
		else
		{
			shape[3].shapecoord[4][1] += 0.01;
		}

		if (shape[3].shapecoord[0][0] > shape[3].shapecoord[3][0])
		{
			shape[3].Process[4] = true;
		}
		else
		{
			shape[3].shapecoord[3][0] -= 0.01;
		}
		if (shape[3].shapecoord[0][1] < shape[3].shapecoord[3][1])
		{
			shape[3].Process[5] = true;
		}
		else
		{
			shape[3].shapecoord[3][1] += 0.01;
		}

		if (shape[3].Process[0] && shape[3].Process[1] && shape[3].Process[2] && shape[3].Process[3] && shape[3].Process[4] && shape[3].Process[5])
		{
			shape[3].shapetype = 1;
			shape[3].done = true;
		}
	}
	glutPostRedisplay();
	if(!shape[0].done || !shape[1].done || !shape[2].done || !shape[3].done)
		glutTimerFunc(10, TimerFunction, 1);
}