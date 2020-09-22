#include <fstream>
#include <iostream>
#include <string>
#include "SongLibrary.h"

//////////////////DO NOT CHANGE THIS CODE////////////////////////

//Construct a Song object with values
Song::Song(const std::string& title, const std::string& artist, 
     const std::string& album, unsigned int year){
	this->title = title;
	this->artist = artist;
	this->album = album;
	this->year = year;
	used = false;
	this->song_group_ptr = NULL;
}

//Song equality doesn't depend on pointers or being used
bool operator== (const Song& s1, const Song& s2){
	return (s1.getYear() == s2.getYear()) && (s1.getTitle() == s2.getTitle())
          && (s1.getAlbum() == s2.getAlbum()) && (s1.getArtist() == s2.getArtist());
}

//Modifier for group pointer
void Song::updateSongGroupPointer(SongGroupNode* ptr){
	if(ptr){
		//Check that ptr is actually for this Song.
		assert(ptr->m_song->value == *this); 
		song_group_ptr = ptr;
	}
	else{
		song_group_ptr = NULL;
	}
}

//Make output easier by overload operator<<
std::ostream& operator<< (std::ostream& ostr, const Song& song){
	if(!song.getSongGroupPointer()){
		ostr << "\"" << song.getTitle() << "\" by " << song.getArtist() << " on \"" 
	       << song.getAlbum() << "\" (" << song.getYear() << ")" << std::endl;
	}
	else{
		ostr << "\"" << song.getTitle() << "\" by " << song.getArtist() << " on \"" 
		<< song.getAlbum() << "\" (" << song.getYear() << ")" << " in Song Group "
		<< song.getSongGroupPointer()->id << std::endl;
	}
	return ostr;
}

/////////////////////////YOUR CODE STARTS HERE/////////////////////////////////


//////////////////////////////GROUP FUNCTIONS/////////////////////////////////

/*
ARGUMENTS:
-song_groups points to a singly-linked list of song group heads
-id is the ID of the list we are searching for
BEHAVIOR:
None
RETURN:
NULL if no list matches the ID, otherwise returns the GroupListNode* containing
the head of the list with ID id.
*/
GroupListNode* GroupExists(GroupListNode* song_groups, GroupID id){
	// Create a search pointer that will hold the current location in the list of song groups
	GroupListNode* search = song_groups;
	while (search!=NULL) {
		// I just need to check the first entry in every song group because they should all have the 
		// same ID
		if (search->value->id==id) {
			return search;
		} else {
			search=search->ptr;
		}
	}
	return NULL; // if nothing found, return NULL as the function asks.

}

/*
ARGUMENTS:
-song_groups points to a singly-linked list of song group heads
-id is the ID of the list we are creating
BEHAVIOR:
Add a new song group to song_groups, give the new song group ID id. Order of
song groups is not guaranteed.
RETURN:
None
*/
void MakeGroup(GroupListNode*& song_groups, GroupID id){
	// Create a new song group list node and a song group node
	GroupListNode* newGroup = new GroupListNode;
	SongGroupNode* newSongGroupNode = new SongGroupNode;

	// Set the song group node equal to the value of the song group list node
	// Basically, give the new group a placeholder value
	newGroup->value=newSongGroupNode;

	// Create more placeholder values
	newGroup->ptr=NULL;
	newGroup->value->next_song_ptr=NULL;
	newGroup->value->prev_song_ptr=NULL;
	newGroup->value->next_by_artist_ptr=NULL;
	newGroup->value->prev_by_year_ptr=NULL;
	newGroup->value->m_song=NULL;

	// The ID shouldn't be set to NULL
	newGroup->value->id=id;

	//Check to see if there are currently Group List Nodes in the list
	if (song_groups==NULL) {
		// If NULL, then no other nodes, so this will be the first and will act as a dummy
		song_groups=newGroup;
	} else {
		// Currently other nodes in list

		//First need to find the end of song groups list by iterating through it
		GroupListNode* endOfSongGroups=song_groups;
		while (endOfSongGroups->ptr!=NULL) {
			endOfSongGroups=endOfSongGroups->ptr;
		}

		// endOfSongGroups should not equal last node in song_groups
		// set it to point to the new node
		endOfSongGroups->ptr=newGroup;
	}
}


/*
ARGUMENTS:
-group_head points to the head of a song group
-song is the Song we are checking the group for
BEHAVIOR:
None
RETURN:
If song is found in the group return true. If song is not found,
return false.
*/
bool SongInGroup(SongGroupNode* group_head, const Song& song){
	// Create node equal to current position in song group -- starting at head.
	SongGroupNode * search = group_head;
	while (search!=NULL) {
		// Search is a song group node which contains a song node whose value is a song
		// Check to see if this is equal to the parameter
		if (search->m_song->value==song) {
			return true;
		}
	}
	return false;
}

