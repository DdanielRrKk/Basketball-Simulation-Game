#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<filesystem>
#include<cstdlib>
#include<ctime>

#include"gamesClass.h"
#include"teamClass.h"

using namespace std;
namespace fs = std::filesystem;

void Games::setGamesNumber(const int val) { mg_gamesNumber = val; }
void Games::setGamesHomeTeam(const vector<PlayerStats> vp) { mg_homeTeam = vp; }
void Games::setGamesAwayTeam(const vector<PlayerStats> vp) { mg_awayTeam = vp; }

int Games::getGamesNumber() const { return mg_gamesNumber; }
vector<PlayerStats> Games::getGamesHomeTeam() const { return mg_homeTeam; }
vector<PlayerStats> Games::getGamesAwayTeam() const { return mg_awayTeam; }

void Games::simulateGame(int day, string& gmPath, Team& ht, Team& at) {
	srand((unsigned int)time(NULL));

	vector<Player> htp = ht.getTeamPlayers();
	vector<Player> atp = at.getTeamPlayers();
	int numb = 0;
	int i = 0;
	int minutes = 0;

	int htscore = 0;
	int atscore = 0;

	double mvpPER = 0.0; string mvpName;
	int mostpts = 0; string ptsName;
	int mostass = 0; string assName;
	int mostreb = 0; string rebName;
	int moststl = 0; string stlName;
	int mostblk = 0; string blkName;
	//system("cls");
	for (auto it = htp.begin(); it != htp.end(); it++) {
		int pts = 0;
		int ass = 0;
		int reb = 0;
		int stl = 0;
		int blk = 0;
		int fol = 0;
		int tov = 0;
		int fta = 0;
		int ftm = 0;
		int fga = 0;
		int fgm = 0;
		int tpta = 0;
		int tptm = 0;

		if (i < 5) { minutes = 35; }
		else if (i < 10) { minutes = 13; }
		else { break; }

		// zadavame minutite na igracha koito shte igrae i simulirame da vidim shansovete koito ima da napravi neshto
		// shte go napravq za pyrvite 5 igracha
		for (int i = 0; i < minutes; i++) {

			// random number if the player scores or passes
			numb = rand() % 101;
			if (40 >= numb) {

				// random number for fg, ft or tpt
				numb = rand() % 101;
				if (50 >= numb) { // FG
					numb = rand() % 75 + 25;
					if ((*it).getPlayerInsideScoringRating() >= numb) {
						pts = pts + 2;
						fga++;
						fgm++;
					}
					else {
						fga++;

						numb = rand() % 75 + 25;
						if ((*it).getPlayerReboundingRating() >= numb) {
							reb++;
						}
					}
				}
				else if (70 >= numb) { // TPT
					numb = rand() % 75 + 25;
					if ((*it).getPlayerOutsideScoringRating() >= numb) {
						pts = pts + 3;
						tpta++;
						tptm++;
					}
					else {
						tpta++;

						numb = rand() % 75 + 25;
						if ((*it).getPlayerReboundingRating() >= numb) {
							reb++;
						}
					}
				}
				else { // FT
					numb = rand() % 75 + 25;
					if ((*it).getPlayerFreeThrowRating() >= numb) {
						pts = pts + 1;
						fta++;
						ftm++;
					}
					else {
						fta++;

						numb = rand() % 75 + 25;
						if ((*it).getPlayerReboundingRating() >= numb) {
							reb++;
						}
					}
				}
			}
			else if (80 >= numb) { // passing
				numb = rand() % 101;
				if (50 >= numb) {
					numb = rand() % 75 + 25;
					if ((*it).getPlayerPassingRating() >= numb) { // ASS
						ass++;
					}
					else {
						numb = rand() % 101;
						if (50 < numb) { // TO
							tov++;
						}
						else {
							// nothing
						}
					}
				}
				else {
					// nothing
				}
			}
			else {
				// nothing
			}

			//random number for rebounding or defensive play
			numb = rand() % 101;
			if (30 >= numb) {
				numb = rand() % 75 + 25;
				if ((*it).getPlayerReboundingRating() >= numb) {
					reb++;
				}
			}
			else if (60 >= numb) {
				// random number for choosing steal or block
				numb = rand() % 101;
				if (20 >= numb) {
					numb = rand() % 75 + 25;
					if ((*it).getPlayerStealingRating() >= numb) {
						stl++;
					}
				}
				else if (40 >= numb) {
					numb = rand() % 75 + 25;
					if ((*it).getPlayerBlockingRating() >= numb) {
						blk++;
					}
				}
				else {
					// nothing
				}
			}
			else {
				// nothing
			}

		}

		PlayerStats hps(pts, ass, reb, stl, blk, minutes, tov, fta, ftm, fga, fgm, tpta, tptm);
		(*it).setPlayerStats(hps);
		//hps.showPlayerStats();

		htscore = htscore + pts;

		if (hps.getStatTotalPoints() > mostpts) { mostpts = hps.getStatTotalPoints(); ptsName = (*it).getPlayerName(); }
		if (hps.getStatTotalAssists() > mostass) { mostass = hps.getStatTotalAssists(); assName = (*it).getPlayerName(); }
		if (hps.getStatTotalRebounds() > mostreb) { mostreb = hps.getStatTotalRebounds(); rebName = (*it).getPlayerName(); }
		if (hps.getStatTotalSteals() > moststl) { moststl = hps.getStatTotalSteals(); stlName = (*it).getPlayerName(); }
		if (hps.getStatTotalBlocks() > mostblk) { mostblk = hps.getStatTotalBlocks(); blkName = (*it).getPlayerName(); }
		if (hps.getStatPER() > mvpPER) { mvpPER = hps.getStatPER(); mvpName = (*it).getPlayerName(); }
		
		i++;
	}

	i = 0;
	for (auto it = atp.begin(); it != atp.end(); it++) {
		int pts = 0;
		int ass = 0;
		int reb = 0;
		int stl = 0;
		int blk = 0;
		int fol = 0;
		int tov = 0;
		int fta = 0;
		int ftm = 0;
		int fga = 0;
		int fgm = 0;
		int tpta = 0;
		int tptm = 0;

		if (i < 5) { minutes = 35; }
		else if (i < 10) { minutes = 13; }
		else { break; }

		// zadavame minutite na igracha koito shte igrae i simulirame da vidim shansovete koito ima da napravi neshto
		// shte go napravq za pyrvite 5 igracha
		for (int i = 0; i < minutes; i++) {

			// random number if the player scores or passes
			numb = rand() % 101;
			if (40 >= numb) {

				// random number for fg, ft or tpt
				numb = rand() % 101;
				if (50 >= numb) { // FG
					numb = rand() % 75 + 25;
					if ((*it).getPlayerInsideScoringRating() >= numb) {
						pts = pts + 2;
						fga++;
						fgm++;
					}
					else {
						fga++;

						numb = rand() % 75 + 25;
						if ((*it).getPlayerReboundingRating() >= numb) {
							reb++;
						}
					}
				}
				else if (70 >= numb) { // TPT
					numb = rand() % 75 + 25;
					if ((*it).getPlayerOutsideScoringRating() >= numb) {
						pts = pts + 3;
						tpta++;
						tptm++;
					}
					else {
						tpta++;

						numb = rand() % 75 + 25;
						if ((*it).getPlayerReboundingRating() >= numb) {
							reb++;
						}
					}
				}
				else { // FT
					numb = rand() % 75 + 25;
					if ((*it).getPlayerFreeThrowRating() >= numb) {
						pts = pts + 1;
						fta++;
						ftm++;
					}
					else {
						fta++;

						numb = rand() % 75 + 25;
						if ((*it).getPlayerReboundingRating() >= numb) {
							reb++;
						}
					}
				}
			}
			else if (80 >= numb) { // passing
				numb = rand() % 101;
				if (50 >= numb) {
					numb = rand() % 75 + 25;
					if ((*it).getPlayerPassingRating() >= numb) { // ASS
						ass++;
					}
					else {
						numb = rand() % 101;
						if (50 < numb) { // TO
							tov++;
						}
						else {
							// nothing
						}
					}
				}
				else {
					// nothing
				}
			}
			else {
				// nothing
			}

			//random number for rebounding or defensive play
			numb = rand() % 101;
			if (30 >= numb) {
				numb = rand() % 75 + 25;
				if ((*it).getPlayerReboundingRating() >= numb) {
					reb++;
				}
			}
			else if (60 >= numb) {
				// random number for choosing steal or block
				numb = rand() % 101;
				if (20 >= numb) {
					numb = rand() % 75 + 25;
					if ((*it).getPlayerStealingRating() >= numb) {
						stl++;
					}
				}
				else if (40 >= numb) {
					numb = rand() % 75 + 25;
					if ((*it).getPlayerBlockingRating() >= numb) {
						blk++;
					}
				}
				else {
					// nothing
				}
			}
			else {
				// nothing
			}

		}

		PlayerStats aps(pts, ass, reb, stl, blk, minutes, tov, fta, ftm, fga, fgm, tpta, tptm);
		(*it).setPlayerStats(aps);
		//aps.showPlayerStats();

		atscore = atscore + pts;

		if (aps.getStatTotalPoints() > mostpts) { mostpts = aps.getStatTotalPoints(); ptsName = (*it).getPlayerName(); }
		if (aps.getStatTotalAssists() > mostass) { mostass = aps.getStatTotalAssists(); assName = (*it).getPlayerName(); }
		if (aps.getStatTotalRebounds() > mostreb) { mostreb = aps.getStatTotalRebounds(); rebName = (*it).getPlayerName(); }
		if (aps.getStatTotalSteals() > moststl) { moststl = aps.getStatTotalSteals(); stlName = (*it).getPlayerName(); }
		if (aps.getStatTotalBlocks() > mostblk) { mostblk = aps.getStatTotalBlocks(); blkName = (*it).getPlayerName(); }
		if (aps.getStatPER() > mvpPER) { mvpPER = aps.getStatPER(); mvpName = (*it).getPlayerName(); }


		i++;
	}
	//system("cls");

	cout << ht.getTeamName() << " " << htscore << " - " << atscore << " " << at.getTeamName() << endl;
	cout << "MVP: " << mvpName << " PER: " << mvpPER << endl;
	cout << "PTS: " << mostpts << "  " << ptsName << endl;
	cout << "ASS: " << mostass << "  " << assName << endl;
	cout << "REB: " << mostreb << "  " << rebName << endl;
	cout << "STL: " << moststl << "  " << assName << endl;
	cout << "BLK: " << mostblk << "  " << blkName << endl;
	cout << endl;
	//system("pause");

	if (htscore != atscore) {
		if (htscore < atscore) { at.addTeamWin(); ht.addTeamLoss(); }
		else{ ht.addTeamWin(); at.addTeamLoss(); }

		fs::path pth{ (gmPath + "/Games") };
		string fname = to_string(day) + ht.getTeamName() + "v" + at.getTeamName() + ".txt";

		pth /= fname;
		fs::create_directory(pth.parent_path());

		fstream fp(pth.string(), ios::out);
		fp << ht.getTeamName() << endl << htscore << endl;
		for (auto it = htp.begin(); it != htp.end(); it++) {
			PlayerStats pls = (*it).getPlayerStats();
			fp << (*it).getPlayerName() << " " << pls;
		}
		fp << at.getTeamName() << endl << atscore << endl;
		for (auto it = atp.begin(); it != atp.end(); it++) {
			PlayerStats pls = (*it).getPlayerStats();
			fp << (*it).getPlayerName() << " " << pls;
		}
		fp.close();
	}
	else {
		simulateGame(day, gmPath, ht, at);
	}
}

