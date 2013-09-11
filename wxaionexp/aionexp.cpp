#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <locale>
#include <iomanip>
#include <vector>

#include <cmath>
#include <stdlib.h>

#include "windows.h"

#define CURRENT_EXP startExp + expGained - levelUpRolldown

using namespace std;

string formatKiloMega(float number){
	ostringstream oss;


	//string resultString;

	if (number > 1000000000){
		oss << setprecision(3) << number / 1000000000 << "B / h";
	}
	else if (number > 1000000){
		oss << setprecision(3) << number / 1000000 << "M / h";
	}
	else {
		oss << setprecision(3) << number / 1000 << "k / h";
	}
	return oss.str();
}

string stripCommas(string line){
	
	//stringstream ss(line);
	string newString;

	for (int i = 0; i < line.length(); i ++){
		if (line.at(i) != ','){
			newString.push_back(line.at(i));
		}
	}
	return newString;
}

double calculateExpPercent(int currentExp, int nextLevel){
	
	return floor((double)currentExp / nextLevel * 10000) / 100;

	
}

int decipherXPLine(string line){
	stringstream ss(line);

	
	
	string dummy;
	getline(ss, dummy, ' '); //date
	getline(ss, dummy, ' '); //time
	getline(ss, dummy, ' '); //:
	getline(ss, dummy, ' '); //You 
	getline(ss, dummy, ' '); //Have
	getline(ss, dummy, ' '); //gained

	getline(ss, dummy, ' ');
	//cout << "tobeDeciphered: " << dummy << endl;
	int experience = atoi(stripCommas(dummy).c_str());
	//cout << "exp gained: " << experience << endl;
	return experience;
}


int decipherCashGain(string line){
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
	return cashGain;
}

int decipherCashSpend(string line){
	stringstream ss(line);

	
	string dummy;
	getline(ss, dummy, ' '); //date
	getline(ss, dummy, ' '); //time
	getline(ss, dummy, ' '); //:
	getline(ss, dummy, ' '); //You
	getline(ss, dummy, ' '); //spent	

	getline(ss, dummy, ' '); 
	int cashSpend = atoi(stripCommas(dummy).c_str());
	return cashSpend;
}


void loadExpChart(vector<int>* expChart){
	string line;
	ifstream file;
	file.open("expchart.dat");
	while(file.good()){
		getline (file,line);
		//cout << atoi(stripCommas(line).c_str()) << endl;
		int expLine = atoi(stripCommas(line).c_str());
		
		expChart->push_back(expLine);
		cout << "expChart size is " << expChart->size() << " / " << expLine << endl;
	}
	file.close();
}

int main(int argc, char* argv[]){

	float elapsedSeconds;

	

	int level = 0;
	int startExp = 0;
	int currentExp = 0;
	int levelUpRolldown = 0;

	int expGained = 0;
	int lastExpPacket = 0;
	float expPerHour = 0;

	int apGained = 0;

	int cashGained = 0;
	int cashSpent = 0;

	int lastCashTransaction = 0;
	

	vector<int> expChart;
	loadExpChart(&expChart);

	string line;
	ifstream file;
	file.open(argv[1]);

	cout << "Seeeking to end of file" << endl;
	file.seekg(0, ios::end);

	system("cls");
	//cout << "I think this is end of file: " << file.tellg() << endl;
	
	cout << "What's your character level?" << endl;
	cin >> level;
	cout << "You are level " << level << endl;
	
	if (level > 0){
		cout << "What's your current EXP?" << endl;
		cin >> startExp;
		
	}

	float startTime = clock();
	

	while (true){
		
		elapsedSeconds = (clock() - startTime) / CLOCKS_PER_SEC;

		//cout << "file.tellg() == " << file.tellg() << endl;
		while(file.good()){
			getline (file,line);
			//cout << line << endl;
			//cout << "file.gcount == " << file.gcount() << endl;
			//if (file.gcount() > 0){
				
			if (line.find("You have gained ", 22) != string::npos){
				if (line.find("XP", 18) != string::npos){
					
					lastExpPacket = decipherXPLine(line);
					//cout << "I gained XP" << endl;
					
					expGained += lastExpPacket;														

				}
				else if (line.find("Abyss ", 22) != string::npos){
					cout << "I gained AP" << endl;
				}

			}
			else if (line.find("Kinah", 22) != string::npos){
				if (line.find("You have earned ", 18) != string::npos){
					cashGained += decipherCashGain(line);
					lastCashTransaction = cashGained;
				}
				else if (line.find("You spent", 18) != string::npos){
					cashSpent += decipherCashSpend(line);
					lastCashTransaction = -cashSpent;
				}
			}
			else if (line.find("You received Soul Healing.", 22) != string::npos){
				if (lastCashTransaction != -1){
					int expLost = floor((float)lastExpPacket * 1.5); 
					expGained -= expLost;
					lastExpPacket -= expLost;
				}
			}
			/*
			else if (line.find("You have acquired ", 22) != string::npos){
				cout << "I acquired some itamz" << endl;
			}
			*/
		
			//}
		}
		file.clear();
		Sleep(1000);
		
		system("cls");
		cout << (int)elapsedSeconds / 60 << " : " <<  (int) elapsedSeconds % 60 << endl;

		if (lastExpPacket > 0){
			cout << "+" << lastExpPacket << " XP";
			if (level > 0){
				cout << " (+" << calculateExpPercent(lastExpPacket, expChart[level-1]) << "%)" << endl;
			}
			cout << endl;
		}
		else cout << endl;

		if (level > 0){
						
			if (CURRENT_EXP > expChart[level - 1]){
				if (level < expChart.size()){
					levelUpRolldown += expChart[level - 1];
					level ++;
				}
				
			}
			
			cout << "EXP: " << CURRENT_EXP << " / " << expChart[level - 1];
			
			cout << "(" << calculateExpPercent(CURRENT_EXP, expChart[level-1]) << "%)";
			cout << endl;
			
		}
		cout << "Exp gained: " << expGained << " XP";
		
		cout << endl;

		
		expPerHour = expGained / (elapsedSeconds / 3600);
		cout << "Exp/hr: " << formatKiloMega(expPerHour) << endl; 
	
		cout << endl;
		cout << "Cash flow in: " << cashGained;
		if (lastCashTransaction > 0) cout << " (+" << lastCashTransaction << ")";
		cout << endl;
		cout << "Cash flow out: " << cashSpent;
		if (lastCashTransaction < 0) cout << " (" << lastCashTransaction << ")";
		cout << endl;
		cout << "Net cash flow: " << cashGained - cashSpent << endl;
		
	}
}