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
#include <algorithm>

// Pokemon Base Class
class Pokemon {
public:
	Pokemon(const std::map<std::string,std::vector<std::string> > &facts); // Constructor 

	// Function Prototypes required by code
	std::string getLabel() const;
	bool SharesEggGroup(Pokemon* other);

	// Virtual Destructor to satisfy compiler
	virtual ~Pokemon() {}

	// Other function I made to identify egg groups more easily
	bool idEggGroup(const std::map<std::string,std::vector<std::string> > &facts, const std::string& eggGroup) const;
private:
	// Every pokemon stores info about itself
	std::map<std::string,std::vector<std::string> > info; 
};

// Empty constructor since my list has no amorphous pokemon
class Amorphous : public Pokemon {
public:
 	Amorphous(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts) {}
};

// Constructor prototype for bug egg group pokemon
class Bug : public Pokemon {
public:
 	Bug(const std::map<std::string,std::vector<std::string> > &facts);
};

// Constructor prototype for dragon egg group pokemon -- virtual public b/c some dragon pokemon have another egg group
class Dragon : virtual public Pokemon {
public:
 	Dragon(const std::map<std::string,std::vector<std::string> > &facts);
};

// Empty constructor since my list has no fairy pokemon
class Fairy : public Pokemon {
public:
 	Fairy(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts) {}
};

// Constructor prototype for field egg group pokemon -- virtual public b/c some field pokemon have another egg group
class Field : virtual public Pokemon {
public:
 	Field(const std::map<std::string,std::vector<std::string> > &facts);
};

// Empty Constructor because my list has no flying pokemon
class Flying : public Pokemon {
public:
 	Flying(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts) {}
};

// Empty Constructor because my list has no grass pokemon
class Grass : public Pokemon {
public:
 	Grass(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts) {}
};

// Constructor prototype for humanlike egg group pokemon -- virtual public b/c some humanlike pokemon have another egg group
class HumanLike : virtual public Pokemon {
public:
 	HumanLike(const std::map<std::string,std::vector<std::string> > &facts);
};

// Empty constructor since my list has no mineral pokemon
class Mineral : public Pokemon {
public:
 	Mineral(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts) {}
};

// Constructor prototype for monster egg group pokemon -- virtual public b/c some monster pokemon have another egg group
class Monster : virtual public Pokemon {
public:
 	Monster(const std::map<std::string,std::vector<std::string> > &facts);
};

// Empty Constuctor b/c my list has no water 1 pokemon
class Water1 : public Pokemon {
public:
 	Water1(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts) {}
};

// Empty Constuctor b/c my list has no water 2 pokemon
class Water2 : public Pokemon {
public:
 	Water2(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts) {}
};

// Empty Constuctor b/c my list has no water 3 pokemon
class Water3 : public Pokemon {
public:
 	Water3(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts) {}
};

// Empty constructor b/c my list doesn't contain ditto
class Ditto : public Pokemon {
public:
 	Ditto(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts) {}
};

// Empty constructor b/c my list doesn't have any undiscovered pokemon
class Undiscovered : public Pokemon {
public:
 	Undiscovered(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts) {}
};

// Constructor prototype for treecko -- inherits from monster and dragon egg groups
class Treecko : public Monster, public Dragon {
public:
	Treecko(const std::map<std::string,std::vector<std::string> > &facts);
private:

};

// Constructor prototype for Grovyle -- inherits from treecko
class Grovyle : public Treecko {
public:
	Grovyle(const std::map<std::string,std::vector<std::string> > &facts);
};

// Constructor prototype for sceptile -- inherits from grovyle
class Sceptile : public Grovyle {
public:
	Sceptile(const std::map<std::string,std::vector<std::string> > &facts);
};

// Constructor prototype for charmander -- inherits from monster and dragon egg groups
class Charmander : public Monster, public Dragon {
public:
	Charmander(const std::map<std::string,std::vector<std::string> > &facts);
};

// Constructor prototype for charmeleon -- inherits from charmander
class Charmeleon : public Charmander {
public:
	Charmeleon(const std::map<std::string,std::vector<std::string> > &facts);
};

// Constructor prototype for charizard -- inherits from charmeleon
class Charizard : public Charmeleon {
public:
	Charizard(const std::map<std::string,std::vector<std::string> > &facts);
};

// Constructor prototype for buneary -- inherits from field and humanlike egg groups
class Buneary : public Field, public HumanLike {
public:
	Buneary(const std::map<std::string,std::vector<std::string> > &facts);
};

// Constructor prototype for lopunny -- inherits from buneary
class Lopunny : public Buneary {
public:
	Lopunny(const std::map<std::string,std::vector<std::string> > &facts);
};

// Constructor prototype for scyther -- inherits from bug egg group
class Scyther : public Bug {
public:
	Scyther(const std::map<std::string,std::vector<std::string> > &facts);
};

// Constructor prototype for pinsir -- inherits from bugg egg group
class Pinsir : public Bug {
public:
	Pinsir(const std::map<std::string,std::vector<std::string> > &facts);
};