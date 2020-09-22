// This program computes a seating arrangement for an airline by taking 
// in a seating layout and a stream of commands that assign passengers 
// to seats following certain criteria.

// imports
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>

// Create global vector of alphabet -- referenced by multiple functions to convert from letters to the right numbered column
char alpha[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ" ;
std::vector<char> alphabet( alpha, alpha+sizeof(alpha)-1 );

// functions
void SRN(std::vector<std::vector<std::string>>& upgrade_list, std::vector<std::vector<std::string>>& seating_chart, std::string pass_id, std::string seat_class, std::string freq_flyer,bool upgrade_request) {
  // SRN takes the passengers-to-be-upgraded list, the current seating chart, 
  // a passenger id, requested seating class, frequent flyer status, and then
  // whether or not this is an upgrade request

  // First check class is valid  
  if ((seat_class=="F")||(seat_class=="B")||(seat_class=="C")) {
    // If valid loop through seating chart rows
    for (unsigned int x = 0; x < seating_chart.size(); ++x) {
      // Verify that currently in a row with the right class -- remember that the class letter is stored in index 0 of every sub-vector
      if (seat_class==seating_chart[x][0]) {
        // If row class is correct check for open window and aisle seats. Windows + Aisles --> left to right
        for (unsigned int y=1; y<seating_chart[x].size(); ++y) {
          // ((If on first OR last column) OR Next to aisle) AND Seat is unocuppied
          if (((((y==1) || (y==seating_chart[x].size()-1)))||((seating_chart[x][y-1]=="!!!!")||(seating_chart[x][y+1]=="!!!!")))&& (seating_chart[x][y]=="....")) {
            std::string seat_number = std::to_string(x+1)+alphabet[y-1]; // Construct seat number in from of NumberLetter
            std::cout << "Passenger " << pass_id << " was given seat " << seat_number << "."<<std::endl; // Output message
            seating_chart[x][y]=pass_id; // Update seating chart

            // Output additional message if passenger was upgraded
            if (upgrade_request==true) {
              std::string seat_class_full;
              // Check if bizness or first class
              if (seat_class=="F") {
                seat_class_full="first class";
              } else if (seat_class=="B") {
                seat_class_full="business class";
              }
              std::cout << "Passenger "<<pass_id<<" was upgraded to the "<< seat_class_full<< " section." << std::endl;
            }
            return; // End function and loop if seat is found
          }
        }
      }
    }
    // Initial loop eneded
    // Checked all rows in a class for window + aisle seats.
    // Loop through seating chart again but just pick first available seats this time.
    for (unsigned int x=0;x<seating_chart.size();++x) {
      // Verify that in a row with the right class
      if (seat_class==seating_chart[x][0]) {
        for (unsigned int y=1; y<seating_chart[x].size();++y) {
          if (seating_chart[x][y]=="....") { // if seat is unoccupied.
            std::string seat_number = std::to_string(x+1)+alphabet[y-1]; // Construct seat number in from of NumberLetter
            std::cout << "Passenger " << pass_id << " was given seat " << seat_number << "."<<std::endl; // Output message
            seating_chart[x][y]=pass_id; // Update seating chart
            
            // Output additional message if passenger was upgraded
            if (upgrade_request==true) {
              std::string seat_class_full;
              if (seat_class=="F") {
                seat_class_full="first class";
              } else if (seat_class=="B") {
                seat_class_full="business class";
              }
              std::cout << "Passenger "<<pass_id<<" was upgraded to the "<< seat_class_full<< " section." << std::endl;
            }
            return; // End function and loop if seat is found
          }
        }
      }
    }
  } else {
    // Class doesn't exist
    std::cout << "Invalid seating class - " << seat_class << "."<<std::endl;
    return;
  }
  // Loop ran and no possible seats were found
  // Don't add to upgrade list if passenger is already scheduled for an upgrade
  if (upgrade_request==false) {
    // Check frequent flyer status to see if eligible for upgrade
    if (freq_flyer=="Y") {
      // Attempt to upgrade passenger --> Bizness to first
      if (seat_class=="B") {
        upgrade_list[0].push_back(pass_id);
      } else if (seat_class=="C") { // Coach --> Bizness
        upgrade_list[1].push_back(pass_id);
      }
    } else {
    // Not a frequent flyer or only wanted first class, so no seat/upgrade available
    std::cout << "Could not find a seat in the "<<seat_class <<" section for passenger " << pass_id << "."<<std::endl;
    }
  }
}

void SSR(std::vector<std::vector<std::string>>& upgrade_list, std::vector<std::vector<std::string> >& seating_chart, std::string pass_id, std::string seat_id, std::string freq_flyer) {
  
  // Need to convert the string representation of the seat "NumberLetter" to integer row and column format

  // First, need to account for varying differences in the size of the seat_id
  int sizeMod = seat_id.length()-2;
  
  unsigned int rowNum = atoi(seat_id.substr(0,1+sizeMod).c_str())-1; // Grab first characters of seat_id -- that's one more than the row number because 0 is an index
  unsigned int colNum = 0; // Initialize column value -- will fill in later
  char letter = seat_id.at(1+sizeMod); // Grab letter character
  // Loop through the alphabet untill the letter matches -- the index is one less than that letter's place in the alphabet which becomes the column number
  for (unsigned int i = 0; i < alphabet.size();++i) {
    if (letter==alphabet[i]) {
      colNum = i+1;
    }
  }

  // Check if the seat is within the bounds of the seating chart
  if ((rowNum<=seating_chart.size())&&(colNum<seating_chart[0].size())) {
    // Get the seat class from the row number -- will use this later if requested seat is occupied or invalid
    std::string seat_class = seating_chart[rowNum][0];

    // Seat exists --> Check if empty
    if (seating_chart[rowNum][colNum]=="....") {
      // Assign current passenger if empty
      std::cout << "Passenger " << pass_id << " was given seat " << seat_id << "."<<std::endl;
      seating_chart[rowNum][colNum]=pass_id;
    } else if (seating_chart[rowNum][colNum]=="!!!!") { // Check if the seat is an aisle
      std::cout << "Passenger " << pass_id << " requested an invalid seat " << seat_id << "."<<std::endl;
      SRN(upgrade_list,seating_chart,pass_id,seat_class,freq_flyer,false); // Try to find different seat in same class
    } else { // If none of the conditions above are met, seat must already have a passenger assigned there
      std::cout << "Passenger " << pass_id << " requested an occupied seat " << seat_id << "."<<std::endl;
      SRN(upgrade_list,seating_chart,pass_id,seat_class,freq_flyer,false); // Try to find different seat in same class
    }
  } else { // If seat doesn't exist (outside bounds of seating chart), output a message
    std::cout << "Passenger " << pass_id << " requested an invalid seat " << seat_id << "."<<std::endl;
  }
}

void CXL(std::vector<std::vector<std::string>>& upgrade_list, std::vector<std::vector<std::string> >& seating_chart, std::string pass_id) {
  // Loop through the rows of the seating chart
  for (unsigned int row = 0; row < seating_chart.size();++row) {
    // Loop through the columns of the seating chart -- starting at 1 because 0 holds the class.
    for (unsigned int col=1; col<seating_chart[row].size();++col) {
      // If the passenger_id matches that of the occupant of the seat, make the seat unoccupied and exit the function.
      if (seating_chart[row][col]==pass_id) {
        seating_chart[row][col]="....";
        return;
      }
    }
  }
  // Check upgrade list for the passenger -- if found change to "NULL" to indicate a deleted value
  for (unsigned int i=0;i<upgrade_list.size();++i) {
    for (unsigned int x=0;x<upgrade_list[i].size();++x) {
      if (upgrade_list[i][x]==pass_id) {
        upgrade_list[i][x]="NULL";
        return;
      }
    }
  }
  // If both loops ended without finding anyone, passenger must not exist
  std::cout << "Passenger " << pass_id << " could not be found." << std::endl;
}

void PRT(std::string flightno, std::vector<std::vector<std::string> >& seating_chart) {
	// Print header for chart
  std::cout << "Seating Chart for Flight " << flightno << std::endl;
	//Create column letter headers by looping through the global alphabet vector
	std::cout << "\t"; 
	for (unsigned int x = 0; x < seating_chart[0].size()-1; ++x) {
		std::cout << alphabet[x] << "    ";
	}
  // Adding the "seating class" column header
	std::cout << "Seating Class" << std::endl;

  // Now print the actual seating chart -- first loop through the rows
	for (unsigned int x = 0; x < seating_chart.size(); ++x) {
    // Begin each row with a number -- adjusted to compensate for the "0" starting point
		std::cout << x+1 << "\t";
    // Loop through the columns
  		for (unsigned int y=1; y<seating_chart[x].size(); ++y) {
  			std::cout << seating_chart[x][y] << " "; // output the passenger ids, "...."s, and "!!!!"s
  		}
  		std::cout << seating_chart[x][0] << std::endl; // Output the seating class on the rightmost column -- I stored those values in index 0 of every column vector
  	}
}

void UPL(std::vector<std::vector<std::string> >& upgrade_list) {
  std::cout << "The following passengers are scheduled to be upgraded to first class:" << std::endl;
  // Index 0 of the "row" vector has the first class upgrades
  for (unsigned int i=0; i<upgrade_list[0].size();++i) {
    if (upgrade_list[0][i]!="NULL") { // Passengers deleted from the upgrade list have their id's changed to NULL -- ignore these values
      std::cout << upgrade_list[0][i] << std::endl;
    }
  }
  std::cout << "The following passengers are scheduled to be upgraded to business class:" << std::endl;
  // index 1 of the "row" vector has the bizness class upgrades
  for (unsigned int i=0; i<upgrade_list[1].size();++i) {
    if (upgrade_list[1][i]!="NULL") { // Passengers deleted from the upgrade list have their id's changed to NULL -- ignore these values
      std::cout << upgrade_list[1][i] << std::endl;
    }
  }
}

void UPP(std::vector<std::vector<std::string> >& upgrade_list, std::vector<std::vector<std::string> >& seating_chart) {
  std::string seat_class; // create empty seat class variable to be assigned a value later
  for (unsigned int x=0; x<upgrade_list.size();++x) {
    for (unsigned int y=0; y<upgrade_list[x].size();++y) {
      if (upgrade_list[x][y]!="NULL") { // ignore NULL values as those refer to passengers who were removed from the upgrade_list with the CXL cmd
        if (x==0) {
          seat_class="F";
        } else if (x==1) {
          seat_class="B";
        }
      SRN(upgrade_list,seating_chart,upgrade_list[x][y],seat_class,"N",true); // Now that we have the proper seating class -- run a SRN command with upgrade
      // request assigned to TRUE to output the additional message if a seat was found.
      }
    }
  }
}

int main(int argc, char* argv[]) {
  //seats = argv[1] and commands = argv[2]
	//Read the seating arrangment in vectors
	std::ifstream in_str(argv[1]);

	// Make main seating chart 2D Vector
	// the first element of every subvector 
	// will be the letter indicating which class
	// A row is in
	std::vector<std::vector<std::string> > seating_chart;

	//Temporary vector to hold stuff
	std::vector<std::string> row;

  // Create the upgrade vector
  // index (1) contains a vector of first class
  // index 2 contains a vector of biz class
  std::vector<std::vector<std::string>> upgrade_list;
  upgrade_list.push_back(row);
  upgrade_list.push_back(row);

	//Temporary variable to see if on the first row of the seating chart
	bool first = true;

	//Load seating chart into a 2D vector of strings
	if (in_str.good()) {
		std::string my_variable; // this variable holds the current input
    	while (in_str >> my_variable) {
    		if ((my_variable=="F") || (my_variable=="B") || (my_variable=="C")) {
    			// New row -- if first don't add anything to seating_chart. If not first, add previous row to seating chart
    			if (!first) {
    				seating_chart.push_back(row);
    			} else {
    				first = false;
    			}
    			row.clear();
    			row.push_back(my_variable);
    		} else {
    			// Not a new row
    			if (my_variable=="!") { // "!"s refer to aisles
    				row.push_back("!!!!");
    			} else if (my_variable==".") { // "."s refer to empty seats
    				row.push_back("....");
    			}
    		}
  		}
  		seating_chart.push_back(row); // Add final row to chart now that loop has ended
  	} else {std::cout << "Something went wrong" << std::endl;} // output error if file read wasn't good
  	in_str.close();

	//Next, load the commands in
  	std::ifstream in_str2(argv[2]);
  	if (in_str2.good()) {
  		// Handle the first line to get the flight number
  		std::string text;
  		in_str2 >> text;
  		std::string flightno = text;
  		while (in_str2 >> text) { // parse through the rest of the file
  			// Read rest of commands

        // Set up placeholder variables to be loaded with data as commands are read
  			std::string pass_id;
  			std::string freq_flyer;
  			std::string seat_class;
  			std::string seat_id;

  			if (text=="SRN") {
  				//SRN CMD
  				in_str2 >> pass_id;
  				in_str2 >> seat_class;
  				in_str2 >> freq_flyer;
  				SRN(upgrade_list,seating_chart,pass_id,seat_class,freq_flyer,false);

  			} else if (text=="SSR") {
  				//SSR CMD
  				in_str2 >> pass_id;
  				in_str2 >> seat_id;
  				in_str2 >> freq_flyer;
  				SSR(upgrade_list,seating_chart,pass_id,seat_id,freq_flyer);
  			} else if (text=="CXL") {
  				// CXL CMD
  				in_str2 >> pass_id;
  				CXL(upgrade_list,seating_chart,pass_id);
  			} else if (text=="UPL") {
  				// UPL CMD
          UPL(upgrade_list);
  			} else if (text=="UPP") {
  				// UPP CMD
          UPP(upgrade_list,seating_chart);
  			} else if (text=="PRT") {
  				// PRT CMD
  				PRT(flightno,seating_chart);
  			} else {
  				//Invalid CMD
  				std::cout << "Invalid command: " << text << std::endl;
  			}
  		}
  	}
	return 0;
}