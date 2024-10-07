#include "GLmain.h"

class Shape
{
public:
	GLfloat shapecoord[3];
	GLfloat color[3];
	Shape()
	{
		for (int i = 0; i < 3; i++)
		{
			Color(color[i]);
			shapecoord[i] = 0.0;
		}
	};

	void Colors()
	{
		for (int i = 0; i < 3; i++)
		{
			Color(color[i]);
		}
	}
};

Shape shape1[220];
Shape shape2[220];
Shape shape3[220];
Shape shape4[220];
Shape shape5[220];
float r = 0.01;
int count = 0;
int shapecount = 1;
int theta = 0;
float fx = 0.0, fy = 0.0;
float xx[4], yy[4];
bool outwardSpiral = true;
bool frame = false;

GLvoid drawScene()
{
	glClearColor(bGCr, bGCg, bGCb, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shaderProgramID);
	UpdateBuffer();
	glBindVertexArray(vao);
	for (int i = 0; i < 220 * shapecount; i++)
	{
		if (frame)
		{
			glDrawArrays(GL_LINE_STRIP, i * 3, 3); // �����̷��� �� ���׸�Ʈ �׸���
		}
		else
		{
			glPointSize(5.0);
			glDrawArrays(GL_POINTS, i * 3, 3); // ����Ʈ�� �׸���
		}
	}
		
	glutSwapBuffers();
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'p':
		frame = false;
		break;
	case 'l':
		frame = true;
		break;
	case '1':
		shapecount = 1;
		break;
	case '2':
		shapecount = 2;
		break;
	case '3':
		shapecount = 3;
		break;
	case '4':
		shapecount = 4;
		break;
	case '5':
		shapecount = 5;
		break;
	case 'q':
		glutLeaveMainLoop();
		break;
	}
	glutPostRedisplay();
}


