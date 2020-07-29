#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<iterator>
#include<algorithm>
#include<stdlib.h>
#include<sstream>
#include<filesystem>
#include<iomanip>

#include"playerStatsClass.h"
#include"playerClass.h"
#include"teamClass.h"
#include"gamesClass.h"
#include"startMenu.h"
#include"gameMenu.h"

using namespace std;
namespace fs = std::filesystem;

// function for making a main team from chosen file
void fromFileToTeam(string fname, Team& gameTeam) {
	string line;
	string tempName;
	int rating;
	int i;

	string s = fname;
	s.erase(0, s.find_last_of("\\") + 1);
	s.erase(s.find_last_of("."), string::npos);
	gameTeam.setTeamName(s);

	fstream chFile(fname, ios::in);
	if (!chFile) {
		cout << endl << "******* ERROR *******";
		exit(1);
	}

	while (getline(chFile, line)) {
		i = 0;
		stringstream ss(line);
		string word;
		Player tempP;

		tempP.setPlayerTeam(s);

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

			// setting the age of the player
			if (i == 2) {
				string st = word;
				rating = stoi(st);
				tempP.setPlayerAge(rating);
			}

			// setting the inside scoring rating of the player
			if (i == 3) {
				string st = word;
				rating = stoi(st);
				tempP.setPlayerInsideScoringRating(rating);
			}

			// setting the outside scoring rating of the player
			if (i == 4) {
				string st = word;
				rating = stoi(st);
				tempP.setPlayerOutsideScoringRating(rating);
			}

			// setting the free throw rating of the player
			if (i == 5) {
				string st = word;
				rating = stoi(st);
				tempP.setPlayerFreeThrowRating(rating);
			}

			// setting the passing rating of the player
			if (i == 6) {
				string st = word;
				rating = stoi(st);
				tempP.setPlayerPassingRating(rating);
			}

			// setting the rebounding rating of the player
			if (i == 7) {
				string st = word;
				rating = stoi(st);
				tempP.setPlayerReboundingRating(rating);
			}

			// setting the stealing rating of the player
			if (i == 8) {
				string st = word;
				rating = stoi(st);
				tempP.setPlayerStealingRating(rating);
			}

			// setting the blocking rating of the player
			if (i == 9) {
				string st = word;
				rating = stoi(st);
				tempP.setPlayerBlockingRating(rating);
			}

			// setting the defending rating of the player
			if (i == 10) {
				string st = word;
				rating = stoi(st);
				tempP.setPlayerDefendingRating(rating);
			}

			// setting the position of the player
			if (i == 11) {
				tempP.setPlayerPosition(word);
			}

			// setting the salary of the player
			if (i == 12) {
				tempP.setPlayerSalary(word);
			}

			// setting the years pro of the player
			if (i == 13) {
				string st = word;
				rating = stoi(st);
				tempP.setPlayerYearsPro(rating);
			}

			i++;
		}
		gameTeam.addPlayerToTeam(tempP);
	}
}



// Start Menu functio for continuing game
void continueGame() {
	string gameName;
	bool flagFullDirectoryGames = false;

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
		cout << endl << "Pick your game by name: ";
		cin.ignore(1, '\n');
		getline(cin, chosenGame);

		for (auto& p : fs::directory_iterator("Games")) {
			if (p.is_directory()) {
				gameName = p.path().string();
				gameName.erase(0, 6);
				if (gameName == chosenGame) {
					gameMenu(chosenGame);
				}
			}
		}
	}
}



