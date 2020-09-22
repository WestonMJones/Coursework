
#include <cstdlib>    // library with the exit function
#include <iostream>
#include <string> 
#include "time.h"
#include <algorithm>
#include <vector>


int main() {
	Time t1(3,54,33);
	Time t2;
	Time t3(3,54,9);


	std::cout << "Testing getter methods" << std::endl;
	std::cout << "Time 1 is " << t1.getHour() << " hours " << t1.getMinute() << " minutes and " << t1.getSecond() << " seconds." << std::endl;
	std::cout << "Time 2 is " << t2.getHour() << " hours " << t2.getMinute() << " minutes and " << t2.getSecond() << " seconds." << std::endl;
	std::cout << "Time 3 is " << t3.getHour() << " hours " << t3.getMinute() << " minutes and " << t3.getSecond() << " seconds." << std::endl;


	std::cout << std::endl << "Testing setter methods." << std::endl;
	t1.setHour(0);
	t1.setMinute(0);
	t1.setSecond(0);
	t2.setHour(12);
	t2.setMinute(0);
	t2.setSecond(1);
	t3.setHour(14);
	t3.setMinute(4);
	t3.setSecond(5);

	std::cout << "Time 1 is " << t1.getHour() << " hours " << t1.getMinute() << " minutes and " << t1.getSecond() << " seconds." << std::endl;
	std::cout << "Time 2 is " << t2.getHour() << " hours " << t2.getMinute() << " minutes and " << t2.getSecond() << " seconds." << std::endl;
	std::cout << "Time 3 is " << t3.getHour() << " hours " << t3.getMinute() << " minutes and " << t3.getSecond() << " seconds." << std::endl;


	std::cout << std::endl;

	std::cout << "Standard Version of t1 is: ";
	t1.PrintAmPm();
	std::cout << std::endl;

	std::cout << "Standard Version of t2 is: ";
	t2.PrintAmPm();
	std::cout << std::endl;

	std::cout << "Standard Version of t3 is: ";
	t3.PrintAmPm();
	std::cout << std::endl;

	std::cout << std::endl << "Testing Checkpoint 3 Stuff" << std::endl;
	Time t10(0,0,0);
	Time t11(5,5,5);
	Time t12(5,5,5);
	Time t13(12,0,1);
	Time t14(12,0,2);
	Time t15(16,8,3);
	Time t16(5,9,3);
	Time t17(5,9,3);
	Time t18(5,9,3);
	Time t19(2,7,35);
	Time t20(2,7,36);

	std::vector<Time> times;
	times.push_back(t10);
	times.push_back(t11);
	times.push_back(t12);
	times.push_back(t13);
	times.push_back(t14);
	times.push_back(t15);
	times.push_back(t16);
	times.push_back(t17);
	times.push_back(t18);
	times.push_back(t19);
	times.push_back(t20);

	sort(times.begin(), times.end(), IsEarlierThan);

	for (unsigned int x = 0; x<times.size();++x) {
		times[x].PrintAmPm();
		std::cout << std::endl;
	}
	return 0;

	// g++ *.cpp -o Time_test.exe -Wall  --TO COMPILE
	// ./Time_test.exe 					 --TO RUN
}