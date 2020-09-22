#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <list>

// Checks if a word can fit into the board at the current position oriented diagonally going upwards and left
bool check_up_left(std::vector< std::vector<char> >& current_board, 
					std::string& word, int row, int col) {

	// Count which char of the word we're on
	int count = 0;

	// loop through characters of word
	while (count<word.size()) {
		// if out on bounds, return false, cuz word def can't fit
		if ((col<0)||(row<0)) {
			return false;
		} else {
			// check if current char can fit
			if ((current_board[row][col]=='.')||(current_board[row][col]==word[count])) {
				// if so, increment to check next char and next position in the board
				count++;
				col--;
				row--;
			} else {
				// else, exit
				return false;
			}
		}
	}
	// All chars passed, so return true
	return true;
}

// Checks if a word can fit into the board at the current position oriented diagonally going upwards and right
// reuses a lot of the same code from above
bool check_up_right(std::vector< std::vector<char> >& current_board, 
					std::string& word, int row, int col) {

	// Count which char of the word we're on
	int count = 0;
	while (count<word.size()) {
		// check bounds
		if ((row<0)||(col>current_board[row].size()-1)) {
			return false;
		} else {
			// check if current char works in the current position
			if ((current_board[row][col]=='.')||(current_board[row][col]==word[count])) {
				// increment position and character in the word
				count++;
				col++;
				row--;
			} else {
				return false;
			}
		}
	}
	// if loop out through everything, then return true
	return true;
}

// Checks if a word can fit into the board at the current position oriented diagonally going downwards and left
bool check_down_left(std::vector< std::vector<char> >& current_board, 
					std::string& word, int row, int col) {

	int count = 0;
	while (count<word.size()) {
		// check within bounds of board
		if ((row>current_board.size()-1)||(col<0)) {
			return false;
		} else {
			// check if char works at current position
			if ((current_board[row][col]=='.')||(current_board[row][col]==word[count])) {
				count++;
				col--;
				row++;
			} else {
				return false;
			}
		}
	}
	return true;
}

// Checks if a word can fit into the board at the current position oriented diagonally going downwards and right
bool check_down_right(std::vector< std::vector<char> >& current_board, 
					std::string& word, int row, int col) {

	int count = 0;
	while (count<word.size()) {
		// check bounds
		if ((row>current_board.size()-1)||(col>current_board[row].size()-1)) {
			return false;
		} else {
			// check if it can fit in current position
			if ((current_board[row][col]=='.')||(current_board[row][col]==word[count])) {
				count++;
				col++;
				row++;
			} else {
				return false;
			}
		}
	}
	return true;
}

// Checks if a word can fit into the board at the current position going straight to the left
bool check_left(std::vector< std::vector<char> >& current_board, 
					std::string& word, int row, int col) {

	int count = 0;
	// check bounds
	while (count<word.size()) {
		if (col<0) {
			return false;
		} else {
			// check current position in the board
			if ((current_board[row][col]=='.')||(current_board[row][col]==word[count])) {
				// increment position within the word and position in the board to be checked next
				count++;
				col--;
			} else {
				return false;
			}
		}
	}
	return true;
}

// Checks if a word can fit into the board at the current position going straight to the right
// Code basically works the same as functions above
bool check_right(std::vector< std::vector<char> >& current_board, 
					std::string& word, int row, int col) {

	int count = 0;
	while (count<word.size()) {
		if (col>current_board[row].size()-1) {
			return false;
		} else {
			if ((current_board[row][col]=='.')||(current_board[row][col]==word[count])) {
				count++;
				col++;
			} else {
				return false;
			}
		}
	}
	return true;
}

// Checks if a word can fit into the board at the current position going straight down
bool check_down(std::vector< std::vector<char> >& current_board, 
					std::string& word, int row, int col) {

	int count = 0;
	while (count<word.size()) {
		if (row>current_board.size()-1) {
			return false;
		} else {
			if ((current_board[row][col]=='.')||(current_board[row][col]==word[count])) {
				count++;
				row++;
			} else {
				return false;
			}
		}
	}
	return true;
}

