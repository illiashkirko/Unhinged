#include "MemberDatabase.h"
#include "RadixTree.h"
#include "provided.h"

#include <fstream>
#include <string>
#include <vector>
#include <set>

using namespace std;


bool MemberDatabase::LoadDatabase(string filename)
{
	//read from a file
	ifstream cin(filename);
	if (!cin)
		return false;
	string name;
	while (getline(cin, name))
	{
		//read input data
		string email;
		getline(cin, email);
		if (m_profiles.search(email) != nullptr)
			return false;
		int num = 0;
		cin >> num;
		cin.ignore(10000, '\n');
		PersonProfile* pp = new PersonProfile(name, email);
		allprofiles.push_back(pp);
		string parseMe;
		//read attribute pairs and add them to the radix tree
		for (int i = 0; i < num; i++)
		{
			getline(cin, parseMe);
			string att, val;
			att = parseMe.substr(0, parseMe.find(','));
			val = parseMe.substr(parseMe.find(',') + 1);
			pp->AddAttValPair(AttValPair(att, val));
			//find a corresponding set of emails and insert a new email in that set
			set<string>* myset = m_emails.search(parseMe);
			if (myset != nullptr)
				myset->insert(email);
			else
			{
				set<string> newset;
				newset.insert(email);
				m_emails.insert(parseMe, newset);
			}
		}
		m_profiles.insert(email, pp);
		getline(cin, name); //reading empty line
	}
	return true;
}

vector<string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const
{
	string source = input.attribute + ',' + input.value;
	vector<string> v;
	//find set of pinters to emails
	set<string>* s_ptr = m_emails.search(source);
	if (s_ptr == nullptr)
		return v;
	//if it's not nullptr, add all items to a vector and return
	auto it = s_ptr->begin();
	for (; it != s_ptr->end(); it++)
		v.push_back(*it);
	return v;
}