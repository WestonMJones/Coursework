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

// Pokemon base class constructor -- assign facts to the internal representation of each pokemon
Pokemon::Pokemon(const std::map<std::string,std::vector<std::string> > &facts) {
	info = facts;
}


std::string Pokemon::getLabel() const {

	// Using only const functions, get the pokemon's name, stored in "label" index
	std::map<std::string,std::vector<std::string> >::const_iterator it = info.find("label");
	std::string label = it->second[0];
	return label;
}

bool Pokemon::SharesEggGroup(Pokemon* other) {
	// Flag to be used later
	bool flag = false;

	// Point to iterators to the egg group vectors of each pokemon
	std::map<std::string,std::vector<std::string> >::const_iterator it = info.find("eggGroups");
	std::map<std::string,std::vector<std::string> >::const_iterator it2 = other->info.find("eggGroups");

	// Loop through egg groups of first pokemon
	for (unsigned int a=0;a<(it->second).size();a++) {
		// Loop through egg groups of second pokemon
		for (unsigned int b=0;b<(it2->second).size();b++) {

			// If there are any matches, set flag to true and break out of loop
			if ((it->second)[a]==(it2->second)[b]) {
				flag = true;
				break;
			}
		}
	}

	return flag;
}

bool Pokemon::idEggGroup(const std::map<std::string,std::vector<std::string> > &facts, const std::string& eggGroup) const {

	// Get the pokemon's egg group vector
	std::map<std::string,std::vector<std::string> >::const_iterator it = facts.find("eggGroups");

	// Make flag to be used later
	bool flag = false;

	// Loop through egg groups of pokemon
	for (unsigned int i=0;i<(it->second).size();i++) {
		// if the parameter eggGroup matches one of the pokemon's egg groups, then return true
		if ((it->second)[i]==eggGroup) {
			flag=true;
			break;
		}
	}
	return flag;
}

// Bug egg group constructor
Bug::Bug(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts) {

	// If pokemon is not in bug egg group, throw an error
	if (idEggGroup(facts,"Bug")==false) {
		throw 1;
	}
 }

// Dragon egg group constructor
Dragon::Dragon(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts) {

	// If pokemon is not in dragon egg group, throw an error
	if (idEggGroup(facts,"Dragon")==false) {
		throw 1;
	}
}

// field egg group constructor
Field::Field(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts) {

	// If pokemon is not in field egg group, throw an error
	if (idEggGroup(facts,"Field")==false) {
		throw 1;
	}
}

// humanlike egg group constructor
HumanLike::HumanLike(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts) {

	// If pokemon is not in human egg group, throw an error
	if (idEggGroup(facts,"HumanLike")==false) {
		throw 1;
	}
}

Monster::Monster(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts) {

	// If pokemon is not in monster egg group, throw an error
	if (idEggGroup(facts,"Monster")==false) {
		throw 1;
	}
}

// Treecko Constructor
Treecko::Treecko(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts), Monster(facts), Dragon(facts) {

	// Get the name of the current pokemon's species
	std::map<std::string,std::vector<std::string> >::const_iterator it = facts.find("species");
	std::string data = it->second[0];

	// If current species is not "WoodGecko" (Treecko and Grovyle) or "Forest" (Sceptile) throw error
	if (!((data=="WoodGecko")||(data=="Forest"))) {
		throw 1;
	} 
}

Grovyle::Grovyle(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts), Treecko(facts) {

	// Verify that current pokemon's first stat is above 50 to eliminate treeckos
	std::map<std::string,std::vector<std::string> >::const_iterator it = facts.find("baseStats");
	int data = std::stoi(it->second[0]);
	if (data<50) {
		throw 1;
	}
		
}

Sceptile::Sceptile(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts), Grovyle(facts) {

	// Verify that current pokemon's first stat is above 70 to eliminate all but sceptiles
	std::map<std::string,std::vector<std::string> >::const_iterator it = facts.find("baseStats");
	int data = std::stoi(it->second[0]);
	if (data<70) {
		throw 1;
	}
}

Charmander::Charmander(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts), Monster(facts), Dragon(facts) {

	// Access abilities vector of current pokemon
	std::map<std::string,std::vector<std::string> >::const_iterator it = facts.find("abilities");

	// Charmander and all of it's evolutions have the 3 abilities 14, 0, and 144 unique to them.
	if (!((it->second[0]=="14")&&(it->second[1]=="0")&&(it->second[2]=="144"))) {
		// If a pokemon doesn't have these 3 abilities then throw error
		throw 1;
	} 
}

Charmeleon::Charmeleon(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts), Charmander(facts) {
	
	// Verify that current pokemon's first stat is above 58 to eliminate charmanders but keep Charizards
	std::map<std::string,std::vector<std::string> >::const_iterator it = facts.find("baseStats");
	int data = std::stoi(it->second[0]);
	if (data<58) {
		throw 1;
	}
}

Charizard::Charizard(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts), Charmeleon(facts) {

	// Verify that current pokemon's first stat is above 78 to eliminate all but Charizards
	std::map<std::string,std::vector<std::string> >::const_iterator it = facts.find("baseStats");
	int data = std::stoi(it->second[0]);
	if (data<78) {
		throw 1;
	}
}

Buneary::Buneary(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts), Field(facts), HumanLike(facts) {

	// Access current pokemon's species
	std::map<std::string,std::vector<std::string> >::const_iterator it = facts.find("species");

	// The rabbit species is unique to Buneary and Lopunny
	if ((it->second)[0]!="Rabbit") {
		throw 1;
	}
}

Lopunny::Lopunny(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts), Buneary(facts) {

	// Verify that first base stat is equal to 65 to confirm current pokemon is a Lopunny
	std::map<std::string,std::vector<std::string> >::const_iterator it = facts.find("baseStats");
	if ((it->second)[0]!="65") {
		throw 1;
	}
}

Scyther::Scyther(const std::map<std::string,std::vector<std::string> > &facts) : Bug(facts) {

	// Mantis species is unique to Scyther -- makes it easy to identify
	std::map<std::string,std::vector<std::string> >::const_iterator it = facts.find("species");
	if ((it->second)[0]!="Mantis") {
		throw 1;
	}
}

Pinsir::Pinsir(const std::map<std::string,std::vector<std::string> > &facts) : Bug(facts) {

	// Stagbeetle species is unique to pinsir -- makes it easy to indentify
	std::map<std::string,std::vector<std::string> >::const_iterator it = facts.find("species");
	if ((it->second)[0]!="Stagbeetle") {
		throw 1;
	}
}