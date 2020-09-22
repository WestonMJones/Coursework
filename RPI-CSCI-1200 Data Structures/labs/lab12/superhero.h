#ifndef SUPERHERO_H
#define SUPERHERO_H


#include <string>
#include <cstddef>
#include <iostream>


class Superhero {
public:
	Superhero(std::string n, std::string id, std::string p);
	bool operator==(const std::string n)const;
	bool operator!=(const std::string n)const;

	std::string getName() const;
	std::string getPower() const;
	bool isGood() const;
	void operator-();

	friend class Team;

private:
	std::string getTrueIdentity() const;

	std::string name;
	std::string identity;
	std::string power;
	bool morality;
};
std::ostream& operator<< (std::ostream& out, const Superhero& s); // Overloaded << Operator
bool operator>(const Superhero& s1, const Superhero& s2);
#endif
