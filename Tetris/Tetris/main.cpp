#pragma once
#include "game.h"
#include "system.h"

using namespace std;

/*
gameinit next_trun = true, �� ����

if next_turn
	change blockqueue change cur_BLOCK
	check can positioning cur_BLOCK at start point if cant game_over (�ϴ� �ְٰܳ�(r�� ������) 3���� ��ġ�� game_over)
	reset r, c
else
	roation����, ����(�ֱٰܳ�, �ȵǸ�(�ϴ� 1�� ���ַ� �ְٰܳ� ���Ŀ� 3�� ��ġ�� �Ǵ� ���) ���� ���·� ��������)
	left_right ����(�������� check �����ϸ� r����)

	control table // set value of table(���ٸ� �������� �ʿ� ����)
	draw table
	�浹����(�Ʒ��� 1�̳� 3�� �ִ��� ����, next_turn ����)

	
	if(!turn_change)
		c--
	else
		convert 2 to 3
		combo check//���� ����
	sleep
*/
int main(void) {
	Game game = Game();
	hideCursor();
	game.gameInit();
	while (1) {
		if (game.get_turn_change()) {
			game.chage_block_q();
			game.check_gameover_at_change_turn();
			if (game.get_game_over())break;			
		}
		else {
			game.left_right_check();
			game.rotation_check();
			game.controlTable();
			system("cls");
			game.drawTable();
			game.check_turn_change();

			if (!game.get_turn_change()) {
				game.recontrolTable();
				game.downBlock();			
				Sleep(100);
			}
			else {
				game.convert_active_block_to_static_block();
				game.combo_check();
				Sleep(100);
			}
		}
	}
}