// imports
#include <iostream>
#include <iomanip> 
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <algorithm>
#include "player.h"
#include "champion.h"

std::string receiveChampionNames(std::vector<std::string> names) {
    // Function that -- given a vector of champion names -- sorts them and 
    // returns them in string format that can be utilized in a table
    std::string temp="";
    sort( names.begin(), names.end() );
    names.erase(std::unique(names.begin(), names.end()), names.end()); // remove duplicate entries
    for (unsigned int x=0;x<names.size();++x) {
        temp = temp+ names[x]+", ";
    }
    temp.pop_back(); // remove last space and comma
    temp.pop_back();
    return temp;
}

void updatePlayerList(std::vector <Player>& player_list,std::string name,int kills,int deaths,int wins, int losses,std::string champion) {
    // updates the list of players given a set of info
    bool newPlayerEntry = true;
    for (unsigned int playerno=0;playerno<player_list.size();++playerno) { // loop through player list
        if (player_list[playerno].getName()==name) {
            // Player already exists
            newPlayerEntry = false;
            player_list[playerno].setKills(kills + player_list[playerno].getKills()); // update kill, death, win count etc
            player_list[playerno].setDeaths(deaths + player_list[playerno].getDeaths());
            player_list[playerno].setWins(wins + player_list[playerno].getWins());
            player_list[playerno].setLosses(losses + player_list[playerno].getLosses());
            player_list[playerno].addChampion(champion); // Adds the name of the current champion
        }
    }
    if (newPlayerEntry==true) { // if the player is new -- wasn't found in list
            // Player doesn't exist
            Player aPlayer(name,0,0,wins,losses,champion);
            player_list.push_back(aPlayer);
    }
}

