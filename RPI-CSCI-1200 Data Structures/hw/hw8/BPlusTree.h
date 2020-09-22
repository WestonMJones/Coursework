/* ASSUMPTIONS:
1. When a node must be split and has an odd number of keys, the extra key will go to the new right-hand node.
2. There will never be a duplicate key passed to insert.
*/

#include <vector>
#include <list>
#include <algorithm>


#ifndef DS_BPLUSTREE
#define DS_BPLUSTREE

///////////////////////////////////////////////////////////////////////////////
//DO NOT CHANGE THIS CODE
///////////////////////////////////////////////////////////////////////////////
template <class T> class BPlusTree;

template <class T>
class BPlusTreeNode{
public:
	BPlusTreeNode() : parent(NULL) {};
	bool is_leaf();
	bool contains(const T& key);

	//For grading only, this is actually bad to have because
	//it exposes a private member variable.
	BPlusTreeNode* get_parent() { return parent; } 

	//We need this to let BPlusTree access private members
	friend class BPlusTree<T>; 
private:
	bool contains(const T& key,std::size_t low,std::size_t high);
	std::vector<T> keys;
	std::vector<BPlusTreeNode*> children;
	BPlusTreeNode* parent;
};

template <class T>
bool BPlusTreeNode<T>::is_leaf(){
	for(unsigned int i=0; i<children.size(); i++){
		if(children[i]){
			return false;
		}
	}
	return true;
}

template <class T>
bool BPlusTreeNode<T>::contains(const T& key){
	return contains(key,0,keys.size()-1);
}

//Private method takes advantage of the fact keys are sorted
template <class T>
bool BPlusTreeNode<T>::contains(const T& key,std::size_t low,std::size_t high){
	if(low>high){
		return false;
	}
	if(low==high){
		return key == keys[low];
	}
	std::size_t mid = (low+high)/2;
	if(key<=keys[mid]){
		return contains(key,0,mid);
	}
	else{
		return contains(key,mid+1,high);
	}
}


///////////////////////////////////////////////////////////////////////////////////////
//Your BPlusTree implementation goes below this point.
///////////////////////////////////////////////////////////////////////////////////////
template <class T> class BPlusTree {
public:
	// Constructors, Assignment Operator, and Destructor
	BPlusTree(const unsigned int& b);
	BPlusTree(const BPlusTree<T>& other);
	BPlusTree<T>& operator=(const BPlusTree<T>& old);
	~BPlusTree();

	// Public Functions
	void insert(const T& key_value);
	BPlusTreeNode<T>* find(const T& key_value);
	void print_sideways(std::ofstream& outfile);
	void print_BFS(std::ofstream& outfile);

private:
	// Representation
	BPlusTreeNode<T>* root;
	unsigned int size;

	// Helper Functions
	void destroy_tree(BPlusTreeNode<T>* p);
	BPlusTreeNode<T>* copy(BPlusTreeNode<T>* old_root, BPlusTreeNode<T>* the_parent);
	void restructure(BPlusTreeNode<T>* current);
	void print_in_order(std::ofstream& outfile, const BPlusTreeNode<T>* p, int depth);

	std::vector<BPlusTreeNode<T>*> sort_children(std::vector<BPlusTreeNode<T>*> children);
	bool compare_children(const BPlusTreeNode<T>* first, const BPlusTreeNode<T>* second);
	
};

template <class T> BPlusTree<T>::BPlusTree(const unsigned int& b) {
	this->root=new BPlusTreeNode<T>; // Initialize root node
	this->size=b;
}

template <class T> BPlusTree<T>::BPlusTree(const BPlusTree& other) {
	size=other.size;
	root = this->copy(other.root,NULL); // Call helper copy function
}

template <class T> BPlusTree<T>& BPlusTree<T>::operator=(const BPlusTree<T>& old) {
	// If the two trees are different...
	if (&old != this) {
		// Destroy old tree
		this->destroy_tree(root);
		delete root;

		// Copy in new trees values
		root = this->copy(old.root,NULL);
		size=old.size;
	}
	return *this;
}

