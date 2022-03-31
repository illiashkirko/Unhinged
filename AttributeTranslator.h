#ifndef ATTRIBUTETRANSLATOR
#define ATTRIBUTETRANSLATOR

#include "provided.h"
#include "RadixTree.h"
#include "utility.h"

#include <string>
#include <vector>
#include <set>

class AttributeTranslator
{
public:
	AttributeTranslator() {}
	bool Load(std::string filename);
	std::vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const;

private:
	RadixTree<std::set<AttValPair>> m_vocab;
};

#endif //ATTRIBUTETRANSLATOR