#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>
#include <stdlib.h>

#define SIZE 4
#define GOAL 2048


typedef struct {
    int map[SIZE][SIZE];
    int score;
    bool win;
    bool lose;
} Game;

// int score;
// int map[SIZE][SIZE];

void init(Game *game) {
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            game->map[i][j] = 0;
        }
    }

    spawn(game);
    spawn(game);
}

void spawn(Game *game) {
    int new_tile = (rand() % 100 < 89) ? 2 : 4;
    int empty_cells[SIZE * SIZE][2];
    int count = 0;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (game->map[i][j] == 0) {
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
        game->map[row][col] = new_tile;
    }
}

void encode_map(Game game) {
    printf("score: %d\n", game.score);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (game.map[i][j] == 0) {
                printf("  ");
            } else {
                printf("%d ", game.map[i][j]);
            }
        }
        printf("\n");
    }
}

void merge(Game *game) {
    for (int i = 0; i < SIZE; i++) {
        int row[SIZE];
        int merged[SIZE];
        int merge_cnt = 0;

        for (int j = 0; j < SIZE; j++) {
            row[j] = game->map[i][j];
            merged[j] = 0;
        }

        for (int j = 0; j < SIZE; j++) {
            if (row[j] != 0) {
                if (merge_cnt > 0 && row[j] == merged[merge_cnt - 1]) {
                    merged[merge_cnt - 1] *= 2;
                    game->score += merged[merge_cnt - 1];
                    row[j] = 0;
                } else {
                    merged[merge_cnt] = row[j];
                    merge_cnt++;
                }
            }
        }

        
        for (int j = 0; j < SIZE; j++) {
            game->map[i][j] = merged[j];
        }
    }
}

void move_left(Game *game) {
    
    merge(game);

    spawn(game);
}

void move_right(Game *game) {
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE / 2; j++) {
            int temp = game->map[i][j];
            game->map[i][j] = game->map[i][SIZE - 1 - j];
            game->map[i][SIZE - 1 - j] = temp;
        }
    }

    
    merge(game);

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE / 2; j++) {
            int temp = game->map[i][j];
            game->map[i][j] = game->map[i][SIZE - 1 - j];
            game->map[i][SIZE - 1 - j] = temp;
        }
    }

    spawn(game);
}

void move_up(Game *game) {
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = i; j < SIZE; j++) {
            int temp = game->map[i][j];
            game->map[i][j] = game->map[j][i];
            game->map[j][i] = temp;
        }
    }

    
    merge(game);

    for (int i = 0; i < SIZE; i++) {
        for (int j = i; j < SIZE; j++) {
            int temp = game->map[i][j];
            game->map[i][j] = game->map[j][i];
            game->map[j][i] = temp;
        }
    }

    spawn(game);
}

void move_down(Game *game) {
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = i; j < SIZE; j++) {
            int temp = game->map[i][j];
            game->map[i][j] = game->map[j][i];
            game->map[j][i] = temp;
        }
    }

    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE / 2; j++) {
            int temp = game->map[i][j];
            game->map[i][j] = game->map[i][SIZE - 1 - j];
            game->map[i][SIZE - 1 - j] = temp;
        }
    }

    
    merge(game);

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE / 2; j++) {
            int temp = game->map[i][j];
            game->map[i][j] = game->map[i][SIZE - 1 - j];
            game->map[i][SIZE - 1 - j] = temp;
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = i; j < SIZE; j++) {
            int temp = game->map[i][j];
            game->map[i][j] = game->map[j][i];
            game->map[j][i] = temp;
        }
    }

    spawn(game);
}

bool game_over(Game *game) {
    if (game->win) {
        return true;
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (game->map[i][j] == GOAL) {
                game->win = true;
                return true;
            }
        }
    }

    return false;
}

void clone(Game a, Game *b){
    memcpy(b->map, a.map, sizeof(a.map));
    b->score, a.score;
    b->win = a.win;
    b->lose = a.lose;
}

int eq(int arr1[SIZE][SIZE], int arr2[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (arr1[i][j] != arr2[i][j]) return 0;
        }
    }
    
    return 1;
}

int main_game() {
    srand(time(NULL));

    Game game, game_clone1, game_clone2, game_clone3, game_clone4;
    init(&game);

    while (true) {
        system("clear");
        encode_map(game);

        char action;
        printf("Enter your action (w/a/s/d): ");
        scanf(" %c", &action);

        if (game_over(&game)) {
            if (game.win) {
                printf("You won!\n");
            } else {
                printf("Game over!\n");
            }
            break;
        }

        
        if (action == 'w') {
            move_up(&game);
        } else if (action == 'a') {
            move_left(&game);
        } else if (action == 's') {
            move_down(&game);
        } else if (action == 'd') {
            move_right(&game);
        }
        clone(game, &game_clone1);
        clone(game, &game_clone2);
        clone(game, &game_clone3);
        clone(game, &game_clone4);
        move_left  (&game_clone1);
        move_right (&game_clone2);
        move_up    (&game_clone3);
        move_down  (&game_clone4);
        
        write_f(game.score);

        if (
            eq(game_clone1.map, game.map) &&
            eq(game_clone2.map, game.map) &&
            eq(game_clone3.map, game.map) &&
            eq(game_clone4.map, game.map)
            ){
                printf("GAME OVER");
                encode_map(game);
                return 0;

        }
    }
}

void intro(){
    int score = get_f();
    if (!score){
        printf("최고 기록: 없음");
    }else{
        printf("최고 기록: %d", score);
    }
    printf("\nenter를 눌러서 시작하세요!");
    getchar();
}

void write_f(int n){
    if (get_f() < n){
        char str_n[20];
        sprintf(str_n, "%d", n);

        FILE* fp = fopen("score.txt","w");
        fputs(str_n, fp);

        fclose(fp);
    }
}

int get_f(){
    FILE* fs;
    fs = fopen("score.txt", "r");
    char str[10];
    fgets(str, 100, fs);
    return atoi(str);
}

int main(){
    while (1)
    {    
        intro();

        main_game();
        
        printf("\n끝내기: ctrl+c, 다시하기: enter");
        getchar();
        
    }
}