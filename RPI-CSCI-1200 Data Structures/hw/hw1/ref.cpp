// main.cpp - a very simple seating chart gnerator for a fictitious airline
//

#include <string>
#include <cstdlib>

// a constamt for genrating seat aisle labels
const std::string ALPHABET("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

// return the row and column from a seat request
//
// Note: This code assumes that the seat chart is stored in a 2D vector or
//       array. If you are using a differnt structure for storing seat
//       information, it won't help.
//
// arguments:
// seat_request - a string of row and colummn, eg. 1A
// total_rows - the number of rows in the seating chart
// total_rows - the number of columns in the seating chart, including aisles
// seat_row, seat_col - the seat row and column. If the seat_request is
//                      formatted properly, on return these variables will
//                      contain the row and column of the seat (0-indexed)
//                      
//
// returns;
// true if the seat request contains a valid seat. false otherwise
//
// a seat is valid if its row number is >= 1 and <= the number of rows and
// its column falls in the alphabet in the range of columns.
bool GetSeatRowCol(const std::string& seat_request,
		   unsigned int total_rows,
		   unsigned int total_columns,
		   int& seat_row, std::size_t& seat_col) {
  
  std::string row_str;
  std::string col_str;
  for (unsigned int i = 0; i < seat_request.size(); ++i) {
    if (seat_request[i] >= '0' && seat_request[i] <= '9')
      row_str += seat_request[i];
    else
      col_str += seat_request[i];	
  }
    
  seat_row = atoi(row_str.c_str()) - 1;
  if (seat_row < 0 || seat_row > (int) total_rows - 1) {
    return false;
  }

  seat_col = ALPHABET.find(col_str);
  if (seat_col == std::string::npos || seat_col > total_columns - 1) {
    return false;
  }

  return true;
}


int main(int argc, char* argv[]) {

  return 0;
}
