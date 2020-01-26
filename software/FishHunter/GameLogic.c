#include "FishPrototype.h"
#include "Specifics.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "Cannon.h"
#include "CannonBall.h"
#include "CannonBallPrototype.h"
#include "FishNet.h"
#include "FishNetPrototype.h"
//BWFISH 4 - 7
//PFISH 2 - 4

void randomNumbers(int* nums, int* total){
	int BWNUM = rand() % (BW_FISH_NUM_MAX - BW_FISH_NUM_MIN + 1) + BW_FISH_NUM_MIN;
	int PNUM = rand() % (P_FISH_NUM_MAX - P_FISH_NUM_MIN + 1) + P_FISH_NUM_MIN;
	int YNUM = rand() % (Y_FISH_NUM_MAX - Y_FISH_NUM_MIN + 1) + Y_FISH_NUM_MIN;
	int RNUM = rand() % (R_FISH_NUM_MAX - R_FISH_NUM_MIN + 1) + R_FISH_NUM_MIN;
	int FLATNUM = rand() % (FLAT_FISH_NUM_MAX - FLAT_FISH_NUM_MIN + 1) + FLAT_FISH_NUM_MIN;
	int BLUNUM = rand() % (BLU_FISH_NUM_MAX - BLU_FISH_NUM_MIN + 1) + BLU_FISH_NUM_MIN;
	nums[0] = BWNUM;
	nums[1] = PNUM;
	nums[2] = YNUM;
	nums[3] = RNUM;
	nums[4] = FLATNUM;
	nums[5] = BLUNUM;

	*total = BWNUM + PNUM + YNUM + RNUM + FLATNUM + BLUNUM ;
}

void generateFish(int* nums, Animal * animals){
	//First part corresponds to BW_FISH
	//Second part corresponds to P_FISH
	int idx = 0;
	for(int i = 0; i < NUM_TYPE_FISH; i++){
		int curNum = nums[i];
		switch(i){
		case 0 : //BW_FISH
			for(int j = 0; j < curNum; j++){
				Animal bwfish = BW_FISH;
				bwfish.y = rand() % (480 - BWFISH_HEIGHT);
				bwfish.x = rand() % (640 - BWFISH_WIDTH);
				bwfish.velocity = -1 * (rand() % (BW_FISH_VELO_MAX - BW_FISH_VELO_MIN + 1) + BW_FISH_VELO_MIN);
				bwfish.func = rand() % 2;
				animals[idx + j] = bwfish;
			}
			break;
		case 1: //P_FISH
			for(int j = 0; j < curNum; j++){
				Animal pfish = P_FISH;
				pfish.y = rand() % (480 - PFISH_HEIGHT);
				pfish.x = rand() % (640 - PFISH_WIDTH);
				pfish.velocity = (rand() % (P_FISH_VELO_MAX - P_FISH_VELO_MIN + 1) + P_FISH_VELO_MIN);
				pfish.func = rand() % 2;
				animals[idx + j] = pfish;
			}
			break;
		case 2: //Y_FISH
			for(int j = 0; j < curNum; j++){
				Animal yfish = Y_FISH;
				yfish.y = rand() % (480 - YFISH_HEIGHT);
				yfish.x = rand() % (640 - YFISH_WIDTH);
				yfish.velocity = -1 * ((rand() % (Y_FISH_VELO_MAX - Y_FISH_VELO_MIN + 1) + Y_FISH_VELO_MIN));
				yfish.func = rand() % 2;
				animals[idx + j] = yfish;
			}
			break;

		case 3: //R_FISH
			for(int j = 0; j < curNum; j++){
				Animal rfish = R_FISH;
				rfish.y = rand() % (480 - RFISH_HEIGHT);
				rfish.x = rand() % (640 - RFISH_WIDTH);
				rfish.velocity = ((rand() % (R_FISH_VELO_MAX - R_FISH_VELO_MIN + 1) + R_FISH_VELO_MIN));
				rfish.func = 2;
				animals[idx + j] = rfish;
			}
			break;

		case 4: //FLAT_FISH
			for(int j = 0; j < curNum; j++){
				Animal flatfish = FLAT_FISH;
				flatfish.y = rand() % (480 - FLATFISH_HEIGHT);
				flatfish.x = rand() % (640 - FLATFISH_WIDTH);
				flatfish.velocity = -1 * ((rand() % (FLAT_FISH_VELO_MAX - FLAT_FISH_VELO_MIN + 1) + FLAT_FISH_VELO_MIN));
				flatfish.func = 2;
				animals[idx + j] = flatfish;
			}
			break;

		case 5: //BLU_FISH
			for(int j = 0; j < curNum; j++){
				Animal blufish = BLU_FISH;
				blufish.y = rand() % (480 - BLUFISH_HEIGHT);
				blufish.x = rand() % (640 - BLUFISH_WIDTH);
				blufish.velocity = -1 * ((rand() % (BLU_FISH_VELO_MAX - BLU_FISH_VELO_MIN + 1) + BLU_FISH_VELO_MIN));
				blufish.func = rand() % 2;
				animals[idx + j] = blufish;
			}
			break;
		}
		idx += curNum;
	}
}

