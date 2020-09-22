class Time {
public:
	Time();
	Time(uintptr_t hr,uintptr_t min, uintptr_t sec);

	// ACCESSORS
	uintptr_t getHour() const;
	uintptr_t getMinute() const;
	uintptr_t getSecond() const;

	// MODIFIERS
	void setHour(uintptr_t hr);
	void setMinute(uintptr_t min);
	void setSecond(uintptr_t sec);

	// OTHER
	void PrintAmPm() const;

private:
	uintptr_t hour;
	uintptr_t minute;
	uintptr_t second;

};
bool IsEarlierThan(const Time& t1, const Time& t2);


