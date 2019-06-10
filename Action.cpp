#include "Action.h"

std::ostream& operator<<(std::ostream& os, const Action& action)
{
	os << action.playerId << ": " << (action.type == Action::Type::kWall?"W":"M")<<action.position;
	return os;
}
