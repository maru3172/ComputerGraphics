#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

enum ColorType { WHITE = 15, GRAY = 8, BLUE = 9, GREEN = 10 } color;

int main()
{
	FILE* fp;
	fp = fopen("data.txt", "r");
	char ch[200][200], chback[200][200], inp;
	int index = 0, line = 0;
	while ((inp = fgetc(fp)) != EOF)
	{
		ch[line][index] = inp;
		index++;
		if (inp == '\n')
		{
			ch[line][index] = '\0';
			line++;
			index = 0;
		}
	}
	fclose(fp);

	for (int i = 0; i < line; i++)
	{
		for (int j = 0; j <= strlen(ch[i]); j++)
		{
			chback[i][j] = ch[i][j];
		}
	}

	char c, temp, before, after, word[100];
	int count = 0, stat = 0, stat2 = 0, stat3 = 0, stat4 = 0, stat5 = 0, stac = 0, tempr;
	bool on = false, onon = false, cons = false, cony = false;
	int* counter = (int*)malloc(sizeof(int) * line);
	int* counterback = (int*)malloc(sizeof(int) * line);
	while (1)
	{
		for (int i = 0; i < line; i++)
		{
			count = 0;
			for (int j = 0; j <= strlen(ch[i]); j++)
			{
				if (ch[i][j] == ' ' || ch[i][j] == '\0' && ch[i][j - 1] != ' ')
				{
					count++;
				}
			}
			counter[i] = count;
			counterback[i] = count;
		}
		count = 0;
		stac = 0;
		for (int i = 0; i < line; i++)
		{
			for (int j = 0; j <= strlen(ch[i]); j++)
			{
				if (on == false && onon == false && stat5 == 0 && cony == false)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
					printf("%c", ch[i][j]);
				}
			}
		}
		printf("\n수행할 명령 입력 : ");
		scanf_s(" %c", &c);
		switch (c)
		{
		case 'c':
			if (on == false)
			{
				for (int i = 0; i < line; i++)
				{
					for (int j = 0; j <= strlen(ch[i]); j++)
					{
						if (ch[i][j] >= 65 && ch[i][j] <= 90)
						{
							cons = true;
						}
						else if (ch[i][j] == ' ' || ch[i][j] == '\0')
						{
							cons = false;
						}
						if (cons == true)
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
							printf("%c", ch[i][j]);
						}
						else
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
							printf("%c", ch[i][j]);
						}
					}
				}
				on = true;
			}
			else
			{
				on = false;
			}

			break;
		case 'd':
			if (stat4 == 0)
			{
				printf("원하시는 줄을 선택해주세요 : ");
				scanf_s(" %d", &count);
				count--;
				if (count < 10)
				{
					for (int i = 0; i < strlen(ch[count]) / 2 - 1; i++)
					{
						temp = ch[count][i];
						ch[count][i] = ch[count][strlen(ch[count]) - 2 - i];
						ch[count][strlen(ch[count]) - i - 2] = temp;
					}
					stat4++;
				}
			}
			else
			{
				for (int i = 0; i < line; i++)
				{
					strcpy(ch[i], chback[i]);
				}
				stat4 = 0;
			}
			break;
		case 'e':
			if (stat3 == 0)
			{
				for (int i = 0; i < line; i++)
				{
					for (int j = 0; j <= strlen(ch[i]); j++)
					{
						if (count == 3)
						{
							for (int z = strlen(ch[i]); z >= j; z--)
							{
								ch[i][z + 2] = ch[i][z];
							}
							ch[i][j] = ch[i][j + 1] = '@';
							j += 2;
							count = 0;
						}
						count++;
					}
				}
				stat3++;
			}
			else
			{
				for (int i = 0; i < line; i++)
				{
					strcpy(ch[i], chback[i]);
				}
				stat3 = 0;
			}
			break;
		case 'f':
			count = 0;
			if (stat5 == 0)
			{
				for (int i = 0; i < line; i++)
				{
					count = 0;
					for (int j = 0; j <= strlen(ch[i]); j++)
					{
						if (ch[i][j] == ' ')
						{
							for (int k = j; k >= count; k--)
							{
								printf("%c", ch[i][k]);
							}
							count = j + 1;
						}
						else if (ch[i][j] == '\0' && ch[i][j] != ' ')
						{
							printf(" ");
							for (int k = j - 2; k >= count; k--)
							{
								printf("%c", ch[i][k]);
							}
							count = j + 1;
							printf("\n");
						}
					}
				}
				stat5++;
			}
			else
			{
				for (int i = 0; i < line; i++)
				{
					strcpy(ch[i], chback[i]);
				}
				stat5 = 0;
			}
			break;
		case 'g':
			if (stat2 == 0)
			{
				printf("바꿀 문자를 입력해주세요. : ");
				scanf_s(" %c", &before);
				printf("원하는 문자를 입력해주세요 : ");
				scanf_s(" %c", &after);
				for (int i = 0; i < line; i++)
				{
					for (int j = 0; j <= strlen(ch[i]); j++)
					{
						if (ch[i][j] == before)
						{
							ch[i][j] = after;
						}
					}
				}
				stat2++;
			}
			else
			{
				for (int i = 0; i < line; i++)
				{
					strcpy(ch[i], chback[i]);
				}
				stat2 = 0;
			}
			break;
		case 'h':
			for (int i = 0; i < line; i++)
			{
				if (stat == 0)
				{
					for (int z = 0; z < line; z++)
					{
						counter[i] = counterback[i];
					}
				}
				else if (stat == 1)
				{
					for (int j = 0; j < line; j++)
					{
						for (int z = 0; z < line; z++)
						{
							if (counter[j] < counter[z])
							{
								tempr = counter[j];
								counter[j] = counter[z];
								counter[z] = tempr;
							}
						}
					}
				}
				else
				{
					for (int j = 0; j < line; j++)
					{
						for (int z = 0; z < line; z++)
						{
							if (counter[j] > counter[z])
							{
								tempr = counter[j];
								counter[j] = counter[z];
								counter[z] = tempr;
							}
						}
					}
				}
				printf("%d번째 줄 단어 개수 %d개\n", i + 1, counter[i]);
			}
			break;
		case 'r':
			if (stat == 0)
			{
				for (int i = 0; i < 100; i++)
				{
					for (int j = 0; j < line; j++)
					{
						if (counter[j] == i)
						{
							for (int z = 0; ch[j][z] != '\0'; z++)
							{
								printf("%c", ch[j][z]);
							}
						}
					}
				}
				stat++;
				cony = true;
			}
			else if (stat == 1)
			{
				for (int i = 100; i >= 0; i--)
				{
					for (int j = 0; j < line; j++)
					{
						if (counter[j] == i)
						{
							for (int z = 0; ch[j][z] != '\0'; z++)
							{
								printf("%c", ch[j][z]);
							}
						}
					}
				}
				stat++;
			}
			else
			{
				for (int i = 0; i < line; i++)
				{
					strcpy(ch[i], chback[i]);
				}
				stat = 0;
				cony = false;
			}
			break;
		case 's':
			if (onon == false)
			{
				scanf_s(" %s", word, 100);
				for (int i = 0; i < line; i++)
				{
					for (int j = 0; j <= strlen(ch[i]); j++)
					{
						if (_strnicmp(&ch[i][j], word, strlen(word)) == 0)
						{
							stac++;
							for (int z = 0; z <= strlen(word); z++)
							{
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
								printf("%c", ch[i][j + z]);
							}
							j += strlen(word);
						}
						else
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
							printf("%c", ch[i][j]);
						}
					}
				}
				printf("%s는 현재 %d개 있습니다.\n", word, stac);
				onon = true;
			}
			else
			{
				onon = false;
			}
			break;
		case 'q':
			free(counter);
			exit(1);
			break;
		}
	}
}