// Start Menu function for making a league
void makingALeague() {
	fstream fp;
	int chTeam;
	string line;
	int i = 0;
	string teamName;
	string tnm;
	int dontLikeTeam;

	string leagueName;
	bool flagDontLikeTeam = false;

	fs::path pthComp;
	do {
		system("cls");

		if (fs::exists(pthComp) == true) {
			cout << "This name already exists, try new one!" << endl << endl;
		}

		cout << "Enter your league name: ";
		cin.ignore(1, '\n');
		getline(cin, leagueName);

		pthComp /= ("Games/" + leagueName);
	} while (fs::exists(pthComp) == true);

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
			teamName = "AllTeams/BOS.txt";
			tnm = "BOS.txt";

			// check if user want this team by showing the roster
			fp.open(teamName, ios::in);
			if (!fp) {
				cout << endl << "******* ERROR *******";
				exit(1);
			}
			if (fp.is_open()) {
				Team tempMenuTeam;
				vector<Player> vtemp;

				fromFileToTeam(teamName, tempMenuTeam);

				cout << endl << "players" << endl << endl;
				vtemp = tempMenuTeam.getTeamPlayers();
				for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
					(*it).showPlayer();
					cout << endl;
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

				fs::path pth{ ("Games/" + leagueName) };
				pth /= "_Main_Team_.txt";
				fs::create_directory(pth.parent_path());

				fs::path pth_i{ ("Games/" + leagueName) };
				pth_i /= "_Info_.txt";
				fs::create_directory(pth_i.parent_path());

				fs::path pth_h{ ("Games/" + leagueName) };
				pth_h /= "History";
				fs::create_directory(pth_h);

				fs::path pth_g{ ("Games/" + leagueName) };
				pth_g /= "Games";
				fs::create_directory(pth_g);

				fp.open(pth, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << tnm;
					fp.close();
				}

				fp.open(pth_i, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << 1 << endl << 0 << endl;
					fp.close();
				}

				fs::copy("AllTeams", ("Games/" + leagueName));

				gameMenu(leagueName);

				system("pause");
				flagDontLikeTeam = false;
			}
			break;

		case 2:
			teamName = "AllTeams/BRO.txt";
			tnm = "BRO.txt";

			// check if user want this team by showing the roster
			fp.open(teamName, ios::in);
			if (!fp) {
				cout << endl << "******* ERROR *******";
				exit(1);
			}
			if (fp.is_open()) {
				Team tempMenuTeam;
				vector<Player> vtemp;

				fromFileToTeam(teamName, tempMenuTeam);

				cout << endl << "players" << endl << endl;
				vtemp = tempMenuTeam.getTeamPlayers();
				for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
					(*it).showPlayer();
					cout << endl;
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

				fs::path pth{ ("Games/" + leagueName) };
				pth /= "_Main_Team_.txt";
				fs::create_directory(pth.parent_path());

				fs::path pth_i{ ("Games/" + leagueName) };
				pth_i /= "_Info_.txt";
				fs::create_directory(pth_i.parent_path());

				fs::path pth_h{ ("Games/" + leagueName) };
				pth_h /= "History";
				fs::create_directory(pth_h);

				fs::path pth_g{ ("Games/" + leagueName) };
				pth_g /= "Games";
				fs::create_directory(pth_g);

				fp.open(pth, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << tnm;
					fp.close();
				}

				fp.open(pth_i, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << 1 << endl << 0 << endl;
					fp.close();
				}

				fs::copy("AllTeams", ("Games/" + leagueName));

				gameMenu(leagueName);

				system("pause");
				flagDontLikeTeam = false;
			}
			break;

		case 3:
			teamName = "AllTeams/NYK.txt";
			tnm = "NYK.txt";

			// check if user want this team by showing the roster
			fp.open(teamName, ios::in);
			if (!fp) {
				cout << endl << "******* ERROR *******";
				exit(1);
			}
			if (fp.is_open()) {
				Team tempMenuTeam;
				vector<Player> vtemp;

				fromFileToTeam(teamName, tempMenuTeam);

				cout << endl << "players" << endl << endl;
				vtemp = tempMenuTeam.getTeamPlayers();
				for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
					(*it).showPlayer();
					cout << endl;
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

				fs::path pth{ ("Games/" + leagueName) };
				pth /= "_Main_Team_.txt";
				fs::create_directory(pth.parent_path());

				fs::path pth_i{ ("Games/" + leagueName) };
				pth_i /= "_Info_.txt";
				fs::create_directory(pth_i.parent_path());

				fs::path pth_h{ ("Games/" + leagueName) };
				pth_h /= "History";
				fs::create_directory(pth_h);

				fs::path pth_g{ ("Games/" + leagueName) };
				pth_g /= "Games";
				fs::create_directory(pth_g);

				fp.open(pth, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << tnm;
					fp.close();
				}

				fp.open(pth_i, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << 1 << endl << 0 << endl;
					fp.close();
				}

				fs::copy("AllTeams", ("Games/" + leagueName));

				gameMenu(leagueName);

				system("pause");
				flagDontLikeTeam = false;
			}
			break;

		case 4:
			teamName = "AllTeams/PHI.txt";
			tnm = "PHI.txt";

			// check if user want this team by showing the roster
			fp.open(teamName, ios::in);
			if (!fp) {
				cout << endl << "******* ERROR *******";
				exit(1);
			}
			if (fp.is_open()) {
				Team tempMenuTeam;
				vector<Player> vtemp;

				fromFileToTeam(teamName, tempMenuTeam);

				cout << endl << "players" << endl << endl;
				vtemp = tempMenuTeam.getTeamPlayers();
				for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
					(*it).showPlayer();
					cout << endl;
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

				fs::path pth{ ("Games/" + leagueName) };
				pth /= "_Main_Team_.txt";
				fs::create_directory(pth.parent_path());

				fs::path pth_i{ ("Games/" + leagueName) };
				pth_i /= "_Info_.txt";
				fs::create_directory(pth_i.parent_path());

				fs::path pth_h{ ("Games/" + leagueName) };
				pth_h /= "History";
				fs::create_directory(pth_h);

				fs::path pth_g{ ("Games/" + leagueName) };
				pth_g /= "Games";
				fs::create_directory(pth_g);

				fp.open(pth, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << tnm;
					fp.close();
				}

				fp.open(pth_i, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << 1 << endl << 0 << endl;
					fp.close();
				}

				fs::copy("AllTeams", ("Games/" + leagueName));

				gameMenu(leagueName);

				system("pause");
				flagDontLikeTeam = false;
			}
			break;

		case 5:
			teamName = "AllTeams/TOR.txt";
			tnm = "TOR.txt";

			// check if user want this team by showing the roster
			fp.open(teamName, ios::in);
			if (!fp) {
				cout << endl << "******* ERROR *******";
				exit(1);
			}
			if (fp.is_open()) {
				Team tempMenuTeam;
				vector<Player> vtemp;

				fromFileToTeam(teamName, tempMenuTeam);

				cout << endl << "players" << endl << endl;
				vtemp = tempMenuTeam.getTeamPlayers();
				for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
					(*it).showPlayer();
					cout << endl;
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

				fs::path pth{ ("Games/" + leagueName) };
				pth /= "_Main_Team_.txt";
				fs::create_directory(pth.parent_path());

				fs::path pth_i{ ("Games/" + leagueName) };
				pth_i /= "_Info_.txt";
				fs::create_directory(pth_i.parent_path());

				fs::path pth_h{ ("Games/" + leagueName) };
				pth_h /= "History";
				fs::create_directory(pth_h);

				fs::path pth_g{ ("Games/" + leagueName) };
				pth_g /= "Games";
				fs::create_directory(pth_g);

				fp.open(pth, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << tnm;
					fp.close();
				}

				fp.open(pth_i, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << 1 << endl << 0 << endl;
					fp.close();
				}

				fs::copy("AllTeams", ("Games/" + leagueName));

				gameMenu(leagueName);

				system("pause");
				flagDontLikeTeam = false;
			}
			break;

		case 6:

			teamName = "AllTeams/CHI.txt";
			tnm = "CHI.txt";

			// check if user want this team by showing the roster
			fp.open(teamName, ios::in);
			if (!fp) {
				cout << endl << "******* ERROR *******";
				exit(1);
			}
			if (fp.is_open()) {
				Team tempMenuTeam;
				vector<Player> vtemp;

				fromFileToTeam(teamName, tempMenuTeam);

				cout << endl << "players" << endl << endl;
				vtemp = tempMenuTeam.getTeamPlayers();
				for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
					(*it).showPlayer();
					cout << endl;
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

				fs::path pth{ ("Games/" + leagueName) };
				pth /= "_Main_Team_.txt";
				fs::create_directory(pth.parent_path());

				fs::path pth_i{ ("Games/" + leagueName) };
				pth_i /= "_Info_.txt";
				fs::create_directory(pth_i.parent_path());

				fs::path pth_h{ ("Games/" + leagueName) };
				pth_h /= "History";
				fs::create_directory(pth_h);

				fs::path pth_g{ ("Games/" + leagueName) };
				pth_g /= "Games";
				fs::create_directory(pth_g);

				fp.open(pth, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << tnm;
					fp.close();
				}

				fp.open(pth_i, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << 1 << endl << 0 << endl;
					fp.close();
				}

				fs::copy("AllTeams", ("Games/" + leagueName));

				gameMenu(leagueName);

				flagDontLikeTeam = false;
			}

			break;

		case 7:

			teamName = "AllTeams/CLE.txt";
			tnm = "CLE.txt";

			// check if user want this team by showing the roster
			fp.open(teamName, ios::in);
			if (!fp) {
				cout << endl << "******* ERROR *******";
				exit(1);
			}
			if (fp.is_open()) {
				Team tempMenuTeam;
				vector<Player> vtemp;

				fromFileToTeam(teamName, tempMenuTeam);

				cout << endl << "players" << endl << endl;
				vtemp = tempMenuTeam.getTeamPlayers();
				for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
					(*it).showPlayer();
					cout << endl;
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

				fs::path pth{ ("Games/" + leagueName) };
				pth /= "_Main_Team_.txt";
				fs::create_directory(pth.parent_path());

				fs::path pth_i{ ("Games/" + leagueName) };
				pth_i /= "_Info_.txt";
				fs::create_directory(pth_i.parent_path());

				fs::path pth_h{ ("Games/" + leagueName) };
				pth_h /= "History";
				fs::create_directory(pth_h);

				fs::path pth_g{ ("Games/" + leagueName) };
				pth_g /= "Games";
				fs::create_directory(pth_g);

				fp.open(pth, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << tnm;
					fp.close();
				}

				fp.open(pth_i, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << 1 << endl << 0 << endl;
					fp.close();
				}

				fs::copy("AllTeams", ("Games/" + leagueName));

				gameMenu(leagueName);

				flagDontLikeTeam = false;
			}

			break;

		case 8:

			teamName = "AllTeams/DET.txt";
			tnm = "DET.txt";

			// check if user want this team by showing the roster
			fp.open(teamName, ios::in);
			if (!fp) {
				cout << endl << "******* ERROR *******";
				exit(1);
			}
			if (fp.is_open()) {
				Team tempMenuTeam;
				vector<Player> vtemp;

				fromFileToTeam(teamName, tempMenuTeam);

				cout << endl << "players" << endl << endl;
				vtemp = tempMenuTeam.getTeamPlayers();
				for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
					(*it).showPlayer();
					cout << endl;
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

				fs::path pth{ ("Games/" + leagueName) };
				pth /= "_Main_Team_.txt";
				fs::create_directory(pth.parent_path());

				fs::path pth_i{ ("Games/" + leagueName) };
				pth_i /= "_Info_.txt";
				fs::create_directory(pth_i.parent_path());

				fs::path pth_h{ ("Games/" + leagueName) };
				pth_h /= "History";
				fs::create_directory(pth_h);

				fs::path pth_g{ ("Games/" + leagueName) };
				pth_g /= "Games";
				fs::create_directory(pth_g);

				fp.open(pth, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << tnm;
					fp.close();
				}

				fp.open(pth_i, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << 1 << endl << 0 << endl;
					fp.close();
				}

				fs::copy("AllTeams", ("Games/" + leagueName));

				gameMenu(leagueName);

				flagDontLikeTeam = false;
			}

			break;

		case 9:

			teamName = "AllTeams/IND.txt";
			tnm = "IND.txt";

			// check if user want this team by showing the roster
			fp.open(teamName, ios::in);
			if (!fp) {
				cout << endl << "******* ERROR *******";
				exit(1);
			}
			if (fp.is_open()) {
				Team tempMenuTeam;
				vector<Player> vtemp;

				fromFileToTeam(teamName, tempMenuTeam);

				cout << endl << "players" << endl << endl;
				vtemp = tempMenuTeam.getTeamPlayers();
				for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
					(*it).showPlayer();
					cout << endl;
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

				fs::path pth{ ("Games/" + leagueName) };
				pth /= "_Main_Team_.txt";
				fs::create_directory(pth.parent_path());

				fs::path pth_i{ ("Games/" + leagueName) };
				pth_i /= "_Info_.txt";
				fs::create_directory(pth_i.parent_path());

				fs::path pth_h{ ("Games/" + leagueName) };
				pth_h /= "History";
				fs::create_directory(pth_h);

				fs::path pth_g{ ("Games/" + leagueName) };
				pth_g /= "Games";
				fs::create_directory(pth_g);

				fp.open(pth, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << tnm;
					fp.close();
				}

				fp.open(pth_i, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << 1 << endl << 0 << endl;
					fp.close();
				}

				fs::copy("AllTeams", ("Games/" + leagueName));

				gameMenu(leagueName);

				flagDontLikeTeam = false;
			}

			break;

		case 10:
			teamName = "AllTeams/MIL.txt";
			tnm = "MIL.txt";

			// check if user want this team by showing the roster
			fp.open(teamName, ios::in);
			if (!fp) {
				cout << endl << "******* ERROR *******";
				exit(1);
			}
			if (fp.is_open()) {
				Team tempMenuTeam;
				vector<Player> vtemp;

				fromFileToTeam(teamName, tempMenuTeam);

				cout << endl << "players" << endl << endl;
				vtemp = tempMenuTeam.getTeamPlayers();
				for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
					(*it).showPlayer();
					cout << endl;
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

				fs::path pth{ ("Games/" + leagueName) };
				pth /= "_Main_Team_.txt";
				fs::create_directory(pth.parent_path());

				fs::path pth_i{ ("Games/" + leagueName) };
				pth_i /= "_Info_.txt";
				fs::create_directory(pth_i.parent_path());

				fs::path pth_h{ ("Games/" + leagueName) };
				pth_h /= "History";
				fs::create_directory(pth_h);

				fs::path pth_g{ ("Games/" + leagueName) };
				pth_g /= "Games";
				fs::create_directory(pth_g);

				fp.open(pth, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << tnm;
					fp.close();
				}

				fp.open(pth_i, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << 1 << endl << 0 << endl;
					fp.close();
				}

				fs::copy("AllTeams", ("Games/" + leagueName));

				gameMenu(leagueName);

				system("pause");
				flagDontLikeTeam = false;
			}
			break;

		case 11:
			teamName = "AllTeams/ATL.txt";
			tnm = "ATL.txt";

			// check if user want this team by showing the roster
			fp.open(teamName, ios::in);
			if (!fp) {
				cout << endl << "******* ERROR *******";
				exit(1);
			}
			if (fp.is_open()) {
				Team tempMenuTeam;
				vector<Player> vtemp;

				fromFileToTeam(teamName, tempMenuTeam);

				cout << endl << "players" << endl << endl;
				vtemp = tempMenuTeam.getTeamPlayers();
				for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
					(*it).showPlayer();
					cout << endl;
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

				fs::path pth{ ("Games/" + leagueName) };
				pth /= "_Main_Team_.txt";
				fs::create_directory(pth.parent_path());

				fs::path pth_i{ ("Games/" + leagueName) };
				pth_i /= "_Info_.txt";
				fs::create_directory(pth_i.parent_path());

				fs::path pth_h{ ("Games/" + leagueName) };
				pth_h /= "History";
				fs::create_directory(pth_h);

				fs::path pth_g{ ("Games/" + leagueName) };
				pth_g /= "Games";
				fs::create_directory(pth_g);

				fp.open(pth, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << tnm;
					fp.close();
				}

				fp.open(pth_i, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << 1 << endl << 0 << endl;
					fp.close();
				}

				fs::copy("AllTeams", ("Games/" + leagueName));

				gameMenu(leagueName);

				flagDontLikeTeam = false;
			}

			break;

		case 12:

			teamName = "AllTeams/CHA.txt";
			tnm = "CHA.txt";

			// check if user want this team by showing the roster
			fp.open(teamName, ios::in);
			if (!fp) {
				cout << endl << "******* ERROR *******";
				exit(1);
			}
			if (fp.is_open()) {
				Team tempMenuTeam;
				vector<Player> vtemp;

				fromFileToTeam(teamName, tempMenuTeam);

				cout << endl << "players" << endl << endl;
				vtemp = tempMenuTeam.getTeamPlayers();
				for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
					(*it).showPlayer();
					cout << endl;
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

				fs::path pth{ ("Games/" + leagueName) };
				pth /= "_Main_Team_.txt";
				fs::create_directory(pth.parent_path());

				fs::path pth_i{ ("Games/" + leagueName) };
				pth_i /= "_Info_.txt";
				fs::create_directory(pth_i.parent_path());

				fs::path pth_h{ ("Games/" + leagueName) };
				pth_h /= "History";
				fs::create_directory(pth_h);

				fs::path pth_g{ ("Games/" + leagueName) };
				pth_g /= "Games";
				fs::create_directory(pth_g);

				fp.open(pth, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << tnm;
					fp.close();
				}

				fp.open(pth_i, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << 1 << endl << 0 << endl;
					fp.close();
				}

				fs::copy("AllTeams", ("Games/" + leagueName));

				gameMenu(leagueName);

				flagDontLikeTeam = false;
			}

			break;

		case 13:
			teamName = "AllTeams/MIA.txt";
			tnm = "MIA.txt";

			// check if user want this team by showing the roster
			fp.open(teamName, ios::in);
			if (!fp) {
				cout << endl << "******* ERROR *******";
				exit(1);
			}
			if (fp.is_open()) {
				Team tempMenuTeam;
				vector<Player> vtemp;

				fromFileToTeam(teamName, tempMenuTeam);

				cout << endl << "players" << endl << endl;
				vtemp = tempMenuTeam.getTeamPlayers();
				for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
					(*it).showPlayer();
					cout << endl;
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

				fs::path pth{ ("Games/" + leagueName) };
				pth /= "_Main_Team_.txt";
				fs::create_directory(pth.parent_path());

				fs::path pth_i{ ("Games/" + leagueName) };
				pth_i /= "_Info_.txt";
				fs::create_directory(pth_i.parent_path());

				fs::path pth_h{ ("Games/" + leagueName) };
				pth_h /= "History";
				fs::create_directory(pth_h);

				fs::path pth_g{ ("Games/" + leagueName) };
				pth_g /= "Games";
				fs::create_directory(pth_g);

				fp.open(pth, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << tnm;
					fp.close();
				}

				fp.open(pth_i, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << 1 << endl << 0 << endl;
					fp.close();
				}

				fs::copy("AllTeams", ("Games/" + leagueName));

				gameMenu(leagueName);

				system("pause");
				flagDontLikeTeam = false;
			}
			break;

		case 14:
			teamName = "AllTeams/ORL.txt";
			tnm = "ORL.txt";

			// check if user want this team by showing the roster
			fp.open(teamName, ios::in);
			if (!fp) {
				cout << endl << "******* ERROR *******";
				exit(1);
			}
			if (fp.is_open()) {
				Team tempMenuTeam;
				vector<Player> vtemp;

				fromFileToTeam(teamName, tempMenuTeam);

				cout << endl << "players" << endl << endl;
				vtemp = tempMenuTeam.getTeamPlayers();
				for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
					(*it).showPlayer();
					cout << endl;
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

				fs::path pth{ ("Games/" + leagueName) };
				pth /= "_Main_Team_.txt";
				fs::create_directory(pth.parent_path());

				fs::path pth_i{ ("Games/" + leagueName) };
				pth_i /= "_Info_.txt";
				fs::create_directory(pth_i.parent_path());

				fs::path pth_h{ ("Games/" + leagueName) };
				pth_h /= "History";
				fs::create_directory(pth_h);

				fs::path pth_g{ ("Games/" + leagueName) };
				pth_g /= "Games";
				fs::create_directory(pth_g);

				fp.open(pth, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << tnm;
					fp.close();
				}

				fp.open(pth_i, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << 1 << endl << 0 << endl;
					fp.close();
				}

				fs::copy("AllTeams", ("Games/" + leagueName));

				gameMenu(leagueName);

				system("pause");
				flagDontLikeTeam = false;
			}
			break;

		case 15:
			teamName = "AllTeams/WAS.txt";
			tnm = "WAS.txt";

			// check if user want this team by showing the roster
			fp.open(teamName, ios::in);
			if (!fp) {
				cout << endl << "******* ERROR *******";
				exit(1);
			}
			if (fp.is_open()) {
				Team tempMenuTeam;
				vector<Player> vtemp;

				fromFileToTeam(teamName, tempMenuTeam);

				cout << endl << "players" << endl << endl;
				vtemp = tempMenuTeam.getTeamPlayers();
				for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
					(*it).showPlayer();
					cout << endl;
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

				fs::path pth{ ("Games/" + leagueName) };
				pth /= "_Main_Team_.txt";
				fs::create_directory(pth.parent_path());

				fs::path pth_i{ ("Games/" + leagueName) };
				pth_i /= "_Info_.txt";
				fs::create_directory(pth_i.parent_path());

				fs::path pth_h{ ("Games/" + leagueName) };
				pth_h /= "History";
				fs::create_directory(pth_h);

				fs::path pth_g{ ("Games/" + leagueName) };
				pth_g /= "Games";
				fs::create_directory(pth_g);

				fp.open(pth, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << tnm;
					fp.close();
				}

				fp.open(pth_i, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << 1 << endl << 0 << endl;
					fp.close();
				}

				fs::copy("AllTeams", ("Games/" + leagueName));

				gameMenu(leagueName);

				system("pause");
				flagDontLikeTeam = false;
			}
			break;

		case 16:

			teamName = "AllTeams/DEN.txt";
			tnm = "DEN.txt";

			// check if user want this team by showing the roster
			fp.open(teamName, ios::in);
			if (!fp) {
				cout << endl << "******* ERROR *******";
				exit(1);
			}
			if (fp.is_open()) {
				Team tempMenuTeam;
				vector<Player> vtemp;

				fromFileToTeam(teamName, tempMenuTeam);

				cout << endl << "players" << endl << endl;
				vtemp = tempMenuTeam.getTeamPlayers();
				for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
					(*it).showPlayer();
					cout << endl;
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

				fs::path pth{ ("Games/" + leagueName) };
				pth /= "_Main_Team_.txt";
				fs::create_directory(pth.parent_path());

				fs::path pth_i{ ("Games/" + leagueName) };
				pth_i /= "_Info_.txt";
				fs::create_directory(pth_i.parent_path());

				fs::path pth_h{ ("Games/" + leagueName) };
				pth_h /= "History";
				fs::create_directory(pth_h);

				fs::path pth_g{ ("Games/" + leagueName) };
				pth_g /= "Games";
				fs::create_directory(pth_g);

				fp.open(pth, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << tnm;
					fp.close();
				}

				fp.open(pth_i, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << 1 << endl << 0 << endl;
					fp.close();
				}

				fs::copy("AllTeams", ("Games/" + leagueName));

				gameMenu(leagueName);

				flagDontLikeTeam = false;
			}

			break;

		case 17:
			teamName = "AllTeams/MIN.txt";
			tnm = "MIN.txt";

			// check if user want this team by showing the roster
			fp.open(teamName, ios::in);
			if (!fp) {
				cout << endl << "******* ERROR *******";
				exit(1);
			}
			if (fp.is_open()) {
				Team tempMenuTeam;
				vector<Player> vtemp;

				fromFileToTeam(teamName, tempMenuTeam);

				cout << endl << "players" << endl << endl;
				vtemp = tempMenuTeam.getTeamPlayers();
				for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
					(*it).showPlayer();
					cout << endl;
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

				fs::path pth{ ("Games/" + leagueName) };
				pth /= "_Main_Team_.txt";
				fs::create_directory(pth.parent_path());

				fs::path pth_i{ ("Games/" + leagueName) };
				pth_i /= "_Info_.txt";
				fs::create_directory(pth_i.parent_path());

				fs::path pth_h{ ("Games/" + leagueName) };
				pth_h /= "History";
				fs::create_directory(pth_h);

				fs::path pth_g{ ("Games/" + leagueName) };
				pth_g /= "Games";
				fs::create_directory(pth_g);

				fp.open(pth, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << tnm;
					fp.close();
				}

				fp.open(pth_i, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << 1 << endl << 0 << endl;
					fp.close();
				}

				fs::copy("AllTeams", ("Games/" + leagueName));

				gameMenu(leagueName);

				system("pause");
				flagDontLikeTeam = false;
			}
			break;

		case 18:
			teamName = "AllTeams/OKC.txt";
			tnm = "OKC.txt";

			// check if user want this team by showing the roster
			fp.open(teamName, ios::in);
			if (!fp) {
				cout << endl << "******* ERROR *******";
				exit(1);
			}
			if (fp.is_open()) {
				Team tempMenuTeam;
				vector<Player> vtemp;

				fromFileToTeam(teamName, tempMenuTeam);

				cout << endl << "players" << endl << endl;
				vtemp = tempMenuTeam.getTeamPlayers();
				for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
					(*it).showPlayer();
					cout << endl;
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

				fs::path pth{ ("Games/" + leagueName) };
				pth /= "_Main_Team_.txt";
				fs::create_directory(pth.parent_path());

				fs::path pth_i{ ("Games/" + leagueName) };
				pth_i /= "_Info_.txt";
				fs::create_directory(pth_i.parent_path());

				fs::path pth_h{ ("Games/" + leagueName) };
				pth_h /= "History";
				fs::create_directory(pth_h);

				fs::path pth_g{ ("Games/" + leagueName) };
				pth_g /= "Games";
				fs::create_directory(pth_g);

				fp.open(pth, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << tnm;
					fp.close();
				}

				fp.open(pth_i, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << 1 << endl << 0 << endl;
					fp.close();
				}

				fs::copy("AllTeams", ("Games/" + leagueName));

				gameMenu(leagueName);

				system("pause");
				flagDontLikeTeam = false;
			}
			break;

		case 19:
			teamName = "AllTeams/POR.txt";
			tnm = "POR.txt";

			// check if user want this team by showing the roster
			fp.open(teamName, ios::in);
			if (!fp) {
				cout << endl << "******* ERROR *******";
				exit(1);
			}
			if (fp.is_open()) {
				Team tempMenuTeam;
				vector<Player> vtemp;

				fromFileToTeam(teamName, tempMenuTeam);

				cout << endl << "players" << endl << endl;
				vtemp = tempMenuTeam.getTeamPlayers();
				for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
					(*it).showPlayer();
					cout << endl;
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

				fs::path pth{ ("Games/" + leagueName) };
				pth /= "_Main_Team_.txt";
				fs::create_directory(pth.parent_path());

				fs::path pth_i{ ("Games/" + leagueName) };
				pth_i /= "_Info_.txt";
				fs::create_directory(pth_i.parent_path());

				fs::path pth_h{ ("Games/" + leagueName) };
				pth_h /= "History";
				fs::create_directory(pth_h);

				fs::path pth_g{ ("Games/" + leagueName) };
				pth_g /= "Games";
				fs::create_directory(pth_g);

				fp.open(pth, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << tnm;
					fp.close();
				}

				fp.open(pth_i, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << 1 << endl << 0 << endl;
					fp.close();
				}

				fs::copy("AllTeams", ("Games/" + leagueName));

				gameMenu(leagueName);

				system("pause");
				flagDontLikeTeam = false;
			}
			break;

		case 20:
			teamName = "AllTeams/UTA.txt";
			tnm = "UTA.txt";

			// check if user want this team by showing the roster
			fp.open(teamName, ios::in);
			if (!fp) {
				cout << endl << "******* ERROR *******";
				exit(1);
			}
			if (fp.is_open()) {
				Team tempMenuTeam;
				vector<Player> vtemp;

				fromFileToTeam(teamName, tempMenuTeam);

				cout << endl << "players" << endl << endl;
				vtemp = tempMenuTeam.getTeamPlayers();
				for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
					(*it).showPlayer();
					cout << endl;
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

				fs::path pth{ ("Games/" + leagueName) };
				pth /= "_Main_Team_.txt";
				fs::create_directory(pth.parent_path());

				fs::path pth_i{ ("Games/" + leagueName) };
				pth_i /= "_Info_.txt";
				fs::create_directory(pth_i.parent_path());

				fs::path pth_h{ ("Games/" + leagueName) };
				pth_h /= "History";
				fs::create_directory(pth_h);

				fs::path pth_g{ ("Games/" + leagueName) };
				pth_g /= "Games";
				fs::create_directory(pth_g);

				fp.open(pth, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << tnm;
					fp.close();
				}

				fp.open(pth_i, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << 1 << endl << 0 << endl;
					fp.close();
				}

				fs::copy("AllTeams", ("Games/" + leagueName));

				gameMenu(leagueName);

				system("pause");
				flagDontLikeTeam = false;
			}
			break;

		case 21:

			teamName = "AllTeams/GSW.txt";
			tnm = "GSW.txt";

			// check if user want this team by showing the roster
			fp.open(teamName, ios::in);
			if (!fp) {
				cout << endl << "******* ERROR *******";
				exit(1);
			}
			if (fp.is_open()) {
				Team tempMenuTeam;
				vector<Player> vtemp;

				fromFileToTeam(teamName, tempMenuTeam);

				cout << endl << "players" << endl << endl;
				vtemp = tempMenuTeam.getTeamPlayers();
				for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
					(*it).showPlayer();
					cout << endl;
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

				fs::path pth{ ("Games/" + leagueName) };
				pth /= "_Main_Team_.txt";
				fs::create_directory(pth.parent_path());

				fs::path pth_i{ ("Games/" + leagueName) };
				pth_i /= "_Info_.txt";
				fs::create_directory(pth_i.parent_path());

				fs::path pth_h{ ("Games/" + leagueName) };
				pth_h /= "History";
				fs::create_directory(pth_h);

				fs::path pth_g{ ("Games/" + leagueName) };
				pth_g /= "Games";
				fs::create_directory(pth_g);

				fp.open(pth, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << tnm;
					fp.close();
				}

				fp.open(pth_i, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << 1 << endl << 0 << endl;
					fp.close();
				}

				fs::copy("AllTeams", ("Games/" + leagueName));

				gameMenu(leagueName);

				flagDontLikeTeam = false;
			}

			break;

		case 22:

			teamName = "AllTeams/LAC.txt";
			tnm = "LAC.txt";

			// check if user want this team by showing the roster
			fp.open(teamName, ios::in);
			if (!fp) {
				cout << endl << "******* ERROR *******";
				exit(1);
			}
			if (fp.is_open()) {
				Team tempMenuTeam;
				vector<Player> vtemp;

				fromFileToTeam(teamName, tempMenuTeam);

				cout << endl << "players" << endl << endl;
				vtemp = tempMenuTeam.getTeamPlayers();
				for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
					(*it).showPlayer();
					cout << endl;
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

				fs::path pth{ ("Games/" + leagueName) };
				pth /= "_Main_Team_.txt";
				fs::create_directory(pth.parent_path());

				fs::path pth_i{ ("Games/" + leagueName) };
				pth_i /= "_Info_.txt";
				fs::create_directory(pth_i.parent_path());

				fs::path pth_h{ ("Games/" + leagueName) };
				pth_h /= "History";
				fs::create_directory(pth_h);

				fs::path pth_g{ ("Games/" + leagueName) };
				pth_g /= "Games";
				fs::create_directory(pth_g);

				fp.open(pth, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << tnm;
					fp.close();
				}

				fp.open(pth_i, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << 1 << endl << 0 << endl;
					fp.close();
				}

				fs::copy("AllTeams", ("Games/" + leagueName));

				gameMenu(leagueName);

				flagDontLikeTeam = false;
			}

			break;

		case 23:

			teamName = "AllTeams/LAL.txt";
			tnm = "LAL.txt";

			// check if user want this team by showing the roster
			fp.open(teamName, ios::in);
			if (!fp) {
				cout << endl << "******* ERROR *******";
				exit(1);
			}
			if (fp.is_open()) {
				Team tempMenuTeam;
				vector<Player> vtemp;

				fromFileToTeam(teamName, tempMenuTeam);

				cout << endl << "players" << endl << endl;
				vtemp = tempMenuTeam.getTeamPlayers();
				for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
					(*it).showPlayer();
					cout << endl;
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

				fs::path pth{ ("Games/" + leagueName) };
				pth /= "_Main_Team_.txt";
				fs::create_directory(pth.parent_path());

				fs::path pth_i{ ("Games/" + leagueName) };
				pth_i /= "_Info_.txt";
				fs::create_directory(pth_i.parent_path());

				fs::path pth_h{ ("Games/" + leagueName) };
				pth_h /= "History";
				fs::create_directory(pth_h);

				fs::path pth_g{ ("Games/" + leagueName) };
				pth_g /= "Games";
				fs::create_directory(pth_g);

				fp.open(pth, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << tnm;
					fp.close();
				}

				fp.open(pth_i, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << 1 << endl << 0 << endl;
					fp.close();
				}

				fs::copy("AllTeams", ("Games/" + leagueName));

				gameMenu(leagueName);

				flagDontLikeTeam = false;
			}

			break;

		case 24:
			teamName = "AllTeams/PHO.txt";
			tnm = "PHO.txt";

			// check if user want this team by showing the roster
			fp.open(teamName, ios::in);
			if (!fp) {
				cout << endl << "******* ERROR *******";
				exit(1);
			}
			if (fp.is_open()) {
				Team tempMenuTeam;
				vector<Player> vtemp;

				fromFileToTeam(teamName, tempMenuTeam);

				cout << endl << "players" << endl << endl;
				vtemp = tempMenuTeam.getTeamPlayers();
				for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
					(*it).showPlayer();
					cout << endl;
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

				fs::path pth{ ("Games/" + leagueName) };
				pth /= "_Main_Team_.txt";
				fs::create_directory(pth.parent_path());

				fs::path pth_i{ ("Games/" + leagueName) };
				pth_i /= "_Info_.txt";
				fs::create_directory(pth_i.parent_path());

				fs::path pth_h{ ("Games/" + leagueName) };
				pth_h /= "History";
				fs::create_directory(pth_h);

				fs::path pth_g{ ("Games/" + leagueName) };
				pth_g /= "Games";
				fs::create_directory(pth_g);

				fp.open(pth, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << tnm;
					fp.close();
				}

				fp.open(pth_i, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << 1 << endl << 0 << endl;
					fp.close();
				}

				fs::copy("AllTeams", ("Games/" + leagueName));

				gameMenu(leagueName);

				system("pause");
				flagDontLikeTeam = false;
			}
			break;

		case 25:
			teamName = "AllTeams/DAL.txt";
			tnm = "DAL.txt";

			// check if user want this team by showing the roster
			fp.open(teamName, ios::in);
			if (!fp) {
				cout << endl << "******* ERROR *******";
				exit(1);
			}
			if (fp.is_open()) {
				Team tempMenuTeam;
				vector<Player> vtemp;

				fromFileToTeam(teamName, tempMenuTeam);

				cout << endl << "players" << endl << endl;
				vtemp = tempMenuTeam.getTeamPlayers();
				for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
					(*it).showPlayer();
					cout << endl;
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

				fs::path pth{ ("Games/" + leagueName) };
				pth /= "_Main_Team_.txt";
				fs::create_directory(pth.parent_path());

				fs::path pth_i{ ("Games/" + leagueName) };
				pth_i /= "_Info_.txt";
				fs::create_directory(pth_i.parent_path());

				fs::path pth_h{ ("Games/" + leagueName) };
				pth_h /= "History";
				fs::create_directory(pth_h);

				fs::path pth_g{ ("Games/" + leagueName) };
				pth_g /= "Games";
				fs::create_directory(pth_g);

				fp.open(pth, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << tnm;
					fp.close();
				}

				fp.open(pth_i, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << 1 << endl << 0 << endl;
					fp.close();
				}

				fs::copy("AllTeams", ("Games/" + leagueName));

				gameMenu(leagueName);

				system("pause");
				flagDontLikeTeam = false;
			}
			break;

		case 26:

			teamName = "AllTeams/DAL.txt";
			tnm = "DAL.txt";

			// check if user want this team by showing the roster
			fp.open(teamName, ios::in);
			if (!fp) {
				cout << endl << "******* ERROR *******";
				exit(1);
			}
			if (fp.is_open()) {
				Team tempMenuTeam;
				vector<Player> vtemp;

				fromFileToTeam(teamName, tempMenuTeam);

				cout << endl << "players" << endl << endl;
				vtemp = tempMenuTeam.getTeamPlayers();
				for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
					(*it).showPlayer();
					cout << endl;
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

				fs::path pth{ ("Games/" + leagueName) };
				pth /= "_Main_Team_.txt";
				fs::create_directory(pth.parent_path());

				fs::path pth_i{ ("Games/" + leagueName) };
				pth_i /= "_Info_.txt";
				fs::create_directory(pth_i.parent_path());

				fs::path pth_h{ ("Games/" + leagueName) };
				pth_h /= "History";
				fs::create_directory(pth_h);

				fs::path pth_g{ ("Games/" + leagueName) };
				pth_g /= "Games";
				fs::create_directory(pth_g);

				fp.open(pth, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << tnm;
					fp.close();
				}

				fp.open(pth_i, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << 1 << endl << 0 << endl;
					fp.close();
				}

				fs::copy("AllTeams", ("Games/" + leagueName));

				gameMenu(leagueName);

				flagDontLikeTeam = false;
			}

			break;

		case 27:

			teamName = "AllTeams/HOU.txt";
			tnm = "HOU.txt";

			// check if user want this team by showing the roster
			fp.open(teamName, ios::in);
			if (!fp) {
				cout << endl << "******* ERROR *******";
				exit(1);
			}
			if (fp.is_open()) {
				Team tempMenuTeam;
				vector<Player> vtemp;

				fromFileToTeam(teamName, tempMenuTeam);

				cout << endl << "players" << endl << endl;
				vtemp = tempMenuTeam.getTeamPlayers();
				for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
					(*it).showPlayer();
					cout << endl;
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

				fs::path pth{ ("Games/" + leagueName) };
				pth /= "_Main_Team_.txt";
				fs::create_directory(pth.parent_path());

				fs::path pth_i{ ("Games/" + leagueName) };
				pth_i /= "_Info_.txt";
				fs::create_directory(pth_i.parent_path());

				fs::path pth_h{ ("Games/" + leagueName) };
				pth_h /= "History";
				fs::create_directory(pth_h);

				fs::path pth_g{ ("Games/" + leagueName) };
				pth_g /= "Games";
				fs::create_directory(pth_g);

				fp.open(pth, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << tnm;
					fp.close();
				}

				fp.open(pth_i, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << 1 << endl << 0 << endl;
					fp.close();
				}

				fs::copy("AllTeams", ("Games/" + leagueName));

				gameMenu(leagueName);

				flagDontLikeTeam = false;
			}

			break;

		case 28:
			teamName = "AllTeams/MEM.txt";
			tnm = "MEM.txt";

			// check if user want this team by showing the roster
			fp.open(teamName, ios::in);
			if (!fp) {
				cout << endl << "******* ERROR *******";
				exit(1);
			}
			if (fp.is_open()) {
				Team tempMenuTeam;
				vector<Player> vtemp;

				fromFileToTeam(teamName, tempMenuTeam);

				cout << endl << "players" << endl << endl;
				vtemp = tempMenuTeam.getTeamPlayers();
				for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
					(*it).showPlayer();
					cout << endl;
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

				fs::path pth{ ("Games/" + leagueName) };
				pth /= "_Main_Team_.txt";
				fs::create_directory(pth.parent_path());

				fs::path pth_i{ ("Games/" + leagueName) };
				pth_i /= "_Info_.txt";
				fs::create_directory(pth_i.parent_path());

				fs::path pth_h{ ("Games/" + leagueName) };
				pth_h /= "History";
				fs::create_directory(pth_h);

				fs::path pth_g{ ("Games/" + leagueName) };
				pth_g /= "Games";
				fs::create_directory(pth_g);

				fp.open(pth, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << tnm;
					fp.close();
				}

				fp.open(pth_i, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << 1 << endl << 0 << endl;
					fp.close();
				}

				fs::copy("AllTeams", ("Games/" + leagueName));

				gameMenu(leagueName);

				system("pause");
				flagDontLikeTeam = false;
			}
			break;

		case 29:
			teamName = "AllTeams/NOR.txt";
			tnm = "NOR.txt";

			// check if user want this team by showing the roster
			fp.open(teamName, ios::in);
			if (!fp) {
				cout << endl << "******* ERROR *******";
				exit(1);
			}
			if (fp.is_open()) {
				Team tempMenuTeam;
				vector<Player> vtemp;

				fromFileToTeam(teamName, tempMenuTeam);

				cout << endl << "players" << endl << endl;
				vtemp = tempMenuTeam.getTeamPlayers();
				for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
					(*it).showPlayer();
					cout << endl;
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

				fs::path pth{ ("Games/" + leagueName) };
				pth /= "_Main_Team_.txt";
				fs::create_directory(pth.parent_path());

				fs::path pth_i{ ("Games/" + leagueName) };
				pth_i /= "_Info_.txt";
				fs::create_directory(pth_i.parent_path());

				fs::path pth_h{ ("Games/" + leagueName) };
				pth_h /= "History";
				fs::create_directory(pth_h);

				fs::path pth_g{ ("Games/" + leagueName) };
				pth_g /= "Games";
				fs::create_directory(pth_g);

				fp.open(pth, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << tnm;
					fp.close();
				}

				fp.open(pth_i, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << 1 << endl << 0 << endl;
					fp.close();
				}

				fs::copy("AllTeams", ("Games/" + leagueName));

				gameMenu(leagueName);

				system("pause");
				flagDontLikeTeam = false;
			}
			break;

		case 30:
			teamName = "AllTeams/SAN.txt";
			tnm = "SAN.txt";

			// check if user want this team by showing the roster
			fp.open(teamName, ios::in);
			if (!fp) {
				cout << endl << "******* ERROR *******";
				exit(1);
			}
			if (fp.is_open()) {
				Team tempMenuTeam;
				vector<Player> vtemp;

				fromFileToTeam(teamName, tempMenuTeam);

				cout << endl << "players" << endl << endl;
				vtemp = tempMenuTeam.getTeamPlayers();
				for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
					(*it).showPlayer();
					cout << endl;
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

				fs::path pth{ ("Games/" + leagueName) };
				pth /= "_Main_Team_.txt";
				fs::create_directory(pth.parent_path());

				fs::path pth_i{ ("Games/" + leagueName) };
				pth_i /= "_Info_.txt";
				fs::create_directory(pth_i.parent_path());

				fs::path pth_h{ ("Games/" + leagueName) };
				pth_h /= "History";
				fs::create_directory(pth_h);

				fs::path pth_g{ ("Games/" + leagueName) };
				pth_g /= "Games";
				fs::create_directory(pth_g);

				fp.open(pth, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << tnm;
					fp.close();
				}

				fp.open(pth_i, ios::out);
				if (!fp) {
					cout << endl << "******* ERROR *******";
					exit(1);
				}
				if (fp.is_open()) {
					fp << 1 << endl << 0 << endl;
					fp.close();
				}

				fs::copy("AllTeams", ("Games/" + leagueName));

				gameMenu(leagueName);

				system("pause");
				flagDontLikeTeam = false;
			}
			break;
		} // close team switch

	} while (flagDontLikeTeam == true); // close do while for picking a team
}



// Start Menu function =========
void startMenu() {
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

			case 1: // case make a new league
				makingALeague();
				break;

			case 2: // case continue existing game
				continueGame();
				break;

			default: exit(1); break;
			}
		} while (true);
	} while (true);
}