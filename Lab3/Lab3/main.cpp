#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <locale.h>

#include "adjacency_lists.h"
#include "Zad4.h"

void zad1();
void zad2();
void zad3();
void zad4();

#define INFTY INT_MAX
int **M1, **M2, **M3;
int **m, **m2;

int N = 5;


void main() {

	zad1();
	
	
	zad2();
	adjacency_list(N, M1, M2);

	zad3();
	zad3_V2(N);

	zad4();


	for (int i = N; i > 0; i--) {
		free(m[i]);

	} 

	free(m);

	for (int i = N - 1; i > 0; i--) { // �������� ������
		free(M1[i]);
		free(M2[i]);


	}
	free(M1);
	free(M2);


	for (int i = N - 2; i > 0; i--) {
		free(m2[i]);

	}

	free(m2); 

	getch();

}

void zad1() {

	setlocale(LC_ALL, "russian");

	printf("\n ������� ������ ������� N*N: ");
	scanf("%d", &N);

	M1 = (int**)malloc(N * sizeof(int *));
	for (int i = 0; i < N; i++)
	{
		M1[i] = (int*)malloc(N * sizeof(int));
	}

	M2 = (int**)malloc(N * sizeof(int *));
	for (int i = 0; i < N; i++)
	{
		M2[i] = (int*)malloc(N * sizeof(int));
	}


	srand(time(NULL));
	for (int i = 0; i < N; i++) // ��������� ������� M1
	{
		M1[i][i] = 0;

		for (int j = i + 1; j < N; j++)
		{

			M1[i][j] = rand() % 2;
			M1[j][i] = M1[i][j];


		}
	}

	for (int i = 0; i < N; i++) // ��������� ������� M2
	{
		M2[i][i] = 0;

		for (int j = i + 1; j < N; j++)
		{

			M2[i][j] = rand() % 2;
			M2[j][i] = M2[i][j];


		}
	}


	printf("\n 1. ����� ��������������� ������ ��������� ����������������� ������\n ");

	for (int i = 0; i < N; i++) { // ����� ������ ���������

		printf("\n ");

		for (int j = 0; j < N; j++) {
			printf("%d", M1[i][j]);
		}


	}

	printf("\n ");

	for (int i = 0; i < N; i++) {

		printf("\n ");

		for (int j = 0; j < N; j++) {
			printf("%d", M2[i][j]);
		}


	}


	getch();
}

