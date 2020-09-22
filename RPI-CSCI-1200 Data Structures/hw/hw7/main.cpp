// -----------------------------------------------------------------
// HOMEWORK 7 WORD FREQUENCY MAPS
//
// You may use all of, some of, or none of the provided code below.
// You may edit it as you like (provided you follow the homework
// instructions).
// -----------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <cstdlib>

// I need these for asserts
#include <stdio.h>      
#include <assert.h>

// Include random number generator and another thing for it
#include "mtrand.h"
#include <time.h>

// ASSIGNMENT: FILL IN YOUR OWN MAP STRUCTURE
// Using a Map the pairs words to other maps that hold the occurances of words following a particular word.
typedef  std::map <std::string, std::map<std::string, int>  >  MY_MAP;
typedef  std::map <std::string, std::map<std::string, std::map< std::string, int> > > MY_MAP2;

// Custom helper function that reads the input stream looking for
// double quotes (a special case delimiter needed below), and white
// space.  Contiguous blocks of alphabetic characters are lowercased &
// packed into the word.
bool ReadNextWord(std::istream &istr, std::string &word) {
  char c;
  word.clear();
  while (istr) {
    // just "peek" at the next character in the stream
    c = istr.peek();
    if (isspace(c)) {
      // skip whitespace before a word starts
      istr.get(c);
      if (word != "") {
	// break words at whitespace
	return true;
      }
    } else if (c == '"') {
      // double quotes are a delimiter and a special "word"
      if (word == "") {
	istr.get(c);
	word.push_back(c);
      }
      return true;
    } else if (isalpha(c)) {
      // this a an alphabetic word character
      istr.get(c);
      word.push_back(tolower(c));
    } else {
      // ignore this character (probably punctuation)
      istr.get(c);
    }
  }
  return false;
}


// Custom helper function that reads the input stream looking a
// sequence of words inside a pair of double quotes.  The words are
// separated by white space, but the double quotes might not have
// space between them and the neighboring word.  Punctuation is
// ignored and words are lowercased.
std::vector<std::string> ReadQuotedWords(std::istream &istr) {
  // returns a vector of strings of the different words
  std::vector<std::string> answer;
  std::string word;
  bool open_quote = false;
  while (ReadNextWord(istr,word)) {
    if (word == "\"") {
      if (open_quote == false) { open_quote=true; }
      else { break; }
    } else {
      // add each word to the vector
      answer.push_back(word);
    }
  }
  return answer;
}



// Loads the sample text from the file, storing it in the map data
// structure Window specifies the width of the context (>= 2) of the
// sequencing stored in the map.  parse_method is a placeholder for
// optional extra credit extensions that use punctuation.
void LoadSampleText(MY_MAP &data, const std::string &filename, int window, const std::string &parse_method) {
  // open the file stream
  std::ifstream istr(filename.c_str());
  if (!istr) { 
    std::cerr << "ERROR cannot open file: " << filename << std::endl; 
    exit(1);
  } 
  // verify the window parameter is appropriate
  if (window < 2) {
    std::cerr << "ERROR window size must be >= 2:" << window << std::endl;
  }
  // verify that the parse method is appropriate
  bool ignore_punctuation = false;
  if (parse_method == "ignore_punctuation") {
    ignore_punctuation = true;
  } else {
    std::cerr << "ERROR unknown parse method: " << parse_method << std::endl;
    exit(1);
  }

  //
  // ASSIGNMENT:SETUP YOUR MAP DATA AS NEEDED
  //

  // Create two string variables to hold the current word and the previous word
  std::string word;
  std::string prev_word = "";

  while (ReadNextWord(istr,word)) {
    // skip the quotation marks (not used for this part)
    if (word == "\"") continue;


    
    //
    // ASSIGNMENT: PROCESS ALL THE NON PUNCTUATION WORDS
    // INSERTING THESE WORDS INTO THE DATA STRUCTURE
    //

    // Looping through every word in the file

    if (prev_word=="") {
      // First word in file as prev word maintains initial assignment. 
      data[word]; // Create a entry for the current word in the outermost map
      ++data["MASTER_COUNT"][word]; // Create an entry for that word under "MASTER_COUNT" which will hold the total times a word appears in the text

    } else {
      // Not first word in the file

      ++data[prev_word][word]; // Increment the occurnace of the current word in the previous word's logs
      ++data["MASTER_COUNT"][word]; // Increment master count -- the total number of times this word has appeared
    }

    prev_word=word; // Make the current word equal to the previous word and mvoe on
  }

}