template <class T> BPlusTreeNode<T>* BPlusTree<T>::copy(BPlusTreeNode<T>* old_root, BPlusTreeNode<T>* the_parent) {
	// Verify that other tree has values
	if (old_root==NULL) {
		return NULL;
	}

	// Create a new node and copy in the equivilant key values from the other tree
	BPlusTreeNode<T>* answer = new BPlusTreeNode<T>;
	answer->keys=old_root->keys;

	// Use recursion to construct the children and rest of the tree 
	for (unsigned int i=0;i<old_root->children.size();i++) {
		answer->children.push_back(copy(old_root->children[i],answer));
	}

	// Add the parent pointer
	answer->parent=the_parent;
	return answer;
}

template <class T> BPlusTree<T>::~BPlusTree() {
	destroy_tree(root);	// Destroy all but the root
	delete root;
}

template <class T> void BPlusTree<T>::destroy_tree(BPlusTreeNode<T>* p) {
	// Use recursion to delete all root's children and children's children, etc
	for (unsigned int i=0;i<p->children.size();i++) {
		destroy_tree(p->children[i]);
		delete p->children[i];
	}
}

template <class T> bool BPlusTree<T>::compare_children(const BPlusTreeNode<T>* first, const BPlusTreeNode<T>* second) {
	if (first->keys[first->keys.size()-1]<second->keys[0]) {
		return true;
	} else {
		return false;
	}
}

template <class T> std::vector<BPlusTreeNode<T>*> BPlusTree<T>::sort_children(std::vector<BPlusTreeNode<T>*> children) {

	// Make new vector to hold sorted values
	std::vector<BPlusTreeNode<T>*> sorted_children;
	if (children.size()<2) {
		return children;
	} else if (children.size()==2) {
		if (compare_children(children[0],children[1])) {
			sorted_children.push_back(children[0]);
			sorted_children.push_back(children[1]);
		} else {
			sorted_children.push_back(children[1]);
			sorted_children.push_back(children[0]);
		}
	} else {
		return children;
	}

	return sorted_children;
}

template <class T> void BPlusTree<T>::insert(const T& key_value) {

	// PRINT TESTING
	std::cout << std::endl << "Trying to insert value: " << key_value << std::endl;
	// PRINT TESTING

	// Find the correct leaf node...start at root
	BPlusTreeNode<T>* current = root;
	// While we're not at a leaf node, keep going down
	while (!current->is_leaf()) {

		// PRINT TESTING
		std::cout << "Currently in node with values: ";
		for (unsigned int i=0;i<current->keys.size();i++) {
			std::cout << current->keys[i] << " ";
		}
		std::cout << "and " << current->children.size() << " children. They are: " << std::endl;
		for (unsigned int i=0;i<current->children.size();i++) {
			std::cout << "Number " << i << " with values: ";
			for (unsigned int z=0;z<current->children[i]->keys.size();z++) {
				std::cout << current->children[i]->keys[z] << " ";
			}
			std::cout << std::endl;
		}
		// PRINT TESTING

		bool bigger_than = true;

		// If the value to insert is less than any of the stored keys in current node, go to corresponding child
		for (unsigned int i=0;i<current->keys.size();i++) {
			if (current->keys[i]>key_value) {

				// PRINT TESTING
				std::cout << current->keys[i] << " is bigger than " << key_value << " so moving left" << std::endl;
				// PRINT TESTING

				bigger_than=false; // Set flag to false so next if statement doesn't trigger
				current=current->children[i];
				break; // Found the correct next branch, so break loop
			}
		}
		// If key value is bigger than all the stored keys, then go to right most child
		if (bigger_than) {

			// PRINT TESTING
			std::cout << current->keys[current->keys.size()-1] << " is smaller than " << key_value << " so moving right." << std::endl;
			// PRINT TESTING

			current = current->children[(current->children.size())-1];
		}
	}

	// Add value to leaf node -- make sure everything is sorted
	current->keys.push_back(key_value);
	std::sort(current->keys.begin(),current->keys.end());

	// PRINT TESTING
	std::cout << "Inserted value: " << key_value << std::endl;
	std::cout << "Contents of current Node:" << std::endl;
	for (unsigned int i=0;i<current->keys.size();i++) {
		std::cout << current->keys[i] << " ";
	}
	std::cout << std::endl;
	// PRINT TESTING

	// Call restructure function to check if insertion made a node too big
	restructure(current);

}

