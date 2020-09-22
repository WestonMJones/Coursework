#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <map>

int main(int argc, char* argv[]) {

	std::map<int, int> numbers;
	int current_text = 0;

	std::ifstream in_str(argv[1]);
	if (in_str.good()) {
		while (in_str >> current_text) {
			++numbers[current_text];

		}
	}

	std::vector<int> modes;
	int max = 0;

	std::map<int, int>::const_iterator it;
	for (it = numbers.begin(); it != numbers.end(); ++it) {
		//std::cout << it->first << "\t" << it->second << std::endl;
		if (it->second>max) {
			modes.clear();
			max = it->second;
			modes.push_back(it->first);
		} else if (it->second==max) {
			modes.push_back(it->first);
		}
	}

	std::cout << "The modes are:" << std::endl;
	for (unsigned int i=0;i<modes.size();i++) {
		std::cout << modes[i]<< std::endl;
	}
  return 0;
}
