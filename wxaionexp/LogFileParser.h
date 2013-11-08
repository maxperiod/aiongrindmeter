#include "ExpHourCalc.h"
#include "GatheringLog.h"
#include "Location.h"
#include "logfile.h"

class LogFileParser{
public:		
	bool isOK;

	LogFileParser(string logFile);
	~LogFileParser();
	bool setExpHourCalc(ExpHourCalc *calc);
	bool setGatheringLog(GatheringLog *gather);
	bool setLocationPinger(LocationPinger *loc);
	
	void processLines();

private:
	ExpHourCalc *expHourCalc;
	GatheringLog *gatheringLog;
	LocationPinger *locationPinger;
	LogFile *logFile;
};