/*
ARGUMENTS:
-library_ptr points to the LibraryNode* containing the Song we want to add.
-list_ptr is the head of the song group we want to add the song to.
BEHAVIOR:
Modify the group pointed to by list_ptr to reflect that the song is in the group.
This may change the length of the list. Modifies the Song's members as well.
RETURN:
None
*/
void AddToGroup(LibraryNode* library_ptr, GroupListNode* list_ptr){
	// First Get the ID value -- will need this when updating certain variables
	unsigned int id = list_ptr->value->id;

	// Library_ptr is being added to a group, so update the relevant field
	library_ptr->value.setUsedInGroup(true);

	// Check if the first node in the head node of the group list has no song pointer -- means its
	// a dummy value
	if (list_ptr->value->m_song==NULL) {
		// empty song group -- can replace dummy / placeholder with the actual song

		// It's the first, so all pointers are set to 0.
		list_ptr->value->m_song=library_ptr;
		list_ptr->value->next_song_ptr=NULL;
		list_ptr->value->prev_song_ptr=NULL;
		list_ptr->value->next_by_artist_ptr=NULL;
		list_ptr->value->prev_by_year_ptr=NULL;

		// Id shouldn't be null
		list_ptr->value->id=id;

		// Update the library to reflect the song's addition to a group
		library_ptr->value.updateSongGroupPointer(list_ptr->value);

	} else {
		// song group with 1+ songs

		// Find the end of the group by iterating with a temporary node
		SongGroupNode * endOfSongGroup = list_ptr->value;
		while (endOfSongGroup->next_song_ptr!=NULL) {
			endOfSongGroup=endOfSongGroup->next_song_ptr;
		}

		// endOfSongGroup now = the last node

		// Create the new song group node
		SongGroupNode * newSongInGroup = new SongGroupNode;

		// Make the old end point to it
		endOfSongGroup->next_song_ptr=newSongInGroup;

		// Fill new end in with the relevant values
		newSongInGroup->next_song_ptr=NULL;
		newSongInGroup->prev_song_ptr=endOfSongGroup;
		newSongInGroup->next_by_artist_ptr=NULL;
		newSongInGroup->prev_by_year_ptr=NULL;
		newSongInGroup->m_song=library_ptr;
		newSongInGroup->id=id;

		// Update the library to reflect the song's addition to a new song group
		library_ptr->value.updateSongGroupPointer(newSongInGroup);
	}
}

/*
ARGUMENTS:
-library_ptr points to the LibraryNode* containing the Song we want to remove from a group.
-song_groups points to a singly-linked list of song group heads
BEHAVIOR:
Modifies the Song's member variables to reflect that it is not in a group. Modifies the group
so that the Song is not in the group. This function may cause song_groups to be modified as well.
RETURN:
None
*/
void RemoveFromGroup(LibraryNode* library_ptr, GroupListNode* song_groups){

	// Create an iterator to search through all the group list nodes
	GroupListNode* search1 = song_groups;
	while (search1!=NULL) {

		// Create a second iterator to search through all the song group nodes
		SongGroupNode * search2 = search1->value;
		while (search2!=NULL) {

			// Check if the current node points to the relevant song
			if (search2->m_song==library_ptr) {
				// Found the right song

				// Adjust the library to reflect the removal of a song from a song group
				library_ptr->value.setUsedInGroup(false);
				library_ptr->value.updateSongGroupPointer(NULL);

				// Create some placeholder nodes to prepare for deleting
				// from a double linked list
				SongGroupNode * prev = search2->prev_song_ptr;
				SongGroupNode * next = search2->next_song_ptr;

				// Check various corner cases first
				if ((prev==NULL)&&(next==NULL)) {
					// Only one element in the list

					// Here we just set the song to a dummy node again -- don't need to delete it
					search1->value->m_song=NULL;
					return;
				} else if ((prev==NULL)&&(next!=NULL)) {
					// One we want is First element in the list

					// Set the one before the one to be deleted to point back to NULL
					next->prev_song_ptr=NULL;

					// Also need to set the group list node to point to this new song list node
					// as the first in the list
					search1->value = next;
					delete search2;
					return;
				} else if ((prev!=NULL)&&(next==NULL)) {
					// one we want is the last element

					// Set the previous element in the list to point to null
					prev->next_song_ptr=NULL;
					delete search2;
					return;
				} else {
					// one we want is in the middle somewhere

					// Adjust the previous and next entries to skip over
					// the entry about to be deleted
					prev->next_song_ptr=next;
					next->prev_song_ptr=prev;

					delete search2;
					return;
				}
			}

			// Increment the current locaton in the list of song nodes
			search2=search2->next_song_ptr;
		}
		// Increment the current location in the list of group list nodes
		search1 = search1->ptr;
	}
}

/*
ARGUMENTS:
-song_groups points to a singly-linked list of song group heads
-list_ptr1 contains to the song group head of Group A
-list_ptr2 contains the song group head of Group B
BEHAVIOR:
Modify Group A so that at the end of its songs, the songs of Group B are added in the same
order they were found in Group B. Remove the now-empty Group B.
RETURN:
None
*/
void CombineGroups(GroupListNode*& song_groups, GroupListNode*& list_ptr1, GroupListNode*& list_ptr2){




}

