#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>

void reverse_list(std::list<int>& l) {
	if (l.size()>1) {
		std::list<int>::iterator p;
		std::list<int>::reverse_iterator ri = l.rbegin();
		int counter = l.size()/2;
		int temp = 0;
		for (p=l.begin();p!=l.end();p++) {
			if (counter>=0) {
				//std::cout << *p << " " << *ri << std::endl;
				temp = *p;
				*p = *ri;
				*ri = temp;
				ri++;
				counter--;
			}
			
		}
	}
	//std::cout << "End of a Call" << std::endl;
}

void reverse_vector(std::vector<int>& v) {
	int temp = 0; // Temporary space to hold values to be swapped
	if (v.size()>1) {
		for (unsigned int x=0;x<(v.size()/2);x++) {
			temp=v[x];
			v[x]=v[v.size()-(1+x)];
			v[v.size()-(1+x)]=temp;
		}
	}
}

void print_list(const std::list<int>& l, const std::string& l_name) {
	std::cout << std::endl << "Contents of "+l_name+": ";
	std::list<int>::const_iterator p;
	std::list<int>::const_iterator end_p = l.end();
	end_p--;
	for (p=l.begin();p!=l.end();p++) {
		std::cout << *p;
		if (p!=end_p) {
			std::cout << ", ";
		}
	}
}

void print_vector(const std::vector<int>& v, const std::string& v_name) {
	std::cout << std::endl << "Contents of "+v_name+": ";
	for (unsigned int x=0;x<v.size();x++) {
		std::cout << v[x];
		if (x!=v.size()-1) {
			std::cout << ", ";
		}
	}
}


int main() {

	std::cout << "Checkpoint One" << std::endl;

	std::vector<int> v1; // 0 elements
	std::vector<int> v2; // 1 element
	std::vector<int> v3; // 2 elements
	std::vector<int> v4; // 3 elements
	std::vector<int> v5; // odd elements
	std::vector<int> v6; // even elements

	for (int i=0;i<10;i++) {
		if (i==5) {
			v2.push_back(i);
			v4.push_back(i);
		} 
		if ((i==3)||(i==7)) {
			v3.push_back(i);
		}
		if ((i==4)||(i==6)) {
			v4.push_back(i);
		}
		if (i!=9) {
			v5.push_back(i);
		}
		v6.push_back(i);
	}

	print_vector(v1,"Vector Zero");
	print_vector(v2,"Vector One");
	print_vector(v3,"Vector Two");
	print_vector(v4,"Vector Three");
	print_vector(v5,"Vector Odd");
	print_vector(v6,"Vector Even");


	std::cout << std::endl << std::endl << "After Reverse" << std::endl;

	reverse_vector(v1);
	reverse_vector(v2);
	reverse_vector(v3);
	reverse_vector(v4);
	reverse_vector(v5);
	reverse_vector(v6);


	print_vector(v1,"Vector Zero");
	print_vector(v2,"Vector One");
	print_vector(v3,"Vector Two");
	print_vector(v4,"Vector Three");
	print_vector(v5,"Vector Odd");
	print_vector(v6,"Vector Even");

	std::cout << std::endl << std::endl << "Checkpoint Two" << std::endl;

	std::list<int> l1; // 0 elements
	std::list<int> l2; // 1 element
	std::list<int> l3; // 2 elements
	std::list<int> l4; // 3 elements
	std::list<int> l5; // odd elements
	std::list<int> l6; // even elements

	for (int i=0;i<10;i++) {
		if (i==5) {
			l2.push_back(i);
			l4.push_back(i);
		} 
		if ((i==3)||(i==7)) {
			l3.push_back(i);
		}
		if ((i==4)||(i==6)) {
			l4.push_back(i);
		}
		if (i!=9) {
			l5.push_back(i);
		}
		l6.push_back(i);
	}

	print_list(l1,"List Zero");
	print_list(l2,"List One");
	print_list(l3,"List Two");
	print_list(l4,"List Three");
	print_list(l5,"List Odd");
	print_list(l6,"List Even");

	std::cout << std::endl << std::endl << "After Reverse" << std::endl;

	reverse_list(l1);
	reverse_list(l2);
	reverse_list(l3);
	reverse_list(l4);
	reverse_list(l5);
	reverse_list(l6);

	print_list(l1,"List Zero");
	print_list(l2,"List One");
	print_list(l3,"List Two");
	print_list(l4,"List Three");
	print_list(l5,"List Odd");
	print_list(l6,"List Even");


	return 0;
}