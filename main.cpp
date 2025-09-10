#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Each node in the Trie
class TrieNode
{
public:
    // Each node has up to 26 children (for each letter)
    TrieNode *children[96];

    // Marks if this node completes a word
    bool isEndOfWord;
    // Constructor
    TrieNode()
    {
        isEndOfWord = false;
        for (int i = 0; i < 96; i++)
        {
            children[i] = nullptr;
        }
    }
};

// The Trie class
class Trie
{
private:
    TrieNode *root;

    // Helper function to find all words from a node
    void findAllWords(TrieNode *node, string currentWord, vector<string> &results)
    {
        // TODO: Implement this function
        // not needed
    }

    // Helper for remove
    bool removeHelper(TrieNode *node, const string &word, int wordIdx)
    {
        if (!node)
            return false;
        if (wordIdx == word.size())
        {
            if (!node->isEndOfWord)
                return false;
            node->isEndOfWord = false;
            for (int i = 0; i < 96; i++)
            {
                if (node->children[i])
                    return false;
            }
            return true;
        }

        char c = word[wordIdx];
        if (c < ' ')
            return false;
        int index = c - ' ';

        if (node->children[index] == nullptr)
            return false;

        bool shouldDeleteChild = removeHelper(node->children[index], word, wordIdx + 1);

        if (shouldDeleteChild)
        {
            delete node->children[index];
            node->children[index] = nullptr;
            if (!node->isEndOfWord)
            {
                for (int i = 0; i < 96; i++)
                {
                    if (node->children[i])
                        return false;
                }
                return true;
            }
        }
        return false;
    }

public:
    Trie()
    {
        // TODO: Implement this function
        root = new TrieNode();
    }

    // Insert a word into the Trie
    void insert(string word)
    {
        if (!root) // if there is no trie
        {
            root = new TrieNode(); // make a new one
        }
        TrieNode *temp = root;
        int i = 0;
        for (int i = 0; i < word.length(); i++)
        {
            char thisChar = word[i];
            if (thisChar < ' ')
            {
                continue;
            }
            int index = thisChar - ' ';

            // if there is no node in children[index] it means that that character is not there
            if (temp->children[index] == nullptr)
            {
                // then make a trienode at that children position (like saying that there is actually a character here)
                // just like in the frequency array when assigning 1 to the index of a character
                temp->children[index] = new TrieNode();
            }
            if (temp->children[0])
            {
                temp->isEndOfWord = true; // Hazem Magdy
            }
            // then after this we anyway go to that node if there is a node or not
            temp = temp->children[index];
        }
        temp->isEndOfWord = true;
    }

    // Search for a word in the Trie
    bool search(string word)
    {
        if (!root)
        {
            return false; // if there is no trie return false
        }

        TrieNode *temp = root;

        for (char thisChar : word)
        {
            if (thisChar < ' ')
            {
                continue;
            }
            int index = thisChar - ' ';

            // if there is a letter in the index then it is there, if it is null then its not
            if (temp->children[index] == nullptr)
            {
                return false;
            }
            temp = temp->children[index]; // go to that letter and check its children for the remaining of word
        }
        return temp->isEndOfWord;
    }

    // Check if any word starts with the given prefix //yo //you //your //you're //yo yo
    bool startsWith(string prefix)
    {
        if (!root)
        {
            return false;
        }

        TrieNode *current = root;
        for (char c : prefix)
        {
            if (c < ' ') // we take from space char and upper
            {
                return false;
            }

            int index = c - ' '; // index for all char from space up
            if (current->children[index] == nullptr)
            {
                return false;
            }
            current = current->children[index];
        }
        return true;
    }

    // helper for autocomplete
    void autocomp(TrieNode *root, string currentstring, int currentcharindex, vector<string> &suggestions)
    {
        if (root == nullptr) // the same as if (!root)
        {
            return;
        }

        currentstring += (currentcharindex + ' '); // to get the char not the index

        if (root->isEndOfWord)
        {
            suggestions.push_back(currentstring);
        }

        for (int i = 0; i < 96; i++)
        {
            autocomp(root->children[i], currentstring, i, suggestions);
        }
        return;
    }

