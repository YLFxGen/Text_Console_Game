#include "Suspect.h"

using namespace std;

Suspect::Suspect() {

}

Suspect::Suspect(string initName, string initDescription, string initStatu) {
	name = initName;
	description = initDescription;
	setStatu(initStatu);
}

Suspect::~Suspect() {

}

string Suspect::getName() {
	return name;
}

string Suspect::getDescription() {
	return description;
}

void Suspect::setLocation(string newLocation) {
	location = newLocation;
}

string Suspect::getLocation() {
	return location;
}

void Suspect::setStatu(string newStatu) {
	statu = newStatu;
}

string Suspect::getStatu() {
	return statu;
}

void Suspect::setAlibi(string newAlibi) {
	alibi = newAlibi;
}

string Suspect::getAlibi() {
	return alibi;
}