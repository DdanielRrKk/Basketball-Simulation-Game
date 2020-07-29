#include<vector>
#include<fstream>
#include<iterator>
#include<algorithm>
#include<stdlib.h>
#include<sstream>
#include<filesystem>
#include<iomanip>

#include"playerStatsClass.h"
#include"playerClass.h"
#include"teamClass.h"
#include"gamesClass.h"
#include"startMenu.h";
#include"gameMenu.h"

using namespace std;
namespace fs = std::filesystem;


void readStats(string gmPath, vector<Team>& teamV) {
	vector<Team> tempTeam = teamV;

	fs::path pth{ gmPath + "/Games" };
	string t1Name, t2Name, line;
	int resT1, resT2;

	for (auto it : fs::directory_iterator(pth)) {
		if (it.is_regular_file()) {

			t1Name = it.path().filename().string();
			t1Name.erase(0, 1);
			t1Name.erase(t1Name.find_last_of("v"), string::npos);
			
			t2Name = it.path().filename().string();
			t2Name.erase(0, t2Name.find_last_of("v") + 1);
			t2Name.erase(t2Name.find_last_of("."), string::npos);
			
			string fname = it.path().string();
			fstream fp(fname, ios::in);
			if (!fp) {
				cout << endl << "******* ERROR *******";
				exit(1);
			}
			if (fp.is_open()) {
				getline(fp, line); // team1 name
				getline(fp, line); // team1 score
				int htRes = stoi(line);

				vector<Player> playV;
				for (auto it_t = tempTeam.begin(); it_t != tempTeam.end(); it_t++) {
					if ((*it_t).getTeamName() == t1Name) {
						playV = (*it_t).getTeamPlayers();
					}
				}

				getline(fp, line);
				while (line != t2Name) {
					string st, pName;
					int val, tempVal;
					PlayerStats stats, ps;

					stringstream ss(line);
					string word;
					getline(ss, word, ' '); // first name
					pName = word;
					getline(ss, word, ' '); // last name
					pName = pName + " " + word;

					for (auto it_p = playV.begin(); it_p != playV.end(); it_p++) {
						if ((*it_p).getPlayerName() == pName) {
							ps = (*it_p).getPlayerStats();
						}
					}

					getline(ss, word, ' ');
					val = stoi(word);
					stats.setStatTotalMinutes(ps.getStatTotalMinutes() + val);

					getline(ss, word, ' ');
					val = stoi(word);
					stats.setStatTotalPoints(ps.getStatTotalPoints() + val);

					getline(ss, word, ' ');
					val = stoi(word);
					stats.setStatTotalAssists(ps.getStatTotalAssists() + val);

					getline(ss, word, ' ');
					val = stoi(word);
					stats.setStatTotalRebounds(ps.getStatTotalRebounds() + val);

					getline(ss, word, ' ');
					val = stoi(word);
					stats.setStatTotalSteals(ps.getStatTotalSteals() + val);

					getline(ss, word, ' ');
					val = stoi(word);
					stats.setStatTotalBlocks(ps.getStatTotalBlocks() + val);

					getline(ss, word, ' ');
					val = stoi(word);
					stats.setStatTotalTurnovers(ps.getStatTotalTurnovers() + val);

					getline(ss, word, ' ');
					val = stoi(word);
					stats.setStatTotalMadeFG(ps.getStatTotalMadeFG() + val);

					getline(ss, word, ' ');
					val = stoi(word);
					stats.setStatTotalAtemptedFG(ps.getStatTotalAtemptedFG() + val);

					getline(ss, word, ' ');
					val = stoi(word);
					stats.setStatTotalMade3PT(ps.getStatTotalMade3PT() + val);

					getline(ss, word, ' ');
					val = stoi(word);
					stats.setStatTotalAtempted3PT(ps.getStatTotalAtempted3PT() + val);

					getline(ss, word, ' ');
					val = stoi(word);
					stats.setStatTotalMadeFT(ps.getStatTotalMadeFT() + val);

					getline(ss, word, ' ');
					val = stoi(word);
					stats.setStatTotalAtemptedFT(ps.getStatTotalAtemptedFT() + val);

					for (auto it_p = playV.begin(); it_p != playV.end(); it_p++) {
						if ((*it_p).getPlayerName() == pName) {
							(*it_p).setPlayerStats(stats);
						}
					}

					getline(fp, line);
				}

				for (auto it_t = tempTeam.begin(); it_t != tempTeam.end(); it_t++) {
					if ((*it_t).getTeamName() == t1Name) {
						(*it_t).setTeamPlayers(playV);
					}
				}
				playV.clear();

				getline(fp, line); // team2 score
				int atRes = stoi(line);

				for (auto it_t = tempTeam.begin(); it_t != tempTeam.end(); it_t++) {
					if ((*it_t).getTeamName() == t2Name) {
						playV = (*it_t).getTeamPlayers();
					}
				}

				while (getline(fp, line)) {
					string st, pName;
					int val, tempVal;
					PlayerStats stats, ps;

					stringstream ss(line);
					string word;
					getline(ss, word, ' '); // first name
					pName = word;
					getline(ss, word, ' '); // last name
					pName = pName + " " + word;

					for (auto it_p = playV.begin(); it_p != playV.end(); it_p++) {
						if ((*it_p).getPlayerName() == pName) {
							ps = (*it_p).getPlayerStats();
						}
					}

					getline(ss, word, ' ');
					val = stoi(word);
					stats.setStatTotalMinutes(ps.getStatTotalMinutes() + val);

					getline(ss, word, ' ');
					val = stoi(word);
					stats.setStatTotalPoints(ps.getStatTotalPoints() + val);

					getline(ss, word, ' ');
					val = stoi(word);
					stats.setStatTotalAssists(ps.getStatTotalAssists() + val);

					getline(ss, word, ' ');
					val = stoi(word);
					stats.setStatTotalRebounds(ps.getStatTotalRebounds() + val);

					getline(ss, word, ' ');
					val = stoi(word);
					stats.setStatTotalSteals(ps.getStatTotalSteals() + val);

					getline(ss, word, ' ');
					val = stoi(word);
					stats.setStatTotalBlocks(ps.getStatTotalBlocks() + val);

					getline(ss, word, ' ');
					val = stoi(word);
					stats.setStatTotalTurnovers(ps.getStatTotalTurnovers() + val);

					getline(ss, word, ' ');
					val = stoi(word);
					stats.setStatTotalMadeFG(ps.getStatTotalMadeFG() + val);

					getline(ss, word, ' ');
					val = stoi(word);
					stats.setStatTotalAtemptedFG(ps.getStatTotalAtemptedFG() + val);

					getline(ss, word, ' ');
					val = stoi(word);
					stats.setStatTotalMade3PT(ps.getStatTotalMade3PT() + val);

					getline(ss, word, ' ');
					val = stoi(word);
					stats.setStatTotalAtempted3PT(ps.getStatTotalAtempted3PT() + val);

					getline(ss, word, ' ');
					val = stoi(word);
					stats.setStatTotalMadeFT(ps.getStatTotalMadeFT() + val);

					getline(ss, word, ' ');
					val = stoi(word);
					stats.setStatTotalAtemptedFT(ps.getStatTotalAtemptedFT() + val);

					for (auto it_p = playV.begin(); it_p != playV.end(); it_p++) {
						if ((*it_p).getPlayerName() == pName) {
							(*it_p).setPlayerStats(stats);
						}
					}

				}

				for (auto it_t = tempTeam.begin(); it_t != tempTeam.end(); it_t++) {
					if ((*it_t).getTeamName() == t2Name) {
						(*it_t).setTeamPlayers(playV);
					}
				}

				for (auto it_t = tempTeam.begin(); it_t != tempTeam.end(); it_t++) {
					if ((*it_t).getTeamName() == t1Name) {
						if (htRes > atRes) {
							(*it_t).addTeamWin();
						}
						else {
							(*it_t).addTeamLoss();
						}
					}

					if ((*it_t).getTeamName() == t2Name) {
						if (atRes > htRes) {
							(*it_t).addTeamWin();
						}
						else {
							(*it_t).addTeamLoss();
						}
					}
				}

				teamV = tempTeam;

				fp.close();
			}
		}
	}
}





