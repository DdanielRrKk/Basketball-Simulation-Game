#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<iterator>
#include<algorithm>
#include<stdlib.h>
#include<sstream>
#include<filesystem>

#include"playerStatsClass.h"
#include"playerClass.h"
#include"teamClass.h"
#include"gamesClass.h"

using namespace std;
namespace fs = std::filesystem;



// function for making a main team from chosen file
void fromFileToTeam(string fname, Team& gameTeam) {
	string line;
	string tempName;
	int rating;
	int i;

	string s = fname;
	s.erase(0, s.find_last_of("\\")+1);
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



//=======================================
void startMenu();
void gameMenu(string chosenGame);
//=======================================



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

	system("cls");
	cout << "Enter your league name: ";
	cin.ignore(1, '\n');
	getline(cin, leagueName);

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

				fs::copy("AllTeams", ("Games/" + leagueName));

				gameMenu(leagueName);

				system("pause");
				flagDontLikeTeam = false;
			}
			break;

		case 3: break;
		case 4: break;
		case 5: break;

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

				fs::copy("AllTeams", ("Games/" + leagueName));

				gameMenu(leagueName);

				flagDontLikeTeam = false;
			}

			break;

		case 10: break;

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

				fs::copy("AllTeams", ("Games/" + leagueName));

				gameMenu(leagueName);

				flagDontLikeTeam = false;
			}
			
			break;

		case 13: break;
		case 14: break;
		case 15: break;

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

				fs::copy("AllTeams", ("Games/" + leagueName));

				gameMenu(leagueName);

				flagDontLikeTeam = false;
			}
			
			break;

		case 17: break;
		case 18: break;
		case 19: break;
		case 20: break;

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

				fs::copy("AllTeams", ("Games/" + leagueName));

				gameMenu(leagueName);

				flagDontLikeTeam = false;
			}
			
			break;

		case 24: break;
		case 25: break;

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

				fs::copy("AllTeams", ("Games/" + leagueName));

				gameMenu(leagueName);

				flagDontLikeTeam = false;
			}
			
			break;

		case 28: break;
		case 29: break;
		case 30: break;
		} // close team switch

	} while (flagDontLikeTeam == true); // close do while for picking a team
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



