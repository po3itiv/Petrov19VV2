// Hamilton.cpp: определяет точку входа для консольного приложения.

#define _CRT_SECURE_NO_WARNINGS

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <time.h>

// Максимальное количество вершин в графе
const int MAX_VERTEX = 100;

// Текущее число вершин
int cnt_vertex;
int cnt_vertex2;

// Матрица расстояний неориентированного графа
int mat[MAX_VERTEX][MAX_VERTEX];
int mat2[MAX_VERTEX][MAX_VERTEX];

// Массив для определения номера области связности для каждой вершины
int connectx[MAX_VERTEX];

// Количество областей связности
int cnt_connect;

// Максимальное число циклов
const int MAX_LOOP = 6000;

// Массив циклов
int* simple_loop[MAX_LOOP];

// Количество циклов
int cnt_loop;

int Mark[MAX_VERTEX];
int Vertex[MAX_VERTEX];

// Коды команд на выполнение
enum
{
	HELP,
	MATRIX,
	HAMILTON,
	RAND,
	MANUAL,
	LOAD,
	SAVE,
	EXIT
};

// Команды оператора
struct CODE
{
	int  code;
	const char* s;
};

struct CODE code[] =
{
	{ HELP,  "help" },
	{ MATRIX, "matrix" },
	{ HAMILTON, "hamilton" },
	{ RAND,  "rand" },
	{ MANUAL,  "manual" },
	{ LOAD,  "load" },
	{ SAVE,   "save" },
	{ EXIT,  "exit" },
	{ 0,     NULL }
};

// Строка с командой оператора
char buf[1024];

// Код команды
int command;

// Количество параметров в команде
int cnt;

// Параметр в виде числа
int num;

// Максимальное число параметров команды
const int MAX_P = 3;

// Массив указателей на параметры
const char* param[MAX_P];

// Контроль записи числа
bool test_num(const char* s)
{
	if (!isdigit(*s))
		return false;

	while (isdigit(*++s))
		;

	return *s == 0;
}

// Печать приглашения на ввод команды оператора,
// ввод команды и разбиение ее на параметры
// return false, если введенная строка пустая
// или число параметров слишком велико
// (в этом случае печатается сообщение об ошибке)
bool input_cmd(void)
{
	char delim[] = " \t\n", * txt, * word;
	int i;
	const char* s;

	// Приглашение и ввод
	printf("/");
	fgets(txt = buf, sizeof(buf) - 1, stdin);

	// Получаем параметры
	for (cnt = 0; (word = strtok(txt, delim)) != NULL; txt = NULL, ++cnt)
	{
		if (cnt == MAX_P)
		{
			printf("Команда содержит слишком много параметров\n");
			return false;
		}
		param[cnt] = word;
	}

	// Команда не введена?
	if (cnt == 0)
		return false;

	// Распознаем тип команды
	for (i = 0; (s = code[i].s) != NULL; ++i)
	{
		if (_stricmp(s, param[0]) == 0)
		{
			command = code[i].code;
			return true;
		}
	}

	printf("Неизвестная команда\n");
	return false;
}

// Разбор команды оператора
bool select_cmd(void)
{
	// Получить список параметров введенной команды
	if (!input_cmd())
		return false;

	// Контролируем число параметров
	switch (command)
	{

	case LOAD:
	case SAVE:
	case HAMILTON:
		if (cnt != 2) // Параметр -1 т.е. количество параметров не равно 1
		{
			printf("Ошибочно число параметров\n");
			return false;
		}
		return true;

	case RAND:
		if (cnt != 3)
		{
			printf("Ошибочно число параметров\n");
			return false;
		}
		return true;

	case MANUAL:
		if (cnt != 3)
		{
			printf("Ошибочно число параметров\n");
			return false;
		}
		return true;
	}

	if (cnt != 1)
	{
		printf("Ошибочно число параметров\n");
		return false;
	}

	return true;
}