bool sortOvr(Player p1, Player p2) { return p1.getPlayerOverall() > p2.getPlayerOverall(); } // support function for sorting
bool compDiff(Player p1, Player p2) { return (p1.getPlayerOverall() == p2.getPlayerOverall()); }
int getPositionNumber(Player p) {
	string pos = p.getPlayerPosition();
	if (pos == "PG" || pos == "SG" || pos == "SF" || pos == "PF") { return 2; }
	else if (pos == "C/PF" || pos == "PF/C") { return 4; }
	else if (pos == "C") { return 1; }
	else { return 5; }
}



// Game Menu function for showing and modifying the roster
void rosterFunction(Team& myTeam) {
	Team rosterTeam = myTeam;
	vector<Player> vtemp = rosterTeam.getTeamPlayers();
	auto vit = vtemp.end() - 1;
	Player ptemp = (*vit);

	vector<Player> starters;

	sort(vtemp.begin(), vtemp.end(), sortOvr);

	system("cls");
	cout << "--Starters---------------------" << endl;
	for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
		string pos = (*it).getPlayerPosition();
		if (pos == "PG" || pos == "PG/SG") {
			if ((*it).getPlayerOverall() > ptemp.getPlayerOverall()) {
				ptemp = (*it);
			}
		}
	}
	if (ptemp.getPlayerName().length() + 4 < 16) {
		cout << "PG: " << ptemp.getPlayerName() << "\t\t\t" << ptemp.getPlayerOverall() << " OVR " << ptemp.getPlayerAge() << "yo\tOFF: " << ptemp.getCalcPlayerOffence() << " DEF: " << ptemp.getCalcPlayerDefence() << endl;
	}
	else if (ptemp.getPlayerName().length() + 4 > 24) {
		cout << "PG: " << ptemp.getPlayerName() << "\t" << ptemp.getPlayerOverall() << " OVR " << ptemp.getPlayerAge() << "yo\tOFF: " << ptemp.getCalcPlayerOffence() << " DEF: " << ptemp.getCalcPlayerDefence() << endl;
	}
	else {
		cout << "PG: " << ptemp.getPlayerName() << "\t\t" << ptemp.getPlayerOverall() << " OVR " << ptemp.getPlayerAge() << "yo\tOFF: " << ptemp.getCalcPlayerOffence() << " DEF: " << ptemp.getCalcPlayerDefence() << endl;
	}
	starters.push_back(ptemp);

	ptemp = (*vit);
	for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
		string pos = (*it).getPlayerPosition();
		if (pos == "SG" || pos == "SG/PG" || pos == "SG/SF") {
			if ((*it).getPlayerOverall() > ptemp.getPlayerOverall()) {
				ptemp = (*it);
			}
		}
	}
	if (ptemp.getPlayerName().length() + 4 < 16) {
		cout << "SG: " << ptemp.getPlayerName() << "\t\t\t" << ptemp.getPlayerOverall() << " OVR " << ptemp.getPlayerAge() << "yo\tOFF: " << ptemp.getCalcPlayerOffence() << " DEF: " << ptemp.getCalcPlayerDefence() << endl;
	}
	else if (ptemp.getPlayerName().length() + 4 > 24) {
		cout << "SG: " << ptemp.getPlayerName() << "\t" << ptemp.getPlayerOverall() << " OVR " << ptemp.getPlayerAge() << "yo\tOFF: " << ptemp.getCalcPlayerOffence() << " DEF: " << ptemp.getCalcPlayerDefence() << endl;
	}
	else {
		cout << "SG: " << ptemp.getPlayerName() << "\t\t" << ptemp.getPlayerOverall() << " OVR " << ptemp.getPlayerAge() << "yo\tOFF: " << ptemp.getCalcPlayerOffence() << " DEF: " << ptemp.getCalcPlayerDefence() << endl;
	}
	starters.push_back(ptemp);

	ptemp = (*vit);
	for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
		string pos = (*it).getPlayerPosition();
		if (pos == "SF" || pos == "SF/SG" || pos == "SF/PF") {
			if ((*it).getPlayerOverall() > ptemp.getPlayerOverall()) {
				ptemp = (*it);
			}
		}
	}
	if (ptemp.getPlayerName().length() + 4 < 16) {
		cout << "SF: " << ptemp.getPlayerName() << "\t\t\t" << ptemp.getPlayerOverall() << " OVR " << ptemp.getPlayerAge() << "yo\tOFF: " << ptemp.getCalcPlayerOffence() << " DEF: " << ptemp.getCalcPlayerDefence() << endl;
	}
	else if (ptemp.getPlayerName().length() + 4 > 24) {
		cout << "SF: " << ptemp.getPlayerName() << "\t" << ptemp.getPlayerOverall() << " OVR " << ptemp.getPlayerAge() << "yo\tOFF: " << ptemp.getCalcPlayerOffence() << " DEF: " << ptemp.getCalcPlayerDefence() << endl;
	}
	else {
		cout << "SF: " << ptemp.getPlayerName() << "\t\t" << ptemp.getPlayerOverall() << " OVR " << ptemp.getPlayerAge() << "yo\tOFF: " << ptemp.getCalcPlayerOffence() << " DEF: " << ptemp.getCalcPlayerDefence() << endl;
	}
	starters.push_back(ptemp);

	ptemp = (*vit);
	for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
		string pos = (*it).getPlayerPosition();
		if (pos == "PF" || pos == "PF/SF" || pos == "PF/C") {
			if ((*it).getPlayerOverall() > ptemp.getPlayerOverall()) {
				ptemp = (*it);
			}
		}
	}
	if (ptemp.getPlayerName().length() + 4 < 16) {
		cout << "PF: " << ptemp.getPlayerName() << "\t\t\t" << ptemp.getPlayerOverall() << " OVR " << ptemp.getPlayerAge() << "yo\tOFF: " << ptemp.getCalcPlayerOffence() << " DEF: " << ptemp.getCalcPlayerDefence() << endl;
	}
	else if (ptemp.getPlayerName().length() + 4 > 24) {
		cout << "PF: " << ptemp.getPlayerName() << "\t" << ptemp.getPlayerOverall() << " OVR " << ptemp.getPlayerAge() << "yo\tOFF: " << ptemp.getCalcPlayerOffence() << " DEF: " << ptemp.getCalcPlayerDefence() << endl;
	}
	else {
		cout << "PF: " << ptemp.getPlayerName() << "\t\t" << ptemp.getPlayerOverall() << " OVR " << ptemp.getPlayerAge() << "yo\tOFF: " << ptemp.getCalcPlayerOffence() << " DEF: " << ptemp.getCalcPlayerDefence() << endl;
	}
	starters.push_back(ptemp);

	ptemp = (*vit);
	for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
		string pos = (*it).getPlayerPosition();
		if (pos == "C" || pos == "C/PF") {
			if ((*it).getPlayerOverall() > ptemp.getPlayerOverall()) {
				ptemp = (*it);
			}
		}
	}
	if (ptemp.getPlayerName().length() + 3 < 16) {
		cout << "C: " << ptemp.getPlayerName() << "\t\t\t" << ptemp.getPlayerOverall() << " OVR " << ptemp.getPlayerAge() << "yo\tOFF: " << ptemp.getCalcPlayerOffence() << " DEF: " << ptemp.getCalcPlayerDefence() << endl;
	}
	else if (ptemp.getPlayerName().length() + 3 > 24) {
		cout << "C: " << ptemp.getPlayerName() << "\t" << ptemp.getPlayerOverall() << " OVR " << ptemp.getPlayerAge() << "yo\tOFF: " << ptemp.getCalcPlayerOffence() << " DEF: " << ptemp.getCalcPlayerDefence() << endl;
	}
	else {
		cout << "C: " << ptemp.getPlayerName() << "\t\t" << ptemp.getPlayerOverall() << " OVR " << ptemp.getPlayerAge() << "yo\tOFF: " << ptemp.getCalcPlayerOffence() << " DEF: " << ptemp.getCalcPlayerDefence() << endl;
	}
	starters.push_back(ptemp);

	vector<Player> bench = vtemp;

	auto pred = [&starters](const Player& pl) ->bool {
		return find(starters.begin(), starters.end(), pl) != starters.end();
	};
	bench.erase(remove_if(bench.begin(), bench.end(), pred), bench.end());

	sort(bench.begin(), bench.end(), sortOvr);

	cout << endl << "--Bench------------------------" << endl;
	for (auto it = bench.begin(); it != bench.end(); it++) {
		Player pl = (*it);
		int pnum = getPositionNumber(pl) + 2;

		if ((*it).getPlayerName().length() + pnum <= 16) {
			cout << (*it).getPlayerPosition() << ": " << (*it).getPlayerName() << "\t\t\t" << (*it).getPlayerOverall() << " OVR " << (*it).getPlayerAge() << "yo\tOFF: " << (*it).getCalcPlayerOffence() << "\tDEF: " << (*it).getCalcPlayerDefence() << endl;
		}
		else if ((*it).getPlayerName().length() + pnum > 24) {
			cout << (*it).getPlayerPosition() << ": " << (*it).getPlayerName() << "\t" << (*it).getPlayerOverall() << " OVR " << (*it).getPlayerAge() << "yo\tOFF: " << (*it).getCalcPlayerOffence() << "\tDEF: " << (*it).getCalcPlayerDefence() << endl;
		}
		else {
			cout << (*it).getPlayerPosition() << ": " << (*it).getPlayerName() << "\t\t" << (*it).getPlayerOverall() << " OVR " << (*it).getPlayerAge() << "yo\tOFF: " << (*it).getCalcPlayerOffence() << "\tDEF: " << (*it).getCalcPlayerDefence() << endl;
		}
	}

	system("pause");
}



