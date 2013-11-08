#include "../../wxaionexp/LogFileParser.h"
#include "testHelpers.h"

int numTestCases = 0;
int numFailed = 0;

int main(){

	makeFileCopy("tests.log", "temp.txt");

	//================================================================================

	header("File Loading");

	ExpHourCalc *expHourCalc = new ExpHourCalc();
	GatheringLog *gatheringLog = new GatheringLog();
	
	LogFileParser *fileNotExist = new LogFileParser("sdlfkjskldfj");
	doTest("LogFileParser with invalid logfile input", fileNotExist->isOK, false);

	LogFileParser *parser = new LogFileParser("temp.txt");
	parser->setExpHourCalc(expHourCalc);
	parser->setGatheringLog(gatheringLog);
	
	doTest("LogFileParser with valid logfile", parser->isOK, true);

	//================================================================================

	header("Essencetapping - no level up");
	expHourCalc->reset();
	gatheringLog->reset();
	
	appendFile("temp.txt", "2013.11.03 19:27:09 : You have started gathering Hintera. ");
	parser->processLines();
	appendFile("temp.txt", "2013.11.03 19:27:14 : Japanese Dolls has conquered Heart of Fissure. ");	
	appendFile("temp.txt", "2013.11.03 19:27:19 : You have acquired [item:152000419;ver4;;;;]. ");
	appendFile("temp.txt", "2013.11.03 19:27:19 : You have gained 9,684 XP (Energy of Salvation 2,075). ");
	appendFile("temp.txt", "2013.11.03 19:27:19 : You have gained experience from gathering. ");

	parser->processLines();

	

	doTest("expGained", expHourCalc->expGained, 9684);
	doTest("numGatheringSuccesses", gatheringLog->numGatheringSuccesses, 1);
	doTest("numGatheringFailures", gatheringLog->numGatheringFailures, 0);
	doTest("numGatheringCancellations", gatheringLog->numGatheringCancellations, 0);
	doTest("gatheringRecord.size()", gatheringLog->gatheringRecord.size(), 1);
	doTest("gatheringRecord[0].name", gatheringLog->gatheringRecord[0].name, "Hintera");
	doTest("gatheringRecord[0].successes", gatheringLog->gatheringRecord[0].successes, 1);
	doTest("gatheringRecord[0].failures", gatheringLog->gatheringRecord[0].failures, 0);
	doTest("gatheringRecord[0].cancellations", gatheringLog->gatheringRecord[0].cancellations, 0);
	doTest("gatherLevelUps.size()", gatheringLog->gatherLevelUps.size(), 0);
	doTest("gatheringLvl", gatheringLog->gatheringLvl, -1);
	doTest("currentlyCrafting", gatheringLog->currentlyCrafting, false);
	

	header("Essencetapping - level up");

	appendFile("temp.txt", "2013.11.03 19:19:33 : You have started gathering Fresh Hintera. ");
	parser->processLines();
	appendFile("temp.txt", "2013.11.03 19:19:43 : Your Essencetapping skill has been upgraded to 485 points. ");
	appendFile("temp.txt", "2013.11.03 19:19:43 : You have acquired [item:152000420;ver4;;;;]. ");
	appendFile("temp.txt", "2013.11.03 19:19:43 : You have gained 9,684 XP (Energy of Salvation 2,075). ");
	appendFile("temp.txt", "2013.11.03 19:19:43 : You have gained experience from gathering. ");

	parser->processLines();
	doTest("numGatheringSuccesses", gatheringLog->numGatheringSuccesses, 2);
	doTest("numGatheringFailures", gatheringLog->numGatheringFailures, 0);
	doTest("numGatheringCancellations", gatheringLog->numGatheringCancellations, 0);
	doTest("gatheringRecord.size()", gatheringLog->gatheringRecord.size(), 2);
	doTest("gatheringRecord[1].name", gatheringLog->gatheringRecord[1].name, "Fresh Hintera");
	doTest("gatheringRecord[1].successes", gatheringLog->gatheringRecord[1].successes, 1);
	doTest("gatheringRecord[1].failures", gatheringLog->gatheringRecord[1].failures, 0);
	doTest("gatheringRecord[1].cancellations", gatheringLog->gatheringRecord[1].cancellations, 0);
	doTest("gatherLevelUps.size()", gatheringLog->gatherLevelUps.size(), 1);
	doTest("gatherLevelUps[0].level", gatheringLog->gatherLevelUps[0].level, 485);
	doTest("gatherLevelUps[0].numGathers", gatheringLog->gatherLevelUps[0].numGathers, -1);
	doTest("", gatheringLog->numGatheredSinceLevelUp, 0);
	doTest("gatheringLvl", gatheringLog->gatheringLvl, 485);
	doTest("currentlyCrafting", gatheringLog->currentlyCrafting, false);

	header("Essencetapping - Two items of same kind");

	appendFile("temp.txt", "2013.11.03 19:27:09 : You have started gathering Hintera. ");
	parser->processLines();
	appendFile("temp.txt", "2013.11.03 19:27:14 : Japanese Dolls has conquered Heart of Fissure. ");	
	appendFile("temp.txt", "2013.11.03 19:27:19 : You have acquired [item:152000419;ver4;;;;]. ");
	appendFile("temp.txt", "2013.11.03 19:27:19 : You have gained 9,684 XP (Energy of Salvation 2,075). ");
	appendFile("temp.txt", "2013.11.03 19:27:19 : You have gained experience from gathering. ");

	parser->processLines();

	doTest("expGained", expHourCalc->expGained, 9684 * 3);
	doTest("numGatheringSuccesses", gatheringLog->numGatheringSuccesses, 3);
	doTest("numGatheringFailures", gatheringLog->numGatheringFailures, 0);
	doTest("numGatheringCancellations", gatheringLog->numGatheringCancellations, 0);
	doTest("gatheringRecord.size()", gatheringLog->gatheringRecord.size(), 2);
	doTest("gatheringRecord[0].name", gatheringLog->gatheringRecord[0].name, "Hintera");
	doTest("gatheringRecord[0].successes", gatheringLog->gatheringRecord[0].successes, 2);
	doTest("gatheringRecord[0].failures", gatheringLog->gatheringRecord[0].failures, 0);
	doTest("gatheringRecord[0].cancellations", gatheringLog->gatheringRecord[0].cancellations, 0);
	doTest("gatherLevelUps.size()", gatheringLog->gatherLevelUps.size(), 1);
	doTest("numGatheredSinceLevelUp", gatheringLog->numGatheredSinceLevelUp, 1);
	doTest("currentlyCrafting", gatheringLog->currentlyCrafting, false);

	header("Essencetapping - Failure");

	appendFile("temp.txt", "2013.11.03 18:46:41 : You have started gathering Anevra.");
	parser->processLines();
	appendFile("temp.txt", "2013.11.03 18:46:56 : You have failed to gather Anevra.");
	parser->processLines();

	doTest("expGained", expHourCalc->expGained, 9684 * 3);
	doTest("numGatheringSuccesses", gatheringLog->numGatheringSuccesses, 3);
	doTest("numGatheringFailures", gatheringLog->numGatheringFailures, 1);
	doTest("numGatheringCancellations", gatheringLog->numGatheringCancellations, 0);
	doTest("gatheringRecord.size()", gatheringLog->gatheringRecord.size(), 3);
	doTest("gatheringRecord[2].name", gatheringLog->gatheringRecord[2].name, "Anevra");
	doTest("gatheringRecord[2].successes", gatheringLog->gatheringRecord[2].successes, 0);
	doTest("gatheringRecord[2].failures", gatheringLog->gatheringRecord[2].failures, 1);
	doTest("gatheringRecord[2].cancellations", gatheringLog->gatheringRecord[2].cancellations, 0);
	doTest("gatherLevelUps.size()", gatheringLog->gatherLevelUps.size(), 1);
	doTest("numGatheredSinceLevelUp", gatheringLog->numGatheredSinceLevelUp, 1);
	doTest("currentlyCrafting", gatheringLog->currentlyCrafting, false);

	header("Essencetapping - Cancel");

	appendFile("temp.txt", "2013.11.03 18:50:25 : You have started gathering Anevra. ");
	appendFile("temp.txt", "2013.11.03 18:50:25 : You have stopped gathering. ");
	parser->processLines();

	doTest("expGained", expHourCalc->expGained, 9684 * 3);
	doTest("numGatheringSuccesses", gatheringLog->numGatheringSuccesses, 3);
	doTest("numGatheringFailures", gatheringLog->numGatheringFailures, 1);
	doTest("numGatheringCancellations", gatheringLog->numGatheringCancellations, 1);
	doTest("gatheringRecord.size()", gatheringLog->gatheringRecord.size(), 3);
	doTest("gatheringRecord[2].name", gatheringLog->gatheringRecord[2].name, "Anevra");
	doTest("gatheringRecord[2].successes", gatheringLog->gatheringRecord[2].successes, 0);
	doTest("gatheringRecord[2].failures", gatheringLog->gatheringRecord[2].failures, 1);
	doTest("gatheringRecord[2].cancellations", gatheringLog->gatheringRecord[2].cancellations, 1);
	doTest("gatherLevelUps.size()", gatheringLog->gatherLevelUps.size(), 1);
	doTest("numGatheredSinceLevelUp", gatheringLog->numGatheredSinceLevelUp, 1);
	doTest("gatheringLvl", gatheringLog->gatheringLvl, 485);
	doTest("currentlyCrafting", gatheringLog->currentlyCrafting, false);

	header("Essencetapping - must level up");

	appendFile("temp.txt", "2013.11.03 19:27:09 : You have started gathering Hintera. ");
	parser->processLines();
	appendFile("temp.txt", "2013.11.03 19:27:14 : Japanese Dolls has conquered Heart of Fissure. ");	
	appendFile("temp.txt", "2013.11.03 19:27:14 : You must level up to raise your skill level.");
	appendFile("temp.txt", "2013.11.03 19:27:19 : You have acquired [item:152000419;ver4;;;;]. ");
	appendFile("temp.txt", "2013.11.03 19:27:19 : You have gained 9,684 XP (Energy of Salvation 2,075). ");
	appendFile("temp.txt", "2013.11.03 19:27:19 : You have gained experience from gathering. ");

	parser->processLines();

	doTest("expGained", expHourCalc->expGained, 9684 * 4);
	doTest("numGatheringSuccesses", gatheringLog->numGatheringSuccesses, 4);
	doTest("numGatheringFailures", gatheringLog->numGatheringFailures, 1);
	doTest("numGatheringCancellations", gatheringLog->numGatheringCancellations, 1);
	doTest("gatheringRecord.size()", gatheringLog->gatheringRecord.size(), 3);	
	doTest("gatheringRecord[0].successes", gatheringLog->gatheringRecord[0].successes, 3);
	doTest("gatheringRecord[0].failures", gatheringLog->gatheringRecord[0].failures, 0);
	doTest("gatheringRecord[0].cancellations", gatheringLog->gatheringRecord[0].cancellations, 0);
	doTest("gatherLevelUps.size()", gatheringLog->gatherLevelUps.size(), 1);
	doTest("numGatheredSinceLevelUp", gatheringLog->numGatheredSinceLevelUp, 1);
	doTest("gatheringLvl", gatheringLog->gatheringLvl, 485);
	doTest("currentlyCrafting", gatheringLog->currentlyCrafting, false);

	header("Gathering - too low level. Assume aethertapping level = essencetapping level");

	appendFile("temp.txt", "2013.11.05 15:08:51 : You have started gathering Magical Aether. ");
	parser->processLines();
	appendFile("temp.txt", "2013.11.05 15:08:53 : The skill level for the Aethertapping skill does not increase as the difficulty is too low. ");
	appendFile("temp.txt", "2013.11.05 15:08:53 : You have acquired [item:152000911;ver4;;;;]. ");

	parser->processLines();

	doTest("expGained", expHourCalc->expGained, 9684 * 4);
	doTest("numGatheringSuccesses", gatheringLog->numGatheringSuccesses, 5);
	doTest("numGatheringFailures", gatheringLog->numGatheringFailures, 1);
	doTest("numGatheringCancellations", gatheringLog->numGatheringCancellations, 1);
	doTest("gatheringRecord.size()", gatheringLog->gatheringRecord.size(), 4);	
	doTest("gatheringRecord[0].successes", gatheringLog->gatheringRecord[3].successes, 1);
	doTest("gatheringRecord[0].failures", gatheringLog->gatheringRecord[0].failures, 0);
	doTest("gatheringRecord[0].cancellations", gatheringLog->gatheringRecord[0].cancellations, 0);
	doTest("getGatherSuccessRate()", gatheringLog->getGatherSuccessRate(), (float)5 * 100 / 7);
	doTest("getGatherFailureRate()", gatheringLog->getGatherFailureRate(), (float)1 * 100 / 7);
	doTest("getGatherCancellationRate()", gatheringLog->getGatherCancellationRate(), (float)1 * 100 / 7);
	doTest("gatherLevelUps.size()", gatheringLog->gatherLevelUps.size(), 1);
	doTest("numGatheredSinceLevelUp", gatheringLog->numGatheredSinceLevelUp, 1);
	doTest("gatheringLvl", gatheringLog->gatheringLvl, 485);
	doTest("currentlyCrafting", gatheringLog->currentlyCrafting, false);
	//doTest("

	//================================================================================

	header("Gathering level ups");

	expHourCalc->reset();
	gatheringLog->reset();

	appendFile("temp.txt", "2013.11.07 09:51:20 : You have started gathering Inina."); 
	appendFile("temp.txt", "2013.11.07 09:51:27 : Mud Potcrab is no longer immobilized. ");
	appendFile("temp.txt", "2013.11.07 09:51:30 : EastWay-TM inflicted 215 damage on Mud Potcrab by using Precision Shot I. ");
	appendFile("temp.txt", "2013.11.07 09:51:30 : Your Essencetapping skill has been upgraded to 14 points. ");
	appendFile("temp.txt", "2013.11.07 09:51:30 : You have acquired [item:152001001;ver4;;;;]. ");
	appendFile("temp.txt", "2013.11.07 09:51:30 : You have gained 574 XP (Energy of Repose 164). ");
	appendFile("temp.txt", "2013.11.07 09:51:30 : You have gained experience from gathering. ");
	appendFile("temp.txt", "2013.11.07 09:51:57 : You have started gathering Cypri. ");
	appendFile("temp.txt", "2013.11.07 09:52:14 : You have acquired [item:152000801;ver4;;;;]. ");
	appendFile("temp.txt", "2013.11.07 09:52:14 : You have gained 604 XP (Energy of Repose 172). ");
	appendFile("temp.txt", "2013.11.07 09:52:14 : You have gained experience from gathering. ");
	appendFile("temp.txt", "2013.11.07 09:52:16 : You have started gathering Cypri. ");
	appendFile("temp.txt", "2013.11.07 09:52:23 : You have acquired [item:152000801;ver4;;;;]. ");
	appendFile("temp.txt", "2013.11.07 09:52:23 : You have gained 604 XP (Energy of Repose 172). ");
	appendFile("temp.txt", "2013.11.07 09:52:23 : You have gained experience from gathering. ");
	appendFile("temp.txt", "2013.11.07 09:52:25 : You have started gathering Cypri. ");
	appendFile("temp.txt", "2013.11.07 09:52:34 : Your Essencetapping skill has been upgraded to 15 points. ");
	appendFile("temp.txt", "2013.11.07 09:52:34 : You have acquired [item:152000801;ver4;;;;]. ");
	appendFile("temp.txt", "2013.11.07 09:52:34 : You have gained 604 XP (Energy of Repose 172). ");
	appendFile("temp.txt", "2013.11.07 09:52:34 : You have gained experience from gathering. ");
	appendFile("temp.txt", "2013.11.07 09:52:40 : You have started gathering Inina. ");
	appendFile("temp.txt", "2013.11.07 09:52:44 : You have acquired [item:152001001;ver4;;;;]. ");
	appendFile("temp.txt", "2013.11.07 09:52:44 : You have gained 574 XP (Energy of Repose 164). ");
	appendFile("temp.txt", "2013.11.07 09:52:44 : You have gained experience from gathering. ");
	appendFile("temp.txt", "2013.11.07 09:52:46 : You have started gathering Inina. ");
	appendFile("temp.txt", "2013.11.07 09:52:55 : You have acquired [item:152001001;ver4;;;;]. ");
	appendFile("temp.txt", "2013.11.07 09:52:55 : You have gained 574 XP (Energy of Repose 164). ");
	appendFile("temp.txt", "2013.11.07 09:52:55 : You have gained experience from gathering. ");
	appendFile("temp.txt", "2013.11.07 09:52:56 : You have started gathering Inina. ");
	appendFile("temp.txt", "2013.11.07 09:52:57 : [3.LFG] [charname:JoelSankop-SL;1.0000 0.6941 0.6941]: [cmd:Ra/yGXhE/coQcISQergrqANBoy+aE2Muwz5EmG7hiRpFUYOZnylZ5HCClET+4/tCmXDUZHEZNU/tGAwpVxrJlA==]LFG for Fire Temple need all ");
	appendFile("temp.txt", "2013.11.07 09:52:58 : Your Essencetapping skill has been upgraded to 16 points. ");
	appendFile("temp.txt", "2013.11.07 09:52:58 : You have acquired [item:152001001;ver4;;;;]. ");
	appendFile("temp.txt", "2013.11.07 09:52:58 : You have gained 574 XP (Energy of Repose 164). ");
	appendFile("temp.txt", "2013.11.07 09:52:58 : You have gained experience from gathering. ");
	appendFile("temp.txt", "2013.11.07 09:52:40 : You have started gathering Inina. ");
	appendFile("temp.txt", "2013.11.07 09:52:44 : You have acquired [item:152001001;ver4;;;;]. ");
	appendFile("temp.txt", "2013.11.07 09:52:44 : You have gained 574 XP (Energy of Repose 164). ");
	appendFile("temp.txt", "2013.11.07 09:52:44 : You have gained experience from gathering. ");
	appendFile("temp.txt", "2013.11.07 09:52:46 : You have started gathering Inina. ");
	appendFile("temp.txt", "2013.11.07 09:52:55 : You have acquired [item:152001001;ver4;;;;]. ");
	appendFile("temp.txt", "2013.11.07 09:52:55 : You have gained 574 XP (Energy of Repose 164). ");
	appendFile("temp.txt", "2013.11.07 09:52:55 : You have gained experience from gathering. ");
	parser->processLines();

	doTest("numGatheringSuccesses", gatheringLog->numGatheringSuccesses, 9);
	doTest("numGatheringFailures", gatheringLog->numGatheringFailures, 0);
	doTest("numGatheringCancellations", gatheringLog->numGatheringCancellations, 0);
	doTest("gatheringRecord.size()", gatheringLog->gatheringRecord.size(), 2);	
	doTest("gatheringRecord[0].name", gatheringLog->gatheringRecord[0].name, "Inina");
	doTest("gatheringRecord[0].successes", gatheringLog->gatheringRecord[0].successes, 6);
	doTest("gatheringRecord[0].failures", gatheringLog->gatheringRecord[0].failures, 0);
	doTest("gatheringRecord[0].cancellations", gatheringLog->gatheringRecord[0].cancellations, 0);
	doTest("gatheringRecord[1].name", gatheringLog->gatheringRecord[1].name, "Cypri");
	doTest("gatheringRecord[1].successes", gatheringLog->gatheringRecord[01].successes, 3);
	doTest("gatheringRecord[1].failures", gatheringLog->gatheringRecord[1].failures, 0);
	doTest("gatheringRecord[1].cancellations", gatheringLog->gatheringRecord[1].cancellations, 0);
	doTest("gatherLevelUps.size()", gatheringLog->gatherLevelUps.size(), 3);
	doTest("numGatheredSinceLevelUp", gatheringLog->numGatheredSinceLevelUp, 2);
	doTest("gatherLevelUps[0].level", gatheringLog->gatherLevelUps[0].level, 14);
	doTest("gatherLevelUps[1].level", gatheringLog->gatherLevelUps[1].level, 15);
	doTest("gatherLevelUps[2].level", gatheringLog->gatherLevelUps[2].level, 16);
	doTest("gatherLevelUps[0].numGathers", gatheringLog->gatherLevelUps[0].numGathers, -1);
	doTest("gatherLevelUps[1].numGathers", gatheringLog->gatherLevelUps[1].numGathers, 3);
	doTest("gatherLevelUps[2].numGathers", gatheringLog->gatherLevelUps[2].numGathers, 3);
	doTest("numGatheredSinceLevelUp", gatheringLog->numGatheredSinceLevelUp, 2);
	doTest("lastNumGatheredToLevelUp", gatheringLog->lastNumGatheredToLevelUp, 3);

	//================================================================================

	expHourCalc->reset();
	gatheringLog->reset();

	header("Crafting");

	appendFile("temp.txt", "2013.11.05 18:04:10 : Quest acquired: Gritty Conide Supplies");
	appendFile("temp.txt", "2013.11.05 18:04:10 : You have acquired 4 [item:182291205;ver4;;;;]s and stored them in your special cube. ");
	appendFile("temp.txt", "2013.11.05 18:04:37 : You are crafting Gritty Conide. ");	
	parser->processLines();
	appendFile("temp.txt", "2013.11.05 18:04:47 : Your Cooking skill has been upgraded to 2 points. ");
	appendFile("temp.txt", "2013.11.05 18:04:47 : You have gained 1,146 XP (Energy of Repose 327). ");
	appendFile("temp.txt", "2013.11.05 18:04:47 : You have crafted successfully. ");
	appendFile("temp.txt", "2013.11.05 18:04:47 : You have crafted [item:182291522;ver4;;;;]. ");
	appendFile("temp.txt", "2013.11.05 18:04:47 : Quest updated: Gritty Conide Supplies ");
	appendFile("temp.txt", "2013.11.05 18:04:49 : You are crafting Gritty Conide. ");
	parser->processLines();
	appendFile("temp.txt", "2013.11.05 18:04:58 : Your Cooking skill has been upgraded to 3 points. ");
	appendFile("temp.txt", "2013.11.05 18:04:59 : You have crafted [item:182291522;ver4;;;;]. ");
	appendFile("temp.txt", "2013.11.05 18:04:59 : You have gained 1,146 XP (Energy of Repose 327). ");
	appendFile("temp.txt", "2013.11.05 18:04:59 : You have crafted successfully. ");
	appendFile("temp.txt", "2013.11.05 18:04:59 : Quest updated: Gritty Conide Supplies ");
	appendFile("temp.txt", "2013.11.05 18:05:01 : You are crafting Gritty Conide. ");
	parser->processLines();
	appendFile("temp.txt", "2013.11.05 18:05:04 : [3.LFG] [charname:Lieli;1.0000 0.6941 0.6941]: wtb [item:101301035;ver4;;;;] my pass, also buying [item:188950013;ver4;;s1a5spLXkRt+gYzaPXKeBd4A58W0H7ZP1LsHWSKEc2XLgHfTXkjFkATB1c8mejKmH0qUYnk1U7Kcwvu29yr3DA==;;] [item:186000237;ver4;;;;] (2100) pst ] ");
	appendFile("temp.txt", "2013.11.05 18:05:10 : Your Cooking skill has been upgraded to 4 points. ");
	appendFile("temp.txt", "2013.11.05 18:05:10 : You have crafted [item:182291522;ver4;;;;]. ");
	appendFile("temp.txt", "2013.11.05 18:05:10 : You have gained 1,146 XP (Energy of Repose 327). ");
	appendFile("temp.txt", "2013.11.05 18:05:10 : You have crafted successfully. ");
	appendFile("temp.txt", "2013.11.05 18:05:10 : Quest updated: Gritty Conide Supplies ");
	appendFile("temp.txt", "2013.11.05 18:05:12 : You are crafting Gritty Conide. ");
	parser->processLines();
	appendFile("temp.txt", "2013.11.05 18:05:27 : You have failed to craft Gritty Conide. ");
	parser->processLines();

	doTest("numCraftingSuccesses", gatheringLog->numCraftingSuccesses, 3);
	doTest("numCraftingFailures", gatheringLog->numCraftingFailures, 1);
	doTest("numCraftingCancellations", gatheringLog->numCraftingCancellations, 0);	
	doTest("numCraftingProcs", gatheringLog->numCraftingProcs, 0);
	doTest("gatherLevelUps.size()", gatheringLog->gatherLevelUps.size(), 0);
	doTest("craftLevelUps.size()", gatheringLog->craftLevelUps.size(), 3);
	doTest("gatheringRecord.size()", gatheringLog->gatheringRecord.size(), 0);
	doTest("craftingRecord.size()", gatheringLog->craftingRecord.size(), 1);
	doTest("craftingRecord[0].name", gatheringLog->craftingRecord[0].name, "Gritty Conide");
	doTest("craftingRecord[0].successes", gatheringLog->craftingRecord[0].successes, 3);
	doTest("craftingRecord[0].failures", gatheringLog->craftingRecord[0].failures, 1);
	doTest("craftingRecord[0].cancellations", gatheringLog->craftingRecord[0].cancellations, 0);
	doTest("craftingRecord[0].failures", gatheringLog->craftingRecord[0].failures, 1);
	doTest("craftingRecord[0].cancellations", gatheringLog->craftingRecord[0].cancellations, 0);
	doTest("craftLevelUps[0].level", gatheringLog->craftLevelUps[0].level, 2);
	doTest("craftLevelUps[0].numGathers", gatheringLog->craftLevelUps[0].numGathers, -1);
	doTest("craftLevelUps[1].level", gatheringLog->craftLevelUps[1].level, 3);
	doTest("craftLevelUps[1].numGathers", gatheringLog->craftLevelUps[1].numGathers, 1);
	doTest("craftLevelUps[2].level", gatheringLog->craftLevelUps[2].level, 4);
	doTest("craftLevelUps[2].numGathers", gatheringLog->craftLevelUps[2].numGathers, 1);
	doTest("numCraftedSinceLevelUp", gatheringLog->numCraftedSinceLevelUp, 0);
	doTest("lastNumCraftedToLevelUp", gatheringLog->lastNumCraftedToLevelUp, 1);
	doTest("estimateNumCraftsToNextLevel", gatheringLog->estimateNumCraftsToNextLevel, 1);
	doTest("currentlyCrafting", gatheringLog->currentlyCrafting, false);
	 
	header("Crafting procs");

	appendFile("temp.txt", "2013.07.17 11:13:18 : You are crafting Poma Herb Bulgogi. ");
	parser->processLines();
	appendFile("temp.txt", "2013.07.17 11:13:31 : You are crafting Tasty Poma Herb Bulgogi. ");
	parser->processLines();
	appendFile("temp.txt", "2013.07.17 11:14:04 : You have gained 15,210 XP. ");
	appendFile("temp.txt", "2013.07.17 11:14:04 : You have crafted successfully. ");
	appendFile("temp.txt", "2013.07.17 11:14:04 : You have crafted 2 [item:160002347;ver4;;;;]s. ");
	appendFile("temp.txt", "2013.07.17 11:14:07 : You are crafting Poma Herb Bulgogi. ");
	parser->processLines();
	appendFile("temp.txt", "2013.07.17 11:14:34 : You are crafting Tasty Poma Herb Bulgogi. ");
	parser->processLines();
	appendFile("temp.txt", "2013.07.17 11:14:49 : You have crafted 2 [item:160002347;ver4;;;;]s. ");
	appendFile("temp.txt", "2013.07.17 11:14:49 : You have gained 15,210 XP. ");
	appendFile("temp.txt", "2013.07.17 11:14:49 : You have crafted successfully. ");
	appendFile("temp.txt", "2013.07.17 11:14:49 : [3.LFG] [charname:Xnxx;1.0000 0.6941 0.6941]: [cmd:YN9dx6QUIAkfM1CUPjouv0VRg5mfKVnkcIKURP7j+0JFUYOZnylZ5HCClET+4/tCzzNQLIyOe3eXmGh3h+unUQ==]BT DUO NEED CLER CHANT!!!??? ");
	appendFile("temp.txt", "2013.07.17 11:14:52 : You are crafting Poma Herb Bulgogi. ");
	parser->processLines();
	appendFile("temp.txt", "2013.07.17 11:15:14 : You have gained 15,210 XP. ");
	appendFile("temp.txt", "2013.07.17 11:15:14 : You have crafted successfully. ");
	appendFile("temp.txt", "2013.07.17 11:15:14 : You have crafted 2 [item:160002341;ver4;;;;]s. ");
	parser->processLines();

	header("Crafting must level up");

	doTest("numCraftingSuccesses", gatheringLog->numCraftingSuccesses, 6);
	doTest("numCraftingFailures", gatheringLog->numCraftingFailures, 1);	
	doTest("numCraftingCancellations", gatheringLog->numCraftingCancellations, 0);
	doTest("numCraftingProcs", gatheringLog->numCraftingProcs, 2);
	doTest("gatherLevelUps.size()", gatheringLog->gatherLevelUps.size(), 0);
	doTest("craftLevelUps.size()", gatheringLog->craftLevelUps.size(), 3);
	doTest("gatheringRecord.size()", gatheringLog->gatheringRecord.size(), 0);
	doTest("craftingRecord.size()", gatheringLog->craftingRecord.size(), 3);
	doTest("craftingRecord[1].name", gatheringLog->craftingRecord[1].name, "Poma Herb Bulgogi");
	doTest("craftingRecord[2].name", gatheringLog->craftingRecord[2].name, "Tasty Poma Herb Bulgogi");
	doTest("craftingRecord[1].successes", gatheringLog->craftingRecord[1].successes, 1);
	doTest("craftingRecord[2].successes", gatheringLog->craftingRecord[2].successes, 2);
	doTest("numCraftedSinceLevelUp", gatheringLog->numCraftedSinceLevelUp, 3);
	doTest("currentlyCrafting", gatheringLog->currentlyCrafting, false);

	appendFile("temp.txt", "2013.07.17 11:14:52 : You are crafting Poma Herb Bulgogi. ");
	parser->processLines();
	appendFile("temp.txt", "2013.11.07 19:22:15 : You must level up to raise your skill level. ");
	appendFile("temp.txt", "2013.07.17 11:15:14 : You have gained 15,210 XP. ");
	appendFile("temp.txt", "2013.07.17 11:15:14 : You have crafted 2 [item:160002341;ver4;;;;]s. ");
	appendFile("temp.txt", "2013.07.17 11:15:14 : You have crafted successfully. ");
	parser->processLines();
		
	doTest("numCraftedSinceLevelUp", gatheringLog->numCraftedSinceLevelUp, 3);
	doTest("isLevelCapped", gatheringLog->isLevelCapped, false);

	//================================================================================

	header("Morphing");

	appendFile("temp.txt", "2013.07.17 11:08:54 : You are crafting Ralloc. ");
	parser->processLines();
	appendFile("temp.txt", "2013.07.17 11:08:58 : You have crafted 3 [item:152000063;ver4;;;;]s. ");
	appendFile("temp.txt", "2013.07.17 11:08:58 : You are crafting Ralloc. ");
	parser->processLines();
	appendFile("temp.txt", "2013.07.17 11:09:02 : You have crafted 3 [item:152000063;ver4;;;;]s. ");
	appendFile("temp.txt", "2013.07.17 11:09:03 : You are crafting Ralloc. ");
	parser->processLines();
	appendFile("temp.txt", "2013.07.17 11:09:07 : You have crafted 3 [item:152000063;ver4;;;;]s. ");
	appendFile("temp.txt", "2013.07.17 11:09:07 : You are crafting Ralloc. ");
	parser->processLines();
	appendFile("temp.txt", "2013.07.17 11:09:11 : You have crafted 3 [item:152000063;ver4;;;;]s. ");
	appendFile("temp.txt", "2013.07.17 11:09:11 : You are crafting Ralloc. ");
	parser->processLines();
	appendFile("temp.txt", "2013.07.17 11:09:15 : You have crafted 3 [item:152000063;ver4;;;;]s. ");
	appendFile("temp.txt", "2013.07.17 11:09:30 : You are crafting Poma. ");
	parser->processLines();
	appendFile("temp.txt", "2013.07.17 11:09:32 : [3.LFG] [charname:Warriorshope;1.0000 0.6941 0.6941]: [cmd:I5TkwvMYr3oc6YJA/ObCXTb2GdZUKHpN86QMGLLtkLpFUYOZnylZ5HCClET+4/tC3z5OcAJxAZjPdHgvpGz8Rg==]Adma Need All ");
	appendFile("temp.txt", "2013.07.17 11:09:33 : You have crafted 3 [item:152001055;ver4;;;;]s. ");
	appendFile("temp.txt", "2013.07.17 11:09:34 : You are crafting Poma. ");
	parser->processLines();
	appendFile("temp.txt", "2013.07.17 11:09:38 : You have crafted 3 [item:152001055;ver4;;;;]s. ");
	parser->processLines();

	doTest("currentlyCrafting", gatheringLog->currentlyCrafting, false);

	appendFile("temp.txt", "2013.07.17 11:09:38 : You are crafting Poma. ");
	parser->processLines();
	appendFile("temp.txt", "2013.07.21 12:41:59 : You stopped crafting.");
	parser->processLines();

	doTest("numCraftingSuccesses", gatheringLog->numCraftingSuccesses, 14);
	doTest("numCraftingFailures", gatheringLog->numCraftingFailures, 1);	
	doTest("numCraftingCancellations", gatheringLog->numCraftingCancellations, 1);
	doTest("getCraftSuccessRate()", gatheringLog->getCraftSuccessRate(), (float)14 * 100 / 16);
	doTest("getCraftFailureRate()", gatheringLog->getCraftFailureRate(), (float)1 * 100 / 16);
	doTest("getCraftCancellationRate()", gatheringLog->getCraftCancellationRate(), (float)1 * 100 / 16);
	doTest("getCraftProcRate()", gatheringLog->getCraftProcRate(), (float) 2 * 100 / 14);
	doTest("craftingRecord[4].cancellations", gatheringLog->craftingRecord[4].cancellations, 1);
	doTest("numCraftingProcs", gatheringLog->numCraftingProcs, 2);
	doTest("gatherLevelUps.size()", gatheringLog->gatherLevelUps.size(), 0);
	doTest("craftLevelUps.size()", gatheringLog->craftLevelUps.size(), 3);
	doTest("numCraftedSinceLevelUp", gatheringLog->numCraftedSinceLevelUp, 3);
	doTest("currentlyCrafting", gatheringLog->currentlyCrafting, false);

	header("Inventory full");

	appendFile("temp.txt", "2013.11.08 00:32:23 : You must have at least one free space in your cube to craft. ");
	appendFile("temp.txt", "2013.11.08 00:32:23 : You stopped crafting. ");
	parser->processLines();

	doTest("numCraftingCancellations", gatheringLog->numCraftingCancellations, 1);
	doTest("getCraftCancellationRate()", gatheringLog->getCraftCancellationRate(), (float)1 * 100 / 16);
	doTest("craftingRecord[4].cancellations", gatheringLog->craftingRecord[4].cancellations, 1);

	//================================================================================

	printSummary();
	delete(parser);
	remove("temp.txt");

	getchar();
	return 0;
}