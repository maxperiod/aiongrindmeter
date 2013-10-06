#include "LogFileParser.h"

/*********************************************************************************************
Attach logfile class to this class
*********************************************************************************************/
LogFileParser::LogFileParser(string filename){
	logFile = new LogFile(filename);
	if (logFile->isOK) isOK = true;
	else isOK = false;
}

/*********************************************************************************************
Attach exp/hour class to this class
*********************************************************************************************/
bool LogFileParser::setExpHourCalc(ExpHourCalc *calc){
	
	expHourCalc = calc;
	if (isOK) return true;
	return false;
}

/*********************************************************************************************
Read and parse new lines added to the Aion log file
*********************************************************************************************/
void LogFileParser::processLines(){
	queue<string> lines = logFile->readLines();

	while(!lines.empty()){
		string line = lines.front();
		
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

		}
		else if (line.find("Kinah", 19) != string::npos){
			if (line.find("You have earned ", START_OF_LINE) == START_OF_LINE){
				expHourCalc->gainCash(line);
			}
			else if (line.find("You spent ", START_OF_LINE) == START_OF_LINE){
				expHourCalc->spendCash(line);
			}
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
		

		lines.pop();
	}

	expHourCalc->tallyExpPackets();
}