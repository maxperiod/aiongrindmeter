
#include "testHelpers.h"

void makeFileCopy(string original, string copy){
	ifstream originalFile;
	ofstream tempFile;
	originalFile.open(original);
	tempFile.open(copy, ios::trunc);
	while(originalFile.good()){
		string copyLine;
		std::getline (originalFile,copyLine);
		tempFile << copyLine << endl;
	}
	originalFile.close();
	tempFile.close();
}

void appendFile(string file, string line){
	ofstream fileToAppend;
	fileToAppend.open(file, ios::app);
	fileToAppend << line << endl;
	fileToAppend.close();
}
