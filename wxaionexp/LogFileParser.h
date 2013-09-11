#include "ExpHourCalc.h"
#include "logfile.h"

class LogFileParser{
public:		
	bool isOK;

	LogFileParser(string logFile);
	bool setExpHourCalc(ExpHourCalc *calc);
	void processLines();

private:
	ExpHourCalc *expHourCalc;
	LogFile *logFile;
};