#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Struktura mapy.
typedef struct {
    int rows;
    int cols;
    unsigned char *cells;
} Map;

//Struktura ohraničení jednoho pole. Another označuje zbývající stěna ať už horní nebo spodní.
typedef struct {
    bool left;
    bool right;
    bool another;
} Border;

//Funkce co vrítí strukturu Border podle hodnoty z parametru ufield
Border get_border(unsigned char ufield) {
    Border field;
    switch (ufield) {
        case '0':
            field.left = false;
            field.right = false;
            field.another = false;
            break;
        case '1':
            field.left = true;
            field.right = false;
            field.another = false;
            break;
        case '2':
            field.left = false;
            field.right = true;
            field.another = false;
            break;
        case '3':
            field.left = true;
            field.right = true;
            field.another = false;
            break;
        case '4':
            field.left = false;
            field.right = false;
            field.another = true;
            break;
        case '5':
            field.left = true;
            field.right = false;
            field.another = true;
            break;
        case '6':
            field.left = false;
            field.right = true;
            field.another = true;
            break;
        case '7':
            field.left = true;
            field.right = true;
            field.another = true;
            break;
    }
    return field;
}

//Funkce zjistí jestli je pole v bludišti validní.
int is_valid_maze_field(unsigned char *number) {
    if (strlen((const char *) number) > 1) {
        return 0;
    }
    if (!(number[0] >= '0' && number[0] <= '7')) {
        return 0;
    }
    return 1;
}

//Funkce vrací hodnotu pozice na řídku. Parametr position je absolutní pozice.
int get_col_position(Map maze, int position) {
    return position % maze.cols;
}

//Funkce vrátí absolutní pozice ze souřadnice.
int get_absolute_position(int rows, int cols, Map maze) {
    return ((rows - 1) * maze.cols) + cols - 1;
}

//Funkce vrátí pořadí řádku z absolutní pozice.
int get_row_position(Map maze, int position) {
    return position / maze.cols;
}

//Funkce z absolutní pozice zjistí jestli je pozice na řádku sudá.
int is_col_even(Map maze, int position) {
    return get_col_position(maze, position) % 2;
}

//Funkce z absolutní pozice zjistí jestli je řádek sudý.
int is_row_even(Map maze, int position) {
    return get_row_position(maze, position) % 2;
}

//Funkce zjistí jetstli je na určité pozici určitá hranice.
//border - 0 pro levou hranici, 1 pro pravou hranice, 2 pro zbývající
bool isborder(Map *map, int position, int border) {
    Border field = get_border(map->cells[position]);
    switch (border) {
        case 0:
            return field.left;
            break;
        case 1:
            return field.right;
            break;
        case 2:
            return field.another;
            break;
    }
    return false;
}

//Funkce zjistí jestli má políčko zbývající stranu dole nebo nahoře.
bool is_down_border(Map maze, int i) {
    return ((is_row_even(maze, i) && !is_col_even(maze, i)) || (!is_row_even(maze, i) && is_col_even(maze, i)));
}

//Funkce zjistí jestli má bludiště platné ohraničení.
bool is_maze_border_valid(Map maze) {
    int limit = maze.cols * maze.rows;

    for (int i = 0; i < limit; i++) {
        if (get_col_position(maze, i) != maze.cols - 1) {
            if (isborder(&maze, i, 1) != isborder(&maze, i + 1, 0)) {
                return false;
            }
        }

        if ((get_row_position(maze, i) + 1 != maze.rows) && is_down_border(maze, i)) {
            if (isborder(&maze, i, 2) != isborder(&maze, maze.cols + i, 2)) {
                return false;
            }
        }
    }
    return true;
}

//Funkce vrátí hranice ze které se má odejít.
int find_way(Map maze, int actual_position, int border_come, bool right) {
    bool have_down_border = is_down_border(maze, actual_position);

    if ((have_down_border && !right) || (!have_down_border && right)) {
        int i = border_come == 2 ? 0 : border_come + 1;
        for (; i != border_come; i++) {
            if (!isborder(&maze, actual_position, i) && i != border_come) {
                return i;
            }
            if (i == 2 && i != border_come) {
                i = -1;
            }
        }
    }

    if ((have_down_border && right) || (!have_down_border && !right)) {
        int i = border_come == 0 ? 2 : border_come - 1;
        for (; i != border_come; i--) {
            if (!isborder(&maze, actual_position, i) && i != border_come) {
                return i;
            }
            if (i == 0 && i != border_come) {
                i = 3;
            }
        }
    }
    return border_come;
}