GLvoid Mouse(int button, int state, int x, int y)
{
	convertXY(x, y, fx, fy);
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		for (int i = 0; i < 220; i++)
		{
			shape1[i].shapecoord[0] = 0;
			shape1[i].shapecoord[1] = 0;
		}
		Color(bGCb);
		Color(bGCg);
		Color(bGCr);
		r = 0.01;
		count = 0;
		theta = 0;
		outwardSpiral = true;
		frame = false;
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> random(0, 800);
		std::uniform_int_distribution<int> random2(0, 600);
		if (shapecount > 1)
		{
			for (int i = 0; i < shapecount - 1; i++)
			{
				convertXY(random(gen), random2(gen), xx[i], yy[i]);
			}
		}
		glutTimerFunc(10, TimerFunction, 1);
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
	glBufferData(GL_ARRAY_BUFFER, 1100 * 3 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	//--- ��ǥ���� attribute �ε��� 0���� ����Ѵ�: ���ؽ� �� 3* float
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//--- attribute �ε��� 0���� ��밡���ϰ� ��
	glEnableVertexAttribArray(0);

	//--- 2��° VBO�� Ȱ��ȭ �Ͽ� ���ε� �ϰ�, ���ؽ� �Ӽ� (����)�� ����
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	//--- ���� colors���� ���ؽ� ������ �����Ѵ�.
	//--- colors �迭�� ������: 9 *float
	glBufferData(GL_ARRAY_BUFFER, 1100 * 3 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	//--- ������ attribute �ε��� 1���� ����Ѵ�: ���ؽ� �� 3*float
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//--- attribute �ε��� 1���� ��� �����ϰ� ��.
	glEnableVertexAttribArray(1);
}

void UpdateBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	for (int i = 0; i < 1100; i++)
	{
		if (i < 220)
		{
			glBufferSubData(GL_ARRAY_BUFFER, i * 3 * sizeof(GLfloat), 3 * sizeof(GLfloat), shape1[i].shapecoord);
		}
		else if (220 <= i && i < 440)
		{
			glBufferSubData(GL_ARRAY_BUFFER, i * 3 * sizeof(GLfloat), 3 * sizeof(GLfloat), shape2[i - 220].shapecoord);
		}
		else if (440 <= i && i < 660)
		{
			glBufferSubData(GL_ARRAY_BUFFER, i * 3 * sizeof(GLfloat), 3 * sizeof(GLfloat), shape3[i - 440].shapecoord);
		}
		else if (660 <= i && i < 880)
		{
			glBufferSubData(GL_ARRAY_BUFFER, i * 3 * sizeof(GLfloat), 3 * sizeof(GLfloat), shape4[i - 660].shapecoord);
		}
		else if (880 <= i && i < 1100)
		{
			glBufferSubData(GL_ARRAY_BUFFER, i * 3 * sizeof(GLfloat), 3 * sizeof(GLfloat), shape5[i - 880].shapecoord);
		}
	}
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	for (int i = 0; i < 1100; i++)
	{
		if (i < 220)
		{
			glBufferSubData(GL_ARRAY_BUFFER, i * 3 * sizeof(GLfloat), 3 * sizeof(GLfloat), shape1[i].color);
		}
		else if (220 <= i && i < 440)
		{
			glBufferSubData(GL_ARRAY_BUFFER, i * 3 * sizeof(GLfloat), 3 * sizeof(GLfloat), shape2[i - 220].color);
		}
		else if (440 <= i && i < 660)
		{
			glBufferSubData(GL_ARRAY_BUFFER, i * 3 * sizeof(GLfloat), 3 * sizeof(GLfloat), shape3[i - 440].color);
		}
		else if (660 <= i && i < 880)
		{
			glBufferSubData(GL_ARRAY_BUFFER, i * 3 * sizeof(GLfloat), 3 * sizeof(GLfloat), shape4[i - 660].color);
		}
		else if (880 <= i && i < 1100)
		{
			glBufferSubData(GL_ARRAY_BUFFER, i * 3 * sizeof(GLfloat), 3 * sizeof(GLfloat), shape5[i - 880].color);
		}
	}
}

GLvoid TimerFunction(int value)
{
	// �� �����̷��� ��ǥ ���

	if (outwardSpiral)
	{
		shape1[count].shapecoord[0] = fx + r * cos(theta * PI / 180);
		shape1[count].shapecoord[1] = fy + r * sin(theta * PI / 180);
		if (shapecount > 1)
		{
			shape2[count].shapecoord[0] = xx[0] + r * cos(theta * PI / 180);
			shape2[count].shapecoord[1] = yy[0] + r * sin(theta * PI / 180);
		}
		if (shapecount > 2)
		{
			shape3[count].shapecoord[0] = xx[1] + r * cos(theta * PI / 180);
			shape3[count].shapecoord[1] = yy[1] + r * sin(theta * PI / 180);
		}
		if (shapecount > 3)
		{
			shape4[count].shapecoord[0] = xx[2] + r * cos(theta * PI / 180);
			shape4[count].shapecoord[1] = yy[2] + r * sin(theta * PI / 180);
		}
		if (shapecount > 4)
		{
			shape5[count].shapecoord[0] = xx[3] + r * cos(theta * PI / 180);
			shape5[count].shapecoord[1] = yy[3] + r * sin(theta * PI / 180);
		}
		theta += 10; // ���� ���� (�ð� ����)
		r += 0.001; // ������ ����
		if (theta >= 1080)
		{ // 2���� �Ŀ�
			fx += r * 2;
			for (int i = 0; i < 4; i++)
			{
				xx[i] += r * 2;
			}
			outwardSpiral = false; // ���� �ܰ�� ��ȯ
			theta = 1080; // �ݴ� ���� ���� ����
		}
	}
	else
	{
		shape1[count].shapecoord[0] = fx - r * cos(theta * PI / 180);
		shape1[count].shapecoord[1] = fy - r * sin(theta * PI / 180);
		if (shapecount > 1)
		{
			shape2[count].shapecoord[0] = xx[0] - r * cos(theta * PI / 180);
			shape2[count].shapecoord[1] = yy[0] - r * sin(theta * PI / 180);
		}
		if (shapecount > 2)
		{
			shape3[count].shapecoord[0] = xx[1] - r * cos(theta * PI / 180);
			shape3[count].shapecoord[1] = yy[1] - r * sin(theta * PI / 180);
		}
		if (shapecount > 3)
		{
			shape4[count].shapecoord[0] = xx[2] - r * cos(theta * PI / 180);
			shape4[count].shapecoord[1] = yy[2] - r * sin(theta * PI / 180);
		}
		if (shapecount > 4)
		{
			shape5[count].shapecoord[0] = xx[3] - r * cos(theta * PI / 180);
			shape5[count].shapecoord[1] = yy[3] - r * sin(theta * PI / 180);
		}
		r -= 0.001;
		theta -= 10; // ���� ���� (�ݽð� ����)
	}

	glutPostRedisplay(); // ȭ�� ���� ��ħ
	count++;
	if (count < 220)
	{
		glutTimerFunc(10, TimerFunction, 1);
	}
}