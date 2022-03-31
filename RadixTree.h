#ifndef RADIXTREE
#define RADIXTREE

#include <string>

using namespace std;

template <typename ValueType>
class RadixTree {
public:
	RadixTree() {
		head = nullptr;
	}
	~RadixTree() {
		cleanUp(head);
	}
	void insert(std::string key, const ValueType& value)
	{
		//if tree is empty, create a new head node
		if (head == nullptr)
		{
			Node* n = new Node;
			head = n;
			n->key = key;
			n->value = value;
			n->hasValue = true;
			return;
		}
		//otherwise
		int i = 0;
		Node* p = head;
		//iterate until we reach the end of key string
		while (i < key.length())
		{
			//if leaf node
			if (p->key != "")
			{
				//if key already in the tree, update its value
				string skey = p->key;
				if (skey == key.substr(i))
				{
					p->value = value;
					p->hasValue = true;
					return;
				}
				//otherwise create new nodes for each letter of common prefix of key and p->key
				int j = 0;
				ValueType v = p->value;
				p->hasValue = false;
				p->key = "";
				while (skey[j] == key[j + i] && j < skey.length() && j + i < key.length())
				{
					Node* pp = new Node;
					p->arr[(int)skey[j]] = pp;
					p = pp;
					j++;
				}
				//if existing one is shorter that the new one
				if (j == skey.length())
				{
					p->value = v;
					p->hasValue = true;
					//create a new node for the new value
					Node* p1 = new Node;
					p->arr[(int)key[j + i]] = p1;
					p1->key = key.substr(j + i + 1);
					p1->value = value;
					p1->hasValue = true;
					return;
				}
				//if new string is shorter than existing one
				if (j + i == key.length())
				{
					p->value = value;
					p->hasValue = true;
					//create a new node for existing value
					Node* p1 = new Node;
					p->arr[(int)skey[j]] = p1;
					p1->key = skey.substr(j + 1);
					p1->value = v;
					p1->hasValue = true;
					return;
				}
				//if both strings have different letters
				Node* p1 = new Node;
				Node* p2 = new Node;
				//store value from p to the new leaf node
				p->arr[(int)skey[j]] = p1;
				p->arr[(int)key[j + i]] = p2;
				p1->key = skey.substr(j + 1);
				p1->value = v;
				p1->hasValue = true;
				//store passed value in a the new leaf node
				p2->key = key.substr(j + i + 1);
				p2->value = value;
				p2->hasValue = true;
				return;
			}
			//if not a leaf node and does not have a curr letter, add a new node with pointer from that letter
			if (p->arr[(int)key[i]] == nullptr)
			{
				Node* addMe = new Node;
				p->arr[(int)key[i]] = addMe;
				addMe->hasValue = true;
				addMe->value = value;
				addMe->key = key.substr(i + 1);
				return;
			}
			//if not a leaf node and has a curr letter, move to the node with that letter
			p = p->arr[(int)key[i]];
			i++;
		}
		if (i == key.length())
			p->value = value;
	}
	ValueType* search(std::string key) const
	{
		int i = 0;
		Node* p = head;
		while (i < key.length())
		{
			if (p == nullptr)
				return nullptr;
			//if leaf node and does not match the key return nullptr
			if (p->arr[(int)key[i]] == nullptr && p->key != key.substr(i))
				return nullptr;
			//if matches the key retrurn value if it has one 
			if (p->key == key.substr(i))
			{
				if (p->hasValue)
					return &(p->value);
				else
					return nullptr;
			}
			//move to the next node
			p = p->arr[(int)key[i]];
			i++;
		}
		//if reached the end of key check if matches
		if (p == nullptr || p->key != key.substr(i))
			return nullptr;
		if (p->hasValue)
			return &(p->value);
		else 
			return nullptr;
	}

private:
	struct Node
	{
		Node() {
			for (int i = 0; i < 128; i++)
				arr[i] = nullptr;
			hasValue = false;
		}
		Node* arr[128];
		bool hasValue;
		ValueType value;
		std::string key;
	};
	Node* head;
	void cleanUp(Node* deleteMe)
	{
		if (deleteMe == nullptr)
			return;
		for (int i = 0; i < 128; i++)
			cleanUp(deleteMe->arr[i]);
		delete deleteMe;
	}
};

#endif //RADIXTREE