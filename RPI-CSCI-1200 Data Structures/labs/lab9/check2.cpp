#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <map>

int main(int argc, char* argv[]) {

	std::map<int, int>::iterator it;

	std::map<int, int> numbers;
	int current_text = 0;

	std::ifstream in_str(argv[1]);
	if (in_str.good()) {
		while (in_str >> current_text) {
			it = numbers.find(current_text);
			if (it==numbers.end()) {
				numbers.insert(std::make_pair(current_text,0));
			} else {
				it->second++;
			}

		}
	}

	std::vector<int> modes;
	int max = 0;

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
