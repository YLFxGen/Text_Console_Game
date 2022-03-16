#include "Item.h"
using namespace std;

Item::Item(string initName, string initDescription) {
	name = initName;
	description = initDescription;
}

Item::Item() {

}

Item::~Item() {

}

string Item::getName() {
	return name;
}

string Item::getDescription() {
	return description;
}

void Item::setPosition(string newPosition) {
	position = newPosition;
}
string Item::getPosition() {
	return position;
}