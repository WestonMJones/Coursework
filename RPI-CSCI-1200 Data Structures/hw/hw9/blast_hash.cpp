#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include "blast_hash.h"

BLAST_hash::BLAST_hash(std::string fname, int tsize, float maxo, int k) {

	// Initialize variables
	current_size = 0;
	max_size = tsize;
	kmer_size = k;
	max_occupancy = maxo;
	resizing = false;

	// Temporary string to hold current line of genome file
	std::string current;

	// Stream reader
	std::ifstream in_str(fname);
	if (in_str.good()) {
		// If file name is good, load contents of genome file into genome file
		while (in_str >> current) {
			genome+=current;
		}
	} else {
		// Bad file name
		std::cout << "Bad file name!" << std::endl;
		return;
	}

	// Initialize vector of MAX_SIZE indices where each index is a pair 
	// that contains the KMER and a vector of locations that KMER appears in the genome
	// The default KMER for every value is "EMPTY"
	std::vector<std::pair<std::string, std::vector<int> > > initial_table(max_size, std::make_pair("EMPTY", std::vector<int>()));
	this->table = initial_table;

	// Loop through the genome character by character -- stop KMER_SIZE indices short of end
	for (unsigned int i=0;i<=genome.size()-kmer_size;i++) {

		// For each character accessed, add the next KMER_SIZE-1 characters to a placeholder string and insert it into the table
		std::string current_kmer = "";
		for (unsigned int k=i;k<i+kmer_size;k++) {
			current_kmer+=genome[k];
		}

		insert(current_kmer,i);
	}

}

void BLAST_hash::insert(const std::string kmer, unsigned int location) {

	// Use the hash function to calculate the right index for the current kmer
	unsigned int index = hash(kmer);

	// Insert kmer

	// If the index refers to an empty slot...
	if (table[index].first=="EMPTY") {

		// Update the key for that slot
		table[index].first=kmer;

		// Add the location in the genome to the vector of locations for that key
		table[index].second.push_back(location);

		// If the table currently isn't being resized, increment the current size of table
		if (!resizing) {
			current_size++;
		}

	// If the index refers to a slot that has the same key, then the KMER is a dupe. Just update
	// the vector of locations
	} else if (table[index].first==kmer) {
		
		table[index].second.push_back(location);

	} else {
		// The current index has a key that is not EMPTY or the current kmer -- there has been a collision

		// Use the probe function to find the next available index using linear probing
		index = probe(kmer,index+1);

		// If the new index is empty, add the location in genome, change the key, and update the current size.
		if (table[index].first=="EMPTY") {
			table[index].first=kmer;
			table[index].second.push_back(location);

			if (!resizing) {
				current_size++;
			}

		// If the new index has the same key, then just add the location to that key's vector -- don't increment current size
		} else if (table[index].first==kmer)  {

			table[index].second.push_back(location);

		} else {

			// Should never reach this part of the code because probing should always return a valid index, assuming resize works correctly.
			// std::cout << "OMG WTF BBQ SOMETHING HAS GONE WRONG NOOOOOOOOOOO!!!!!111!!!!!" << std::endl;
			
		}



	}

	// Calculate current percent occupied and compare it to max occupied. 
	if (((float)current_size/float(max_size))>max_occupancy) {
		//If table is too big, call resize function.
		resize();
	}

}

unsigned int BLAST_hash::probe(const std::string kmer, unsigned int index, bool first) {
	
	// Loop from current index to end of table
	while (index<max_size) {

		if (table[index].first=="EMPTY") {

			// If an empty slot is found, return that index
			return index;

		} else if (table[index].first==kmer) {

			// If the current index has a key that matches the key we're trying to insert, then return that index
			return index;

		} else {

			// If current index is occupied, check one index ahead and try again			
			index++;

		}
	}

	// If the function gets to this point then it means every index from the original to the end of the table was filled.
	// This seems to happen sometimes when the hash function returns indices towards the end of the table
	// If this is the case, then run probe again but start at the beginning of the table
	// However, we also use probe to search the table for keys and sometimes a given key won't be in the table
	// To avoid an infinite loop, the third optional parameter is set to false so that the function doesn't keep searching the table
	if (first) {
		return probe(kmer,0,false);
	} else {

		// Function will only get here if probe is called by query to search for a sequence that doesn't exist
		// If this is the case, return an impossible index value so query knows that the sequence doesn't exist
		return max_size+1;
	}
}