//Funkce vrátí následující pozice.
int next_position(Map maze, int border_leave, int actual_position) {
    int row = get_row_position(maze, actual_position);
    bool border_down = is_down_border(maze, actual_position);
    if (((border_leave == 2) && ((row == 0 && !border_down) || (row == maze.rows - 1 && border_down)))) {
        return -1;
    }

    if ((border_leave == 1 && get_col_position(maze, actual_position) + 1 == maze.cols) ||
        (border_leave == 0 && get_col_position(maze, actual_position) == 0)) {
        return -1;
    }

    if (border_leave == 2) {
        if (border_down) {
            return actual_position + maze.cols;
        } else {
            return actual_position - maze.cols;
        }
    }

    if (border_leave == 0) {
        return actual_position - 1;
    }

    if (border_leave == 1) {
        return actual_position + 1;
    }

    return actual_position;
}

//Funkce zjistí z jakého pole se má začínat. Pokud nemá jak vrátí -2
int start_border(Map *map, int r, int c, bool leftright) { //1 = right
    int position = get_absolute_position(r, c, *map);
    if (r == 1 && c == 1) {
        if(!isborder(map, position, 0)) {
            return find_way(*map, position, 0, leftright);
        }
        if(!isborder(map, position, 2)) {
            return find_way(*map, position, 2, leftright);
        }
        fprintf(stderr, "Invalid\n");
        return -1;
    }

    if (r == 1 && c == map->cols) {
        if (!isborder(map, position, 1)) {
            return find_way(*map, position, 1, leftright);
        }

        if (!is_down_border(*map, position)) {
            if (isborder(map, position, 2)) {
                return find_way(*map, position, 2, leftright);
            }
        }
        fprintf(stderr, "Invalid\n");
        return -1;
    }

    if (r == map->rows && c == 1) {
        if (!isborder(map, position, 0)) {
            return find_way(*map, position, 0, leftright);
        }
        if (is_down_border(*map, position)) {
            if (!isborder(map, position, 2)) {
                return find_way(*map, position, 2, leftright);
            }
        }
        fprintf(stderr, "Invalid\n");
        return -1;
    }

    if (r == map->rows && c == map->cols) {
        if (!isborder(map, position, 1)) {
            return find_way(*map, position, 1, leftright);
        }
        if (is_down_border(*map, position)) {
            if (!isborder(map, position, 2)) {
                return find_way(*map, position, 2, leftright);
            }
        }
        fprintf(stderr, "Invalid\n");
        return -1;
    }

    if (r == 1) {
        if (is_down_border(*map, position) || isborder(map, position, 2)) {
            fprintf(stderr, "Invalid\n");
            return -1;
        }
        return find_way(*map, position, 2, leftright);
    }

    if (r == map->rows) {
        if (!is_down_border(*map, position) || isborder(map, position, 2)) {
            fprintf(stderr, "Invalid\n");
            return -1;
        }
        return find_way(*map, position, 2, leftright);
    }

    if (c == 1) {
        if (isborder(map, position, 0)) {
            fprintf(stderr, "Invalid\n");
            return -1;
        }
        return find_way(*map, position, 0, leftright);
    }

    if (c == map->cols) {
        if (isborder(map, position, 1)) {
            fprintf(stderr, "Invalid\n");
            return -1;
        }
        return find_way(*map, position, 1, leftright);
    }
    return -1;
}

//Funkce načte ze souboru mapu do struktury Map.
Map load_map(FILE *file) {
    Map maze;

    if (fscanf(file, "%d", &maze.rows) == -1) {
        maze.cols = -1;
        return maze;
    }

    if (fscanf(file, "%d", &maze.cols) == -1) {
        maze.cols = -1;
        return maze;
    }

    int position = 0;
    unsigned char field[3] = "1";
    unsigned char *cells = malloc(sizeof(unsigned char) * maze.rows * maze.cols); //pridal
    while (1) {

        if (fscanf(file, "%2s", field) == -1) {
            break;
        }

        if (position > maze.rows * maze.cols) {
            maze.cols = -1;
            break;
        }

        if (is_valid_maze_field(field)) {
            cells[position] = field[0];
        } else {
            maze.cols = -1;
            break;
        }
        position++;
    }
    maze.cells = cells;

    return maze;
}

