#pragma once

typedef struct GameStateStruct{
	int time;	//How much time player has played
	int score;
	int state;	//If 0, naturally stop.	//If 1, forced stop
}GameState;