void updateChampionList(std::vector <Champion>& champion_list,std::string name,int wins,int losses,int minion_deaths) {
    bool newChampEntry = true;
    for (unsigned int championno=0;championno<champion_list.size();++championno) {
        if (champion_list[championno].getName()==name) {
            // Champion already exists
            newChampEntry = false;
            // update existing champion by adding values
            champion_list[championno].setWins(wins + champion_list[championno].getWins() );
            champion_list[championno].setLosses(losses + champion_list[championno].getLosses() );
            champion_list[championno].setMinionDeaths(minion_deaths + champion_list[championno].getMinionDeaths() );
        } 
    }
    if (newChampEntry) {
        // champion has yet to be added
        Champion aChampion(name,wins,losses,0);
        champion_list.push_back(aChampion);
    }
}
int main(int argc, char* argv[]) {
	// argv[1] = input file | argv[2] = output file | argv[3] = type

    // First create two vectors -- one of players and one of champions
    std::vector <Player> player_list;
    std::vector <Champion> champion_list;

	// First read the input file
	std::ifstream in_str(argv[1]);
	if (in_str.good()) {
		std::string current_input; // this variable holds the current input

		// Create generic playerholder variables to store parsed names and the champions + players of this round
		std::string name;
		std::string name2;
        std::vector <std::string> current_players;
        std::vector <std::string> current_champs;

    	while (in_str >> current_input) {
    		// Space to do stuff to input
    		if (current_input=="MATCH") {
    			// Start of a new match
    			in_str >> current_input; // skip word ID
    			in_str >> current_input; // skip ID Number
    			in_str >> current_input; // Load in "Winning / Losing"

    			// Create variable that will indicate which team won and lost
    			bool on_winning_team;

                // temporary variables for storing initial wins and losses
                int initial_wins;
                int initial_losses;

                // See if winning or losing team is going first and plan accordingly
    			if (current_input=="WINNING") {
    				on_winning_team=true;
                    initial_wins=1;
                    initial_losses=0;
    			} else if (current_input=="LOSING") {
    				on_winning_team=false;
                    initial_wins=0;
                    initial_losses=1;
    			}
				// Get champion and player names
				in_str >> current_input; // Skip "Team"
				for (unsigned int i=0;i<5;++i) {
					in_str >> name; // Load player name
					in_str >> current_input; // skip "playing"
					in_str >> current_input; // skip "champion"
					in_str >> name2; // get champion name

                    // Define new champion and player classes and add them to their respective lists. These methods
                    // account for existing player classes.
                    updateChampionList(champion_list,name2,initial_wins,initial_losses,0);
                    updatePlayerList(player_list,name,0,0,initial_wins,initial_losses,name2);

                    // update list of current players 
                    current_players.push_back(name);
                    current_champs.push_back(name2);

				}
				in_str >> current_input; // Input winning / losing
                // check again for which team we're on
                if (current_input=="WINNING") {
                    on_winning_team=true;
                    initial_wins=1;
                    initial_losses=0;
                } else if (current_input=="LOSING") {
                    on_winning_team=false;
                    initial_wins=0;
                    initial_losses=1;
                }
				in_str >> current_input; // Skip "Team"
				for (unsigned int i=0;i<5;++i) {
					in_str >> name; // Load player name
					in_str >> current_input; // skip "playing"
					in_str >> current_input; // skip "champion"
					in_str >> name2; // get champion name

                    // Define new champion and player classes and add them to their respective lists. These methods
                    // account for existing player classes.
                    updateChampionList(champion_list,name2,initial_wins,initial_losses,0);
                    updatePlayerList(player_list,name,0,0,initial_wins,initial_losses,name2);

                    // update list of current players 
                    current_players.push_back(name);
                    current_champs.push_back(name2);
				}
    		} else if (current_input=="EVENTS") {
    			// Check if @ -- a command -- or a "END" -- the end of the current game.
    			while (true) { // infinite loop until broken off
    				in_str >> current_input; 
    				if (current_input=="@") {
    					// Extract killer and killed from the line
    					in_str >> current_input; // first Skip over the timestamp
    					in_str >> name; // Get killer name
    					in_str >> current_input; // Load next input -- either "killed" or "["

    					//Handle the brackets for assists -- first check for brackets
    					if (current_input=="[") {
    						// Multiple potential assists in the kill
    						while (true) {
    							in_str >> current_input;
    							if (current_input=="]") { // Check when at end of assist list
    								break; // if so, break off 
    							} else { // if not, add an assist count to the current player
                                    for (unsigned int playerno=0;playerno<player_list.size();playerno++) {
                                        if (current_input==player_list[playerno].getName()) {
                                            player_list[playerno].addAssist();
                                        }
                                    }
                                }
    						}
    						in_str >> current_input; // Skip the word "killed"
    					}
    					in_str >> name2; // Get killed's name
                        if (name=="minion") {
                            // Handle minion deaths
                            for (unsigned int playerno=0;playerno<current_players.size();++playerno) {
                                // Look through player list for find the name of the player who got minion killed
                                if (name2==current_players[playerno]) {
                                    // Found the right player -- get what champion he was playing
                                    std::string temp_champ_name = current_champs[playerno];
                                    // Update that champion's minion death count
                                    for (unsigned int champno=0;champno<champion_list.size();++champno) {
                                        if (temp_champ_name==champion_list[champno].getName()) {
                                            champion_list[champno].addMinionDeath();
                                        }
                                    }
                                }
                            }
                            // Also need to update the list of players with the minion death
                            for (unsigned int playerno=0;playerno<player_list.size();++playerno) {
                                if (name2==player_list[playerno].getName()) {
                                    player_list[playerno].addDeath();
                                }
                            }
                        } else {
                            // Not a minion death
                            for (unsigned int playerno=0;playerno<player_list.size();++playerno) {
                                if (player_list[playerno].getName()==name) {
                                    // Matches the name of the person who scored a kill
                                    player_list[playerno].addKill();
                                }
                                if (player_list[playerno].getName()==name2) {
                                    // Matches the name of the person who got killed
                                    player_list[playerno].addDeath();
                                }
                            }
                        }
    				} else if (current_input=="END") {
                        // end of the "EVENT" section -- clear vectors that hold game specific stuff
                        current_champs.clear();
                        current_players.clear();
    					break; // break out of infinite loop
    				}
    			}
    		}
    	}
    }

    // Classes + Vectors are all set up -- need to write output now

    // Initialize stream writer
    std::ofstream out_str(argv[2]);
    if (!out_str.good()) {
        std::cout << "Can't open " << argv[3] << " to write.\n";
        exit(1);
    }

    std::string cmd_type=argv[3]; // convert 3rd cmd line arg to string for easy comparison

    if (cmd_type=="players") {
        // Player table
        sort(player_list.begin(), player_list.end(), isBefore); // Sort players as per .pdf instructions

        // construct table headers
        out_str << std::setw(20) << std::left <<"PLAYER NAME" << std::setw(8) << std::right << "KILLS" << std::setw(8) << std::right << 
        "DEATHS" << std::setw(8) << std::right << "KDR" <<"   " << "PLAYED WITH CHAMPION(S)" << "\n";

        // construct the table rows
        for (unsigned int playerno=0;playerno<player_list.size();++playerno) {
            out_str << std::setw(20) << std::left << player_list[playerno].getName();
            out_str << std::setw(8) << std::right << player_list[playerno].getKills();
            out_str << std::setw(8) << std::right << player_list[playerno].getDeaths();
            out_str << std::setw(8) << std::right << std::setprecision(2) << std::fixed << player_list[playerno].calcKDR() << "   ";
            out_str << receiveChampionNames(player_list[playerno].getChampions()) << "\n";
        }
        out_str.close(); // close stream when done.
    } else if (cmd_type=="champions") {
        // Champion table
        sort(champion_list.begin(), champion_list.end(), isBefore2); // sort champions as per the HW instructions

        // construct table headers
        out_str << std::setw(20) << std::left <<"CHAMPION NAME" << std::setw(8) << std::right << "WINS" << std::setw(8) << std::right << 
        "LOSSES" << std::setw(8) << std::right << "WIN%" <<"   " << "MINION DEATHS" << "\n";

        // Construct table rows
        for (unsigned int champno=0;champno<champion_list.size();++champno) {
            out_str << std::setw(20) << std::left << champion_list[champno].getName();
            out_str << std::setw(8) << std::right << champion_list[champno].getWins();
            out_str << std::setw(8) << std::right << champion_list[champno].getLosses();
            out_str << std::setw(8) << std::right << 
            std::setprecision(2) << std::fixed 
                                    << champion_list[champno].calcWinPercent();
            out_str << std::setw(16) << std::right << champion_list[champno].getMinionDeaths() << "\n";
        }
        out_str.close(); // close steam when done

    } else if (cmd_type=="custom") {
        // Custom table
        // Calculate all the players' scores
        for (unsigned int playerno=0;playerno<player_list.size();playerno++) {
            player_list[playerno].calcScore();
        }
        sort(player_list.begin(), player_list.end(), Rank); // sort players by score (descending) then lexographically
        // Construct headers: Place, Name, Score, Kills, Deaths, KDR, Assists, Wins, Losses
        out_str << 
        std::setw(8) << std::left << "PLACE" << 
        std::setw(20) << std::left << "PLAYER NAME" <<
        std::setw(8) << std::left << "SCORE" << 
        std::setw(8) << std::left << "KILLS" <<
        std::setw(8) << std::left << "DEATHS" <<
        std::setw(8) << std::left << "KDR" <<
        std::setw(8) << std::left << "ASSISTS" <<
        std::setw(8) << std::left << "WINS" <<
        std::setw(8) << std::left << "LOSSES" << "\n";

        // Construct table rows
        for (unsigned int playerno=0;playerno<player_list.size();playerno++) {
            out_str << std::setw(5) << std::right << playerno+1 << ".  "; 
            out_str << std::setw(20) << std::left << player_list[playerno].getName();
            out_str << std::setw(8) << std::left << player_list[playerno].getScore();
            out_str << std::setw(8) << std::left << player_list[playerno].getKills();
            out_str << std::setw(8) << std::left << player_list[playerno].getDeaths();
            out_str << std::setw(8) << std::left << std::setprecision(2) << std::fixed << player_list[playerno].calcKDR();
            out_str << std::setw(8) << std::left << player_list[playerno].getAssists();
            out_str << std::setw(8) << std::left << player_list[playerno].getWins();
            out_str << std::setw(8) << std::left << player_list[playerno].getLosses() << "\n";
        }

    }
	return 0;
}