// Main function
int main() {
	startMenu();
	return 0;
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


bool sortOvr(Player p1, Player p2) {return p1.getPlayerOverall() > p2.getPlayerOverall();} // support function for sorting
bool compDiff(Player p1, Player p2) { return (p1.getPlayerOverall() == p2.getPlayerOverall()); }
int getPositionNumber(Player p) { string pos = p.getPlayerPosition();
	if (pos == "PG" || pos == "SG" || pos == "SF" || pos == "PF") { return 2; }
	else if (pos == "C/PF" || pos == "PF/C") { return 4; }
	else if (pos == "C") { return 1; }
	else { return 5; }
}

// Game Menu function for showing and modifying the roster
void rosterFunction(Team& myTeam) {
	Team rosterTeam = myTeam;
	vector<Player> vtemp = rosterTeam.getTeamPlayers();
	auto vit = vtemp.end() - 1;
	Player ptemp = (*vit);

	vector<Player> starters;

	sort(vtemp.begin(), vtemp.end(), sortOvr);

	system("cls");
	cout << "--Starters---------------------" << endl;
	for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
		string pos = (*it).getPlayerPosition();
		if (pos == "PG" || pos == "PG/SG") {
			if ((*it).getPlayerOverall() > ptemp.getPlayerOverall()) {
				ptemp = (*it);
			}
		}
	}
	if (ptemp.getPlayerName().length() + 4 < 16) {
		cout << "PG: " << ptemp.getPlayerName() << "\t\t\t" << ptemp.getPlayerOverall() << " OVR " << ptemp.getPlayerAge() << "yo\tOFF: " << ptemp.getCalcPlayerOffence() << " DEF: " << ptemp.getCalcPlayerDefence() << endl;
	}
	else if (ptemp.getPlayerName().length() + 4 > 24) {
		cout << "PG: " << ptemp.getPlayerName() << "\t" << ptemp.getPlayerOverall() << " OVR " << ptemp.getPlayerAge() << "yo\tOFF: " << ptemp.getCalcPlayerOffence() << " DEF: " << ptemp.getCalcPlayerDefence() << endl;
	}
	else {
		cout << "PG: " << ptemp.getPlayerName() << "\t\t" << ptemp.getPlayerOverall() << " OVR " << ptemp.getPlayerAge() << "yo\tOFF: " << ptemp.getCalcPlayerOffence() << " DEF: " << ptemp.getCalcPlayerDefence() << endl;
	}
	starters.push_back(ptemp);

	ptemp = (*vit);
	for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
		string pos = (*it).getPlayerPosition();
		if (pos == "SG" || pos == "SG/PG" || pos == "SG/SF") {
			if ((*it).getPlayerOverall() > ptemp.getPlayerOverall()) {
				ptemp = (*it);
			}
		}
	}
	if (ptemp.getPlayerName().length() + 4 < 16) {
		cout << "SG: " << ptemp.getPlayerName() << "\t\t\t" << ptemp.getPlayerOverall() << " OVR " << ptemp.getPlayerAge() << "yo\tOFF: " << ptemp.getCalcPlayerOffence() << " DEF: " << ptemp.getCalcPlayerDefence() << endl;
	}
	else if (ptemp.getPlayerName().length() + 4 > 24) {
		cout << "SG: " << ptemp.getPlayerName() << "\t" << ptemp.getPlayerOverall() << " OVR " << ptemp.getPlayerAge() << "yo\tOFF: " << ptemp.getCalcPlayerOffence() << " DEF: " << ptemp.getCalcPlayerDefence() << endl;
	}
	else {
		cout << "SG: " << ptemp.getPlayerName() << "\t\t" << ptemp.getPlayerOverall() << " OVR " << ptemp.getPlayerAge() << "yo\tOFF: " << ptemp.getCalcPlayerOffence() << " DEF: " << ptemp.getCalcPlayerDefence() << endl;
	}
	starters.push_back(ptemp);

	ptemp = (*vit);
	for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
		string pos = (*it).getPlayerPosition();
		if (pos == "SF" || pos == "SF/SG" || pos == "SF/PF") {
			if ((*it).getPlayerOverall() > ptemp.getPlayerOverall()) {
				ptemp = (*it);
			}
		}
	}
	if (ptemp.getPlayerName().length() + 4 < 16) {
		cout << "SF: " << ptemp.getPlayerName() << "\t\t\t" << ptemp.getPlayerOverall() << " OVR " << ptemp.getPlayerAge() << "yo\tOFF: " << ptemp.getCalcPlayerOffence() << " DEF: " << ptemp.getCalcPlayerDefence() << endl;
	}
	else if (ptemp.getPlayerName().length() + 4 > 24) {
		cout << "SF: " << ptemp.getPlayerName() << "\t" << ptemp.getPlayerOverall() << " OVR " << ptemp.getPlayerAge() << "yo\tOFF: " << ptemp.getCalcPlayerOffence() << " DEF: " << ptemp.getCalcPlayerDefence() << endl;
	}
	else {
		cout << "SF: " << ptemp.getPlayerName() << "\t\t" << ptemp.getPlayerOverall() << " OVR " << ptemp.getPlayerAge() << "yo\tOFF: " << ptemp.getCalcPlayerOffence() << " DEF: " << ptemp.getCalcPlayerDefence() << endl;
	}
	starters.push_back(ptemp);

	ptemp = (*vit);
	for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
		string pos = (*it).getPlayerPosition();
		if (pos == "PF" || pos == "PF/SF" || pos == "PF/C") {
			if ((*it).getPlayerOverall() > ptemp.getPlayerOverall()) {
				ptemp = (*it);
			}
		}
	}
	if (ptemp.getPlayerName().length() + 4 < 16) {
		cout << "PF: " << ptemp.getPlayerName() << "\t\t\t" << ptemp.getPlayerOverall() << " OVR " << ptemp.getPlayerAge() << "yo\tOFF: " << ptemp.getCalcPlayerOffence() << " DEF: " << ptemp.getCalcPlayerDefence() << endl;
	}
	else if (ptemp.getPlayerName().length() + 4 > 24) {
		cout << "PF: " << ptemp.getPlayerName() << "\t" << ptemp.getPlayerOverall() << " OVR " << ptemp.getPlayerAge() << "yo\tOFF: " << ptemp.getCalcPlayerOffence() << " DEF: " << ptemp.getCalcPlayerDefence() << endl;
	}
	else {
		cout << "PF: " << ptemp.getPlayerName() << "\t\t" << ptemp.getPlayerOverall() << " OVR " << ptemp.getPlayerAge() << "yo\tOFF: " << ptemp.getCalcPlayerOffence() << " DEF: " << ptemp.getCalcPlayerDefence() << endl;
	}
	starters.push_back(ptemp);

	ptemp = (*vit);
	for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
		string pos = (*it).getPlayerPosition();
		if (pos == "C" || pos == "C/PF") {
			if ((*it).getPlayerOverall() > ptemp.getPlayerOverall()) {
				ptemp = (*it);
			}
		}
	}
	if (ptemp.getPlayerName().length() + 3 < 16) {
		cout << "C: " << ptemp.getPlayerName() << "\t\t\t" << ptemp.getPlayerOverall() << " OVR " << ptemp.getPlayerAge() << "yo\tOFF: " << ptemp.getCalcPlayerOffence() << " DEF: " << ptemp.getCalcPlayerDefence() << endl;
	}
	else if (ptemp.getPlayerName().length() + 3 > 24) {
		cout << "C: " << ptemp.getPlayerName() << "\t" << ptemp.getPlayerOverall() << " OVR " << ptemp.getPlayerAge() << "yo\tOFF: " << ptemp.getCalcPlayerOffence() << " DEF: " << ptemp.getCalcPlayerDefence() << endl;
	}
	else {
		cout << "C: " << ptemp.getPlayerName() << "\t\t" << ptemp.getPlayerOverall() << " OVR " << ptemp.getPlayerAge() << "yo\tOFF: " << ptemp.getCalcPlayerOffence() << " DEF: " << ptemp.getCalcPlayerDefence() << endl;
	}
	starters.push_back(ptemp);

	vector<Player> bench = vtemp;

	auto pred = [&starters](const Player& pl) ->bool {
		return find(starters.begin(), starters.end(), pl) != starters.end();
	};
	bench.erase(remove_if(bench.begin(), bench.end(), pred), bench.end());

	sort(bench.begin(), bench.end(), sortOvr);

	cout << endl << "--Bench------------------------" << endl;
	for (auto it = bench.begin(); it != bench.end(); it++) {
		Player pl = (*it);
		int pnum = getPositionNumber(pl) + 2;

		if ((*it).getPlayerName().length() + pnum <= 16) {
			cout << (*it).getPlayerPosition() << ": " << (*it).getPlayerName() << "\t\t\t" << (*it).getPlayerOverall() << " OVR " << (*it).getPlayerAge() << "yo\tOFF: " << (*it).getCalcPlayerOffence() << "\tDEF: " << (*it).getCalcPlayerDefence()  << endl;
		}
		else if ((*it).getPlayerName().length() + pnum > 24) {
			cout << (*it).getPlayerPosition() << ": " << (*it).getPlayerName() << "\t" << (*it).getPlayerOverall() << " OVR " << (*it).getPlayerAge() << "yo\tOFF: " << (*it).getCalcPlayerOffence() << "\tDEF: " << (*it).getCalcPlayerDefence() << endl;
		}
		else {
			cout << (*it).getPlayerPosition() << ": " << (*it).getPlayerName() << "\t\t" << (*it).getPlayerOverall() << " OVR " << (*it).getPlayerAge() << "yo\tOFF: " << (*it).getCalcPlayerOffence() << "\tDEF: " << (*it).getCalcPlayerDefence() << endl;
		}
	}

	system("pause");
}



