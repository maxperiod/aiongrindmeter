#include "LogFile.h"
#include <iostream>

using namespace std;

LogFile::LogFile(string filename){
	file.open(filename);
	file.seekg(0, ios::end);
	
	if (file.fail()) isOK = false;
	else isOK = true;
}

LogFile::~LogFile(){
	file.close();	
}

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
