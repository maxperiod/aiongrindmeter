//#include "../../wxaionexp/ExpHourCalc.h"
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

	//ExpHourCalc *failtest = new ExpHourCalc("sldfkjslkdfj");
	//doTest("ExpHourCalc init failtest", failtest->isOK, false);


	//ExpHourCalc *expHourCalc = new ExpHourCalc("temp.txt");
	//doTest("ExpHourCalc init expHourCalc", expHourCalc->isOK, true);

	doTest("Level 1 exp", expHourCalc->getExpChartEntry(1), 400);
	doTest("Level 65 exp", expHourCalc->getExpChartEntry(65), 584561235);

	//================================================================================

	header("XP / AP Gain");

	expHourCalc->start(-1, -1, -1);

	appendFile("temp.txt", "2013.06.27 23:35:36 : Critical Hit!You inflicted 944 damage on Wori by using Righteous Punishment I. ");
	appendFile("temp.txt", "2013.06.27 23:35:36 : You have gained 1,008 Abyss Points. ");
	appendFile("temp.txt", "2013.06.27 23:35:36 : You have gained 8,867 XP from Wori. ");
	appendFile("temp.txt", "2013.06.27 23:35:36 : You have defeated Wori. ");
	appendFile("temp.txt", "2013.06.27 23:35:36 : Invalid target. ");

	parser->processLines();

	cout << endl << "No level, xp, or ap input" << endl;
	doTest("exp: ", expHourCalc->expGained, 8867);
	//doTest("formatted exp display", expHour

	cout << endl << "XP + AP gain" << endl;
	doTest("XP: ", expHourCalc->expGained, 8867);
	doTest("AP: ", expHourCalc->apGained, 1008);
	doTest("last tick XP", expHourCalc->lastExpPacket, 8867);
	doTest("last tick AP", expHourCalc->lastApPacket, 1008);
	doTest("lastTickHasChanges is true", expHourCalc->lastTickHasChanges, true);
	doTest("numExpPacketsOnLastChange", expHourCalc->numExpPacketsOnLastChange, 1);
	doTest("numApPacketsOnLastChange", expHourCalc->numApPacketsOnLastChange, 1);
	doTest("currentExp", expHourCalc->currentExp, -1);
	doTest("currentAp", expHourCalc->currentExp, -1);
	doTest("getLastExpPacketPercent", expHourCalc->getLastExpPacketPercent(), 0);
	doTest("getLastApPacketPercent", expHourCalc->getLastApPacketPercent(), 0);
	doTest("getExpChartEntry", expHourCalc->getExpChartEntry(expHourCalc->level), -1);
	doTest("getNextRankAp", expHourCalc->getNextRankAp(), -1);

	cout << endl << "Quest EXP with repose" << endl;

	appendFile("temp.txt", "2013.06.27 22:17:33 : Roadhouse recovered 183 MP due to the effect of Strong Instant Recovery. ");
	appendFile("temp.txt", "2013.06.27 22:17:34 : You have gained 20,052,999 XP from Vard (Energy of Repose 10,405). ");
	appendFile("temp.txt", "2013.06.27 22:17:34 : Quest complete: Kata-where? ");
	appendFile("temp.txt", "2013.06.27 22:17:34 : Quest updated: For the Dead ");

	parser->processLines();
	
	doTest("exp gained: ", expHourCalc->expGained, 20052999 + 8867);
	doTest("repose consumed: ", expHourCalc->reposeExp, 10405);
	doTest("currentExp", expHourCalc->currentExp, -1);
	doTest("getLastExpPacketPercent", expHourCalc->getLastExpPacketPercent(), 0);

	cout << endl << "Strong repose" << endl;

	expHourCalc->reset();

	appendFile("temp.txt", "2013.06.27 22:17:34 : You have gained 200,000 XP from Vard (Strong Energy of Repose 100,000). ");
	
	parser->processLines();

	doTest("Strong exp gained: ", expHourCalc->expGained, 200000);
	doTest("Strong repose consumed: ", expHourCalc->reposeExp, 100000);



	//================================================================================

	header("Repose + salvation");

	expHourCalc->reset();

	expHourCalc->level = 20;
	expHourCalc->expGained = 5000;
	expHourCalc->currentExp = 12000;

	appendFile("temp.txt", "2013.06.26 22:05:44 : You have gained 15,411 XP from Studio Butler (Energy of Repose 3,626, Energy of Salvation 2,719).");
	
	parser->processLines();

	doTest("current exp: ", expHourCalc->currentExp, 27411);
	doTest("exp gained: ", expHourCalc->expGained, 20411);
	doTest("repose consumed: ", expHourCalc->reposeExp, 3626);
	doTest("salvation consumed: ", expHourCalc->salvationExp, 2719);
	doTest("lastTickHasChanges is true", expHourCalc->lastTickHasChanges, true);
	doTest("numExpPacketsOnLastChange", expHourCalc->numExpPacketsOnLastChange, 1);
	doTest("numApPacketsOnLastChange", expHourCalc->numApPacketsOnLastChange, 0);

	expHourCalc->reset();

	cout << endl << "Strong Repose + salvation" << endl;

	appendFile("temp.txt", "2013.06.26 22:05:44 : You have gained 23,000 XP from Studio Butler (Strong Energy of Repose 10,000, Energy of Salvation 3,000).");

	parser->processLines();

	doTest("exp gained: ", expHourCalc->expGained, 23000);
	doTest("strong repose consumed: ", expHourCalc->reposeExp, 10000);
	doTest("salvation consumed: ", expHourCalc->salvationExp, 3000);

	expHourCalc->reset();

	cout << endl << "Salvation only" << endl;

	appendFile("temp.txt", "2013.06.26 22:05:44 : You have gained 13.000.000 XP from s u p e r c h a r g e d (Energy of Salvation 3.000.000).");

	parser->processLines();

	doTest("exp gained: ", expHourCalc->expGained, 13000000);
	doTest("salvation consumed: ", expHourCalc->salvationExp, 3000000);

	appendFile("temp.txt", "2013.06.26 22:05:44 : You have gained 6666 XP from fucking piece of shit (Energy of Salvation 666).");

	parser->processLines();

	doTest("Additional salvation consumed: ", expHourCalc->salvationExp, 3000000 + 666);

	//================================================================================

	expHourCalc->reset();

	header("With level and starting exp, gathering");

	expHourCalc->level = 20;
	expHourCalc->currentExp = 12000;

	appendFile("temp.txt", "2013.07.29 23:55:28 : You have started gathering Ancient Aether.");
	appendFile("temp.txt", "2013.07.02 01:25:12 : You have acquired [item:152000916;ver4;;;;]. ");
	appendFile("temp.txt", "2013.07.02 01:25:12 : You have gained 7,580 XP. ");
	appendFile("temp.txt", "2013.07.02 01:25:12 : You have gained experience from gathering. ");
	appendFile("temp.txt", "2013.07.02 01:25:12 : You have started gathering Pure Ancient Aether. ");
	
	parser->processLines();

	doTest("new exp value: ", expHourCalc->currentExp, 19580);
	doTest("new exp gained: ", expHourCalc->expGained, 7580);

	expHourCalc->reset();

	header("Level up exp rollover");
	
	expHourCalc->level = 5;
	expHourCalc->currentExp = 7000;

	appendFile("temp.txt", "2013.06.27 22:17:34 : You have gained 2,000 XP from Vard.");

	parser->processLines();

	doTest("char exp", expHourCalc->currentExp, 7000 + 2000 - 8601);
	doTest("total exp gained", expHourCalc->expGained, 2000);
	doTest("char lvl", expHourCalc->level, 6);

	//================================================================================

	header("Pre ascension exp waste");

	expHourCalc->reset();

	expHourCalc->level = 9;
	expHourCalc->currentExp = 10000;

	appendFile("temp.txt", "2013.06.28 09:42:49 : Quest updated: Ascension ");
	appendFile("temp.txt", "2013.06.28 09:42:49 : You have learned the Essencetapping skill. ");
	appendFile("temp.txt", "2013.06.28 09:42:49 : You have learned the Morph Substances skill. ");
	appendFile("temp.txt", "2013.06.28 09:42:49 : You have learned [recipe_ex:155005001;DeleteAfterAscen-IS]. ");
	appendFile("temp.txt", "2013.06.28 09:42:49 : You have learned [recipe_ex:155005002;DeleteAfterAscen-IS]. ");
	appendFile("temp.txt", "2013.06.28 09:42:49 : You have learned [recipe_ex:155005005;DeleteAfterAscen-IS]. ");
	appendFile("temp.txt", "2013.06.28 09:42:49 : You have learned the Aethertapping skill. ");
	appendFile("temp.txt", "2013.06.28 09:42:50 : [3.LFG] [charname:Onimushaz-SL;1.0000 0.6941 0.6941]: [cmd:rGSlNwGJGRxRQv03cJhj8zmbH1pS5sI2+Ojm4GyCo/tFUYOZnylZ5HCClET+4/tCS7qtaOGT6oZDfpuNO+D18g==]Adma Rush Need Cleric at Lannok  ");
	appendFile("temp.txt", "2013.06.28 09:42:57 : [3.LFG] [charname:Draizon-KR;1.0000 0.6941 0.6941]: [cmd:ZuRJ77suA3HGXknXXvlwhpPM8QnGQsOkmk/KeMfcfBdFUYOZnylZ5HCClET+4/tC4UL+Ir0PulB5jOt1gqsgzQ==]NTC need all! ");
	appendFile("temp.txt", "2013.06.28 09:43:01 : [3.LFG] [charname:Demolize-TM;1.0000 0.6941 0.6941]: [cmd:P4LwuGgTZY+ycKKEACMJvuAyWLtXF0rdZGbvQ8Z9+DdFUYOZnylZ5HCClET+4/tCg5pior9yCPYe0vyEXekmgw==]?BT?NEED ALL 59+ ?? Hard Mode ");
	appendFile("temp.txt", "2013.06.28 09:43:04 : You have gained 73,200 XP from Munin. ");
	appendFile("temp.txt", "2013.06.28 09:43:04 : You can advance to level 10 only after you have completed the class change quest. ");

	parser->processLines();
	
	doTest("char exp", expHourCalc->currentExp, 43087);	
	doTest("char level", expHourCalc->level, 9);
	doTest("exp gained", expHourCalc->expGained, 33087);

	expHourCalc->currentExp = 43087;

	appendFile("temp.txt", "2013.06.27 22:17:34 : You have gained 2,000 XP from Vard.");
	appendFile("temp.txt", "2013.06.27 09:43:04 : You can advance to level 10 only after you have completed the class change quest. ");

	parser->processLines();

	doTest("char exp", expHourCalc->currentExp, 43087);
	doTest("char level", expHourCalc->level, 9);

	cout << endl << "Ascended" << endl;

	appendFile("temp.txt", "2013.06.27 22:17:34 : You have gained 2,000 XP from Vard.");

	parser->processLines();

	doTest("char exp", expHourCalc->currentExp, 2000);
	doTest("char level", expHourCalc->level, 10);

	//================================================================================

	header("Fast Track Server level cap exp waste");

	expHourCalc->reset();

	expHourCalc->level = 55;
	expHourCalc->currentExp = 103225345;

	appendFile("temp.txt", "2013.09.23 22:26:04 : You have used Inggison Illusion Fortress Scroll. ");
	appendFile("temp.txt", "2013.09.23 22:26:13 : aasfer-IS was affected by its own Aion's Favor I. ");
	appendFile("temp.txt", "2013.09.23 22:26:15 : Quest updated: [Coin] For the Scholars ");
	appendFile("temp.txt", "2013.09.23 22:26:20 : You have acquired 5 [item:186000018;ver4;;;;]s and stored them in your special cube. ");
	appendFile("temp.txt", "2013.09.23 22:26:20 : You have gained 4,186,683 XP from Eduardo. ");
	appendFile("temp.txt", "2013.09.23 22:26:20 : You cannot be Level 56 on the Fast-Track Server. ");
	appendFile("temp.txt", "2013.09.23 22:26:20 : Quest complete: [Coin] For the Scholars ");

	parser->processLines();
	
	doTest("char exp", expHourCalc->currentExp, 104225345);	
	doTest("char level", expHourCalc->level, 55);
	doTest("exp gained", expHourCalc->expGained, 1000000);


	//================================================================================

	header("Level cap exp waste");

	expHourCalc->reset();
	
	expHourCalc->level = 65;
	expHourCalc->currentExp = 10000000;

	appendFile("temp.txt", "2013.06.27 22:17:34 : You have gained 20,052,999 XP from Vard (Energy of Repose 10,405). ");
	
	parser->processLines();

	doTest("char exp", expHourCalc->currentExp, 30052999);
	doTest("exp gained", expHourCalc->expGained, 20052999);
	doTest("last exp packet", expHourCalc->lastExpPacket, 20052999);
	doTest("char level", expHourCalc->level, 65);
	doTest("repose consumed", expHourCalc->reposeExp, 10405);

	expHourCalc->reset();
	
	expHourCalc->level = 65;
	expHourCalc->currentExp = 584561235;

	appendFile("temp.txt", "2013.06.27 22:17:34 : You have gained 20,052,999 XP from Vard (Energy of Repose 10,405). ");
	
	parser->processLines();

	
	doTest("char exp", expHourCalc->currentExp, 584561235);
	doTest("exp gained", expHourCalc->expGained, 0);
	doTest("last exp packet", expHourCalc->lastExpPacket, 20052999);
	doTest("char level", expHourCalc->level, 65);
	doTest("repose consumed", expHourCalc->reposeExp, 10405);

	//================================================================================

	header("Soul Healing / EXP loss on death");

	expHourCalc->reset();
	
	//lv 13
	//61581 xp
	//die
	//58595
	//551 zeny
	//gain 2171
	//60766 xp

	//60766
	//57510
	//59681

	//lv 43
	//21,016,061
	//die
	//20,648,891
	//18022 zeny
	//gain 244780
	//20,893,671

	cout << "lv 13 exp 61851" << endl;

	expHourCalc->level = 13;
	expHourCalc->currentExp = 61851;

	appendFile("temp.txt","2013.06.27 23:03:19 : You are no longer bleeding. ");
	appendFile("temp.txt","2013.06.27 23:03:19 : You have died. ");

	parser->processLines();

	doTest("Died to a monster, most likely XP lost, needExpUpdate is true", expHourCalc->needExpUpdate, true);
	doTest("needApUpdate is false unless there was no XP loss", expHourCalc->needApUpdate, false);

	appendFile("temp.txt", "2013.07.04 18:15:04 : You spent 551 Kinah.");
	appendFile("temp.txt", "2013.07.04 18:15:04 : You have gained 2,171 XP. ");
	appendFile("temp.txt", "2013.07.04 18:15:04 : You received Soul Healing. ");

	parser->processLines();

	doTest("exp change:", expHourCalc->lastExpPacket, -1085);
	doTest("exp after:", expHourCalc->currentExp, 60766);
	doTest("zeny spent:", expHourCalc->cashSpent, 551);
	doTest("last zeny transaction:", expHourCalc->lastCashTransaction, -551);
	doTest("Soul healing done, needExpUpdate is false", expHourCalc->needExpUpdate, false);
	doTest("lastTickHasChanges is true", expHourCalc->lastTickHasChanges, true);
	doTest("expLostToDeaths", expHourCalc->expLostToDeaths, 1085 + 2171);

	expHourCalc->reset();

	cout << "lv 43 exp 21016061" << endl;

	expHourCalc->level = 43;
	expHourCalc->currentExp = 21016061;

	appendFile("temp.txt","2013.06.27 23:03:19 : You have died. ");
	appendFile("temp.txt", "2013.07.04 18:40:23 : You spent 18,022 Kinah. ");
	appendFile("temp.txt", "2013.07.04 18:40:23 : You have gained 244,780 XP. ");
	appendFile("temp.txt", "2013.07.04 18:40:23 : You received Soul Healing.");

	parser->processLines();

	doTest("exp change:", expHourCalc->lastExpPacket, -122390);
	doTest("exp gained so far:", expHourCalc->expGained, -122390);
	doTest("exp after:", expHourCalc->currentExp, 20893671);
	doTest("zeny spent:", expHourCalc->cashSpent, 18022);
	doTest("last zeny transaction:", expHourCalc->lastCashTransaction, -18022);

	appendFile("temp.txt","2013.06.27 23:03:19 : You have died. ");
	appendFile("temp.txt", "2013.07.04 18:40:23 : You spent 18,022 Kinah. ");
	appendFile("temp.txt", "2013.07.04 18:40:23 : You have gained 244,780 XP. ");
	appendFile("temp.txt", "2013.07.04 18:40:23 : You received Soul Healing.");

	parser->processLines();

	doTest("expLostToDeaths after 2 deaths", expHourCalc->expLostToDeaths, (244780 + 122390) * 2);
	doTest("exp gained so far:", expHourCalc->expGained, -244780);
	doTest("currentExp:", expHourCalc->currentExp, 20893671 - 122390);

	//================================================================================

	header("1 zeny soul healing -> PKed");

	expHourCalc->reset();

	expHourCalc->level = 43;
	expHourCalc->currentExp = 21016061;

	appendFile("temp.txt","2013.06.27 23:03:19 : You have died. ");
	appendFile("temp.txt","2013.07.05 00:54:59 : Saamn recovered 183 MP due to the effect of Strong Instant Recovery. ");
	appendFile("temp.txt","2013.07.05 00:54:59 : You have resurrected. ");
	appendFile("temp.txt","2013.07.05 00:55:02 : [3.LFG] [charname:ImSoBucci;1.0000 0.6941 0.6941]: [cmd:0cWaGV/kjHuy7eO6sQkkLIOFT2cFnzucw1Y29SlJmwZFUYOZnylZ5HCClET+4/tCGl2bZjvYqe8X4QPegOqKKQ==]BTHM LF DPS,TANK,HEALS ");
	appendFile("temp.txt","2013.07.05 00:55:04 : Demonjon restored 1,940 HP. ");
	appendFile("temp.txt","2013.07.05 00:55:04 : Demonjon restored 357 MP. ");
	appendFile("temp.txt","2013.07.05 00:55:09 : You spent 1 Kinah. ");
	appendFile("temp.txt","2013.07.05 00:55:09 : You received Soul Healing. ");
	appendFile("temp.txt","2013.07.05 00:55:11 : The weapon has been changed. ");

	parser->processLines();

	doTest("PK soul healing no exp loss check:", expHourCalc->currentExp, 21016061);

	//================================================================================

	header("Clear needExpUpdate if no XP to recover");

	expHourCalc->reset();
	expHourCalc->level = 44;
	expHourCalc->currentExp = 10000000;
	expHourCalc->expGained = 480752;

	appendFile("temp.txt","2013.07.15 18:24:31 : You can see again ");
	appendFile("temp.txt","2013.07.15 18:24:31 : You have died. ");
	appendFile("temp.txt","2013.07.15 16:42:31 : You have resurrected. ");
	appendFile("temp.txt","2013.07.13 17:11:07 : You do not have any XP to recover. ");

	doTest("needExpUpdate", expHourCalc->needExpUpdate, false);
	doTest("needApUpdate", expHourCalc->needApUpdate, false);

	//================================================================================

	header("Manual exp update - pve death");

	expHourCalc->reset();
	expHourCalc->level = 44;
	expHourCalc->currentExp = 10000000;
	expHourCalc->expGained = 480752;

	appendFile("temp.txt","2013.06.27 20:21:33 : You cannot do that while you are in combat.  ");
	appendFile("temp.txt","2013.06.27 20:21:33 : You have died.  ");
	appendFile("temp.txt","2013.06.27 20:21:49 : You have resurrected.  ");
	appendFile("temp.txt","2013.06.27 20:21:49 : You cannot attack the enemy faction in this region.  ");
	appendFile("temp.txt","2013.06.27 20:22:00 : Suder inflicted 4,192 damage on Training Dummy by using Ritual Push I.  ");
	
	parser->processLines();	

	expHourCalc->updateExp(10000000 - 380752);
	parser->processLines();	

	doTest("currentExp", expHourCalc->currentExp, 10000000 - 380752);
	doTest("expGained", expHourCalc->expGained, 100000);
	doTest("lastExpPacket", expHourCalc->lastExpPacket, -380752);
	doTest("needExpUpdate", expHourCalc->needExpUpdate, false);
	doTest("expLostToDeaths", expHourCalc->expLostToDeaths, 380752);

	appendFile("temp.txt","2013.06.27 20:22:02 : You spent 28,259 Kinah.  ");
	appendFile("temp.txt","2013.06.27 20:22:02 : You have gained 719,902 XP.  ");
	appendFile("temp.txt","2013.06.27 20:22:02 : You received Soul Healing.  ");

	parser->processLines();

	doTest("soul heal after manual exp update: currentExp", expHourCalc->currentExp, 10000000 - 380752 + 719902);
	doTest("needExpUpdate is false", expHourCalc->needExpUpdate, false);
	doTest("needApUpdate is false", expHourCalc->needApUpdate, false);
	doTest("lastCashTransaction", expHourCalc->lastCashTransaction, -28259);
	doTest("cashSpent", expHourCalc->cashSpent, 28259);
	doTest("expLostToDeaths", expHourCalc->expLostToDeaths, 380752);

	

	//================================================================================

	header("Abyss Rank");

	expHourCalc->currentAp = 1000;

	doTest("9 kyu test", expHourCalc->getAbyssRankName(), "9 kyu");

	expHourCalc->currentAp = 120000;

	doTest("2 kyu test", expHourCalc->getAbyssRankName(), "2 kyu");

	expHourCalc->currentAp = 200000;

	doTest("200000 AP test", expHourCalc->getAbyssRankName(), "???");

	expHourCalc->currentAp = 2000000000;

	doTest("2 billion AP test", expHourCalc->getAbyssRankName(), "???");

	//================================================================================

	header("AP Spending");

	expHourCalc->reset();
	expHourCalc->currentAp = 95000;
	expHourCalc->apGained = 95000;
	expHourCalc->lastApPacket = 95000;

	appendFile("temp.txt","2013.07.03 18:15:39 : Your Abyss Rank has changed to Soldier, Rank 7. ");
	appendFile("temp.txt","2013.07.03 18:15:39 : You used 89,775 Abyss Points. ");
	appendFile("temp.txt","2013.07.03 18:15:40 : [3.LFG] [charname:Vladarina;1.0000 0.6941 0.6941]: Asmos, we expect a LOT of elyos to attack [pos:Pradeth;600060000 2676.0 2720.2 0.0 0] tonight. I need everybody (even level 50s) I can get inside of that fort EARLY, before 11 pm est vuln (5 hours). Bind  ");
	appendFile("temp.txt","2013.07.03 18:15:40 : You have purchased [item:140000816;ver4;;;;]. ");

	parser->processLines();

	doTest("AP spent ", expHourCalc->apSpent, 89775);
	doTest("AP after purchase", expHourCalc->currentAp, 5225);
	doTest("AP gained after purchase", expHourCalc->apGained, 5225);		
	doTest("last AP Packet", expHourCalc->lastApPacket, -89775);
	doTest("lastTickHasChanges is true", expHourCalc->lastTickHasChanges, true);

	//================================================================================


	header("Got PKed, need to ask for manual AP update");

	expHourCalc->reset();
	expHourCalc->currentAp = 100000;

	appendFile("temp.txt","2013.07.05 16:15:18 : Tip: Elyos and Asmodians cannot fight one another in a neutral zone.");
	appendFile("temp.txt","2013.07.05 16:15:18 : You may be unable to use certain skills or items in this area. ");
	appendFile("temp.txt","2013.07.05 16:15:18 : A survey has arrived. Click the icon to open the survey window. ");
	appendFile("temp.txt","2013.07.05 16:15:20 : You have joined Standard Server. ");
	appendFile("temp.txt","2013.07.07 00:56:26 : You are no longer silenced.  ");
	appendFile("temp.txt","2013.07.07 00:56:26 : Your movement speed is restored to normal.  ");
	appendFile("temp.txt","2013.07.07 00:56:26 : Your attack speed is restored to normal.  ");
	appendFile("temp.txt","2013.07.07 00:56:26 : You were killed by Thomasbangalter's attack.  ");
	appendFile("temp.txt","2013.07.07 00:56:28 : Noble Energy inflicted 684 damage on Thomasbangalter by using Noble Energy IV.  ");
	appendFile("temp.txt","2013.07.07 00:56:28 : Thomasbangalter inflicted 733 damage on Devios by using Illusion Storm VII.  ");

	parser->processLines();

	doTest("I'm on Standard Server", expHourCalc->getCurrentServer(), "Standard");
	doTest("Got PKed in standard server, need ap update yes", expHourCalc->needApUpdate, true);
	doTest("needExpUpdate needs to be false", expHourCalc->needExpUpdate, false);

	expHourCalc->updateAp(95000);
	appendFile("temp.txt","2013.06.27 23:03:26 : You have resurrected. ");
	appendFile("temp.txt","2013.06.27 23:03:52 : You spent 1 Kinah. ");
	appendFile("temp.txt","2013.06.27 23:03:52 : You received Soul Healing. ");

	parser->processLines();

	doTest("already updated AP, don't apupdate again", expHourCalc->needApUpdate, false);

	appendFile("temp.txt","2013.07.07 00:56:26 : You were killed by Sogyawie's attack.  ");
	appendFile("temp.txt","2013.06.27 23:03:26 : You have resurrected. ");
	appendFile("temp.txt","2013.06.27 23:03:52 : You spent 1 Kinah. ");
	appendFile("temp.txt","2013.06.27 23:03:52 : You received Soul Healing. ");

	parser->processLines();

	doTest("Got PKed, didn't update AP, soul healed", expHourCalc->needApUpdate, true);

	header("Got killed in structured PvP, no AP loss, don't ask for update");

	expHourCalc->reset();
	appendFile("temp.txt","2013.06.25 14:44:14 : You have item(s) left to settle at the Broker. ");
	appendFile("temp.txt","2013.06.25 14:44:16 : You have joined the group. ");
	appendFile("temp.txt","2013.06.25 14:44:16 : You have joined Instance Server. ");
	appendFile("temp.txt","2013.06.25 14:44:21 : You have joined the Terath Dredgion region channel. ");
	appendFile("temp.txt","2013.06.25 14:44:21 : You have joined the Terath Dredgion trade channel. ");
	appendFile("temp.txt","2013.06.25 14:44:21 : You have joined the LFG Channel. ");
	appendFile("temp.txt","2013.06.25 14:44:23 : Nekoh-IS has joined your group. ");
	appendFile("temp.txt","2013.06.25 14:44:24 : You have joined the Templar Channel. ");
	appendFile("temp.txt","2013.06.27 19:04:58 : You were killed by Mrplatino's attack.");

	parser->processLines();

	doTest("I'm on Instance Server", expHourCalc->getCurrentServer(), "Instance");
	doTest("needApUpdate should be false", expHourCalc->needApUpdate, false);

	header("Got killed in by mobster in structured PvP, manual EXP enter, no EXP or AP loss, don't ask for AP update");

	expHourCalc->reset();
	expHourCalc->level = 60;
	expHourCalc->currentExp = 1234567;
	appendFile("temp.txt","2013.06.25 14:44:14 : You have item(s) left to settle at the Broker. ");
	appendFile("temp.txt","2013.06.25 14:44:16 : You have joined the group. ");
	appendFile("temp.txt","2013.06.25 14:44:16 : You have joined Instance Server. ");
	appendFile("temp.txt","2013.06.25 14:44:21 : You have joined the Terath Dredgion region channel. ");
	appendFile("temp.txt","2013.06.25 14:44:21 : You have joined the Terath Dredgion trade channel. ");
	appendFile("temp.txt","2013.06.25 14:44:21 : You have joined the LFG Channel. ");
	appendFile("temp.txt","2013.06.25 14:44:23 : Nekoh-IS has joined your group. ");
	appendFile("temp.txt","2013.06.25 14:44:24 : You have joined the Templar Channel. ");
	appendFile("temp.txt","2013.06.27 19:04:58 : You have died. ");

	parser->processLines();
	expHourCalc->updateExp(1234567);
	parser->processLines();
	
	doTest("needApUpdate should be false", expHourCalc->needApUpdate, false);
	doTest("lastTickHasChanges is true", expHourCalc->lastTickHasChanges, true);
	doTest("expLostToDeaths", expHourCalc->expLostToDeaths, 0);
	doTest("apLostToPk", expHourCalc->apLostToPk, 0);

	appendFile("temp.txt","2013.07.05 16:15:20 : You have joined Standard Server. ");
	appendFile("temp.txt","2013.06.27 23:03:19 : You are no longer bleeding. ");
	appendFile("temp.txt","2013.06.27 23:03:19 : You have died. ");
	
	parser->processLines();

	header("Back to Standard Server, attacked by enemy faction player, finished blow from monster"); 
	doTest("Don't know whether XP was lost or not - needExpUpdate is true", expHourCalc->needExpUpdate, true);

	appendFile("temp.txt","2013.06.27 23:03:19 : You do not have much flight time left. Please land on a secure place. ");
	appendFile("temp.txt","2013.06.27 23:03:19 : Pashid Offense Elite Fighter is in the boost Physical Def,Magical Defense state because Pashid Offense Elite Fighter used Conqueror's Passion. ");
	appendFile("temp.txt","2013.06.27 23:03:19 : Pashid Offense Elite Protector is in the boost Physical Def,Magical Defense state because Pashid Offense Elite Protector used Conqueror's Passion. ");
	appendFile("temp.txt","2013.06.27 23:03:20 : Pashid Offense Elite Archer is in the boost Physical Def,Magical Defense state because Pashid Offense Elite Archer used Conqueror's Passion. ");
	appendFile("temp.txt","2013.06.27 23:03:20 : Pashid Offense Elite Archer is in the boost Physical Def,Magical Defense state because Pashid Offense Elite Archer used Conqueror's Passion. ");
	appendFile("temp.txt","2013.06.27 23:03:20 : Pashid Offense Elite Archer is in the boost Physical Def,Magical Defense state because Pashid Offense Elite Archer used Conqueror's Passion. ");
	appendFile("temp.txt","2013.06.27 23:03:24 : [charname:Gwc;0.6118 0.9059 0.8627]: gub ");
	appendFile("temp.txt","2013.06.27 23:03:26 : You have resurrected. ");

	appendFile("temp.txt","2013.06.27 23:03:50 : [charname:Mystfang;0.6118 0.9059 0.8627]: omg ");
	appendFile("temp.txt","2013.06.27 23:03:52 : You spent 1 Kinah. ");
	appendFile("temp.txt","2013.06.27 23:03:52 : You received Soul Healing. ");

	parser->processLines();

	doTest("1 zeny soul healing means u lost AP", expHourCalc->needApUpdate, true);
	doTest("No EXP loss when you lost AP", expHourCalc->needExpUpdate, false);
	doTest("Soul healing done, needExpUpdate is false", expHourCalc->needExpUpdate, false);

	expHourCalc->currentExp = 100000;
	expHourCalc->currentAp = 1000000;

	header("Manual XP update, EXP unchanged (no exp loss) = possible AP loss");

	appendFile("temp.txt","2013.06.27 23:03:19 : You are no longer bleeding. ");
	appendFile("temp.txt","2013.06.27 23:03:19 : You have died. ");

	parser->processLines();

	expHourCalc->updateExp(100000);
	parser->processLines();	

	doTest("needApUpdate", expHourCalc->needApUpdate, true);
	doTest("clear needExpUpdate", expHourCalc->needExpUpdate, false);
	doTest("lastTickHasChanges is true", expHourCalc->lastTickHasChanges, true);
	
	expHourCalc->updateAp(999000);
	parser->processLines();	

	doTest("After manual AP update, needExpUpdate false", expHourCalc->needExpUpdate, false);
	doTest("After manual AP update, needApUpdate false", expHourCalc->needApUpdate, false);
	doTest("current exp", expHourCalc->currentExp, 100000);
	doTest("current ap", expHourCalc->currentAp, 999000);
	doTest("last exp packet", expHourCalc->lastExpPacket, 0);
	doTest("last ap packet", expHourCalc->lastApPacket, -1000);
	doTest("expLostToDeaths", expHourCalc->expLostToDeaths, 0);
	doTest("apLostToPk", expHourCalc->apLostToPk, 1000);
	doTest("lastTickHasChanges is true", expHourCalc->lastTickHasChanges, true);

	appendFile("temp.txt","2013.06.27 23:03:52 : You spent 1 Kinah. ");
	appendFile("temp.txt","2013.06.27 23:03:52 : You received Soul Healing. ");
	parser->processLines();
	
	doTest("After manual AP update, soul healed, don't ask for AP update again", expHourCalc->needApUpdate, false);

	//================================================================================

	header("Promopt for AP update due to AP loss on death");

	expHourCalc->reset();
	expHourCalc->currentAp = 95000;
	expHourCalc->apGained = 95000;
	expHourCalc->lastApPacket = 1234;

	appendFile("temp.txt","2013.06.27 19:04:58 : You were killed by Mrplatino's attack.");

	parser->processLines();

	cout << endl << "Invalid update" << endl;

	expHourCalc->updateAp(95001);
	parser->processLines();	
	doTest("currentAp after invalid update", expHourCalc->currentAp, 95000);
	doTest("apGained after invalid update", expHourCalc->apGained, 95000);		
	doTest("lastApPacket after invalid update", expHourCalc->lastApPacket, 1234);
	doTest("apLostToPk after invalid update", expHourCalc->apLostToPk, 0);
	doTest("Still need ap update", expHourCalc->needApUpdate, true);
	doTest("lastTickHasChanges is false", expHourCalc->lastTickHasChanges, false);
	doTest("apLostToPk", expHourCalc->apLostToPk, 0);

	cout << endl << "Valid update" << endl;

	expHourCalc->updateAp(94500);
	parser->processLines();	
	doTest("currentAp after getting PKed", expHourCalc->currentAp, 94500);
	doTest("apGained after getting PKed", expHourCalc->apGained, 94500);		
	doTest("lastApPacket after getting PKed", expHourCalc->lastApPacket, -500);
	doTest("apLostToPk after getting PKed", expHourCalc->apLostToPk, 500);
	doTest("Still need ap update", expHourCalc->needApUpdate, false);
	doTest("lastTickHasChanges is true", expHourCalc->lastTickHasChanges, true);	
	doTest("apLostToPk", expHourCalc->apLostToPk, 500);

	header("Double deaths");

	appendFile("temp.txt","2013.06.27 17:08:23 : You have gained 3,421,093 XP from Lumiden. ");
	appendFile("temp.txt","2013.06.27 17:08:23 : You have gained 402 Abyss Points. ");
	appendFile("temp.txt","2013.06.27 17:08:23 : You can receive the weekly quest again at 9 in the morning on Wednesday. ");
	appendFile("temp.txt","2013.09.05 20:35:58 : You were killed by SteveForansi's attack.");
	parser->processLines();

	expHourCalc->updateAp(93602);
	parser->processLines();
	
	doTest("currentAp after getting PKed for second time", expHourCalc->currentAp, 93602);
	doTest("apGained after getting PKed for second time", expHourCalc->apGained, 93602);
	doTest("lastApPacket after getting PKed  for second time", expHourCalc->lastApPacket, -1300);
	doTest("apLostToPk", expHourCalc->apLostToPk, 1800);
	doTest("Still need ap update", expHourCalc->needApUpdate, false);
	doTest("lastTickHasChanges is true", expHourCalc->lastTickHasChanges, true);	


	cout << endl << "Reject inputs that exceed currentAP + apLostToPk" << endl;

	appendFile("temp.txt","2013.09.05 20:35:58 : You were killed by Vagina's attack.");
	parser->processLines();

	expHourCalc->updateAp(95403);
	parser->processLines();

	doTest("currentAp", expHourCalc->currentAp, 93602);
	doTest("apGained ", expHourCalc->apGained, 93602);	
	doTest("lastApPacket", expHourCalc->lastApPacket, -1300);
	doTest("apLostToPk", expHourCalc->apLostToPk, 1800);
	doTest("Still need ap update", expHourCalc->needApUpdate, true);
	doTest("lastTickHasChanges is true", expHourCalc->lastTickHasChanges, false);	

	expHourCalc->updateAp(95402);
	parser->processLines();

	cout << endl << "Allow manual updates up to currentAP + apLostToPk" << endl;

	doTest("currentAp", expHourCalc->currentAp, 95402);
	doTest("apGained ", expHourCalc->apGained, 95402);
	doTest("lastApPacket", expHourCalc->lastApPacket, 1800);
	doTest("apLostToPk", expHourCalc->apLostToPk, 0);
	doTest("Still need ap update", expHourCalc->needApUpdate, false);
	doTest("lastTickHasChanges is true", expHourCalc->lastTickHasChanges, true);	


	//================================================================================

	header("AP not entered during startup");

	expHourCalc->reset();
	expHourCalc->level = 60;
	expHourCalc->currentExp = 50000000;
	expHourCalc->currentAp = -1;
	expHourCalc->apGained = 95000;
	expHourCalc->lastApPacket = 1234;

	appendFile("temp.txt","2013.06.27 19:04:58 : You were killed by Mrplatino's attack.");

	parser->processLines();

	doTest("Still need ap update", expHourCalc->needApUpdate, false);
	doTest("lastTickHasChanges is false", expHourCalc->lastTickHasChanges, false);
	

	cout << endl << "Attacked by player, finishing blow by monster, soul healing" << endl;

	appendFile("temp.txt","2013.06.27 23:03:19 : You have died. ");

	appendFile("temp.txt","2013.06.27 23:03:52 : You spent 1 Kinah. ");
	appendFile("temp.txt","2013.06.27 23:03:52 : You received Soul Healing. ");

	parser->processLines();

	doTest("Still need ap update", expHourCalc->needApUpdate, false);
	doTest("lastTickHasChanges is false", expHourCalc->lastTickHasChanges, false);

	cout << endl << "Attacked by player, finishing blow by monster, manual exp update" << endl;

	appendFile("temp.txt","2013.06.27 23:03:19 : You have died. ");
	parser->processLines();

	expHourCalc->updateExp(50000000);
	parser->processLines();

	doTest("don't need exp update", expHourCalc->needExpUpdate, false);
	doTest("Still need ap update", expHourCalc->needApUpdate, false);
	doTest("lastTickHasChanges is false", expHourCalc->lastTickHasChanges, true);


	//================================================================================

	header("Blood Marks and AP Relics");

	expHourCalc->reset();

	expHourCalc->currentAp = 10000;
	expHourCalc->apGained = 1000;
	
	appendFile("temp.txt","2013.07.23 12:32:19 : You have acquired [item:186000066;ver4;;;;]. ");
	appendFile("temp.txt","2013.07.23 12:32:19 : You have acquired 2 [item:162000120;ver4;;;;](s). ");
	
	parser->processLines();

	doTest("currentAP after lesser icon", expHourCalc->currentAp, 10000);
	doTest("apGained after lesser icon", expHourCalc->apGained, 1000);
	doTest("relicAp after lesser icon", expHourCalc->relicAp, 315);

	appendFile("temp.txt","2013.07.22 17:19:53 : Quest updated: [Daily] Sweeping Away the Elyos ");
	appendFile("temp.txt","2013.07.22 17:19:54 : You have acquired 12 [item:186000236;ver4;;;;]s and stored them in your special cube. ");
	appendFile("temp.txt","2013.07.22 17:19:54 : You have gained 3,446,516 XP from Hrund. ");
	appendFile("temp.txt","2013.07.22 17:19:54 : You can receive the weekly quest again at 9 in the morning on Wednesday. ");
	appendFile("temp.txt","2013.07.22 17:19:54 : Quest complete: [Daily] Sweeping Away the Elyos ");

	parser->processLines();

	doTest("relicAp after 12 blood mark", expHourCalc->relicAp, 6413);

	//================================================================================

	header("Join Channel");

	appendFile("temp.txt","2013.07.24 15:28:52 : You have joined the Poeta region channel. ");
	appendFile("temp.txt","2013.07.24 15:28:52 : You have joined the Poeta trade channel. ");
	appendFile("temp.txt","2013.07.24 15:28:52 : You have joined the LFG Channel. ");
	appendFile("temp.txt","2013.07.24 15:28:55 : You have joined the Assassin Channel. ");
	appendFile("temp.txt","2013.07.24 15:28:55 : You have joined the Ranger Channel. ");
	appendFile("temp.txt","2013.06.25 14:44:16 : You have joined Instance Server.");

	parser->processLines();
	doTest("lastTickHasChanges is false", expHourCalc->lastTickHasChanges, false);

	//================================================================================

	header("Do not recognize user chat as commands");

	expHourCalc->reset();

	expHourCalc->level = 43;
	expHourCalc->currentExp = 21016061;
	expHourCalc->lastExpPacket = 10000;
	expHourCalc->lastCashTransaction = 62351;

	appendFile("temp.txt","2013.07.24 15:24:51 : [3.LFG] [charname:Eikwel;1.0000 0.6941 0.6941]: blah blah blah : You received Soul Healing.");

	parser->processLines();

	doTest("Soul healing from chat", expHourCalc->currentExp, 21016061);
	doTest("Soul healing from chat", expHourCalc->lastExpPacket, 10000);
	doTest("lastTickHasChanges is false", expHourCalc->lastTickHasChanges, false);

	//================================================================================
	printSummary();
	delete(parser);
	remove("temp.txt");

	getchar();
	return 0;
}