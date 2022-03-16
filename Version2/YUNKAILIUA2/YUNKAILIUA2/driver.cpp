#include <fstream>
#include <iostream>
#include "Room.h"
#include "Player.h"
#include "Item.h"
#include "Suspect.h"
using namespace std;
Room roomInformation[3][4];                             //an array containing all the room objects
Item itemInformation[6];                                //an array containing all the item objects
Suspect suspectInformation[7];                          //an array containing all the suspect objects
string crimeScene;                                      //a string holding the correct murder scene
string weapon;                                          //a string holding the correct weapon
string reviewNote;                                      //store all the conversation between suspects and player.
bool endGame = false;
bool questionMurder = false;                            //for additional feature, after player qustion him, he will kill player in
int turnToBeKilled = 0;                                 // 15 turns.
bool isWinning = false;
int turnCounter = 0;                                    //store how many turns player has already used.
Player detective;

void openDocument(string s);                            /*read from file(file name is parameter),including map, helpMenu
                                                        , victory condition, background, and how to play.*/
void initialRoomInformation();                          /*initial 12 rooms in the crime scene using data read from the file 
                                                        and store them in the roomInformation array*/
void initialItem();                                     /*initial 6 items in the crime scene using data read from the file 
                                                        and store them in the itemInformation array*/                           
void initialSuspect();                                  /*initial 7 suspects in the crime scene using data read from the file 
                                                        and store them in the suspectInformation array*/ 
void goSomewhere(string s);                             //Move around the crime scene.Parameter is the destination
void takeSomething(string s);                            //pick up something and add it to inventory. Parameter is the target item.
void dropSomething(string s);                           //drop something and remove it from inventory. Parameter is the target item.
void search();                                          //find the items and doubtful point(murder scene?) in the current room
void examineItem(string s);                             //Get the information about an item(point out by parameter)
void questionSomeone(string s);                         //ask for suspects' alibi 
void gather();                                          //gather all suspects in the current room
int accuse(string s);                                   //decide wheather the player win or lose the game.
void quitGame();                                        

int main() {
	/*show splash screen*/
	openDocument("background");                         
	system("pause");
	system("cls");
	openDocument("howToPlay");
	system("pause");
	system("cls");
	openDocument("victoryCondition");
	system("pause");
	system("cls");
	openDocument("helpMenu");
	system("pause");
	system("cls");
	cout << "Please enter your name:" << endl;
	string playerName;
	cin >> playerName;
	detective.setName(playerName);
	cout << "Hi, " << detective.getName() << "! Ready to begin the game?" << endl;
	cin.ignore(1024, '\n');                                 //clear cin to be ready for receiving next instruction
	system("pause");
	system("cls");
	initialRoomInformation();                               //create all the objects needed for the game
	initialItem();
	initialSuspect();
	openDocument("startingPoint");
	goSomewhere("porch");
	while (!endGame) {                                      //A loop asks player to enter instruction. One loop is one turn.
		string instruction;                                 
		string verb;
		string noun;
		turnCounter++;
		/*Additional feature*/
		if (turnCounter % 6 == 0) {                         //every six turns, suspects will saunter around(reset position randomly)
			for (int i = 0;i < 6;i++) {
				int randI = rand() % 3;                     //get random numbers from 0-2 and 0-3 to randomly set position
				int randJ = rand() % 4;
				suspectInformation[i].setLocation(roomInformation[randI][randJ].getName());
			}
			cout << "\n\nPeople begin to saunter around the house" << endl;
		}
		cout << "\nWhat now?" << endl;
		getline(cin, instruction);                          //get user input
		int spaceIndex = instruction.find(" ");
		if (spaceIndex == string::npos) {                   //find space in the instruction to seperate verb(go,search,get...)
			verb = instruction;                             //and noun(suspectName, roomName)(used as the parameter for functions)
			noun = "";
		}
		else {
			verb = instruction.substr(0, spaceIndex);
			noun = instruction.substr(spaceIndex + 1);
		}
		if (verb == "HELP" && noun =="") {
			system("cls");
			openDocument("helpMenu");
			system("pause");
			system("cls");
		}
		else if (verb == "GO") {
			goSomewhere(noun);
		}
		else if (verb == "MAP" && noun == "") {
			system("cls");
			openDocument("map");
		}
		else if (verb == "QUIT" && noun == "") {
			quitGame();
		}
		else if (verb == "TAKE") {
			takeSomething(noun);
		}
		else if (verb == "DROP") {
			dropSomething(noun);
		}
		else if (verb == "SEARCH" && (noun == "" || noun == "room")){
			search();
		}
		else if (verb == "EXAMINE") {
			examineItem(noun);
		}
		else if (verb == "I" && noun == "") {                                  //print name and description of item carried by the player
			detective.printInventory();
		}
		else if (verb == "REVIEW" && noun == "") {                             //print all the conversations between player and suspects
			if (reviewNote == "") {
				cout << "You have not talked to anyone" << endl;
			}
			else {
				cout << reviewNote << endl;
			}
		}
		else if (verb == "QUESTION") {
			questionSomeone(noun);
		}
		else if (verb == "GATHER" && noun == "") {
			gather();
		}
		else if(verb == "ACCUSE"){
			int result = accuse(noun);
			/*accuse will return 3 value,0,1,2. 
			0 means player have not found all the neccessary information correctly.
			1 means player have not gathered everyone or player enter an invalid name. 
			2 means player carry the correct weapon, accuse the correct murder in the correct murder scene */
			if (result == 0) {                                  
				endGame = true;
				isWinning = false;
			}
			else if (result == 2) {                             
				endGame = true;
				isWinning = true;
			}
			if (isWinning) {
				cout << "\n\n\nYou Win" << endl;
			}
			else {
				cout << "\n\nThe murder escaped\nGame Over" << endl;
			}
			system("pause");
		}
		else {
			cout << "I can't understand what you mean.Please enter some valid instructions.\n"
				<< "If you have any questions, please type in HELP to look help note." << endl;
		}
		/*Additional Feature*/
		if (questionMurder) {                        //Murder will escape if player cannot find him within time limit.
			turnToBeKilled++;
			if (turnToBeKilled > 15) {
				endGame = true;
				isWinning = false;
				cout << "\n\nYou are killed.The murder escaped\nGame Over" << endl;
				system("pause");
			}
		}
	}
	return 0;
}


