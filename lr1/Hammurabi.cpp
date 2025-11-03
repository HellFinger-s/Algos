#include <iostream>
#include <locale.h> 
#include "inc/Parameters.h"
#include "inc/StateCodes.h"
#include "inc/GameState.h"
#include "inc/WorldEvents.h"
#include "inc/MyInput.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	std::string savePath{ "gamestate.txt" };
	GameState currentState;
	GameStateInit(currentState);
	CheckSaves(currentState, savePath);
	InputStruct inputValues;
	int stateCode = PLAYING;

	for (int i = currentState.round; i <= ROUNDS_COUNT && stateCode == PLAYING; i++)
	{
		if (i > 1)
			stateCode = OfferQuit();
		if (stateCode == QUIT)
		{
			SaveGameStateToFile(currentState, savePath);
			break;
		}

		GenerateNewLandPrice(currentState);
		GameStatePrint(currentState);
		HandleInput(currentState, inputValues);
		DoWorldEvents(currentState, inputValues);
		stateCode = CheckLose(currentState);
	}

	HandleStateCode(currentState, stateCode);

	return 0;
}
