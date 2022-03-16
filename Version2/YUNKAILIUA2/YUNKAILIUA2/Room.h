#ifndef ROOM_H
#define ROOM_H
#include <string>
using namespace std;
/*A class used to create all the rooms in the crime scene*/
class Room {
private:
	string name;
	string description;
public:
	Room();
	Room(string initName,string initDescription);
	~Room();

	string getName();
	string getDescription();
	void setDescription(string newDescription);

};
#endif // !ROOM_H

