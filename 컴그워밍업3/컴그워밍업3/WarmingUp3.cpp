#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

struct List
{
	double x;
	double y;
	double z;
	bool state;
};

int main()
{
	int maximum = 0;
	int location = 0, count = 0, queue = 0, maxcount = 0, mincount = 0, son = 0;
	double sum = 0, sum2 = 0, max = 0, min = 0, sumsum = 0;
	List list[20], temp;
	char c;

	while (1)
	{
		for (int i = 0; i < 20; i++)
		{
			if (list[i].state == true)
				printf(" %d - x: %d, y: %d, z: %d \n", i, list[i].x, list[i].y, list[i].z);
		}
		printf("수행할 명령 입력 : ");
		scanf_s(" %c", &c);
		switch (c)
		{
		case '+':
			if (maximum != 20)
			{
				scanf_s(" %d %d %d", &list[maximum].x, &list[maximum].y, &list[maximum].z);
				list[maximum].state = true;
				maximum++;
				count++;
			}
			break;
		case '-':
			if (count != 0)
			{
				maximum--;
				count--;
				list[maximum].state = false;
			}
			break;
		case 'e':
			if (list[0].state == true)
			{
				son = 0;
				for (int i = 0; i < 20; i++)
				{
					if (list[i].state == true)
					{
						son++;
					}
					else
					{
						break;
					}
				}
				if (son == maximum)
				{
					for (int i = maximum; i >= 0; i--)
					{
						list[i + 1] = list[i];
					}
					maximum++;
				}
				else
				{
					for (int i = son - 1; i >= 0; i--)
					{
						list[i + 1] = list[i];
					}
				}
			}
			scanf_s(" %d %d %d", &list[0].x, &list[0].y, &list[0].z);
			list[0].state = true;
			queue = 0;
			count++;
			break;
		case 'd':
			if (list[queue].state == true)
			{
				list[queue].state = false;
				for (int i = 0; i < maximum; i++)
				{
					if (list[queue].state == false)
					{
						queue++;
					}
				}
			}
			count--;
			break;
		case 'l':
			printf("현재 리스트에 저장된 점 개수 : %d \n", count);
			break;
		case 'c':
			for (int i = 0; i < 20; i++)
			{
				list[i].state = false;
			}
			maximum = 0;
			count = 0;
			break;
		case 'm':
			sum = 0;
			sumsum = 0;
			for (int i = 0; i < maximum; i++)
			{
				if (list[i].state == true)
				{
					sumsum = pow(list[i].x, 2) + pow(list[i].y, 2) + pow(list[i].z, 2);
					sum = sqrt(sumsum);
					if (max < sum)
					{
						max = sum;
						maxcount = i;
					}
				}
			}
			printf("원점에서 가장 먼 거리에 있는 좌표값 x : %d, y : %d, z : %d\n", list[maxcount].x, list[maxcount].y, list[maxcount].z);
			break;
		case 'n':
			sum = 0;
			sumsum = 0;
			for (int i = 0; i < maximum; i++)
			{
				if (list[i].state == true)
				{
					sumsum = pow(list[i].x, 2) + pow(list[i].y, 2) + pow(list[i].z, 2);
					sum = sqrt(sumsum);
					if (min  sum)
					{
						min = sum;
						mincount = i;
					}
				}
			}
			printf("원점에서 가장 가까운 거리에 있는 좌표값 x : %d, y : %d, z : %d\n", list[mincount].x, list[mincount].y, list[mincount].z);
			break;
		case 'a':
			for (int i = 0; i < maximum; i++)
			{
				for (int j = 0; j < maximum; j++)
				{
					sum = list[i].x + list[i].y + list[i].z;
					sum2 = list[j].x + list[j].y + list[j].z;
					if (sum < sum2)
					{
						temp = list[i];
						list[i] = list[j];
						list[j] = temp;
					}
				}
			}
			for (int i = 0; i < maximum; i++)
			{
				if (list[i].state == false)
				{
					for (int j = i; j < maximum; j++)
					{
						list[j] = list[j + 1];
					}
					list[maximum].state = false;
					maximum--;
				}
			}
			break;
		case 's':
			for (int i = 0; i < maximum; i++)
			{
				for (int j = 0; j < maximum; j++)
				{
					sum = list[i].x + list[i].y + list[i].z;
					sum2 = list[j].x + list[j].y + list[j].z;
					if (sum > sum2)
					{
						temp = list[i];
						list[i] = list[j];
						list[j] = temp;
					}
				}
			}
			break;
		case 'q':
			exit(1);
			break;
		}
	}
}