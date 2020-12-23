#include <vector>
#include <iostream>
#include <algorithm>

void zad2_V2(int N, int **M2);
void zad3_V2(int N);

using Edge = int; // ����� - ����� �����, �����������, ���� ����
using Vertex = std::vector<Edge>; // ������� - ����� ����
using Graph = std::vector<Vertex>; // ���� - ����� ������

Graph g1, g2, g3, g4;

void adjacency_list(int N, int **M1, int **M2)
{
	

	g1.resize(N); // ������ ������ �����
	for (int i = 0; i < N; i++) // ���������� ���������������� ���������
	{
		for (int j = 0; j < N; j++)
		{
			if (M1[i][j] == 1)
				g1[i].push_back(j);
		}
	}

	g2.resize(N);
	for (int i = 0; i < N; i++) 
	{
		for (int j = 0; j < N; j++)
		{
			if (M2[i][j] == 1)
				g2[i].push_back(j);
		}
	}

	std::cout << "\n\n";
	std::cout << " ���� (1)\n";

	for (int i = 0; i < g1.size(); i++) // ����� ������
	{
		std::cout << "  " << i + 1 << " : ";
		for (int j = 0; j < g1[i].size(); j++)
		{
			std::cout << g1[i][j] + 1 << " ";
		}

		std::cout << "\n";
	}
	
	std::cout << "\n\n";
	std::cout << " ���� (2)\n";

	for (int i = 0; i < g2.size(); i++) // ����� ������
	{
		std::cout <<"  " << i + 1 << " : ";
		for(int j = 0; j < g2[i].size(); j++) 
		{
			std::cout << g2[i][j] + 1 << " ";
		}
		
		std::cout << "\n";
	}

	zad2_V2(N, M2);


}

