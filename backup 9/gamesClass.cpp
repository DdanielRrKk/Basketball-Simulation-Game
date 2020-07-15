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

void Games::simulateGame(int day, string gmPath, Team ht, Team at) {
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
			if (30 >= numb) {

				// random number for fg, ft or tpt
				numb = rand() % 101;
				if (50 >= numb) { // FG
					numb = rand() % 101;
					if ((*it).getPlayerInsideScoringRating() >= numb) {
						pts = pts + 2;
						fga++;
						fgm++;
					}
					else {
						fga++;

						numb = rand() % 101;
						if ((*it).getPlayerReboundingRating() >= numb) {
							reb++;
						}
					}
				}
				else if (70 >= numb) { // TPT
					numb = rand() % 101;
					if ((*it).getPlayerOutsideScoringRating() >= numb) {
						pts = pts + 3;
						tpta++;
						tptm++;
					}
					else {
						tpta++;

						numb = rand() % 101;
						if ((*it).getPlayerReboundingRating() >= numb) {
							reb++;
						}
					}
				}
				else { // FT
					numb = rand() % 101;
					if ((*it).getPlayerFreeThrowRating() >= numb) {
						pts = pts + 1;
						fta++;
						ftm++;
					}
					else {
						fta++;

						numb = rand() % 101;
						if ((*it).getPlayerReboundingRating() >= numb) {
							reb++;
						}
					}
				}
			}
			else if (60 >= numb) { // passing
				numb = rand() % 101;
				if (50 >= numb) {
					numb = rand() % 101;
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
			if (20 >= numb) {
				numb = rand() % 101;
				if ((*it).getPlayerReboundingRating() >= numb) {
					reb++;
				}
			}
			else if (40 >= numb) {
				// random number for choosing steal or block
				numb = rand() % 101;
				if (20 >= numb) {
					numb = rand() % 101;
					if ((*it).getPlayerStealingRating() >= numb) {
						stl++;
					}
				}
				else if (40 >= numb) {
					numb = rand() % 101;
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
			if (30 >= numb) {

				// random number for fg, ft or tpt
				numb = rand() % 101;
				if (50 >= numb) { // FG
					numb = rand() % 101;
					if ((*it).getPlayerInsideScoringRating() >= numb) {
						pts = pts + 2;
						fga++;
						fgm++;
					}
					else {
						fga++;

						numb = rand() % 101;
						if ((*it).getPlayerReboundingRating() >= numb) {
							reb++;
						}
					}
				}
				else if (70 >= numb) { // TPT
					numb = rand() % 101;
					if ((*it).getPlayerOutsideScoringRating() >= numb) {
						pts = pts + 3;
						tpta++;
						tptm++;
					}
					else {
						tpta++;

						numb = rand() % 101;
						if ((*it).getPlayerReboundingRating() >= numb) {
							reb++;
						}
					}
				}
				else { // FT
					numb = rand() % 101;
					if ((*it).getPlayerFreeThrowRating() >= numb) {
						pts = pts + 1;
						fta++;
						ftm++;
					}
					else {
						fta++;

						numb = rand() % 101;
						if ((*it).getPlayerReboundingRating() >= numb) {
							reb++;
						}
					}
				}
			}
			else if (60 >= numb) { // passing
				numb = rand() % 101;
				if (50 >= numb) {
					numb = rand() % 101;
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
			if (20 >= numb) {
				numb = rand() % 101;
				if ((*it).getPlayerReboundingRating() >= numb) {
					reb++;
				}
			}
			else if (40 >= numb) {
				// random number for choosing steal or block
				numb = rand() % 101;
				if (20 >= numb) {
					numb = rand() % 101;
					if ((*it).getPlayerStealingRating() >= numb) {
						stl++;
					}
				}
				else if (40 >= numb) {
					numb = rand() % 101;
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
	system("cls");

	cout << ht.getTeamName() << " " << htscore << " - " << atscore << " " << at.getTeamName() << endl;
	cout << "MVP: " << mvpName << " PER: " << mvpPER << endl;
	cout << "PTS: " << mostpts << "  " << ptsName << endl;
	cout << "ASS: " << mostass << "  " << assName << endl;
	cout << "REB: " << mostreb << "  " << rebName << endl;
	cout << "STL: " << moststl << "  " << assName << endl;
	cout << "BLK: " << mostblk << "  " << blkName << endl;

	system("pause");

	fs::path pth{ (gmPath + "/Games") };
	string fname = to_string(day) + ht.getTeamName() + at.getTeamName() + ".txt";

	pth /= fname;
	fs::create_directory(pth.parent_path());

	fstream fp(pth.string(), ios::out);
	fp << ht.getTeamName() << " " << htscore << endl;
	for (auto it = htp.begin(); it != htp.end(); it++) {
		PlayerStats pls = (*it).getPlayerStats();
		fp << (*it).getPlayerName() << " " << pls;
	}
	fp << at.getTeamName() << " " << atscore << endl;
	for (auto it = atp.begin(); it != atp.end(); it++) {
		PlayerStats pls = (*it).getPlayerStats();
		fp << (*it).getPlayerName() << " " << pls;
	}
}
