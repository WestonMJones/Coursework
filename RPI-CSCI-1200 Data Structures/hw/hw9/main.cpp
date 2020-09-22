#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include "blast_hash.h"

int main() {

  // Define some place holder variables for parsing the input file
	std::string command;
	std::string arg1;
	std::string arg2;  

  // Define placeholder variables that will eventually hold data to be passed to the table constructor
	std::string filename;
	int table_size = 100;
	float max_occupancy = .5;
	int kmer = 0;

  // In the first round of parsing just grab the info about the initial table setup
	while (std::cin >> command) {
  		if (command=="query") {

        // A query command means we've reached the end up the table info portion of the input file
        // Grab the query arguments and move on
  			std::cin >> arg1;
  			std::cin >> arg2;
  			break;

  		} else if (command=="genome") {

        // Load in the filename to read the genome from
  			std::cin >> arg1;
  			filename = arg1;

  		} else if (command=="table_size") {

        // Load in the initial table size
  			std::cin >> arg1;
  			table_size = std::stoi(arg1);

  		} else if (command=="occupancy") {

        // Load in the occupancy ratio for the table
  			std::cin >> arg1;
  			max_occupancy = std::stof(arg1);

  		} else if (command=="kmer") {

        // Load in the kmer size for the table
  			std::cin >> arg1;
  			kmer = std::stoi(arg1);

  		}
  	}

  	// Now that we have all the table specificiations, construct the table
  	BLAST_hash table(filename,table_size,max_occupancy,kmer);

    // Pass in first query command from when the above loop broke
    table.query(std::stoi(arg1),arg2);

  	// Parse rest of query commands
  	while (std::cin >> command) {

  		if (command=="query") {

  			std::cin >> arg1;
  			std::cin >> arg2;
        table.query(std::stoi(arg1),arg2);

  		} else if (command=="quit") {

        // Exit the final loop upon arriving at "quit"
  			break;

  		}
  	}

	return 0;
}