void openDocument(string s) {
	string line;
	ifstream doc;
	doc.open(s + ".txt");
	if (doc.is_open()) {
		while (getline(doc, line)) {
			cout << line << endl;
		}
	}
	else {
		cout << "File doesn't exist!" << endl;
	}
	doc.close();
}

void goSomewhere(string s) {
	int indexI = -1;
	int indexJ = -1;
	for (int i = 0; i < 3;i++) {
		for (int j = 0; j < 4; j++) {
			if (roomInformation[i][j].getName() == s) {                   //check wheather the noun is a valid roomName or not
				indexI = i;
				indexJ = j;
			}
		}
	}
	if (indexI != -1) {                                              
		cout << roomInformation[indexI][indexJ].getDescription() << endl;                //print room description
		detective.setPosition(s);
		for (int k = 0;k < 6;k++) {
			if (detective.getPosition() == suspectInformation[k].getLocation()) {
				cout << suspectInformation[k].getName() << " is here" << endl;           //print suspects in this room
			}
		}
	}
	else {
		cout << "Room not found" << endl;
	}
}

void takeSomething(string s) {
	int itemIndex = -1;
	for (int i = 0;i < 6;i++) {
		if (itemInformation[i].getName() == s) {                          //check wheather the parameter is a valid itemName
			itemIndex = i;
		}
	}
	if (itemIndex != -1) {
		if (detective.getPosition() == itemInformation[itemIndex].getPosition()) {//check if the item is in player's current room  
			if (detective.pick(itemInformation[itemIndex])) {               //check if the inventory has enough space
				itemInformation[itemIndex].setPosition("Player");
			}
		}
		else {
			cout << "Item not found" << endl;
		}
	}
	else {
		cout << "Item not found" << endl;
	}
}

void dropSomething(string s) {
	int itemIndex = -1;
	for (int i = 0;i < 6;i++) {
		if (itemInformation[i].getName() == s) {                       //check wheather the parameter is a valid itemName
			if (detective.getInventory().size() > 0) {
				if (s == detective.getInventory()[0].getName()) {      //check if the item is in player's inventory 
					itemIndex = i;
				}
			}
		}
	}
	if (itemIndex != -1) {
		if (detective.drop(itemInformation[itemIndex])) {
			itemInformation[itemIndex].setPosition(detective.getPosition());
		}
	}
	else {
		cout << "Item not found" << endl;
	}
}

