#include "GLmain.h"

glm::vec3 rotatin(30.0f, -30.0f, -30.0f);

bool Surface = false;
bool Projection = false;
bool YRot = false;
bool hexa = false, pyramid = false, hexaCeiling = false, hexaFrontUp = false, hexaSideUp = false, hexaBackUp = false, pyramidAll1 = false, pyramidAll2 = false, pyramidOne = false, so = false;
int theta = 0;
float num = 0;

GLvoid drawScene()
{
	glEnable(GL_DEPTH_TEST);
	glUseProgram(shaderProgramID);

	// Draw axes
	GLuint modelTransformLoc = glGetUniformLocation(shaderProgramID, "model");
	GLuint projectionTransformLoc = glGetUniformLocation(shaderProgramID, "projection");
	// Surface 설정
	if (Surface)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);

	glm::mat4 pTransform = glm::mat4(1.0f);
	if (!Projection)
		pTransform = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 50.0f);
	else
		pTransform = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, 0.1f, 50.0f);
	glUniformMatrix4fv(projectionTransformLoc, 1, GL_FALSE, &pTransform[0][0]);

	unsigned int objColorLocation = glGetUniformLocation(shaderProgramID, "objectColor");
	// Draw axes
	glBindVertexArray(axesVAO);
	glm::mat4 axesTransform = glm::mat4(1.0f);
	axesTransform = glm::rotate(axesTransform, glm::radians(rotatin.x), glm::vec3(1.0f, 0.0f, 0.0f));
	axesTransform = glm::rotate(axesTransform, glm::radians(rotatin.y), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(modelTransformLoc, 1, GL_FALSE, &axesTransform[0][0]);
	glUniform3f(objColorLocation, 1.0f, 1.0f, 1.0f); // 축은 흰색으로 설정
	glDrawArrays(GL_LINES, 0, 6);

	glBindVertexArray(vao);
	for (int i = 0; i < 11; i++)
	{
		if (shape[i].ShapeState)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::scale(model, shape[i].scale);
			model = glm::translate(model, shape[i].position);
			model = glm::rotate(model, glm::radians(shape[i].rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, glm::radians(shape[i].rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, glm::radians(shape[i].rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelTransformLoc, 1, GL_FALSE, &model[0][0]);

			glUniform3f(objColorLocation, shape[i].colors[0], shape[i].colors[1], shape[i].colors[2]);
			UpdateBuffer(shape[i]);

			glDrawElements(GL_TRIANGLES, shape[i].faces.size(), GL_UNSIGNED_INT, shape[i].faces.data());
		}
	}
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'h': case 'H':
		Surface = !Surface;
		break;
	case 'y': case 'Y':
		YRot = !YRot;
		break;
	case 't': case 'T':
		hexa = true;
		pyramid = false;
		hexaCeiling = !hexaCeiling;
		break;
	case 'f': case 'F':
		hexa = true;
		pyramid = false;
		hexaFrontUp = !hexaFrontUp;
		break;
	case 's': case 'S':
		hexa = true;
		pyramid = false;
		hexaSideUp = !hexaSideUp;
		break;
	case 'b': case 'B':
		hexa = true;
		pyramid = false;
		hexaBackUp = !hexaBackUp;
		break;
	case 'o': case 'O':
		pyramid = true;
		hexa = false;
		if (theta < 180)
		{
			pyramidAll1 = true;
		}
		else
		{
			pyramidAll2 = true;
		}
		break;
	case 'r': case 'R':
		pyramid = true;
		hexa = false;
		pyramidOne = true;
		break;
	case 'p': case 'P':
		break;
	case 'q': case 'Q':
		glutLeaveMainLoop();
		break;
	}

	for (int i = 0; i < 11; i++)
	{
		if (pyramid)
		{
			if (i > 5)
			{
				shape[i].ShapeState = true;
			}
			else
			{
				shape[i].ShapeState = false;
			}
		}
		else if (hexa)
		{
			if (i < 6)
			{
				shape[i].ShapeState = true;
			}
			else
			{
				shape[i].ShapeState = false;
			}
		}
	}
	glutPostRedisplay();
}

void InitBuffer()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(2, vbo);

	if (model)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);
	}
	else
	{
		// Vertex position buffer
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * 11, NULL, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		//normal
		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * 11, NULL, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);
	}

	glUseProgram(shaderProgramID);
	unsigned int lightPosLocation = glGetUniformLocation(shaderProgramID, "lightPos"); //--- lightPos 값 전달: (0.0, 0.0, 5.0);
	glUniform3f(lightPosLocation, 0.0, 0.0, 5.0);
	unsigned int lightColorLocation = glGetUniformLocation(shaderProgramID, "lightColor"); //--- lightColor 값 전달: (1.0, 1.0, 1.0) 백색
	glUniform3f(lightColorLocation, 1.0, 1.0, 1.0);

	// Initialize axes VAO and VBO (implement drawAxes() function separately)
	drawAxes();
}

