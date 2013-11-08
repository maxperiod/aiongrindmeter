#include "Location.h"
#include <iostream>;
LocationPinger::LocationPinger(){
	x = 0;
	y = 0;


	prevX = 0;
	prevY = 0;

	distKm = 0;
	distMiles = 0;

	map = 0;
	lastMap = 0;
}

void LocationPinger::pingLocation(string line){
	stringstream ss(line);
	//while(true);
	string dummy;	
	
	

	getline(ss, dummy, '['); //You 
	
	getline(ss, dummy, ':'); //Have
	if (dummy == "pos"){
		getline(ss, dummy, ';'); //gained
		
		getline(ss, dummy, ' ');		
		lastMap = map;
		map = atoi(dummy.c_str());		

		getline(ss, dummy, ' ');
		prevX = x;
		x = atof(dummy.c_str());

		getline(ss, dummy, ' ');
		prevY = y;
		y = atof(dummy.c_str());
		
		calculateDistance();
		
	}
	
}

void LocationPinger::calculateDistance(){
	if (map == lastMap){
		distKm = sqrt((x - prevX) * (x - prevX) + (y - prevY) * (y - prevY)) / 1000;
		distMiles = distKm * 0.62137;
	}
	else{
		distKm = 0;
		distMiles = 0;
	}
}