// Ручной ввод графа
void manual_graph(void)
{
	int  i, n1, n2, v1, v2, v;
	char delim[] = " \t\n", * txt, * word;

	if (!test_num(param[1]))
	{
		printf("Количество вершин ошибочно\n");
		return;
	}
	if ((n1 = atoi(param[1])) < 3 || n1 > MAX_VERTEX)
	{
		printf("Количество вершин должно быть в диапазоне [3...%d]\n", MAX_VERTEX);
		return;
	}

	if (!test_num(param[2]))
	{
		printf("Количество ребер ошибочно\n");
		return;
	}
	if ((n2 = atoi(param[2])) < 3 || n2 > (n1 * (n1 - 1)) / 2)
	{
		printf("Количество ребер должно быть в диапазоне [3...%d]\n", (n1 * (n1 - 1)) / 2);
		return;
	}

	cnt_vertex = n1;
	memset(mat, 0, sizeof(mat));

	// Вводим ребра со стоимостью
	for (i = 0; i < n2;)
	{
		printf("Ребро и ее стоимость: ");
		fgets(txt = buf, sizeof(buf) - 1, stdin);

		// Получаем параметры
		for (cnt = 0; (word = strtok(txt, delim)) != NULL; txt = NULL, ++cnt)
		{
			if (cnt == 3)
			{
				++cnt;
				break;
			}
			param[cnt] = word;
		}

		if (cnt != 3)
		{
			printf("Ребро должно задаваться указанием двух вершин и ее стоимости\n");
			continue;
		}

		if (!test_num(param[0]) || (v1 = atoi(param[0])) < 1 || v1 > n1)
		{
			printf("Первая вершина ошибочна\n");
			continue;
		}
		if (!test_num(param[1]) || (v2 = atoi(param[1])) < 1 || v2 > n1)
		{
			printf("Вторая вершина ошибочна\n");
			continue;
		}
		if (v1 == v2)
		{
			printf("Вершины не должны совпадать\n");
			continue;
		}

		if (!test_num(param[2]) || (v = atoi(param[2])) < 1)
		{
			printf("Ошибочна стоимость ребра\n");
			continue;
		}

		// Устанавливаем симметрично вес ребра
		--v1;
		--v2;
		mat[v1][v2] = mat[v2][v1] = v;
		++i;
	}
}

// Ввод графа из файла
void load_graph(void)
{
	FILE* f;
	int  i, j;
	bool zero;

	if ((f = fopen(param[1], "r")) == NULL)
	{
		printf("Файл с описанием графа не найден\n");
		return;
	}

	if (fscanf(f, "%d", &cnt_vertex2) != 1)
	{
		printf("Ошибочно количество вершин\n");
		fclose(f);
		return;
	}

	if (cnt_vertex2 < 3 || cnt_vertex2 > MAX_VERTEX)
	{
		printf("Количество вершин должно быть в диапазоне [3...%d]\n", MAX_VERTEX);
		fclose(f);
		return;
	}

	// Вводим матрицу расстояний
	for (i = 0; i < cnt_vertex2; ++i)
	{
		for (j = 0; j < cnt_vertex2; ++j)
		{
			if (fscanf(f, "%d", mat2[i] + j) != 1)
			{
				printf("Ошибочно расстояние A[%d][%d]\n", i, j);
				fclose(f);
				return;
			}

			if (mat2[i][j] < 0)
			{
				printf("Отрицательное расстояние A[%d][%d]\n", i, j);
				fclose(f);
				return;
			}
		}
	}
	fclose(f);

	// Окончательный контроль матрицы расстояний
	zero = true;
	for (i = j = 0; i < cnt_vertex2; ++i)
	{
		if (mat2[i][i])
		{
			printf("Матрица расстояний должна содержать нулевую диагональ, A[%d][%d] != 0\n", i, i);
			return;
		}

		for (j = 0; j < cnt_vertex2; ++j)
		{
			if (mat2[i][j])
				zero = false;
			if (mat2[i][j] != mat2[j][i])
			{
				printf("Матрица расстояний должна быть симметричной, A[%d][%d] != A[%d][%d]\n", i, j, j, i);
				return;
			}
		}
	}

	if (zero)
	{
		printf("Матрица расстояний нулевая\n");
		return;
	}

	// Устанавливаем матрицу расстояний
	memcpy(mat, mat2, sizeof(mat2));
	cnt_vertex = cnt_vertex2;
}

// Вернуть true, если граф не задан
bool empty_graph(void)
{
	if (cnt_vertex == 0)
	{
		printf("Граф не задан\n");
		return true;
	}
	return false;
}

