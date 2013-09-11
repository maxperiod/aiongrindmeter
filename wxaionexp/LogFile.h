#include <string>
#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

class LogFile{

public:
	LogFile(string filename);
	~LogFile();
	queue<string> readLines();
	bool isOK;
	

private:
	ifstream file;
	//stack<string> lines;
	
};