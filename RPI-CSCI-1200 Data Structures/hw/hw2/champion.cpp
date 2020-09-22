#include <string>
#include "champion.h"

Champion::Champion() {
	name = "undefined";
	wins = 0;
	losses = 0;
	minion_deaths = 0;
}

Champion::Champion(std::string n, int w, int l, int md ) {
	name = n;
	wins = w;
	losses = l;
	minion_deaths = md;
}

std::string Champion::getName() const {
	return name;
}

int Champion::getWins() const {
	return wins;
}

int Champion::getLosses() const {
	return losses;
}

int Champion::getMinionDeaths() const {
	return minion_deaths;
}

void Champion::setName(std::string n) {
	name = n;
}

void Champion::setWins(int w) {
	wins = w;
}

void Champion::setLosses(int l) {
	losses=l;
}

void Champion::setMinionDeaths(int md) {
	minion_deaths = md;
}

void Champion::addWin() {
	wins = wins + 1;
}

void Champion::addLoss() {
	losses = losses + 1;
}

void Champion::addMinionDeath() {
	minion_deaths = minion_deaths + 1;
}

float Champion::calcWinPercent() const {
	// calculates and return the win loss ratio in percent form for a champion
	if (wins==0) {
		return 0.00;
	} else if (losses==0) {
		return 1.00;
	} else {
		return (float)wins / (float)(losses+wins);
	}
}

bool isBefore2(const Champion& c1, const Champion& c2) {
	// Sorts via the HW pdf instructions as copied below
	//Overall this table is sorted by win percentage, highest first. If tied in win percentage,
 	//champions should be sorted by wins, then by losses, and finally by name if all of the above are equal.
 	if (c1.calcWinPercent()>c2.calcWinPercent()) {
 		return true;
 	} else if (c1.calcWinPercent()<c2.calcWinPercent()) {
 		return false;
 	} else {
 		if (c1.getWins()>c2.getWins()) {
 			return true;
 		} else if (c1.getWins()<c2.getWins()) {
 			return false;
 		} else {
 			if (c1.getLosses()<c2.getLosses()) {
 				return true;
 			} else if (c1.getLosses()>c2.getLosses()) {
 				return false;
 			} else {
 				if (c1.getName()<c2.getName()) {
 					return true;
 				} else {
 					return false;
 				}
 			}
 		}
 	}
}
