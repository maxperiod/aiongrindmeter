#include <string>

#include "ExpHourCalc.h"
#include "stringFunctions.h"

ExpHourCalc::ExpHourCalc(){

	expChart[ 0] = 400;
	expChart[ 1] = 1033;
	expChart[ 2] = 2387;
	expChart[ 3] = 5234;
	expChart[ 4] = 8601;
	expChart[ 5] = 13323;
	expChart[ 6] = 21032;
	expChart[ 7] = 30972;
	expChart[ 8] = 43087;
	expChart[ 9] = 56183;
	expChart[10] = 78370;
	expChart[11] = 100203;
	expChart[12] = 129506;
	expChart[13] = 158838;
	expChart[14] = 195209;
	expChart[15] = 238640;
	expChart[16] = 318338;
	expChart[17] = 407257;
	expChart[18] = 506158;
	expChart[19] = 627122;
	expChart[20] = 827364;
	expChart[21] = 1041897;
	expChart[22] = 1299044;
	expChart[23] = 1522142;
	expChart[24] = 1745386;
	expChart[25] = 2017917;
	expChart[26] = 2336082;
	expChart[27] = 2607688;
	expChart[28] = 3039136;	
	expChart[29] = 3784200;
	expChart[30] = 4423094;
	expChart[31] = 5255354;
	expChart[32] = 6286020;
	expChart[33] = 8223545;
	expChart[34] = 10478922;
	expChart[35] = 12824678;
	expChart[36] = 16916703;
	expChart[37] = 19447692;
	expChart[38] = 22796975;
	expChart[39] = 27395550;
	expChart[40] = 32060906;
	expChart[41] = 37661563;
	expChart[42] = 40313649;
	expChart[43] = 42806525;
	expChart[44] = 45761278;
	expChart[45] = 49008484;
	expChart[46] = 51861666;
	expChart[47] = 54998404;
	expChart[48] = 58478318;
	expChart[49] = 62106470;
	expChart[50] = 69317277;
	expChart[51] = 75246001;
	expChart[52] = 80259032;
	expChart[53] = 90030075;
	expChart[54] = 104225345;
	expChart[55] = 124225345;
	expChart[56] = 142978501;
	expChart[57] = 144107684;
	expChart[58] = 163937509;
	expChart[59] = 239209928;
	expChart[60] = 248865663;
	expChart[61] = 257678943;
	expChart[62] = 281111621;
	expChart[63] = 508568274;
	expChart[64] = 584561235;

	apChart[9] = 0;
	apChart[8] = 1200;
	apChart[7] = 4220;
	apChart[6] = 10990;
	apChart[5] = 23500;
	apChart[4] = 42780;
	apChart[3] = 69700;
	apChart[2] = 105600;
	apChart[1] = 150800;
	apChart[0] = 2100000000;

	/*
	Lesser Icon 186000066: 315 / 300
	Normal Icon 186000065: 630 / 600
	Greater Icon 186000064
	Major Icon 186000063

	Lesser Seal 186000062
	Normal Seal 186000061
	Greater Seal 186000060
	Major Seal 186000059

	Lesser Goblet 186000058
	Normal Goblet 186000057
	Greater Goblet 186000056
	Major Goblet 186000055

	Lesser Crown 186000054
	Normal Crown 186000053
	Greater Crown 186000052
	Major Crown 186000051

	Lesser Danuar 186000250
	Normal Danuar 186000249
	Greater Danuar 186000248
	Major Danuar 186000247

	Blood Mark 186000236
	*/
	
	//Icons
	relicApValues[186000066] = new float[2];
	relicApValues[186000066][0] = 315;
	relicApValues[186000066][1] = 300;

	relicApValues[186000065] = new float[2];
	relicApValues[186000065][0] = 630;
	relicApValues[186000065][1] = 600;

	relicApValues[186000064] = new float[2];
	relicApValues[186000064][0] = 945;
	relicApValues[186000064][1] = 900;

	relicApValues[186000063] = new float[2];
	relicApValues[186000063][0] = 1260;
	relicApValues[186000063][1] = 1200;
	
	//Seals
	relicApValues[186000062] = new float[2];
	relicApValues[186000062][0] = 630;
	relicApValues[186000062][1] = 600;

	relicApValues[186000061] = new float[2];
	relicApValues[186000061][0] = 1260;
	relicApValues[186000061][1] = 1200;

	relicApValues[186000060] = new float[2];
	relicApValues[186000060][0] = 1890;
	relicApValues[186000060][1] = 1800;

	relicApValues[186000059] = new float[2];
	relicApValues[186000059][0] = 2520;
	relicApValues[186000059][1] = 2400;

	//Goblets
	relicApValues[186000058] = new float[3];
	relicApValues[186000058][0] = 1200;
	relicApValues[186000058][1] = 840;
	relicApValues[186000058][2] = 800;

	relicApValues[186000057] = new float[3];
	relicApValues[186000057][0] = 2400;
	relicApValues[186000057][1] = 1680;
	relicApValues[186000057][2] = 1600;

	relicApValues[186000056] = new float[3];
	relicApValues[186000056][0] = 3600;
	relicApValues[186000056][1] = 2520;
	relicApValues[186000056][2] = 2400;

	relicApValues[186000055] = new float[3];
	relicApValues[186000055][0] = 4800;
	relicApValues[186000055][1] = 3360;
	relicApValues[186000055][2] = 3200;

	//Crowns
	relicApValues[186000054] = new float[3];
	relicApValues[186000054][0] = 2400;
	relicApValues[186000054][1] = 1680;
	relicApValues[186000054][2] = 1600;

	relicApValues[186000053] = new float[3];
	relicApValues[186000053][0] = 4800;
	relicApValues[186000053][1] = 3360;
	relicApValues[186000053][2] = 3200;

	relicApValues[186000052] = new float[3];
	relicApValues[186000052][0] = 7200;
	relicApValues[186000052][1] = 5040;
	relicApValues[186000052][2] = 4800;

	relicApValues[186000051] = new float[3];
	relicApValues[186000051][0] = 9600;
	relicApValues[186000051][1] = 6720;
	relicApValues[186000051][2] = 6400;

	//Danuar Relic

	relicApValues[186000250] = new float[3];
	relicApValues[186000250][0] = 2550;
	relicApValues[186000250][1] = 1785;
	relicApValues[186000250][2] = 1700;

	relicApValues[186000249] = new float[3];
	relicApValues[186000249][0] = 5100;
	relicApValues[186000249][1] = 3570;
	relicApValues[186000249][2] = 3400;

	relicApValues[186000248] = new float[3];
	relicApValues[186000248][0] = 7650;
	relicApValues[186000248][1] = 5355;
	relicApValues[186000248][2] = 5100;

	relicApValues[186000247] = new float[3];
	relicApValues[186000247][0] = 10200;
	relicApValues[186000247][1] = 7140;
	relicApValues[186000247][2] = 6800;


	//Blood Marks
	relicApValues[186000236] = new float[3];
	relicApValues[186000236][0] = 508.2;
	relicApValues[186000236][1] = 363;
	relicApValues[186000236][2] = 302.5;
		
	level = 0;
	currentExp = 0;	
	currentAp = 0;
	reset();
	
}