void zad2_V2(int N, int **M2)
{
	//int m[5][5] = { { 0,0,0,1,1 },{ 0,0,1,1,1 },{ 0,1,0,1,1 },{ 1,1,1,0,0 },{ 1,1,1,0,0 } };
	int c, c2;

	int m[7][7] = { { 0,0,1,1,0, 0 , 0 },{ 0,0,1,1,0, 1 , 1 },{ 1,1,0,1,0, 1 , 0 },{ 1,1,1,0,0, 0 , 1 },{ 0,0,0,0,0, 1 , 1 } ,{ 0,1,1,0,1, 0 , 0 } ,{ 0,1,0,1,1, 0 , 0 } };

	g3.resize(N);

	for (int i = 0; i < N; i++) // ��������� ����
	{
		for (int j = 0; j < N; j++)
		{
			if (M2[i][j] == 1)
				g3[i].push_back(j);
		}
	}


	std::cout << "\n\n 2*. ����� ������� ������� ����� ������������?\n";
	std::cout << " ";
	std::cin >> c;
	std::cin >> c2;

	c--;  c2--;
	int bolsh, mensh, bolsh2;

	if (c > c2) // ���������� ������ � ������� �������
	{
		bolsh = c;
		bolsh2 = c;
		mensh = c2;
	}

	else
	{
		bolsh = c2;
		bolsh2 = c2;
		mensh = c;
	}

	int x1 = 0;
	int x2 = 0;
	int x3 = 0;
	int x4 = 0;
	int x5 = 0;



	for (int i = 0; i < g3.size(); i++) // ��������������
	{


		if (i == 0)
		{

			g3[mensh].push_back(mensh); // ������������� ����� ����� � �����

			for (int j = 0; j < g3[bolsh].size(); j++)
			{
				x1 = 0;

				for (int j2 = 0; j2 < g3[mensh].size(); j2++)
				{

					if (g3[bolsh][j] == mensh)
					{
						x1 = 1; // ���� � ������� ������� ���� ����� � �������
						break; // ����������
					}

					if ((g3[bolsh][j] == g3[mensh][j2]) && (g3[bolsh][j] != mensh))
					{
						x1 = 1; // ������� ������� ����� � ���� �������
						break;
					}
				}

				if (x1 == 1) // ���� ���� ����� ���� - ����������
					continue;

				else
				{
					x2 = g3[bolsh][j];
					g3[mensh].push_back(x2); // ����� ��������� ����� �����

					for(int j2 = 0; j2 < g3[x2].size(); j2++)
					{
						if (g3[x2][j2] == bolsh2)
							g3[x2][j2] = mensh;
					}

				}

			}
		}


		else

		{
			if ((bolsh + 1) < N)
			{

				x1 = g3[bolsh + 1].size();
				g3[bolsh].resize(x1); // ��������� ������
				g3[bolsh] = g3[bolsh + 1]; // ��������� �������
				bolsh++;
			}


		}

		for (int j = 0; j < g3[i].size(); j++)
		{
			if (g3[i][j] == bolsh2)
				g3[i][j] = mensh;
		}



	}
	g3[N - 1].clear();
	g3.resize(N - 1); // ��������� ������

	for (int i = 0; i < g3.size(); i++) // ����������
	{
		sort(g3[i].begin(), g3[i].end());
	}

	for (int i = 0; i < g3.size(); i++) // �������� �������� ������
	{
		for (int j = 0; j < g3[i].size(); j++)
		{

			if (g3[i][j] >= bolsh2)
			{
				g3[i][j]--;

			}

		}
	}

	x2 = 0;

	for (int i = 0; i < g3.size(); i++) // ����������� �������
	{

		for (int j = 0; j < g3[i].size(); j++)
		{
			if ((j + 1) >= g3[i].size())
				break;

			if (g3[i][j] == g3[i][j + 1]) // ���� ���� 2 ���� �� ����� ������� � ������ �������
			{
				g3[i][j + 1] = (N + 5); // ������� �� ������� �����

			}

		}

		sort(g3[i].begin(), g3[i].end()); // ���������

		for (int j = 0; j < g3[i].size(); j++)
		{
			if (g3[i][j] > N) // ������� ���������� ���������� ����
				x2++;

		}

		x1 = g3[i].size();
		g3[i].resize(x1 - x2); // ������� ��

		x2 = 0;

	}


	std::cout << "\n";

	for (int i = 0; i < g3.size(); i++) // ����� ������
	{
		std::cout << "  " << i + 1 << " : ";
		for (int j = 0; j < g3[i].size(); j++)
		{
			std::cout << g3[i][j] + 1 << " ";
		}

		std::cout << "\n";
	}


	//////////////////////////////////////////////////////////
	g3.clear();
	g3.resize(N);

	for (int i = 0; i < N; i++) // ��������� ����
	{
		for (int j = 0; j < N; j++)
		{
			if (M2[i][j] == 1)
				g3[i].push_back(j);
		}
	}

	std::cout << "\n 2*. ����� ������� ������� ����� �������?\n ";
	std::cin >> c;
	std::cin >> c2;

	c--;  c2--;

	if (c > c2) // ���������� ������ � ������� �������
	{
		bolsh = c;
		bolsh2 = c;
		mensh = c2;
	}

	else
	{
		bolsh = c2;
		bolsh2 = c2;
		mensh = c;
	}

	x1 = 0;
	x2 = 0;

	for (int i = 0; i < g3[c].size(); i++)
	{
		if (g3[c][i] == c2)
		{
			x1 = 1; // �������� �� ������� ����� ����� ���������
			break;
		}
	}

	if (x1 == 0)
		printf("\n ������� ����� �����������. ��� �����.\n");

	else {

		for (int i = 0; i < g3.size(); i++) // ����������
		{


			if (i == 0)
			{


				for (int j = 0; j < g3[bolsh].size(); j++)
				{
					x1 = 0;

					for (int j2 = 0; j2 < g3[mensh].size(); j2++)
					{

						if (g3[bolsh][j] == mensh)
						{
							x1 = 1; // ���� � ������� ������� ���� ����� � �������
							break; // ����������
						}

						if ((g3[bolsh][j] == g3[mensh][j2]) && (g3[bolsh][j] != mensh))
						{
							x1 = 1; // ������� ������� ����� � ���� �������
							break;
						}
					}

					if (x1 == 1) // ���� ���� ����� ���� - ����������
						continue;

					else
					{
						x2 = g3[bolsh][j];
						g3[mensh].push_back(x2); // ����� ��������� ����� �����

						for (int j2 = 0; j2 < g3[x2].size(); j2++)
						{
							if (g3[x2][j2] == bolsh2)
								g3[x2][j2] = mensh;
						}

					}

				}
			}


			else

			{
				if ((bolsh + 1) < N)
				{

					x1 = g3[bolsh + 1].size();
					g3[bolsh].resize(x1); // ��������� ������
					g3[bolsh] = g3[bolsh + 1]; // ��������� �������
					bolsh++;
				}


			}

			for (int j = 0; j < g3[i].size(); j++)
			{

				if (g3[i][j] == bolsh2)
					g3[i][j] = mensh;
			}

		}
		g3[N - 1].clear();
		g3.resize(N - 1); // ��������� ������

		for (int i = 0; i < g3.size(); i++) // ����������
		{
			sort(g3[i].begin(), g3[i].end());
		}

		for (int i = 0; i < g3.size(); i++) // �������� �������� ������
		{
			for (int j = 0; j < g3[i].size(); j++)
			{

				if (g3[i][j] >= bolsh2)
				{
					g3[i][j]--;

				}

			}
		}

		
		x2 = 0;

		for (int i = 0; i < g3.size(); i++) // ����������� �������
		{

			for (int j = 0; j < g3[i].size(); j++)
			{
				
				if (g3[i][j] == i) // ���� ���� ���� � ����
					g3[i][j] = (N + 5); // �������
				
				if ((j + 1) >= g3[i].size())
					break;

				if (g3[i][j] == g3[i][j + 1]) // ���� ���� 2 ���� �� ����� ������� � ������ �������
				{
					g3[i][j + 1] = (N + 5); // ������� �� ������� �����

				}


			}

			sort(g3[i].begin(), g3[i].end()); // ���������

			for (int j = 0; j < g3[i].size(); j++)
			{
				if (g3[i][j] > N) // ������� ���������� ���������� ����
					x2++;

			}

			x1 = g3[i].size();
			g3[i].resize(x1 - x2); // ������� ��

			x2 = 0;

		}


		std::cout << "\n";

		for (int i = 0; i < g3.size(); i++) // ����� ������
		{
			std::cout << "  " << i + 1 << " : ";
			for (int j = 0; j < g3[i].size(); j++)
			{
				std::cout << g3[i][j] + 1 << " ";
			}

			std::cout << "\n";
		}

	}
	/////////////////////////////////////////////////////////////

	g3.clear();
	g3.resize(N + 1); // ����������� ������

	for (int i = 0; i < N; i++) // ��������� ����
	{
		for (int j = 0; j < N; j++)
		{
			if (M2[i][j] == 1)
				g3[i].push_back(j);
		}
	}

	std::cout << "\n 2*. ����� ������� ������� ����� ���������?\n ";
	std::cin >> c;
	c--;

	x1 = 0;



	g3[N].push_back(c); // ������������� ����� ����� ������� � �����������

	int j2 = 0;

	for (int i = 0; i < g3[c].size(); i++) // �����������
	{

		x2 = 0;

		if (g3[c][i] > c)
		{
			g3[N].push_back(g3[c][i]); // � ������������ ������������ ����������� ������� ���������
			x2 = g3[c][i]; // ������� ��������� �������
			x1++;

			for (int j = 0; j < g3[x2].size(); j++)
			{
				if (g3[x2][j] == c)
					g3[x2][j] = N; // ������ ����������� ������� �� �����

			}

		}

	}


	x2 = g3[c].size(); // x2 - ����������� ���������� ���� � ������ �������
	g3[c].resize(x2 - x1); // x1 - ���������� ���������� ����
	g3[c].push_back(N); // ������������� ����� ����� ������� � �����������

	for (int i = 0; i < g3.size(); i++) // ����������
	{
		sort(g3[i].begin(), g3[i].end());
	}

	std::cout << "\n";

	for (int i = 0; i < g3.size(); i++) // ����� ������
	{
		std::cout << "  " << i + 1 << " : ";
		for (int j = 0; j < g3[i].size(); j++)
		{
			std::cout << g3[i][j] + 1 << " ";
		}

		std::cout << "\n";
	}



}

