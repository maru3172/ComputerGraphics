#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int random()
{
	int matrixplace;
	matrixplace = rand() % 16;
	return matrixplace;
}

int main()
{
	int Matrix1[4][4], matrixnum[2], count = 0;
	int Matrix2[4][4], MatrixRest1[4][4], MatrixRest2[4][4], Shape = 0, MatrixT1[4][4], MatrixT2[4][4], MatrixDet1, MatrixDet2, s1, s2, s3, s4;
	srand(time(NULL));

	for (int i = 0; i < 2; i++)
	{
		matrixnum[i] = random();
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int z = 0; z < 2; z++)
			{
				if (matrixnum[z] == count)
				{
					Matrix1[i][j] = 2;
					break;
				}
				else
					Matrix1[i][j] = rand() % 2;
			}
			count++;
		}
	}

	for (int i = 0; i < 2; i++)
	{
		matrixnum[i] = random();
	}
	count = 0;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int z = 0; z < 2; z++)
			{
				if (matrixnum[z] == count)
				{
					Matrix2[i][j] = 2;
					break;
				}
				else
					Matrix2[i][j] = rand() % 2;
			}
			count++;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			MatrixRest1[i][j] = Matrix1[i][j];
			MatrixRest2[i][j] = Matrix2[i][j];
		}
	}

	char c;
	while (1)
	{
		int n = 0;
		int sum = 0;
		printf("\n");
		printf("1번째 행렬 \n");
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				printf(" %d ", Matrix1[i][j]);
			}
			printf("\n");
		}
		printf("\n");
		printf("2번째 행렬 \n");
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				printf(" %d ", Matrix2[i][j]);
			}
			printf("\n");
		}
		printf("원하는 명령 입력 : ");
		scanf_s(" %c", &c);
		switch (c)
		{
		case 'm':
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					for (int k = 0; k < 4; k++)
					{
						sum += Matrix1[i][k] * Matrix2[k][j];
					}
					printf(" %d ", sum);
					sum = 0;
				}
				printf("\n");

			}
			break;
		case 'a':
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					printf(" %d ", Matrix1[i][j] + Matrix2[i][j]);
				}
				printf("\n");
			}
			break;
		case 'd':
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					printf(" %d ", Matrix1[i][j] - Matrix2[i][j]);
				}
				printf("\n");
			}
			break;
		case 'r':
			s1 = Matrix1[0][0] * (Matrix1[1][1] * (Matrix1[2][2] * Matrix1[3][3] - Matrix1[3][2] * Matrix1[2][3]) - Matrix1[1][2] * (Matrix1[2][1] * Matrix1[3][3] - Matrix1[2][3] * Matrix1[3][1]) + Matrix1[1][3] * (Matrix1[2][1] * Matrix1[3][2] - Matrix1[2][2] * Matrix1[3][1]));
			s2 = Matrix1[0][1] * (Matrix1[1][0] * (Matrix1[2][2] * Matrix1[3][3] - Matrix1[3][2] * Matrix1[2][3]) - Matrix1[1][2] * (Matrix1[2][0] * Matrix1[3][3] - Matrix1[2][3] * Matrix1[3][0]) + Matrix1[1][3] * (Matrix1[2][0] * Matrix1[3][2] - Matrix1[2][2] * Matrix1[3][0]));
			s3 = Matrix1[0][2] * (Matrix1[1][0] * (Matrix1[2][1] * Matrix1[3][3] - Matrix1[3][1] * Matrix1[2][3]) - Matrix1[1][1] * (Matrix1[2][0] * Matrix1[3][3] - Matrix1[2][3] * Matrix1[3][0]) + Matrix1[1][3] * (Matrix1[2][0] * Matrix1[3][1] - Matrix1[2][1] * Matrix1[3][0]));
			s4 = Matrix1[0][3] * (Matrix1[1][0] * (Matrix1[2][1] * Matrix1[3][2] - Matrix1[3][1] * Matrix1[2][2]) - Matrix1[1][1] * (Matrix1[2][0] * Matrix1[3][2] - Matrix1[2][2] * Matrix1[3][0]) + Matrix1[1][2] * (Matrix1[2][0] * Matrix1[3][1] - Matrix1[2][1] * Matrix1[3][0]));
			MatrixDet1 = s1 - s2 + s3 - s4;
			s1 = Matrix2[0][0] * (Matrix2[1][1] * (Matrix2[2][2] * Matrix2[3][3] - Matrix2[3][2] * Matrix2[2][3]) - Matrix2[1][2] * (Matrix2[2][1] * Matrix2[3][3] - Matrix2[2][3] * Matrix2[3][1]) + Matrix2[1][3] * (Matrix2[2][1] * Matrix2[3][2] - Matrix2[2][2] * Matrix2[3][1]));
			s2 = Matrix2[0][1] * (Matrix2[1][0] * (Matrix2[2][2] * Matrix2[3][3] - Matrix2[3][2] * Matrix2[2][3]) - Matrix2[1][2] * (Matrix2[2][0] * Matrix2[3][3] - Matrix2[2][3] * Matrix2[3][0]) + Matrix2[1][3] * (Matrix2[2][0] * Matrix2[3][2] - Matrix2[2][2] * Matrix2[3][0]));
			s3 = Matrix2[0][2] * (Matrix2[1][0] * (Matrix2[2][1] * Matrix2[3][3] - Matrix2[3][1] * Matrix2[2][3]) - Matrix2[1][1] * (Matrix2[2][0] * Matrix2[3][3] - Matrix2[2][3] * Matrix2[3][0]) + Matrix2[1][3] * (Matrix2[2][0] * Matrix2[3][1] - Matrix2[2][1] * Matrix2[3][0]));
			s4 = Matrix2[0][3] * (Matrix2[1][0] * (Matrix2[2][1] * Matrix2[3][2] - Matrix2[3][1] * Matrix2[2][2]) - Matrix2[1][1] * (Matrix2[2][0] * Matrix2[3][2] - Matrix2[2][2] * Matrix2[3][0]) + Matrix2[1][2] * (Matrix2[2][0] * Matrix2[3][1] - Matrix2[2][1] * Matrix2[3][0]));
			MatrixDet2 = s1 - s2 + s3 - s4;
			printf("첫 번째 행렬 행렬식 값 : %d\n", MatrixDet1);
			printf("두 번째 행렬 행렬식 값 : %d\n", MatrixDet2);
			break;
		case 't':
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					MatrixT1[j][i] = Matrix1[i][j];
					MatrixT2[j][i] = Matrix2[i][j];
				}
			}

			printf("1번째 전치행렬 \n");
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					printf(" %d ", MatrixT1[i][j]);
				}
				printf("\n");
			}
			printf("\n");
			printf("2번째 전치행렬 \n");
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					printf(" %d ", MatrixT2[i][j]);
				}
				printf("\n");
			}

			s1 = MatrixT1[0][0] * (MatrixT1[1][1] * (MatrixT1[2][2] * MatrixT1[3][3] - MatrixT1[3][2] * MatrixT1[2][3]) - MatrixT1[1][2] * (MatrixT1[2][1] * MatrixT1[3][3] - MatrixT1[2][3] * MatrixT1[3][1]) + MatrixT1[1][3] * (MatrixT1[2][1] * MatrixT1[3][2] - MatrixT1[2][2] * MatrixT1[3][1]));
			s2 = MatrixT1[0][1] * (MatrixT1[1][0] * (MatrixT1[2][2] * MatrixT1[3][3] - MatrixT1[3][2] * MatrixT1[2][3]) - MatrixT1[1][2] * (MatrixT1[2][0] * MatrixT1[3][3] - MatrixT1[2][3] * MatrixT1[3][0]) + MatrixT1[1][3] * (MatrixT1[2][0] * MatrixT1[3][2] - MatrixT1[2][2] * MatrixT1[3][0]));
			s3 = MatrixT1[0][2] * (MatrixT1[1][0] * (MatrixT1[2][1] * MatrixT1[3][3] - MatrixT1[3][1] * MatrixT1[2][3]) - MatrixT1[1][1] * (MatrixT1[2][0] * MatrixT1[3][3] - MatrixT1[2][3] * MatrixT1[3][0]) + MatrixT1[1][3] * (MatrixT1[2][0] * MatrixT1[3][1] - MatrixT1[2][1] * MatrixT1[3][0]));
			s4 = MatrixT1[0][3] * (MatrixT1[1][0] * (MatrixT1[2][1] * MatrixT1[3][2] - MatrixT1[3][1] * MatrixT1[2][2]) - MatrixT1[1][1] * (MatrixT1[2][0] * MatrixT1[3][2] - MatrixT1[2][2] * MatrixT1[3][0]) + MatrixT1[1][2] * (MatrixT1[2][0] * MatrixT1[3][1] - MatrixT1[2][1] * MatrixT1[3][0]));
			MatrixDet1 = s1 - s2 + s3 - s4;
			s1 = MatrixT2[0][0] * (MatrixT2[1][1] * (MatrixT2[2][2] * MatrixT2[3][3] - MatrixT2[3][2] * MatrixT2[2][3]) - MatrixT2[1][2] * (MatrixT2[2][1] * MatrixT2[3][3] - MatrixT2[2][3] * MatrixT2[3][1]) + MatrixT2[1][3] * (MatrixT2[2][1] * MatrixT2[3][2] - MatrixT2[2][2] * MatrixT2[3][1]));
			s2 = MatrixT2[0][1] * (MatrixT2[1][0] * (MatrixT2[2][2] * MatrixT2[3][3] - MatrixT2[3][2] * MatrixT2[2][3]) - MatrixT2[1][2] * (MatrixT2[2][0] * MatrixT2[3][3] - MatrixT2[2][3] * MatrixT2[3][0]) + MatrixT2[1][3] * (MatrixT2[2][0] * MatrixT2[3][2] - MatrixT2[2][2] * MatrixT2[3][0]));
			s3 = MatrixT2[0][2] * (MatrixT2[1][0] * (MatrixT2[2][1] * MatrixT2[3][3] - MatrixT2[3][1] * MatrixT2[2][3]) - MatrixT2[1][1] * (MatrixT2[2][0] * MatrixT2[3][3] - MatrixT2[2][3] * MatrixT2[3][0]) + MatrixT2[1][3] * (MatrixT2[2][0] * MatrixT2[3][1] - MatrixT2[2][1] * MatrixT2[3][0]));
			s4 = MatrixT2[0][3] * (MatrixT2[1][0] * (MatrixT2[2][1] * MatrixT2[3][2] - MatrixT2[3][1] * MatrixT2[2][2]) - MatrixT2[1][1] * (MatrixT2[2][0] * MatrixT2[3][2] - MatrixT2[2][2] * MatrixT2[3][0]) + MatrixT2[1][2] * (MatrixT2[2][0] * MatrixT2[3][1] - MatrixT2[2][1] * MatrixT2[3][0]));
			MatrixDet2 = s1 - s2 + s3 - s4;
			printf("첫 번째 전치 행렬 행렬식 값 : %d\n", MatrixDet1);
			printf("두 번째 전치 행렬 행렬식 값 : %d\n", MatrixDet2);
			break;
		case 'e':
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					Matrix1[i][j] = MatrixRest1[i][j];
					Matrix2[i][j] = MatrixRest2[i][j];
				}
			}
			Shape++;
			if (Shape == 1)
			{
				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						if (Matrix1[i][j] != 2)
							Matrix1[i][j] = 0;
						if (Matrix2[i][j] != 2)
							Matrix2[i][j] = 0;
					}
				}
			}
			else if (Shape == 2)
			{
				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						if (Matrix1[i][j] != 1)
							Matrix1[i][j] = 0;
						if (Matrix2[i][j] != 1)
							Matrix2[i][j] = 0;
					}
				}
			}
			else if (Shape == 3)
				Shape = 0;
			break;
		case 's':
			count = 0;
			for (int i = 0; i < 2; i++)
			{
				matrixnum[i] = random();
			}

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					for (int z = 0; z < 2; z++)
					{
						if (matrixnum[z] == count)
						{
							Matrix1[i][j] = 2;
							break;
						}
						else
							Matrix1[i][j] = rand() % 2;
					}
					count++;
				}
			}

			for (int i = 0; i < 2; i++)
			{
				matrixnum[i] = random();
			}
			count = 0;

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					for (int z = 0; z < 2; z++)
					{
						if (matrixnum[z] == count)
						{
							Matrix2[i][j] = 2;
							break;
						}
						else
							Matrix2[i][j] = rand() % 2;
					}
					count++;
				}
			}
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					MatrixRest1[i][j] = Matrix1[i][j];
					MatrixRest2[i][j] = Matrix2[i][j];
				}
			}
			break;
		case '1':
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					Matrix1[i][j] *= 1;
					Matrix2[i][j] *= 1;
				}
			}
			break;
		case '2':
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					Matrix1[i][j] *= 2;
					Matrix2[i][j] *= 2;
				}
			}
			break;
		case '3':
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					Matrix1[i][j] *= 3;
					Matrix2[i][j] *= 3;
				}
			}
			break;
		case '4':
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					Matrix1[i][j] *= 4;
					Matrix2[i][j] *= 4;
				}
			}
			break;
		case '5':
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					Matrix1[i][j] *= 5;
					Matrix2[i][j] *= 5;
				}
			}
			break;
		case '6':
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					Matrix1[i][j] *= 6;
					Matrix2[i][j] *= 6;
				}
			}
			break;
		case '7':
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					Matrix1[i][j] *= 7;
					Matrix2[i][j] *= 7;
				}
			}
			break;
		case '8':
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					Matrix1[i][j] *= 8;
					Matrix2[i][j] *= 8;
				}
			}
			break;
		case '9':
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					Matrix1[i][j] *= 9;
					Matrix2[i][j] *= 9;
				}
			}
			break;
		case 'q':
			exit(1);
			break;
		}
	}

}