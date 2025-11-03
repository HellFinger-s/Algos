#ifndef HAMMURABI_MYINPUT_H_
#define HAMMURABI_MYINPUT_H_

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#endif

#include "StateCodes.h"
#include "GameState.h"

struct InputStruct
{
	int sellLandCount;
	int buyLandCount;
	int bushelsForFeedCount;
	int landForCultivateCount;
};

void HandleInput(GameState currentState, InputStruct& inputValues);
int OfferQuit();

#endif