bool sortSal(Player p1, Player p2) {
	double p1s, p2s;
	string sal;

	sal = p1.getPlayerSalary();
	sal.erase(0, 2);
	p1s = stod(sal);

	sal = p2.getPlayerSalary();
	sal.erase(0, 2);
	p2s = stod(sal);

	return p1s > p2s;
}

// Game Manu function for showing the finances of the team
void showFinances(Team& myTeam) {
	Team finTeam = myTeam;
	vector<Player> vtemp = finTeam.getTeamPlayers();

	sort(vtemp.begin(), vtemp.end(), sortSal);

	system("cls");
	cout << "--Team-Finances--------------------------------------------------------------" << endl;
	cout << "\t\t\t\t\tYear 1\tYear 2\tYear 3\tYear 4\tYear 5" << endl << endl;
	for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
		if ((*it).getPlayerName().length() <= 15) {
			cout << (*it).getPlayerName() << "\t\t" << (*it).getPlayerOverall() << " OVR -\t" << (*it).salaryForFinances() << endl;
		}
		else {
			cout << (*it).getPlayerName() << "\t" << (*it).getPlayerOverall() << " OVR -\t" << (*it).salaryForFinances() << endl;
		}
	}
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << finTeam.getTeamName() << " - \t\t\t\t\t";
	vector<double> d = finTeam.salaryForFinances();
	for (auto it = d.begin(); it != d.end(); it++) {
		cout << setprecision(2) << fixed << *it << "\t";
	}
	//cout << finTeam.getTeamName() << " - " << finTeam.salaryForFinances() << endl << endl;
	cout << endl << endl;
	system("pause");
}



