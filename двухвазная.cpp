// двухвазная.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <stdio.h>
#include <stdlib.h>
#include <clocale>

int search_size()
{
	FILE* t;
	int size = 0, a;
	fopen_s(&t, "t.txt", "r");
	if (t == 0)
	{
		printf("file not open\n");
		exit(0);
	}
	while (!feof(t))
	{
		fscanf_s(t, "%d", &a);
		size++;
	}
	fclose(t);

	return size;
}
void print_t(int seria)
{
	FILE* t;
	int a, count = 0;
	fopen_s(&t, "t.txt", "r");
	if (t == 0)
	{
		printf("file not open\n");
		exit(0);
	}
	printf("t: ");
	while (!feof(t))
	{
		fscanf_s(t, "%d", &a);
		if (!feof(t))
		{
			printf("%d ", a);
			count++;
			if (count == seria)
			{
				printf("| ");
				count = 0;
			}
		}
	}
	printf("\n");
	fclose(t);
}
void print_f(int seria)
{
	FILE* f;
	int a, count = 0;
	fopen_s(&f, "f.txt", "r");
	if (f == 0)
	{
		printf("file not open\n");
		exit(0);
	}
	printf("f: ");
	while (feof(f) == 0)
	{
		fscanf_s(f, "%d", &a);
		if (!feof(f))
		{
			printf("%d ", a);
			count++;
			if (count == seria)
			{
				printf("| ");
				count = 0;
			}
		}
	}
	printf("\n");
	fclose(f);
}
void print_g(int seria)
{
	FILE* g;
	int a, count = 0;
	fopen_s(&g, "g.txt", "r");
	if (g == 0)
	{
		printf("file not open\n");
		exit(0);
	}
	printf("g: ");
	while (!feof(g))
	{
		fscanf_s(g, "%d", &a);
		if (!feof(g))
		{
			printf("%d ", a);
			count++;
			if (count == seria)
			{
				printf("| ");
				count = 0;
			}
		}
	}
	printf("\n");
	fclose(g);
}
void separation(int* seria, int size)
{
	FILE* t, * f, * g;
	fopen_s(&t, "t.txt", "r");
	fopen_s(&f, "f.txt", "w");
	fopen_s(&g, "g.txt", "w");
	int a, i = 0, j = 0;
	if (t == 0 || f == 0 || g == 0)
	{
		printf("file not open\n");
		exit(0);
	}
	char count = 0;
	while (count < size)
	{
		if (i < (*seria))
		{
			j = 0;
			fscanf_s(t, "%d", &a);
			fprintf(f, "%d", a);
			fprintf(f, " ");
			count++;
			i++;
		}
		else
		{
			if (j < (*seria))
			{
				fscanf_s(t, "%d", &a);
				fprintf(g, "%d", a);
				fprintf(g, " ");
				count++;
				j++;
			}
			else
			{
				i = 0;
			}
		}
	}
	fclose(t);
	fclose(f);
	fclose(g);
}

void merge(int* seria)
{
	int a, b, flag = 0, i = 0, j = 0;
	FILE* t, * f, * g;
	fopen_s(&t, "t.txt", "w");
	fopen_s(&f, "f.txt", "r");
	fopen_s(&g, "g.txt", "r");
	if (t == 0 || f == 0 || g == 0)
	{
		printf("file not open\n");
		exit(0);
	}
	if (f != NULL && g != NULL)
	{
		fscanf_s(f, "%d", &a);
		fscanf_s(g, "%d", &b);
		while ((flag != 1) && (flag != 2))
		{
			while ((!feof(f)) || (!feof(g)))
			{
				if (i < (*seria) && j < (*seria))
				{
					if (a <= b)
					{
						if (!feof(f))
						{
							fprintf(t, "%d", a);
							fprintf(t, " ");
						}
						fscanf_s(f, "%d", &a);
						if (feof(f))
						{
							flag = 2;
						}
						i++;
					}
					else if (a >= b)
					{
						if (!feof(g))
						{
							fprintf(t, "%d", b);
							fprintf(t, " ");
						}
						fscanf_s(g, "%d", &b);
						if (feof(g))
						{
							flag = 1;
						}
						j++;
					}
				}
				else if (i < (*seria) && j == (*seria))
				{
					while (i != (*seria))
					{
						if (!feof(f))
						{
							fprintf(t, "%d", a);
							fprintf(t, " ");
						}
						fscanf_s(f, "%d", &a);
						i++;
					}
					i = 0;
					j = 0;
					if (feof(f))
					{
						flag = 2;
					}
				}
				else if (j < (*seria) && i == (*seria))
				{
					while (j != (*seria))
					{
						if (!feof(g))
						{
							fprintf(t, "%d", b);
							fprintf(t, " ");
						}
						fscanf_s(g, "%d", &b);
						j++;
					}
					i = 0;
					j = 0;
					if (feof(f))
					{
						flag = 1;
					}
				}
			}
		}
		if (flag == 1)
		{
			while (!feof(f))
			{
				fprintf(t, "%d", a);
				fprintf(t, " ");
				fscanf_s(f, "%d", &a);
			}
		}
		if (flag == 2)
		{
			while (!feof(g))
			{
				fprintf(t, "%d", b);
				fprintf(t, " ");
				fscanf_s(g, "%d", &b);
			}
		}
	}
	(*seria) *= 2;
	fclose(t);
	fclose(f);
	fclose(g);
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int seria = 1;

	int size = search_size();

	while (seria <= size)
	{
		separation(&seria, size);
		print_f(seria);
		print_g(seria);
		merge(&seria);
		printf("Отсортированный: \n");
		printf("-----------------------------------------------------------\n");
		print_t(seria);
		printf("-----------------------------------------------------------\n");
	}

	return 0;
}