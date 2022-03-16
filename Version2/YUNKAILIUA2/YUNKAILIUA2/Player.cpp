#include "Player.h"
#include <iostream>
using namespace std;

Player::Player() {
	name = "";
	position = "porch";
}

Player::~Player() {

}

/*Player's inventory can only hold one item. So player needs to drop first if there is already an item in inventory*/
bool Player::pick(Item i) {
	bool retVal = false;
	if (inventory.size() == 0) {
		inventory.push_back(i);
		cout << "You pick up " << i.getName() << endl;
		retVal = true;
	}
	else {
		cout << "Your inventory is full. Please drop item in your inventory first!" << endl;
	}
	return retVal;
}

/*Player can only drop if there is an item in inventory. Otherwise, an error messenge will be shown*/
bool Player::drop(Item i) {
	bool retVal = false;
	if (inventory.size() == 1) {
		inventory.pop_back();
		cout << "You drop " << i.getName() << endl;
		retVal = true;
	}
	else {
		cout << "Your inventory is empty!" << endl;
	}
	return retVal;
}

void Player::setName(string newName) {
	name = newName;
}

string Player::getName() {
	return name;
}

void Player::printInventory() {
	if (inventory.size() > 0) {
		cout << "Name: " << inventory[0].getName() << endl;
		cout << "Description: " << inventory[0].getDescription() << endl;
	}
	else {
		cout << "Your inventory is empty" << endl;
	}
}

void Player::setPosition(string newPosition) {
	position = newPosition;
}
string Player::getPosition() {
	return position;
}

vector<Item> Player::getInventory() {
	return inventory;
}
