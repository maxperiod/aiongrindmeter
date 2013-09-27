#include <string>
#include <fstream>

#define header(message) cout << endl << "====================" << endl \
	<< message << endl << "====================" << endl

#define doTest(description, value, expected) \
	if (value != expected) { \
		cout << "---FAILED--- "; \
		numFailed ++; \
	} \
	cout << description << ": Expected " << expected << ", actual " << value; \
	numTestCases ++; \
	cout << endl
#define printSummary() cout << endl \
	<< "Total test cases: " << numTestCases << endl \
	<< "Failed test cases: " << numFailed << endl 



using namespace std;



void makeFileCopy(string original, string copy);
void appendFile(string file, string line);