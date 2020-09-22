class Time {
public:
	Time();
	Time(int hr,int min, int sec);

	// ACCESSORS
	int getHour() const;
	int getMinute() const;
	int getSecond() const;

	// MODIFIERS
	void setHour(int hr);
	void setMinute(int min);
	void setSecond(int sec);

	// OTHER
	void PrintAmPm() const;

private:
	int hour;
	int minute;
	int second;

};
bool IsEarlierThan(const Time& t1, const Time& t2);

