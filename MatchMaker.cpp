#include "MatchMaker.h"
#include "provided.h"
#include "utility.h"

#include <set>
#include <vector>
#include <string>
#include <map>
#include <algorithm>


using namespace std;

bool cmp(const EmailCount& e1, const EmailCount& e2)
{
	//first compare count then email
	if (e1.count > e2.count)
		return true;
	if (e1.count < e2.count)
		return false;
	return e1.email < e2.email;
}

vector<EmailCount> MatchMaker::IdentifyRankedMatches(string email, int threshold) const
{
	//getting personprofile by email
	const PersonProfile* p = m_mdb->GetMemberByEmail(email);
	if (p == nullptr)
	{
		std::vector<EmailCount> v;
		return v;
	}
	//for each attvalpair from personprofile find compatible pairs and add them to a set
	set<AttValPair> comp_pairs;
	for (int i = 0; i < p->GetNumAttValPairs(); i++)
	{
		AttValPair av;
		if (p->GetAttVal(i, av))
		{
			vector<AttValPair> v = m_at->FindCompatibleAttValPairs(av);
			for (int j = 0; j < v.size(); j++)
				comp_pairs.insert(v[j]);
		}
	}
	//for each compatible pair in a set look for people who have it and count how many times they occure
	std::map<std::string, int> possible_matches;
	auto it = comp_pairs.begin();
	for (; it != comp_pairs.end(); it++)
	{
		std::vector<std::string> matches = m_mdb->FindMatchingMembers(*it);
		for (int i = 0; i < matches.size(); i++)
		{
			if (possible_matches.find(matches[i]) == possible_matches.end())
				possible_matches[matches[i]] = 1;
			else
				possible_matches[matches[i]]++;
		}
	}
	//add results that are higher than the threshold to a vector
	std::vector<EmailCount> result;
	auto mapit = possible_matches.begin();
	for (; mapit != possible_matches.end(); mapit++)
		if (mapit->second >= threshold)
			result.push_back(EmailCount(mapit->first, mapit->second));
	//sort the vector and return
	sort(result.begin(), result.end(), cmp);
	return result;
}