bool compSeasonTeam(Team t1, Team t2) {
	if (t1.getTeamLoses() != t2.getTeamLoses()) { return t1.getTeamLoses() < t2.getTeamLoses(); }
	else { return t1.getTeamWins() > t2.getTeamWins(); }
}
bool compEmptyTeam(Team t1, Team t2) {
	return t1.getTeamCalcOverall() > t2.getTeamCalcOverall();
}

//Game Menu function for showing the standings
void showTeamStandings(Games gm, string gmPath, vector<Team>& vtemp) {
	system("cls");
	int day = gm.getInfoDay(gmPath);
	vector<Team>& tvec = vtemp;

	cout << "Team\tWins\tLoses" << endl;
	cout << "-------------------" << endl;
	if (day == 0) {
		sort(tvec.begin(), tvec.end(), compEmptyTeam);
		for (auto it = tvec.begin(); it != tvec.end(); it++) {
			cout << (*it).getTeamName() << "\t" << (*it).getTeamWins() << "\t" << (*it).getTeamLoses() << endl;
		}
	}
	else {
		sort(tvec.begin(), tvec.end(), compSeasonTeam);
		for (auto it = tvec.begin(); it != tvec.end(); it++) {
			cout << (*it).getTeamName() << "\t" << (*it).getTeamWins() << "\t" << (*it).getTeamLoses() << endl;
		}
	}

	system("pause");
}



