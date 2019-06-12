#pragma once
#include <iostream>
#include <fstream>

extern bool debug;

class Log
{
public:
	std::ofstream *pFout = nullptr;
	void setF(std::ofstream *p) { pFout = p; }
	template <class T> Log& operator<<(const T& t)
	{
		if (debug) {
			if(pFout != nullptr)
			{
				(*pFout) << t;
			}else
			{
				std::cout << t;
			}
		}
		return *this;
	}
};