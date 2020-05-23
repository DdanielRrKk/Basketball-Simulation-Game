#include<iostream>
#include<string>
#include<vector>

#include"playerClass.h"

using namespace std;

// Class for making a basketball Player
void Player::setPlayerOverall() { mp_overall = ((7 * mp_insideScoring) + (8 * mp_outsideScoring) + mp_freeThrow + (6 * mp_passing) + (5 * mp_rebounding) + (2 * mp_stealing) + (3 * mp_blocking) + (4 * mp_defending)) / 30; }
void Player::addPlayerAward(const string awr) { mp_awards.push_back(awr); }

// setters
void Player::setPlayerName(const string val) { mp_name = val; }
void Player::setPlayerAge(const int val) { mp_age = val; }
void Player::setPlayerInsideScoringRating(const int val) { mp_insideScoring = val; setPlayerOverall(); }
void Player::setPlayerOutsideScoringRating(const int val) { mp_outsideScoring = val; setPlayerOverall(); }
void Player::setPlayerFreeThrowRating(const int val) { mp_freeThrow = val; setPlayerOverall(); }
void Player::setPlayerPassingRating(const int val) { mp_passing = val; setPlayerOverall(); }
void Player::setPlayerReboundingRating(const int val) { mp_rebounding = val; setPlayerOverall(); }
void Player::setPlayerStealingRating(const int val) { mp_stealing = val; setPlayerOverall(); }
void Player::setPlayerBlockingRating(const int val) { mp_blocking = val; setPlayerOverall(); }
void Player::setPlayerDefendingRating(const int val) { mp_defending = val; setPlayerOverall(); }

void Player::setPlayerPosition(const string val) { mp_position = val; }
void Player::setPlayerSalary(const string val) { mp_salary = val; }
void Player::setPlayerYearsPro(const int val) { mp_yearsPro = val; }
void Player::setPlayerEnergy(const int val) { mp_energy = val; }
void Player::setPlayerInjury(const int days, const string name) { mp_injury.first = days; mp_injury.second = name; }

void Player::setPlayerTeam(const string val) { mp_team = val; }

void Player::setPlayerStats(const PlayerStats ps) { mp_stats = ps; }

// getters
string Player::getPlayerName() const { return mp_name; }
int Player::getPlayerAge() const { return mp_age; }
int Player::getPlayerInsideScoringRating() const { return mp_insideScoring; }
int Player::getPlayerOutsideScoringRating() const { return mp_outsideScoring; }
int Player::getPlayerFreeThrowRating() const { return mp_freeThrow; }
int Player::getPlayerPassingRating() const { return mp_passing; }
int Player::getPlayerReboundingRating() const { return mp_rebounding; }
int Player::getPlayerStealingRating() const { return mp_stealing; }
int Player::getPlayerBlockingRating() const { return mp_blocking; }
int Player::getPlayerDefendingRating() const { return mp_defending; }
int Player::getPlayerOverall() const { return mp_overall; }
string Player::getPlayerPosition() const { return mp_position; }
string Player::getPlayerSalary() const { return mp_salary; }
int Player::getPlayerYearsPro() const { return mp_yearsPro; }

int Player::getPlayerEnergy() const { return mp_energy; }
pair<int, string> Player::getPlayerInjury() const { return mp_injury; }

string Player::getPlayerTeam() const { return mp_team; }

vector<string> Player::getPlayerAwards() const { return mp_awards; }
PlayerStats Player::getPlayerStats() { return mp_stats; }

int Player::getCalcPlayerOffence() { return (mp_insideScoring + mp_outsideScoring + mp_freeThrow + mp_passing) / 4; }
int Player::getCalcPlayerDefence() { return (mp_rebounding + mp_stealing + mp_defending + mp_blocking) / 4; }

// default constructor
Player::Player() {
	mp_name = " ";
	mp_age = 0;
	mp_overall = 0;
	mp_insideScoring = 0;
	mp_outsideScoring = 0;
	mp_freeThrow = 0;
	mp_passing = 0;
	mp_rebounding = 0;
	mp_stealing = 0;
	mp_blocking = 0;
	mp_defending = 0;

	mp_position = " ";
	mp_salary = " ";
	mp_yearsPro = 0;

	mp_energy = 0;
	mp_injury.first = 0; mp_injury.second = " ";

	mp_team = "Free Agent";
}

