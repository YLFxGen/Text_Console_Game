#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
#include "Item.h"
using namespace std;
/*A class to create the player object,including player's current position, name, inventory and associated behaviors*/
class Player {
private:
	string name;
	vector<Item> inventory;
	string position;
public:
	Player();
	~Player();
	bool pick(Item i);                        //add new item to inventory
	bool drop(Item i);                        //drop item in the inventory
	void setName(string newName);
	string getName();
	void printInventory();                    // show the name and description of the item in player's inventory
	void setPosition(string newPosition);
	string getPosition();
	vector<Item> getInventory();
};

#endif // !PLAYER_H

