#include "trie.h"

int Trie::getIndex(char c)
{
    if (isdigit(c))
        return c - '0';
    if (isalpha(c))
        return 10 + tolower(c) - 'a';
    if (c == '.')
        return ALPHA_SIZE;

    throw "Undefined character";
}

void Trie::insert(string key)
{
    TrieNode *node = root;
    for (size_t i = 0; i < key.length(); i++)
    {
        int index = getIndex(key[i]);
        if (node->children[index] == nullptr)
            node->children[index] = new TrieNode();
        node = node->children[index];
    }
    node->isEndOfWord = true;
}

bool Trie::search(string key)
{
    TrieNode *node = root;
    for (size_t i = 0; i < key.length(); i++)
    {
        int index = getIndex(key[i]);
        node = node->children[index];
        if (node == nullptr)
            return false;
    }
    if (node->isEndOfWord)
        return true;
    return false;
}

bool isNodeEmpty(TrieNode *node)
{
    for (int i = 0; i < ALPHA_SIZE; i++)
        if (node->children[i] != nullptr)
            return false;
    return true;
}

void Trie::remove(string key)
{
    remove(key, root, 0);
}

// Returns Root
TrieNode *Trie::remove(string key, TrieNode *node, int depth)
{
    if (node == nullptr)
        return nullptr;

    if ((size_t)depth == key.length())
    {
        if (node->isEndOfWord)
            node->isEndOfWord = false;

        if (isNodeEmpty(node))
        {
            delete node;
            node = nullptr;
        }
        return node;
    }

    int index = getIndex(key[depth]);
    node->children[index] = remove(key, node->children[index], depth + 1);

    if (isNodeEmpty(node) && !node->isEndOfWord && depth != 0)
    {
        delete node;
        node = nullptr;
    }

    return node;
}