void search() {
	bool retVal = true;
	for (int q = 0;q < 6;q++) {
		if (detective.getPosition() == itemInformation[q].getPosition()) {
			cout << "Oh, there is a [" << itemInformation[q].getName() << "]" << endl;    //print items in current room
			retVal = false;
		}
	}
	if (detective.getPosition() == crimeScene) {          //if current room is murder scene, print messenge to inform player
		cout << "You notice that there is blood on the wall." << endl;          
		retVal = false;
	}
	if (retVal) {
		cout << "Nothing is found" << endl;
	}
}

void examineItem(string s) {
	int itemIndex = -1;
	for (int i = 0;i < 6;i++) {
		if (itemInformation[i].getName() == s) {
			itemIndex = i;
		}
	}
	if (itemIndex != -1) {
		if (itemInformation[itemIndex].getPosition() == detective.getPosition() || itemInformation[itemIndex].getPosition() == "Player") {          //check if the item is in the current room or in player's inventory
			cout << itemInformation[itemIndex].getDescription() << endl;
			if (itemInformation[itemIndex].getName() == weapon) {
				cout << "You notice that there is blood on it" << endl;
			}
		}
		else {
			cout << "Item not found" << endl;
		}
	}
	else {
		cout << "Item not found" << endl;
	}
}

void questionSomeone(string s) {
	int suspectIndex = -1;
	string alibiInfor = "";
	for (int i = 0;i < 6;i++) {
		if (suspectInformation[i].getName() == s) {   //check wheather the parameter is a valid name
			suspectIndex = i;
		}
	}
	if (suspectIndex != -1) {
		if (suspectInformation[suspectIndex].getLocation() == detective.getPosition()) {
			alibiInfor = "I am " + suspectInformation[suspectIndex].getAlibi();
			cout << alibiInfor << endl;
			reviewNote += suspectInformation[suspectIndex].getName() + " : " + alibiInfor + "\n";
			if (suspectInformation[suspectIndex].getStatu() == "murder") {
				questionMurder = true;    // After questioning murder, he will look for opportunities to kill player
			}
		}
		else {
			cout << "He is not in this room" << endl;
		}
	}
	else {
		cout << "Name not identified" << endl;
	}
}

void gather() {
	for (int i = 0;i < 6;i++) {
		suspectInformation[i].setLocation(detective.getPosition());
	}
	cout << "Now everyone is here, time to tell the truth!" << endl;
	for (int i = 0;i < 6;i++) {
		cout << suspectInformation[i].getName() << endl;
	}
}

int accuse(string s) {
	int retVal = 0;
	bool isGather = true;
	for (int i = 0;i < 6;i++) {
		if (suspectInformation[i].getLocation() != detective.getPosition()) {
			isGather = false;
		}
	}
	if (isGather) {
		int suspectIndex = -1;
		for (int i = 0;i < 6;i++) {
			if (suspectInformation[i].getName() == s) {
				suspectIndex = i;
			}
		}
		if (suspectIndex != -1) {
			if (suspectInformation[suspectIndex].getStatu() == "murder") {
				if (detective.getPosition() == crimeScene) {
					if (detective.getInventory().size() == 1 && detective.getInventory()[0].getName() == weapon) {
						cout << suspectInformation[suspectIndex].getName() << "! You are the murder!" << endl;
						cout << "You use " << weapon << " to kill " << suspectInformation[6].getName() << " in this room" << endl;
						retVal = 2;
					}
					else {
						cout << "You have not found the weapon" << endl;
					}
				}
				else {
					cout << "You are not in the crime scene" << endl;
					retVal = 0;
				}
			}
			else {
				cout << "You accused the wrong person" << endl;
				retVal = 0;
			}
		}
		else {
			cout << "Name not identified" << endl;
			retVal = 1;
		}
	}
	else {
		cout << "You need to gather all the suspects here(using GATHER)" << endl;
		retVal = 1;
	}
	return retVal;
}

void quitGame() {
	endGame = true;
}