void ExpHourCalc::start(int startLevel, int startExp, int startAp){
	reset();
	startTime = clock();
	level = startLevel;
	currentExp = startExp;
	currentAp = startAp;
}
void ExpHourCalc::stop(){
	stopTime = clock();
}

void ExpHourCalc::reset(){
	// Don't reset the level, currentExp, and currentAp fields or the manual initial inputs will be gone

	lastTickHasChanges = false;

	// XP variables
	
	startExp = 0;	

	reposeExp = 0;
	salvationExp = 0;

	expGained = 0;
	lastExpPacket = 0;
	expLostToDeaths = 0;

	needExpUpdate = false;

	// AP variables
	
	apGained = 0;
	apSpent = 0;
	apLostToPk = 0;
	lastApPacket = 0;

	relicAp = 0;
	lastRelicApPacket = 0;

	needApUpdate = false;

	// Cash variables
	cashGained = 0;
	cashSpent = 0;
	lastCashTransaction = 0;

	// Private variables
	tempExpGained = 0;
	tempApGained = 0;
	tempNumExpPackets = 0;
	tempNumApPackets = 0;

	currentServer = STANDARD_SERVER;

	cannotLevelTo10 = false;
		
	lastDeathIsPk = false;

}

float ExpHourCalc::getExpPerHour(){
	float hours = (clock() - startTime) / (CLOCKS_PER_SEC * 3600);

	return expGained / hours;
}

