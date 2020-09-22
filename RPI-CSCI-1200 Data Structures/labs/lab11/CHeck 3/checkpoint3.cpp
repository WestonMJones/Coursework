// Question 3.1

template <class T>
const T& FindLargestInTree(TreeNode<T>* root) {
	while(root->right){
		root = root->right;
	}
	return root->value;
}

// Question 3.2 -- Helper Function -- Don't Change

template <class T>
TreeNode<T>* FindSmallestInRange(const T& a, const T& b, TreeNode<T>* root){
	if(!root){
		return NULL;
	}
	T best_value = FindLargestInTree(root);
	TreeNode<T>* ret = FindSmallestInRange(a, b, root, best_value);
	if(best_value >= b){
		return NULL;
	}
	return ret;
}

// Question 3.2 Actual Solution

template <class T>
TreeNode<T>* FindSmallestInRange(const T& a, const T& b, TreeNode<T>* root, T& best_value){
	if(!root){
		return NULL;
	}
	TreeNode<T>* left_subtree = FindSmallestInRange(a,b,root->left,best_value);
	TreeNode<T>* right_subtree = FindSmallestInRange(a,b,root->right,best_value);
	if(root->value > a && root->value < best_value){
		best_value = root->value;
		return root;
	} else if(left_subtree && left_subtree->value == best_value){
		return left_subtree;
	} else if (right_subtree){
		return right_subtree;
	}
	return NULL;
}

// Question 3.3 Solution

template <class T>
std::vector<T> TreeSort(TreeNode<T>* root){
	std::vector<T> ret;
	T start = FindSmallestInTree(root);
	T end = FindLargestInTree(root);
	ret.push_back(start);
	TreeNode<T>* find = FindSmallestInRange(ret[ret.size()-1],end,root);
	while(find){
		ret.push_back(find->value);
		find = FindSmallestInRange(ret[ret.size()-1],end,root);
	}
	ret.push_back(end);
	return ret;
}
