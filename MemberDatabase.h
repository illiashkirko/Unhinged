#ifndef MEMBERDATABASE
#define MEMBERDATABASE

#include "PersonProfile.h"
#include "RadixTree.h"
#include <vector>
#include <string>
#include <set>

class MemberDatabase
{
public:
	MemberDatabase() {}
	~MemberDatabase() {
		for (int i = 0; i < allprofiles.size(); i++)
			delete allprofiles[i];
	}
	bool LoadDatabase(std::string filename);
	std::vector<std::string> FindMatchingMembers(const AttValPair& input) const;
	const PersonProfile* GetMemberByEmail(std::string email) const {
		PersonProfile** p = m_profiles.search(email);
		if (p == nullptr)
			return nullptr;
		return *p;
	}
private:
	RadixTree<PersonProfile*> m_profiles;
	RadixTree<std::set<std::string>> m_emails;
	std::vector<PersonProfile*> allprofiles;
};

#endif //MEMBERDATABASE