unsigned int BLAST_hash::hash(const std::string key) const {
	
	unsigned int hash = 1315423911;
	for(unsigned int i = 0; i < key.length(); i++)
		hash ^= ((hash << 5) + key[i] + (hash >> 2));
	hash = hash % max_size;
	return hash;

}

void BLAST_hash::resize() {

	// Double the current allocation
	max_size = max_size*2;

	// Make a copy of the current hash table
	std::vector<std::pair<std::string, std::vector<int> > > old_table = this->table;

	// Make a new hash table with the updated max size.
	std::vector<std::pair<std::string, std::vector<int> > > new_table(max_size, std::make_pair("EMPTY", std::vector<int>()));

	// Set the new empty table to the current table
	table = new_table;

	// Set the resizing flag so insert doesn't increment the current size
	this->resizing = true;

	// Loop through every slot in the old hash table copy
	for (unsigned int i=0;i<old_table.size();i++) {
		if (old_table[i].first!="EMPTY") {
			// If the current index wasn't empty, loop through each of the location values stored and insert them into the new table.
			for (unsigned int x=0;x<old_table[i].second.size();x++) {
				insert(old_table[i].first,old_table[i].second[x]);
			}
		}
	}
	
	// Turn the resizing flag off so the current size of the table is incremented properly.
	this->resizing = false;
	
}

// Print function I used for debugging -- ignore
void BLAST_hash::print() {
	std::cout << std::endl;
	for (unsigned int i=0;i<table.size();i++) {

		if (table[i].first=="EMPTY") {
			std::cout << "Index " << i << " is empty!" << std::endl;
		} else if (table[i].second.size()==1){
			std::cout << "Kmer " << table[i].first << " at table index " << i << " is found at index " << table[i].second[0] << std::endl;
		} else  {
			std::cout << "Kmer " << table[i].first << " at table index " << i << " is found at " << table[i].second.size() << " locations in genome:" << std::endl;
			for (unsigned int x=0;x<table[i].second.size();x++) {
				std::cout << "Location Number " << x+1 << ": " << table[i].second[x] << std::endl;
			} 
		}

		
	}
	std::cout << std::endl;
}

// Pulic query command
void BLAST_hash::query(const int errors, const std::string query) {

	// Output the first line of the command, the sequnce we're searching for
	std::cout << "Query: " << query << std::endl;

	// Get the first KMER_SIZE characters of the query
	// Store them in a string called search
	std::string search = "";
	for (unsigned int i=0;i<kmer_size;i++) {
		search+=query[i];
	}

	// Find the starting index for the search string using the hash function.
	unsigned int index = hash(search);

	// If the hash doesn't contain the right key...
	if (table[index].first != search) {
		// Use probe to return the right key
		index = probe(search,index+1);

		// If probe returns max_size+1 then the key doesn't exist.
		if (index==max_size+1) {

			// Output no match and end the current query.
			std::cout << "No Match" << std::endl;
			return;

		}
	}

	// Flag to be used later to see if a valid sequence was found
	bool not_found = true;

	// Now that the index is correct, loop through all the genome locations stored by the current slot in table
	for (unsigned int x=0;x<table[index].second.size();x++) {

		// Set up some variables
		int current_errors = 0; // This will keep track of the current number of errors
		unsigned int place_in_genome = table[index].second[x]; // this will keep track of the current index in the genome -- start at the kmer's start index
		std::string out_string = ""; // This will keep track of the matched sequence to be output by the query

		// Loop through every character in the query string
		for (unsigned int place_in_word=0;place_in_word<query.size();place_in_word++) {

			// Before accessing anything, also make sure the place_in_genome is within the bounds of the string
			if (place_in_genome<genome.size()) {

				// If there's an error between the genome and the current query, increment current_errors
				if (genome[place_in_genome]!=query[place_in_word]) {
					current_errors++;
				}

				// Increment the matching sequence to be output
				out_string+=genome[place_in_genome];

				// Also increment the index in the genome
				place_in_genome++;
			} else {
				// If the current index in the genome is outside of the bounds of the character array
				// (This happens sometimes if the relevant kmer is towards the end of the genome and the
				// query is long) then just ignore this location and end the loop to avoid memory errors

				current_errors = errors+1;
				break;
			}
			
		}

		// If the errors between the sequences was low enough, output the matched sequence and change the not_found flag for this query
		if (current_errors<=errors) {
			std::cout << table[index].second[x] << " " << current_errors << " " << out_string << std::endl;
			not_found = false;
		}


	}

	// If not queries were found or those that were had too many errors, output No Match
	if (not_found) {
		std::cout << "No Match" << std::endl;
	}

}