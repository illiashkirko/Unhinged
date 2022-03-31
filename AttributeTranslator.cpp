#include "AttributeTranslator.h"
#include "provided.h"
#include "utility.h"

#include <fstream>
#include <vector>
#include <string>
#include <set>

using namespace std;

bool AttributeTranslator::Load(string filename)
{
	//read from a file
	ifstream cin(filename);
	if (!cin)
		return false;
	string s;
	while (getline(cin, s))
	if (s != "")
	{
		//parse string with source and compatible pairs
		string src_att, src_v, comp_att, comp_v;
		src_att = s.substr(0, s.find(','));
		s = s.substr(s.find(',') + 1);
		src_v = s.substr(0, s.find(','));
		s = s.substr(s.find(',') + 1);
		comp_att = s.substr(0, s.find(','));
		comp_v = s.substr(s.find(',') + 1);
		//insert new source pair and corresponding comp pair to the radix tree
		string source = src_att + "," + src_v;
		AttValPair av(comp_att, comp_v);
		set<AttValPair>* comp_pairs = m_vocab.search(source);
		if (comp_pairs != nullptr)
			comp_pairs->insert(av);
		else
		{
			set<AttValPair> myset;
			myset.insert(av);
			m_vocab.insert(source, myset);
		}
	}
	return true;
}

vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const
{
	//find compatible pairs
	vector<AttValPair> v;
	string s = source.attribute + ',' + source.value;
	set<AttValPair>* s_ptr = m_vocab.search(s);
	if (s_ptr == nullptr)
		return v;
	//if found, copy them to a vector and return
	auto it = s_ptr->begin();
	for (; it != s_ptr->end(); it++)
		v.push_back(*it);
	return v;
}