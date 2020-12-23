#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <conio.h>
#include <windows.h>

int compare(const void* x1, const void* x2);
void shell(int* items, int count);
void qs(int* items, int left, int right);

void zapolnenie_um(int* a, int* b, int* c, int kolvo);
void zapolnenie_rand(int* a, int* b, int* c, int kolvo);
void zapolnenie_uv(int* a, int* b, int* c, int kolvo);
void zapolnenie_uv_um(int* a, int* b, int* c, int kolvo);

int zad1(void);

//int a[2000][2000], b[2000][2000], c[2000][2000];
FILE* file;
int main(void)
{
	setlocale(LC_ALL, "russian");
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);

	if
		((file = fopen("../../10000years.txt", "r")) == 0)
		file = fopen("../../10000years.txt", "w");

	else
		file = fopen("../../10000years.txt", "a");

	int* items, count = 10000, left = 0, right;
	int kursor;
	printf("\n �������� �������: \n");
	printf(" 1 - ������� 1\n");
	printf(" 2 - ������� 2\n");
	fprintf(file,"\n �������� �������: \n");
	fprintf(file," 1 - ������� 1\n");
	fprintf(file," 2 - ������� 2\n");
	kursor = _getch();
	
	if (kursor == 49)
	{
		fprintf(file, "\n <1>\n");
		zad1();
	}

	if (kursor == 50)
	{
		fprintf(file, "\n <2>\n");
		if (kursor == 49)
		{
			zad1();
		}
		int kolvo = 0;
		int* a2, * b2, * c2;
		printf("\n ������� ���-�� ���������: ");
		scanf("%d", &kolvo);
		fprintf(file, "\n ������� ���-�� ���������: %d", kolvo);
		count = kolvo;
		right = kolvo - 1;
		a2 = (int*)malloc(kolvo * sizeof(int));
		b2 = (int*)malloc(kolvo * sizeof(int));
		c2 = (int*)malloc(kolvo * sizeof(int));

		printf("\n ������� ������ ���������� ���������: \n");
		printf(" 1 - ���������\n");
		printf(" 2 - �� �������� � ��������\n");
		printf(" 3 - �� �������� � ��������\n");
		printf(" 4 - ������� �������������, ����� �����������\n\n");
		fprintf(file,"\n ������� ������ ���������� ���������: \n");
		fprintf(file," 1 - ���������\n");
		fprintf(file," 2 - �� �������� � ��������\n");
		fprintf(file," 3 - �� �������� � ��������\n");
		fprintf(file," 4 - ������� �������������, ����� �����������\n\n");
		kursor = _getch();
	
		switch (kursor) {
		case 49:
			fprintf(file, " <1>\n\n");
			zapolnenie_rand(a2, b2, c2, kolvo);
			break;

		case 50:
			fprintf(file, " <2>\n\n");
			zapolnenie_uv(a2, b2, c2, kolvo);
			break;

		case 51:
			fprintf(file, " <3>\n\n");
			zapolnenie_um(a2, b2, c2, kolvo);
			break;

		case 52:
			fprintf(file, " <4>\n\n");
			zapolnenie_uv_um(a2, b2, c2, kolvo);
		}
		shell(a2, count);

		clock_t start2 = clock();
		qs(b2, left, right);
		clock_t end2 = clock();
		int result2 = end2 - start2;
		printf("�����, ����������� �� ���������� ������� ����������: %d \n", result2);
		fprintf(file,"�����, ����������� �� ���������� ������� ����������: %d \n", result2);

		clock_t start3 = clock();
		qsort(c2, kolvo, sizeof(int), compare);
		clock_t end3 = clock();
		int result3 = end3 - start3;
		printf("�����, ����������� �� ���������� ����������� �������� qsort: %d \n", result3);
		fprintf(file, "�����, ����������� �� ���������� ����������� �������� qsort: %d \n", result3);

		free(a2);
		free(b2);
		free(c2);
		fprintf(file, "\n-------------------------------------------------\n");
		fclose(file);
	}
	_getch();
	return(0);
}


