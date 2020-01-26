#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "Animal.h"
#include "keyboard.h"
#include "Draw.h"
#include "Cannon.h"
#include "Specifics.h"

#include "FishPrototype.h"
#include "GameLogic.h"
#include "CannonBall.h"

#include "CannonBallPrototype.h"
#include "FishNetPrototype.h"

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

GameState playGame(){
	int total;		//Total number of fish
	int nums[NUM_TYPE_FISH];	//Number of each type of fish
	//Space : 44
	int power_use = 0;
	int power_calc = 0;
	int key = 0;
	int prevkey = 0;
	int total_score = 0;
	int prev_total = 0;
	//printf("START\n");
	//setTimeout(5000);
	//printf("Done\n");
	int msec = 0;
	int prevsec = 0;
	int sec = 0;

	randomNumbers(nums, &total);	//generate necessary random numbers

	Animal animals[total];		//Array that store animals

	generateFish(nums, animals);	//Generate fish randomly

	//printf("Start enumerating\n");

	Cannon cannon = {.degree = 90, .curIdx = 12, .idxStart = CANNON_IDXSTART};
	CannonBall cannonball = CANNON_BALL_PRO;
	FishNet fishnet = FISH_NET_PRO;
	init_background();	//Initialize background
	printf("Start Gaming\n");
	FRAME_DONE = 1;

	int flag = 0;	//If flag is 0, naturally stop. If flag is 1, forced stop
	clock_t before = clock();
	while(1){
		prevkey = key;
		key = get_key();
		if(key == 41){
			flag = 1;
			break;
		}
		power_calc = keyPress(key,power_calc);
		//printf("power: %d\n", power_calc/2);
		//printf("Key Code : %d\n",key);
		move_cannon(&cannon, key);
		//draw_cannon(cannon);
		updateFishNet(&fishnet, cannonball);
		updateCannonBall(cannon.degree, prevkey, key, power_use, &cannonball);
		showpower(power_use);
		power_use = power_calc;

		draw_frame(total,animals,cannon,cannonball,fishnet,total_score, 60-sec,0);
		delay_loop();
		//copyAnimals(total ,animals, prevs);
		updateFish(total, animals, fishnet, &total_score);
		/*if(total_score != prev_total)
			printf("Total Score : %d\n",total_score);*/
		prev_total = total_score;

		clock_t difference = clock() - before;
		msec = difference * 1000 / CLOCKS_PER_SEC;
		//printf("Time taken %d seconds %d milliseconds\n",msec/1000, msec%1000);
		sec = msec/1000;
		if(sec > 60){
			int frame_count = 1;
			for(int i = 0; i < 7; i++){
				draw_frame(total,animals,cannon,cannonball,fishnet,total_score, 60-sec,frame_count);
				frame_count++;
				setTimeout(500);
			}
			break;
		}
		/*if(sec != prevsec)
			printf("Time : %d\n",sec);*/
		prevsec = sec;
	}
	printf("Time UP! Your Score: %d\n",total_score);
	GameState gamestate = {.time = sec, .score = total_score, .state = flag};
	return gamestate;
}

char displayMenu(){
	init_background();
	draw_Logo();
	draw_Options();
	int key;
	int pos = 0;
	//Enter : 40
	char option;
	while(1){
		FRAME_DONE = 0;
		init_background();
		draw_Logo();
		draw_Options();
		key = get_key();
		if(pos == 0 && key == 81)
			pos = 1;
		else if(pos == 1 && key == 82)
			pos = 0;
		draw_Arrow(pos);
		FRAME_DONE = 1;
		delay_loop();
		//printf("Key Code : %d\n",key);
		if(key == 40){
			option = pos ?'s':'p';
			break;
		}
	}
	return option;
}

//scores[0] : Highest score
//scores[1] : Second high
void updateScores(int* scores, int cur_score){
	for(int i = 0; i < 5; i++){
		if(cur_score > scores[i]){
			int temp = scores[i];
			int temp2;
			scores[i] = cur_score;
			for(int j = i+1; j < 5; j++){
				temp2 = scores[j];
				scores[j] = temp;
				temp = temp2;
			}
			return;
		}
	}
}

void displayScores(int* scores){
	init_background();
	int key = 0;
	IDX = HIGHSCORE_IDXSTART;
	X_START = 320-HIGHSCORE_WIDTH/2;
	Y_START = 120-HIGHSCORE_HEIGHT/2;
	X_STOP = X_START + HIGHSCORE_WIDTH;
	Y_STOP = Y_START + HIGHSCORE_HEIGHT;
	DRAW_START = 1;
	while(!DRAW_DONE);
	DRAW_START = 0;
	for(int i = 1; i<=5; i++){
		draw_Num(i,280, 160 + i * 35);
		draw_SC(282+NUMBER_WIDTH, 160+i*35);
		int digit3 = scores[i-1]/100;
		if(digit3 == 0)
			digit3 = 10;
		int digit2 = scores[i-1]/10%10;
		if(digit3 == 10 && digit2 == 0)
			digit2 = 10;
		int digit1 = scores[i-1]%10;
		draw_Num(digit3,318+NUMBER_WIDTH,160+i*35);
		draw_Num(digit2,320+NUMBER_WIDTH*2,160+i*35);
		draw_Num(digit1,322+NUMBER_WIDTH*3,160+i*35);
	}
	while(1){
		key = get_key();
		if(key == 41){
			break;
		}
	}
}
