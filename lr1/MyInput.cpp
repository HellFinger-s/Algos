#include <stdio.h>
#include <iostream>
#include <limits>
#include "inc/MyInput.h"


int EnterPositiveInt(int* value);
void EnterBuyLandCout(GameState currentState, int* value);
void EnterSellLandCout(GameState currentState, int* value);
void EnterBushelsForFeed(GameState currentState, int* value);
void EnterLandForSeed(GameState currentState, int* value);

void HandleInput(GameState currentState, InputStruct& inputValues)
{
	printf("Что пожелаешь, повелитель?");
	printf("\nСколько акров земли повелеваешь купить? ");
	EnterBuyLandCout(currentState, &inputValues.buyLandCount);
	printf("\nСколько акров земли повелеваешь продать? ");
	EnterSellLandCout(currentState, &inputValues.sellLandCount);
	printf("\nСколько бушелей пшеницы повелеваешь съесть? ");
	EnterBushelsForFeed(currentState, &inputValues.bushelsForFeedCount);
	printf("\nСколько акров земли повелеваешь засеять? ");
	EnterLandForSeed(currentState, &inputValues.landForCultivateCount);
}

int OfferQuit()
{
	int state = 0;
	printf("Желаете выйти и сохранить игру?\n 1/0:");
	scanf("%d", &state);
	if (state == 1)
		state = QUIT;
	else
		state = PLAYING;
	return state;
}

int EnterPositiveInt(int* value)
{
	int x;
	char tail[2];
	int rc = scanf(" %d%1[^ \t\r\n]", &x, tail);
	if (rc == 1 && x >= 0) {
		*value = x;
		return 1;
	}

	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}
	return 0;                  
}

void EnterBuyLandCout(GameState currentState, int* value)
{
	while (EnterPositiveInt(value) == 0 || *value * currentState.landPrice > currentState.bushelsTotalCount)
	{
		printf("Не могу это выполнить, повелитель. Попробуйте снова.");
	}
}

void EnterSellLandCout(GameState currentState, int* value)
{
	while (EnterPositiveInt(value) == 0 || *value > currentState.landTotal)
	{
		printf("Не могу это выполнить, повелитель. Попробуйте снова.");
	}
}

void EnterBushelsForFeed(GameState currentState, int* value)
{
	while (EnterPositiveInt(value) == 0 || *value > currentState.bushelsTotalCount)
	{
		printf("Не могу это выполнить, повелитель. Попробуйте снова.");
	}
}

void EnterLandForSeed(GameState currentState, int* value)
{
	while (EnterPositiveInt(value) == 0 || *value > currentState.landTotal)
	{
		printf("Не могу это выполнить, повелитель. Попробуйте снова.");
	}
}