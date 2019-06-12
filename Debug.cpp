#include "Debug.h"



Debug::Debug()
{
}

Debug::Debug(std::ostream& os)
{
	pOs = &os;
}


void Debug::init(std::ostream& os)
{
	pOs = &os;
}

Debug::~Debug()
{
}
