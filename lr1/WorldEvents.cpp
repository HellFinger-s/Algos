#include <cstdlib>
#include <ctime>
#include "inc/WorldEvents.h"
#include "inc/StateCodes.h"


void TickRound(GameState& state);
void GenerateLandFertility(GameState& state);

void GenerateNewLandPrice(GameState& state)
{
	srand(time(NULL));
	state.landPrice = rand() % (MAX_LAND_PRICE - MIN_LAND_PRICE + 1) + MIN_LAND_PRICE;
}

void GenerateLandFertility(GameState& state)
{
	srand(time(NULL));
	state.bushelsPerLandCount = rand() % (MAX_BUSHELS_PER_LAND - MIN_BUSHELS_PER_LAND + 1) + MIN_BUSHELS_PER_LAND;
}

void DoWorldEvents(GameState& state, InputStruct inputValues)
{
	BuyLand(state, inputValues.buyLandCount);
	SellLand(state, inputValues.sellLandCount);
	FeedCitizens(state, inputValues.bushelsForFeedCount);
	CountArrived(state);
	Plague(state);
	GenerateLandFertility(state);
	CultivateLand(state, inputValues.landForCultivateCount);
	FeedRats(state);
	TickRound(state);
}

void FeedRats(GameState& state)
{
	srand(time(NULL));
	int bushelsEaten = rand() % int(ceil(RATS_MULTIPLIER * state.bushelsTotalCount + 1));
	state.bushelsDestroyedCount = bushelsEaten;
	state.bushelsTotalCount -= bushelsEaten;
}

void FeedCitizens(GameState& state, int bushelsForFeedCount)
{
	int maximumFedCount = bushelsForFeedCount / CITIZEN_CONSUMPTION;
	int remainCitizensCount = maximumFedCount - state.population;
	if (remainCitizensCount >= 0)
	{
		state.p += 0;
		state.deadByHugerCount = 0;
		state.bushelsTotalCount = state.bushelsTotalCount - bushelsForFeedCount + remainCitizensCount * CITIZEN_CONSUMPTION;
	}
	else
	{
		state.p += remainCitizensCount * -100 / state.population;
		state.bushelsTotalCount -= bushelsForFeedCount;
		state.population = maximumFedCount;
		state.deadByHugerCount = remainCitizensCount * -1;
	}
}

void CountArrived(GameState& state)
{
	int newCount = ceil(state.deadByHugerCount / 2 + (5 - state.bushelsPerLandCount) * state.bushelsTotalCount / 600 + 1);
	if (newCount < 0)
		newCount = 0;
	if (newCount > MAX_ARRIVED)
		newCount = MAX_ARRIVED;
	state.arrivedCount = newCount;
	state.population += newCount;
}

void Plague(GameState& state)
{
	srand(time(NULL));
	int plagueCheck = rand() % 101;
	if (plagueCheck <= PLAGUE_CHANCE)
	{
		state.population = state.population / 2;
		state.wasPlague = true;
	}
	else
		state.wasPlague = false;
}

void CultivateLand(GameState& state, int landCount)
{
	int maxCultivatedLandCount = state.population * CITIZEN_MAX_CULTIVATED;
	if (landCount <= maxCultivatedLandCount)
		state.bushelsGrownCount = state.bushelsPerLandCount * landCount;
	else
		state.bushelsGrownCount = state.bushelsPerLandCount * maxCultivatedLandCount;
	state.bushelsTotalCount += state.bushelsGrownCount;
}

void SellLand(GameState& state, int landCount)
{
	state.landTotal -= landCount;
	state.bushelsTotalCount += landCount * state.landPrice;
	state.l -= landCount;
}

void BuyLand(GameState& state, int landCount)
{
	state.landTotal += landCount;
	state.bushelsTotalCount -= landCount * state.landPrice;
	state.l += state.landTotal;
}

void TickRound(GameState& state)
{
	state.round += 1;
}

int CheckLose(GameState state)
{
	if (state.population == 0 || state.deadByHugerCount / state.population * 100 > MAX_DEAD_PERCENT_BY_HUGER)
		return LOSE;
	return PLAYING;
}

void HandleStateCode(GameState state, int stateCode)
{
	if (stateCode == PLAYING)
	{
		int pPercent = state.p / ROUNDS_COUNT;
		int lCount = state.l / ROUNDS_COUNT;
		if (pPercent > P_LOW_BORDER && lCount < L_LOW_BORDER)
			printf("Из-за вашей некомпетентности в управлении, народ устроил бунт, и изгнал вас их города.Теперь вы вынуждены влачить жалкое существование в изгнании");
		else if (pPercent > P_MIDDLE_BORDER && lCount < L_MIDDLE_BORDER)
			printf("«Вы правили железной рукой, подобно Нерону и Ивану Грозному.Народ вздохнул с облегчением, и никто больше не желает видеть вас правителем");
		else if (pPercent > P_HIGH_BORDER && lCount < L_HIGH_BORDER)
			printf("Вы справились вполне неплохо, у вас, конечно, есть недоброжелатели, но многие хотели бы увидеть вас во главе города снова");
		else
			printf("Фантастика! Карл Великий, Дизраэли и Джефферсон вместе не справились бы лучше");
	}

}