bool sortSal(Player p1, Player p2) {
	double p1s, p2s;
	string sal;

	sal = p1.getPlayerSalary();
	sal.erase(0, 2);
	p1s = stod(sal);

	sal = p2.getPlayerSalary();
	sal.erase(0, 2);
	p2s = stod(sal);

	return p1s > p2s;
}

// Game Manu function for showing the finances of the team
void showFinances(Team& myTeam) {
	Team finTeam = myTeam;
	vector<Player> vtemp = finTeam.getTeamPlayers();

	sort(vtemp.begin(), vtemp.end(), sortSal);

	system("cls");
	for (auto it = vtemp.begin(); it != vtemp.end(); it++) {
		if ((*it).getPlayerName().length() <= 15) {
			cout << (*it).getPlayerName() << "\t\t" << (*it).getPlayerOverall() << " OVR -\t" << (*it).salaryForFinances() << endl;
		}
		else {
			cout << (*it).getPlayerName() << "\t" << (*it).getPlayerOverall() << " OVR -\t" << (*it).salaryForFinances() << endl;
		}
	}
	cout << "------------------------------------------------------------------------" << endl;
	cout << finTeam.getTeamName() << " - " << finTeam.salaryForFinances() << endl << endl;

	system("pause");
}



bool compSeasonTeam(Team t1, Team t2) {
	return t1.getTeamLoses() < t2.getTeamLoses();
}
bool compEmptyTeam(Team t1, Team t2) {
	return t1.getTeamCalcOverall() > t2.getTeamCalcOverall();
}