//Funkce otevře soubor.
FILE *open_file(char *name) {
    FILE *file;
    file = fopen(name, "r");
    return file;
}

//Funkce zjistí jestli je startovní pozice na mapě.
bool is_start_position_valid(int R, int C, Map maze) {
    if (R <= maze.rows && C <= maze.cols) {
        return true;
    }
    return false;
}

//Funkce vypočití exponenciální hodnotu.
int exponent(int e, int x) {
    int result = 1;
    for (int i = 1;i <= x; i++) {
        result *= e;
    }
    return result;
}

//Funkce převede string na int.
int str_to_int(char *text) {
    int text_len = strlen(text);
    int result = 0;
    for (int i = 0; i < text_len; i++) {
        result += (text[i] - '0') * exponent(10, (text_len - i - 1));
    }
    return result;
}

//Funkce uvolní alokovanou paměť.
void destroy_maze(Map *map) {
    free(map->cells);
    return;;
}

int main(int argc, char *argv[]) {

    if (argc >= 2) {
        if (!strcmp(argv[1], "--help") && argc == 2) {
            printf("--help způsobí, že program vytiskne nápovědu používání programu a skončí.\n"
                   "--test pouze zkontroluje, že soubor daný druhým argumentem programu obsahuje řádnou definici mapy bludiště. V případě, že formát obrázku odpovídá definici (viz níže), vytiskne Valid. V opačném případě (např. ilegálních znaků, chybějících údajů nebo špatných hodnot) program tiskne Invalid.\n"
                   "--rpath hledá průchod bludištěm na vstupu na řádku R a sloupci C. Průchod hledá pomocí pravidla pravé ruky (pravá ruka vždy na zdi).\n"
                   "--lpath hledá průchod bludištěm na vstupu na řádku R a sloupci C, ale za pomoci pravidla levé ruky.\n");
            return 0;
        }

        if (argc == 3) {
            if (!strcmp(argv[1], "--test")) {
                FILE *file = open_file(argv[2]);
                if (file == NULL) {
                    fclose(file);
                    fprintf(stdout, "Invalid\n");
                    return 1;
                }
                Map maze = load_map(file);
                fclose(file);
                if (maze.cols == -1) {
                    fprintf(stderr, "Invalid\n");
                    destroy_maze(&maze);
                    return 1;
                }
                if (is_maze_border_valid(maze)) {
                    fprintf(stdout, "Valid\n");
                    destroy_maze(&maze);
                    return 0;
                } else {
                    fprintf(stdout, "Invalid\n");
                    destroy_maze(&maze);
                    return 1;
                }
            }
        }
        if (argc == 5) {
            FILE *file = open_file(argv[4]);
            if (file == NULL) {
                fprintf(stdout, "Invalid\n");
                fclose(file);
                return 1;
            }
            Map maze = load_map(file);
            if (maze.cols == -1) {
                destroy_maze(&maze);
                fprintf(stderr, "Invalid\n");
                return 1;
            }
            fclose(file);
            int R = str_to_int(argv[2]);
            int C = str_to_int(argv[3]);
            bool right;
            if (!strcmp(argv[1], "--lpath")) {
                right = 0;
            } else if (!strcmp(argv[1], "--rpath")) {
                right = 1;
            } else {
                fprintf(stdout, "Invalid\n");
                destroy_maze(&maze);
                return 1;
            }
            if (is_maze_border_valid(maze) && is_start_position_valid(R, C, maze)) {
                int actual_position = get_absolute_position(R, C, maze);
                int border_leave = start_border(&maze, R, C, right);
                if (border_leave == -1) {
                    fprintf(stdout, "Invalid\n");
                    return 1;
                }
                printf("%d,%d\n", get_row_position(maze, actual_position) + 1,
                       get_col_position(maze, actual_position) + 1);
                while ((actual_position = next_position(maze, border_leave, actual_position)) != -1) {
                    if (border_leave != 2) {
                        border_leave = border_leave == 0 ? 1 : 0;
                    }
                    printf("%d,%d\n", get_row_position(maze, actual_position) + 1,
                           get_col_position(maze, actual_position) + 1);
                    border_leave = find_way(maze, actual_position, border_leave, right);
                }
            } else {
                fprintf(stdout, "Invalid\n");
                destroy_maze(&maze);
                return 1;
            }
            destroy_maze(&maze);
        }
    }
    return 0;
}