// Обход графа в глубину для присваивания всем вершинам
// номера области связности
void dfs_connect(int v)
{
	int i;

	// Помечаем текущую вершину как посещенную и принадлежащую cnt_connect-й компоненте связности
	connectx[v] = cnt_connect;

	// Перебираем все вершины смежные с v, которые еще не были посещены
	for (i = 0; i < cnt_vertex; ++i)
	{
		if (mat[v][i] != 0 && connectx[i] == 0)
		{
			// Повторяем алгоритм для i-й вершины
			dfs_connect(i);
		}
	}
}

// Определение компонент связности
void connected_parts(void)
{
	int i;

	// Номер очередной компоненты связности
	cnt_connect = 0;

	// Сброс номеров компонент связности
	memset(connectx, 0, sizeof(connectx));

	for (i = 0; i < cnt_vertex; ++i)
	{
		// Если вершина еще не была посещена, начинаем
		// из нее поиск новой компоненты связности
		if (connectx[i] == 0)
		{
			// Увеличиваем число областей связности
			++cnt_connect;

			// Просматриваем все вершины, достижимые из i-й
			dfs_connect(i);
		}
	}
 }

// Вернуть количество ребер
int get_cnt_edge(void)
{
	int i, j, m;

	for (i = m = 0; i < cnt_vertex; ++i)
	{
		for (j = 0; j < cnt_vertex; ++j)
		{
			if (mat[i][j] != 0)
				++m;
		}
	}

	return m;
}

// Вернуть true, если граф содержит достаточно ребер и односвязный
bool yes_loop(FILE* f)
{
	// А есть ли граф?
	if (empty_graph())
		return false;

	// Определение компонент связности
	connected_parts();
	if (cnt_connect != 1)
	{
		fprintf(f, "Граф не односвязный, областей связности = %d\n", cnt_connect);
		return false;
	}
	cnt_connect = 0;

	// Достаточно ли ребер для построения хотя бы одного цикла?
	if (get_cnt_edge() / 2 < 3)
	{
		fprintf(f, "Для цикла необходимо хотя бы 3 ребра\n");
		return false;
	}
 
	return true;
}

// Удалить циклы Гамильтона
void del_loop(void)
{
	int i;

	for (i = 0; i < cnt_loop; ++i)
		delete simple_loop[i];
}

bool first;

// Поиск Гамильтоновых циклов
// k - номер шага
void Hamilton(int k)
{
	int i, j, k1, k2, k3, k4, n, q, * adr;

	// Номер последней вершины
	i = Vertex[k - 1];	
	for (j = 0; j < cnt_vertex; ++j)
	{
		// Есть ребро?
		if (mat[i][j] != 0)
		{
			if (k == cnt_vertex && j == 0)
			{
				// Может быть этот цикл уже есть в каком-то виде?
				for (n = 0; n < cnt_loop; ++n)
				{
					// Находим совпадение по одной вершине
					adr = simple_loop[n];
					for (k1 = 0; Vertex[0] != adr[k1]; ++k1)
						;

					 

					// Есть совпадение всех вершин в прямом/обратном направлении?
					for (k3 = k1, k2 = 0; k2 < cnt_vertex; ++k2)
					{
						if (Vertex[k2] != adr[k3])
							break;
						if (k3 == 0)
							k3 = cnt_vertex - 1;
						else
							--k3;
					}
					if (k2 == cnt_vertex)
						break;

					// Есть совпадение всех вершин в обратном/прямом направлении?
					for (k3 = k1, k2 = 0, k4 = 0; k2 < cnt_vertex; ++k2)
					{
						if (Vertex[k4] != adr[k3++ % cnt_vertex])
							break;
						if (k4 == 0)
							k4 = cnt_vertex - 1;
						else
							--k4;
					}
					if (k2 == cnt_vertex)
						break;

					 
					if (k2 == cnt_vertex)
						break;
				}

				// Помещаем цикл в результат, если он не реверсно дубликатный
				if (n == cnt_loop)
				{
					if (cnt_loop == MAX_LOOP)
					{
						if (first)
						{
							printf("Количество циклов превысило %d\n", MAX_LOOP);
							first = false;
							return;
						}
					}
					simple_loop[cnt_loop] = new int[cnt_vertex];
					for (q = 0; q < cnt_vertex; ++q)
						simple_loop[cnt_loop][q] = Vertex[q];
					++cnt_loop;
				}
			}
			else if (Mark[j] == 0)
			{
				Vertex[k] = j;
				Mark[j] = 1;
				Hamilton(k + 1);
				Mark[j] = 0;
			}
		}
	}
}

