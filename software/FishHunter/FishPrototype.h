#include "Specifics.h"
#include "Animal.h"
#pragma once
//int bwfish[] = BWFISH;
//int pfish[] = PFISH;


//Create Prototypes to quickly populate fish

//What really matters is y location, step size, and function
static Animal BW_FISH = {.pat = BWFISH, .len = BWFISH_LEN,\
		.x = 610, .y = 200, .width = BWFISH_WIDTH,\
		.height = BWFISH_HEIGHT, .point = BWFISH_PT,.curIdx = BWFISH_IDXSTART,\
		.idxStart = BWFISH_IDXSTART, .velocity = 3, .caught = 0, .caughtFrame = 0};

static Animal P_FISH = {.pat = PFISH, .len = PFISH_LEN, .x = 15, .y = 70,\
		.width = PFISH_WIDTH, .height = PFISH_HEIGHT, .point = PFISH_PT,\
		.curIdx = PFISH_IDXSTART, .idxStart = PFISH_IDXSTART, .velocity = 3, .caught = 0, .caughtFrame = 0};

static Animal Y_FISH = {.pat = YFISH, .len = YFISH_LEN, .x = 15, .y = 70,\
		.width = YFISH_WIDTH, .height = YFISH_HEIGHT, .point = YFISH_PT,\
		.curIdx = YFISH_IDXSTART, .idxStart = YFISH_IDXSTART, .velocity = 3, .caught = 0, .caughtFrame = 0};

static Animal FLAT_FISH = {.pat = FLATFISH, .len = FLATFISH_LEN, .x = 15, .y = 70,\
		.width = FLATFISH_WIDTH, .height = FLATFISH_HEIGHT, .point = FLATFISH_PT,\
		.curIdx = FLATFISH_IDXSTART, .idxStart =FLATFISH_IDXSTART, .velocity = 3, .caught = 0, .caughtFrame = 0};

static Animal R_FISH = {.pat = RFISH, .len = RFISH_LEN, .x = 15, .y = 70,\
		.width = RFISH_WIDTH, .height = RFISH_HEIGHT, .point = RFISH_PT,\
		.curIdx = RFISH_IDXSTART, .idxStart = RFISH_IDXSTART, .velocity = 3, .caught = 0, .caughtFrame = 0};

static Animal BLU_FISH = {.pat = BLUFISH, .len = BLUFISH_LEN, .x = 15, .y = 70,\
		.width = BLUFISH_WIDTH, .height = BLUFISH_HEIGHT, .point = BLUFISH_PT,\
		.curIdx = BLUFISH_IDXSTART, .idxStart = BLUFISH_IDXSTART, .velocity = 3, .caught = 0, .caughtFrame = 0};
