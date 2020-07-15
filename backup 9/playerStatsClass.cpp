#include<iostream>
#include<string>

#include"playerStatsClass.h"

using namespace std;



void PlayerStats::calcPER() { ps_PER = (ps_totalPoints + ps_totalAssists + ps_totalRebunds + ps_totalSteals + ps_totalBlocks - (ps_totalAtemptedFG - ps_totalMadeFG) - (ps_totalAtemptedFT - ps_totalMadeFT) - ps_totalTurnovers) / ps_gamesPlayed; }
void PlayerStats::progresOneGamesPlayed(const int val) { ps_gamesPlayed++; calcPER(); }

// setters
void PlayerStats::setStatGamesPlayed(const int val) { ps_gamesPlayed = val; }
void PlayerStats::setStatGamesStarted(const int val) { ps_gamesStarted = val; }

void PlayerStats::setStatTotalPoints(const int val) { ps_totalPoints = ps_totalPoints + val; }
void PlayerStats::setStatTotalAssists(const int val) { ps_totalAssists = ps_totalAssists + val; }
void PlayerStats::setStatTotalRebounds(const int val) { ps_totalRebunds = ps_totalRebunds + val; }
void PlayerStats::setStatTotalSteals(const int val) { ps_totalSteals = ps_totalSteals + val; }
void PlayerStats::setStatTotalBlocks(const int val) { ps_totalBlocks = ps_totalBlocks + val; }
void PlayerStats::setStatTotalMinutes(const int val) { ps_totalMinutes = ps_totalMinutes + val; }
void PlayerStats::setStatTotalFouls(const int val) { ps_totalFouls = ps_totalFouls + val; }
void PlayerStats::setStatTotalTurnovers(const int val) { ps_totalTurnovers = ps_totalTurnovers + val; }

void PlayerStats::setStatTotalAtemptedFT(const int val) { ps_totalAtemptedFT = ps_totalAtemptedFT + val; }
void PlayerStats::setStatTotalMadeFT(const int val) { ps_totalMadeFT = ps_totalMadeFT + val; }
void PlayerStats::setStatTotalAtemptedFG(const int val) { ps_totalAtemptedFG = ps_totalAtemptedFG + val; }
void PlayerStats::setStatTotalMadeFG(const int val) { ps_totalMadeFG = ps_totalMadeFG + val; }
void PlayerStats::setStatTotalAtempted3PT(const int val) { ps_totalAtempted3PT = ps_totalAtempted3PT + val; }
void PlayerStats::setStatTotalMadeThree3PT(const int val) { ps_totalMade3PT = ps_totalMade3PT + val; }

// getters
int PlayerStats::getStatGamesPlayed() const { return ps_gamesPlayed; }
int PlayerStats::getStatGamesStated() const { return ps_gamesStarted; }
int PlayerStats::getStatTotalPoints() const { return ps_totalPoints; }
int PlayerStats::getStatTotalAssists() const { return ps_totalAssists; }
int PlayerStats::getStatTotalRebounds() const { return ps_totalRebunds; }
int PlayerStats::getStatTotalSteals() const { return ps_totalSteals; }
int PlayerStats::getStatTotalBlocks() const { return ps_totalBlocks; }
int PlayerStats::getStatTotalMinutes() const { return ps_totalMinutes; }
int PlayerStats::getStatTotalFouls() const { return ps_totalFouls; }
int PlayerStats::getStatTotalTurnovers() const { return ps_totalTurnovers; }

int PlayerStats::getStatTotalAtemptedFT() const { return ps_totalAtemptedFT; }
int PlayerStats::getStatTotalMadeFT() const { return ps_totalMadeFT; }
int PlayerStats::getStatTotalAtemptedFG() const { return ps_totalAtemptedFG; }
int PlayerStats::getStatTotalMadeFG() const { return ps_totalMadeFG; }
int PlayerStats::getStatTotalAtempted3PT() const { return ps_totalAtempted3PT; }
int PlayerStats::getStatTotalMade3PT() const { return ps_totalMade3PT; }

double PlayerStats::getStatPER() const { return ps_PER; }

// get calculating averages
double PlayerStats::getStatCalcPoints() const { return ps_totalPoints / ps_gamesPlayed; }
double PlayerStats::getStatCalcAssists() const { return ps_totalAssists / ps_gamesPlayed; }
double PlayerStats::getStatCalcRebounds() const { return ps_totalRebunds / ps_gamesPlayed; }
double PlayerStats::getStatCalcSteals() const { return ps_totalSteals / ps_gamesPlayed; }
double PlayerStats::getStatCalcBlocks() const { return ps_totalBlocks / ps_gamesPlayed; }
double PlayerStats::getStatCalcMinutes() const { return ps_totalMinutes / ps_gamesPlayed; }
double PlayerStats::getStatCalcFouls() const { return ps_totalFouls / ps_gamesPlayed; }
double PlayerStats::getStatCalcTurnovers() const { return ps_totalTurnovers / ps_gamesPlayed; }

