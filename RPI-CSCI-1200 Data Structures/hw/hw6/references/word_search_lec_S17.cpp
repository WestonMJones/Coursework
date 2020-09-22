#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// Simple class to record the grid location. 
class loc {
public:
  loc(int r=0, int c=0) : row(r), col(c) {}
  int row, col;
};
bool operator== (const loc& lhs, const loc& rhs) { 
  return lhs.row == rhs.row && lhs.col == rhs.col; 
}
// helper function to check if a position has already been used for this word
bool on_path(loc position, std::vector<loc> const& path) {
  for (unsigned int i=0; i<path.size(); ++i)
    if (position == path[i]) return true;
  return false;
}

bool search_from_loc(loc position /* current position */,
                     const std::vector<std::string>& board, const std::string& word,  
                     std::vector<loc>& path /* path leading to the current pos */ ) {

	//std::cout << "Current position: " << position.row << "," << position.col << std::endl;

	//for(unsigned int i=0; i<path.size(); ++i)
        //std::cout << "  " << word[i] << ":  (" << path[i].row << "," << path[i].col << ")\n";

/////////Base cases

	//Went off the board
	int num_rows = board.size();
	int num_cols = board[0].size();
	int curr_row = position.row;
	int curr_col = position.col;
	if( curr_row < 0 || curr_col < 0 ||
			curr_row >=num_rows || curr_col >= num_cols){
		return false;
	}

	
	//We we trying to check if the current letter is the one we want
	//Problem was that initially path is empty, so we're checking
	// word[-1]
  //We accidentally had a new invariant: That the path is never empty
  //Why? Because of how we structured our recursion. We DIDN'T have an invariant
  //that was present in the word_search_sol.cpp (see the assert at the top of the function
  //in that code!)
	if(board[position.row][position.col] != word[path.size()-1]){
		return false;
	}
	

	//Found the full word
	if(path.size() == word.size()){
		return true;
	}

	//Decide where to recurse next

	//suppose i'm at (1,1)
	//could try: (0,0), (0,1), (0,2)
	//					 (1,0), (1,1), (1,2)
	//					 (2,0), (2,1), (2,2)

	for(int xoff = -1; xoff<=1; xoff++){
		for(int yoff = -1; yoff<=1; yoff++){
			loc new_pos;
			new_pos.row = position.row + xoff;
			new_pos.col = position.col + yoff;
			if(xoff == 0 && yoff == 0){ continue; }
			//??? Something goes here
			/*if(board[new_pos.row][new_pos.col] != word[path.size()]){
				continue;
			}*/
			if(on_path(new_pos,path)){ continue; }
			path.push_back(new_pos);
			if(search_from_loc(new_pos,board,word,path)){  //If recursive call finds a solution
				return true;
			}
			else{ //Otherwise
				path.pop_back();
			}
		}
	}

	return path.size() == word.size();
}

// Read in the letter grid, the words to search and print the results
int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " grid-file\n";
    return 1;
  }
  std::ifstream istr(argv[1]);
  if (!istr) {
    std::cerr << "Couldn't open " << argv[1] << '\n';
    return 1;
  }
  std::vector<std::string> board;   
  std::string word;
  std::vector<loc> path;           //  The sequence of locations...
  std::string line;
  //  Input of grid from a file.  Stops when character '-' is reached.
  while ((istr  >> line) && line[0] != '-')
    board.push_back(line);
  while (istr >> word) {
    bool found = false;
    std::vector<loc> path;  //  Path of locations in finding the word
    //  Check all grid locations.  For any that have the first
    //  letter of the word, call the function search_from_loc
    //  to check if the rest of the word is there.
    for (unsigned int r=0; r<board.size() && !found; ++r) {
      for (unsigned int c=0; c<board[r].size() && !found; ++c) {
				//Made changes to the main loop!
        if (board[r][c] == word[0]){
					loc position(r,c);
					path.push_back(position);
            if(search_from_loc(position, board, word, path)){
		 					found = true;
						}
						else{
							path.pop_back();
						}		
				}         
      }
    }
    //  Output results
    std::cout << "\n** " << word << " ** ";
    if (found) {
      std::cout << "was found.  The path is \n";
      for(unsigned int i=0; i<path.size(); ++i)
        std::cout << "  " << word[i] << ":  (" << path[i].row << "," << path[i].col << ")\n";
    } else {
      std::cout << " was not found\n";
    }
  }
  return 0;
}
