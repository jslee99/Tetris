#include<iostream>
#include<Windows.h>

using namespace std;


//test goto XY
void gotoXY(int x, int y) {
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int main(void) {
	int a[4][4] = { {0,1,1,0},
					{0,1,1,0},
					{0,1,1,0},
					{0,1,1,0} };
	for (int i = 0; i < 4; i++) {
		gotoXY(1, i + 1);
		for (int j = 0; j < 4; j++) {
			if (a[i][j] == 1) {
				cout << "��";
			}
			else {
				cout << "��";
			}

		}
	}
	gotoXY(20, 20);
	cout << "��";

	for (int i = 0; i < 4; i++) {
		gotoXY(1, i + 5);
		for (int j = 0; j < 4; j++) {
			if (a[i][j] == 0) {
				cout << "��";
			}
			else {
				cout << "��";
			}

		}
	}
}

