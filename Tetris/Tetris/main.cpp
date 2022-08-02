#pragma once
#include "game.h"
#include "system.h"

using namespace std;

/*
gameinit next_trun = true, 벽 설정

if next_turn
	change blockqueue change cur_BLOCK
	check can positioning cur_BLOCK at start point if cant game_over (일단 꾸겨넣고(r만 조절함) 3번과 겹치면 game_over)
	reset r, c
else
	roation감지, 변경(꾸겨넣기, 안되면(일단 1을 위주로 꾸겨넣고 그후에 3과 겹치게 되는 경우) 원래 상태로 돌려놓기)
	left_right 감지(가능한지 check 가능하면 r변경)

	control table // set value of table(별다른 오류감지 필요 없음)
	draw table
	충돌감지(아래에 1이나 3이 있는지 여부, next_turn 설정)

	
	if(!turn_change)
		c--
	else
		convert 2 to 3
		combo check//아직 안함
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