#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<iterator>
#include<algorithm>
#include<stdlib.h>
#include<sstream>
#include<filesystem>

using namespace std;
namespace fs = std::filesystem;



// Class for making a basketball Player
class Player {
private:
	string mp_name;
	int mp_overall;
	int mp_insideScoring;
	int mp_outsideScoring;
	int mp_freeThrow;
	int mp_passing;
	int mp_rebounding;
	int mp_stealing;
	int mp_blocking;
	int mp_defending;

public:
	void setPlayerOverall() { mp_overall = (mp_insideScoring + mp_outsideScoring + mp_freeThrow + mp_passing + mp_rebounding + mp_stealing + mp_blocking + mp_defending) / 8; }

	void setPlayerName(const string val) { mp_name = val; }	
	void setPlayerInsideScoringRating(const int val) { mp_insideScoring = val; setPlayerOverall(); }
	void setPlayerOutsideScoringRating(const int val) { mp_outsideScoring = val; setPlayerOverall(); }
	void setPlayerFreeThrowRating(const int val) { mp_freeThrow = val; setPlayerOverall(); }
	void setPlayerPassingRating(const int val) { mp_passing = val; setPlayerOverall(); }
	void setPlayerReboundingRating(const int val) { mp_rebounding = val; setPlayerOverall(); }
	void setPlayerStealingRating(const int val) { mp_stealing = val; setPlayerOverall(); }
	void setPlayerBlockingRating(const int val) { mp_blocking = val; setPlayerOverall(); }
	void setPlayerDefendingRating(const int val) { mp_defending = val; setPlayerOverall(); }

	string getPlayerName() const { return mp_name; }
	int getPlayerInsideScoringRating() const { return mp_insideScoring; }
	int getPlayerOutsideScoringRating() const { return mp_outsideScoring; }
	int getPlayerFreeThrowRating() const { return mp_freeThrow; }
	int getPlayerPassingRating() const { return mp_passing; }
	int getPlayerReboundingRating() const { return mp_rebounding; }
	int getPlayerStealingRating() const { return mp_stealing; }
	int getPlayerBlockingRating() const { return mp_blocking; }
	int getPlayerDefendingRating() const { return mp_defending; }
	int getPlayerOverall() const { return mp_overall; }

	Player() {
		mp_name = " ";
		mp_overall = 0;
		mp_insideScoring = 0;
		mp_outsideScoring = 0;
		mp_freeThrow = 0;
		mp_passing = 0;
		mp_rebounding = 0;
		mp_stealing = 0;
		mp_blocking = 0;
		mp_defending = 0;
	}

	// explicit constructor without name of a team, may be the player is a Free Agent
	Player(string nmval, int isval, int osval, int ftval, int psval, int rbval, int stval, int blval, int dfval) {
		mp_name = nmval;
		mp_insideScoring = isval;
		mp_outsideScoring = osval;
		mp_freeThrow = ftval;
		mp_passing = psval;
		mp_rebounding = rbval;
		mp_stealing = stval;
		mp_blocking = blval;
		mp_defending = dfval;
		setPlayerOverall();
	}

	Player(const Player& p) {
		mp_name = p.getPlayerName();
		mp_insideScoring = p.getPlayerInsideScoringRating();
		mp_outsideScoring = p.getPlayerOutsideScoringRating();
		mp_freeThrow = p.getPlayerFreeThrowRating();
		mp_passing = p.getPlayerPassingRating();
		mp_rebounding = p.getPlayerReboundingRating();
		mp_stealing = p.getPlayerStealingRating();
		mp_blocking = p.getPlayerBlockingRating();
		mp_defending = p.getPlayerDefendingRating();
		setPlayerOverall();
	}

	// pod vypros ?? za istoriqta na igracha
	istream& inputPlayer(istream& in) {
		in >> mp_name;
		in >> mp_overall;
		in >> mp_insideScoring;
		in >> mp_outsideScoring;
		in >> mp_freeThrow;
		in >> mp_passing;
		in >> mp_rebounding;
		in >> mp_stealing;
		in >> mp_blocking;
		in >> mp_defending;
		return in;
	}
	friend istream& operator>>(istream& in, Player& pl) { return pl.inputPlayer(in); }

