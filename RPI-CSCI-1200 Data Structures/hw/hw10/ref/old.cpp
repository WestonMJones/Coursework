#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <set>
#include <iomanip>
#include "pokemon.h"

Pokemon::Pokemon(const std::map<std::string,std::vector<std::string> > &facts) {
	info = facts;
}

std::string Pokemon::getLabel() {
	std::map<std::string,std::vector<std::string> >::const_iterator it = info.find("label");
	std::string label = it->second[0];
	return label;
}

bool Pokemon::SharesEggGroup(Pokemon* other) {
	bool flag = false;
	std::map<std::string,std::vector<std::string> >::const_iterator it = info.find("eggGroups");
	std::map<std::string,std::vector<std::string> >::const_iterator it2 = other->info.find("eggGroups");
	for (unsigned int a=0;a<(it->second).size();a++) {
		for (unsigned int b=0;b<(it2->second).size();b++) {
			if ((it->second)[a]==(it2->second)[b]) {
				flag = true;
			}
		}
	}

	return flag;
}

bool Pokemon::idEggGroup(const std::map<std::string,std::vector<std::string> > &facts, std::string eggGroup) {
	std::map<std::string,std::vector<std::string> >::const_iterator it = facts.find("eggGroups");
	bool flag = false;
	for (unsigned int i=0;i<(it->second).size();i++) {
		if ((it->second)[i]==eggGroup) {
			flag=true;
		}
	}
	return flag;
}

Treecko::Treecko(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts), Monster(facts), Dragon(facts) {
	
	std::map<std::string,std::vector<std::string> >::const_iterator it = facts.find("species");
		std::string data = it->second[0];
		if (!((data=="WoodGecko")||(data=="Forest"))) {
			throw 1;
		} 

		it = facts.find("baseStats");
		int data2 = std::stoi(it->second[0]);
		if (data2<40) {
			throw 1;
		}

	

}