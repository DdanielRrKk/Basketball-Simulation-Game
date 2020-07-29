#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<sstream>

#include"playerClass.h"

using namespace std;

// Class for Basketball Teams
class Team {
private:
	string mt_name;
	vector<Player> mt_Players;

	int mt_wins;
	int mt_loses;

public:

	void setTeamName(const string val);
	void setTeamPlayers(const vector<Player> vplay);
	void setTeamWins(const int val);
	void setTeamLoses(const int val);

	string getTeamName() const;
	vector<Player> getTeamPlayers() const;
	int getTeamWins() const;
	int getTeamLoses() const;

	void addPlayerToTeam(Player& p);
	void addTeamWin();
	void addTeamLoss();

	Team();

	Team(string tmval, vector<Player> vplay, int wval, int lval);

	Team(const Team& tm);

	// getters for averages from players
	int getTeamCalcInsideScoring();

	int getTeamCalcOutsideScoring();

	int getTeamCalcFreeThrow();

	int getTeamCalcPassing();

	int getTeamCalcRebounding();

	int getTeamCalcStealing();

	int getTeamCalcBlocking();

	int getTeamCalcDefending();

	int getTeamCalcOverall();

	double getTeamCalcSalary();


	vector<double> salaryForFinances();
	void readStats(string gmPath);
};