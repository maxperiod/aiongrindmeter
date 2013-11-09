#include "LogFileParser.h"

LogFileParser::LogFileParser(string filename){
	logFile = new LogFile(filename);
	if (logFile->isOK) isOK = true;
	else isOK = false;
}

LogFileParser::~LogFileParser(){
	delete(logFile);
}

bool LogFileParser::setExpHourCalc(ExpHourCalc *calc){
	
	expHourCalc = calc;
	if (isOK) return true;
	return false;
}

bool LogFileParser::setGatheringLog(GatheringLog *gather){
	gatheringLog = gather;
	if (isOK) return true;
	else return false;
}

bool LogFileParser::setLocationPinger(LocationPinger *loc){
	locationPinger = loc;
	if (isOK) return true;
	else return false;
}

void LogFileParser::processLines(){
	queue<string> lines = logFile->readLines();

	while(!lines.empty()){
		string line = lines.front();
		
		// ExpHourCalc messages
		if (line.find("You have joined ", START_OF_LINE) == START_OF_LINE){
			int channelWordPos = line.find("Channel.", START_OF_LINE + 20);
			if (channelWordPos != string::npos){
				expHourCalc->joinChannel(line, channelWordPos - 1);
			}
			else {
				int serverWordPos = line.find("Server.", START_OF_LINE + 16);
				if (serverWordPos != string::npos){
					expHourCalc->joinServer(line, serverWordPos - 1);
				}
			}
		}
		else if (line.find("You have gained ", START_OF_LINE) == START_OF_LINE){
			if (line.find("XP", 38) != string::npos){					
				expHourCalc->gainExp(line);										
			}
			else if (line.find("Abyss ", 38) != string::npos){
				expHourCalc->gainAP(line);
			}
			else if (line.find("experience from gathering.", 38)!= string::npos){
				gatheringLog->gainGatherExp();
			}

		}
		else if (line.find("Kinah", 19) != string::npos){
			if (line.find("You have earned ", START_OF_LINE) == START_OF_LINE){
				expHourCalc->gainCash(line);
			}
			else if (line.find("You spent ", START_OF_LINE) == START_OF_LINE){
				expHourCalc->spendCash(line);
			}
		}
		else if (line.find("Sales complete.", START_OF_LINE) == START_OF_LINE){	
			expHourCalc->sellToNpc();
		}
		else if (line.find("You sold the item.", START_OF_LINE) == START_OF_LINE){	
			expHourCalc->sellToNpc();
		}
		else if (line.find("You have acquired ", START_OF_LINE) == START_OF_LINE){											
			expHourCalc->acquireItem(line);			
		}
		else if (line.find("You received Soul Healing.", START_OF_LINE) == START_OF_LINE){									
			expHourCalc->calculateDeathPenalty();			
			
		}
		else if (line.find("You do not have any XP to recover.", START_OF_LINE) == START_OF_LINE){									
			expHourCalc->needExpUpdate = false;			
			
		}
		else if (line.find("You used ", START_OF_LINE) == START_OF_LINE){						
			if (line.find(" Abyss Points", 31) != string::npos){
				expHourCalc->spendAP(line);
			}
		}
		else if (line.find("You were killed by ", START_OF_LINE) == START_OF_LINE){						
			if (line.find("'s attack.", 41) != string::npos){						
				expHourCalc->PvPDeath();

			}
		}
		else if (line.find("You have died.", START_OF_LINE) == START_OF_LINE){	
			expHourCalc->PvEDeath();
			
			
		}
		else if (expHourCalc->level == 9){
			if (line.find("You can advance to level 10 only after you have completed the class change quest.", START_OF_LINE) == START_OF_LINE){
				expHourCalc->setCannotLevelTo10();
				
			}
		}
		else if (expHourCalc->level == 55){
			if (line.find("You cannot be Level 56 on the ", START_OF_LINE) == START_OF_LINE){
				expHourCalc->setCannotLevelTo10();
			}
		}
		
		// GatheringLog Messages
		else if (line.find("You have started gathering ", START_OF_LINE) == START_OF_LINE){	
			gatheringLog->gather(line);
		}
		else if (line.find("You are gathering ", START_OF_LINE) == START_OF_LINE){	
			gatheringLog->gather(line);
		}
		else if (line.find("You have gathered successfully.", START_OF_LINE) == START_OF_LINE){	
			gatheringLog->gainGatherExp();
		}
		else if (line.find("You have failed to gather ", START_OF_LINE) == START_OF_LINE){	
			gatheringLog->gatherFailure(line);
		}
		else if (line.find("You have stopped gathering.", START_OF_LINE) == START_OF_LINE){	
			gatheringLog->gatherCancel();
		}
		else if (line.find("You are crafting ", START_OF_LINE) == START_OF_LINE){	
			gatheringLog->craft(line);
		}
		else if (line.find("You have crafted ", START_OF_LINE) == START_OF_LINE){	
			if (line.find("successfully.", START_OF_LINE + 17) != string::npos){
				gatheringLog->gainCraftExp();
			}
			else{
				gatheringLog->craftSuccess();
			}
		}
		else if (line.find("You have failed to craft ", START_OF_LINE) == START_OF_LINE){	
			gatheringLog->craftFailure(line);
		}
		else if (line.find("You failed to craft the combo, and crafted", START_OF_LINE) == START_OF_LINE){
			gatheringLog->craftProcFailure();
		}
		else if (line.find("You must have at least one free space in your cube to craft.", START_OF_LINE) == START_OF_LINE){	
			gatheringLog->inventoryFull();
		}
		else if (line.find("You stopped crafting.", START_OF_LINE) == START_OF_LINE){	
			gatheringLog->craftCancel();
		}		
		else if (line.find("Your ", START_OF_LINE) == START_OF_LINE){	
			if (line.find("has been upgraded to ", 27) != string::npos){
				gatheringLog->gatherLevelUp(line);
			}
		}
		else if (line.find("The skill level for the", START_OF_LINE) == START_OF_LINE){	
			if (line.find("does not increase as the difficulty is too low.", START_OF_LINE + 24) != string::npos){
				gatheringLog->skillLevelTooLow(line);
			}			
		}
		/*
		else if ((line.find("Your skill level does not increase with low level crafting as you are an Expert.", START_OF_LINE) == START_OF_LINE) ||
			(line.find("Such basic crafting doesn't affect your skill level, Master.", START_OF_LINE) == START_OF_LINE)){
				gatheringLog->skillLevelTooLow();
		}
		*/

		else if (line.find("You must level up to raise your skill level.", START_OF_LINE) == START_OF_LINE){	
			gatheringLog->levelCapped();
		}
		else if (line.find("[pos:") != string::npos){	
			locationPinger->pingLocation(line);
		}
		

		lines.pop();
	}

	expHourCalc->tallyExpPackets();
	gatheringLog->tickCleanUp();
}