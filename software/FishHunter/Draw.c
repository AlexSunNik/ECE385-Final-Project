#include "Specifics.h"
#include "Animal.h"
#include "Cannon.h"
#include "CannonBall.h"
#include "FishNet.h"

void init_background(){
	IDX = BACKGROUND;
	X_START = 0;
	Y_START = 0;
	X_STOP = 640;
	Y_STOP = 480;
	DRAW_START = 1;
	while(!DRAW_DONE);
	DRAW_START = 0;
	//FRAME_DONE = 1;
}

void draw_background(int drawXStart, int drawYStart, int drawXEnd, int drawYEnd){
	IDX = BACKGROUND;
	X_START = drawXStart;
	Y_START = drawYStart;
	X_STOP = drawXEnd;
	Y_STOP = drawYEnd;
	DRAW_START = 1;
	while(!DRAW_DONE);
	DRAW_START = 0;
}


void draw_animal(Animal animal){
	//draw_background(animal.x,animal.y,animal.x + animal.width,animal.y + animal.height);
	IDX = animal.curIdx;
	X_START = animal.x;
	Y_START = animal.y;
	X_STOP = animal.x + animal.width;
	Y_STOP = animal.y + animal.height;
	DRAW_START = 1;
	while(!DRAW_DONE);
	DRAW_START = 0;
	//delay_loop();
}

void draw_backgrounds(int num, Animal animals[]){
	draw_background(CANNON_X,CANNON_Y,CANNON_X + CANNON_WIDTH, CANNON_Y + CANNON_HEIGHT);
	for(int i = 0; i < num; i++){
		draw_background(animals[i].x,animals[i].y,animals[i].x + animals[i].width,animals[i].y + animals[i].height);
	}
}

void draw_frame(int num, Animal animals[], Cannon cannon, CannonBall cannonball, FishNet fishnet, int score, int sec, int frame_count){
	//init_background();
	FRAME_DONE = 0;
	//draw_backgrounds(num,prev);
	init_background();
	if(sec >= 0 && sec <= 60){
		draw_CannonBall(cannonball);
		draw_cannon(cannon);
	}
	for(int i = 0; i < num; i++){
		if(!(animals[i].caughtFrame%2))
			draw_animal(animals[i]);
	}
	if(sec >= 0 && sec <= 60){
		draw_FishNet(fishnet);
	}
	if(sec >= -1 && sec <= 60 &&(!(frame_count%2))){
		draw_Score_Ingame(score);
		sec = (sec < 0) ?0 :sec;
		draw_Time_Ingame(sec);
	}
	FRAME_DONE = 1;
}

void draw_cannon(Cannon cannon){
	//draw_background(CANNON_X,CANNON_Y,CANNON_X + CANNON_WIDTH, CANNON_Y + CANNON_HEIGHT);
	IDX = SUPPORT_IDXSTART;
	X_START = SUPPORT_X;
	Y_START = SUPPORT_Y;
	X_STOP = SUPPORT_X + SUPPORT_WIDTH;
	Y_STOP = SUPPORT_Y + SUPPORT_HEIGHT;
	DRAW_START = 1;
	while(!DRAW_DONE);
	DRAW_START = 0;
	IDX = cannon.curIdx;
	X_START = CANNON_X;
	Y_START = CANNON_Y;
	X_STOP = CANNON_X + CANNON_WIDTH;
	Y_STOP = CANNON_Y + CANNON_HEIGHT;
	DRAW_START = 1;
	while(!DRAW_DONE);
	DRAW_START = 0;
}

void draw_CannonBall(CannonBall cannonball){
	if(!cannonball.hidden && cannonball.frame > 3){
		IDX = cannonball.curIdx;
		X_START = cannonball.x;
		Y_START = cannonball.y;
		X_STOP = cannonball.x + CANNON_BALL_WIDTH;
		Y_STOP = cannonball.y + CANNON_BALL_HEIGHT;
		DRAW_START = 1;
		while(!DRAW_DONE);
		DRAW_START = 0;
	}
}

void draw_FishNet(FishNet fishnet){
	if(!fishnet.hidden){
		IDX = fishnet.curIdx;
		X_START = fishnet.x;
		Y_START = fishnet.y;
		X_STOP = fishnet.x + NET_WIDTH;
		Y_STOP = fishnet.y + NET_HEIGHT;
		DRAW_START = 1;
		while(!DRAW_DONE);
		DRAW_START = 0;
	}
}

