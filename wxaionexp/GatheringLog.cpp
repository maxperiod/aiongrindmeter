#include "GatheringLog.h"

#include <iostream>

GatheringLog::GatheringLog(){
	reset();
}

void GatheringLog::start(){
	reset();
	startTime = clock();
}

void GatheringLog::reset(){
	numGatheringSuccesses = 0;
	numGatheringFailures = 0;
	numGatheringCancellations = 0;

	numCraftingSuccesses = 0;
	numCraftingFailures = 0;
	numCraftingCancellations = 0;
	numCraftingProcs = 0;

	gatheringLvl = -1;	
	craftingLvl = -1;

	numGatheredSinceLevelUp = -2;	//For this value, -2 represents unknown value instead of -1. After level up it sets to -1 for some weird reasons.
	numCraftedSinceLevelUp = -2;

	lastNumGatheredToLevelUp = -2;
	lastNumCraftedToLevelUp = -2;
	
	currentlyCrafting = false;
	lastItemGathered = "";
	gatheringRecord.erase(gatheringRecord.begin(), gatheringRecord.end());
	craftingRecord.erase(craftingRecord.begin(), craftingRecord.end());
	
	gatherLevelUps.erase(gatherLevelUps.begin(), gatherLevelUps.end());
	craftLevelUps.erase(craftLevelUps.begin(), craftLevelUps.end());
	
}

bool GatheringLog::gatheringListHasItem(string name){
	for (int i = 0; i < gatheringRecord.size(); i ++){
		if (gatheringRecord[i].name == name){
			//gatheringRecord[i].successes ++;
			return true;
		}
	}
	return false;
}

bool GatheringLog::craftingListHasItem(string name){
	for (int i = 0; i < craftingRecord.size(); i ++){
		if (craftingRecord[i].name == name){
			//gatheringRecord[i].successes ++;
			return true;
		}
	}
	return false;
}

void GatheringLog::gather(string line){
	stringstream ss(line);
	
	string dummy;
	do {
		getline(ss, dummy, ' ');		
	}
	while (dummy != "gathering" && ss.good());
	
	/*
	getline(ss, dummy, ' '); //date
	getline(ss, dummy, ' '); //time
	getline(ss, dummy, ' '); //:
	getline(ss, dummy, ' '); //You 
	getline(ss, dummy, ' '); //have
	getline(ss, dummy, ' '); //started
	getline(ss, dummy, ' '); //gathering
	*/
	getline(ss, dummy, '.');
	//numGatheringSuccesses ++;
	
	//currentlyCrafting = true;

	lastItemGathered = dummy;
	if (!gatheringListHasItem(dummy)){
		GatheringRecord temp;
		temp.name = dummy;
		temp.successes = 0;
		temp.failures = 0;
		temp.cancellations = 0;
		gatheringRecord.push_back(temp);
		
	}
}

void GatheringLog::gatherSuccess(){	
	numGatheringSuccesses ++;
	//currentlyCrafting = false;
	
	for (int i = 0; i < gatheringRecord.size(); i ++){		
		
		if (gatheringRecord[i].name == lastItemGathered){
			//cout << i << ": " << gatheringRecord[i].name << " vs. " << lastItemGathered << endl;
			gatheringRecord[i].successes ++;
		}
	}
}

void GatheringLog::gatherFailure(string line){
	numGatheringFailures ++;
	//currentlyCrafting = false;

	for (int i = 0; i < gatheringRecord.size(); i ++){
		if (gatheringRecord[i].name == lastItemGathered){
			gatheringRecord[i].failures ++;
		}
	}
}

void GatheringLog::gatherCancel(){
	numGatheringCancellations ++;
	//currentlyCrafting = false;

	for (int i = 0; i < gatheringRecord.size(); i ++){
		if (gatheringRecord[i].name == lastItemGathered){
			gatheringRecord[i].cancellations ++;
		}
	}
}

