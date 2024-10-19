#include "GLmain.h"

bool XPRot = false, XMRot = false, YPRot = false, YMRot = false, Orbit1 = false, Orbit2 = false, starts = false, done = false, swap = false;
float r = 0.0f;
int theta = 0, theta2 = 0;

#define PI 3.14

glm::vec3 rotatin(30.0f, 30.0f, 30.0f);

GLvoid drawScene()
{
	glClearColor(bGCr, bGCg, bGCb, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glUseProgram(shaderProgramID);

	// Draw axes
	glBindVertexArray(axesVAO);
	glm::mat4 axesTransform = glm::mat4(1.0f);
	GLuint transformLoc = glGetUniformLocation(shaderProgramID, "modelTransform");
	axesTransform = glm::rotate(axesTransform, glm::radians(rotatin.x), glm::vec3(1.0f, 0.0f, 0.0f));
	axesTransform = glm::rotate(axesTransform, glm::radians(rotatin.y), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(axesTransform));
	glDrawArrays(GL_LINES, 0, 6);

	glBindVertexArray(vao);
	for (int i = 0; i < 2; i++)
	{
		if (shape[i].ShapeState)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, shape[i].position);
			model = glm::rotate(model, glm::radians(shape[i].rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, glm::radians(shape[i].rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, glm::radians(shape[i].rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, shape[i].scale);
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));

			UpdateBuffer(shape[i]);

			glDrawElements(GL_POLYGON, shape[i].faces.size(), GL_UNSIGNED_INT, shape[i].faces.data());
		}
	}
	glutSwapBuffers();
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	done = false;
	switch (key)
	{
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
	case 'r':
		Orbit1 = true;
		Orbit2 = false;
		break;
	case 'R':
		Orbit1 = false;
		Orbit2 = true;
		break;
	case 'c':
		for (int i = 0; i < 2; i++)
		{
			shape[i].shapetype = random3(gen);
			if (shape[i].shapetype == 0)
			{
				shape[i].loadFromObjFile("Sphere.obj.txt");
			}
			else if (shape[i].shapetype == 1)
			{
				shape[i].loadFromObjFile("Cone.obj.txt");
			}
			else if (shape[i].shapetype == 2)
			{
				shape[i].loadFromObjFile("Cube.obj.txt");
			}
		}
		break;
	case 's':
		for (int i = 0; i < 2; i++)
		{
			shape[i].position = glm::vec3(0.5f, 0.0f, 0.0f);
			shape[i].rotation = glm::vec3(30.0f, 30.0f, 0.0f);
			shape[i].scale = glm::vec3(0.2f, 0.2f, 0.2f);
			shape[i].XPRot = false;
			shape[i].XMRot = false;
			shape[i].YPRot = false;
			shape[i].YMRot = false;
		}
		shape[1].position = glm::vec3(-0.5f, 0.0f, 0.0f);
		XPRot = false;
		YPRot = false;
		XMRot = false;
		YMRot = false;
		starts = false;
		Orbit1 = false;
		Orbit2 = false;
		done = true;
		swap = false;
		break;
	case '1':
		if (XPRot)
		{
			shape[0].XPRot = true;
			shape[0].XMRot = false;
		}
		else if (XMRot)
		{
			shape[0].XPRot = false;
			shape[0].XMRot = true;
		}
		if (YPRot)
		{
			shape[0].YPRot = true;
			shape[0].YMRot = false;
		}
		else if (YMRot)
		{
			shape[0].YPRot = false;
			shape[0].YMRot = true;
		}
		break;
	case '2':
		if (XPRot)
		{
			shape[1].XPRot = true;
			shape[1].XMRot = false;
		}
		else if (XMRot)
		{
			shape[1].XPRot = false;
			shape[1].XMRot = true;
		}
		if (YPRot)
		{
			shape[1].YPRot = true;
			shape[1].YMRot = false;
		}
		else if (YMRot)
		{
			shape[1].YPRot = false;
			shape[1].YMRot = true;
		}
		break;
	case '3':
		if (XPRot)
		{
			shape[0].XPRot = true;
			shape[0].XMRot = false;
			shape[1].XPRot = true;
			shape[1].XMRot = false;
		}
		else if (XMRot)
		{
			shape[0].XPRot = false;
			shape[0].XMRot = true;
			shape[1].XPRot = false;
			shape[1].XMRot = true;
		}
		if (YPRot)
		{
			shape[0].YPRot = true;
			shape[0].YMRot = false;
			shape[1].YPRot = true;
			shape[1].YMRot = false;
		}
		else if (YMRot)
		{
			shape[0].YPRot = false;
			shape[0].YMRot = true;
			shape[1].YPRot = false;
			shape[1].YMRot = true;
		}
		break;

	case '4': // 여기서부터 16번
		break;
	case '5':
		swap = true;
		break;
	case '6':
		break;
	case '7':
		break;
	case '8':
		break;

	case 'q':
		glutLeaveMainLoop();
		break;
	}
	glutPostRedisplay();
	if (XPRot || XMRot || YPRot || YMRot || Orbit1 || Orbit2 || swap)
	{
		if (!starts && !done)
		{
			glutTimerFunc(60, TimerFunction, 1);
			starts = true;
		}
	}
}

