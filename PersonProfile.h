#ifndef PERSONPROFILE
#define PERSONPROFILE

#include "RadixTree.h"
#include "provided.h"
#include <string>
#include <vector>
#include <set>

class PersonProfile
{
public:
	PersonProfile(std::string name, std::string email) {
		m_name = name;
		m_email = email;
	}
	~PersonProfile() {}
	std::string GetName() const {
		return m_name;
	}
	std::string GetEmail() const {
		return m_email;
	}
	void AddAttValPair(const AttValPair& attval);
	int GetNumAttValPairs() const {
		return m_attvalpairs.size();
	}
	bool GetAttVal(int attribute_num, AttValPair& attval) const;
private:
	std::string m_name;
	std::string m_email;
	RadixTree<std::set<std::string>> m_attributes;
	std::vector<AttValPair> m_attvalpairs;
};

#endif //PERSONPROFILE