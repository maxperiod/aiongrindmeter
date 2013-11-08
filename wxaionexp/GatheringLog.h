#include <string>
#include <sstream>
#include <vector>
#include <ctime>

using namespace std;

struct GatheringRecord{
	string name;
	//int nameHash;
	int successes;
	int failures;
	int cancellations;
};

struct GatherLevelUps{
	int level;
	int numGathers;
};

class GatheringLog{
public:
	vector<GatheringRecord> gatheringRecord;
	vector<GatheringRecord> craftingRecord;

	vector<GatherLevelUps> gatherLevelUps;
	vector<GatherLevelUps> craftLevelUps;

	int numGatheringSuccesses;
	int numGatheringFailures;
	int numGatheringCancellations;

	int numCraftingSuccesses;
	int numCraftingFailures;
	int numCraftingCancellations;
	int numCraftingProcs;

	int numGatheredSinceLevelUp;
	int numCraftedSinceLevelUp;

	int lastNumGatheredToLevelUp;
	int lastNumCraftedToLevelUp;

	int gatheringLvl;
	int craftingLvl;

	string lastItemGathered;

	bool isLevelCapped;
	bool currentlyCrafting;
	bool isInventoryFull;

	GatheringLog();

	void gather(string line);
	void gatherSuccess();
	void gatherFailure(string line);
	void gatherCancel();

	void craft(string line);
	void craftSuccess();
	void craftFailure(string line);
	void craftCancel();
	void clearCraftingStatus();

	void inventoryFull();

	float getGatherSuccessRate();
	float getGatherFailureRate();
	float getGatherCancellationRate();

	float getCraftSuccessRate();
	float getCraftFailureRate();
	float getCraftCancellationRate();
	float getCraftProcRate();

	void gainGatherExp();
	void gainCraftExp();

	void gatherLevelUp(string line);
	void craftLevelUp(string line);

	int estimateNumGathersToNextLevel;
	int estimateNumCraftsToNextLevel;	
	
	void skillLevelTooLow();
	void levelCapped();	

	float getNumGatheredPerHour();
	float getNumCraftedPerHour();

	float getNumGatherLvlsPerHour();
	float getNumCraftLvlsPerHour();
	
	void start();
	void reset();

	void tickCleanUp();

private:
	float startTime;



	bool gatheringListHasItem(string name);
	bool craftingListHasItem(string name);

	void calculateNextLevelRequirementEstimates();
};