float ExpHourCalc::getApPerHour(){
	float hours = (clock() - startTime) / (CLOCKS_PER_SEC * 3600);

	return apGained / hours;
}

float ExpHourCalc::getRelicApPerHour(){
	float hours = (clock() - startTime) / (CLOCKS_PER_SEC * 3600);

	return relicAp / hours;
}

float ExpHourCalc::getExpPercent(){
	if (level > 0 && level <= LEVEL_CAP){
		return floor((float)currentExp / getExpChartEntry(level) * 10000) / 100;
	}
	else return 0;
}

float ExpHourCalc::getLastExpPacketPercent(){
	if (level > 0 && level <= LEVEL_CAP) return (float)lastExpPacket / getExpChartEntry(level) * 100;
	else return 0;
}

float ExpHourCalc::getLastApPacketPercent(){
	int ApRank = getAbyssRank();	
	if (getNextRankAp() > 0)
		return floor((float)lastApPacket / (apChart[ApRank-1] - apChart[ApRank]) * 10000) / 100;
	else return 0;
}

float ExpHourCalc::getApPercent(){
	int ApRank = getAbyssRank();
	if (ApRank > 9) return 0;
	if (ApRank > 1)
		return floor((float)(currentAp - apChart[ApRank]) / (apChart[ApRank-1] - apChart[ApRank]) * 10000) / 100;
	return 100;
}


int ExpHourCalc::getExpChartEntry(int level){		
	if (level <= LEVEL_CAP && level > 0) return expChart[level - 1];	
	return -1;
}

float ExpHourCalc::getNextRankAp(){
	int ApRank = getAbyssRank();
	if (ApRank <= 1) return 0;
	else if (ApRank <= 9)
		return apChart[ApRank-1];
	else return -1;
}

int ExpHourCalc::getAbyssRank(){

	int i;
	if (currentAp == -1) return 10;
	for (i = 0; currentAp < apChart[i]; i ++){
		
	}
	return i;
}

string ExpHourCalc::getAbyssRankName(){
	return formatAbyssRankName(getAbyssRank());
}

string ExpHourCalc::getElapsedTime(){
	return formatElapsedTime((clock() - startTime) / CLOCKS_PER_SEC);
}



int ExpHourCalc::getNetCashFlow(){
	return cashGained - cashSpent;
}


void ExpHourCalc::checkLevelUp(){
	if (level >= 1){	
		//Ascension quest reward already accepted, character is not at level cap
		if (!cannotLevelTo10 && level < LEVEL_CAP){
			while (currentExp > getExpChartEntry(level)){
				//expGained -= currentExp - getExpChartEntry(level);
				currentExp -= getExpChartEntry(level);
				level ++;
			}
		}
		//Cannot level up, handle overfill exp
		if (currentExp > getExpChartEntry(level)){
			expGained -= currentExp - getExpChartEntry(level);
			currentExp = getExpChartEntry(level);
		}
	}
	
	
}