void InitBuffer()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(2, vbo);

	// Vertex position buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	// Color buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	// Initialize axes VAO and VBO (implement drawAxes() function separately)
	drawAxes();
}

void UpdateBuffer(const Shape& shape)
{
	// Update vertex position buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, shape.vertices.size() * sizeof(glm::vec3), shape.vertices.data(), GL_DYNAMIC_DRAW);

	// Update color buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, shape.colors.size() * sizeof(glm::vec3), shape.colors.data(), GL_DYNAMIC_DRAW);
}

GLvoid TimerFunction(int value)
{
	for (int i = 0; i < 2; i++)
	{
		if (shape[i].XPRot)
		{
			shape[i].rotation.x += 5;
		}
		else if (shape[i].XMRot)
		{
			shape[i].rotation.x -= 5;
		}
		if (shape[i].rotation.x < 0)
		{
			shape[i].rotation.x = 360.0;
		}
		else if (shape[i].rotation.x > 360)
		{
			shape[i].rotation.x = 0;
		}

		if (shape[i].YPRot)
		{
			shape[i].rotation.y += 5;
		}
		else if (shape[i].YMRot)
		{
			shape[i].rotation.y -= 5;
		}
		if (shape[i].rotation.y > 0)
		{
			shape[i].rotation.y = -360.0;
		}
		else if (shape[i].rotation.y < -360)
		{
			shape[i].rotation.y = 0;
		}
	}

	if (Orbit1)
	{
		shape[0].position.x = 0.5f * cos(theta * PI / 180);
		shape[0].position.y = 0.5f * sin(theta * PI / 180);
		shape[1].position.x = -0.5f * cos(theta * PI / 180);
		shape[1].position.y = -0.5f * sin(theta * PI / 180);
		theta += 2;
	}
	else if (Orbit2)
	{
		shape[0].position.x = 0.5f * cos(theta * PI / 180);
		shape[0].position.y = 0.5f * sin(theta * PI / 180);
		shape[1].position.x = -0.5f * cos(theta * PI / 180);
		shape[1].position.y = -0.5f * sin(theta * PI / 180);
		theta -= 2;
	}
	if (theta > 360)
	{
		theta = 0;
	}
	else if (theta < 0)
	{
		theta = 360;
	}

	if (swap)
	{
		if (!shape[0].Swap)
		{
			shape[0].position.x -= 0.01;
		}
		else
		{
			shape[0].position.x += 0.01;
		}
		if (!shape[1].Swap)
		{
			shape[1].position.x += 0.01;
		}
		else
		{
			shape[1].position.x -= 0.01;
		}

		if (shape[0].position.x < -0.5)
		{
			shape[0].Swap = true;
		}
		else if (shape[0].position.x > 0.5)
		{
			shape[0].Swap = false;
		}
		if (shape[1].position.x > 0.5)
		{
			shape[1].Swap = true;
		}
		else if (shape[1].position.x < -0.5)
		{
			shape[1].Swap = false;
		}
	}
	glutPostRedisplay();
	if (starts)
	{
		glutTimerFunc(10, TimerFunction, 1);
	}
}