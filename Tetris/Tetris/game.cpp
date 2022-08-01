#include "game.h"

using namespace std;

void Game::downBlock() {
	c--;
}

void Game::gameInit() {
	r = -1;
	c = 7;
	next_turn = true;
	for (int i = 0; i < TABLE_R; i++) {
		for (int j = 0; j < TABLE_C; j++) {
			if (is_wall_position(i, j))table[i][j] = 1;
			else table[i][j] = 0;
		}
	}
}

bool Game::is_wall_position(int i, int j) {//row, column
	return i == 0 || i == TABLE_R - 1 || j == 0 || j == TABLE_C - 1;
}

void Game::drawTable(){
	gotoRC(0, 0);
	for (int i = 0; i < TABLE_R; i++) {
		for (int j = 0; j < TABLE_C; j++) {
			if (table[i][j] == 0) cout << "  ";
			else if (table[i][j] == 1) cout << "▦";
			else if (table[i][j] == 2) cout << "■";
			else if (table[i][j] == 3) cout << "■";
		}
		cout << endl;
	}
}





void Game::controlTable() {
	for (int i = 1; i < TABLE_R - 1; i++) {
		for (int j = 1; j < TABLE_C - 1; j++) {
			if (table[i][j] == 3)table[i][j] = 3;
			else table[i][j] = 0;
		}
	}

	for (int i = 0; i < 4; i++) {//꾸겨넣기
		for (int j = 0; j < 4; j++) {
			if (cur_BLOCK[i][j] == 2) {
				while (r + i < 1) r++;
				while (c + j < 1) c++;
				while (c + j > TABLE_C - 2) c--;
			}
		}
	}

	for (int i = 0; i < 4; i++) {//game_over check
		for (int j = 0; j < 4; j++) {
			if (table[r + i][c + j] == 2) game_over = true;
		}
	}
}