// Game Menu function for showing the player standings by overall
void showPlayerStandings(int ch, vector<Team> vtemp) {
	system("cls");
	vector<Player> pvec;
	vector<Team> tvec = vtemp;

	// showing rookie standings
	if (ch == 1) {
		for (auto it_t = tvec.begin(); it_t != tvec.end(); it_t++) {
			vector<Player> ptemp = (*it_t).getTeamPlayers();
			for (auto it_p = ptemp.begin(); it_p != ptemp.end(); it_p++) {
				Player p = (*it_p);
				if (p.getPlayerYearsPro() == 1) {
					pvec.push_back(p);
				}
			}
		}

		sort(pvec.begin(), pvec.end(), sortOvr);
		cout << "--Player Rookie----------------------" << endl;
		int i = 1;
		int iSize = 0;
		for (auto it = pvec.begin(); it != pvec.end(); it++) {
			if (i < 10) { iSize = 1; }
			else if (i >= 10 && i < 100) { iSize = 2; }
			else { iSize = 3; }

			if ((*it).getPlayerName().length() + iSize + 2 > 23) {
				cout << i << ". " << (*it).getPlayerName() << "\t" << (*it).getPlayerAge() << "yo\t" << (*it).getPlayerTeam() << "\t" << (*it).getPlayerOverall() << " OVR" << "\tOFF: " << (*it).getCalcPlayerOffence() << "\tDIF: " << (*it).getCalcPlayerDefence() << endl;
			}
			else if ((*it).getPlayerName().length() + iSize + 2 < 16) {
				cout << i << ". " << (*it).getPlayerName() << "\t\t\t" << (*it).getPlayerAge() << "yo\t" << (*it).getPlayerTeam() << "\t" << (*it).getPlayerOverall() << " OVR" << "\tOFF: " << (*it).getCalcPlayerOffence() << "\tDIF: " << (*it).getCalcPlayerDefence() << endl;
			}
			else {
				cout << i << ". " << (*it).getPlayerName() << "\t\t" << (*it).getPlayerAge() << "yo\t" << (*it).getPlayerTeam() << "\t" << (*it).getPlayerOverall() << " OVR" << "\tOFF: " << (*it).getCalcPlayerOffence() << "\tDIF: " << (*it).getCalcPlayerDefence() << endl;
			}

			i++;
		}
	}

	// showing sophomore standings
	if (ch == 2) {
		for (auto it_t = tvec.begin(); it_t != tvec.end(); it_t++) {
			vector<Player> ptemp = (*it_t).getTeamPlayers();
			for (auto it_p = ptemp.begin(); it_p != ptemp.end(); it_p++) {
				Player p = (*it_p);
				if (p.getPlayerYearsPro() == 2) {
					pvec.push_back(p);
				}
			}
		}

		sort(pvec.begin(), pvec.end(), sortOvr);
		cout << "--Player Sophomore----------------------" << endl;
		int i = 1;
		int iSize = 0;
		for (auto it = pvec.begin(); it != pvec.end(); it++) {
			if (i < 10) { iSize = 1; }
			else if (i >= 10 && i < 100) { iSize = 2; }
			else { iSize = 3; }

			if ((*it).getPlayerName().length() + iSize + 2 > 23) {
				cout << i << ". " << (*it).getPlayerName() << "\t" << (*it).getPlayerAge() << "yo\t" << (*it).getPlayerTeam() << "\t" << (*it).getPlayerOverall() << " OVR" << "\tOFF: " << (*it).getCalcPlayerOffence() << "\tDIF: " << (*it).getCalcPlayerDefence() << endl;
			}
			else if ((*it).getPlayerName().length() + iSize + 2 < 16) {
				cout << i << ". " << (*it).getPlayerName() << "\t\t\t" << (*it).getPlayerAge() << "yo\t" << (*it).getPlayerTeam() << "\t" << (*it).getPlayerOverall() << " OVR" << "\tOFF: " << (*it).getCalcPlayerOffence() << "\tDIF: " << (*it).getCalcPlayerDefence() << endl;
			}
			else {
				cout << i << ". " << (*it).getPlayerName() << "\t\t" << (*it).getPlayerAge() << "yo\t" << (*it).getPlayerTeam() << "\t" << (*it).getPlayerOverall() << " OVR" << "\tOFF: " << (*it).getCalcPlayerOffence() << "\tDIF: " << (*it).getCalcPlayerDefence() << endl;
			}

			i++;
		}
	}

	// showing all players standings
	if (ch == 3) {
		for (auto it_t = tvec.begin(); it_t != tvec.end(); it_t++) {
			vector<Player> ptemp = (*it_t).getTeamPlayers();
			for (auto it_p = ptemp.begin(); it_p != ptemp.end(); it_p++) {
				Player p = (*it_p);
				pvec.push_back(p);
			}
		}

		sort(pvec.begin(), pvec.end(), sortOvr);
		cout << "--Player Standings----------------------" << endl;
		int i = 1;
		int iSize = 0;
		for (auto it = pvec.begin(); it != pvec.end(); it++) {
			if (i < 10) { iSize = 1; }
			else if (i >= 10 && i < 100) { iSize = 2; }
			else { iSize = 3; }

			if ((*it).getPlayerName().length() + iSize + 2 > 23) {
				cout << i << ". " << (*it).getPlayerName() << "\t" << (*it).getPlayerAge() << "yo\t" << (*it).getPlayerTeam() << "\t" << (*it).getPlayerOverall() << " OVR" << "\tOFF: " << (*it).getCalcPlayerOffence() << "\tDIF: " << (*it).getCalcPlayerDefence() << endl;
			}
			else if ((*it).getPlayerName().length() + iSize + 2 < 16) {
				cout << i << ". " << (*it).getPlayerName() << "\t\t\t" << (*it).getPlayerAge() << "yo\t" << (*it).getPlayerTeam() << "\t" << (*it).getPlayerOverall() << " OVR" << "\tOFF: " << (*it).getCalcPlayerOffence() << "\tDIF: " << (*it).getCalcPlayerDefence() << endl;
			}
			else {
				cout << i << ". " << (*it).getPlayerName() << "\t\t" << (*it).getPlayerAge() << "yo\t" << (*it).getPlayerTeam() << "\t" << (*it).getPlayerOverall() << " OVR" << "\tOFF: " << (*it).getCalcPlayerOffence() << "\tDIF: " << (*it).getCalcPlayerDefence() << endl;
			}

			i++;

			if (i == 251) { break; }
		}
	}

	system("pause");
}