void draw_Logo(){
	IDX = LOGO_IDXSTART;
	X_START = 320-LOGO_WIDTH/2;
	Y_START = 120-LOGO_HEIGHT/2;
	X_STOP = X_START + LOGO_WIDTH;
	Y_STOP = Y_START + LOGO_HEIGHT;
	DRAW_START = 1;
	while(!DRAW_DONE);
	DRAW_START = 0;
}

void draw_Options(){
	IDX = START_IDXSTART;
	X_START = 320-START_WIDTH/2;
	Y_START = 300-START_HEIGHT/2;
	X_STOP = X_START + START_WIDTH;
	Y_STOP = Y_START + START_HEIGHT;
	DRAW_START = 1;
	while(!DRAW_DONE);
	DRAW_START = 0;
	IDX = HIGHSCORE_IDXSTART;
	X_START = 320-HIGHSCORE_WIDTH/2;
	Y_START = 370-HIGHSCORE_HEIGHT/2;
	X_STOP = X_START + HIGHSCORE_WIDTH;
	Y_STOP = Y_START + HIGHSCORE_HEIGHT;
	DRAW_START = 1;
	while(!DRAW_DONE);
	DRAW_START = 0;
}

void draw_Arrow(int pos){
	//If pos = 0, draw Start
	//If pos = 1, draw HS
	IDX = ARROW_IDXSTART;
	X_START = 185-ARROW_WIDTH/2;
	X_STOP = X_START + ARROW_WIDTH;
	if(pos){
		Y_START = 370-ARROW_HEIGHT/2;
		Y_STOP = Y_START + ARROW_HEIGHT;
	}else{
		Y_START = 300-ARROW_HEIGHT/2;
		Y_STOP = Y_START + ARROW_HEIGHT;
	}
	DRAW_START = 1;
	while(!DRAW_DONE);
	DRAW_START = 0;
}

void draw_Num(int num, int x, int y){
	//If pos = 0, draw Start
	//If pos = 1, draw HS
	IDX = NUMBER_IDXSTART+num;
	X_START = x;
	X_STOP = x + NUMBER_WIDTH;
	Y_START = y;
	Y_STOP = y + NUMBER_HEIGHT;
	DRAW_START = 1;
	while(!DRAW_DONE);
	DRAW_START = 0;
}

void draw_SC(int x, int y){
	IDX = SC_IDXSTART;
	X_START = x;
	X_STOP = x + SC_WIDTH;
	Y_START = y;
	Y_STOP = y + SC_HEIGHT;
	DRAW_START = 1;
	while(!DRAW_DONE);
	DRAW_START = 0;
}

void draw_Score_Ingame(int score){
	IDX = SCORE_IDXSTART;
	X_START = CURR_SCORE_X;
	X_STOP =  CURR_SCORE_X+ SCORE_WIDTH;
	Y_START = CURR_SCORE_Y;
	Y_STOP = CURR_SCORE_Y + SCORE_HEIGHT;
	DRAW_START = 1;
	while(!DRAW_DONE);
	DRAW_START = 0;
	int digit3 = score/100;
	if(digit3 == 0)
		digit3 = 10;
	int digit2 = score/10%10;
	if(digit3 == 10 && digit2 == 0)
		digit2 = 10;
	int digit1 = score%10;
	draw_Num(digit3,CURR_SCORE_X+ SCORE_WIDTH+10 ,CURR_SCORE_Y);
	draw_Num(digit2,CURR_SCORE_X+ SCORE_WIDTH+12+NUMBER_WIDTH ,CURR_SCORE_Y);
	draw_Num(digit1,CURR_SCORE_X+ SCORE_WIDTH+14+NUMBER_WIDTH*2 ,CURR_SCORE_Y);
}


void draw_Time_Ingame(int sec){
	IDX = TIME_IDXSTART;
	X_START = CURR_TIME_X;
	X_STOP =  CURR_TIME_X+ TIME_WIDTH;
	Y_START = CURR_TIME_Y;
	Y_STOP = CURR_TIME_Y + TIME_HEIGHT;
	DRAW_START = 1;
	while(!DRAW_DONE);
	DRAW_START = 0;
	int digit2 = sec/10;
	if(digit2 == 0)
		digit2 = 10;
	int digit1 = sec%10;
	draw_Num(digit2,CURR_TIME_X+ SCORE_WIDTH+12+NUMBER_WIDTH ,CURR_TIME_Y);
	draw_Num(digit1,CURR_TIME_X+ SCORE_WIDTH+14+NUMBER_WIDTH*2 ,CURR_TIME_Y);
}
