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


class Pokemon {
public:
	Pokemon(const std::map<std::string,std::vector<std::string> > &facts);
	std::string getLabel();
	bool SharesEggGroup(Pokemon* other);
	virtual ~Pokemon() {}

	bool idEggGroup(const std::map<std::string,std::vector<std::string> > &facts, std::string eggGroup);
private:
	std::map<std::string,std::vector<std::string> > info; 
};

class Amorphous : public Pokemon {
public:
 	Amorphous(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts) {}
 		//throw 1;
 	//}
private:
};

class Bug : public Pokemon {
public:
 	Bug(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts) {
 		if (idEggGroup(facts,"Bug")==false) {
 			throw 1;
 		}
 	}
private:
};

class Dragon : virtual public Pokemon {
public:
 	Dragon(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts) {
 		if (idEggGroup(facts,"Dragon")==false) {
 			throw 1;
 		}
 	}
private:
};

class Fairy : public Pokemon {
public:
 	Fairy(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts) {
 		throw 1;
 	}
private:
};

class Field : virtual public Pokemon {
public:
 	Field(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts) {
 		if (idEggGroup(facts,"Field")==false) {
 			throw 1;
 		}
 	}
private:
};

class Flying : public Pokemon {
public:
 	Flying(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts) {
 		throw 1;
 	}
private:
};

class Grass : public Pokemon {
public:
 	Grass(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts) {
 		throw 1;
 	}
private:
};

class HumanLike : virtual public Pokemon {
public:
 	HumanLike(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts) {
 		if (idEggGroup(facts,"HumanLike")==false) {
 			throw 1;
 		}
 	}
private:
};

class Mineral : public Pokemon {
public:
 	Mineral(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts) {
 		throw 1;
 	}
private:
};

class Monster : virtual public Pokemon {
public:
 	Monster(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts) {

 		if (idEggGroup(facts,"Monster")==false) {
 			throw 1;
 		}
 	}
private:
};

class Water1 : public Pokemon {
public:
 	Water1(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts) {
 		throw 1;
 	}
private:
};

class Water2 : public Pokemon {
public:
 	Water2(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts) {
 		throw 1;
 	}
private:
};

class Water3 : public Pokemon {
public:
 	Water3(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts) {
 		throw 1;
 	}
private:
};

class Ditto : public Pokemon {
public:
 	Ditto(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts) {
 		throw 1;
 	}
private:
};

class Undiscovered : public Pokemon {
public:
 	Undiscovered(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts) {
 		throw 1;
 	}
private:
};

/*class Treecko : public Monster, public Dragon {
public:
	Treecko(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts), Monster(facts), Dragon(facts) {
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
private:

};*/

class Treecko : public Monster, public Dragon {
public:
	Treecko(const std::map<std::string,std::vector<std::string> > &facts);
private:

};

class Grovyle : public Treecko {
public:
	Grovyle(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts), Treecko(facts) {
		std::map<std::string,std::vector<std::string> >::const_iterator it = facts.find("species");
		std::string data = it->second[0];
		if (!((data=="WoodGecko")||(data=="Forest"))) {
			throw 1;
		} 
		it = facts.find("baseStats");
		int data2 = std::stoi(it->second[0]);
		if (data2<50) {
			throw 1;
		}
		
	}
};

class Sceptile : public Grovyle {
public:
	Sceptile(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts), Grovyle(facts) {
		std::map<std::string,std::vector<std::string> >::const_iterator it = facts.find("species");
		std::string data = it->second[0];
		if (!((data=="WoodGecko")||(data=="Forest"))) {
			throw 1;
		} 
		
		it = facts.find("baseStats");
		int data2 = std::stoi(it->second[0]);
		if (data2<70) {
			throw 1;
		}
		

	}
};

class Charmander : public Monster, public Dragon {
public:
	Charmander(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts), Monster(facts), Dragon(facts) {
		std::map<std::string,std::vector<std::string> >::const_iterator it = facts.find("abilities");
		if (!((it->second[0]=="14")&&(it->second[1]=="0")&&(it->second[2]=="144"))) {
			throw 1;
		} 
		it = facts.find("baseStats");
		int data2 = std::stoi(it->second[0]);
		if (data2<39) {
			throw 1;
		}
	}
private:

};

class Charmeleon : public Charmander {
public:
	Charmeleon(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts), Charmander(facts) {
		std::map<std::string,std::vector<std::string> >::const_iterator it = facts.find("abilities");
		if (!((it->second[0]=="14")&&(it->second[1]=="0")&&(it->second[2]=="144"))) {
			throw 1;
		} 
		it = facts.find("baseStats");
		int data2 = std::stoi(it->second[0]);
		if (data2<58) {
			throw 1;
		}
	}
};

class Charizard : public Charmeleon {
public:
	Charizard(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts), Charmeleon(facts) {
		std::map<std::string,std::vector<std::string> >::const_iterator it = facts.find("abilities");
		if (!((it->second[0]=="14")&&(it->second[1]=="0")&&(it->second[2]=="144"))) {
			throw 1;
		} 
		it = facts.find("baseStats");
		int data2 = std::stoi(it->second[0]);
		if (data2<78) {
			throw 1;
		}
	}
};

class Buneary : public Field, public HumanLike {
public:
	Buneary(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts), Field(facts), HumanLike(facts) {
		std::map<std::string,std::vector<std::string> >::const_iterator it = facts.find("species");
		if ((it->second)[0]!="Rabbit") {
			throw 1;
		}
	}
};

class Lopunny : public Buneary {
public:
	Lopunny(const std::map<std::string,std::vector<std::string> > &facts) : Pokemon(facts), Buneary(facts) {
		std::map<std::string,std::vector<std::string> >::const_iterator it = facts.find("species");
		if ((it->second)[0]!="Rabbit") {
			throw 1;
		}
		it = facts.find("baseStats");
		if ((it->second)[0]!="65") {
			throw 1;
		}
	}
};

class Scyther : public Bug {
public:
	Scyther(const std::map<std::string,std::vector<std::string> > &facts) : Bug(facts) {
		std::map<std::string,std::vector<std::string> >::const_iterator it = facts.find("species");
		if ((it->second)[0]!="Mantis") {
			throw 1;
		}
	}
};

class Pinsir : public Bug {
public:
	Pinsir(const std::map<std::string,std::vector<std::string> > &facts) : Bug(facts) {
		std::map<std::string,std::vector<std::string> >::const_iterator it = facts.find("species");
		if ((it->second)[0]!="Stagbeetle") {
			throw 1;
		}
	}
};