void GatheringLog::craft(string line){
	//numCraftingSuccesses ++;
	stringstream ss(line);
	
	string dummy;
	getline(ss, dummy, ' '); //date
	getline(ss, dummy, ' '); //time
	getline(ss, dummy, ' '); //:
	getline(ss, dummy, ' '); //You 
	getline(ss, dummy, ' '); //are	
	getline(ss, dummy, ' '); //crafting

	getline(ss, dummy, '.');
	//numGatheringSuccesses ++;
	
	if (currentlyCrafting){
		numCraftingProcs ++;
		procBaseItem = lastItemGathered;
	}
	currentlyCrafting = true;

	lastItemGathered = dummy;
	if (!craftingListHasItem(dummy)){
		GatheringRecord temp;
		temp.name = dummy;
		temp.successes = 0;
		temp.failures = 0;
		temp.cancellations = 0;
		craftingRecord.push_back(temp);
		
	}
}

void GatheringLog::craftSuccess(){
	numCraftingSuccesses ++;
	currentlyCrafting = false;

	//if (!isLevelCapped && numCraftedSinceLevelUp >= -1) numCraftedSinceLevelUp ++;
	
	for (int i = 0; i < craftingRecord.size(); i ++){		
	
		if (craftingRecord[i].name == lastItemGathered){
			//cout << i << ": " << craftingRecord[i].name << " vs. " << lastItemGathered << " s: " << craftingRecord[i].successes << endl;
			craftingRecord[i].successes ++;
		}
	}
}

void GatheringLog::craftFailure(string line){
	numCraftingFailures ++;
	currentlyCrafting = false;

	for (int i = 0; i < craftingRecord.size(); i ++){
		if (craftingRecord[i].name == lastItemGathered){
			craftingRecord[i].failures ++;
		}
	}
}

void GatheringLog::craftCancel(){
	if (!isInventoryFull){
		numCraftingCancellations ++;
		for (int i = 0; i < craftingRecord.size(); i ++){
			if (craftingRecord[i].name == lastItemGathered){
				craftingRecord[i].cancellations ++;
			}
		}
	}
	currentlyCrafting = false;
}

void GatheringLog::craftProcFailure(){
	numCraftingProcs --;
	currentlyCrafting = false;
	lastItemGathered = procBaseItem;
	craftSuccess();
}

void GatheringLog::inventoryFull(){
	isInventoryFull = true;
}

void GatheringLog::clearCraftingStatus(){
	currentlyCrafting = false;
}


float GatheringLog::getGatherSuccessRate(){
	int attempts = numGatheringSuccesses + numGatheringFailures + numGatheringCancellations;
	if (attempts > 0) return (float)numGatheringSuccesses * 100 / attempts;
	else return 0;
}
float GatheringLog::getGatherFailureRate(){
	int attempts = numGatheringSuccesses + numGatheringFailures + numGatheringCancellations;
	if (attempts > 0) return (float)numGatheringFailures * 100 / attempts;
	else return 0;
}
float GatheringLog::getGatherCancellationRate(){
	int attempts = numGatheringSuccesses + numGatheringFailures + numGatheringCancellations;
	if (attempts > 0) return (float)numGatheringCancellations * 100 / attempts;
	else return 0;
}

float GatheringLog::getCraftSuccessRate(){
	int attempts = numCraftingSuccesses + numCraftingFailures + numCraftingCancellations;
	if (attempts > 0) return (float)numCraftingSuccesses * 100 / attempts;
	else return 0;
}
float GatheringLog::getCraftFailureRate(){
	int attempts = numCraftingSuccesses + numCraftingFailures + numCraftingCancellations;
	if (attempts > 0) return (float)numCraftingFailures * 100 / attempts;
	else return 0;
}
float GatheringLog::getCraftCancellationRate(){
	int attempts = numCraftingSuccesses + numCraftingFailures + numCraftingCancellations;
	if (attempts > 0) return (float)numCraftingCancellations * 100 / attempts;
	else return 0;
}
float GatheringLog::getCraftProcRate(){
	if (numCraftingSuccesses > 0) return (float)numCraftingProcs * 100 / numCraftingSuccesses;
	else return 0;
}

void GatheringLog::gainGatherExp(){
	gatherSuccess();
	if (!isLevelCapped && numGatheredSinceLevelUp >= -1) numGatheredSinceLevelUp ++;
}

void GatheringLog::gainCraftExp(){
	//craftSuccess();
	if (!isLevelCapped && numCraftedSinceLevelUp >= -1) numCraftedSinceLevelUp ++;
}