void ExpHourCalc::gainExp(string line){
	stringstream ss(line);

	bool hasRepose = false;
	bool hasSalvation = false;
	
	if (line.find("Energy of Repose ", 22) != string::npos) hasRepose = true;
	if (line.find("Energy of Salvation ", 22) != string::npos) hasSalvation = true;

	string dummy;
	getline(ss, dummy, ' '); //date
	getline(ss, dummy, ' '); //time
	getline(ss, dummy, ' '); //:
	getline(ss, dummy, ' '); //You 
	getline(ss, dummy, ' '); //Have
	getline(ss, dummy, ' '); //gained

	getline(ss, dummy, ' ');
	
	int expValue = atoi(stripCommas(dummy).c_str());
		
	tempExpGained += expValue;
	tempNumExpPackets ++;

	if (hasRepose || hasSalvation){
		getline(ss, dummy, '('); // skip to first bracket
		getline(ss, dummy, ' '); // Energy
		if (dummy == "Strong" || dummy == "Powerful") getline(ss, dummy, ' '); //Strong Energy of Repose
		 //Strong Energy of Repose
		getline(ss, dummy, ' '); // Of
		getline(ss, dummy, ' '); // Repose/Salvation
		
		if (dummy == "Repose"){
			getline(ss, dummy, ' ');		
			//cout << dummy << endl;
			reposeExp += atoi(stripCommas(dummy).c_str());
		}
		else if (dummy == "Salvation"){
			getline(ss, dummy, ' ');			
			//cout << dummy << endl;
			salvationExp += atoi(stripCommas(dummy).c_str());
		}				
	}

	if (hasRepose && hasSalvation){
		getline(ss, dummy, ' '); // Energy
		getline(ss, dummy, ' '); // Of
		getline(ss, dummy, ' '); // Salvation

		getline(ss, dummy, ' ');
		salvationExp += atoi(stripCommas(dummy).c_str());
	}

}

void ExpHourCalc::gainAP(string line){
	stringstream ss(line);

	string dummy;

	getline(ss, dummy, ' '); //date
	getline(ss, dummy, ' '); //time
	getline(ss, dummy, ' '); //:
	getline(ss, dummy, ' '); //You 
	getline(ss, dummy, ' '); //Have
	getline(ss, dummy, ' '); //gained

	getline(ss, dummy, ' ');
	
	int apValue = atoi(stripCommas(dummy).c_str());

	tempApGained += apValue;
	tempNumApPackets ++;
}

void ExpHourCalc::gainCash(string line){
	stringstream ss(line);

	
	string dummy;
	getline(ss, dummy, ' '); //date
	getline(ss, dummy, ' '); //time
	getline(ss, dummy, ' '); //:
	getline(ss, dummy, ' '); //You
	getline(ss, dummy, ' '); //have
	getline(ss, dummy, ' '); //earned

	getline(ss, dummy, ' '); 
	int cashGain = atoi(stripCommas(dummy).c_str());
	cashGained += cashGain;
	lastCashTransaction = cashGain;
	
}

void ExpHourCalc::spendCash(string line){
	stringstream ss(line);
	
	string dummy;
	getline(ss, dummy, ' '); //date
	getline(ss, dummy, ' '); //time
	getline(ss, dummy, ' '); //:
	getline(ss, dummy, ' '); //You
	getline(ss, dummy, ' '); //spent	

	getline(ss, dummy, ' '); 

	int cashSpend = atoi(stripCommas(dummy).c_str());
	cashSpent += cashSpend;
	lastCashTransaction = -cashSpend;
}

void ExpHourCalc::spendAP(string line){
	stringstream ss(line);
	
	string dummy;
	getline(ss, dummy, ' '); //date
	getline(ss, dummy, ' '); //time
	getline(ss, dummy, ' '); //:
	getline(ss, dummy, ' '); //You
	getline(ss, dummy, ' '); //used	

	getline(ss, dummy, ' '); 
	int apSpend = atoi(stripCommas(dummy).c_str());
	
	apSpent += apSpend;

	tempApGained -= apSpend;
	tempNumApPackets ++;

}

bool ExpHourCalc::updateExp(int newValue){
	if (newValue < 0) return false;
	int expLost = currentExp - newValue;	
	if (newValue <= currentExp + expLostToDeaths){

		tempExpGained -= expLost;
		expLostToDeaths += expLost;
		tempNumExpPackets ++;		
		
		if (expLost == 0 && currentServer == STANDARD_SERVER){
			needApUpdate = true;
		}
		needExpUpdate = false;
		return true;
	}
	return false;
}

