#ifndef BSQ_H
#define BSQ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_MSG "error de mapa\n\n"

typedef struct {
	int		rows;
	int		cols;
	char	empty;
	char	obstacle;
	char	full;
	char 	**map;
} t_map;

typedef struct {
	int		size;
	int		row;
	int		col;

} t_square;

int read_map(FILE *fp, t_map *map);
int validate_map(t_map *map);
void free_map(t_map *map);
int min3(int a, int b, int c);
void print_solution(t_map *map, t_square *square);
int resolve_map(t_map *map, t_square *square);
int process_map(FILE *fp);
void print_error();

#endif 