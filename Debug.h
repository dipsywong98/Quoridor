#pragma once
#include <iostream>

class Debug
{
public:
	Debug();
	Debug(std::ostream &os);
	~Debug();
	void init(std::ostream &os);
	// void setDebug(bool isDebug);
	template <class T> friend Debug& operator<<(Debug& debug, const T& t);
private:
	std::ostream* pOs;
	bool debug;
};