void GatheringLog::gatherLevelUp(string line){
	stringstream ss(line);
	
	string dummy;
	getline(ss, dummy, ' '); //date
	getline(ss, dummy, ' '); //time
	getline(ss, dummy, ' '); //:
	getline(ss, dummy, ' '); //Your
	getline(ss, dummy, ' '); //(Gathering Discipline)

	bool isGather = false;
	if (dummy == "Essencetapping" || dummy == "Aethertapping" || dummy == "Collection"){
		isGather = true;	
	}
	//cout << dummy << endl;

	getline(ss, dummy, 'o'); //to
	getline(ss, dummy, ' '); //
	getline(ss, dummy, ' '); //level
	
	int level = atoi(dummy.c_str());

	GatherLevelUps levelup;
	levelup.level = level;
	
	if (isGather){
		gatheringLvl = level;
		levelup.numGathers = numGatheredSinceLevelUp + 1;
		gatherLevelUps.push_back(levelup);

		lastNumGatheredToLevelUp = numGatheredSinceLevelUp + 1;
		numGatheredSinceLevelUp = -1;
	}
	else {		
		craftingLvl = level;
		levelup.numGathers = numCraftedSinceLevelUp + 1;
		craftLevelUps.push_back(levelup);

		lastNumCraftedToLevelUp = numCraftedSinceLevelUp + 1;
		numCraftedSinceLevelUp = -1;
	}
	
}

void GatheringLog::craftLevelUp(string line){
	
}



void GatheringLog::calculateNextLevelRequirementEstimates(){
	int estimateNumGathersToNextLevel = -1;
	int estimateNumCraftsToNextLevel = -1;

	if (lastNumGatheredToLevelUp > 0){
		if (numGatheredSinceLevelUp < lastNumGatheredToLevelUp) estimateNumGathersToNextLevel = lastNumGatheredToLevelUp;
		else estimateNumGathersToNextLevel = numGatheredSinceLevelUp + 1;
	}
	if (estimateNumGathersToNextLevel > 0) 
		estimatedGatherExpBar = (float)numGatheredSinceLevelUp / estimateNumGathersToNextLevel;
	else estimatedGatherExpBar = 0;

	if (lastNumCraftedToLevelUp > 0){
		if (numCraftedSinceLevelUp < lastNumCraftedToLevelUp) estimateNumCraftsToNextLevel = lastNumCraftedToLevelUp;
		else estimateNumCraftsToNextLevel = numCraftedSinceLevelUp + 1;
	}
	if (estimateNumCraftsToNextLevel > 0)
		estimatedCraftExpBar = (float) numCraftedSinceLevelUp / estimateNumCraftsToNextLevel;
	else estimatedCraftExpBar = 0;
	
}

void GatheringLog::skillLevelTooLow(string line){

	stringstream ss(line);
	
	string dummy;
	getline(ss, dummy, ' '); //date
	getline(ss, dummy, ' '); //time
	getline(ss, dummy, ' '); //:
	getline(ss, dummy, ' '); //The
	getline(ss, dummy, 'h'); //Skill level for t	
	getline(ss, dummy, ' '); //e
	getline(ss, dummy, ' '); //(Gathering Discipline)

	//bool isGather = false;
	if (dummy == "Essencetapping" || dummy == "Aethertapping" || dummy == "Collection"){
		gatherSuccess();
	}
		
}

void GatheringLog::levelCapped(){
	isLevelCapped = true;
}

float GatheringLog::getNumGatheredPerHour(){
	return (numGatheringSuccesses)
		/ ((clock() - startTime) / (CLOCKS_PER_SEC * 3600));
	
}

float GatheringLog::getNumCraftedPerHour(){
	return (numCraftingSuccesses)
		/ ((clock() - startTime) / (CLOCKS_PER_SEC * 3600));
}

float GatheringLog::getNumGatherLvlsPerHour(){
	return ((float)gatherLevelUps.size() + estimatedGatherExpBar)
		/ ((clock() - startTime) / (CLOCKS_PER_SEC * 3600));
}

float GatheringLog::getNumCraftLvlsPerHour(){
	return ((float)craftLevelUps.size() + estimatedCraftExpBar)
		/ ((clock() - startTime) / (CLOCKS_PER_SEC * 3600));
}

void GatheringLog::tickCleanUp(){
	isLevelCapped = false;
	isInventoryFull = false;
	calculateNextLevelRequirementEstimates();
}