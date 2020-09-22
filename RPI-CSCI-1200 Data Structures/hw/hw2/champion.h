#ifndef CHAMPION_H // weird if statement stuff to prevent multiple class definitions
#define CHAMPION_H

#include <string>
class Champion {
public:
	Champion(); // default constructor
	Champion(std::string n,int k, int d,int md); // One with args 

	// ACCESSORS
	std::string getName() const;
	int getWins() const;
	int getLosses() const;
	int getMinionDeaths() const;

	// SETTERS
	void setName(std::string n);
	void setWins(int k);
	void setLosses(int d);
	void setMinionDeaths(int md);

	//Other Functions
	void addWin();
	void addLoss();
	void addMinionDeath();
	float calcWinPercent() const; // calculates and return the win loss ratio in percent form for a champion

	
private:
	std::string name;
	int wins;
	int losses;
	int minion_deaths;
}; 
bool isBefore2(const Champion& c1, const Champion& c2); // sorting helper method
#endif