//Game Menu function for showing the standings
void showTeamStandings(int day, vector<Team>& vtemp) {
	system("cls");
	vector<Team>& tvec = vtemp;

	cout << "Team\tWins\tLoses" << endl;
	cout << "-------------------" << endl;
	if (day == 0) {
		sort(tvec.begin(), tvec.end(), compEmptyTeam);
		for (auto it = tvec.begin(); it != tvec.end(); it++) {
			cout << (*it).getTeamName() << "\t" << (*it).getTeamWins() << "\t" << (*it).getTeamLoses() << endl;
		}
	}
	else {
		sort(tvec.begin(), tvec.end(), compSeasonTeam);
		for (auto it = tvec.begin(); it != tvec.end(); it++) {
			cout << (*it).getTeamName() << "\t" << (*it).getTeamWins() << "\t" << (*it).getTeamLoses() << endl;
		}
	}

	system("pause");
}



// Game Menu function for showing the player standings by overall
void showPlayerStandings(int ch, vector<Team> vtemp) {
	system("cls");
	vector<Player> pvec;
	vector<Team> tvec = vtemp;

	// showing rookie standings
	if (ch == 1) {
		for (auto it_t = tvec.begin(); it_t != tvec.end(); it_t++) {
			vector<Player> ptemp = (*it_t).getTeamPlayers();
			for (auto it_p = ptemp.begin(); it_p != ptemp.end(); it_p++) {
				Player p = (*it_p);
				if (p.getPlayerYearsPro() == 1) {
					pvec.push_back(p);
				}
			}
		}

		sort(pvec.begin(), pvec.end(), sortOvr);
		cout << "--Player Rookie----------------------" << endl;
		int i = 1;
		int iSize = 0;
		for (auto it = pvec.begin(); it != pvec.end(); it++) {
			if (i < 10) { iSize = 1; }
			else { iSize = 2; }

			if ((*it).getPlayerName().length() + iSize + 2 > 23) {
				cout << i << ". " << (*it).getPlayerName() << "\t" << (*it).getPlayerAge() << "yo\t" << (*it).getPlayerTeam() << "\t" << (*it).getPlayerOverall() << " OVR" << "\tOFF: " << (*it).getCalcPlayerOffence() << "\tDIF: " << (*it).getCalcPlayerDefence() << endl;
			}
			else if ((*it).getPlayerName().length() + iSize + 2 < 16) {
				cout << i << ". " << (*it).getPlayerName() << "\t\t\t" << (*it).getPlayerAge() << "yo\t" << (*it).getPlayerTeam() << "\t" << (*it).getPlayerOverall() << " OVR" << "\tOFF: " << (*it).getCalcPlayerOffence() << "\tDIF: " << (*it).getCalcPlayerDefence() << endl;
			}
			else {
				cout << i << ". " << (*it).getPlayerName() << "\t\t" << (*it).getPlayerAge() << "yo\t" << (*it).getPlayerTeam() << "\t" << (*it).getPlayerOverall() << " OVR" << "\tOFF: " << (*it).getCalcPlayerOffence() << "\tDIF: " << (*it).getCalcPlayerDefence() << endl;
			}

			i++;
		}
	}

	// showing sophomore standings
	if (ch == 2) {
		for (auto it_t = tvec.begin(); it_t != tvec.end(); it_t++) {
			vector<Player> ptemp = (*it_t).getTeamPlayers();
			for (auto it_p = ptemp.begin(); it_p != ptemp.end(); it_p++) {
				Player p = (*it_p);
				if (p.getPlayerYearsPro() == 2) {
					pvec.push_back(p);
				}
			}
		}

		sort(pvec.begin(), pvec.end(), sortOvr);
		cout << "--Player Sophomore----------------------" << endl;
		int i = 1;
		int iSize = 0;
		for (auto it = pvec.begin(); it != pvec.end(); it++) {
			if (i < 10) { iSize = 1; }
			else { iSize = 2; }

			if ((*it).getPlayerName().length() + iSize + 2 > 23) {
				cout << i << ". " << (*it).getPlayerName() << "\t" << (*it).getPlayerAge() << "yo\t" << (*it).getPlayerTeam() << "\t" << (*it).getPlayerOverall() << " OVR" << "\tOFF: " << (*it).getCalcPlayerOffence() << "\tDIF: " << (*it).getCalcPlayerDefence() << endl;
			}
			else if ((*it).getPlayerName().length() + iSize + 2 < 16) {
				cout << i << ". " << (*it).getPlayerName() << "\t\t\t" << (*it).getPlayerAge() << "yo\t" << (*it).getPlayerTeam() << "\t" << (*it).getPlayerOverall() << " OVR" << "\tOFF: " << (*it).getCalcPlayerOffence() << "\tDIF: " << (*it).getCalcPlayerDefence() << endl;
			}
			else {
				cout << i << ". " << (*it).getPlayerName() << "\t\t" << (*it).getPlayerAge() << "yo\t" << (*it).getPlayerTeam() << "\t" << (*it).getPlayerOverall() << " OVR" << "\tOFF: " << (*it).getCalcPlayerOffence() << "\tDIF: " << (*it).getCalcPlayerDefence() << endl;
			}

			i++;
		}
	}

	// showing all players standings
	if (ch == 3) {
		for (auto it_t = tvec.begin(); it_t != tvec.end(); it_t++) {
			vector<Player> ptemp = (*it_t).getTeamPlayers();
			for (auto it_p = ptemp.begin(); it_p != ptemp.end(); it_p++) {
				Player p = (*it_p);
				pvec.push_back(p);
			}
		}

		sort(pvec.begin(), pvec.end(), sortOvr);
		cout << "--Player Standings----------------------" << endl;
		int i = 1;
		int iSize = 0;
		for (auto it = pvec.begin(); it != pvec.end(); it++) {
			if (i < 10) { iSize = 1; }
			else { iSize = 2; }

			if ((*it).getPlayerName().length() + iSize + 2 > 23) {
				cout << i << ". " << (*it).getPlayerName() << "\t" << (*it).getPlayerAge() << "yo\t" << (*it).getPlayerTeam() << "\t" << (*it).getPlayerOverall() << " OVR" << "\tOFF: " << (*it).getCalcPlayerOffence() << "\tDIF: " << (*it).getCalcPlayerDefence() << endl;
			}
			else if ((*it).getPlayerName().length() + iSize + 2 < 16) {
				cout << i << ". " << (*it).getPlayerName() << "\t\t\t" << (*it).getPlayerAge() << "yo\t" << (*it).getPlayerTeam() << "\t" << (*it).getPlayerOverall() << " OVR" << "\tOFF: " << (*it).getCalcPlayerOffence() << "\tDIF: " << (*it).getCalcPlayerDefence() << endl;
			}
			else {
				cout << i << ". " << (*it).getPlayerName() << "\t\t" << (*it).getPlayerAge() << "yo\t" << (*it).getPlayerTeam() << "\t" << (*it).getPlayerOverall() << " OVR" << "\tOFF: " << (*it).getCalcPlayerOffence() << "\tDIF: " << (*it).getCalcPlayerDefence() << endl;
			}

			i++;
		}
	}

	system("pause");
}