//get calculated persentages
double PlayerStats::getStatCalcFT() const { return (ps_totalMadeFT / ps_totalAtemptedFT) * 100; }
double PlayerStats::getStatCalcFG() const { return (ps_totalMadeFG / ps_totalAtemptedFG) * 100; }
double PlayerStats::getStatCalc3PT() const { return (ps_totalMade3PT / ps_totalAtempted3PT) * 100; }

PlayerStats::PlayerStats() {
	ps_gamesPlayed = 0;
	ps_gamesStarted = 0;

	ps_totalPoints = 0;
	ps_totalAssists = 0;
	ps_totalRebunds = 0;
	ps_totalSteals = 0;
	ps_totalBlocks = 0;
	ps_totalMinutes = 0;
	ps_totalFouls = 0;
	ps_totalTurnovers = 0;

	ps_totalAtemptedFT = 0;
	ps_totalMadeFT = 0;
	ps_totalAtemptedFG = 0;
	ps_totalMadeFG = 0;
	ps_totalAtempted3PT = 0;
	ps_totalMade3PT = 0;

	ps_PER = 0.0;
}

PlayerStats::PlayerStats(int gp, int gs, int tp, int ta, int tr, int ts, int tb, int tm, int tf, int tt, int taft, int tmft, int tafg, int tmfg, int tapt, int tmpt, double per) {
	ps_gamesPlayed = gp;
	ps_gamesStarted = gs;

	ps_totalPoints = tp;
	ps_totalAssists = ta;
	ps_totalRebunds = tr;
	ps_totalSteals = ts;
	ps_totalBlocks = tb;
	ps_totalMinutes = tm;
	ps_totalFouls = tf;
	ps_totalTurnovers = tt;

	ps_totalAtemptedFT = taft;
	ps_totalMadeFT = tmft;
	ps_totalAtemptedFG = tafg;
	ps_totalMadeFG = tmfg;
	ps_totalAtempted3PT = tapt;
	ps_totalMade3PT = tmpt;

	ps_PER = per;
}

PlayerStats::PlayerStats(int tp, int ta, int tr, int ts, int tb, int tm, int tt, int taft, int tmft, int tafg, int tmfg, int tapt, int tmpt) {
	ps_totalPoints = tp;
	ps_totalAssists = ta;
	ps_totalRebunds = tr;
	ps_totalSteals = ts;
	ps_totalBlocks = tb;
	ps_totalMinutes = tm;
	ps_totalTurnovers = tt;

	ps_totalAtemptedFT = taft;
	ps_totalMadeFT = tmft;
	ps_totalAtemptedFG = tafg;
	ps_totalMadeFG = tmfg;
	ps_totalAtempted3PT = tapt;
	ps_totalMade3PT = tmpt;

	calcPER();
}

PlayerStats::PlayerStats(PlayerStats& ps) {
	ps_gamesPlayed = ps.getStatGamesPlayed();
	ps_gamesStarted = ps.getStatGamesStated();

	ps_totalPoints = ps.getStatTotalPoints();
	ps_totalAssists = ps.getStatTotalAssists();
	ps_totalRebunds = ps.getStatTotalRebounds();
	ps_totalSteals = ps.getStatTotalSteals();
	ps_totalBlocks = ps.getStatTotalBlocks();
	ps_totalMinutes = ps.getStatTotalMinutes();
	ps_totalFouls = ps.getStatTotalFouls();
	ps_totalTurnovers = ps.getStatTotalTurnovers();

	ps_totalAtemptedFT = ps.getStatTotalAtemptedFT();
	ps_totalMadeFT = ps.getStatTotalMadeFT();
	ps_totalAtemptedFG = ps.getStatTotalAtemptedFG();
	ps_totalMadeFG = ps.getStatTotalMadeFG();
	ps_totalAtempted3PT = ps.getStatTotalAtempted3PT();
	ps_totalMade3PT = ps.getStatTotalMade3PT();

	ps_PER = ps.getStatPER();
}

void PlayerStats::showPlayerStats() {
	cout << ps_totalMinutes << "   ";
	cout << ps_totalPoints << "   ";
	cout << ps_totalAssists << "   ";
	cout << ps_totalRebunds << "   ";
	cout << ps_totalSteals << "   ";
	cout << ps_totalBlocks << "   ";
	cout << ps_totalTurnovers << "   ";
	cout << ps_totalMadeFG << "/" << ps_totalAtemptedFG << "   ";
	cout << ps_totalMade3PT << "/" << ps_totalAtempted3PT << "   ";
	cout << ps_totalMadeFT << "/" << ps_totalAtemptedFT << endl;
}

ostream& PlayerStats::output(ostream& out) {
	out << ps_totalMinutes << " ";
	out << ps_totalPoints << " ";
	out << ps_totalAssists << " ";
	out << ps_totalRebunds << " ";
	out << ps_totalSteals << " ";
	out << ps_totalBlocks << " ";
	out << ps_totalTurnovers << " ";
	out << ps_totalMadeFG << " " << ps_totalAtemptedFG << " ";
	out << ps_totalMade3PT << " " << ps_totalAtempted3PT << " ";
	out << ps_totalMadeFT << " " << ps_totalAtemptedFT << endl;
	return out;
}

ostream& operator<<(ostream& out, PlayerStats ps) { return ps.output(out); }