#include <cstdlib>    // library with the exit function
#include <iostream>
#include <string>
#include "time.h"

Time::Time() {
	hour = 0;
	minute = 0;
	second = 0;
}

Time::Time(int hr, int min, int sec) {
	hour = hr;
	minute = min;
	second = sec;
}

int Time::getHour() const {
	return hour;
}

int Time::getMinute() const {
	return minute;
}

int Time::getSecond() const {
	return second;
}

void Time::setHour(int hr) {
	hour = hr;
}

void Time::setMinute(int min) {
	minute = min;
}

void Time::setSecond(int sec) {
	second = sec;
}

void Time::PrintAmPm() const {

	std::string minpadding = "";
	std::string secpadding = "";
	int newHour = hour;

	std::string noon = "am";
	if (hour>=12) {
		noon = "pm";
		if (hour!=12) {
			newHour = hour - 12;
		} 
	}
	
	if (newHour==0) {
		newHour=12;
	}

	if (minute<10) {
		minpadding = "0";
	}

	if (second<10) {
		secpadding="0";
	}

	std::cout << newHour <<":"<<minpadding<<minute<<":"<<secpadding<<second<<" "<<noon;
}

bool IsEarlierThan(const Time& t1, const Time& t2) {
	if (t1.getHour()<t2.getHour()) {
		return true;
	} else if (t1.getHour()>t2.getHour()) {
		return false;
	} else if (t1.getHour()==t2.getHour()) {
		if (t1.getMinute()<t2.getMinute()) {
			return true;
		} else if (t1.getMinute()>t2.getMinute()) {
			return false;
		} else if (t1.getMinute()==t2.getMinute()) {
			if (t1.getSecond()<t2.getSecond()) {
				return true;
			} else {
				return false;
			}
		}
	}
	return false;
}