// Checks if a word can fit into the board at the current position going straight upwards
bool check_up(std::vector< std::vector<char> >& current_board, 
					std::string& word, int row, int col) {

	int count = 0;
	while (count<word.size()) {
		if (row<0) {
			return false;
		} else {
			if ((current_board[row][col]=='.')||(current_board[row][col]==word[count])) {
				count++;
				row--;
			} else {
				return false;
			}
		}
	}
	return true;
}

// The compiler was yelling at me for not prototyping these functions -- ignore this for now

bool check_solution(std::vector<std::vector<char> >& current_board,std::vector<std::string>& bad_words);
void fill_blanks(std::list< std::vector<std::vector<char> > >& solutions,
	std::vector<std::vector<char> >& current_board, 
	std::vector<std::string>& bad_words
	);


/*
Aptly named main recursive function

Takes for parameters:
1. A current view of the board
2. The solutions board -- passed by reference
3. Vector of words to include
4. Vector of words to exclude
5. An integer to signal which "word to include" the function is on
6. A flag to determine if the program is being run in one_solution or all_solutions mode
7. A flag to signal when to stop recursion if being run in one_solution mode <-- didn't end up implementing this

*/

void ugh_recursion(std::vector< std::vector<char> >& current_board, 
					std::list< std::vector<std::vector<char> > >& solutions,
					 std::vector<std::string>& good_words,
					 std::vector<std::string>& bad_words,
					unsigned int current_word,
					bool one_solution,
					bool& go_on) {

	// Check if recursion has been stopped and if at the end of the words to include vector
	if ((go_on)&&(current_word<good_words.size())) {

		// Loop through 2D vector representing the current board 
		for (unsigned int row=0;row<current_board.size();row++) {
			for (unsigned int col=0;col<current_board[row].size();col++) {
				// FOr every slot in the board, check to see if the current word can fit in any 
				// of the 8 directions

				// Check left across
				if (check_left(current_board,good_words[current_word],row,col)) {

					// If check passes, copy the board and add word to the copy
					std::vector< std::vector<char> > new_board = current_board;
					for (unsigned int i=0;i<good_words[current_word].size();i++) {
						// Decrement column since moving left
						new_board[row][col-i]=good_words[current_word][i];
					}

					// Check if that was the last word to include
					if (current_word==good_words.size()-1) {
						// If so...

						// I had meant to implement an early stop for the one solution mode but I realized it wouldn't work
						// the way I had it implemented, so I just got rid of it.
						// Check if in on solution mode, if so, stop recursion and end program a bit earlier
						// 
						// if (one_solution==true) {
						// 	go_on=false;
						// }

						// Call fill_blanks method which will fill banks, check for any "bad words", and add all valid solutions to the list
						fill_blanks(solutions,new_board,bad_words);
					} else {
						// If not the last word...RECURSION TIME
						// All parameters are the same, except increment "current word" to move to next word to include
						ugh_recursion(new_board,solutions,good_words,bad_words,current_word+1,one_solution,go_on);
					}
				}

				// Check right across direction
				if(check_right(current_board,good_words[current_word],row,col)) {
					// Add word to a board copy if it can fit
					std::vector< std::vector<char> > new_board = current_board;
					for (unsigned int i=0;i<good_words[current_word].size();i++) {
						new_board[row][col+i]=good_words[current_word][i];
					}
					// check if last word
					if (current_word==good_words.size()-1) {
						// last word

						// Call fill_blanks method which will fill banks, check for any "bad words", and add all valid solutions to the list
						fill_blanks(solutions,new_board,bad_words);
					} else {
						// not last word -- recurse again on next word
						ugh_recursion(new_board,solutions,good_words,bad_words,current_word+1,one_solution,go_on);
					}
				}

				// Check upwards
				if(check_up(current_board,good_words[current_word],row,col)) {
					// If check passes, Add word to a board copy
					std::vector< std::vector<char> > new_board = current_board;
					for (unsigned int i=0;i<good_words[current_word].size();i++) {
						new_board[row-i][col]=good_words[current_word][i];
					}

					// check if last word
					if (current_word==good_words.size()-1) {
						// last word

						

						// fill blanks method
						fill_blanks(solutions,new_board,bad_words);
					} else {
						// not last word -- increment to next word and recurse again
						ugh_recursion(new_board,solutions,good_words,bad_words,current_word+1,one_solution,go_on);
					}
				}

				// Check downwards -- basically everything is the same as before
				if(check_down(current_board,good_words[current_word],row,col)) {

					// Add word to the board
					std::vector< std::vector<char> > new_board = current_board;
					for (unsigned int i=0;i<good_words[current_word].size();i++) {
						new_board[row+i][col]=good_words[current_word][i];
					}

					// check if last word
					if (current_word==good_words.size()-1) {
						// last word

						
						fill_blanks(solutions,new_board,bad_words);
					} else {
						// not last word
						ugh_recursion(new_board,solutions,good_words,bad_words,current_word+1,one_solution,go_on);
					}
				}

				// Check downwards left direction 
				if(check_down_left(current_board,good_words[current_word],row,col)) {
					// Add word to the board
					std::vector< std::vector<char> > new_board = current_board;
					for (unsigned int i=0;i<good_words[current_word].size();i++) {
						new_board[row+i][col-i]=good_words[current_word][i];
					}
					if (current_word==good_words.size()-1) {
						// last word
						
						fill_blanks(solutions,new_board,bad_words);
					} else {
						// not last word
						ugh_recursion(new_board,solutions,good_words,bad_words,current_word+1,one_solution,go_on);
					}
				}

				// Check down right
				if(check_down_right(current_board,good_words[current_word],row,col)) {
					// Add word to the board
					std::vector< std::vector<char> > new_board = current_board;
					for (unsigned int i=0;i<good_words[current_word].size();i++) {
						new_board[row+i][col+i]=good_words[current_word][i];
					}
					if (current_word==good_words.size()-1) {
						// last word
						
						fill_blanks(solutions,new_board,bad_words);
					} else {
						// not last word
						ugh_recursion(new_board,solutions,good_words,bad_words,current_word+1,one_solution,go_on);
					}
				}

				// Check up left
				if(check_up_left(current_board,good_words[current_word],row,col)) {
					// Add word to the board
					std::vector< std::vector<char> > new_board = current_board;
					for (unsigned int i=0;i<good_words[current_word].size();i++) {
						new_board[row-i][col-i]=good_words[current_word][i];
					}
					if (current_word==good_words.size()-1) {
						// last word
						
						fill_blanks(solutions,new_board,bad_words);
					} else {
						// not last word
						ugh_recursion(new_board,solutions,good_words,bad_words,current_word+1,one_solution,go_on);
					}
				}

				// Check up right
				if(check_up_right(current_board,good_words[current_word],row,col)) {
					// Add word to the board
					std::vector< std::vector<char> > new_board = current_board;
					for (unsigned int i=0;i<good_words[current_word].size();i++) {
						new_board[row-i][col+i]=good_words[current_word][i];
					}
					if (current_word==good_words.size()-1) {
						// last word
						
						fill_blanks(solutions,new_board,bad_words);
					} else {
						// not last word
						ugh_recursion(new_board,solutions,good_words,bad_words,current_word+1,one_solution,go_on);
					}
				}


			}
		}

	}
}