bool ExpHourCalc::updateAp(int newValue){
	if (newValue < 0) return false;
	int apLost = currentAp - newValue;
	if (newValue <= currentAp + apLostToPk){
		apLostToPk += apLost;
		
		tempApGained -= apLost;
		tempNumApPackets ++;

		needApUpdate = false;
		lastDeathIsPk = true;
		return true;
	}
	return false;
}

void ExpHourCalc::calculateDeathPenalty(){
	
	//If Soul healing amount is not 1 zeny AND flagged PvE with "You have died.",
	//EXP has been lost
	if (lastCashTransaction != -1 && needExpUpdate == true){		
		int expLost = floor((float)tempExpGained * 1.5); 
		
		tempExpGained -= expLost;
		expLostToDeaths += expLost;
		tempNumExpPackets ++;
	}
	//Soul healed for 1 zeny, and finishing blow was from PvE, ask for AP update
	else if (lastCashTransaction == -1 && lastDeathIsPk == false && currentAp != -1){
		needApUpdate = true;
	}
	needExpUpdate = false;
}

void ExpHourCalc::PvEDeath(){
	needExpUpdate = true;
	lastDeathIsPk = false;
}

void ExpHourCalc::PvPDeath(){
	if (currentServer == STANDARD_SERVER && currentAp != -1){							
		needApUpdate = true;
		lastDeathIsPk = true;
	}
}

void ExpHourCalc::acquireItem(string line){
	stringstream ss(line);
	
	string dummy;
	getline(ss, dummy, ' '); //date
	getline(ss, dummy, ' '); //time
	getline(ss, dummy, ' '); //:
	getline(ss, dummy, ' '); //You
	getline(ss, dummy, ' '); //have
	getline(ss, dummy, ' '); //acquired 
	
	getline(ss, dummy, '['); 
	int quantity = atoi(stripCommas(dummy).c_str());
	if (quantity < 1) quantity = 1;
	getline(ss, dummy, ':'); //item tag

	getline(ss, dummy, ';'); 
	int itemId = atoi(stripCommas(dummy).c_str());

	try{
		int itemApValue = relicApValues.at(itemId)[0] * quantity;				
		relicAp += itemApValue;
		lastRelicApPacket = itemApValue;
	}
	catch(const exception& e){
		
	}
	
	
}

void ExpHourCalc::tallyExpPackets(){
	
	if (tempNumExpPackets > 0 || tempNumApPackets > 0){
		if (level > 0 && currentExp != -1) currentExp += tempExpGained;
		expGained += tempExpGained;	
		lastExpPacket = tempExpGained;

		if (currentAp != -1) currentAp += tempApGained;
		apGained += tempApGained;	
		lastApPacket = tempApGained;

		checkLevelUp();
		cannotLevelTo10 = false;

		numExpPacketsOnLastChange = tempNumExpPackets;
		numApPacketsOnLastChange = tempNumApPackets;
		lastTickHasChanges = true;		

		tempExpGained = 0;
		tempApGained = 0;
		tempNumExpPackets = 0;
		tempNumApPackets = 0;

		
	}
	else {
		lastTickHasChanges = false;
	}

}

void ExpHourCalc::joinChannel(string line, int channelWordPos){
	string channel = line.substr(START_OF_LINE + 20, channelWordPos - START_OF_LINE - 20);
}

void ExpHourCalc::joinServer(string line, int serverWordPos){
	string server = line.substr(START_OF_LINE + 16, serverWordPos - START_OF_LINE - 16);
	
	if (server == "Standard")
		currentServer = STANDARD_SERVER;
	else if (server == "Fast-Track")
		currentServer = FAST_TRACK_SERVER;
	else if (server == "Instance")
		currentServer = INSTANCE_SERVER;
	
}

string ExpHourCalc::getCurrentServer(){
	switch(currentServer){
	case STANDARD_SERVER:
		return "Standard";
		break;
	case FAST_TRACK_SERVER:
		return "Fast-Track";
		break;
	case INSTANCE_SERVER:
		return "Instance";
		break;
	default:
		return "Unknown";
	}
}

void ExpHourCalc::setCannotLevelTo10(){
	cannotLevelTo10 = true;
}
