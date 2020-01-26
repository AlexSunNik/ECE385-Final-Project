#pragma once

#define PI 3.1415926
//Properties
/******AVALON INTERFACE RELATED*********/
#define IDX DRAW_PTR[0]
#define X_START DRAW_PTR[1]
#define Y_START DRAW_PTR[2]
#define X_STOP DRAW_PTR[3]
#define Y_STOP DRAW_PTR[4]
#define FRAME_DONE DRAW_PTR[5]
#define DRAW_START DRAW_PTR[6]
#define DRAW_DONE DRAW_PTR[7]
static volatile unsigned int * DRAW_PTR = (unsigned int *) 0x00000020;
static volatile unsigned int * POWER_PTR = (unsigned int *) 0x00000040;
/*******DRAWING/IMAGES RELATES**********/
#define BACKGROUND 0
#define PFISH {41,42,43,44}		//Purple Fish
#define BWFISH {51,52,53,54,55,56,57,58}	//Black White Fish
#define RFISH {61,62,63,64}
#define YFISH {71,72,73,74}
#define FLATFISH {81,82,83,84,85}
#define BLUFISH {91,92,93,94}

#define NET {25,26,27,28}
#define CANNON_BALL {29,30,31,32}

#define BWFISH_WIDTH 31
#define BWFISH_HEIGHT 45
#define BWFISH_PT 3
#define BWFISH_LEN 8
#define BWFISH_IDXSTART 51

#define PFISH_WIDTH 51
#define PFISH_HEIGHT 59
#define PFISH_PT 5
#define PFISH_LEN 4
#define PFISH_IDXSTART 41

#define RFISH_WIDTH 40
#define RFISH_HEIGHT 43
#define RFISH_PT 5
#define RFISH_LEN 4
#define RFISH_IDXSTART 61

#define YFISH_WIDTH 34
#define YFISH_HEIGHT 27
#define YFISH_PT 1
#define YFISH_LEN 4
#define YFISH_IDXSTART 71

#define FLATFISH_WIDTH 111
#define FLATFISH_HEIGHT 42
#define FLATFISH_PT 8
#define FLATFISH_LEN 5
#define FLATFISH_IDXSTART 81

#define BLUFISH_WIDTH 34
#define BLUFISH_HEIGHT 25
#define BLUFISH_PT 3
#define BLUFISH_LEN 4
#define BLUFISH_IDXSTART 91

#define CANNON_WIDTH 212
#define CANNON_HEIGHT 108
#define CANNON_IDXSTART 1
#define CANNON_X 214
#define CANNON_Y 372

#define SUPPORT_WIDTH 70
#define SUPPORT_HEIGHT 40
#define SUPPORT_IDXSTART 24
#define SUPPORT_X 290
#define SUPPORT_Y 440

#define NET_WIDTH 101
#define NET_HEIGHT 84
#define NET_LEN 4
#define NET_IDXSTART 25
#define NET_RADIUS_SQR	2139

#define CANNON_BALL_WIDTH 50
#define CANNON_BALL_HEIGHT 58
#define CANNON_BALL_LEN 4
#define CANNON_BALL_IDXSTART 29

#define LOGO_WIDTH 151
#define LOGO_HEIGHT 121
#define LOGO_IDXSTART 99

#define ARROW_WIDTH 28
#define ARROW_HEIGHT 11
#define ARROW_IDXSTART 100

#define START_WIDTH 96
#define START_HEIGHT 29
#define START_IDXSTART 95

#define HIGHSCORE_WIDTH 197
#define HIGHSCORE_HEIGHT 39
#define HIGHSCORE_IDXSTART 96

#define SCORE_WIDTH 75
#define SCORE_HEIGHT 20
#define SCORE_IDXSTART 97

#define TIME_WIDTH 74
#define TIME_HEIGHT 22
#define TIME_IDXSTART 98

#define NUMBER_WIDTH 16
#define NUMBER_HEIGHT 21
#define NUMBER_IDXSTART 101
#define NUMBER_LEN 11

#define SC_WIDTH 6
#define SC_HEIGHT 21
#define SC_IDXSTART 112

//DELAY LOOPS
#define DELAY_TIME 8000

/****GAME LOGIC RELATED****/

#define NUM_TYPE_FISH 6
//TRAJECTORY FUNCTION
#define FREQ_MIN 5
#define FREQ_MAX 10
#define AMP_MIN	10
#define AMP_MAX 20
//FISH NUMBER AND VELOCITY
#define BW_FISH_NUM_MIN 4	//MIN and MAX Number of certain types of fish appearing
#define BW_FISH_NUM_MAX 7
#define BW_FISH_VELO_MIN 2
#define BW_FISH_VELO_MAX 4

#define P_FISH_NUM_MIN 3
#define P_FISH_NUM_MAX 5
#define P_FISH_VELO_MIN 3
#define P_FISH_VELO_MAX 5

#define Y_FISH_NUM_MIN 8
#define Y_FISH_NUM_MAX 15
#define Y_FISH_VELO_MIN 5
#define Y_FISH_VELO_MAX 10

#define FLAT_FISH_NUM_MIN 1
#define FLAT_FISH_NUM_MAX 3
#define FLAT_FISH_VELO_MIN 7
#define FLAT_FISH_VELO_MAX 13

#define BLU_FISH_NUM_MIN 4
#define BLU_FISH_NUM_MAX 8
#define BLU_FISH_VELO_MIN 3
#define BLU_FISH_VELO_MAX 8

#define R_FISH_NUM_MIN 3
#define R_FISH_NUM_MAX 5
#define R_FISH_VELO_MIN 3
#define R_FISH_VELO_MAX 5


#define CANNON_BALL_VELO 30

#define CURR_SCORE_X 480
#define CURR_SCORE_Y 80
#define CURR_TIME_X 480
#define CURR_TIME_Y 30

//Functions
static void delay_loop(){
	for(int i = 0; i < DELAY_TIME; i++);
}
