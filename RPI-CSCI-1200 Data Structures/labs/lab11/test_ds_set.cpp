#include <iostream>
#include <string>
#include <utility>
#include <cassert>
#include <set>

#include "ds_set.h"

int main() {

  ds_set<std::string> set1;
  set1.insert("hello");
  set1.insert("good-bye");
  set1.insert("friend");
  set1.insert("abc");
  set1.insert("puppy");
  set1.insert("zebra");
  set1.insert("daddy");
  set1.insert("puppy");  // should recognize that this is a duplicate!

  assert(set1.sanity_check());
  assert (set1.size() == 7);

  ds_set<std::string>::iterator p = set1.begin();
  assert(p != set1.end() && *p == std::string("abc"));

  p = set1.find( "foo" );
  assert (p == set1.end());

  p = set1.find("puppy");
  assert (p != set1.end());
  assert (*p == "puppy");

  std::cout << "Here is the tree, printed sideways.\n"
	    << "The indentation is proportional to the depth of the node\n"
	    << "so that the value stored at the root is the only value printed\n"
	    << "without indentation.  Also, for each node, the right subtree\n"
	    << "can be found above where the node is printed and indented\n"
	    << "relative to it\n";
  set1.print_as_sideways_tree( std::cout );
  std::cout << std::endl;


  // copy the set
  ds_set<std::string> set2( set1 );
  assert(set1.sanity_check());
  assert(set2.sanity_check());
  assert(set1.size() == set2.size());
  

  //  Now add stuff to set2
  set2.insert( std::string("a") );
  set2.insert( std::string("b") );
  std::cout << "After inserting stuff:\n";
  set2.print_as_sideways_tree( std::cout );
  std::cout << std::endl;
  assert(set1.sanity_check());
  assert(set2.sanity_check());
  assert(set1.size() == set2.size() - 2);


  //  Now erase stuff from set2
  set2.erase("hello");
  set2.erase("a");
  set2.erase("hello"); // should recognize that it's not there anymore!
  set2.erase("abc");
  set2.erase("friend");
  std::cout << "After erasing stuff:\n";
  set2.print_as_sideways_tree( std::cout );
  std::cout << std::endl;
  assert(set1.sanity_check());
  assert(set2.sanity_check());
  assert(set1.size() == set2.size() + 2);


  // Test the iterators!
  ds_set<int> test_set;
  test_set.insert(8);
  test_set.insert(4);
  test_set.insert(2);
  test_set.insert(6);
  test_set.insert(1);
  test_set.insert(3);
  test_set.insert(5);
  test_set.insert(7);
  test_set.insert(12);
  test_set.insert(10);
  test_set.insert(14);
  test_set.insert(9);
  test_set.insert(11);
  test_set.insert(13);
  test_set.insert(15);
  std::cout << std::endl << std::endl << "Printing the tree Structure for a balanced tree -- Test Case 1" << std::endl;
  test_set.print_as_sideways_tree(std::cout);
  std::cout << std::endl << std::endl;

  std::cout << "Now testing increment iterator:" << std::endl;
  ds_set<int>::iterator it;

  for (it=test_set.begin();it!=test_set.end();it++) {
    std::cout << *it << " ";
  }
  std::cout << std::endl; 

  std::cout << "Now testing decrement iterator:" << std::endl;
  it = test_set.end();
  while (it!=test_set.begin()) {
    it--;
    std::cout << *it << " ";
  }
  
  std::cout << std::endl;
  std::cout << "The accumulation is: " << test_set.accumulate(0) << std::endl << std::endl << std::endl;
  

  ds_set<std::string> test_set2;
  test_set2.insert("a");
  test_set2.insert("b");
  test_set2.insert("c");
  test_set2.insert("d");
  test_set2.insert("e");
  test_set2.insert("f");
  test_set2.insert("g");
  test_set2.insert("h");
  test_set2.insert("i");
  test_set2.insert("j");
  test_set2.insert("k");
  test_set2.insert("l");
  test_set2.insert("m");
  test_set2.insert("n");
  test_set2.insert("o");
  std::cout << std::endl << std::endl << "Printing the tree Structure for an unbalanced tree -- Test Case 2" << std::endl;
  test_set2.print_as_sideways_tree(std::cout);
  std::cout << std::endl << std::endl;

  std::cout << "Now testing increment iterator:" << std::endl;
  ds_set<std::string>::iterator it2;
  for (it2=test_set2.begin();it2!=test_set2.end();it2++) {
    std::cout << *it2 << " ";
  }
  std::cout << std::endl; 

  std::cout << "Now testing decrement iterator:" << std::endl;
  it2 = test_set2.end();
  while (it2!=test_set2.begin()) {
    it2--;
    std::cout << *it2 << " ";
  }
  std::cout << std::endl;

  std::cout << "The accumulation is: " << test_set2.accumulate("") << std::endl << std::endl << std::endl;

  ds_set<int> test_set3;
  test_set3.insert(4);
  test_set3.insert(2);
  test_set3.insert(6);
  test_set3.insert(8);
  test_set3.insert(10);
  test_set3.insert(12);
  test_set3.insert(14);
  test_set3.insert(1);
  test_set3.insert(5);
  test_set3.insert(3);
  test_set3.insert(9);
  test_set3.insert(7);
  test_set3.insert(13);
  test_set3.insert(11);
  test_set3.insert(15);
  std::cout << std::endl << std::endl << "Printing the tree Structure for an unbalanced tree -- Test Case 3" << std::endl;
  test_set3.print_as_sideways_tree(std::cout);
  std::cout << std::endl << std::endl;

  std::cout << "Now testing increment iterator:" << std::endl;

  for (it=test_set3.begin();it!=test_set3.end();it++) {
    std::cout << *it << " ";
  }
  std::cout << std::endl; 

  std::cout << "Now testing decrement iterator:" << std::endl;
  it = test_set3.end();
  while (it!=test_set3.begin()) {
    it--;
    std::cout << *it << " ";
  }
  std::cout << std::endl;
  std::cout << std::endl << "The accumulation is: " << test_set3.accumulate(0) << std::endl << std::endl << std::endl;
  return 0;
}
