#include "../../wxaionexp/LogFileParser.h"
#include "windows.h"

int main(int argc, char* argv[]){
	
	LogFileParser *parser = new LogFileParser("e:\\Aion\\Chat.log");
	if (!parser->isOK) cout << "UNABLE TO OPEN CHAT.LOG" << endl;

	ExpHourCalc *dummy = new ExpHourCalc();
	GatheringLog *gatheringLog = new GatheringLog();
	LocationPinger *locationPinger = new LocationPinger();

	parser->setExpHourCalc(dummy);
	parser->setGatheringLog(gatheringLog);
	parser->setLocationPinger(locationPinger);

	gatheringLog->reset();

	while(true){
		parser->processLines();
		system("cls");
		cout << "Pinged location at " << locationPinger->map << ": " << locationPinger->x << ", " << locationPinger->y << endl;
		cout << "Last location at " << locationPinger->lastMap << ": " << locationPinger->prevX << ", " << locationPinger->prevY << endl;
		cout << "Dist between pings: " << locationPinger->distKm << " km / " <<locationPinger->distMiles << " mi " << endl;
		cout << endl;
		cout << "Gathering: pass / fail / cancel: " 
			<< gatheringLog->numGatheringSuccesses << " / " 
			<< gatheringLog->numGatheringFailures << " / " 
			<< gatheringLog->numGatheringCancellations << " ("
			<< gatheringLog->getNumGatheredPerHour() << " / h)"
			<< endl;
		cout << "Crafting: pass / fail / cancel [procs]: " 
			<< gatheringLog->numCraftingSuccesses << " / " 
			<< gatheringLog->numCraftingFailures << " / " 
			<< gatheringLog->numCraftingCancellations << " ["
			<< gatheringLog->numCraftingProcs << "] ("
			<< gatheringLog->getNumCraftedPerHour() << " / h)"
			<< endl;
		cout << endl;

		for (int i = 0; i < gatheringLog->gatheringRecord.size(); i ++){
			cout << "[" << gatheringLog->gatheringRecord[i].successes << "S\t" 
				<< gatheringLog->gatheringRecord[i].failures << "F\t" 
				<< gatheringLog->gatheringRecord[i].cancellations << "C]\t"				
				<< gatheringLog->gatheringRecord[i].name
				<< endl;
		}

		for (int i = 0; i < gatheringLog->craftingRecord.size(); i ++){
			cout << "[" << gatheringLog->craftingRecord[i].successes << "S\t" 
				<< gatheringLog->craftingRecord[i].failures << "F\t" 
				<< gatheringLog->craftingRecord[i].cancellations << "C]\t"				
				<< gatheringLog->craftingRecord[i].name
				<< endl;
		}
		cout << endl;
		cout << "Gathering level ups (" << gatheringLog->getNumGatherLvlsPerHour() <<  " / h): " << gatheringLog->gatherLevelUps.size() << endl;		
		cout << "Gathering level: " << gatheringLog->gatheringLvl 
			<< " (" << gatheringLog->numGatheredSinceLevelUp << " / " << gatheringLog->estimateNumGathersToNextLevel << " estimated to next level)";
		if (gatheringLog->estimateNumGathersToNextLevel > 0) cout << " (" << (float)gatheringLog->numGatheredSinceLevelUp / gatheringLog->estimateNumGathersToNextLevel * 100 << "%)";
		cout << endl;

		for (int i = 0; i < gatheringLog->gatherLevelUps.size(); i ++){
			cout << "To " << gatheringLog->gatherLevelUps[i].level << ": " << gatheringLog->gatherLevelUps[i].numGathers << endl;
		}

		cout << "Crafting level ups (" << gatheringLog->getNumCraftLvlsPerHour() <<  " / h): " << gatheringLog->craftLevelUps.size() << endl;
		cout << "Crafting level: " << gatheringLog->craftingLvl 
			<< " (" << gatheringLog->numCraftedSinceLevelUp << " / " << gatheringLog->estimateNumCraftsToNextLevel <<  " estimated to next level)" << endl;
		if (gatheringLog->estimateNumCraftsToNextLevel > 0) cout << " (" << (float)gatheringLog->numCraftedSinceLevelUp / gatheringLog->estimateNumCraftsToNextLevel * 100 << "%)";
		cout << endl;

		for (int i = 0; i < gatheringLog->craftLevelUps.size(); i ++){
			cout << "To " << gatheringLog->craftLevelUps[i].level << ": " << gatheringLog->craftLevelUps[i].numGathers << endl;
		}

		Sleep(1000);
		
	}
}