template <class T> void BPlusTree<T>::restructure(BPlusTreeNode<T>* current) {
	//Check if node has too many values
	if (current->keys.size()==size) {

		// Calculate midpoint for split
		unsigned int midpoint = size/2;

		// 4 Cases to check for -- splitting the root for the first time, splitting root subsequent times, splitting internal node, or a leaf
		if (current==root) {
			if (root->children.size()==0) {
				// Splitting Root for  the first time

				// Create new children
				BPlusTreeNode<T>* left = new BPlusTreeNode<T>;
				BPlusTreeNode<T>* right = new BPlusTreeNode<T>;

				// Add values to children using midpoint
				for (unsigned int a=0;a<midpoint;a++) {
					left->keys.push_back(current->keys[a]);
				}	

				for (unsigned int b=midpoint;b<current->keys.size();b++) {
					right->keys.push_back(current->keys[b]);
				}

				// Make current root the parent of children
				left->parent = current;
				right->parent = current;

				// Clear out old values and add in middle value
				current->keys.clear();
				current->keys.push_back(right->keys[0]);

				// Then  update root's children
				current->children.push_back(left);
				current->children.push_back(right);

				// PRINT TESTING
				std::cout << std::endl <<"Root Restructure first time:"<< std::endl << "Contents of current node" << std::endl;
				for (unsigned int i=0;i<current->keys.size();i++) {
					std::cout << current->keys[i] << " ";
				}

				std::cout << std::endl << "Contents of left node" << std::endl;
				for (unsigned int i=0;i<left->keys.size();i++) {
					std::cout << left->keys[i]<< " ";
				}

				std::cout << std::endl << "Contents of right node" << std::endl;
				for (unsigned int i=0;i<right->keys.size();i++) {
					std::cout << right->keys[i]<< " ";
				}
				std::cout << std::endl << std::endl;
				// PRINT TESTING

			} else {
				// Splitting root subsequent times

				// PRINT TESTING
				std::cout << std::endl <<"Root restructure not first time:"<< std::endl;
				std::cout << "Contents of node before restructure:" << std::endl;
				for (unsigned int i=0;i<current->keys.size();i++) {
					std::cout << current->keys[i] << " ";
				}
				std::cout << std::endl;
				// PRINT TESTING

				// Make new children
				BPlusTreeNode<T>* left = new BPlusTreeNode<T>;
				BPlusTreeNode<T>* right = new BPlusTreeNode<T>;

				// Add values to children but exclude middle value from right hand child
				for (unsigned int a=0;a<midpoint;a++) {
					left->keys.push_back(current->keys[a]);
				}	

				T mid_value = current->keys[midpoint];

				for (unsigned int b=midpoint+1;b<current->keys.size();b++) {
					right->keys.push_back(current->keys[b]);
				}

				// Make current root the parent of the new children
				left->parent = current;
				right->parent = current;

				// Clear out old values from root and add middle value
				current->keys.clear();
				current->keys.push_back(mid_value);

				// Need to handle children's children -- update those parent child relationships
				for (unsigned int a=0;a<midpoint+1;a++) {
					left->children.push_back(current->children[a]);
					left->children[a]->parent=left;
				}

				int count=0;

				for (unsigned int b=midpoint+1;b<current->children.size();b++) {
					right->children.push_back(current->children[b]);
					right->children[count]->parent=right;
					count++;
				}

	 			// Then  update children of current root
	 			current->children.clear();
				current->children.push_back(left);
				current->children.push_back(right);

				// PRINT TESTING
				std::cout << "Contents of current node" << std::endl;
				for (unsigned int i=0;i<current->keys.size();i++) {
					std::cout << current->keys[i] << " ";
				}

				std::cout << std::endl << "Contents of left node" << std::endl;
				for (unsigned int i=0;i<left->keys.size();i++) {
					std::cout << left->keys[i]<< " ";
				}

				std::cout << std::endl << "Contents of right node" << std::endl;
				for (unsigned int i=0;i<right->keys.size();i++) {
					std::cout << right->keys[i]<< " ";
				}
				std::cout << std::endl << std::endl;
				// PRINT TESTING

			}

		} else if (current->is_leaf()) {
			// Need to split a Leaf

			// PRINT TESTING
			std::cout << std::endl <<"Leaf Restructure" << std::endl;
			std::cout << "Contents of parents before restructure:" << std::endl;
			for (unsigned int i=0;i<current->parent->keys.size();i++) {
				std::cout << current->parent->keys[i] << " ";
			}
			std::cout << std::endl;
			// PRINT TESTING

			// Create two new vectors that will hold new values for resultant nodes
			std::vector<T> left_values;
			std::vector<T> right_values;

			// Add proper values to those vectors
			for (unsigned int a=0;a<midpoint;a++) {
				left_values.push_back(current->keys[a]);
			}	

			for (unsigned int b=midpoint;b<current->keys.size();b++) {
				right_values.push_back(current->keys[b]);
			}

			// The current leaf will be the "left" node in the split
			// Need to make the right node
			BPlusTreeNode<T>* right = new BPlusTreeNode<T>;

			// Give right node proper variables
			right->parent=current->parent;
			right->keys=right_values;

			// Update values for current / left node
			current->keys=left_values;

			// Update parent node with new right hand child
			// Need to make sure children are sorted though
			current->parent->children.push_back(right);
			current->parent->children=sort_children(current->parent->children);

			// Also add the key to parent and sort those values again
			current->parent->keys.push_back(right->keys[0]);
			std::sort(current->parent->keys.begin(),current->parent->keys.end());

			// PRINT TESTING
			std::cout << "Contents of new left node" << std::endl;
			for (unsigned int i=0;i<current->keys.size();i++) {
				std::cout << current->keys[i] << " ";
			}
			std::cout << std::endl << "Contents of right node" << std::endl;
			for (unsigned int i=0;i<right->keys.size();i++) {
				std::cout << right->keys[i]<< " ";
			}
			std::cout << std::endl << "Contents of parent node" << std::endl;
			for (unsigned int i=0;i<current->parent->keys.size();i++) {
				std::cout << current->parent->keys[i]<< " ";
			}
			std::cout << std::endl << std::endl;
			// PRINT TESTING

			// Continue to restructure up the tree
			restructure(current->parent);

		} else {
			// Need to split an Internal Node

			// PRINT TESTING
			std::cout << std::endl <<"Internal Restructure:"<< std::endl;
			std::cout << "Contents of node before restructure:" << std::endl;
			for (unsigned int i=0;i<current->keys.size();i++) {
				std::cout << current->keys[i] << " ";
			}
			std::cout << std::endl;
			// PRINT TESTING

			// Create two vectors to hold values for resultant nodes
			std::vector<T> left_values;
			std::vector<T> right_values;

			// Add proper values to those nodes, but exclude middle from right hand split
			for (unsigned int a=0;a<midpoint;a++) {
				left_values.push_back(current->keys[a]);
			}	

			T mid_value = current->keys[midpoint];

			for (unsigned int b=midpoint+1;b<current->keys.size();b++) {
				right_values.push_back(current->keys[b]);
			}

			// Make the right hand node with proper variables
			BPlusTreeNode<T>* right = new BPlusTreeNode<T>;
			right->parent=current->parent;
			right->keys=right_values;

			// Update current / new left hand node with proper values
			current->keys=left_values;

			// Add middle value to parent and sort those values again
			current->parent->keys.push_back(mid_value);
			std::sort(current->parent->keys.begin(),current->parent->keys.end());

			// Handle the children's children -- create two vectors and split current node's children
			std::vector<BPlusTreeNode<T>*> left_children;
			std::vector<BPlusTreeNode<T>*> right_children;

			for (unsigned int a=0;a<midpoint+1;a++) {
				left_children.push_back(current->children[a]);
			}

			for (unsigned int b=midpoint+1;b<current->children.size();b++) {
				right_children.push_back(current->children[b]);
				current->children[b]->parent=right;
			}

			// Update split nodes with correct children
 			current->children=left_children;
			right->children=right_children;

			// Add right hand node to be a child of current parent
			current->parent->children.push_back(right);

			// PRINT TESTING
			std::cout << "Contents of parent node after restructure" << std::endl;
			for (unsigned int i=0;i<current->parent->keys.size();i++) {
				std::cout << current->parent->keys[i] << " ";
			}
			std::cout << std::endl << "Contents of left node" << std::endl;
			for (unsigned int i=0;i<current->keys.size();i++) {
				std::cout << current->keys[i]<< " ";
			}
			std::cout << std::endl << "Contents of right node" << std::endl;
			for (unsigned int i=0;i<right->keys.size();i++) {
				std::cout << right->keys[i]<< " ";
			}
			std::cout << std::endl << std::endl;
			// PRINT TESTING

			// Continue to restructure further up the tree
			restructure(current->parent);
		}
	}
}

