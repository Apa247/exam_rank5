#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

typedef struct {
	int x;
	int y;
	int is_drav;
} t_pen;

char **new_tab(int rows, int cols)
{
	char **tab = calloc(sizeof(char *), rows);
	if (!tab)
		return 0;
	for (int i = 0; i < rows; i++)
	{
		tab[i] = calloc(sizeof(char), cols + 1);
		if (!tab[i])
			return 0;
		for (int j = 0; j < cols; j++)
			tab[i][j] = ' ';
	}
	return tab;
}

void free_map(char **map, int rows)
{
	for (int i = 0; i < rows; i++)
		free(map[i]);
	free(map);
}

void print_map(char **map, int rows, int cols)
{	
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			putchar(map[i][j]);
		putchar('\n');
	}
}

int count_c(char **map, int x, int y, int rows, int cols)
{
	int count = 0;
	for (int i = -1; i <= 1; i++){
		for(int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)
				continue;
			int new_y = y + i;
			int new_x = x + j;
			if (new_x >= 0 && new_x < cols && new_y >= 0 && new_y < rows)
				if (map[new_y][new_x] == '0')
					count++;
		}
	}
	return count; 
}

void iter_map(char **map, int rows, int cols)
{
	char **new_map = new_tab(rows, cols);
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			int count = count_c(map, x, y, rows, cols);
			if (map[y][x] == '0')
			{
				if (count == 2 || count == 3)
					new_map[y][x] = '0';
			}
			else
			{
				if (count == 3)
					new_map[y][x] = '0';
			}
		}
	}
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			map[i][j] = new_map[i][j];
	free_map(new_map, rows);
}

int main(int ac, char **av)
{
	if (ac != 4)
		return 0;
	t_pen pen = {0, 0, 0};
	int cols = atoi(av[1]);
	int rows = atoi(av[2]);
	int iter = atoi(av[3]);
	char **tab = new_tab(rows, cols);
	if (!tab)
		return 0;
	char comand;
	while (read(0, &comand, 1) > 0)
	{
		if (pen.is_drav)
			tab[pen.y][pen.x] = '0';
		switch (comand)
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
				pen.is_drav = !pen.is_drav;
				break;
		}
	}

	for (int i = 0; i < iter; i++)
		iter_map(tab, rows, cols);
	print_map(tab, rows, cols);
	free_map(tab, rows);
	return 0;
}