// Here begins the "delete direction" methods
// these see if a bad word / "word to exclude" is present at the current location going out in a given directon

bool delete_down_right(int row, int col, std::string& word, std::vector<std::vector<char> >& current_board) {
	// count will hold which character in the word-to-check we're on
	int count = 0;
	// loop through the characters of the bad word
	while (count<word.size()) {
		// check bounds the same as other methods have
		if ((row>current_board.size()-1)||(col>current_board[row].size()-1)) {
			return false;
		} else {
			// check current location to see if it matches the current character
			if (current_board[row][col]==word[count]) {
				// if so, increment the current character and the position in the board to next position in the downwards left diagonal
				count++;
				col++;
				row++;
			} else {
				// if not a match, return false
				return false;
			}
		}
	}
	// if the function got through the loop, then can return true
	return true;
}

// next direction checker, words the same as before
bool delete_down_left(int row, int col, std::string& word, std::vector<std::vector<char> >& current_board) {

	int count = 0;
	while (count<word.size()) {
		if ((row>current_board.size()-1)||(col<0)) {
			
			return false;
		} else {
			if (current_board[row][col]==word[count]) {
				count++;
				col--;
				row++;
			} else {
				
				return false;
			}
		}
	}

	

	return true;
}

bool delete_up_right(int row, int col, std::string& word, std::vector<std::vector<char> >& current_board) {

	int count = 0;
	while (count<word.size()) {
		if ((row<0)||(col>current_board[row].size()-1)) {
			return false;
		} else {
			if (current_board[row][col]==word[count]) {
				count++;
				col++;
				row--;
			} else {
				return false;
			}
		}
	}
	return true;
}

