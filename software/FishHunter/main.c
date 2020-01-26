#include "MainLogic.h"
#include <time.h>
#include "keyboard.h"
#include "GameState.h"
/*
Register Map:

0 : Item/Object Index	Indicate the object or the pattern you want to draw
1 : VGA Screen X Location of the item	(Top left Pixel coordinate)
2 : VGA Screen Y Location of the item	(Top left Pixel coordinate)
3 : VGA Screen X Location of the item	(Bottom Right Pixel coordinate)
4 : VGA Screen Y Location of the item	(Bottom Right Pixel coordinate)
5 : Reserved
6 : Draw_Start
7 : Draw_Done
*/

int main(){
	keyboard_init();
	srand((unsigned)time(NULL));	//INIT SEED
	char option;
	int scores[5] = {0,0,0,0,0};
	MENU:
	option = displayMenu();
	//printf("Option : %c\n");
	if(option == 'p'){
		GameState gamestate = playGame();
		updateScores(scores, gamestate.score);
		goto MENU;
	}
	else if(option == 's'){
		displayScores(scores);
		goto MENU;
	}
}