void Games::simulateTime(int days, string& gmPath, vector<Team>& teamVec) {
	system("cls");

	vector<Team> teamV = teamVec;
	vector<string> gamesVec;
	int currentDay = getInfoDay(gmPath);

	fstream fp("shed.txt", ios::in);
	if (!fp) {
		cout << endl << "******* ERROR *******";
		exit(1);
	}
	if (fp.is_open()) {
		string line;
		int insideCount = 0;

		getline(fp, line);
		while (insideCount != (currentDay + days)) {
			if (insideCount > currentDay - 1) { gamesVec.push_back(line); }
			if (line == "no") { insideCount++; }
			getline(fp, line);
		}
		fp.close();
	}

	int iDay = currentDay + 1;

	cout << endl << "------Day " << iDay << "------" << endl;
	for (auto it = gamesVec.begin(); it != gamesVec.end(); it++) {
		if (*it != "no") {
			string htm = *it;
			htm.erase(0, htm.find_last_of("-") + 1);

			string atm = *it;
			atm.erase(atm.find_last_of("-"), string::npos);

			Team ta, th;

			for (auto itr = teamV.begin(); itr != teamV.end(); itr++) {
				if ((*itr).getTeamName() == atm) {
					ta = (*itr);
				}
				if ((*itr).getTeamName() == htm) {
					th = (*itr);
				}
			}

			simulateGame(iDay, gmPath, th, ta);

			for (auto itr = teamV.begin(); itr != teamV.end(); itr++) {
				if ((*itr).getTeamName() == atm) {
					(*itr) = ta;
				}
				if ((*itr).getTeamName() == htm) {
					(*itr) = th;
				}
			}

		}
		else {
			system("pause");
			system("cls");
			iDay++;
			if (iDay <= currentDay + days) { cout << endl << "------Day " << iDay << "------" << endl; }
		}
	}
	system("pause");

	setInfoDay((currentDay + days), gmPath);
	teamVec = teamV;
}

int Games::getInfoDay(string gmPath) const {
	string line;
	fs::path pth{ (gmPath) };
	pth /= "_Info_.txt";

	fstream fp(pth.string(), ios::in);
	if (!fp) {
		cout << endl << "******* ERROR *******";
		exit(1);
	}
	if (fp.is_open()) {
		getline(fp, line);
		getline(fp, line);
		fp.close();
	}

	return stoi(line);
}

void Games::setInfoDay(const int val, string gmPath) {
	string line;
	fs::path pth{ (gmPath) };
	pth /= "_Info_.txt";

	fstream fp(pth.string(), ios::in);
	if (!fp) {
		cout << endl << "******* ERROR *******";
		exit(1);
	}
	if (fp.is_open()) {
		getline(fp, line);
		fp.close();
	}

	fp.open(pth.string(), ios::out);
	if (!fp) {
		cout << endl << "******* ERROR *******";
		exit(1);
	}
	if (fp.is_open()) {
		fp << line << endl;
		fp << val << endl;
		fp.close();
	}

}