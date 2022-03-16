#include <fstream>
#include <iostream>
#include <string>
using namespace std;

bool endGame = false;
string roomName[3][4];


void openHelp();
void openMap();
void showSplashScreen();
void initialRoomName();
void showStartingPoint();
void goSomewhere(string s);
void quitGame();

int main() {
	showSplashScreen();
	openHelp();
	system("pause");
	system("cls");
	initialRoomName();
	showStartingPoint();
	goSomewhere("porch");
	while (!endGame) {
		string instruction;
		string verb;
		string noun;
		cout << "\nWhat now?" << endl;
		getline(cin, instruction);
		int spaceIndex = instruction.find(" ");
		if (spaceIndex == string::npos) {
			verb = instruction;
		}
		else {
			verb = instruction.substr(0, spaceIndex);
			noun = instruction.substr(spaceIndex + 1);
		}
		if (verb == "HELP") {
			system("cls");
			openHelp();
			system("pause");
			system("cls");
		}
		else if (verb == "GO") {
			goSomewhere(noun);
		}
		else if (verb == "MAP") {
			system("cls");
			openMap();
			system("pause");
			system("cls");
		}
		else if (verb == "QUIT") {
			quitGame();
		}
		else {
			cout << "I can't understand what you mean.Please enter some valid instructions.\n"
				<< "If you have any questions, please type in HELP to look help note." << endl;
		}
	}
	return 0;
}

void openHelp() {
	string line;
	ifstream helpMenu;
	helpMenu.open("helpMenu.txt");
	if (helpMenu.is_open()) {
		while (getline(helpMenu, line)) {
			cout << line << endl;
		}
	}
	else {
		cout << "File doesn't exist!" << endl;
	}
	helpMenu.close();
}

void openMap() {
	string line;
	ifstream map;
	map.open("map.txt");
	if (map.is_open()) {
		while (getline(map, line)) {
			cout << line << endl;
		}
	}
	else {
		cout << "File doesn't exist!" << endl;
	}
	map.close();
}

void showSplashScreen() {
	string line;

	ifstream background;
	background.open("background.txt");
	if (background.is_open()) {
		while (getline(background, line)) {
			cout << line << endl;
		}
	}
	else {
		cout << "File doesn't exist!" << endl;
	}
	background.close();
	system("pause");
	system("cls");

	ifstream howToPlay;
	howToPlay.open("howToPlay.txt");
	if (howToPlay.is_open()) {
		while (getline(howToPlay, line)) {
			cout << line << endl;
		}
	}
	else {
		cout << "File doesn't exist!" << endl;
	}
	howToPlay.close();
	system("pause");
	system("cls");

	ifstream victoryCondition;
	victoryCondition.open("victoryCondition.txt");
	if (victoryCondition.is_open()) {
		while (getline(victoryCondition, line)) {
			cout << line << endl;
		}
	}
	else {
		cout << "File doesn't exist!" << endl;
	}
	victoryCondition.close();
	system("pause");
	system("cls");
}

void showStartingPoint() {
	string line;
	ifstream startingPoint;
	startingPoint.open("startingPoint.txt");
	if (startingPoint.is_open()) {
		while (getline(startingPoint, line)) {
			cout << line << endl;
		}
	}
	else {
		cout << "File doesn't exist!" << endl;
	}
	startingPoint.close();
}

void goSomewhere(string s) {
	string line;
	ifstream somewhere;
	somewhere.open(s + ".txt");
	if (somewhere.is_open()) {
		while (getline(somewhere, line)) {
			cout << line << endl;
		}
	}
	else {
		cout << "File doesn't exist!" << endl;
	}
	somewhere.close();
}

void quitGame() {
	endGame = true;
}

void initialRoomName() {
	ifstream initRoomName;
	initRoomName.open("roomName.txt");
	if (initRoomName.is_open()) {
		for (int i = 0; i < 3;i++) {
			for (int j = 0; j < 4; j++) {
				roomName[i][j] = initRoomName.get();
			}
		}
	}
	else {
		cout << "File doesn't exist!" << endl;
	}
	initRoomName.close();
}