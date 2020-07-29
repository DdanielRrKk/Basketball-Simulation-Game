#include<iostream>
#include<string>
#include<vector>

#include"playerClass.h"
#include"teamClass.h"
#include"gamesClass.h"
#include"startMenu.h";

using namespace std;

void readStats(string gmPath, vector<Team>& teamV);

bool sortOvr(Player p1, Player p2);
bool compDiff(Player p1, Player p2);
int getPositionNumber(Player p);

void rosterFunction(Team& myTeam);

bool sortSal(Player p1, Player p2);
void showFinances(Team& myTeam);

bool compSeasonTeam(Team t1, Team t2);
bool compEmptyTeam(Team t1, Team t2);
void showTeamStandings(Games gm, string gmPath, vector<Team>& vtemp);

void showPlayerStandings(int ch, vector<Team> vtemp);

void gameMenu(string chosenGame);