// Game Menu function when you enter a started game
void gameMenu(string chosenGame) {
	Team myTeam;
	fstream gameFile;
	string gamePath = "Games/" + chosenGame;
	string line;
	Games game;

	fs::path pth{ ("Games/" + chosenGame) };
	pth /= "_Main_Team_.txt";

	gameFile.open(pth, ios::in);
	if (!gameFile) {
		cout << endl << "******* ERROR *******";
		exit(1);
	}
	if (gameFile.is_open()) {
		getline(gameFile, line);

		fs::path tempPth{ ("Games/" + chosenGame) };
		tempPth /= line;

		fromFileToTeam(tempPth.string(), myTeam);
		gameFile.close();
	}

	int days = 0;

	vector<Team> tvec;
	for (auto& p : fs::directory_iterator("Games/" + chosenGame)) {
		if (p.is_regular_file()) {
			Team tempT;
			string str = p.path().filename().string();
			if (str != "_Main_Team_.txt") {
				fromFileToTeam(p.path().string(), tempT);
				tvec.push_back(tempT);
			}
		}
	}

	auto itv = tvec.begin();
	Team t1 = (*itv);
	itv++;
	Team t2 = (*itv);

	int choice = 0;
	do {
		do {
			system("cls");
			cout << "===========================================" << endl;
			cout << "==================MENU=====================" << endl;
			cout << "---Play------------------------------" << endl;
			cout << "1. Progress One Day" << endl;
			cout << "2. Progress One Week" << endl;
			cout << "3. Progress One Month" << endl;
			cout << "4. Progress in Time" << endl;
			cout << "---Management------------------------" << endl;
			cout << "5. Roster" << endl;
			cout << "6. Team Standings" << endl;
			cout << "7. Progress in Time" << endl;
			cout << "8. View opponent" << endl;
			cout << "9. News" << endl;
			cout << "---Market----------------------------" << endl;
			cout << "10. Draft" << endl;
			cout << "11. Free Agency" << endl;
			cout << "12. Tradeing" << endl;
			cout << "13. Finances" << endl;
			cout << "--Top--------------------------------" << endl;
			cout << "14. Players Standing" << endl;
			cout << "15. Sophomores Standing" << endl;
			cout << "16. Rookie Standing" << endl;
			cout << "--Statistics-------------------------" << endl;
			cout << "17. Players Stats" << endl;
			cout << "18. Sophomores Stats" << endl;
			cout << "19. Rookie Stats" << endl;
			cout << "20. History" << endl;
			cout << "--Other------------------------------" << endl;
			cout << "21. Back to Manu" << endl;
			cout << "End" << endl;
			cout << "===========================================" << endl;
			cout << "-: ";
			cin >> choice;
			switch (choice) {
			case 1:
				game.simulateGame(days, gamePath, t1, t2);
				break;

			case 2:
				
				break;

			case 3:

				break;

			case 4:

				break;

			case 5:
				rosterFunction(myTeam);
				break;

			case 6:
				showTeamStandings(days, tvec);
				break; 
			
			case 7:

				break;

			case 8:
				
				break;

			case 9:
				
				break;

			case 10:
				
				break;

			case 11:

				break;

			case 12:

				break;

			case 13:
				showFinances(myTeam);
				break;

			case 14:
				showPlayerStandings(3, tvec);
				break;

			case 15:
				showPlayerStandings(2, tvec);
				break;

			case 16:
				showPlayerStandings(1, tvec);
				break;

			case 17:

				break;

			case 18:

				break;

			case 19:

				break;

			case 20:

				break;

			case 21:
				return;
				break;

			default: exit(1); break;
			}
		} while (true);
	} while (true);

}