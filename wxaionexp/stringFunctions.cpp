#include "stringFunctions.h"

string formatKiloMega(float number){
	ostringstream oss;

	if (abs(number) >= 1000000000){
		oss << setprecision(3) << number / 1000000000 << " B / h";
	}
	else if (abs(number) >= 1000000){
		oss << setprecision(3) << number / 1000000 << " M / h";
	}
	else {
		oss << setprecision(3) << number / 1000 << " k / h";
	}
	return oss.str();
}

/*********************************************************************************************
Remove non-numeric characters from the string, intended for strip commas from a number
*********************************************************************************************/
string stripCommas(string line){
	
	string newString;

	for (int i = 0; i < line.length(); i ++){
		if (line.at(i) >= 48 && line.at(i) <= 57){
			newString.push_back(line.at(i));
		}
	}
	return newString;
}

/*********************************************************************************************
Format a integer with comma separators. Optionally add plus sign on non-negative numbers
*********************************************************************************************/
string formatNumber(int number, bool addPlusSign){
	ostringstream oss;
	oss.imbue(locale(""));
	if (addPlusSign && number >= 0) oss << "+";
	oss << fixed << number;
	return oss.str();
	
}

/*********************************************************************************************
Format percentages with 2 decimal spaces
*********************************************************************************************/
string formatPercent(float percentage){
	ostringstream oss;
	oss.imbue(locale(""));
	oss << fixed << setprecision(2) << percentage << "%";
	return oss.str();
}

/*********************************************************************************************
Format percentage changes. 2 decimal spaces, 3 if below 0.1% Add plus sign if not negative
*********************************************************************************************/
string formatPercentChange(float value){
	ostringstream oss;
	oss.imbue(locale(""));
	
	if (value >= 0) oss << "+";
	oss << fixed;
	if (abs(value) < 0.0005) oss << setprecision(0);
	else if (abs(value) < 0.1) oss << setprecision(3);
	else oss << setprecision(2);
	
	oss << value << "%";
	return oss.str();
}

/*********************************************************************************************
Format two values into (XXX,XXX,XXX / YYY,YYY,YYY)
*********************************************************************************************/
string formatCurrentAndNextValues(int current, int next){
	ostringstream oss;
	oss.imbue(locale(""));
	
	if (current >= 0) oss << current;
	else oss << "???";
	oss << " / ";
	if (next >= 0) oss << next;
	else oss << "???";
	return oss.str();
}


double calculateExpPercent(int currentExp, int nextLevel){
	
	return floor((double)currentExp / nextLevel * 10000) / 100;

	
}

/*********************************************************************************************
Get of Abyss Rank
*********************************************************************************************/
string formatAbyssRankName(int abyssRank){
	ostringstream oss;
	if (abyssRank > 1) oss << abyssRank << " kyu";
	else oss << "???";
	return oss.str();
}

/*********************************************************************************************
Format elasped time into HH : MM : SS format
*********************************************************************************************/
string formatElapsedTime(int elapsedTime){
	ostringstream oss;
	int hours = elapsedTime / 3600;
	int minutes = (elapsedTime % 3600) / 60;
	int seconds = elapsedTime % 60;
	
	if (hours < 10) oss << "0";
	oss << hours << " : ";
	if (minutes < 10) oss << "0";
	oss << minutes << " : ";
	if (seconds < 10) oss << "0";
	oss << seconds;

	return oss.str();

}

/*********************************************************************************************
Verify a string to see whether it's a valid integer or not. Invalid inputs return -1
*********************************************************************************************/
int verifyNumericInput(string input){
	bool hasComma = false;
	bool hasPeriod = false;

	
	while(input[0] == ' ') input.erase(0, 1);
	while (input[input.length() - 1] == ' ') input.erase(input.length() - 1, 1);
	if (input.length() < 1) return -2;

	for (int i = 0; i < input.length(); i ++){
		if (!((input[i] >= 48 && input[i] <= 57) || input[i] == ',' || input[i] == '.'))
			return -1;
	}
	
	for (int i = 0; i < input.length(); i ++){
		if (input[i] == ',') hasComma = true;
	}

	for (int i = 0; i < input.length(); i ++){
		if (input[i] == '.'){
			if (hasComma) return -1;
			else hasPeriod = true;
		}
	}
		
	if (hasComma || hasPeriod){
		for (int i = 0; i < input.length(); i ++){
			if (input[i] == ',' || input[i] == '.'){
				if (i == 0) return -1;
				if ((input.length() - i) % 4 != 0) return -1;
				
			}
			else if ((input.length() - i) % 4 == 0) return -1;
		}

	}

	return atoi(stripCommas(input).c_str());
}