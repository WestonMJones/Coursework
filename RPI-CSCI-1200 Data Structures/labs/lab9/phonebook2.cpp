// A simple "caller ID" program

#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

// add a number, name pair to the phonebook
void add(map <int, string >& phonebook, int number, string const& name) {
  phonebook[number] = name;
}

// given a phone number, determine who is calling
void identify(const map<int,string> & phonebook, int number) {

  std::map<int, string>::const_iterator it = phonebook.find(number);


  if (it == phonebook.end()) 
    cout << "unknown caller!" << endl;
  else 
    cout << it->second << " is calling!" << endl;
}


int main() {
  // create the phonebook; initially all numbers are unassigned
  map<int, string> phonebook;


  // add several names to the phonebook
  add(phonebook, 1111, "fred");
  add(phonebook, 2222, "sally");
  add(phonebook, 3333, "george");
  add(phonebook, 6666666, "satan");

  // test the phonebook
  identify(phonebook, 2222);
  identify(phonebook, 4444);
  identify(phonebook, 6666666);
}
