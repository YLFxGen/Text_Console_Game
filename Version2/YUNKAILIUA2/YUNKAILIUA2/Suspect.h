#ifndef SUSPECT_H
#define SUSPECT_H
#include <string>
using namespace std;
/*A class used to create all the suspects, including murder, victim and suspects*/
class Suspect {
private:
	string name;
	string description;
	string location;
	string statu;                              //one of "victim", "suspect", "murder"
	string alibi;
public:
	Suspect();
	Suspect(string initName,string initDescription,string initstatu);
	~Suspect();
	string getName();
	string getDescription();
	void setLocation(string newLocation);
	string getLocation();
	void setStatu(string newStatu);
	string getStatu();
	void setAlibi(string newAlibi);
	string getAlibi();
};

#endif // !SUSPECT_H

