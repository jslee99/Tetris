#include "game.h"

using namespace std;

void Game::check_turn_change() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (BLOCK[cur_BLOCK][cur_rotation][i][j] == 2) {
				if (table[r + i + 1][c + j] == 1 || table[r + i + 1][c + j] == 3) turn_change = true;
			}
		}
	}
}

void Game::convert_active_block_to_static_block(){
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (BLOCK[cur_BLOCK][cur_rotation][i][j] == 2) table[r + i][c + j] = 3;
		}
	}
}

bool Game::get_turn_change(){
	return turn_change;
}

void Game::recontrolTable(){
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (BLOCK[cur_BLOCK][cur_rotation][i][j] == 2) table[r + i][c + j] = 0;
		}
	}
}

bool Game::get_game_over()
{
	return game_over;
}

void Game::downBlock() {
	r++;
}

void Game::chage_block_q(){
	cur_BLOCK = next_block_q.front();
	cur_rotation = 0;
	next_block_q.pop();


	//test
	//next_block_q.push(rand() % 7);
	next_block_q.push(0);
}

void Game::check_gameover_at_change_turn(){
	this->reset_RC();
	bool flag = false;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (BLOCK[cur_BLOCK][cur_rotation][i][j] == 2) {
				while (r + i < 1)r++;
				flag = true;
				break;
			}
		}
		if (flag) break;
	}


	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (BLOCK[cur_BLOCK][cur_rotation][i][j] == 2) {
				if (table[r + i][c + j] == 3) game_over = true;
			}
		}
	}

	turn_change = false;
}

void Game::reset_RC(){
	r = -1;
	c = 4;
}



void Game::gameInit() {
	turn_change = true;
	game_over = false;
	

	srand((unsigned int)time(NULL));
	for (int i = 0; i < 7; i++) {
		//test
		//next_block_q.push(rand() % 7);
		next_block_q.push(0);
	}

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
			else if (table[i][j] == 1) cout << "в╦";
			else if (table[i][j] == 2) cout << "бс";
			else if (table[i][j] == 3) cout << "бс";
		}
		cout << endl;
	}
}

void Game::controlTable() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (BLOCK[cur_BLOCK][cur_rotation][i][j] == 2)table[r + i][c + j] = 2;
		}
	}
}