template <class T> BPlusTreeNode<T>* BPlusTree<T>::find(const T& key_value) {
	// If the tree is empty, return NULL
	if (root->keys.size()==0) {
		return NULL;
	}

	// Start at root and make way down to lead where value is supposed to fit
	BPlusTreeNode<T>* current = root;
	while (!current->is_leaf()) {

		bool bigger_than = true;

		// Check if value is smaller than any keys in current node, if so, go to appropriate child
		for (unsigned int i=0;i<current->keys.size();i++) {
			if (current->keys[i]>key_value) {
				bigger_than=false;
				current=current->children[i];
				break;
			}
		}
		// else go to rightmost child
		if (bigger_than) {
			current = current->children[(current->children.size())-1];
		}
	}
	// Should be at correct leaf node, so return pointer to current location
	return current;
}

template <class T> void BPlusTree<T>::print_in_order(std::ofstream& outfile, const BPlusTreeNode<T>* p, int depth) {
	
	// If not at null node...
	if (p) {
		// Calculate midpoint
		unsigned int midpoint = p->children.size()/2;

		// handle first half of children
		for (unsigned int i=0;i<midpoint;i++) {
			print_in_order(outfile,p->children[i],depth+1);
		}

		// Prepare to print values in current node by creating tabs equal to depth in tree
		for (int i=0;i<depth;i++) {
			outfile << "\t";
		}

		// Print out values in current node
		for (unsigned int i=0;i<p->keys.size();i++) {
			outfile << p->keys[i];

			// Add comas for multiple keys in a node
			if (i!=p->keys.size()-1) {
				outfile << ",";
			}
		}

		// New line to print next
		outfile << "\n";

		// Handle second half of children
		for (unsigned int i=midpoint;i<p->children.size();i++) {
			print_in_order(outfile,p->children[i],depth+1);
		}
	}
}

