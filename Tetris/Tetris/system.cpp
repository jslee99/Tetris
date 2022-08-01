#include "system.h"

using namespace std;

void hideCursor() {
	HANDLE consoleHanlde = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO consoleCursor;
	consoleCursor.bVisible = false;
	consoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHanlde, &consoleCursor);
}


void gotoRC(int r, int c) {
	COORD pos = { c, r };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}