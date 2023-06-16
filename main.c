#include <stdio.h>
#include <stdlib.h>
void add_rand(int map[4][4]);
void print_map(int map[4][4]);

int main() {
	srand(time(NULL));
	int map[4][4] = {
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
	};
	add_rand(map);
	add_rand(map);
	print_map(map);
}

void add_rand(int map[4][4]) {
	int y = rand() % 4, x = rand() % 4;
	while (!map[y][x]){
		if (!map[y][x]) {
			map[y][x] = 2;
			break;
		}
		y = rand() % 4;
		x = rand() % 4;
	}
}
void print_map(int map[4][4]) {
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++) {
			int block = map[i][j];
			switch (block) {
				case 0: printf("\x1b[47m  \x1b[0m"); break;
				case 2: printf("\x1b[45m  \x1b[0m"); break;
			}
		}
		printf("\n");
	}
}