// explicit constructor
Player::Player(string nmval, int aval, int isval, int osval, int ftval, int psval, int rbval, int stval, int blval, int dfval, string posval, string salval, int yeval, int enval, int injdayval, string injnamval) {
	mp_name = nmval;
	mp_age = aval;
	mp_insideScoring = isval;
	mp_outsideScoring = osval;
	mp_freeThrow = ftval;
	mp_passing = psval;
	mp_rebounding = rbval;
	mp_stealing = stval;
	mp_blocking = blval;
	mp_defending = dfval;
	setPlayerOverall();

	mp_position = posval;
	mp_salary = salval;
	mp_yearsPro = yeval;

	mp_energy = enval;
	mp_injury.first = injdayval; mp_injury.second = injnamval;
}

// copy constructor
Player::Player(const Player& p) {
	mp_name = p.getPlayerName();
	mp_age = p.getPlayerAge();
	mp_insideScoring = p.getPlayerInsideScoringRating();
	mp_outsideScoring = p.getPlayerOutsideScoringRating();
	mp_freeThrow = p.getPlayerFreeThrowRating();
	mp_passing = p.getPlayerPassingRating();
	mp_rebounding = p.getPlayerReboundingRating();
	mp_stealing = p.getPlayerStealingRating();
	mp_blocking = p.getPlayerBlockingRating();
	mp_defending = p.getPlayerDefendingRating();
	setPlayerOverall();

	mp_position = p.getPlayerPosition();
	mp_salary = p.getPlayerSalary();
	mp_yearsPro = p.getPlayerYearsPro();

	mp_energy = p.getPlayerEnergy();
	mp_injury = p.getPlayerInjury();

	mp_team = p.getPlayerTeam();
}

istream& Player::inputPlayer(istream& in) {
	in >> mp_name;
	in >> mp_age;
	in >> mp_overall;
	in >> mp_insideScoring;
	in >> mp_outsideScoring;
	in >> mp_freeThrow;
	in >> mp_passing;
	in >> mp_rebounding;
	in >> mp_stealing;
	in >> mp_blocking;
	in >> mp_defending;

	in >> mp_position;
	in >> mp_salary;
	in >> mp_yearsPro;
	return in;
}
istream& operator>>(istream& in, Player& pl) { return pl.inputPlayer(in); }

ostream& Player::outputPlayer(ostream& out) {
	out << mp_name << " ";
	out << mp_age << " ";
	out << mp_overall << " ";
	out << mp_insideScoring << " ";
	out << mp_outsideScoring << " ";
	out << mp_freeThrow << " ";
	out << mp_passing << " ";
	out << mp_rebounding << " ";
	out << mp_stealing << " ";
	out << mp_blocking << " ";
	out << mp_defending << " ";

	out << mp_position << " ";
	out << mp_salary << " ";
	out << mp_yearsPro << " ";
	return out;
}
ostream& operator<<(ostream& out, Player& pl) { return pl.outputPlayer(out); }

bool operator==(Player p1, Player p2) {
	return (p1.getPlayerName() == p2.getPlayerName());
}
bool operator>(Player p1, Player p2) {
	return (p1.getPlayerOverall() > p2.getPlayerOverall());
}


void Player::showPlayer() {
	cout << mp_name << " ";
	cout << mp_age << "yo ";
	cout << mp_position << " ";
	cout << mp_overall << " Overall" << " ";
	cout << "Sal: " << mp_salary << "M" << endl;
	cout << "S.INS: " << mp_insideScoring << " ";
	cout << "S.OUT: " << mp_outsideScoring << " ";
	cout << "S.FREE: " << mp_freeThrow << " ";
	cout << "PASS: " << mp_passing << " ";
	cout << "REB: " << mp_rebounding << " ";
	cout << "STL: " << mp_stealing << " ";
	cout << "BLK: " << mp_blocking << " ";
	cout << "DEF: " << mp_defending << endl;
}

string Player::salaryForFinances() {
	string str;

	string s = mp_salary;
	s.erase(s.find_last_of("x"), string::npos);

	string m = mp_salary;
	m.erase(0, m.find_last_of("x") + 1);
	for (int i = 0; i < stoi(s); i++) {
		if ((stoi(s) - i) == 1) {
			str = str + m + "M";
		}
		else {
			str = str + m + "M\t";
		}
	}

	return str;
}
