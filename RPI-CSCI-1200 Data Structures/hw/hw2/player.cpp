#include <string>
#include <vector>
#include "player.h"
#include "champion.h"
#include <algorithm>

Player::Player() {
	name = "undefined";
	kills = 0;
	deaths = 0;
	score = 0;
	assists=0;
	wins = 0;
	losses = 0;
}
Player::Player(std::string n, int k, int d,int w,int l, std::string aChampionName ) {
	name = n;
	kills = k;
	deaths = d;
	wins = w;
	losses = l;
	// the way my code is set up, assists and score are only worked on later and will never have an initial value other than zero
	assists = 0; 
	score =0;
	addChampion(aChampionName);
}

std::string Player::getName() const {
	return name;
}

int Player::getKills() const {
	return kills;
}

int Player::getDeaths() const {
	return deaths;
}

std::vector <std::string> Player::getChampions() const {
	return champion_names;
}

void Player::setName(std::string n) {
	name = n;
}

void Player::setKills(int k) {
	kills = k;
}

void Player::setDeaths(int d) {
	deaths=d;
}

void Player::setChampions(std::vector <std::string> champion_name_list) {
	champion_names = champion_name_list;
}

void Player::addKill() {
	kills = kills + 1;
}

void Player::addDeath() {
	deaths = deaths + 1;
}

void Player::addChampion(std::string aChampionName) {
	champion_names.push_back(aChampionName);
}

float Player::calcKDR() const {
	// calculates and returns the float form of the KD ratio
	if (kills==0) {
		return 0.00;
	} else if (deaths==0) {
		return (float)kills + .00;
	} else {
		return (float)kills / (float)deaths;
	}
}

bool isBefore(const Player& player1, const Player& player2) {
	// Sorts by these criteria
	// KDR
	// Kills
	// Deaths
	// Player Name

	if (player1.calcKDR()>player2.calcKDR()) {
		return true;
	} else if (player1.calcKDR()<player2.calcKDR()) {
		return false;
	} else {
		// equal KDRs -- check kills
		if (player1.getKills()>player2.getKills()) {
			return true;
		} else if (player1.getKills()<player2.getKills()) {
			return false;
		} else {
			// equal KDRS and Kills -- check deaths
			if (player1.getDeaths()<player2.getDeaths()) {
				return true;
			} else if (player1.getDeaths()>player2.getDeaths()) {
				return false;
			} else {
				// equal KDRS, KILLS, and Deaths -- check names
				if (player1.getName()<player2.getName()) {
					return true;
				} else {
					return false;
				}
			}
		}
	}
}
void Player::calcScore() {
	/*Kills are worth 10 points
 	Assists are worth 2 points 
 	Winning a match is worth 5 points
 	A death is worth -4 points
 	losing a match doesn't effect your score.*/
	score = (score + (10*getKills()) + (2*getAssists()) + (5*getWins())) - (4*getDeaths());
}

void Player::addAssist() {
	assists = assists + 1;
}
void Player::setWins(int numWins) {
	wins = numWins;
}
void Player::setLosses(int numLosses) {
	losses = numLosses;
}
int Player::getScore() const {
	return score;
}
int Player::getAssists() const{
	return assists;
}
int Player::getWins() const{
	return wins;
}
int Player::getLosses() const {
	return losses;
}
bool Rank(const Player& player1, const Player& player2) {
	// sorting helper method
	// sorts by score then lexographically
	if (player1.getScore()>player2.getScore()) {
		return true;
	} else if (player1.getScore()<player2.getScore()) {
		return false;
	} else {
		if (player1.getName()<player2.getName()) {
			return true;
		} else {
			return false;
		}
	}
}
