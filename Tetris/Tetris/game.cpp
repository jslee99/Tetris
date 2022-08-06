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

void Game::left_right_check(){
	bool flag = true;
	if (GetAsyncKeyState(VK_LEFT)) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (BLOCK[cur_BLOCK][cur_rotation][i][j] == 2) {
					if (table[r + i][c + j - 1] == 1 || table[r + i][c + j - 1] == 3)flag = false;
				}
			}
		}
		if (flag) {
			c--;
			is_moving_left_right = true;
		}
	}
	

	flag = true;
	if (GetAsyncKeyState(VK_RIGHT)) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (BLOCK[cur_BLOCK][cur_rotation][i][j] == 2) {
					if (table[r + i][c + j + 1] == 1 || table[r + i][c + j + 1] == 3)flag = false;
				}
			}
		}
		if (flag) {
			c++;
			is_moving_left_right = true;
		}
	}
}

void Game::combo_check(){
	vector<int> row_v;
	bool flag = false;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (BLOCK[cur_BLOCK][cur_rotation][i][j] == 2) {
				row_v.push_back(r + i);
				flag = true;
				break;
			}
		}
		if (flag) {
			flag = false;
		}
	}

	for (int i = 0; i < (int)row_v.size(); i++) {
		bool combo = true;
		for (int j = 1; j < TABLE_C - 1; j++) {
			if (!(table[row_v[i]][j] == 3)) {
				combo = false;
				break;
			}
		}
		if (combo) {
			table.erase(table.begin() + row_v[i]);
			vector<int> tmp = vector<int>(TABLE_C, 0);
			tmp[0] = 1, tmp[TABLE_C - 1] = 1;
			table.insert(table.begin() + 1, tmp);
		}
	}
}
/*
bool Game::one_cycle_runnig(){
	if (this->get_turn_change()) {
		this->chage_block_q();
		this->check_gameover_at_change_turn();
		if (this->get_game_over())
			return true;
		else
			return false;
	}
	else {
		this->left_right_check();
		this->rotation_check();
		this->controlTable();
		system("cls");
		this->drawTable();
		Sleep(500);
		this->recontrolTable();
		if (this->is_moving_left_right) {
			is_moving_left_right = false;
			return false;
		}
		this->check_turn_change();

		if (!this->get_turn_change()) {
			this->downBlock();
			system("cls");
			this->drawTable();
		}
		else {
			this->convert_active_block_to_static_block();
			this->combo_check();
		}
		return false;
	}
}*/

bool Game::one_cycle_runnig() {
	if (this->get_turn_change()) {
		this->chage_block_q();
		this->check_gameover_at_change_turn();
		if (this->get_game_over())
			return true;
		else
			return false;
	}
	else {
		this->left_right_check();
		this->rotation_check();
		this->controlTable();
		system("cls");
		this->drawTable();
		Sleep(500);
		this->check_turn_change();

		if (!this->get_turn_change()) {
			this->recontrolTable();
			this->downBlock();
			
		}
		else {
			this->convert_active_block_to_static_block();
			this->combo_check();
		}
		return false;
	}
}

/*
bool Game::one_cycle_while_running() {
	if (this->turn_change) {
		this->chage_block_q();
		this->check_gameover_at_change_turn();
		if (this->game_over) return true;

		return false;
	}
	else {
		this->check_turn_change();
		if (this->turn_change) {
			this->convert_active_block_to_static_block();
			this->combo_check();
		}
		else {
			if (!this->is_moving_left_right) {
				this->downBlock();
				this->controlTable();
				system("cls");
				Sleep(500);
				this->recontrolTable();
			}
		}
	}
}
*/

void Game::rotation_check(){
	if (GetAsyncKeyState(VK_UP)) {
		bool flag = false;
		int before_r = r;
		int before_c = c;
		int before_rotation = cur_rotation;

		cur_rotation = (cur_rotation + 1) % 4;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (BLOCK[cur_BLOCK][cur_rotation][i][j] == 2) {
					while (r + i < 1)r++;
					while (r + i > TABLE_R - 2)r--;
					while (c + j < 1)c++;
					while (c + j > TABLE_C - 2)c--;
				}
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (BLOCK[cur_BLOCK][cur_rotation][i][j] == 2) {
					if (table[r + i][c + j] == 3)flag = true;
				}
			}
		}

		if (flag) {
			r = before_r;
			c = before_c;
			cur_rotation = before_rotation;
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
	next_block_q.push(rand() % 7);
	//next_block_q.push(0);
}

void Game::check_gameover_at_change_turn(){//r,c 초기화까즤
	reset_RC();
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
	is_moving_left_right = false;

	srand((unsigned int)time(NULL));
	for (int i = 0; i < 7; i++) {
		//test
		next_block_q.push(rand() % 7);
		//next_block_q.push(0);
	}

	for (int i = 0; i < TABLE_R; i++) {
		table.push_back(vector<int>(TABLE_C, 0));
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
			else if (table[i][j] == 1) cout << "▦";
			else if (table[i][j] == 2) cout << "■";
			else if (table[i][j] == 3) cout << "■";
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

