#ifndef HAMMURABI_WORLDEVENTS_H_
#define HAMMURABI_WORLDEVENTS_H_

#include "GameState.h"
#include "Parameters.h"
#include "MyInput.h"

void DoWorldEvents(GameState& state, InputStruct inputValues);
void GenerateNewLandPrice(GameState& state);
void FeedRats(GameState& state);
void FeedCitizens(GameState& state, int bushelsForFeedCount);
void CountArrived(GameState& state);
void Plague(GameState& state);
void CultivateLand(GameState& state, int landForCultivateCount);
void SellLand(GameState& state, int landCount);
void BuyLand(GameState& state, int landCount);
int CheckLose(GameState state);
void HandleStateCode(GameState state, int stateCode);

#endif
