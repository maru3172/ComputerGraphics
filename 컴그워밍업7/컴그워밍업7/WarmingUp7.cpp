#include <iostream>
#include <windows.h>

enum { white = 15, red = 4 };

void setColor(int forground)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	int code = forground;
	SetConsoleTextAttribute(consoleHandle, code);
}

struct Shape
{
	int x1;
	int x2;
	int y1;
	int y2;
};

void move1(int& z, int& z2, int area)
{
	z++;
	z2++;
	if (z == area)
	{
		z = 0;
	}
	else if (z2 == area)
	{
		z2 = 0;
	}
}

void move2(int& z, int& z2, int area)
{
	z--;
	z2--;
	if (z < 0)
	{
		z = area - 1;
	}
	else if (z2 < 0)
	{
		z2 = area - 1;
	}
}

void ZoomIn(int& x, int& y, int area)
{
	x++;
	y++;
	if (x == area && y == area)
	{
		x = area;
		y = area;
	}
}

void ZoomOut(int& x, int& y)
{
	x--;
	y--;
	if (x < 0 && y < 0)
	{
		x = 0;
		y = 0;
	}
}

void Print(int area, int x1, int x2, int y1, int y2, int x3, int x4, int y3, int y4)
{
	for (int i = 0; i < area; i++)
	{
		for (int j = 0; j < area; j++)
		{
			if (x1 <= j && j <= x4 && x3 <= j && j <= x2 && y1 <= i && i <= y4 && y3 <= i && i <= y2)
			{
				setColor(red);
				std::cout << " X ";
			}
			else
			{
				if (x1 <= j && j <= x2 && y1 <= i && i <= y2)
				{
					setColor(white);
					std::cout << " O ";
				}
				else if (x1 <= j && x1 > x2 && j <= area - 1 && y1 <= i && i <= y2 || j <= x2 && x1 > x2 && j >= 0 && y1 <= i && i <= y2)
				{
					setColor(white);
					std::cout << " O ";
				}
				else if (y1 <= i && y1 > y2 && i <= area - 1 && x1 <= j && j <= x2 || i <= y2 && y1 > y2 && i >= 0 && x1 <= j && j <= x2)
				{
					setColor(white);
					std::cout << " O ";
				}
				else if (x3 <= j && j <= x4 && y3 <= i && i <= y4)
				{
					setColor(white);
					std::cout << " # ";
				}
				else if (x3 <= j && x3 > x4 && j <= area - 1 && y3 <= i && i <= y4 || j <= x4 && x3 > x4 && j >= 0 && y3 <= i && i <= y4)
				{
					setColor(white);
					std::cout << " # ";
				}
				else if (y3 <= i && y3 > y4 && i <= area - 1 && x3 <= j && j <= x4 || i <= y4 && y3 > y4 && i >= 0 && x3 <= j && j <= x4)
				{
					setColor(white);
					std::cout << " # ";
				}
				else
				{
					setColor(white);
					std::cout << " . ";
				}
			}

		}
		std::cout << std::endl;
	}
	return;
}

int main()
{
	Shape shape1, shape2;
	int range = 20;

	std::cout << "첫 번째 도형 좌표를 결정해주세요. : ";
	std::cin >> shape1.x1 >> shape1.y1 >> shape1.x2 >> shape1.y2;

	std::cout << "두 번째 도형 좌표를 결정해주세요. : ";
	std::cin >> shape2.x1 >> shape2.y1 >> shape2.x2 >> shape2.y2;

	while (1)
	{
		system("cls");
		char c;
		Print(range, shape1.x1, shape1.x2, shape1.y1, shape1.y2, shape2.x1, shape2.x2, shape2.y1, shape2.y2);
		std::cout << "원하시는 명령을 입력해주세요. : ";
		std::cin >> c;
		switch (c)
		{
		case 'x':
			move2(shape1.x1, shape1.x2, range);
			break;
		case 'X':
			move1(shape1.x1, shape1.x2, range);
			break;
		case 'y':
			move1(shape1.y1, shape1.y2, range);
			break;
		case 'Y':
			move2(shape1.y1, shape1.y2, range);
			break;
		case 's':
			ZoomOut(shape1.x2, shape1.y2);
			break;
		case 'S':
			ZoomIn(shape1.x2, shape1.y2, range);
			break;
		case 'w':
			move2(shape2.x1, shape2.x2, range);
			break;
		case 'W':
			move1(shape2.x1, shape2.x2, range);
			break;
		case 'a':
			move1(shape2.y1, shape2.y2, range);
			break;
		case 'A':
			move2(shape2.y1, shape2.y2, range);
			break;
		case 'd':
			ZoomOut(shape2.x2, shape2.y2);
			break;
		case'D':
			ZoomIn(shape2.x2, shape2.y2, range);
			break;
		case 'r':
			std::cout << "다시 입력받고 시작합니다. " << std::endl;
			std::cout << "첫 번째 도형 좌표를 결정해주세요. : ";
			std::cin >> shape1.x1 >> shape1.y1 >> shape1.x2 >> shape1.y2;

			std::cout << "두 번째 도형 좌표를 결정해주세요. : ";
			std::cin >> shape2.x1 >> shape2.y1 >> shape2.x2 >> shape2.y2;
			break;
		case 'q':
			exit(0);
			break;
		}
	}
}