/*
ARGUMENTS:
-song_groups points to a singly-linked list of song group heads
-list_ptr is the head of the song group we want to remove.
BEHAVIOR:
Remove the group from the list of song groups. No Song objects should remain associated with the
group, and the function should modify Song member variables appropriately to reflect this. Any
memory associated with the group must be released.
RETURN:
None
*/
void RemoveGroup(GroupListNode*& song_groups, GroupListNode* list_ptr){




}

/*
ARGUMENTS:
-list_ptr is the head of the song group we want to add the song to.
BEHAVIOR:
Recompute all prev_by_year_ptr members in the song group pointed to by
list_ptr.
RETURN:
None
*/
void RecomputePrevByYear(GroupListNode* list_ptr){




}

////////////////////////////PRINT FUNCTIONS////////////////////////////////////

/*
ARGUMENTS:
-library_head points to the first LibraryNode* of the song library
-print_file points to an ostream to print output to
BEHAVIOR:
Print each song in the library in the order it was added.
RETURN:
None
*/
void PrintLibrary(LibraryNode* library_head,std::ostream& print_file){

	// Initialize a count variable
	unsigned int count = 0;

	// Create an iterator that points to current head of list
	LibraryNode* current = library_head;
	while (current->ptr!=NULL) {
		// Print out current head and increment iterator + count
		print_file << current->value;
		current = current->ptr;
		count++;
	} 
	// Need to print out the last entry
	print_file << current->value;

	// Print out final message
	print_file << "Library contains "<<count+1<<" song(s)" << std::endl;


}

/*
ARGUMENTS:
-group_head points to the first SongGroupNode* of the group to print
-print_file points to an ostream to print output to
BEHAVIOR:
Print each song in the group in the order it was added.
RETURN:
None
*/
void PrintGroupSequential(SongGroupNode* group_head,std::ostream& print_file){
	// Initialize a count variable
	unsigned int count = 0;

	// Print out the first line that displays the ID
	print_file << "List ID " << group_head->id << " contains:" << std::endl;

	// Iterate through the list of song group nodes
	while (group_head!=NULL) {

		// If the first entry is a dummy node, then the list is empty and exit loop before we get an error
		if (group_head->m_song==NULL) {
			break;
		}

		// The << operator put an extra line break at the end, so I had to print out the same data 
		// the long way to add in the "in group group ID#" part
		print_file << "\"" << group_head->m_song->value.getTitle() << "\" by " <<
		group_head->m_song->value.getArtist() << " on \"" << group_head->m_song->value.getAlbum() <<
		"\" (" << group_head->m_song->value.getYear() << ") in Song Group " << group_head->id << std::endl;

		// increment the iterator and the song count
		group_head = group_head->next_song_ptr;
		count++;
	}
	// print out the closing message with the number of songs
	print_file << count << " song(s)"<< std::endl;
}

/*
ARGUMENTS:
-group_ptr points to the location in a particular song group to start printing from
-print_file points to an ostream to print output to
BEHAVIOR:
Print a rewind list by following the prev_by_year_ptr pointers, starting from the song
pointed to by group_ptr.
RETURN:
None
*/
void PrintGroupRewind(SongGroupNode* group_ptr,std::ostream& print_file){




}

/*
ARGUMENTS:
-group_ptr points to the location in a particular song group to start printing from
-print_file points to an ostream to print output to
BEHAVIOR:
Print a rewind list by following the next_by_artist_ptr pointers, starting from the song
pointed to by group_ptr.
RETURN:
None
*/
void PrintGroupMarathon(SongGroupNode* group_ptr,std::ostream& print_file){




}

/*
ARGUMENTS:
-group_head points to the first SongGroupNode* of the group to analyze
-print_file points to an ostream to print output to
BEHAVIOR:
Find the rewind list with the most songs in the song group pointed to by group_head.
Print the rewind list and the song count to print_file.
RETURN:
None
*/
void PrintLongestGroupRewind(GroupListNode* group_head,std::ostream& print_file){




}

///////////////////////////////CLEANUP/////////////////////////////////////////

/*
ARGUMENTS:
-song_groups points to a singly-linked list of song group heads
BEHAVIOR:
Delete every group. Do not leak. Modifies all groups and the song_groups list.
Update every Song to reflect not being in a group.
RETURN:
None
*/
void DeleteAllSongGroups(GroupListNode*& song_groups){

	// Iterate through all group list nodes
	while(song_groups!=NULL) {
		// save the current group list node and increment the group list iterator
		GroupListNode* song_group = song_groups;
		song_groups = song_groups->ptr;

		// Create an iterator for all the song group nodes in the current position of the group list
		SongGroupNode* song_node= song_group->value;
		while (song_node!=NULL) {
			// Create a temporary variable for the current song group node
			SongGroupNode* dummy = song_node;

			// increment the iterator
			song_node = song_node->next_song_ptr;

			// delete the previous entry
			delete dummy;
		}

		// delete the previous entry
		delete song_group;
	}
}