// Печать Гамильтоновых циклов
// и выбор из них минимального
void print_hamilton(FILE* f, int v)
{
	int i, i2 = 0, j, k, k2, min = 0, v1, v2, s, ind = 0;
	int* adr;

	fprintf(f, "Гамильтоновы циклы графа для вершины %d:\n", v--);
	for (i = 0; i < cnt_loop; ++i)
	{
		// Находим позицию вершины в Гамильтоне
		adr = simple_loop[i];
		for (k = 0; adr[k] != v; ++k)
			;

		// Печатаем Гамильтон в прямом направлении
		// и определяем минимальный Гамильтон
		fprintf(f, "%3d) ", ++i2);
		fprintf(f, "%d", v + 1);
		v1 = v;
		for (j = s = 0; j < cnt_vertex; ++j)
		{
			fprintf(f, "-%d", (v2 = adr[(k + j + 1) % cnt_vertex]) + 1);
			s += mat[v1][v2];
			v1 = v2;
		}
		fprintf(f, "\n");

		if (min == 0 || min > s)
		{
			min = s;
			ind = i2;
		}

		// Печатаем Гамильтон в обратном направлении	
		fprintf(f, "%3d) ", ++i2);
		fprintf(f, "%d", v + 1);
		v1 = v;
		k2 = k;
		for (j = s = 0; j < cnt_vertex; ++j)
		{
			if (--k2 < 0)
				k2 = cnt_vertex - 1;
			fprintf(f, "-%d", adr[k2] + 1);
		}
		fprintf(f, "\n");
	}

	fprintf(f, "Цикл %d минимальной стоимости %d\n", ind, min);
}

void Hamilton()
{
	int i, v;
	int check = 0;
	int q = 0;
	int e=cnt_vertex/2;

	/* if (cnt_vertex % 2 == 1)
		e = cnt_vertex / 2 + 1;
	else
		e = cnt_vertex / 2; */

	for (int i = 0; i < cnt_vertex; i++)
	{
		q = 0;
		for (int j = 0; j < cnt_vertex; j++)
		{
			if (mat[i][j] != 0)
				q++;

		}
		if (q < e) {

			printf(" Граф не содержит Гамильтоновых циклов по Условию Дирака\n");
			return;
		}
    }
	 

	if (!yes_loop(stdout))
		return;

	if (!test_num(param[1]) || (v = atoi(param[1])) < 1 || v > cnt_vertex)
	{
		printf("Вершина ошибочна или вне диапазона [1...%d]\n", cnt_vertex);
		return;
	}

	first = true;
	cnt_loop = 0;
	for (i = 0; i < cnt_vertex; ++i)
		Mark[i] = 0;
	Mark[0] = 1;
	Hamilton(1);

	if (cnt_loop == 0)
		printf("Граф не содержит Гамильтоновых циклов\n");
	else
	{
		print_hamilton(stdout, v);
		del_loop();
	}
}

// Сохранение графа
void save_graph(void)
{
	FILE* f;
	int  i, j;

	if (empty_graph())
		return;

	if ((f = fopen(param[1], "w")) == NULL)
	{
		printf("Нельзя создать файл\n");
		return;
	}

	// Сохраняем количество вершин
	fprintf(f, "%d\n", cnt_vertex);

	// Построчно сохраняем матрицу смежности
	for (i = 0; i < cnt_vertex; ++i)
	{
		for (j = 0; j < cnt_vertex; ++j)
		{
			fprintf(f, "%d ", mat[i][j]);
		}
		fprintf(f, "\n");
	}
	// Сохраняем Гамильтоновы циклы
	fprintf(f, "\n");
	if (yes_loop(f))
	{
		first = true;
		cnt_loop = 0;
		for (i = 0; i < cnt_vertex; ++i)
			Mark[i] = 0;
		Mark[0] = 1;
		Hamilton(1);

		if (cnt_loop == 0)
			fprintf(f, "Граф не содержит Гамильтоновых циклов\n");
		else
		{
			for (i = 1; i <= cnt_vertex; ++i)
				print_hamilton(f, i);
			del_loop();
		}
	}

	fclose(f);
}

