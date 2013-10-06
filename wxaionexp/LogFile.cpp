#include "LogFile.h"
#include <iostream>

using namespace std;

/*********************************************************************************************
Constructor: Open Aion log file from filename, move file pointer to end of file
*********************************************************************************************/
LogFile::LogFile(string filename){
	file.open(filename);
	file.seekg(0, ios::end);
	
	if (file.fail()) isOK = false;
	else isOK = true;
}

/*********************************************************************************************
Destructor: Close file
*********************************************************************************************/
LogFile::~LogFile(){
	file.close();	
}

/*********************************************************************************************
Read new lines that have been appended to the log file by the game Client, put them into a queue
*********************************************************************************************/
queue<string> LogFile::readLines(){
	

	queue<string> lines;
	string line;


	while(file.good()){
		std::getline (file,line);
		//cout << line << endl;
		lines.push(line);
	}
	if (isOK) file.clear();
	//return lines.size();
	return lines;
}
