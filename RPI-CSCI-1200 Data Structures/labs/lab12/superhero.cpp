#include <string>
#include <cstddef>
#include <iostream>

#include "superhero.h"

Superhero::Superhero(std::string n, std::string id, std::string p) {
	name = n;
	identity = id;
	power = p;
	morality = true;
}

bool Superhero::operator==(const std::string n) const {
	if (n==getTrueIdentity()) {
		return true;
	} else {
		return false;
	}
}

bool Superhero::operator!=(const std::string n) const {
	if (n==getTrueIdentity()) {
		return false;
	} else {
		return true;
	}
}

std::string Superhero::getName() const {
	return name;
}

std::string Superhero::getPower() const {
	return power;
}

std::string Superhero::getTrueIdentity() const {
	return identity;
}

bool Superhero::isGood() const {
	if (morality) {
		return true;
	} else {
		return false;
	}
}

std::ostream& operator<< (std::ostream& out, const Superhero& s) {
	//Superhero Falcon has power Flying
	if (s.isGood()) {
		out << "Superhero " << s.getName() << " has power " << s.getPower() << std::endl; 
	} else {
		out << "Supervillian " << s.getName() << " has power " << s.getPower() << std::endl; 
	}
	return out;
}

bool operator>(const Superhero& s1, const Superhero& s2) {
	if ((s1.getPower()=="Fire")&&(s2.getPower()=="Wood")) {
		return true;
	} else if ((s1.getPower()=="Wood")&&(s2.getPower()=="Water")) {
		return true;
	} else if ((s1.getPower()=="Water")&&(s2.getPower()=="Fire")) {
		return true;
	} else {
		if (s1.getPower() > s2.getPower()) {
			return false;
		} else {
			return true;
		}
	}
}

void Superhero::operator-() {
	this->morality = !morality;
}
