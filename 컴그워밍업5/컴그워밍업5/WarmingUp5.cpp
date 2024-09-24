#include <stdio.h>
#include <stdlib.h>
#include <iostream>

struct Shape
{
	int x1;
	int x2;
	int y1;
	int y2;
};

void move1(int& z1, int& z2, int area)
{
	z1++;
	z2++;
	if (z1 == area)
	{
		z1 = 0;
	}
	else if (z2 == area)
	{
		z2 = 0;
	}
}

void move2(int& z1, int& z2, int area)
{
	z1--;
	z2--;
	if (z1 < 0)
	{
		z1 = area - 1;
	}
	else if (z2 < 0)
	{
		z2 = area - 1;
	}
}

void ZoomIn(int& z, int area)
{
	z++;
	if (z == area)
	{
		z = area - 1;
	}
}

void ZoomOut(int& z)
{
	z--;
	if (z < 0)
	{
		z = 0;
	}
}

void AreaRadio(int area, int radio, int& Result)
{
	double areas = area * area;
	Result = (radio / areas) * 100;
}

void Print(int area, int x1, int x2, int y1, int y2)
{
	for (int i = 0; i < area; i++)
	{
		for (int j = 0; j < area; j++)
		{
			if (x1 <= j && j <= x2 && y1 <= i && i <= y2)
			{
				std::cout << " O ";
			}
			else if (x1 <= j && x1 > x2 && j <= area - 1 && y1 <= i && i <= y2 || j <= x2 && x1 > x2 && j >= 0 && y1 <= i && i <= y2)
			{
				std::cout << " O ";
			}
			else if (y1 <= i && y1 > y2 && i <= area - 1 && x1 <= j && j <= x2 || i <= y2 && y1 > y2 && i >= 0 && x1 <= j && j <= x2)
			{
				std::cout << " O ";
			}
			else
			{
				std::cout << " . ";
			}
		}
		std::cout << std::endl;
	}
}

void Radio(int x1, int y1, int x2, int y2, int& Radio)
{
	Radio = (x2 - x1 + 1) * (y2 - y1 + 1);
}

int main()
{
	Shape shape;
	std::cout << "좌표를 입력해주세요 (x1, y1), (x2, y2) : ";
	std::cin >> shape.x1 >> shape.y1 >> shape.x2 >> shape.y2;
	int area = 10, radio = 0;
	int result = 0;
	while (1)
	{
		char c;
		if (radio != 0 && result == 0)
		{
			std::cout << "현재 사각형의 면적 : " << radio << std::endl;
		}
		else if (result != 0)
		{
			std::cout << "전체 면적에 대한 사각형의 면적 비율 : " << result << "%" << std::endl;
		}

		Print(area, shape.x1, shape.x2, shape.y1, shape.y2);
		result = 0, radio = 0;
		std::cout << "명령을 입력해주세요 : ";
		std::cin >> c;
		switch (c)
		{
		case 'x':
			move1(shape.x1, shape.x2, area);
			break;
		case 'X':
			move2(shape.x1, shape.x2, area);
			break;
		case 'y':
			move1(shape.y1, shape.y2, area);
			break;
		case 'Y':
			move2(shape.y1, shape.y2, area);
			break;
		case 'i':
			ZoomIn(shape.x2, area);
			break;
		case 'I':
			ZoomOut(shape.x2);
			break;
		case 'j':
			ZoomIn(shape.y2, area);
			break;
		case 'J':
			ZoomOut(shape.y2);
			break;
		case 'a':
			ZoomIn(shape.x2, area);
			ZoomOut(shape.y2);
			break;
		case 'A':
			ZoomIn(shape.y2, area);
			ZoomOut(shape.x2);
			break;
		case 'm':
			Radio(shape.x1, shape.y1, shape.x2, shape.y2, radio);
			break;
		case 'n':
			Radio(shape.x1, shape.y1, shape.x2, shape.y2, radio);
			AreaRadio(area, radio, result);
			break;
		case 'r':
			std::cout << "다시 시작합니다. 좌표를 입력해주세요 (x1, y1), (x2, y2) : ";
			std::cin >> shape.x1 >> shape.y1 >> shape.x2 >> shape.y2;
			break;
		case 'q':
			exit(0);
			break;
		}
		system("cls");
	}
}