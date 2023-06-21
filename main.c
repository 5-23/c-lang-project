#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>

#define SIZE 4
#define GOAL 2048

int map[SIZE][SIZE];
int score;
bool win;

void init() {
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            map[i][j] = 0;
        }
    }

    add_new_tile();
    add_new_tile();
}

void add_new_tile() {
    int new_tile = (rand() % 100 < 89) ? 2 : 4;
    int empty_cells[SIZE * SIZE][2];
    int count = 0;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (map[i][j] == 0) {
                empty_cells[count][0] = i;
                empty_cells[count][1] = j;
                count++;
            }
        }
    }

    if (count > 0) {
        int rnd = rand() % count;
        int row = empty_cells[rnd][0];
        int col = empty_cells[rnd][1];
        map[row][col] = new_tile;
    }
}

void encode_map() {
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (map[i][j] == 0) {
                printf("  ");
            } else {
                printf("%d ", map[i][j]);
            }
        }
        printf("\n");
    }
}

void merge_tiles_left() {
    for (int i = 0; i < SIZE; i++) {
        int row[SIZE];
        int merged[SIZE];
        int merge_count = 0;

        for (int j = 0; j < SIZE; j++) {
            row[j] = map[i][j];
            merged[j] = 0;
        }

        for (int j = 0; j < SIZE; j++) {
            if (row[j] != 0) {
                if (merge_count > 0 && row[j] == merged[merge_count - 1]) {
                    merged[merge_count - 1] *= 2;
                    score += merged[merge_count - 1];
                    row[j] = 0;
                } else {
                    merged[merge_count] = row[j];
                    merge_count++;
                }
            }
        }

        
        for (int j = 0; j < SIZE; j++) {
            map[i][j] = merged[j];
        }
    }
}

void move_left() {
    
    merge_tiles_left();

    add_new_tile();
}

void move_right() {
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE / 2; j++) {
            int temp = map[i][j];
            map[i][j] = map[i][SIZE - 1 - j];
            map[i][SIZE - 1 - j] = temp;
        }
    }

    
    merge_tiles_left();

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE / 2; j++) {
            int temp = map[i][j];
            map[i][j] = map[i][SIZE - 1 - j];
            map[i][SIZE - 1 - j] = temp;
        }
    }

    add_new_tile();
}

void move_up() {
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = i; j < SIZE; j++) {
            int temp = map[i][j];
            map[i][j] = map[j][i];
            map[j][i] = temp;
        }
    }

    
    merge_tiles_left();

    for (int i = 0; i < SIZE; i++) {
        for (int j = i; j < SIZE; j++) {
            int temp = map[i][j];
            map[i][j] = map[j][i];
            map[j][i] = temp;
        }
    }

    add_new_tile();
}

void move_down() {
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = i; j < SIZE; j++) {
            int temp = map[i][j];
            map[i][j] = map[j][i];
            map[j][i] = temp;
        }
    }

    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE / 2; j++) {
            int temp = map[i][j];
            map[i][j] = map[i][SIZE - 1 - j];
            map[i][SIZE - 1 - j] = temp;
        }
    }

    
    merge_tiles_left();

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE / 2; j++) {
            int temp = map[i][j];
            map[i][j] = map[i][SIZE - 1 - j];
            map[i][SIZE - 1 - j] = temp;
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = i; j < SIZE; j++) {
            int temp = map[i][j];
            map[i][j] = map[j][i];
            map[j][i] = temp;
        }
    }

    add_new_tile();
}

bool game_over() {
    if (win) {
        return true;
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (map[i][j] == GOAL) {
                win = true;
                return true;
            }
        }
    }

    return false;
}

int main_game() {
    srand(time(NULL));

    
    init();

    while (true) {
        system("clear");
        encode_map();

        char action;
        printf("Enter your action (w/a/s/d): ");
        scanf(" %c", &action);

        if (game_over()) {
            if (win) {
                printf("You won!\n");
            } else {
                printf("Game over!\n");
            }
            break;
        }

        
        if (action == 'w') {
            move_up();
        } else if (action == 'a') {
            move_left();
        } else if (action == 's') {
            move_down();
        } else if (action == 'd') {
            move_right();
        }
    }
}

int main(){
	main_game();
}