#include "bsq.h"
#include <sys/types.h>


int parse_first_line(char *line, t_map *map) {
    char empty, obstacle, full;
    int rows;
    if (sscanf(line, "%d %c %c %c", &rows, &empty, &obstacle, &full) != 4)
        return 0;
    if (empty == obstacle || empty == full || obstacle == full)
        return 0;
    if ((empty < 32 || empty > 126) || (obstacle < 32 || obstacle > 126) || (full < 32 || full > 126))
        return 0;
    map->rows = rows;
    map->empty = empty;
    map->obstacle = obstacle;
    map->full = full;
    return 1;
}

int read_map(FILE *fp, t_map *map) {
    size_t len = 0;
    ssize_t read;
    char *line = NULL;
    int i = 0;
    map->map = malloc(sizeof(char *) * map->rows);
    if (!map->map) return 0;
    while (i < map->rows && (read = getline(&line, &len, fp)) != -1) {
        if (line[read - 1] == '\n') {
            line[--read] = '\0';
        }
        if (i == 0) map->cols = read;
        else if (read != map->cols) { free(line); return 0; }
        map->map[i] = malloc(map->cols + 1);
        if (!map->map[i]) { free(line); return 0; }
        strncpy(map->map[i], line, map->cols);
        map->map[i][map->cols] = '\0';
        i++;
    }
    free(line);
    return (i == map->rows);
}

int validate_map(t_map *map) {
    if (map->rows < 1 || map->cols < 1) return 0;
    for (int i = 0; i < map->rows; i++) {
        for (int j = 0; j < map->cols; j++) {
            char c = map->map[i][j];
            if (c != map->empty && c != map->obstacle && c != map->full)
                return 0;
        }
    }
    return 1;
}

void free_map(t_map *map) {
    for (int i = 0; i < map->rows; i++)
        free(map->map[i]);
    free(map->map);
}

int min3(int a, int b, int c) {
    int min = a;
    if (b < min) min = b;
    if (c < min) min = c;
    return min;
}

int solve_bsq(t_map *map, t_square *square) {
    int **dp = malloc(sizeof(int *) * map->rows);
    if (!dp) return 0;
    for (int i = 0; i < map->rows; i++) {
        dp[i] = calloc(map->cols, sizeof(int));
        if (!dp[i]) return 0;
    }
    int max_size = 0, max_row = 0, max_col = 0;
    for (int i = 0; i < map->rows; i++) {
        for (int j = 0; j < map->cols; j++) {
            if (map->map[i][j] == map->empty) {
                if (i == 0 || j == 0)
                    dp[i][j] = 1;
                else
                    dp[i][j] = 1 + min3(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]);
                if (dp[i][j] > max_size) {
                    max_size = dp[i][j];
                    max_row = i;
                    max_col = j;
                }
            }
        }
    }
    square->size = max_size;
    square->row = max_row;
    square->col = max_col;
    for (int i = 0; i < map->rows; i++) free(dp[i]);
    free(dp);
    return (max_size > 0);
}

void print_solution(t_map *map, t_square *square) {
    for (int i = square->row - square->size + 1; i <= square->row; i++) {
        for (int j = square->col - square->size + 1; j <= square->col; j++) {
            map->map[i][j] = map->full;
        }
    }
    for (int i = 0; i < map->rows; i++) {
        fputs(map->map[i], stdout);
        fputc('\n', stdout);
    }
}

void print_error() {
    fputs(ERROR_MSG, stderr);
}

int process_map(FILE *fp) {
    t_map map = {0};
    t_square square = {0};
    char *line = NULL;
    size_t len = 0;
    if (getline(&line, &len, fp) == -1 || !parse_first_line(line, &map)) {
        print_error();
        free(line);
        return 0;
    }
    free(line);
    if (!read_map(fp, &map) || !validate_map(&map) || !solve_bsq(&map, &square)) {
        print_error();
        free_map(&map);
        return 0;
    }
    print_solution(&map, &square);
    free_map(&map);
    return 1;
}

int main(int argc, char **argv) {
    if (argc == 1) {
        process_map(stdin);
    } else {
        for (int i = 1; i < argc; i++) {
            FILE *fp = fopen(argv[i], "r");
            if (!fp) { print_error(); continue; }
            process_map(fp);
            fclose(fp);
        }
    }
    return 0;
}
