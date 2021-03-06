#pragma once
#include<iostream>
#include<string>
#include<vector>

#include"playerStatsClass.h"
#include"teamClass.h"

using namespace std;

class Games {
private:
	int mg_gamesNumber;
	vector<PlayerStats> mg_homeTeam;
	vector<PlayerStats> mg_awayTeam;

public:
	void setGamesNumber(const int val);
	void setGamesHomeTeam(const vector<PlayerStats> vp);
	void setGamesAwayTeam(const vector<PlayerStats> vp);

	int getGamesNumber() const;
	vector<PlayerStats> getGamesHomeTeam() const;
	vector<PlayerStats> getGamesAwayTeam() const;

	void simulateGame(int day, string& gmPath, Team& ht, Team& at);
	void simulateTime(int days, string& gmPath, vector<Team>& teamVec);

	int getInfoDay(string gmPath) const;
	void setInfoDay(const int val, string gmPath);
};