	ostream& outputPlayer(ostream& out) {
		out << mp_name << " ";
		out << mp_overall << " ";
		out << mp_insideScoring << " ";
		out << mp_outsideScoring << " ";
		out << mp_freeThrow << " ";
		out << mp_passing << " ";
		out << mp_rebounding << " ";
		out << mp_stealing << " ";
		out << mp_blocking << " ";
		out << mp_defending << endl;
		return out;
	}
	friend ostream& operator<<(ostream& out, Player& pl) { return pl.outputPlayer(out); }


	void showPlayer() {
		cout << mp_name << " ";
		cout << mp_overall << " Overall" << endl;
		cout << "S.INS: " << mp_insideScoring << " ";
		cout << "S.OUT: " << mp_outsideScoring << " ";
		cout << "S.FREE: " << mp_freeThrow << " ";
		cout << "PASS: " << mp_passing << " ";
		cout << "REB: " << mp_rebounding << " ";
		cout << "STL: " << mp_stealing << " ";
		cout << "BLK: " << mp_blocking << " ";
		cout << "DEF: " << mp_defending << endl;
	}
};



// Class for Basketball Teams
class Team {
private:
	string mt_name;
	vector<Player> mt_Players;

public:

	void setTeamName(const string val) { mt_name = val; }
	void setTeamPlayers(const vector<Player> vplay) { mt_Players = vplay; }

	string getTeamName() const { return mt_name; }
	vector<Player> getTeamPlayers() const { return mt_Players; }

	void addPlayerToTeam(Player& p) { Player tp = p; mt_Players.push_back(tp); }

	int getTeamCalcInsideScoring() {
		int res;
		for (auto it = mt_Players.begin(); it != mt_Players.end(); it++) {
			res = res + (*it).getPlayerInsideScoringRating();
		}
		return res / mt_Players.size();
	}

	int getTeamCalcOutsideScoring() {
		int res;
		for (auto it = mt_Players.begin(); it != mt_Players.end(); it++) {
			res = res + (*it).getPlayerOutsideScoringRating();
		}
		return res / mt_Players.size();
	}

	int getTeamCalcFreeThrow() {
		int res;
		for (auto it = mt_Players.begin(); it != mt_Players.end(); it++) {
			res = res + (*it).getPlayerFreeThrowRating();
		}
		return res / mt_Players.size();
	}

	int getTeamCalcPassing() {
		int res;
		for (auto it = mt_Players.begin(); it != mt_Players.end(); it++) {
			res = res + (*it).getPlayerPassingRating();
		}
		return res / mt_Players.size();
	}

	int getTeamCalcRebounding() {
		int res;
		for (auto it = mt_Players.begin(); it != mt_Players.end(); it++) {
			res = res + (*it).getPlayerReboundingRating();
		}
		return res / mt_Players.size();
	}

	int getTeamCalcStealing() {
		int res;
		for (auto it = mt_Players.begin(); it != mt_Players.end(); it++) {
			res = res + (*it).getPlayerStealingRating();
		}
		return res / mt_Players.size();
	}

	int getTeamCalcBlocking() {
		int res;
		for (auto it = mt_Players.begin(); it != mt_Players.end(); it++) {
			res = res + (*it).getPlayerBlockingRating();
		}
		return res / mt_Players.size();
	}

	int getTeamCalcDefending() {
		int res;
		for (auto it = mt_Players.begin(); it != mt_Players.end(); it++) {
			res = res + (*it).getPlayerDefendingRating();
		}
		return res / mt_Players.size();
	}

	int getTeamCalcOverall() {
		int res;
		for (auto it = mt_Players.begin(); it != mt_Players.end(); it++) {
			res = res + (*it).getPlayerOverall();
		}
		return res / mt_Players.size();
	}


	Team() {
		mt_name = " ";
		mt_Players.clear();
	}

