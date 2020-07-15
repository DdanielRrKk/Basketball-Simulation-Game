#include<iostream>
#include<string>
#include<vector>
#include<sstream>

#include"teamClass.h"

using namespace std;

// Class for Basketball Teams
void Team::setTeamName(const string val) { mt_name = val; }
void Team::setTeamPlayers(const vector<Player> vplay) { mt_Players = vplay; }
void Team::setTeamWins(const int val) { mt_wins = mt_wins + val; }
void Team::setTeamLoses(const int val) { mt_loses = mt_loses + val; }

string Team::getTeamName() const { return mt_name; }
vector<Player> Team::getTeamPlayers() const { return mt_Players; }
int Team::getTeamWins() const { return mt_wins; }
int Team::getTeamLoses() const { return mt_loses; }

void Team::addPlayerToTeam(Player& p) { Player tp = p; mt_Players.push_back(tp); }

Team::Team() {
	mt_name = " ";
	mt_Players.clear();
	mt_wins = 0;
	mt_loses = 0;
}

Team::Team(string tmval, vector<Player> vplay, int wval, int lval) {
	mt_name = tmval;
	mt_Players = vplay;
	mt_wins = wval;
	mt_loses = lval;
}

Team::Team(const Team& tm) {
	mt_name = tm.getTeamName();
	mt_Players = tm.getTeamPlayers();
	mt_wins = tm.getTeamWins();
	mt_loses = tm.getTeamLoses();
}

// getters for averages from players
int Team::getTeamCalcInsideScoring() {
	int res = 0;
	for (auto it = mt_Players.begin(); it != mt_Players.end(); it++) {
		res = res + (*it).getPlayerInsideScoringRating();
	}
	return res / mt_Players.size();
}

int Team::getTeamCalcOutsideScoring() {
	int res = 0;
	for (auto it = mt_Players.begin(); it != mt_Players.end(); it++) {
		res = res + (*it).getPlayerOutsideScoringRating();
	}
	return res / mt_Players.size();
}

int Team::getTeamCalcFreeThrow() {
	int res = 0;
	for (auto it = mt_Players.begin(); it != mt_Players.end(); it++) {
		res = res + (*it).getPlayerFreeThrowRating();
	}
	return res / mt_Players.size();
}

int Team::getTeamCalcPassing() {
	int res = 0;
	for (auto it = mt_Players.begin(); it != mt_Players.end(); it++) {
		res = res + (*it).getPlayerPassingRating();
	}
	return res / mt_Players.size();
}

int Team::getTeamCalcRebounding() {
	int res = 0;
	for (auto it = mt_Players.begin(); it != mt_Players.end(); it++) {
		res = res + (*it).getPlayerReboundingRating();
	}
	return res / mt_Players.size();
}

int Team::getTeamCalcStealing() {
	int res = 0;
	for (auto it = mt_Players.begin(); it != mt_Players.end(); it++) {
		res = res + (*it).getPlayerStealingRating();
	}
	return res / mt_Players.size();
}

int Team::getTeamCalcBlocking() {
	int res = 0;
	for (auto it = mt_Players.begin(); it != mt_Players.end(); it++) {
		res = res + (*it).getPlayerBlockingRating();
	}
	return res / mt_Players.size();
}

int Team::getTeamCalcDefending() {
	int res = 0;
	for (auto it = mt_Players.begin(); it != mt_Players.end(); it++) {
		res = res + (*it).getPlayerDefendingRating();
	}
	return res / mt_Players.size();
}

int Team::getTeamCalcOverall() {
	int res = 0;
	for (auto it = mt_Players.begin(); it != mt_Players.end(); it++) {
		res = res + (*it).getPlayerOverall();
	}
	return res / mt_Players.size();
}

double Team::getTeamCalcSalary() {
	double res = 0.0;
	string sal;
	for (auto it = mt_Players.begin(); it != mt_Players.end(); it++) {
		sal = (*it).getPlayerSalary();
		sal.erase(0, 2);
		res = res + stod(sal);
	}
	return res;
}


vector<double> Team::salaryForFinances() {
	double y1(0), y2(0), y3(0), y4(0), y5(0);

	for (auto it = mt_Players.begin(); it != mt_Players.end(); it++) {
		string s = (*it).getPlayerSalary();
		s.erase(s.find_last_of("x"), string::npos);

		string m = (*it).getPlayerSalary();
		m.erase(0, m.find_last_of("x") + 1);

		for (int i = 0; i < stoi(s); i++) {
			if (i == 0) {
				y1 = (y1 + stod(m));
			}
			if (i == 1) {
				y2 = (y2 + stod(m));
			}
			if (i == 2) {
				y3 = (y3 + stod(m));
			}
			if (i == 3) {
				y4 = (y4 + stod(m));
			}
			if (i == 4) {
				y5 = (y5 + stod(m));
			}
		}
	}

	vector<double> d;
	d.push_back(y1);
	d.push_back(y2);
	d.push_back(y3);
	d.push_back(y4);
	d.push_back(y5);
	return d;
}
