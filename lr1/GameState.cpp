#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include "inc/GameState.h"
#include "inc/Parameters.h"


void GameStateInit(GameState& state)
{
	state.round = 1;
	state.deadByHugerCount = 0;
	state.arrivedCount = 0;
	state.wasPlague = false;
	state.population = START_POPULATION;
	state.bushelsGrownCount = 0;
	state.bushelsPerLandCount = 0;
	state.bushelsDestroyedCount = 0;
	state.bushelsTotalCount = START_BUSHELS;
	state.landTotal = START_LAND;
	state.landPrice = 0;
    state.p = 0;
    state.l = 0;
}


void GameStatePrint(GameState state)
{
	printf("Мой повелитель, соизволь поведать тебе\n в году %d твоего высочайшего правления\n", state.round);
	if (state.deadByHugerCount > 0)
		printf("%d человек умерло от голода;\n", state.deadByHugerCount);
	if (state.arrivedCount > 0)
		printf("%d человек прибыло в город;\n", state.arrivedCount);
	if (state.wasPlague)
		printf("Чума уничтожила половину населения\n");
	else
		printf("Хвала богам, чума нас миновала;\n");
	printf("Население города составляет %d человек;\n", state.population);
	printf("Мы собрали %d бушелей пшеницы, по %d бушеля с акра;\n", state.bushelsGrownCount, state.bushelsPerLandCount);
	printf("Крысы истребили %d бушелей пшеницы, оставив %d бушеля в амбарах;\n", state.bushelsDestroyedCount, state.bushelsTotalCount);
	printf("Город сейчас занимает %d акров;\n", state.landTotal);
	printf("1 акр земли стоит сейчас %d бушель.\n", state.landPrice);
}

bool SaveFileExists(std::string& filename)
{
    std::ifstream file(filename);
    return file.good();
}

bool LoadGameStateFromFile(GameState& state, std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        return false;

    std::string line;

    auto readInt = [&file, &line]() -> int {
        std::getline(file, line);
        return std::stoi(line);
    };

    auto readBool = [&file, &line]() -> bool {
        std::getline(file, line);
        return (line == "1");
    };

    try
    {
        state.round = readInt();
        state.deadByHugerCount = readInt();
        state.arrivedCount = readInt();
        state.wasPlague = readBool();
        state.population = readInt();
        state.bushelsGrownCount = readInt();
        state.bushelsPerLandCount = readInt();
        state.bushelsDestroyedCount = readInt();
        state.bushelsTotalCount = readInt();
        state.landTotal = readInt();
        state.landPrice = readInt();
        state.p = readInt();
        state.l = readInt();
    }
    catch (const std::exception&)
    {
        return false;
    }

    return file.good() || file.eof();
}

bool SaveGameStateToFile(GameState& state, std::string& filename)
{
    std::ofstream file(filename);
    if (!file.is_open())
        return false;

    file << state.round << '\n';
    file << state.deadByHugerCount << '\n';
    file << state.arrivedCount << '\n';
    file << (state.wasPlague ? "1" : "0") << '\n';
    file << state.population << '\n';
    file << state.bushelsGrownCount << '\n';
    file << state.bushelsPerLandCount << '\n';
    file << state.bushelsDestroyedCount << '\n';
    file << state.bushelsTotalCount << '\n';
    file << state.landTotal << '\n';
    file << state.landPrice << '\n';
    file << state.p << '\n';
    file << state.l << '\n';

    return file.good();
}


void CheckSaves(GameState &state, std::string savePath)
{
    if (SaveFileExists(savePath))
    {
        int answer = 0;
        printf("Найдена сохраненная игра, желаете продолжить?\n 1/0:");
        scanf_s("%d", &answer, 1024);
        if (answer == 1)
            LoadGameStateFromFile(state, savePath);
    }
}