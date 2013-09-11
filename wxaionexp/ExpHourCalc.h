#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <ctime>

//#include "LogFile.h"


using namespace std;

#define STANDARD_SERVER 0
#define FAST_TRACK_SERVER 1
#define INSTANCE_SERVER 2

#define LEVEL_CAP 65

#define START_OF_LINE 22

class ExpHourCalc {
public:

	//bool isOK;
	//bool expChartOK;

	// Tick Information
	bool lastTickHasChanges;
	int numExpPacketsOnLastChange;
	int numApPacketsOnLastChange;

	// XP variables
	int level;
	int startExp;
	int currentExp;

	int reposeExp;
	int salvationExp;

	int expGained;
	int lastExpPacket;
	int expLostToDeaths;
	
	bool needExpUpdate;

	// AP variables
	int currentAp;
	int apGained;
	int apSpent;
	int apLostToPk;
	int lastApPacket;

	int relicAp;
	int lastRelicApPacket;

	bool needApUpdate;

	// Cash variables
	int cashGained;
	int cashSpent;
	int lastCashTransaction;
	
	int getNetCashFlow();

	// Constructor
	//ExpHourCalc(string filename);
	ExpHourCalc();
	
	// Core functions
	//void processLines();

	void start(int startLevel, int startExp, int startAp);
	void stop();
	void pause();
	void reset();

	string getElapsedTime();

	int currentServer;

	// XP functions

	float getExpPercent();
	float getLastExpPacketPercent();

	float getExpPerHour();

	int getExpChartEntry(int level);

	bool updateExp(int newValue);
	
	// AP functions
	
	string getCurrentServer();

	float getApPerHour();	
	float getLastApPacketPercent();

	float getRelicApPerHour();	

	string getAbyssRankName();	
	float getNextRankAp();
	float getApPercent();
	
	bool updateAp(int newValue);
	
	//

	void checkLevelUp();	

	

	void gainExp(string line);
	void gainAP(string line);
	void gainCash(string line);

	void spendCash(string line);
	void spendAP(string line);
		
	void acquireItem(string line);

	void tallyExpPackets();

	void joinChannel(string line, int channelWordPos);
	void joinServer(string line, int serverWordPos);

	void PvEDeath();
	void PvPDeath();

	void calculateDeathPenalty();
	void setCannotLevelTo10();

private:

	//vector<int> expChart;
	int expChart[65];
	int apChart[10];
	map<int, float*> relicApValues;
	
	//LogFile* logFile;
	
	float startTime;
	float stopTime;

	int tempExpGained;
	int tempApGained;
	int tempNumExpPackets;
	int tempNumApPackets;

	bool cannotLevelTo10;
	
	int getAbyssRank();
	
	bool lastDeathIsPk;

	//void loadExpChart(string filename);

	
	
};