void zad3_V2(int N)
{
	g3 = g1;
	g4 = g2;

	int i2 = 0;
	int x1 = 0;
	int x2 = 0;

	
	for (int i = 0; i < g3.size(); )
	{
		
		sort(g4[i].begin(), g4[i].end()); // ���������

		if (i2 == g3[i].size()) // ���� ���� ���������� ��� ������
		{
			i++; // ��������� �� ���������
			i2 = 0;
			continue;

		}
		
		x1 = 0;

		for (int j = 0; j < g4[i].size(); j++)
		{
			if (g3[i][i2] == g4[i][j])
			{
				x1 = 1;
				i2++;
				break;
				

			}
		}

		if (x1 == 1) // ���� ���� ����� ���� - ����������
			continue;

		else
		{
			g4[i].push_back(g3[i][i2]); // ����� ��������� ����� �����
			i2++;

		}

	}


	printf("\n\n\n 3*. ����������� ������ 1 � 2\n");

	for (int i = 0; i < g4.size(); i++) // ����� ������
	{
		std::cout << "  " << i + 1 << " : ";
		for (int j = 0; j < g4[i].size(); j++)
		{
			std::cout << g4[i][j] + 1 << " ";
		}

		std::cout << "\n";
	}
	
	/////////////////////////////////////////////////

	g3 = g1;
	g4 = g2;

	for (int i = 0; i < g3.size(); )
	{

		//sort(g4[i].begin(), g4[i].end()); // ���������

		if (i2 == g3[i].size()) // ���� ���� ���������� ��� ������
		{
			i++; // ��������� �� ���������
			i2 = 0;
			continue;

		}

		x1 = 0;

		for (int j = 0; j < g4[i].size(); j++)
		{
			if (g3[i][i2] == g4[i][j])
			{
				x1 = 1;
				i2++;
				break;


			}
		}

		if (x1 == 1) // ���� ���� ����� ���� - ����������
			continue;

		else
		{
			g3[i][i2] = (N+5); // ����� ������� �����
			i2++;

		}

	}

	x2 = 0;

		for (int i = 0; i < g3.size(); i++) // ����������� ������������ ����
		{


			sort(g3[i].begin(), g3[i].end()); // ���������

			for (int j = 0; j < g3[i].size(); j++)
			{
				if (g3[i][j] > N) // ������� ���������� ���������� ����
					x2++;

			}

			x1 = g3[i].size();
			g3[i].resize(x1 - x2); // ������� ��

			x2 = 0;

		}

	
		printf("\n\n 3*. ����������� ������ 1 � 2\n");

		for (int i = 0; i < g3.size(); i++) // ����� ������
		{
			std::cout << "  " << i + 1 << " : ";
			for (int j = 0; j < g3[i].size(); j++)
			{
				std::cout << g3[i][j] + 1 << " ";
			}

			std::cout << "\n";
		}

		/////////////////////////////////////////////////

		g3 = g1;
		g4 = g2;

		i2 = 0;

		for (int i = 0; i < g3.size(); )
		{

			//sort(g4[i].begin(), g4[i].end()); // ���������

			if (i2 == g3[i].size()) // ���� ���� ���������� ��� ������
			{
				i++; // ��������� �� ���������
				i2 = 0;
				continue;

			}

			x1 = 0;

			for (int j = 0; j < g4[i].size(); j++)
			{
				if (g3[i][i2] == g4[i][j])
				{
					g4[i][j] = (N + 5); // ���� ���� ����� ����� ������� ��� �� ����� ������
					x1 = 1;
					break;


				}
			}

			if (x1 == 0) 
			{		// ���� ��� ������ ����� - ����������

				i2++;
				continue;
			}

			else
			{
				g3[i][i2] = (N + 5); // ����� ������� �����
				i2++;
				
			}

		}

		x2 = 0;


		for (int i = 0; i < g3.size(); i++) // ����������� ������������ �����
		{


			sort(g3[i].begin(), g3[i].end()); // ���������

			for (int j = 0; j < g3[i].size(); j++)
			{
				if (g3[i][j] > N) // ������� ���������� ���������� ����
					x2++;

			}

			x1 = g3[i].size();
			g3[i].resize(x1 - x2); // ������� ��

			x2 = 0;

		}
		
		
		x2 = 0;
		
		for (int i = 0; i < g4.size(); i++) // ����������� ���� 2
		{


			sort(g4[i].begin(), g4[i].end()); // ���������

			for (int j = 0; j < g4[i].size(); j++)
			{
				if (g4[i][j] > N) // ������� ���������� ���������� ����
					x2++;

			}

			x1 = g4[i].size();
			g4[i].resize(x1 - x2); // ������� ��

			x2 = 0;

		}

		i2 = 0;

		for (int i = 0; i < g3.size(); ) // � ���������� ��������������� �����
		{

			sort(g4[i].begin(), g4[i].end()); // ���������

			if (i2 == g3[i].size()) // ���� ���� ���������� ��� ������
			{
				i++; // ��������� �� ���������
				i2 = 0;
				continue;

			}

			x1 = 0;

			for (int j = 0; j < g4[i].size(); j++)
			{
				if (g3[i][i2] == g4[i][j])
				{
					x1 = 1;
					i2++;
					break;


				}
			}

			if (x1 == 1) // ���� ���� ����� ���� - ����������
				continue;

			else
			{
				g4[i].push_back(g3[i][i2]); // ����� ��������� ����� �����
				i2++;

			}

		}

		


		printf("\n\n 3*. ��������� ����� ������ 1 � 2\n");

		for (int i = 0; i < g4.size(); i++) // ����� ������
		{
			std::cout << "  " << i + 1 << " : ";
			for (int j = 0; j < g4[i].size(); j++)
			{
				std::cout << g4[i][j] + 1 << " ";
			}

			std::cout << "\n";
		}



}