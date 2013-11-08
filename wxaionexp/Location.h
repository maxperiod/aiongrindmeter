#include <string>
#include <sstream>

using namespace std;

class LocationPinger{
public:
	float x;
	float y;


	float prevX;
	float prevY;

	float distKm;
	float distMiles;

	int map;
	int lastMap;
	

	LocationPinger();

	void pingLocation(string line);
	
	void calculateDistance();

};