bool delete_up_left(int row, int col, std::string& word, std::vector<std::vector<char> >& current_board) {

	int count = 0;
	while (count<word.size()) {
		if ((row<0)||(col<0)) {
			return false;
		} else {
			if (current_board[row][col]==word[count]) {
				count++;
				col--;
				row--;
			} else {
				return false;
			}
		}
	}
	return true;
}

bool delete_right(int row, int col, std::string& word, std::vector<std::vector<char> >& current_board) {

	int count = 0;
	while (count<word.size()) {
		if (col>current_board[row].size()-1) {
			return false;
		} else {
			if (current_board[row][col]==word[count]) {
				count++;
				col++;
			} else {
				return false;
			}
		}
	}
	return true;
}

bool delete_left(int row, int col, std::string& word, std::vector<std::vector<char> >& current_board) {

	int count = 0;
	while (count<word.size()) {
		if (col<0) {
			return false;
		} else {
			if (current_board[row][col]==word[count]) {
				count++;
				col--;
			} else {
				return false;
			}
		}
	}
	return true;
}

bool delete_up(int row, int col, std::string& word, std::vector<std::vector<char> >& current_board) {

	int count = 0;
	while (count<word.size()) {
		if (row<0) {
			return false;
		} else {
			if (current_board[row][col]==word[count]) {
				count++;
				row--;
			} else {
				return false;
			}
		}
	}
	return true;
}

bool delete_down(int row, int col, std::string& word, std::vector<std::vector<char> >& current_board) {

	int count = 0;
	while (count<word.size()) {
		if (row>current_board.size()-1) {
			return false;
		} else {
			if (current_board[row][col]==word[count]) {
				count++;
				row++;
			} else {
				return false;
			}
		}
	}
	return true;
}


// this method checks a solution against all the "bad words" -- returning true if it's good
// and false if it contains a "word to exclude"

bool check_solution(std::vector<std::vector<char> >& current_board,std::vector<std::string>& bad_words) {
	// loop through all the bad words
	for (unsigned int i=0;i<bad_words.size();i++) {

		// loop through the dimensions of the current board
		for (unsigned int r=0;r<current_board.size();r++) {
				for (unsigned int c=0;c<current_board[r].size();c++) {

					// if the current character == the first character of the current bad word...
					if (current_board[r][c] == bad_words[i][0]) {
						// then check every single direction to see if the current bad word exists in the board
						if (delete_up(r,c,bad_words[i],current_board)) {
							return false;
						} else if (delete_down(r,c,bad_words[i],current_board)) {
							return false;
						} else if (delete_right(r,c,bad_words[i],current_board)) {
							return false;
						} else if (delete_left(r,c,bad_words[i],current_board)) {
							return false;
						} else if (delete_up_left(r,c,bad_words[i],current_board)) {
							return false;
						} else if (delete_down_left(r,c,bad_words[i],current_board)) {
							return false;
						} else if (delete_up_right(r,c,bad_words[i],current_board)) {
							return false;
						} else if (delete_down_right(r,c,bad_words[i],current_board)) {
							return false;
						}
					}
				}
			}
		
	}
	// if it passed all the checks, then solution is good and return true
	return true;
}
/*
this method checks a board that's been filled with all the good words / words to include
for blank spaces. it fills these in with random alphabetical characters and adds
all valid permutations to the solutions list.

This function is also recursive -- oh boyyyy

*/
void fill_blanks(std::list< std::vector<std::vector<char> > >& solutions,
	std::vector<std::vector<char> >& current_board, 
	std::vector<std::string>& bad_words
	) {

	// Create a flag to see if any blanks were found
	bool found_blank = false;

	// the alphabet for filling in blanks
	std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

	// loop through the dimensions of the current board
	for (unsigned int r=0;r<current_board.size();r++) {
		for (unsigned int c=0;c<current_board[r].size();c++) {

			// if current location is a blank...
			if (current_board[r][c]=='.') {

				// change flag
				found_blank = true;

				// loop through alphabet
				for (unsigned int i=0;i<alphabet.size();i++) {
					
					// create new boards in which the blank is filled with
					// each letter of the alphabet

					std::vector<std::vector<char> > new_board = current_board;
					new_board[r][c]=alphabet[i];

					// if the new board is a valid solution, recurse to check for more blanks and generate permutations

					if (check_solution(new_board,bad_words)==true) {
						fill_blanks(solutions,new_board,bad_words);
					}
				}
			}
		}
	}

	// if all the blanks are filled, check if solution is valid, then add to borard

	if (found_blank==false) {
		if (check_solution(current_board,bad_words)==true) {
			solutions.push_back(current_board);
		}
	}

}

