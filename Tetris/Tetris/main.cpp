#pragma once
#include "game.h"
#include "system.h"

using namespace std;

/*
if next_turn
	change blockqueue
	change cur_BLOCK
	check can positioning cur_BLOCK at start point if cant game_over (일단 꾸겨넣고 3번과 겹치면 game_over)
	reset r, c
else
	roation감지
	left_right 감지
	control table // set value of table(꾸겨넣기(1,3을 모두 신경쓴다.)) , 불가능한 경우인지 확인(1번 또는 3번과 겹치면 game_over)),  (충돌감지)
	draw table
	check game_over // (next_turn == true && block position at first line)
	c--
	sleep
*/
int main(void) {
	Game game = Game();
	hideCursor();
	game.gameInit();

	while (1) {
		system("cls");
		game.controlTable();
		game.drawTable();
		Sleep(25);
	}
}