// Печать матрицы смежности
void print_matrix(void)
{
	int i, j, v;
	char txt[20];
	unsigned w;

	// А есть ли граф?
	if (empty_graph())
		return;

	// Определим максимальную стоимость
	for (i = v = 0; i < cnt_vertex; ++i)
	{
		for (j = 0; j < cnt_vertex; ++j)
		{
			if (mat[i][j] > v)
				v = mat[i][j];
		}
	}

	// Определим ширину максимального элемента
	w = sprintf(txt, "%d", v);
	printf("Матрица смежности\n");
	for (i = 0; i < cnt_vertex; ++i)
	{
		for (j = 0; j < cnt_vertex; ++j)
		{
			printf("%*d ", w, mat[i][j]);
		}
		printf("\n");
	}
}

// Создание случайного графа
void rand_graph(void)
{
	int i, j, v1, v2, n, n1, n2;

	if (!test_num(param[1]))
	{
		printf("Количество вершин ошибочно\n");
		return;
	}
	if ((n1 = atoi(param[1])) < 3 || n1 > MAX_VERTEX)
	{
		printf("Количество вершин должно быть в диапазоне [3...%d]\n", MAX_VERTEX);
		return;
	}


	if (!test_num(param[2]))
	{
		printf("Количество ребер ошибочно\n");
		return;
	}
	if ((n2 = atoi(param[2])) < 3 || n2 > (n1 * (n1 - 1)) / 2)
	{
		printf("Количество ребер должно быть в диапазоне [3...%d]\n", (n1 * (n1 - 1)) / 2);
		return;
	}

	cnt_vertex = n1;

	for (i = 0; i < 100; ++i)
	{
		memset(mat, 0, sizeof(mat));
		for (j = 0; j < n2; ++j)
		{
			for (;;)
			{
				v1 = rand() % n1;
				v2 = rand() % n1;
				if (v1 != v2 && mat[v1][v2] == 0)
				{
					mat[v1][v2] = mat[v2][v1] = 5 + rand() % 20;
					break;
				}
			}
		}

		// Если граф односвязный - завершаем генерацию
		connected_parts();
		if (cnt_connect == 1)
			break;
	} 

	
}

// Краткая справка
char help[] =
 
"\n"
"Help               - краткая справка\n"
"Load name          - загрузка графа из набора данных в файле с именем name\n"
"Save name          - сохранение графа в файле с именем name\n"
"Manual vertex edge - создание графа вводом с консоли (vertex вершины , edge ребер)\n"
"Rand vertex edge   - создание случайного графа (vertex вершин, edge ребер)\n"
"Matrix             - печать матрицы смежности графа\n"
"Hamilton vertex    - поиск Гамильтоновых циклов для вершины vertex\n"
"Exit               - завершение работы\n"
"\n";

int main()
{
	// Установить кодировку печатаемых символов
	// для корректной печати и ввода русского текста
	SetConsoleOutputCP(1251);

	// Инициализация датчика случайных чисел
	srand((unsigned)time(NULL));

	// Печать справки
	system("color 5F");
	printf(help);

	// Обработка команд
	for (;;)
	{
		// Введенная команда ошибочна?
		if (!select_cmd())
			continue;

		// Выполняем команду
		switch (command)
		{

			// Завершение выполнения программы
		default:
			return 0;

			// Помощь
		case HELP:
			printf(help);
			continue;

			// Печать матрицы смежности
		case MATRIX:
			print_matrix();
			continue;

			// Поиск Гамильтоновых циклов
		case HAMILTON:
			Hamilton();
			continue;

			// Получить описание графа из файла
		case LOAD:
			load_graph();
			continue;

			// Получить описание графа с консоли
		case MANUAL:
			manual_graph();
			continue;

			// Сохранить граф в файле
		case SAVE:
			save_graph();
			continue;

			// Создать случайный граф
		case RAND:
			rand_graph();
		}
	}
}