void UpdateBuffer(const Shape& shape)
{
	if (shape.model)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, shape.vertices.size() * sizeof(glm::vec3), shape.vertices.data(), GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, shape.normal.size() * sizeof(glm::vec3), shape.normal.data(), GL_DYNAMIC_DRAW);
	}
	else
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, shape.vertices.size() * sizeof(glm::vec3), shape.vertices.data());

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, shape.colors.size() * sizeof(glm::vec3), shape.normal.data());
	}
}

GLvoid TimerFunction(int value)
{
	if (YRot)
	{
		for (int i = 0; i < 11; i++)
		{
			shape[i].rotation.y -= 1;
			if (shape[i].rotation.y < -360)
			{
				shape[i].rotation.y = 0;
			}
		}
	}
	if (hexaCeiling)
	{
		shape[4].vertices[0] = glm::vec3(-0.5 * cos(shape[4].theta), 0.5 + num, -0.5 * sin(shape[4].theta));
		shape[4].vertices[1] = glm::vec3(0.5 * cos(shape[4].theta), 0.5 + num, -0.5 * sin(shape[4].theta));
		shape[4].vertices[2] = glm::vec3(0.5 * cos(shape[4].theta), 0.5 - num, 0.5 * sin(shape[4].theta));
		shape[4].vertices[3] = glm::vec3(-0.5 * cos(shape[4].theta), 0.5 - num, 0.5 * sin(shape[4].theta));
		shape[4].theta += 10;
		if (!so)
		{
			num += 0.0277f;
		}
		else
		{
			num -= 0.0277f;
		}
		if (shape[4].theta >= 180 && shape[4].theta < 360)
		{
			so = true;
		}
		if (shape[4].theta >= 360)
		{
			so = false;
			num = 0;
			shape[4].theta = 0;
		}
	}
	if (hexaFrontUp)
	{
		if (!shape[0].Front)
		{
			shape[0].position.y += 0.01;
		}
		else
		{
			shape[0].position.y -= 0.01;
		}

		if (shape[0].position.y > 1.0)
		{
			shape[0].Front = true;
		}
		else if (shape[0].position.y < 0)
		{
			shape[0].Front = false;
		}
	}
	if (hexaSideUp)
	{
		if (!shape[2].Front)
		{
			shape[2].position.y += 0.01;
		}
		else
		{
			shape[2].position.y -= 0.01;
		}

		if (shape[2].position.y > 1.0)
		{
			shape[2].Front = true;
		}
		else if (shape[2].position.y < 0)
		{
			shape[2].Front = false;
		}

		if (!shape[3].Front)
		{
			shape[3].position.y += 0.01;
		}
		else
		{
			shape[3].position.y -= 0.01;
		}

		if (shape[3].position.y > 1.0)
		{
			shape[3].Front = true;
		}
		else if (shape[3].position.y < 0)
		{
			shape[3].Front = false;
		}
	}
	if (hexaBackUp)
	{
		if (!shape[1].Front)
		{
			shape[1].position.y += 0.01;
		}
		else
		{
			shape[1].position.y -= 0.01;
		}

		if (shape[1].position.y > 1.0)
		{
			shape[1].Front = true;
		}
		else if (shape[1].position.y < 0)
		{
			shape[1].Front = false;
		}
	}
	if (pyramidAll1)
	{
		shape[6].vertices[0] = glm::vec3(0, 1.0 * cos(theta), 0);
		shape[7].vertices[0] = glm::vec3(0, 1.0 * cos(theta), 0);
		shape[8].vertices[0] = glm::vec3(0, 1.0 * cos(theta), 0);
		shape[9].vertices[0] = glm::vec3(0, 1.0 * cos(theta), 0);
		theta += 2;
		if (theta > 180)
		{
			theta = 180;
			pyramidAll1 = false;
		}
	}
	else if (pyramidAll2)
	{
		shape[6].vertices[0] = glm::vec3(0, 1.0 * cos(theta), 0);
		shape[7].vertices[0] = glm::vec3(0, 1.0 * cos(theta), 0);
		shape[8].vertices[0] = glm::vec3(0, 1.0 * cos(theta), 0);
		shape[9].vertices[0] = glm::vec3(0, 1.0 * cos(theta), 0);
		theta -= 2;
		if (theta < 0)
		{
			theta = 0;
			pyramidAll2 = false;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(30, TimerFunction, 1);
}