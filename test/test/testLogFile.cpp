//#include "../../wxaionexp/LogFile.h"
#include "../../wxaionexp/ExpHourCalc.h"
#include "testHelpers.h"


#include <iostream>



int numTestCases = 0;
int numFailed = 0;


int main(){
	makeFileCopy("tests.log", "temp.txt");

	stack<string> lines;
		
	//ExpHourCalc *expHourcalc = new ExpHourCalc("temp.txt");
	
	LogFile* nonExistantFile = new LogFile("sldfkjsdlfkjsefjl");
	doTest("nonExistantFile isOK", nonExistantFile->isOK, false);
	doTest("nonExistantFile pop", nonExistantFile->readLines().size(), 0);

	LogFile* logFile = new LogFile("temp.txt");
	doTest("logFile isOK", logFile->isOK, true);
	doTest("logFile pop", logFile->readLines().size(), 1);

	appendFile("temp.txt", "hello");
	appendFile("temp.txt", "I");
	appendFile("temp.txt", "hate you!");

	doTest("logFile pop", logFile->readLines().size(), 4);
	/*
	lines = logFile->readLines();
	
	doTest("readlines", lines.size(), 4);
	
	while(!lines.empty()){
		string line = lines.top();
		cout << line << endl;
		lines.pop();
	}
	*/

	//logFile->processLines();

	appendFile("temp.txt", "2013.06.27 23:35:36 : Critical Hit!You inflicted 944 damage on Wori by using Righteous Punishment I. ");
	appendFile("temp.txt", "2013.06.27 23:35:36 : You have gained 1,008 Abyss Points. ");
	appendFile("temp.txt", "2013.06.27 23:35:36 : You have gained 8,867 XP from Wori. ");
	appendFile("temp.txt", "2013.06.27 23:35:36 : You have defeated Wori. ");
	appendFile("temp.txt", "2013.06.27 23:35:36 : Invalid target. ");

	/*
	lines = logFile->readLines();

	doTest("readlines", lines.size(), 6);

	while(!lines.empty()){
		string line = lines.top();
		cout << line << endl;
		lines.pop();
	}
	*/

	//soul healing
	//lvl 62
	//744,497 XP

	cout << "numTestCases == " << numTestCases << endl;
	cout << "numFailed == " << numFailed  << endl;
	
	getchar();

	return 0;
}