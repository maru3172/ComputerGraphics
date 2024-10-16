#include "GLmain.h"

GLvoid drawScene()
{
	glClearColor(bGCr, bGCg, bGCb, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shaderProgramID);

	glBindVertexArray(axesVAO);
	glm::mat4 axesTransform = glm::mat4(1.0f);
	GLuint Loc = glGetUniformLocation(shaderProgramID, "transform");
	glUniformMatrix4fv(Loc, 1, GL_FALSE, glm::value_ptr(axesTransform));
	glDrawArrays(GL_LINES, 0, 4);

	glBindVertexArray(vao);
	for (int i = 0; i < 10; i++)
	{
		if (shape[i].ShapeState)
		{
			if (shape[i].shapetype == 1)
			{
				glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(i * 4 * sizeof(GLuint)));
			}
			else if (shape[i].shapetype == 2)
			{
				glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, (void*)(i * 4 * sizeof(GLuint)));
			}
		}
	}
	glutSwapBuffers();
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	for (int i = 0; i < 10; i++)
	{
		shape[i].ShapeState = false;
	}
	switch (key)
	{
	case '1':
		shape[0].ShapeState = true;
		break;
	case '2':
		shape[1].ShapeState = true;
		break;
	case '3':
		shape[2].ShapeState = true;
		break;
	case '4':
		shape[3].ShapeState = true;
		break;
	case '5':
		shape[4].ShapeState = true;
		break;
	case '6':
		shape[5].ShapeState = true;
		break;
	case '7':
		shape[6].ShapeState = true;
		break;
	case '8':
		shape[7].ShapeState = true;
		break;
	case '9':
		shape[8].ShapeState = true;
		break;
	case '0':
		shape[9].ShapeState = true;
		break;
	case 'c':
		for (int i = 0; i < 2; i++)
		{
			shape[random1(gen)].ShapeState = true;
		}
		break;
	case 't':
		for (int i = 0; i < 2; i++)
		{
			shape[random2(gen)].ShapeState = true;
		}
		break;
	case 'q':
		glutLeaveMainLoop();
		break;
	}
	glutPostRedisplay();
}

void InitBuffer()
{
	glGenVertexArrays(1, &vao); //--- VAO �� �����ϰ� �Ҵ��ϱ�
	glBindVertexArray(vao); //--- VAO�� ���ε��ϱ�

	glGenBuffers(2, vbo); //--- 2���� VBO�� �����ϰ� �Ҵ��ϱ�
	//--- 1��° VBO�� Ȱ��ȭ�Ͽ� ���ε��ϰ�, ���ؽ� �Ӽ� (��ǥ��)�� ����
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	//--- ���� diamond ���� ���ؽ� ������ ���� ���ۿ� �����Ѵ�.
	//--- triShape �迭�� ������: 9 * float
	glBufferData(GL_ARRAY_BUFFER, 10 * 4 * 3 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	//--- ��ǥ���� attribute �ε��� 0���� ����Ѵ�: ���ؽ� �� 3* float
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//--- attribute �ε��� 0���� ��밡���ϰ� ��
	glEnableVertexAttribArray(0);

	//--- 2��° VBO�� Ȱ��ȭ �Ͽ� ���ε� �ϰ�, ���ؽ� �Ӽ� (����)�� ����
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	//--- ���� colors���� ���ؽ� ������ �����Ѵ�.
	//--- colors �迭�� ������: 9 *float
	glBufferData(GL_ARRAY_BUFFER, 10 * 4 * 3 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	//--- ������ attribute �ε��� 1���� ����Ѵ�: ���ؽ� �� 3*float
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//--- attribute �ε��� 1���� ��� �����ϰ� ��.
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	GLuint indices[10 * 4];
	for (int i = 0; i < 10 * 4; i++)
	{
		indices[i] = i % 4;
	}
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

	for (int i = 0; i < 10; i++)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferSubData(GL_ARRAY_BUFFER, i * 4 * 3 * sizeof(GLfloat), 4 * 3 * sizeof(GLfloat), glm::value_ptr(shape[i].vertices[0]));

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferSubData(GL_ARRAY_BUFFER, i * 4 * 3 * sizeof(GLfloat), 4 * 3 * sizeof(GLfloat), glm::value_ptr(shape[i].colors[0]));
	}
	drawAxes();
}