// Game Menu function when you enter a started game
void gameMenu(string chosenGame) {
	Team myTeam;
	fstream gameFile, fp;
	string gamePath = "Games/" + chosenGame;
	string line;
	Games game;

	fs::path pth{ ("Games/" + chosenGame) };
	pth /= "_Main_Team_.txt";

	gameFile.open(pth, ios::in);
	if (!gameFile) {
		cout << endl << "******* ERROR *******";
		exit(1);
	}
	if (gameFile.is_open()) {
		getline(gameFile, line);

		fs::path tempPth{ ("Games/" + chosenGame) };
		tempPth /= line;

		fromFileToTeam(tempPth.string(), myTeam);
		gameFile.close();
	}

	vector<Team> tvec;
	for (auto& p : fs::directory_iterator("Games/" + chosenGame)) {
		if (p.is_regular_file()) {
			Team tempT;
			string str = p.path().filename().string();
			if (str != "_Main_Team_.txt" && str != "_Info_.txt") {
				fromFileToTeam(p.path().string(), tempT);
				tvec.push_back(tempT);
			}
		}
	}

	readStats(gamePath, tvec);

	int days = 0;

	int choice = 0;
	do {
		do {
			system("cls");
			cout << "===========================================" << endl;
			cout << "==================MENU=====================" << endl;
			cout << "---Play------------------------------" << endl;
			cout << "1. Progress One Day" << endl;
			cout << "2. Progress One Week" << endl;
			cout << "3. Progress One Month" << endl;
			cout << "4. Progress in Time" << endl;
			cout << "---Management------------------------" << endl;
			cout << "5. Roster" << endl;
			cout << "6. Team Standings" << endl;
			cout << "7. Progress in Time" << endl;
			cout << "8. View opponent" << endl;
			cout << "9. News" << endl;
			cout << "---Market----------------------------" << endl;
			cout << "10. Draft" << endl;
			cout << "11. Free Agency" << endl;
			cout << "12. Tradeing" << endl;
			cout << "13. Finances" << endl;
			cout << "--Top--------------------------------" << endl;
			cout << "14. Players Standing" << endl;
			cout << "15. Sophomores Standing" << endl;
			cout << "16. Rookie Standing" << endl;
			cout << "--Statistics-------------------------" << endl;
			cout << "17. Players Stats" << endl;
			cout << "18. Sophomores Stats" << endl;
			cout << "19. Rookie Stats" << endl;
			cout << "20. History" << endl;
			cout << "--Other------------------------------" << endl;
			cout << "21. Back to Menu" << endl;
			cout << "End" << endl;
			cout << "===========================================" << endl;
			cout << "-: ";
			cin >> choice;
			switch (choice) {
			case 1:
				game.simulateTime(1, gamePath, tvec);
				break;

			case 2:
				game.simulateTime(7, gamePath, tvec);
				break;

			case 3:
				game.simulateTime(30, gamePath, tvec);
				break;

			case 4:
				do {
					cout << "Pick a day ( 1-167 ) : ";
					cin >> days;
				} while (days < 1 || days>167);
				game.simulateTime(days, gamePath, tvec);
				break;

			case 5:
				rosterFunction(myTeam);
				break;

			case 6:
				showTeamStandings(game, gamePath, tvec);
				break;

			case 7:

				break;

			case 8:

				break;

			case 9:

				break;

			case 10:

				break;

			case 11:

				break;

			case 12:

				break;

			case 13:
				showFinances(myTeam);
				break;

			case 14:
				showPlayerStandings(3, tvec);
				break;

			case 15:
				showPlayerStandings(2, tvec);
				break;

			case 16:
				showPlayerStandings(1, tvec);
				break;

			case 17:

				break;

			case 18:

				break;

			case 19:

				break;

			case 20:

				break;

			case 21:
				return;
				break;

			default: exit(1); break;
			}
		} while (true);
	} while (true);

}
