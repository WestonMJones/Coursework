#ifndef blast_hash_h_
#define blast_hash_h_

// Includes
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

class BLAST_hash {
public:

	BLAST_hash(std::string fname, int tsize, float maxo, int k); // Constructor 
	void query(const int errors, const std::string query); // Query command



private:

	void insert(const std::string kmer, const unsigned int location); // Command to insert sequence into table
	unsigned int probe(const std::string kmer, unsigned int location, bool first=true); // Command to find an open address for a value
	unsigned int hash(const std::string key) const; // Hash function
	void resize(); // Double the size of the table and rehash the data

	void print(); // Command I made to print the contents of the table -- for debugging purposes

	// Representation
	std::vector<std::pair<std::string, std::vector<int> > > table; // Top level vector of hash table
	std::string genome; // The entire genome as one big string
	unsigned int current_size; // Current number of unique keys in the table
	unsigned int max_size; // Maximum size of the table
	unsigned int kmer_size; // Size of kmers
	bool resizing; // Flag to indicate if table is being resized and thus not to increment the current size of the table when values are inserted
	float max_occupancy; // Max occupancy of the table


};



#endif