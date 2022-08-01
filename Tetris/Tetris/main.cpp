#pragma once
#include "game.h"
#include "system.h"

using namespace std;

/*
if next_turn
	change blockqueue
	change cur_BLOCK
	check can positioning cur_BLOCK at start point if cant game_over (�ϴ� �ְٰܳ� 3���� ��ġ�� game_over)
	reset r, c
else
	roation����
	left_right ����
	control table // set value of table(�ֱٰܳ�(1,3�� ��� �Ű澴��.)) , �Ұ����� ������� Ȯ��(1�� �Ǵ� 3���� ��ġ�� game_over)),  (�浹����)
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