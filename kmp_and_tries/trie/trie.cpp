#include "trie.h"
#include <iostream>

Trie::Trie()
{
	this->root = this->getNode();
}

// Returns new trie node (initialized to NULLs)
struct TrieNode* Trie::getNode(void)
{
	struct TrieNode* pNode = new TrieNode();
	return pNode;
}

// If not present, inserts key into trie. If the
// key is prefix of trie node, just marks leaf node
void Trie::insert(struct TrieNode* root, const std::string key)
{
	struct TrieNode* ptr = this->root;
	for (char c : key) {
		if (ptr->children[c - 'a'] == NULL) {
			ptr->children[c - 'a'] = this->getNode();
		}
		ptr = ptr->children[c - 'a'];
	}
	ptr->isWordEnd = true;
}

bool Trie::search(struct TrieNode *root, std::string key)
{
	struct TrieNode* ptr = this->root;
	for (char c : key) {
		if (ptr->children[c - 'a'] == NULL) {
			return false;
		}
		ptr = ptr->children[c - 'a'];
	}
	return (ptr != NULL && ptr->isWordEnd);
}

// Returns 0 if current node has a child
// If all children are NULL, return 1.
bool Trie::isLastNode(struct TrieNode* root)
{
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (root->children[i] != NULL) {
			return false;
		}
	}
	return true;
}

// Recursive function to print auto-suggestions for given
// node.
void Trie::suggestionsRec(struct TrieNode* root,
					std::string currPrefix)
{
	// found a string in Trie with the given prefix
	if (root->isWordEnd) {
		std::cout << currPrefix << std::endl;
	}

	// All children struct node pointers are NULL
	if (this->isLastNode(root)) {
		return;
	}

	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (root->children[i] != NULL) {
			// append current character to currPrefix string
			currPrefix.push_back(97 + i);

			// recur over the rest
			this->suggestionsRec(root->children[i], currPrefix);

			// remove last character
			currPrefix.pop_back();
		}
	}
}

// print suggestions for given query prefix.
int Trie::printAutoSuggestions(TrieNode* root, const std::string query)
{
	struct TrieNode* ptr = this->root;

	// Check if prefix is present and find the
	// node (of last character) with last character of
	// given string.
	for (char c : query) {
		if (ptr->children[c - 'a'] == NULL) {
			return 0;
		}
		ptr = ptr->children[c - 'a'];
	}

	// If prefix is present as a word.
	bool isWord = (ptr->isWordEnd == true);

	// If prefix is last node of tree (has no
	// children)
	bool isLast = this->isLastNode(ptr);

	// If prefix is present as a word, but
	// there is no subtree below the last
	// matching node.
	if (isWord && isLast) {
		std::cout << query << std::endl;
		return -1;
	}

	// If there are are nodes below last
	// matching character.
	if (!isLast) {
		std::string prefix = query;
		this->suggestionsRec(ptr, prefix);
		return 1;
	}
	return 0;
}
void Trie::processContext()
{
	std::ifstream file("lorem.txt");
	std::string word;
	while (file >> word) {		
		this->insert(this->root, word);
	}
	file.close();
	
}
