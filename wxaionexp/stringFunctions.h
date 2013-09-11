#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

string formatKiloMega(float number);
string stripCommas(string line);
string formatCurrentAndNextValues(int current, int next);
string formatNumber(int number, bool addPlusSign = false);
string formatPercent(float percentage);
string formatPercentChange(float value);
double calculateExpPercent(int currentExp, int nextLevel);
string formatAbyssRankName(int abyssRank);
string formatElapsedTime(int elapsedTime);

int verifyNumericInput(string input);