#include "GLmain.h"

bool XPRot = false, XMRot = false, YPRot = false, YMRot = false, Orbit1 = false, Orbit2 = false, starts = false, done = false, swap = false, Scale = false, SwapCircle = false, done2 = false, mi = false, SwapUnD = false, Spiral = false;
float r = 0.0f;
int theta = 0;
float disThetas = 2.0f * M_PI / 200.0f, disRadian = 1.0f / 600.0f;

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
	axesTransform = glm::rotate(axesTransform, glm::radians(rotatin.z), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(axesTransform));
	glDrawArrays(GL_LINES, 0, 6);

	if (Spiral)
	{
		glBindVertexArray(spiralVAO);
		glm::mat4 spiralTransform = glm::mat4(1.0f);
		spiralTransform = glm::rotate(spiralTransform, glm::radians(rotatin.x), glm::vec3(1.0f, 0.0f, 0.0f));
		spiralTransform = glm::rotate(spiralTransform, glm::radians(rotatin.z), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(spiralTransform));
		glDrawArrays(GL_LINE_STRIP, 0, 600);
	}

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
			shape[i].position = glm::vec3(0.5f, 0.5f, 0.5f);
			shape[i].rotation = glm::vec3(30.0f, -30.0f, 0.0f);
			shape[i].scale = glm::vec3(0.2f, 0.2f, 0.2f);
			shape[i].XPRot = false;
			shape[i].XMRot = false;
			shape[i].YPRot = false;
			shape[i].YMRot = false;
			shape[i].Swap = false;
			shape[i].radian = 0.0f;
			shape[i].thetas = 0.0f;
			shape[i].SwapUnD = false;
			shape[i].UpDown = false;
		}
		theta = 0;
		shape[1].position = glm::vec3(-0.5f, -0.5f, -0.5f);
		XPRot = false;
		YPRot = false;
		XMRot = false;
		YMRot = false;
		starts = false;
		Orbit1 = false;
		Orbit2 = false;
		done = true;
		swap = false;
		Scale = false;
		done2 = false;
		SwapCircle = false;
		mi = false;
		Spiral = false;
		SwapUnD = false;
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
		Spiral = true;
		break;
	case '5':
		swap = true;
		break;
	case '6':
		SwapCircle = true;
		break;
	case '7':
		SwapUnD = true;
		break;
	case '8':
		Orbit1 = true;
		XPRot = true;
		shape[0].YPRot = true;
		shape[0].YMRot = false;
		shape[1].YPRot = true;
		shape[1].YMRot = false;
		Scale = true;
		break;

	case 'q':
		glutLeaveMainLoop();
		break;
	}
	glutPostRedisplay();
	if (XPRot || XMRot || YPRot || YMRot || Orbit1 || Orbit2 || swap || Scale || SwapCircle || Spiral || SwapUnD)
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
	SpiralAxes();
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

		if (Spiral)
		{
			shape[i].position.x = shape[i].radian * cos(-shape[i].thetas);
			shape[i].position.z = 0.0f;
			shape[i].position.y = shape[i].radian * sin(-shape[i].thetas);
			shape[i].thetas += shape[i].speed * disThetas;
			shape[i].radian += shape[i].speed * disRadian;

			if (shape[i].radian > 1.0)
			{
				shape[i].thetas = 0.0f;
				shape[i].radian = 0.0f;
			}
		}
	}

	if (Orbit1)
	{
		shape[0].position.x = 0.5f * cos(theta * PI / 180);
		shape[0].position.y = 0.5f * sin(theta * PI / 180);
		shape[1].position.x = -0.5f * cos(theta * PI / 180);
		shape[1].position.y = -0.5f * sin(theta * PI / 180);
		theta += 2;
		if (!mi)
		{
			shape[0].position.z -= 0.01;
			shape[1].position.z += 0.01;
		}
		else
		{
			shape[0].position.z += 0.01;
			shape[1].position.z -= 0.01;
		}

		if (shape[0].position.z < -0.5)
		{
			mi = true;
		}
		else if (shape[0].position.z > 0.5)
		{
			mi = false;
		}
	}
	else if (Orbit2)
	{
		shape[0].position.x = 0.5f * cos(theta * PI / 180);
		shape[0].position.y = 0.5f * sin(theta * PI / 180);
		
		shape[1].position.x = -0.5f * cos(theta * PI / 180);
		shape[1].position.y = -0.5f * sin(theta * PI / 180);
		
		theta -= 2;
		if (!mi)
		{
			shape[0].position.z += 0.01;
			shape[1].position.z -= 0.01;
		}
		else
		{
			shape[0].position.z -= 0.01;
			shape[1].position.z += 0.01;
		}

		if (shape[0].position.z > 0.5)
		{
			mi = true;
		}
		else if (shape[0].position.z < -0.5)
		{
			mi = false;
		}
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
			shape[0].position.y -= 0.01;
			shape[0].position.z -= 0.01;
		}
		else
		{
			shape[0].position.x += 0.01;
			shape[0].position.y += 0.01;
			shape[0].position.z += 0.01;
		}
		if (!shape[1].Swap)
		{
			shape[1].position.x += 0.01;
			shape[1].position.y += 0.01;
			shape[1].position.z += 0.01;
		}
		else
		{
			shape[1].position.x -= 0.01;
			shape[1].position.y -= 0.01;
			shape[1].position.z -= 0.01;
		}

		if (shape[0].position.x < -0.5)
		{
			shape[0].Swap = true;
			swap = false;
			starts = false;
		}
		else if (shape[0].position.x > 0.5)
		{
			shape[0].Swap = false;
			swap = false;
			starts = false;
		}
		if (shape[1].position.x > 0.5)
		{
			shape[1].Swap = true;
			swap = false;
			starts = false;
		}
		else if (shape[1].position.x < -0.5)
		{
			shape[1].Swap = false;
			swap = false;
			starts = false;
		}
	}

	if (Scale)
	{
		if (!shape[0].Scale)
		{
			shape[0].scale.x += 0.01;
			shape[0].scale.y += 0.01;
			shape[0].scale.z += 0.01;
		}
		else
		{
			shape[0].scale.x -= 0.01;
			shape[0].scale.y -= 0.01;
			shape[0].scale.z -= 0.01;
		}

		if (!shape[1].Scale)
		{
			shape[1].scale.x -= 0.01;
			shape[1].scale.y -= 0.01;
			shape[1].scale.z -= 0.01;
		}
		else
		{
			shape[1].scale.x += 0.01;
			shape[1].scale.y += 0.01;
			shape[1].scale.z += 0.01;
		}

		if (shape[0].scale.x > 0.25)
		{
			shape[0].Scale = true;
		}
		else if (shape[0].scale.x < 0.0)
		{
			shape[0].Scale = false;
		}

		if (shape[1].scale.x < 0.0)
		{
			shape[1].Scale = true;
		}
		else if (shape[1].scale.x > 0.25)
		{
			shape[1].Scale = false;
		}
	}

	if (SwapCircle)
	{
		if (!done2)
		{
			shape[0].position.x = 0.5 * cos(theta * PI / 180);
			shape[0].position.y = 0.5 * sin(theta * PI / 180);
			shape[0].position.z -= 0.01;
			shape[1].position.x = -0.5 * cos(theta * PI / 180);
			shape[1].position.y = -0.5 * sin(theta * PI / 180);
			shape[1].position.z += 0.01;
		}
		else
		{
			shape[0].position.x = 0.5 * cos(theta * PI / 180);
			shape[0].position.y = 0.5 * sin(theta * PI / 180);
			shape[0].position.z += 0.01;
			shape[1].position.x = -0.5 * cos(theta * PI / 180);
			shape[1].position.y = -0.5 * sin(theta * PI / 180);
			shape[1].position.z -= 0.01;
		}
		theta += 2;
		if (theta == 180 && !done2)
		{
			SwapCircle = false;
			done2 = true;
		}
		else if (theta == 360 && done2)
		{
			theta = 0;
			done2 = false;
			SwapCircle = false;
		}
	}

	if (SwapUnD)
	{
		if (!shape[0].SwapUnD)
		{
			shape[0].position.x -= 0.01;
			shape[0].position.z -= 0.01;
			if (!shape[0].UpDown)
			{
				shape[0].position.y += 0.01;
			}
			else
			{
				shape[0].position.y -= 0.03;
			}
		}
		else
		{
			shape[0].position.x += 0.01;
			shape[0].position.z += 0.01;
			if (shape[0].UpDown)
			{
				shape[0].position.y -= 0.01;
			}
			else
			{
				shape[0].position.y += 0.03;
			}
		}
		if (!shape[1].SwapUnD)
		{
			shape[1].position.x += 0.01;
			shape[1].position.z += 0.01;

			if (!shape[1].UpDown)
			{
				shape[1].position.y -= 0.01;
			}
			else
			{
				shape[1].position.y += 0.03;
			}
		}
		else
		{
			shape[1].position.x -= 0.01;
			shape[1].position.z -= 0.01;

			if (shape[1].UpDown)
			{
				shape[1].position.y += 0.01;
			}
			else
			{
				shape[1].position.y -= 0.03;
			}
		}

		if (shape[0].position.x < 0 && !shape[0].UpDown)
		{
			shape[0].UpDown = true;
		}
		else if (shape[0].position.x > 0 && shape[0].UpDown)
		{
			shape[0].UpDown = false;
		}

		if (shape[1].position.x > 0 && !shape[1].UpDown)
		{
			shape[1].UpDown = true;
		}
		else if (shape[1].position.x < 0 && shape[1].UpDown)
		{
			shape[1].UpDown = false;
		}

		if (shape[0].position.x < -0.5)
		{
			shape[0].SwapUnD = true;
			SwapUnD = false;
			starts = false;
		}
		else if (shape[0].position.x > 0.5)
		{
			shape[0].SwapUnD = false;
			SwapUnD = false;
			starts = false;
		}
		if (shape[1].position.x > 0.5)
		{
			shape[1].SwapUnD = true;
			SwapUnD = false;
			starts = false;
		}
		else if (shape[1].position.x < -0.5)
		{
			shape[1].SwapUnD = false;
			SwapUnD = false;
			starts = false;
		}
	}

	
	glutPostRedisplay();
	if (starts)
	{
		glutTimerFunc(10, TimerFunction, 1);
	}
}