void copyAnimals(int total, Animal* animals, Animal* prevs){
	for(int i = 0; i < total; i++)
		prevs[i] = animals[i];
}

int isCaught(FishNet fishnet, Animal animal){
	float cent_X_FishNet = fishnet.x + NET_WIDTH/2.0;
	float cent_Y_FishNet = fishnet.y + NET_HEIGHT/2.0;
	float cent_X_animal = animal.x + animal.width/2.0;
	float cent_Y_animal = animal.y + animal.height/2.0;

	float distance_sqr = (cent_X_animal - cent_X_FishNet) * (cent_X_animal - cent_X_FishNet)\
			+ (cent_Y_animal - cent_Y_FishNet) * (cent_Y_animal - cent_Y_FishNet);
	return ((fishnet.frame == 4) && (distance_sqr < NET_RADIUS_SQR));
}

void updateFish(int total, Animal* animals, FishNet fishnet, int* total_score){
	for(int i = 0; i < total; i++){
		if(animals[i].caught){
			animals[i].caughtFrame++;
			if(animals[i].caughtFrame > 8){
				animals[i].x = 640;
				animals[i].y = rand() % (480 - animals[i].height);
				animals[i].caught = 0;
				animals[i].caughtFrame = 0;
			}
			continue;
		}
		if(!fishnet.hidden){
			if(isCaught(fishnet, animals[i])){
				animals[i].caught = 1;
				*total_score += animals[i].point;
				continue;
			}
		}
		animals[i].x += animals[i].velocity;
		switch(animals[i].func){
		case 0 : //y unchanged
			break;
		case 1:
			//animals[i].y = func1(animals[i].x, animals[i].y);
			break;
		case 2:
			animals[i].y = func2(animals[i]);
			break;
		}
		animals[i].curIdx = ((animals[i].curIdx - animals[i].idxStart+1) % animals[i].len) + animals[i].idxStart;
		if(animals[i].x <= -1*(animals[i].width)){
			animals[i].x = 640;
			animals[i].y = rand() % (480 - animals[i].height);
		}
		if(animals[i].x > 640){
			animals[i].x = -1*(animals[i].width)+3;
			animals[i].y = rand() % (480 - animals[i].height);
		}
		if(animals[i].y > 480){
			animals[i].y = -1*(animals[i].height) + 3;
			animals[i].x = rand() % (640 - animals[i].width);
		}
		if(animals[i].y <= -1*(animals[i].height)){
			animals[i].y = 480;
			animals[i].x = rand() % (640 - animals[i].width);
		}
	}
}

void move_cannon(Cannon* cannon, int key){
	if(key == 7 || key == 79){
		if(cannon -> curIdx != 1){
			cannon -> curIdx --;
			cannon -> degree -= 8;
		}
	}
	else if(key == 4 || key == 80){
		if(cannon -> curIdx != 23){
			cannon -> curIdx ++;
			cannon -> degree += 8;
		}
	}
}

float maxLength(int degree){
	if(degree > 56 && degree < 124)
		return 430.0 / sin(degree / 180.0 * PI);
	else
		return abs(320.0 / cos(degree / 180.0 * PI));
}

