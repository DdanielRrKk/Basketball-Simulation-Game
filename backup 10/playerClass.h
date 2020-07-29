#pragma once
#include<iostream>
#include<string>
#include<vector>

#include"playerStatsClass.h"

using namespace std;

// Class for making a basketball Player
class Player {
private:
	string mp_name;
	int mp_age;
	int mp_overall;
	int mp_insideScoring;
	int mp_outsideScoring;
	int mp_freeThrow;
	int mp_passing;
	int mp_rebounding;
	int mp_stealing;
	int mp_blocking;
	int mp_defending;

	string mp_position;
	string mp_salary;
	int mp_yearsPro;

	int mp_energy;
	pair<int, string> mp_injury;

	PlayerStats mp_stats;
	vector<string> mp_awards;

	string mp_team;

public:
	void setPlayerOverall();
	void addPlayerAward(const string awr);

	// setters
	void setPlayerName(const string val);
	void setPlayerAge(const int val);
	void setPlayerInsideScoringRating(const int val);
	void setPlayerOutsideScoringRating(const int val);
	void setPlayerFreeThrowRating(const int val);
	void setPlayerPassingRating(const int val);
	void setPlayerReboundingRating(const int val);
	void setPlayerStealingRating(const int val);
	void setPlayerBlockingRating(const int val);
	void setPlayerDefendingRating(const int val);

	void setPlayerPosition(const string val);
	void setPlayerSalary(const string val);
	void setPlayerYearsPro(const int val);

	void setPlayerEnergy(const int val);
	void setPlayerInjury(const int days, const string name);

	void setPlayerTeam(const string val);

	void setPlayerStats(const PlayerStats ps);

	// getters
	string getPlayerName() const;
	int getPlayerAge() const;
	int getPlayerInsideScoringRating() const;
	int getPlayerOutsideScoringRating() const;
	int getPlayerFreeThrowRating() const;
	int getPlayerPassingRating() const;
	int getPlayerReboundingRating() const;
	int getPlayerStealingRating() const;
	int getPlayerBlockingRating() const;
	int getPlayerDefendingRating() const;
	int getPlayerOverall() const;

	string getPlayerPosition() const;
	string getPlayerSalary() const;
	int getPlayerYearsPro() const;

	int getPlayerEnergy() const;
	pair<int, string> getPlayerInjury() const;

	string getPlayerTeam() const;

	vector<string> getPlayerAwards() const;
	PlayerStats getPlayerStats();

	int getCalcPlayerOffence();
	int getCalcPlayerDefence();

	// default constructor
	Player();

	// explicit constructor
	Player(string nmval, int aval, int isval, int osval, int ftval, int psval, int rbval, int stval, int blval, int dfval, string posval, string salval, int yeval, int enval, int injdayval, string injnamval);

	// copy constructor
	Player(const Player& p);

	istream& inputPlayer(istream& in);
	friend istream& operator>>(istream& in, Player& pl);

	ostream& outputPlayer(ostream& out);
	friend ostream& operator<<(ostream& out, Player& pl);

	friend bool operator==(Player p1, Player p2);
	friend bool operator>(Player p1, Player p2);


	void showPlayer();

	string salaryForFinances();
};