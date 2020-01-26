/*******************
1: Black-White Fish Point:3pts
2: Purple Fish Point:5pts

*******************/
#pragma once

typedef struct animalStruct{
	int point;
	int curIdx;	//Current index in the animation frames
	int idxStart;
	int* pat;
	int len;	//Length of the frames(GIF)
	int x;
	int y;
	int width;
	int height;
	int velocity;	//Pos means going right, vice versa
	int func;
	int caught;
	int caughtFrame;
}Animal;
