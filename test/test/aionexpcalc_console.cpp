#include "../../wxaionexp/ExpHourCalc.h"
#include "windows.h"

int main(int argc, char* argv[]){

	ExpHourCalc expHourCalc("Chat.log");
	if (!expHourCalc.isOK) cout << "UNABLE TO OPEN CHAT.LOG" << endl;

	int level = 0, startExp = 0, startAp = 0;

	for (int i = 1; i < 65; i ++) cout << i << ": " << expHourCalc.getExpChartEntry(i) << endl;

	cout << "What's your character level?" << endl;
	cin >> level;
	cout << "You are level " << level << endl;
	
	if (level > 0){
		cout << "What's your current EXP?" << endl;
		cin >> startExp;
		
	}
	cout << "What's your current AP?" << endl;
	cin >> startAp;

	expHourCalc.reset();

	expHourCalc.level = level;
	expHourCalc.currentExp = startExp;
	expHourCalc.currentAp = startAp;


	expHourCalc.start();

	while(true){
		expHourCalc.processLines();
		system("cls");
		cout << expHourCalc.getElapsedTime() << endl;

		if (expHourCalc.needApUpdate){
			int newAP;
			cout << "What's your current AP?" << endl;
			cin >> newAP;
			if (newAP <= expHourCalc.currentAp) expHourCalc.updateAp(newAP);
			system("cls");
		}


		if (level > 0){
			cout << "Level: " << expHourCalc.level << endl;
			cout << "EXP: " << expHourCalc.currentExp << " / " << expHourCalc.getExpChartEntry(expHourCalc.level)
				<< "(" << expHourCalc.getExpPercent() << "%) ";		
		}
		if (expHourCalc.lastExpPacket > 0) cout << "+";
		cout << expHourCalc.lastExpPacket;
		if (level > 0) {
			cout << "(" << expHourCalc.getLastExpPacketPercent() << "%)";
		}
		cout << endl; 

		cout << "Exp gained: " << expHourCalc.expGained << " XP" << endl;
		

		cout << "Repose consumed: " << expHourCalc.reposeExp << endl;
		cout << "Salvation consumed: " << expHourCalc.salvationExp << endl;
		
		cout << endl;

		
		
		cout << "Exp/hr: " << expHourCalc.getExpPerHour() << endl; 
	
		cout << endl;
		if (startAp > 0){
			cout << "Abyss Rank: " << expHourCalc.getAbyssRankName() << endl;
			cout << "AP: " << expHourCalc.currentAp; 
			cout << " / " << expHourCalc.getNextRankAp() << " (" << expHourCalc.getApPercent() << "%)" << endl;
		}
		cout << "AP gained: " << expHourCalc.apGained << ' ' << endl;
		if (expHourCalc.lastApPacket >= 0) cout << '+';
		cout << expHourCalc.lastApPacket << endl;
		cout << endl;
		cout << "AP/hr: " << expHourCalc.getApPerHour() << endl;
		cout << endl;
		cout << "AP value of items gained: " << expHourCalc.relicAp << " (+" << expHourCalc.lastRelicApPacket << ")" << endl;

		cout << endl;
		cout << "Cash flow in: " << expHourCalc.cashGained;
		if (expHourCalc.lastCashTransaction > 0) cout << " (+" << expHourCalc.lastCashTransaction << ")";
		cout << endl;
		cout << "Cash flow out: " << expHourCalc.cashSpent;
		if (expHourCalc.lastCashTransaction < 0) cout << " (" << expHourCalc.lastCashTransaction << ")";
		cout << endl;
		cout << "Net cash flow: " << expHourCalc.cashGained - expHourCalc.cashSpent << endl;

		Sleep(1000);
		
	}
}