	// Reading players from file
	Team(string fname) {
		fstream fp;
		fp.open(fname, ios::in);
		if (!fp) {
			cout << endl << "******* ERROR *******";
			exit(1);
		}

		string line;
		int rating = 0;

		if (fp.is_open()) {
			while (getline(fp, line)) {
				Player pl;
				getline(fp, line);
				
			}
			fp.close();
		}
	}

	Team(string tmval, vector<Player> vplay) {
		mt_name = tmval;
		mt_Players = vplay;
	}

	Team(Team& tm) {
		mt_name = tm.getTeamName();
		mt_Players = tm.getTeamPlayers();
	}

	/*istream& inputTeam(istream& in) {
		in >> mt_name;
		in >> mt_coach;
		int siz = 0;
		in >> siz;
		for (int i = 0; i < siz; i++) {
			Player pl;
			in >> pl;
			mt_Players.push_back(pl);
		}
		return in;
	}
	friend istream& operator>>(istream& in, Team& tm) { return tm.inputTeam(in); }

	ostream& outputTeam(ostream& out) {
		out << mt_name << endl;
		out << mt_coach << endl;
		out << mt_Players.size() << endl;
		for (auto it = mt_Players.begin(); it != mt_Players.end(); it++) {
			out << (*it);
		}
		return out;
	}
	friend ostream& operator<<(ostream& out, Team& tm) { return tm.outputTeam(out); }
*/
};



// function for making a main team from chosen file
void makeTeamMain(string fname, Team& gameTeam) {
	string line;
	string tempName;
	int rating;
	int i;

	ifstream chFile(fname, ios::in);
	if (!chFile) {
		cout << endl << "******* ERROR *******";
		exit(1);
	}

	while (getline(chFile, line)) {
		i = 0;
		stringstream ss(line);
		string word;
		Player tempP;

		while (getline(ss, word, ' ')) {
			if (i < 2) {
				if (i == 1) {
					tempName = tempName + " " + word;
					tempP.setPlayerName(tempName);
				}
				else {
					tempName = word;
				}
			}

			// setting the inside scoring rating of the player
			if (i == 2) {
				string st = word;
				rating = stoi(st);
				tempP.setPlayerInsideScoringRating(rating);
			}

			// setting the outside scoring rating of the player
			if (i == 3) {
				string st = word;
				rating = stoi(st);
				tempP.setPlayerOutsideScoringRating(rating);
			}

			// setting the free throw rating of the player
			if (i == 4) {
				string st = word;
				rating = stoi(st);
				tempP.setPlayerFreeThrowRating(rating);
			}

			// setting the passing rating of the player
			if (i == 5) {
				string st = word;
				rating = stoi(st);
				tempP.setPlayerPassingRating(rating);
			}

			// setting the rebounding rating of the player
			if (i == 6) {
				string st = word;
				rating = stoi(st);
				tempP.setPlayerReboundingRating(rating);
			}

			// setting the stealing rating of the player
			if (i == 7) {
				string st = word;
				rating = stoi(st);
				tempP.setPlayerStealingRating(rating);
			}

			// setting the blocking rating of the player
			if (i == 8) {
				string st = word;
				rating = stoi(st);
				tempP.setPlayerBlockingRating(rating);
			}

			// setting the defending rating of the player
			if (i == 9) {
				string st = word;
				rating = stoi(st);
				tempP.setPlayerDefendingRating(rating);
			}

			i++;
		}
		gameTeam.addPlayerToTeam(tempP);
	}
}



void startMenu();
void gameManu(string chosenGame, Team& tempTeam);

// Main function
int main() {
	startMenu();
	return 0;
}



