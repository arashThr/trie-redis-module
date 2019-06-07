#include <iostream>
using namespace std;

const int ALPHA_SIZE = 10 + 26 + 1;

class TrieNode {
	public:
	TrieNode *children[ALPHA_SIZE];
	bool isEndOfWord;

	TrieNode()
	{
        isEndOfWord = false;
        for (int i = 0; i < ALPHA_SIZE; i++)
			children[i] = nullptr;
	}
};

class Trie
{
    static int getIndex(char);
    TrieNode *remove(string key, TrieNode *node, int depth = 0);

public:
	TrieNode *root;
	void insert(string);
    bool search(string);
    void remove(string key);

    Trie() {
		root = new TrieNode();
	}

	~Trie() {
		delete root;
	}
};
