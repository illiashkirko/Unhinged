#include "PersonProfile.h"

#include <set>
#include <string>

using namespace std;

void PersonProfile::AddAttValPair(const AttValPair& attval) 
{
	//find attvalpairs with this attribute if exist
	set<string>* val = m_attributes.search(attval.attribute);
	//add new value to a vector and also add it to the tree
	m_attvalpairs.push_back(attval);
	set<string> s;
	if (val != nullptr) 
		s = *val;
	s.insert(attval.value);		
	m_attributes.insert(attval.attribute, s);
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const 
{
	//return i-th member of the vector
	if (attribute_num < 0 && attribute_num >= GetNumAttValPairs())
		return false;
	attval.attribute = m_attvalpairs[attribute_num].attribute;
	attval.value = m_attvalpairs[attribute_num].value;
	return true;
}