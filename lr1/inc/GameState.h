#ifndef HAMMURABI_GAMESTATE_H_
#define HAMMURABI_GAMESTATE_H_

#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>

struct GameState
{
	int round;
	int deadByHugerCount;
	int arrivedCount;
	bool wasPlague;
	int population;
	int bushelsGrownCount;
	int bushelsPerLandCount;
	int bushelsDestroyedCount;
	int bushelsTotalCount;
	int landTotal;
	int landPrice;
	int p;
	int l;
};

void GameStateInit(GameState& state);
void GameStatePrint(GameState state);
bool SaveFileExists(std::string& filename);
bool LoadGameStateFromFile(GameState& state, std::string& filename);
bool SaveGameStateToFile(GameState& state, std::string& filename);
void CheckSaves(GameState& state, std::string savePath);

#endif