int zad1(void)
{

	
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	int kolvo = 0;
	printf("\n ������� ���-�� ��������� (x*x): ");

	scanf("%d", &kolvo);
	fprintf(file,"\n ������� ���-�� ��������� (x*x): %d", kolvo);
	int** a1 = (int**)malloc(kolvo * sizeof(int)); // ��������� ������ ��� ��������� �� ������
	for (int i = 0; i < kolvo; i++)
		a1[i] = (int*)malloc(kolvo * sizeof(int)); // ��������� ������ ��� �������� �����

	int** b1 = (int**)malloc(kolvo * sizeof(int));
	for (int i = 0; i < kolvo; i++)
		b1[i] = (int*)malloc(kolvo * sizeof(int));

	int** c1 = (int**)malloc(kolvo * sizeof(int));
	for (int i = 0; i < kolvo; i++)
		c1[i] = (int*)malloc(kolvo * sizeof(int));

	clock_t start1 = clock(); // ��������� ���������� ��� ����������� ������� ����������

	int i = 0, j = 0, r, elem_c;

	srand(time(NULL)); // �������������� ��������� ���������� ��������� �����
	while (i < kolvo)
	{
		while (j < kolvo)
		{
			a1[i][j] = rand() % 100 + 1; // ��������� ������ ���������� �������
			j++;
		}
		i++;
		j = 0;
	}


	srand(time(NULL)); // �������������� ��������� ���������� ��������� �����
	i = 0; j = 0;
	while (i < kolvo)
	{
		while (j < kolvo)
		{
			b1[i][j] = rand() % 100 + 1; // ��������� ������ ���������� �������
			j++;
		}
		i++;
		j = 0;
	}

	clock_t start2 = clock();
	for (i = 0; i < kolvo; i++)
	{
		for (j = 0; j < kolvo; j++)
		{
			elem_c = 0;
			for (r = 0; r < kolvo; r++)
			{
				elem_c = elem_c + a1[i][r] * b1[r][j];
				c1[i][j] = elem_c;
			}
		}



	}
	int end = clock();
	int result1 = end - start1;
	int result2 = end - start2;
	printf(" �����, ����������� �� ���������� ���� ���������: %d \n", result1);
	printf(" �����, ����������� �� ���������� �������� �����: %d \n", result2);
	fprintf(file," �����, ����������� �� ���������� ���� ���������: %d \n", result1);
	fprintf(file," �����, ����������� �� ���������� �������� �����: %d \n", result2);

	for (i = kolvo - 1; i > 0; i--) {
		free(a1[i]);
		free(b1[i]);
		free(c1[i]);
	}
	free(a1);
	free(b1);
	free(c1);
	fclose(file);
	return(0);
}

void shell(int* items, int count)
{
	
	clock_t start1 = clock();
	int i, j, gap, k;
	int x, a[5];

	a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;

	for (k = 0; k < 5; k++) {
		gap = a[k];
		for (i = gap; i < count; ++i) {
			x = items[i];
			for (j = i - gap; (x < items[j]) && (j >= 0); j = j - gap)
				items[j + gap] = items[j];
			items[j + gap] = x;
		}
	}
	clock_t end1 = clock();
	int result1 = end1 - start1;
	printf("�����, ����������� �� ���������� ���������� �����: %d \n", result1);
	fprintf(file, "�����, ����������� �� ���������� ���������� �����: %d \n", result1);
}

void qs(int* items, int left, int right) //����� �������: qs(items, 0, count-1);
{
	int i, j;
	int x, y;


	setlocale(LC_ALL, "russian");
	i = left; j = right;

	/* ����� ���������� */
	x = items[(left + right) / 2];

	do {
		while ((items[i] < x) && (i < right)) i++;
		while ((x < items[j]) && (j > left)) j--;

		if (i <= j) {
			y = items[i];
			items[i] = items[j];
			items[j] = y;
			i++; j--;
		}
	} while (i <= j);

	if (left < j)
		qs(items, left, j);
	if (i < right)
		qs(items, i, right);

}

int compare(const void* x1, const void* x2) // ������� ��������� ��������� �������
{
	return (*(int*)x1 - *(int*)x2); // ���� ��������� ��������� ����� 0, �� ����� �����, < 0: x1 < x2; > 0: x1 > x2
}

void zapolnenie_um(int* a, int* b, int* c, int kolvo) {

	int sch = 3330000;

	for (int i = 0; i < kolvo; i++) {

		a[i] = b[i] = c[i] = sch - 250;
		sch = sch - 333;

	}

}

void zapolnenie_rand(int* a, int* b, int* c, int kolvo) {

	int i = 0;

	srand(time(NULL)); // �������������� ��������� ���������� ��������� �����
	while (i < kolvo)
	{
		a[i] = b[i] = c[i] = rand() % 100000 + 1; // ��������� ������ ���������� �������

		i++;
	}
}

void zapolnenie_uv(int* a, int* b, int* c, int kolvo) {

	int i = 0;
	int cplus = 0;
	int sum = 10;
	srand(time(NULL)); // �������������� ��������� ���������� ��������� �����
	while (i < kolvo)
	{

		a[i] = b[i] = c[i] = rand() % 10 + cplus; // ��������� ������ ���������� �������
		i++;
		cplus = cplus + 10;

	}
}

void zapolnenie_uv_um(int* a, int* b, int* c, int kolvo) {

	int i = 0;
	int cplus = 0;
	int sum = 10;
	srand(time(NULL)); // �������������� ��������� ���������� ��������� �����
	while (i < kolvo / 2)
	{

		a[i] = b[i] = c[i] = rand() % 10 + cplus; // ��������� ������ ���������� �������
		i++;
		cplus = cplus + 10;


	}

	int sch = cplus;

	for (; i < kolvo; i++) {

		a[i] = b[i] = c[i] = sch - 4;
		sch = sch - 10;

	}

}