#ifndef ITEM_H
#define ITEM_H
#include <string>
using namespace std;
/*A class used to create all the items including weapon in the game*/
class Item {
private:
	string name;
	string description;
	string position;
public:
	Item();
	Item(string initName,string initDescription);
	~Item();
	string getName();
	string getDescription();
	void setPosition(string newPosition);
	string getPosition();
};

#endif // !ITEM_H

