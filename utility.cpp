#include "utility.h"
#include "provided.h"

bool operator<(const AttValPair& av1, const AttValPair& av2)
{
	//first compare attribute then value
	if (av1.attribute < av2.attribute)
		return true;
	if (av1.attribute > av2.attribute)
		return false;
	return av1.value < av2.value;
}
