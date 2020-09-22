#include <string>
#include <vector>
#include "champion.h"
class Player {
public:
	Player();
	// Construct with args -- takes name, kills, deaths, wins, losses, and an initial champion
	Player(std::string n,int k, int d,int w, int l,std::string aChampionName);  

	// ACCESSORS
	std::string getName() const;
	int getKills() const;
	int getDeaths() const;
	std::vector <std::string> getChampions () const;

	// SETTERS
	void setName(std::string n);
	void setKills(int k);
	void setDeaths(int d);
	void setChampions(std::vector <std::string> champion_name_list);

	//Other Functions
	void addKill();
	void addDeath();
	void addChampion(std::string aChampionName);
	float calcKDR() const;

	// Functions for custom stuff
	void addAssist();
	void setWins(int numWins);
	void setLosses(int numLosses);
	void calcScore();
	int getScore() const;
	int getAssists() const;
	int getWins() const;
	int getLosses() const;

private:
	std::string name;
	int kills;
	int deaths;
	std::vector <std::string> champion_names; // vector of strings that contains the names of champions used by this player NOT champion classes

	// Variables for custom stuff
	int score;
	int assists;
	int wins;
	int losses;

};
bool isBefore(const Player& player1, const Player& player2); //  for sorting for "players" mode
bool Rank(const Player& player1, const Player& player2); // for sorting for "custom" mode

