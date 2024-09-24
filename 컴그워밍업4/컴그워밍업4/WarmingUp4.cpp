#include <iostream>
#include <random>
#include <windows.h>

enum { white = 15, blue = 1, cyan = 3, red = 4, green = 2, purple = 5, brown = 6, lightgray = 7, lightblue = 9, lightgreen = 10, lightcyan = 11, lightred = 12, lightpurple = 13 };

struct Board
{
	char c;
	bool state;
	bool done;
};

void setColor(int forground)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	int code = forground;
	SetConsoleTextAttribute(consoleHandle, code);
}

char Reset2(int a)
{
	char index[25] = { 'A', 'A', 'B', 'B', 'C', 'C', 'D', 'D', 'E', 'E', 'F', 'F', 'G', 'G' , 'H', 'H', 'I', 'I', 'J', 'J', 'K', 'K', 'L', 'L', '@' };
	return index[a];
}

void Print(char c, bool state)
{
	if (state == true)
	{
		if (c == 'A')
		{
			setColor(blue);
		}
		else if (c == 'B')
		{
			setColor(cyan);
		}
		else if (c == 'C')
		{
			setColor(red);
		}
		else if (c == 'D')
		{
			setColor(green);
		}
		else if (c == 'E')
		{
			setColor(purple);
		}
		else if (c == 'F')
		{
			setColor(brown);
		}
		else if (c == 'G')
		{
			setColor(lightgray);
		}
		else if (c == 'H')
		{
			setColor(lightblue);
		}
		else if (c == 'I')
		{
			setColor(lightgreen);
		}
		else if (c == 'J')
		{
			setColor(lightcyan);
		}
		else if (c == 'K')
		{
			setColor(lightred);
		}
		else if (c == 'L')
		{
			setColor(lightpurple);
		}
		std::cout << " " << c << " ";
	}
	else
	{
		setColor(white);
		std::cout << " * ";
	}
}

int TransForm(char c)
{
	int a = 0;
	if (c == 'a' || c == 'A')
	{
		a = 0;
	}
	else if (c == 'b' || c == 'B')
	{
		a = 1;
	}
	else if (c == 'c' || c == 'C')
	{
		a = 2;
	}
	else if (c == 'd' || c == 'D')
	{
		a = 3;
	}
	else if (c == 'e' || c == 'E')
	{
		a = 4;
	}
	return a;
}

bool Display(bool state)
{
	return state = true;
}

void Compare(char c1, char c2, bool& state1, bool& state2, bool& done1, bool& done2, int& score, int& num)
{
	if (c1 != c2 && done1 != true && done2 != true && state1 == true && state2 == true)
	{
		state1 = false;
		state2 = false;
		score -= 5;
		num--;
	}
	else if (c1 == c2 && done1 != true && done2 != true && state1 == true && state2 == true)
	{
		done1 = true;
		done2 = true;
		score += 20;
		num--;
	}
	else
	{
		return;
	}
}

void Joker(bool& state, bool& done)
{
	state = true;
	done = true;
}

void Grading(int num, int score)
{
	std::cout << "총 점수 : " << score << " 남은 횟수 : " << num << std::endl;
}

void Reset(int& score, int& num)
{
	score = 0;
	num = 7;
}

char Write(int a)
{
	char c = 65 + a;
	return c;
}

char Reset1()
{
	char c = '\0';
	return c;
}

int main()
{
	Board board[5][5];
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			board[i][j].c = Reset1();
			board[i][j].state = false;
			board[i][j].done = false;
		}
	}
	char x, select;
	char index[25] = { 'A', 'A', 'B', 'B', 'C', 'C', 'D', 'D', 'E', 'E', 'F', 'F', 'G', 'G' , 'H', 'H', 'I', 'I', 'J', 'J', 'K', 'K', 'L', 'L', '@' };
	int y, x1, score = 0, num = 10, x2, y2, count = 0, random2 = 0, cx = 0, cy = 0, cnt = 0;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> number2(0, 24);
	for (int i = 0; i < 25; i++)
	{
		random2 = number2(gen);
		if (index[random2] != '\0')
		{
			board[cy][cx].c = index[random2];
			index[random2] = '\0';
			cx++;
			if (cx == 5)
			{
				cx = 0;
				cy++;
			}
		}
		else
		{
			i--;
		}
	}
	bool first = false;
	while (num > 0)
	{
		system("cls");
		std::cout << "현재 점수 : " << score << " 남은 횟수 : " << num << std::endl;
		std::cout << "  a  b  c  d  e " << std::endl;
		for (int i = 0; i < 5; i++)
		{
			std::cout << i + 1;
			for (int j = 0; j < 5; j++)
			{
				Print(board[i][j].c, board[i][j].state);
			}
			std::cout << std::endl;
		}
		for (int i = 0; i < 5; i++)
		{
			std::cout << i + 1;
			for (int j = 0; j < 5; j++)
			{
				std::cout << " " << board[i][j].c << " ";
			}
			std::cout << std::endl;
		}
		std::cout << "좌표를 입력해주세요. : ";
		std::cin >> x;
		switch (x)
		{
		case 'r':
			std::cout << "게임을 리셋하고 다시 시작합니다. " << std::endl;
			cnt = 0;
			Reset(score, num);
			for (int i = 0; i < 25; i++)
			{
				index[i] = Reset2(i);
			}
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					board[i][j].c = Reset1();
					board[i][j].state = false;
					board[i][j].done = false;
				}
			}
			cx = 0, cy = 0;
			for (int i = 0; i < 25; i++)
			{
				random2 = number2(gen);
				if (index[random2] != '\0')
				{
					board[cy][cx].c = index[random2];
					index[random2] = '\0';
					cx++;
					if (cx == 5)
					{
						cx = 0;
						cy++;
					}
				}
				else
				{
					i--;
				}
			}
			continue;
			break;
		}
		std::cin >> y;
		bool str = false;
		x1 = TransForm(x);
		if (board[y - 1][x1].state != true)
		{
			board[y - 1][x1].state = Display(board[y - 1][x1].state);
			if (first == false)
			{
				first = true;
				select = board[y - 1][x1].c;
				x2 = x1;
				y2 = y - 1;
			}
			else
			{
				first = false;
			}
			if (board[y - 1][x1].c != '@' && first == false)
			{
				for (int i = 0; i < 5; i++)
				{
					for (int j = 0; j < 5; j++)
					{
						Compare(board[y - 1][x1].c, board[i][j].c, board[y - 1][x1].state, board[i][j].state, board[i][j].done, board[y - 1][x1].done, score, num);
						break;
					}
				}
			}
			else if (board[y - 1][x1].c == '@' && first == false)
			{
				for (int i = 0; i < 5; i++)
				{
					for (int j = 0; j < 5; j++)
					{
						if (select == board[i][j].c)
						{
							Joker(board[i][j].state, board[i][j].done);
							Joker(board[y2][x2].state, board[y2][x2].done);
							Joker(board[y - 1][x1].state, board[y - 1][x1].done);
							num--;
							score += 15;
						}
					}
				}
			}
		}
	}
	Grading(num, score);
}