// Start Menu function =========
void startMenu() {
	fstream fp;
	int chTeam;
	const char* tempChar;
	string line;
	int i = 0;

	Team tempMenuTeam;
	vector<Player> vtemp;

	//Case 1
	string leagueName;
	int dontLikeTeam;
	bool flagDontLikeTeam = false;

	//Case 2
	string gameName;
	bool flagFullDirectoryGames = false;

	int choice = 0;
	do {
		do {
			system("cls");
			cout << "===========================================" << endl;
			cout << "==================MENU=====================" << endl;
			cout << "1. Make a new League" << endl;
			cout << "2. Continue League" << endl;
			cout << "End" << endl;
			cout << "===========================================" << endl;
			cout << "-: ";
			cin >> choice;
			switch (choice) {

				// case make a new league
			case 1:
				system("cls");
				cout << "Enter your league name: ";
				cin >> leagueName;

				//fs::create_directory("Games/" + leagueName);

				// repeating until user likes a team
				do {
					cout << endl << "Pick your Team" << endl;
					fp.open("Teams.txt", ios::in);
					if (fp.is_open()) {
						i = 0;
						while (getline(fp, line)) {
							i++;
							cout << i << " - " << line << endl;
						}
						fp.close();
					}
					cout << "-: ";
					cin >> chTeam;

					switch (chTeam) {
					case 1:

						// check if user want this team by showing the roster
						fp.open("AllTeams/Celtics.txt", ios::in);
						if (!fp) {
							cout << endl << "******* ERROR *******";
							exit(1);
						}
						if (fp.is_open()) {
							cout << endl << "players" << endl;
							while (getline(fp, line)) {
								cout << line << endl;
							}
							fp.close();
						}

						cout << endl << "Do you like this team? (1-Yes , 0-No): ";
						cin >> dontLikeTeam;

						if (dontLikeTeam == 0) { 
							flagDontLikeTeam = true;
							system("cls");
							cout << "Enter your league name: " << endl << leagueName << endl;
						}
						else {

							makeTeamMain("AllTeams/Celtics.txt", tempMenuTeam);

							cout << endl << "players" << endl;
							vtemp = tempMenuTeam.getTeamPlayers();
							for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
								(*it).showPlayer();
								cout << endl;
							}

							//string temp = leagueName + "_Main_Team_.txt";

							fs::path pth{ ("Games/" + leagueName) };
							pth /= "_Main_Team_.txt";
							fs::create_directory(pth.parent_path());

							fp.open(pth, fstream::trunc | fstream::out);
							if (!fp) {
								cout << endl << "******* ERROR *******";
								exit(1);
							}
							if (fp.is_open()) {
								fp << "Celtics.txt";
								fp.close();
							}

							fs::copy("AllTeams", leagueName);
							
							//gameManu()

							system("pause");
							flagDontLikeTeam = false;
						}
						break;

					case 2: break;
					case 3: break;
					case 4: break;
					case 5: break;
					case 6: break;
					case 7: break;
					case 8: break;
					case 9: break;
					case 10: break;
					case 11: break;
					case 12: break;
					case 13: break;
					case 14: break;
					case 15: break;
					case 16: break;
					case 17: break;
					case 18: break;
					case 19: break;
					case 20: break;
					case 21: break;
					case 22: break;
					case 23: break;
					case 24: break;
					case 25: break;
					case 26: break;
					case 27: break;
					case 28: break;
					case 29: break;
					case 30: break;
					} // close team switch

				}while (flagDontLikeTeam == true); // close do while for picking a team

				break; // close case make a new league

				// case continue existing game
			case 2:
				system("cls");
				cout << "===== All Your Games =====" << endl;
				for (auto& p : fs::directory_iterator("Games")) {
					if (p.is_directory()) {
						gameName = p.path().string();
						gameName.erase(0, 6);
						cout << gameName << endl;
						flagFullDirectoryGames = true;
					}
				}
				if (flagFullDirectoryGames == false) {
					cout << "Currently you dont have games";
				}
				else {
					string chosenGame;
					cout << "Pick your game by name: ";
					cin >> chosenGame;

					for (auto& p : fs::directory_iterator("Games")) {
						if (p.is_directory()) {
							gameName = p.path().string();
							gameName.erase(0, 6);
							if (gameName == chosenGame) {
								Team tempTeam;
								gameManu(chosenGame, tempTeam);
							}
						}
					}
				}

				system("pause");
				break; // close case continue existing game

			default: exit(1); break;
			}
		} while (true);
	} while (true);
}



// Game Menu function when you enter a started game
void gameManu(string chosenGame, Team& tempTeam) {
	Team myTeam = tempTeam;
}
