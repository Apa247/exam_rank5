#ifndef BSQ_H
#define BSQ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_MSG "error de mapa\n"

// Estructura para guardar la información del mapa
typedef struct {
    int rows;
    int cols;
    char empty;
    char obstacle;
    char full;
    char **map;
} t_map;

// Estructura para la solución del cuadrado más grande
typedef struct {
    int size;
    int row;
    int col;
} t_square;

// Prototipos
int parse_first_line(char *line, t_map *map);
int read_map(FILE *fp, t_map *map);
int validate_map(t_map *map);
void free_map(t_map *map);
int solve_bsq(t_map *map, t_square *square);
void print_solution(t_map *map, t_square *square);
void print_error();
int min3(int a, int b, int c);

#endif // BSQ_H