void initialRoomInformation() {
	string roomName[3][4];
	string roomDescription[3][4];
	ifstream initRoomName;
	initRoomName.open("roomName.txt");
	if (initRoomName.is_open()) {
		for (int i = 0; i < 3;i++) {
			for (int j = 0; j < 4; j++) {
				initRoomName >> roomName[i][j];
				ifstream initRoomDescription;
				string line;
				initRoomDescription.open(roomName[i][j] + ".txt");
				if (initRoomDescription.is_open()) {
					while (getline(initRoomDescription, line)) {               //get name and description from files
						roomDescription[i][j] += line + "\n";
					}
					Room r(roomName[i][j], roomDescription[i][j]);
					roomInformation[i][j] = r;
					int randI = rand() % 3;                                    //randomly get a murder scene
					int randJ = rand() % 4;
					crimeScene = roomInformation[randI][randJ].getName();
				}
				else {
					cout << "File doesn't exist" << endl;
				}
				initRoomDescription.close();
			}
		}
	}
	else {
		cout << "File doesn't exist!" << endl;
	}
	initRoomName.close();
}

void initialItem() {
	string itemName[6];
	string itemDescription[6];
	ifstream initItemName;
	initItemName.open("itemName.txt");
	if (initItemName.is_open()) {
		for (int i = 0;i < 6;i++) {
			initItemName >> itemName[i];
			ifstream initItemDescription;
			string line;
			initItemDescription.open(itemName[i] + ".txt");
			if (initItemDescription.is_open()) {
				while (getline(initItemDescription, line)) {
					itemDescription[i] += line + "\n";
				}
				Item it(itemName[i], itemDescription[i]);
				itemInformation[i] = it;
				int randI = rand() % 3;
				int randJ = rand() % 4;
				itemInformation[i].setPosition(roomInformation[randI][randJ].getName());    //randomly set items' positions
				int randW = rand() % 6;
				weapon = itemInformation[randW].getName();
			}
			else {
				cout << "File doesn't exist" << endl;
			}
			initItemDescription.close();
		}
	}
	else {
		cout << "File doesn't exist!" << endl;
	}
	initItemName.close();
}

void initialSuspect() {
	string namePool[15];
	vector<string> suspectName;
	string suspectDescription[7];
	string line;
	ifstream initSuspectName;
	initSuspectName.open("namePool.txt");
	if (initSuspectName.is_open()) {
		for (int i = 0;i < 15;i++) {
			initSuspectName >> namePool[i];            //read in all the names from the file
		}
		int randN = rand() % 6;
		for (int j = randN;j < randN + 7;j++) {        //randomly choose seven names
			suspectName.push_back(namePool[j]);
		}
	}
	else {
		cout << "File doesn't exist!" << endl;
	}
	initSuspectName.close();
	ifstream initSuspectDescription;
	initSuspectDescription.open("suspectDescription.txt");
	if (initSuspectDescription.is_open()) {
		for (int i = 0;i < 7;i++) {
			getline(initSuspectDescription, line);
			suspectDescription[i] = line;
		}
	}
	else {
		cout << "File doesn't exist!" << endl;
	}
	initSuspectDescription.close();

	Suspect m(suspectName[0], suspectDescription[0],"murder");
	suspectInformation[0] = m;                                            //create murder object
	Suspect v(suspectName[6], suspectDescription[6],"victim");
	suspectInformation[6] = v;                                            //create victim object
	for (int i = 1; i < 6;i++) {
		Suspect innocent(suspectName[i], suspectDescription[i], "suspect");
		suspectInformation[i] = innocent;
	}                                                                     //create suspect objects
	for (int i = 0;i < 6;i++) {
		int randI = rand() % 3;
		int randJ = rand() % 4;
		suspectInformation[i].setLocation(roomInformation[randI][randJ].getName());
	}
	suspectInformation[0].setAlibi("with " + suspectInformation[5].getName());
	suspectInformation[1].setAlibi("with " + suspectInformation[2].getName());
	suspectInformation[2].setAlibi("with " + suspectInformation[1].getName());
	suspectInformation[3].setAlibi("with " + suspectInformation[4].getName());
	suspectInformation[4].setAlibi("with " + suspectInformation[3].getName());
	suspectInformation[5].setAlibi("alone");
}