void zad2()
{


	setlocale(LC_ALL, "russian");

	int c = 0, c2 = 0, bolsh = 0, mensh = 0;

	m = (int**)malloc((N + 1) * sizeof(int *)); // ������������ ������� ��� ��������������
	for (int i = 0; i < (N + 1); i++)
	{
		m[i] = (int*)malloc((N + 1) * sizeof(int));
	}

	m2 = (int**)malloc((N - 1) * sizeof(int *)); // ����������� ������� 
	for (int i = 0; i < (N - 1); i++)
	{
		m2[i] = (int*)malloc((N - 1) * sizeof(int));
	}




	printf("\n\n 2. ����� ������� ������ ������� ������������?\n");
	printf(" ");
	scanf("%d %d", &c, &c2);

	c = c - 1;
	c2 = c2 - 1;

	int i1 = 0, j = 0, j1 = 1, sch = 0;


	for (int i = 0; i < N; i++) // ���������� ������� ��� �������������� ���������� ������
	{
		for (int j = 0; j < N; j++)
		{
			m[i][j] = M2[i][j];
		}
	}


	for (int i = 0; i < N; i++) // ��������������
	{

		if ((bolsh + 1) >= N)
			break;

		if (i == 0)
		{
			for (int j = 0; j < N; j++)
			{
				if (c < c2)
				{
					m[c][j] = m[c][j] || m[c2][j]; // ���� ������ �������� ������ �������
					m[j][c] = m[c][j];				// ������������ ������� �� ������� � ������
					bolsh = c2;
					m[c][c] = 1;						// ������������� ����� ����� � �����

				}

				else
				{
					m[c2][j] = m[c][j] || m[c2][j]; // ����� ��������
					m[j][c2] = m[c2][j];
					bolsh = c;
					m[c2][c2] = 1;

				}
			}
		}


		else
		{


			for (i1 = bolsh; j < N; j++) // ������� � ������� ������ ��������� ������
			{

				m[i1][j] = m[i1 + 1][j];

			}

			j = bolsh;

			for (i1 = 0; i1 < N; i1++) // ������� � ������� ������� ���������� �������
			{

				m[i1][j] = m[i1][j + 1];

			}
			j = 0;

			bolsh++; // � ��� �� ������
		}
	}



	for (int i = 0; i < (N - 1); i++) // ������� ����������������� ������� � �����������
	{
		for (j = 0; j < (N - 1); j++)
		{
			m2[i][j] = m[i][j];
		}
	}


	for (int i = 0; i < (N - 1); i++) // �����
	{

		printf("\n ");

		for (int j = 0; j < (N - 1); j++)
		{
			printf("%d", m2[i][j]);
		}

	}


	//////////////////////////////////////////////////////////////////

	printf("\n\n 2. ����� ����� ������ ������� �������?\n");
	printf(" ");
	scanf("%d %d", &c, &c2);

	c = c - 1;
	c2 = c2 - 1;
	bolsh = 0;
	j = 0;

	if (M2[c][c2] == 0)

		printf("\n ������� ����� �����������. ��� �����.");

	else {


		for (int i = 0; i < N; i++) // �� ������� �����
		{
			for (int j = 0; j < N; j++)
			{
				m[i][j] = M2[i][j];
			}
		}


		for (int i = 0; i < N; i++)
		{

			if ((bolsh + 1) >= N)
				break;

			if (i == 0)
			{
				for (int j = 0; j < N; j++)
				{
					if (c < c2)
					{
						m[c][j] = m[c][j] || m[c2][j];
						m[j][c] = m[c][j];
						bolsh = c2;
						m[c][c] = 0; // �� ��� ����� � �����

					}

					else
					{
						m[c2][j] = m[c][j] || m[c2][j];
						m[j][c2] = m[c2][j];
						bolsh = c;
						m[c2][c2] = 0;

					}
				}
			}


			else
			{


				for (i1 = bolsh; j < N; j++)
				{

					m[i1][j] = m[i1 + 1][j];

				}

				j = bolsh;

				for (i1 = 0; i1 < N; i1++)
				{

					m[i1][j] = m[i1][j + 1];

				}
				j = 0;

				bolsh++;
			}
		}



		for (int i = 0; i < (N - 1); i++)
		{
			for (j = 0; j < (N - 1); j++)
			{
				m2[i][j] = m[i][j];
			}
		}


		for (int i = 0; i < (N - 1); i++)
		{

			printf("\n ");

			for (int j = 0; j < (N - 1); j++)
			{
				printf("%d", m2[i][j]);
			}

		}
	}

	///////////////////////////////////////////////////

	int N2 = N + 1;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			m[i][j] = M2[i][j];
		}
	}

	for (int i = 0; i < N2; i++) // ���������� ������ ����� �������
	{
		for (int j = 0; j < N2; j++)
		{
			if (m[i][j] < 0 || m[i][j] > 1)
				m[i][j] = 0;
		}
	}

	printf("\n\n 2. ����� ������� ������ ������� ���������?\n");
	printf(" ");
	scanf("%d", &c);

	c = c - 1;
	int i = c;
	for (; i < N2; i++) // � ����� ����������� ������� �������
	{						// ��������� ��� "1" � ����� �������
		if (m[c][i] == 1)
		{
			m[N2 - 1][i] = m[i][N2 - 1] = 1; //��������� "1" ����������� � ����� �������
			m[c][i] = m[i][c] = 0;			// ������ ���� ���������

		}
		else
			m[N2 - 1][i] = m[i][N2 - 1] = 0;
	}


	m[N2 - 1][c] = m[c][N2 - 1] = 1; // ��������� ����� ������� �� ������

	for (int i = 0; i < N2; i++) // �����
	{

		printf("\n ");

		for (int j = 0; j < N2; j++)
		{
			printf("%d", m[i][j]);
		}

	}

	getch();
}

void zad3()
{


	setlocale(LC_ALL, "russian");

	/*int m[5][5] = { { 0,1,0,0,1 },{ 1,0,1,1,1 },{ 0,1,0,1,1 },{ 0,1,1,0,0 },{ 1,1,1,0,0 } };
	int m2[5][5] = { { 0,1,0,0,1 },{ 1,0,1,1,1 },{ 0,1,0,1,1 },{ 0,1,1,0,0 },{ 1,1,1,0,0 } };
	int m3[5][5] = { { 0,1,0,0,1 },{ 1,0,1,1,1 },{ 0,1,0,1,1 },{ 0,1,1,0,0 },{ 1,1,1,0,0 } };*/


	printf("\n\n 3. ����������� ������ 1 � 2\n"); // ����� ���������� "���" ����������

	for (int i = 0; i < N; i++)
	{
		printf("\n ");
		for (int j = 0; j < N; j++)
		{
			m[i][j] = M1[i][j] || M2[i][j];
			printf("%d", m[i][j]);
		}
	}

	printf("\n\n 3. ����������� ������ 1 � 2\n"); // ����� ���������� "�" ������� �����������

	for (int i = 0; i < N; i++)
	{
		printf("\n ");
		for (int j = 0; j < N; j++)
		{
			m[i][j] = M1[i][j] & M2[i][j];
			printf("%d", m[i][j]);
		}
	}

	printf("\n\n 3. ��������� ����� ������ 1 � 2\n"); // ����� "����������� ���" ������� ��������� �����
													  // 1 ^ 1 = 0
	for (int i = 0; i < N; i++)
	{
		printf("\n ");
		for (int j = 0; j < N; j++)
		{
			m[i][j] = M1[i][j] ^ M2[i][j];
			printf("%d", m[i][j]);
		}
	}

	getch();
}