// Given the starter word and map data, this function outputs a sequence of words up to a given length
// following a given selection method
void NextWord(const std::string& current_word,int length,const bool& selection_method,MY_MAP &data) {

  // First check if there are still more words to print.
  if (length>0) {  

    // Create a placeholder
    std::string next_word;

    // Most_common instead of random
    if (selection_method==false) {

      // Placeholder to find most common
      int max = 0;

      // Declare an iterator and loop through the list of words following the current word
      std::map<std::string, int>::iterator it;
      for (it=data[current_word].begin();it!=data[current_word].end();++it) {
        // If this next word appears more often than the current most common next word, update variables.
        if (it->second > max) {
          max = it->second;
          next_word = it->first; // Make the found word the new "current word"
        }
      }
      // Output the found most common word
      std::cout << " " << next_word;
      length--;

      // Recurse now that length has been decremented and the next word has been found
      NextWord(next_word,length,selection_method,data);
    } else {
      // Random mode is ON

      static MTRand_int32 mtrand(time(NULL)); // Seed the generator

      // Initialize a vector of strings to hold all possible choices 
      std::vector<std::string> choices;

      // Placeholder that will store total number of choices
      int total = 0;

      // Make an iterator and iterate through all the words following the current word 
      std::map<std::string, int>::iterator it;
      for (it=data[current_word].begin();it!=data[current_word].end();++it) {

        // For every word, update the current total of possible selections
        total = total + it->second;

        // Add that word to the choices pool a number of times equal to its incidence
        for (int i=0;i<it->second;i++) {
          choices.push_back(it->first);
        }
      }

      // Generate a random number between 0 and 1 less than the current number of choices
      int random_num = (mtrand() % total);

      // Use the random number to make a selection from the vector of choices
      std::cout << " " << choices[random_num];

      // Update variables and recurse
      next_word = choices[random_num];
      length--;
      NextWord(next_word,length,selection_method,data);

    }
  }
}

void LoadSampleText2(MY_MAP2 &data, const std::string &filename, int window, const std::string &parse_method) {
  // open the file stream
  std::ifstream istr(filename.c_str());
  if (!istr) { 
    std::cerr << "ERROR cannot open file: " << filename << std::endl; 
    exit(1);
  } 
  // verify the window parameter is appropriate
  if (window < 2) {
    std::cerr << "ERROR window size must be >= 2:" << window << std::endl;
  }
  // verify that the parse method is appropriate
  bool ignore_punctuation = false;
  if (parse_method == "ignore_punctuation") {
    ignore_punctuation = true;
  } else {
    std::cerr << "ERROR unknown parse method: " << parse_method << std::endl;
    exit(1);
  }

  while (ReadNextWord(istr,word)) {
    // skip the quotation marks (not used for this part)
    if (word == "\"") continue;
    

  }

}

int main () {

  

  // Parse each command
  std::string command;    
  while (std::cin >> command) {

    // load the sample text file
    if (command == "load") {
      std::string filename;
      int window;
      std::string parse_method;
      std::cin >> filename >> window >> parse_method;      

      //
      // ASSIGNMENT: ADD YOUR COMMANDS HERE
      //

      // Check Window size
      if (window==2) {
        // ASSIGNMENT: THE MAIN DATA STRUCTURE
        MY_MAP data;

        // Load the data and output the first line
        LoadSampleText(data,filename,window,parse_method);
      } else {
        // Data Structure for Window length of 3
        MY_MAP2 data;
        LoadSampleText2(data,filename,window,parse_method);
      }
      std::cout << "Loaded " << filename << " with window = " << window << " and parse method = " << parse_method << std::endl << std::endl;

      

    } 

    // print the portion of the map structure with the choices for the
    // next word given a particular sequence.
    else if (command == "print") {
      std::vector<std::string> sentence = ReadQuotedWords(std::cin);


      //
      // ASSIGNMENT: ADD YOUR COMMANDS HERE
      //

      // FIrst have to ouput total occurances of the word -- reference the entry "Master count" for the current word
      std::cout << sentence[0] << " (" << data["MASTER_COUNT"][sentence[0]]<< ")" << std::endl;

      // Now I have to print all the words that follow the current word -- loop through the current word's map entry
      std::map<std::string, int>::iterator it;
      for (it=data[sentence[0]].begin();it!=data[sentence[0]].end();++it) {
        // generate the line
        std::cout << sentence[0] << " " << it->first << " (" << it->second<< ")" << std::endl;
      }
      std::cout << std::endl;
    }

    // generate the specified number of words 
    else if (command == "generate") {
      std::vector<std::string> sentence = ReadQuotedWords(std::cin);
      // how many additional words to generate
      int length;
      std::cin >> length;
      std::string selection_method;
      std::cin >> selection_method;
      bool random_flag;
      if (selection_method == "random") {
	random_flag = true;
      } else {
	assert (selection_method == "most_common");
	random_flag = false;
      }


      //
      // ASSIGNMENT: ADD YOUR COMMANDS HERE
      //

      // Output first word from the generate statement
      std::cout << sentence[0];
      // Call the recursive NextWord function to generate subsequent words
      NextWord(sentence[0],length,random_flag,data);
      // Finish by adding a new line
      std::cout << std::endl << std::endl;
    } else if (command == "quit") {
      break;
    } else {
      std::cout << "WARNING: Unknown command: " << command << std::endl;
    }
  }
}
