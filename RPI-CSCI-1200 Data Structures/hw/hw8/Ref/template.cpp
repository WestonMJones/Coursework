// -------------------------------------------------------------------
// TREE NODE CLASS
template <class T> class TreeNode {
	public:
		TreeNode() : left(NULL), right(NULL), parent(NULL) {}
		TreeNode(const T& init) : value(init), left(NULL), right(NULL), parent(NULL) {}
		T value;
		TreeNode* left;
		TreeNode* right;
		TreeNode* parent; // to allow implementation of iterator increment & decrement
};
template <class T> class ds_set;
// -------------------------------------------------------------------
// TREE NODE ITERATOR CLASS
template <class T> class tree_iterator {
	public:
		tree_iterator() : ptr_(NULL), set_(NULL) {}
		tree_iterator(TreeNode<T>* p, const ds_set<T> * s) : ptr_(p), set_(s) {}
		// operator* gives constant access to the value at the pointer
		const T& operator*() const { return ptr_->value; }
		// comparions operators are straightforward
		bool operator== (const tree_iterator& rgt) { return ptr_ == rgt.ptr_; }
		bool operator!= (const tree_iterator& rgt) { return ptr_ != rgt.ptr_; }
		// increment & decrement operators
		tree_iterator<T> & operator++() {
			if (ptr_->right != NULL) { // find the leftmost child of the right node
				ptr_ = ptr_->right;
				while (ptr_->left != NULL) { ptr_ = ptr_->left; }
			} else { // go upwards along right branches... stop after the first left
				while (ptr_->parent != NULL && ptr_->parent->right == ptr_) { ptr_ = ptr_->parent; }
					ptr_ = ptr_->parent;
				}
			return *this;
		}
		tree_iterator<T> operator++(int) { tree_iterator<T> temp(*this); ++(*this); return temp; }
		tree_iterator<T> & operator--() {
			if (ptr_ == NULL) { // so that it works for end()
				assert (set_ != NULL);
				ptr_ = set_->root_;
				while (ptr_->right != NULL) { ptr_ = ptr_->right; }
			} else if (ptr_->left != NULL) { // find the rightmost child of the left node
				ptr_ = ptr_->left;
				while (ptr_->right != NULL) { ptr_ = ptr_->right; }
			} else { // go upwards along left brances... stop after the first right
				while (ptr_->parent != NULL && ptr_->parent->left == ptr_) { ptr_ = ptr_->parent; }
				ptr_ = ptr_->parent;
			}
			return *this;
		}
		tree_iterator<T> operator--(int) { tree_iterator<T> temp(*this); --(*this); return temp; }
	private:
		// representation
		TreeNode<T>* ptr_;
		const ds_set<T>* set_;
};
// -------------------------------------------------------------------
// DS_ SET CLASS
template <class T> class ds_set {
public:
	ds_set() : root_(NULL), size_(0) {}
	ds_set(const ds_set<T>& old) : size_(old.size_) { root_ = this->copy_tree(old.root_,NULL); }
	~ds_set() { this->destroy_tree(root_); root_ = NULL; }
	ds_set& operator=(const ds_set<T>& old) {
		if (&old != this) {
			this->destroy_tree(root_);
			root_ = this->copy_tree(old.root_,NULL);
			size_ = old.size_;
		}
		return *this;
	}
	typedef tree_iterator<T> iterator;
	friend class tree_iterator<T>;
	int size() const { return size_; }
	bool operator==(const ds_set<T>& old) const { return (old.root_ == this->root_); }
	// FIND, INSERT & ERASE
	iterator find(const T& key_value) { return find(key_value, root_); }
	std::pair< iterator, bool > insert(T const& key_value) { return insert(key_value, root_, NULL); }
	int erase(T const& key_value) { return erase(key_value, root_); }
	// ITERATORS
	iterator begin() const {
		if (!root_) return iterator(NULL,this);
		TreeNode<T>* p = root_;
		while (p->left) p = p->left;
		return iterator(p,this);
	}
	iterator end() const { return iterator(NULL,this); }
private:
	// REPRESENTATION
	TreeNode<T>* root_;
	int size_;
	// PRIVATE HELPER FUNCTIONS
	TreeNode<T>* copy_tree(TreeNode<T>* old_root, TreeNode<T>* the_parent) {
		if (old_root == NULL) return NULL;
		TreeNode<T> *answer = new TreeNode<T>();
		answer->value = old_root->value;
		answer->left = copy_tree(old_root->left,answer);
		answer->right = copy_tree(old_root->right,answer);
		answer->parent = the_parent;
		return answer;
	}
	void destroy_tree(TreeNode<T>* p) {
		if (!p) return;
		destroy_tree(p->right);
		destroy_tree(p->left);
		delete p;
	}

	iterator find(const T& key_value, TreeNode<T>* p) {
		if (!p) return end();
		if (p->value > key_value) return find(key_value, p->left);
		else if (p->value < key_value) return find(key_value, p->right);
		else return iterator(p,this);
	}

std::pair<iterator,bool> insert(const T& key_value, TreeNode<T>*& p, TreeNode<T>* the_parent) {
	if (!p) {
		p = new TreeNode<T>(key_value);
		p->parent = the_parent;
		this->size_++;
		return std::pair<iterator,bool>(iterator(p,this), true);
	}
	else if (key_value < p->value)
		return insert(key_value, p->left, p);
	else if (key_value > p->value)
		return insert(key_value, p->right, p);
	else
		return std::pair<iterator,bool>(iterator(p,this), false);
	}
int erase(T const& key_value, TreeNode<T>* &p) {

	//Return 0 if nothing erased, 1 otherwise
    /* Implemented in Lecture 20 */ 
	//What if we can't erase the value
	//iterator it = find(key_value);

	//Need to check if we're erasing the root
		//Especially if root was only node
	if(!p){ return 0; }


	//Basically do our find first
	if(p->value < key_value){
		return erase(key_value,p->right);
	}
	else if(p->value > key_value){
		return erase(key_value,p->left);
	}

	//Otherwise we're at the right node



//There's both children, pick a value, copy it, call erase()
	if(p->left && p->right){
		TreeNode<T>* largest_left = p->left;
		while(largest_left->right){
			largest_left = largest_left->right;
		}
		p->value = largest_left->value; //Swap in the value
		erase(p->value,largest_left);
		return 1;
	}
	//If there's only one child, erase, connect my child to my parent, stop
	else if(p->left){ //Left
		TreeNode<T>* tmp = p;
		p = p->left;
		delete tmp;
		size_--;
		return 1;
	}
	else if(p->right){ //Right
		TreeNode<T>* tmp = p;
		p = p->right;
		delete tmp;
		size_--;
		return 1;
	}
	//If there's no children, erase and stop	
	else{
		delete p;
		p = NULL;
		size_--;
	}
  }
};
