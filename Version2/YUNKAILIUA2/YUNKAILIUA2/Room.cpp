#include "Room.h"
using namespace std;

Room::Room() {

}

Room::Room(string initName, string initDescription) {
	name = initName;
	description = initDescription;
}

Room::~Room() {

}


string Room::getName() {
	return name;
}

string Room::getDescription() {
	return description;
}

void Room::setDescription(string newDescription) {
	description = newDescription;
}


