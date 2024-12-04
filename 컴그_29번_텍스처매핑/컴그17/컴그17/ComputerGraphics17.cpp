#include "GLmain.h"

glm::vec3 rotatin(30.0f, -30.0f, -30.0f);

bool Surface = false;
bool Projection = false;
bool YRot = false, XRot = false;
bool hexa = false, pyramid = false, hexaCeiling = false, hexaFrontUp = false, hexaSideUp = false, hexaBackUp = false, pyramidAll1 = false, pyramidAll2 = false, pyramidOne = false, so = false;
int theta = 0;
float num = 0;
unsigned int texture[4];

void InitTexture()
{
	int widthImage, heightImage, numberOfChannel;
	glGenTextures(4, texture);

	//stbi_set_flip_vertically_on_load(true);
	//--- texture[0]

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data1 = stbi_load("sky.bmp", &widthImage, &heightImage, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);

	//--- texture[1]
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data2 = stbi_load("sea.bmp", &widthImage, &heightImage, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);

	//--- texture[2]
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data3 = stbi_load("forest.bmp", &widthImage, &heightImage, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, data3);

	//--- texture[3]
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data4 = stbi_load("snow.bmp", &widthImage, &heightImage, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, data4);
}

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

			if (shape[i].shapetype == 0)
			{
				glBindTexture(GL_TEXTURE_2D, texture[0]);
			}
			else if (shape[i].shapetype == 1)
			{
				glBindTexture(GL_TEXTURE_2D, texture[1]);
			}
			else if (shape[i].shapetype == 2)
			{
				glBindTexture(GL_TEXTURE_2D, texture[2]);
			}
			else if (shape[i].shapetype == 3)
			{
				glBindTexture(GL_TEXTURE_2D, texture[3]);
			}
			glDrawElements(GL_TRIANGLES, shape[i].faces.size(), GL_UNSIGNED_INT, shape[i].faces.data());
		}
	}
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'c':
		hexa = true;
		pyramid = false;
		break;
	case 'p':
		hexa = false;
		pyramid = true;
		break;
	case 'x': case 'X':
		XRot = !XRot;
		break;
	case 'y': case 'Y':
		YRot = !YRot;
		break;
	case 's':
		XRot = false;
		YRot = false;
		for (int i = 0; i < 11; i++)
		{
			shape[i].rotation = glm::vec3(30.0f, -30.0f, 0.0f);
		}
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
	glGenBuffers(3, vbo);

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

		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 11, NULL, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(2);
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

		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, shape.texcoords.size() * sizeof(glm::vec2), shape.texcoords.data());
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
	if (XRot)
	{
		for (int i = 0; i < 11; i++)
		{
			shape[i].rotation.x += 1;
			if (shape[i].rotation.x > 360)
			{
				shape[i].rotation.x = 0;
			}
		}
	}
	glutPostRedisplay();
	glutTimerFunc(30, TimerFunction, 1);
}