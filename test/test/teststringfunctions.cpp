#include "testHelpers.h"
#include "../../wxaionexp/stringFunctions.h"
#include <iostream>
using namespace std;

int numTestCases = 0;
int numFailed = 0;

int main(){
	cout << endl << "String Functions" << endl;
	
	//================================================================================

	cout << endl << "formatKiloMega" << endl;

	string formatKiloMegaMinus1 = formatKiloMega(-1050520.97);
	doTest("formatKiloMegaMinus1", formatKiloMegaMinus1, "-1.05 M / h");

	string formatKiloMega0 = formatKiloMega(-150);
	doTest("formatKiloMega0", formatKiloMega0, "-0.150 k / h");

	string formatKiloMega1 = formatKiloMega(0);
	doTest("formatKiloMega1", formatKiloMega1, "0 k / h");

	string formatKiloMega2 = formatKiloMega(1010.975);
	doTest("formatKiloMega2", formatKiloMega2, "1.01 k / h");

	string formatKiloMega3 = formatKiloMega(998.510);
	doTest("formatKiloMega3", formatKiloMega3, "0.999 k / h");

	string formatKiloMega4 = formatKiloMega(1000012.345);
	doTest("formatKiloMega4", formatKiloMega4, "1.00 M / h");

	string formatKiloMega7 = formatKiloMega(1000000000.467);
	doTest("formatKiloMega7", formatKiloMega7, "1.00 B / h");

	string formatKiloMega8 = formatKiloMega(999099999999.99);
	doTest("formatKiloMega8", formatKiloMega8, "999 B / h");

	//================================================================================

	cout << endl << "formatNumber" << endl;

	string formatNumber1 = formatNumber(1234);
	doTest("formatNumber1", formatNumber1, "1,234");

	string formatNumber2 = formatNumber(123);
	doTest("formatNumber2", formatNumber2, "123");

	string formatNumber3 = formatNumber(876543210);
	doTest("formatNumber3", formatNumber3, "876,543,210");

	//================================================================================

	cout << endl << "formatCurrentAndNextValues" << endl;

	string formatCurrentAndNextValues1 = formatCurrentAndNextValues(0, 1);
	doTest("formatCurrentAndNextValues1", formatCurrentAndNextValues1, "0 / 1");

	string formatCurrentAndNextValues2 = formatCurrentAndNextValues(-1, 165798);
	doTest("formatCurrentAndNextValues2", formatCurrentAndNextValues2, "??? / 165,798");

	string formatCurrentAndNextValues3 = formatCurrentAndNextValues(2103657987, -1);
	doTest("formatCurrentAndNextValues3", formatCurrentAndNextValues3, "2,103,657,987 / ???");

	//================================================================================

	int verifyNumericInput1 = verifyNumericInput("12345");
	doTest("verifyNumericInput1", verifyNumericInput1, 12345);

	int verifyNumericInput2 = verifyNumericInput("15,623,733");
	doTest("verifyNumericInput2", verifyNumericInput2, 15623733);

	int verifyNumericInput3 = verifyNumericInput(" 36,203");
	doTest("verifyNumericInput3", verifyNumericInput3, 36203);

	int verifyNumericInput4 = verifyNumericInput("364,455  ");
	doTest("verifyNumericInput4", verifyNumericInput4, 364455);

	int verifyNumericInput5 = verifyNumericInput("6.789");
	doTest("verifyNumericInput5", verifyNumericInput5, 6789);

	int verifyNumericInput6 = verifyNumericInput("a6923");
	doTest("verifyNumericInput6", verifyNumericInput6, -1);

	int verifyNumericInput7 = verifyNumericInput("");
	doTest("verifyNumericInput7", verifyNumericInput7, -2);

	int verifyNumericInput7a = verifyNumericInput("    ");
	doTest("verifyNumericInput7a", verifyNumericInput7a, -2);

	int verifyNumericInput8 = verifyNumericInput("4,4963,567");
	doTest("verifyNumericInput8", verifyNumericInput8, -1);

	int verifyNumericInput9 = verifyNumericInput("5,55");
	doTest("verifyNumericInput9", verifyNumericInput9, -1);

	int verifyNumericInput10 = verifyNumericInput(",975");
	doTest("verifyNumericInput10", verifyNumericInput10, -1);

	int verifyNumericInput11 = verifyNumericInput("7654,310");
	doTest("verifyNumericInput11", verifyNumericInput11, -1);

	int verifyNumericInput12 = verifyNumericInput("6,74y,3C6");
	doTest("verifyNumericInput12", verifyNumericInput12, -1);

	int verifyNumericInput13 = verifyNumericInput("33s3");
	doTest("verifyNumericInput13", verifyNumericInput13, -1);
	
	//================================================================================

	printSummary();
	
	getchar();
	return 0;
}