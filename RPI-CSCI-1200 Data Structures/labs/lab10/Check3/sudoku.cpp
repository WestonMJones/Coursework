#include <vector>
#include <set>
#include <iostream>
#include <math.h>
#include <cassert>
#include "sudoku.h"

using std::set;
using std::vector;
using std::cout;
using std::cin;
using std::endl;

// ======================================================
// A program to solve very simple Sudoku puzzles
// ======================================================

int main() {

  int size;
  while (cin >> size) {
    // Read in the board size and create an empty board
    Sudoku board(size);

    // Read in and set the known positions in the board
    char c;
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {      
        cin >> c;
        if (c != '.') {
          board.Set(i,j,c-'0');
        }
      }
    }
    
    // The iterative solving routine 
    while (1) {
      
      // Is the puzzle is already solved?
      if (board.IsSolved()) {
        cout << "\nPuzzle is solved:" << endl;
        board.Print();
        break;
      }
      
      // Is the puzzle impossible?
      if (board.Impossible()) {
        cout << "\nCannot solve this puzzle:" << endl;
        board.Print();
        break;
      }
      
      // Try to reduce the number of choices in one or more board cells
      // by propagating known values within each row, column, and quadrant
      int changed = 0;
      for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
          if (board.KnownValue(i,j))
            changed += board.Propagate(i,j);
        }
      }
      
      // If nothing changed this iteration, give up
      if (changed == 0) {
        cout << "\nPuzzle is too difficult for this solver!" << endl;
        board.Print();
        break;      
      }
    }
  }
}

// ======================================================

// Construct an empty board
Sudoku::Sudoku(int s) {
  // set the size
  size = s;
  quadrant_size = (int)sqrt(size);
  assert (quadrant_size*quadrant_size == s);

  
  // You need to finish this function!

    std::vector< std::vector< std::set<int> > > blah(size, std::vector< std::set<int> >(size));

    board = blah;
    for (int x=0;x<size;x++) {
      for (int y=0;y<size;y++) {
        for (int i=1;i<size+1;i++) {
          board[x][y].insert(i);
        }
      }
    }
   



}

// To construct the puzzle, set the value of a particular cell
void Sudoku::Set(int i, int j, int value) {
  // make sure the value is one of the legal values
  assert (board[i][j].find(value) != board[i][j].end());
  board[i][j].clear();
  board[i][j].insert(value);
}

// Does the cell have exactly one legal value?
bool Sudoku::KnownValue(int i, int j) const {
  return (board[i][j].size() == 1);
}

// If there is exactly one number in each cell of the grid, the puzzle is solved!
bool Sudoku::IsSolved() const {


  // You need to write this function
  for (int x=0;x<size;x++) {
      for (int y=0;y<size;y++) {
        if (Sudoku::KnownValue(x,y)==false) {
          return false;
        }
      }
    }
  return true;
}

// If there are no legal choices in one or more cells of the grid, the puzzle is impossible
bool Sudoku::Impossible() const {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (board[i][j].size() == 0) 
        return true;
    }
  }
  return false;
}

// print out the solution
void Sudoku::Print() const {
  int solved = IsSolved();
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      int count = size+1;
      for (set<int>::iterator itr = board[i][j].begin(); itr != board[i][j].end(); itr++) {
        count--;
        cout << *itr;
      }
      if (!solved) {
        // if it's not solved, print out spaces to separate the values
        for (int k = 0; k < count; k++) {
          cout << " ";
        }
      }
    }
    cout << endl;
  }
}


// Propagate information from this cell along columns & rows &
// within quadrant. Return the number of cells that changed.
int Sudoku::Propagate(int i, int j) {


  // You need to write this function
  int count = 0 ;

  std::set <int> blah = board[i][j];
  int current = *blah.begin();


  //std::set<int>::iterator it;

  // Handle Rows
  for (int x=0;x<size;x++) {
    if (x!=j) {
      if (board[i][x].erase(current)>0) {
        count++;
      }
    }
  }

  // Handle Columns
  for (int x=0;x<size;x++) {
    if (x!=i) {
      if (board[x][j].erase(current)>0) {
        count++;
      }
    }
  }

  // Handle quadrants
  int qstartx = 0;
  int qstarty = 0;

  // Find X
  if (i<quadrant_size) {
    qstartx=0;
  } else if (i<quadrant_size*2) {
    qstartx=quadrant_size;
  } else {
    qstartx=(quadrant_size*2);
  }

  // Find Y
  if (j<quadrant_size) {
    qstarty=0;
  } else if (j<quadrant_size*2) {
    qstarty=quadrant_size;
  } else {
    qstarty=(quadrant_size*2);
  }


  for (int a=qstartx;a<qstartx+quadrant_size;a++) {
    for (int b=qstarty;b<qstarty+quadrant_size;b++) {
      if ((a!=i)&&(b!=j)) {
        if (board[a][b].erase(current)>0) {
          count++;
        }
      }
    }
  }



  return count;

}