int main(int argc, char* argv[]) {
	// 1st arg = puzzle file, 2nd arg = oufile 3rd arg = one solution flag

	// Create stream reader
	std::ifstream in_str(argv[1]);

	// initialize good / required and bad / forbidden word vectors
	std::vector<std::string> good_words;
	std::vector<std::string> bad_words;

	// initialize the number of rows and columns

	int num_rows = 0;
	int num_cols = 0;

	if (in_str.good()) {
		std::string current_text; // holds string input from file
		int current_num = 0; // holds int input from file
		in_str >> current_num;
		num_rows = current_num; // get number rows
		in_str >> current_num;
		num_cols = current_num; // get number cols

		// loop through lines of files
		while (in_str >> current_text) {
			if (current_text=="+") {
				// if a plus, add next word to good words
				in_str >> current_text;
				good_words.push_back(current_text);
			} else if (current_text=="-") {
				// if a minus, add next word to bad words
				in_str >> current_text;
				bad_words.push_back(current_text);
			}

		}
	}


	// initialize board (2d char vector) filled with periods to represent blanks

	std::vector< std::vector<char> > board(num_cols, std::vector<char>(num_rows, '.'));

	// initalize solutions list
	std::list< std::vector<std::vector<char> > > solutions;

	// get the one solution flag
	std::string flag = argv[3];

	// initalizee stream writer
	std::ofstream out_str(argv[2]);
	 if (!out_str.good()) {
        std::cout << "Can't open " << argv[3] << " to write.\n";
        exit(1);
    }

    // initialize the go on flag to be passed
    bool go_on=true; 
	if (flag=="one_solution") {
		// One solution Code
		// start recursion
		ugh_recursion(board,solutions,good_words,bad_words,0,true,go_on);

		// check if no solutions found
		if (solutions.size()==0) {
			out_str << "No solutions found";
			return 0;
		}

		// else, output first solution
		out_str << "Board:" << std::endl;
		std::list< std::vector<std::vector<char> > >::const_iterator iterator = solutions.begin();
		
		// loop through 2D vector to construct board
		for (unsigned int r=0;r<(*iterator).size();r++) {
			out_str << "  ";
			for (unsigned int c=0;c<(*iterator)[r].size();c++) {
				out_str << (*iterator)[r][c];
			}
			out_str << std::endl;
		}
	} else if (flag=="all_solutions") {
		// All solution Code
		ugh_recursion(board,solutions,good_words,bad_words,0,false,go_on);
		
		// removes all duplicate entries from the list		
		solutions.unique();

		// check if no solutions found
		if (solutions.size()==0) {
			out_str << "No solutions found";
			return 0;
		}

		// output number of solutions at header
		out_str << solutions.size() << " solution(s)" << std::endl;

		// loop through solutions list
		for (std::list< std::vector<std::vector<char> > >::const_iterator iterator = solutions.begin(), end = solutions.end(); iterator != end; ++iterator) {

			// output the text representation of each valid board
			out_str << "Board:" << std::endl;
			for (unsigned int r=0;r<(*iterator).size();r++) {
				out_str << "  ";
				for (unsigned int c=0;c<(*iterator)[r].size();c++) {
					out_str << (*iterator)[r][c];;
				}
				out_str << std::endl;
			}
		}

	}
	return 0;
}