    vector<string> autocomplete(string prefix)
    {
        vector<string> suggestions;
        if (!root)
            return {};
        TrieNode *currentNode = root;
        string start;

        for (int i = 0; i < prefix.length(); i++)
        {
            char thisChar = prefix[i];
            int currIndex = thisChar - ' ';

            if (currentNode->children[currIndex] == nullptr) // end of trie branch
            {
                return suggestions;
            }

            start += thisChar;

            if (currentNode->isEndOfWord)
            {
                suggestions.push_back(start);
            }
            currentNode = currentNode->children[currIndex];
        }

        for (int i = 0; i < 96; i++)
        {
            autocomp(currentNode->children[i], start, i, suggestions);
        }
        return suggestions;
    }

    void remove(string word)
    {
        if (!root)
            return;
        removeHelper(root, word, 0);
    }
    // Bonus functions : counter
    void counter(TrieNode *root, int &count)
    {
        if (root == nullptr)
            return;
        if (root->isEndOfWord)
            count++;

        for (int i = 0; i < 96; i++)
        {
            counter(root->children[i], count);
        }
        return;
    }
    void wordcount()
    {
        int count = 0;
        counter(root, count);
        cout << "Total words in Trie: " << count << endl;
    }
};

// Main function
int main()
{
    cout << "=== TRIE DATA STRUCTURE IMPLEMENTATION ===" << endl;
    cout << "Testing all Trie functionalities..." << endl;

    Trie trie;

    // Test 1: Basic insertion and search
    cout << "\n1. Testing basic insertion and search:" << endl;
    cout << "======================================" << endl;

    vector<string> words = {"apple", "banana", "orange", "grape", "kiwi"};
    for (const string &word : words)
    {
        trie.insert(word);
        cout << "Inserted: " << word << endl;
    }

    // Test search for existing words
    for (const string &word : words)
    {
        bool found = trie.search(word);
        cout << "Search '" << word << "': " << (found ? "FOUND" : "NOT FOUND") << endl;
    }

    // Test search for non-existing words
    vector<string> nonExisting = {"app", "ban", "ora", "graph", "kiwis"}; // is end of word or //not pointed to //not valid node
    for (const string &word : nonExisting)
    {
        bool found = trie.search(word);
        cout << "Search '" << word << "': " << (found ? "FOUND" : "NOT FOUND") << " (expected: NOT FOUND)" << endl;
    }

    // Test 2: Prefix checking
    cout << "\n2. Testing prefix checking:" << endl;
    cout << "==========================" << endl;

    vector<string> prefixes = {"app", "ban", "ora", "grap", "k"}; // apply //apple //app //apply //apple
    for (const string &prefix : prefixes)
    {
        bool hasPrefix = trie.startsWith(prefix);
        cout << "Prefix '" << prefix << "': " << (hasPrefix ? "EXISTS" : "DOESN'T EXIST") << endl;
    }

    vector<string> nonPrefixes = {"x", "yield", "zed", "micro", "nano"};
    for (const string &prefix : nonPrefixes)
    {
        bool hasPrefix = trie.startsWith(prefix);
        cout << "Prefix '" << prefix << "': " << (hasPrefix ? "EXISTS" : "DOESN'T EXIST") << " (expected: DOESN'T EXIST)" << endl;
    }

    // Test 3: Autocomplete functionality
    cout << "\n3. Testing autocomplete functionality:" << endl;
    cout << "======================================" << endl;

    vector<string> testPrefixes = {"a", "b", "o", "g", "k", "ap", "ban", "ora", "gr", "ki"};
    for (const string &prefix : testPrefixes)
    {
        vector<string> suggestions = trie.autocomplete(prefix);
        cout << "Autocomplete for '" << prefix << "': ";
        if (suggestions.empty())
        {
            cout << "No suggestions found";
        }
        else
        {
            for (size_t i = 0; i < suggestions.size(); i++)
            {
                if (i > 0)
                    cout << ", ";
                cout << suggestions[i];
            }
        }
        cout << endl;
    }

    // Test 4: Edge cases
    cout << "\n4. Testing edge cases:" << endl;
    cout << "======================" << endl;

    // Empty string tests
    bool emptySearch = trie.search(""); // root
    cout << "Search empty string: " << (emptySearch ? "FOUND" : "NOT FOUND") << " (expected: NOT FOUND)" << endl;

    bool emptyPrefix = trie.startsWith("");
    cout << "Starts with empty prefix: " << (emptyPrefix ? "EXISTS" : "DOESN'T EXIST") << " (expected: EXISTS)" << endl;

    vector<string> emptySuggestions = trie.autocomplete("");
    cout << "Autocomplete for empty string: ";
    if (emptySuggestions.empty())
    {
        cout << "No suggestions found";
    }
    else
    {
        for (size_t i = 0; i < emptySuggestions.size(); i++)
        {
            if (i > 0)
                cout << ", ";
            cout << emptySuggestions[i];
        }
    }
    cout << " (expected: all words)" << endl;

    // Test 5: Adding more words and retesting
    cout << "\n5. Testing with additional words:" << endl;
    cout << "================================" << endl;

    vector<string> additionalWords = {"application", "appetizer", "banister", "bandana", "oracle", "grapefruit"}; // a //ap
    for (const string &word : additionalWords)
    {
        trie.insert(word);
        cout << "Inserted: " << word << endl;
    }

    // Test search for new words
    for (const string &word : additionalWords)
    {
        bool found = trie.search(word);
        cout << "Search '" << word << "': " << (found ? "FOUND" : "NOT FOUND") << endl;
    }

    // Test autocomplete with new words
    vector<string> newPrefixes = {"app", "ban", "ora", "gra"};
    for (const string &prefix : newPrefixes)
    {
        vector<string> suggestions = trie.autocomplete(prefix);
        cout << "Autocomplete for '" << prefix << "': ";
        if (suggestions.empty())
        {
            cout << "No suggestions found";
        }
        else
        {
            for (size_t i = 0; i < suggestions.size(); i++)
            {
                if (i > 0)
                    cout << ", ";
                cout << suggestions[i];
            }
        }
        cout << endl;
    }

    // Test 6: Case sensitivity (all lowercase expected)
    cout << "\n6. Testing case sensitivity:" << endl;
    cout << "============================" << endl;

    trie.insert("Hello");
    trie.insert("WORLD");
    trie.insert("Hazem Magdy Lasheen");
    trie.insert("_Hello");
    trie.insert("1234 Ahmed");
    trie.insert("ahmed-lasheen");
    trie.insert("lasheen_hazem");

    vector<string> caseWords = {
        "hello",               // not found
        "Hello",               // found
        "WORLD",               // found
        "world",               // not found
        "HAZEM",               // not found (all uppercase)
        "Hazem Magdy Lasheen", // found
        "_Hello",              // found
        "1234 Ahmed",          // found
        "hazem_lasheen",       // found
        "hazem_Lasheen",       // not found "L capital"
        "ahmed-lasheen",       // found
        "lasheen_hazem"        // found
    };

    for (const string &word : caseWords)
    {
        bool found = trie.search(word);
        cout << "Search '" << word << "': " << (found ? "FOUND" : "NOT FOUND") << endl;
    }

    cout << "\n=== ALL TESTS COMPLETED ===" << endl;
    cout << "\n=== BONUS TESTS===" << endl;
    cout << "\n7. Testing words counter:" << endl;
    cout << "============================" << endl;
    trie.wordcount();

    cout << "\n8. Testing longest word:" << endl;
    cout << "============================" << endl;

    cout << "\n9. Testing remove word:" << endl;
    cout << "============================" << endl;

    bool found = trie.search("_Hello");
    trie.remove("_hello");                                                              // should not do anything
    cout << "Search '" << "_Hello" << "': " << (found ? "FOUND" : "NOT FOUND") << endl; // FOUND
    trie.remove("_Hello");                                                              // should remove _Hello
    found = trie.search("_Hello");
    cout << "Search '" << "_Hello" << "': " << (found ? "FOUND" : "NOT FOUND") << endl; // NOT FOUND

    cout << "\n=== BONUS COMPLETED ===" << endl;

    return 0;
}