template <class T> void BPlusTree<T>::print_sideways(std::ofstream& outfile) {
	// If tree is empty, say so
	if (root->keys.size()==0) {
		outfile << "Tree is empty." << std::endl;
	} else {
		// else call recursive helper function to print
		print_in_order(outfile,root,0);
	}
}

template <class T> void BPlusTree<T>::print_BFS(std::ofstream& outfile) {
	
	// If tree is empty, say so
	if (root->keys.size()==0) {
		outfile << "Tree is empty." << std::endl;
	} else {
		// else print BFS

		// Create lists to hold nodes
		std::list<BPlusTreeNode<T>*> current_row;
		std::list<BPlusTreeNode<T>*> next_row;

		// start at root
		current_row.push_back(root);

		// While there are still more levels...
		while(!current_row.empty()) {

			// While there are still more nodes on this level...
			while(!current_row.empty()) {

				// Grab a node on this level
				BPlusTreeNode<T>*& temp = current_row.front();

				// print out that nodes keys
				for (unsigned int i=0;i<temp->keys.size();i++) {
					outfile << temp->keys[i];

					// Add commas to delineate separate keys
					if (i!=temp->keys.size()-1) {
						outfile << ",";

					// Add tabs to delineate separate nodes -- don't put at the end of a level though
					} else if ((i==temp->keys.size()-1)&&(current_row.size()!=1)) {
						outfile << "\t";
					}
				}

				// Add the children of the current node on this level to the nodes on the next level
				for (unsigned int i=0;i<temp->children.size();i++) {
					next_row.push_back(temp->children[i]);
				}

				// Move on to next node on this level
				current_row.pop_front();
			}

			// Add a new line now that we're finished on current level
			outfile << std::endl;

			// move on to next level and repeat
			current_row = next_row;
			next_row.clear();
		}
	}
}
#endif
