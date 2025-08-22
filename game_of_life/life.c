#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
	int x;
	int y;
	int is_draw;
} t_pen;

void free_tab(char **tab, int height)
{
	for (int i = 0; i < height; i++)
		free(tab[i]);
	free(tab);
}

char **new_tab(int rows, int cols)
{
	char **tab = calloc(sizeof(char *), rows);
	for (int i = 0; i < rows; i++)
	{
		tab[i] = calloc(sizeof(char), cols);
		for (int j = 0; j < cols; j++)
			tab[i][j] = ' ';
	}
	return tab;
}

int count_c(char **tab, int x, int y, int rows, int cols)
{
	int count = 0;
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)
				continue;
			int new_y = y + i;
			int new_x = x + j;
			if (new_x >= 0 && new_x < cols && new_y >= 0 && new_y < rows)
				if (tab[new_y][new_x] == '0')
					count++;
		}
	}
	return count;
} 

void print_tab(char **tab, int rows, int cols)
{
	for (int x = 0; x < rows; x++)
	{
		for (int y = 0; y < cols; y++)
			putchar(tab[x][y]);
		putchar('\n');
	}
}

void iter_map(char **map, int rows, int cols)
{
	char **n_tab =new_tab(rows, cols);
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			int count = count_c(map, x, y, rows, cols);
			if (map[y][x] == '0')
			{
				if (count == 2 || count == 3)
					n_tab[y][x] = '0';
			}
			else
			{
				if (count == 3)
					n_tab[y][x] = '0';
			}
		}
	}
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			map[i][j] = n_tab[i][j];
	free_tab(n_tab, rows);
}

int main (int ac, char **av)
{
	if (ac != 4)
		return 1;
	int cols = atoi(av[1]);
	int rows = atoi(av[2]);
	int iter = atoi(av[3]);
	char **tab = new_tab(rows, cols);
	t_pen pen = {0, 0, 0};
	char command;

	while (read(0, &command, 1) > 0)
	{
		if (pen.is_draw)
			tab[pen.y][pen.x] = '0';
		switch (command)
		{
			case 'w':
				if (pen.y > 0)
					pen.y--;
				break;
			case 's':
				if (pen.y < rows - 1)
					pen.y++;
				break;
			case 'a':
				if (pen.x > 0)
					pen.x--;
				break;
			case 'd':
				if (pen.x < cols - 1)
					pen.x++;
				break;
			case 'x':
				pen.is_draw = !pen.is_draw;
				break;
		}
	}
	for (int i = 0; i < iter; i++)
		iter_map(tab, rows, cols);
	print_tab(tab, rows, cols);
	free_tab(tab, rows);
	return 0;
}