void updateCannonBall(int deg, int prevkey, int key, int power, CannonBall* cannonball){
	if(prevkey == 44 && key != 44 && cannonball -> fix == 0){
		cannonball -> hidden = 0;
		//cannonball -> deg = deg;
		cannonball -> fix = 1;
		cannonball -> distance = maxLength(deg)/8.0 * power;
		cannonball -> stopY = 430 - ((cannonball -> distance) * sin(deg / 180.0 * PI));
		cannonball -> x_velo = CANNON_BALL_VELO * cos(deg / 180.0 * PI);
		cannonball -> y_velo = -1 * sin( deg / 180.0 * PI) * CANNON_BALL_VELO;
		//printf("stopY: %d\n",cannonball -> stopY );
	}

	if(!(cannonball -> hidden)){
		//x_velo = CANNON_BALL_VELO * cos(degree / 180.0 * PI);
		//y_velo = -1 * sin( degree / 180.0 * PI) * CANNON_BALL_VELO;

		if(cannonball->y <= cannonball->stopY)
			*cannonball = CANNON_BALL_PRO;

		cannonball -> x += cannonball -> x_velo;
		cannonball -> y += cannonball -> y_velo;
		cannonball -> curIdx = ((cannonball -> curIdx - CANNON_BALL_IDXSTART+1) % CANNON_BALL_LEN) + CANNON_BALL_IDXSTART;
		cannonball -> frame ++;

		if(cannonball -> x > 640 || cannonball -> x <= -1*CANNON_BALL_WIDTH || cannonball -> y > 480 || cannonball -> y <= -1*CANNON_BALL_HEIGHT){
			*cannonball = CANNON_BALL_PRO;
		}
	}
}


void updateFishNet(FishNet* fishnet, CannonBall cannonball){
	if(cannonball.y <= cannonball.stopY){
		fishnet -> hidden = 0;
		fishnet -> x = cannonball.x + CANNON_BALL_WIDTH/2 - NET_WIDTH/2;
		fishnet -> y = cannonball.y + CANNON_BALL_HEIGHT/2 - NET_HEIGHT/2;
	}
	if(!fishnet -> hidden){
		fishnet -> curIdx += 1;
		if(fishnet -> curIdx > 28)
			fishnet -> curIdx = 28;
		fishnet -> frame ++;
		if(fishnet -> frame > 10)
			*fishnet = FISH_NET_PRO;
	}
}

//Trajectory functions of fish

//Function 0 is y unchanged -- going a straight line

//Function 1 is cos/sin with random parameters
int func1(Animal animal){
	//double freq =  0.01 * (rand() % (FREQ_MAX - FREQ_MIN + 1) + FREQ_MIN);
	//int amp = rand() % (AMP_MAX - AMP_MIN + 1) + AMP_MIN;
	return 10*sin(0.08*animal.x) + animal.y;
}

int func2(Animal animal){
	return animal.y + animal.velocity / 3 * 2;
}
//

/********Key Press Detector******/
int keyPress(int key, int power){
	//Power: 8 levels
	int new_power = power;
	if(key == 44){
		new_power += 1;
		if(new_power >= 8)
			new_power = 8;
	}
	else
		new_power = 0;
	return new_power;
}

void showpower(int power){
	switch(power){
	case 1:
		* POWER_PTR = 1;
		break;
	case 2:
		* POWER_PTR = 3;
		break;
	case 3:
		* POWER_PTR = 7;
		break;
	case 4:
		* POWER_PTR = 15;
		break;
	case 5:
		* POWER_PTR = 31;
		break;
	case 6:
		* POWER_PTR = 63;
		break;
	case 7:
		* POWER_PTR = 127;
		break;
	case 8:
		* POWER_PTR = 255;
		break;
	default:
		* POWER_PTR = 0;
	}
}

void setTimeout(int milliseconds)
{
    // If milliseconds is less or equal to 0
    // will be simple return from function without throw error
    if (milliseconds <= 0) {
        return;
    }

    // a current time of milliseconds
    int milliseconds_since = clock() * 1000 / CLOCKS_PER_SEC;

    // needed count milliseconds of return from this timeout
    int end = milliseconds_since + milliseconds;

    // wait while until needed time comes
    do {
        milliseconds_since = clock() * 1000 / CLOCKS_PER_SEC;
    } while (milliseconds_since <= end);
}
