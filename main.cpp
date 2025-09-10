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
    // you  //u is end of word
    // your
    // you're

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
    // Input: current node, current word formed so far, results vector to store words
    // Output: none (modifies results vector by reference)
    // Purpose: Recursively find all complete words starting from the given node
    void findAllWords(TrieNode *node, string currentWord, vector<string> &results)
    {
        // TODO: Implement this function
    }
    // int count=0;

public:
    // Constructor
    // Input: none
    // Output: none
    // Purpose: Initialize the Trie with a root node
    Trie()
    {
        // TODO: Implement this function
        //start null
        root=new TrieNode();

    }

    // Insert a word into the Trie
    // Input: word to insert (string)
    // Output: none
    // Purpose: Add a word to the Trie by creating nodes for each character
    void insert(string word)
    {              // HAZEM
        if (!root) // if there is no trie
        {
            root = new TrieNode(); // make a new one
        }
        TrieNode *temp = root;

        for (char thisChar : word)
        {
            if (thisChar > 'A' && thisChar < 'Z') // make uppercase letters lowercase
            {
                thisChar = thisChar - 'A' + 'a';
            }

            if (thisChar < 'a' || thisChar > 'z') // if it is not a letter (notice that uppercase is already handled)
            {
                continue; // don't take it into consideration
            }
            int index = thisChar - 'a';

            // if there is no node in children[index] it means that that letter is not there
            if (temp->children[index] == nullptr)
            {
                // then make a trienode at that children position (like saying that there is actually a letter here)
                // just like in the frequency array when assigning 1 to the index of a letter
                temp->children[index] = new TrieNode();
            }
            // then after this we anyway go to that node if there is a node or not
            temp = temp->children[index];
        }
        temp->isEndOfWord = true;
    }

    // Search for a word in the Trie
    // Input: word to search for (string)
    // Output: boolean indicating if the word exists
    // Purpose: Check if the complete word exists in the Trie
    bool search(string word)
    {
        if (!root)
        {
            return false; // if there is no trie return false
        }

        TrieNode *temp = root;

        for (char thisChar : word)
        {
            if (thisChar > 'A' && thisChar < 'Z') // make uppercase letters lowercase
            {
                thisChar = thisChar - 'A' + 'a';
            }

            if (thisChar < 'a' || thisChar > 'z') // if it is not a letter (notice that uppercase is already handled)
            {
                continue; // don't take it into consideration
            }
            int index = thisChar - 'a';

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
    // Input: prefix to check (string)
    // Output: boolean indicating if any word has this prefix
    // Purpose: Verify if the prefix exists in the Trie (doesn't need to be a complete word)
    bool startsWith(string prefix) {//MENNA
        TrieNode*current=root;
        for(char c:prefix)
        {
            int index= c-' '; //lowercase letters
            if(index<0|| index>=96)
            {
                return false; //character not valid

            }
            if(current->children[index]==nullptr)
            {
                return false;
            }
            current=current->children[index];
        }
        
        return true ; 
    }

    // Get all words that start with the given prefix
    // Input: prefix to complete (string)
    // Output: vector of strings that start with the prefix
    // Purpose: Find all complete words that begin with the given prefix
    void autocomp(TrieNode* root,string currentstring,int currentchar,vector<string>& suggestions)
    {
        if(root==nullptr)
            return;
        currentstring.push_back(currentchar+' ');
        if(root->isEndOfWord)
            suggestions.push_back(currentstring);
        for(int i=0;i<96;i++)
            autocomp(root->children[i],currentstring,i,suggestions);  
        return;
    }

    vector<string> autocomplete(string prefix)
    { // LASHEEN
        vector<string> suggestions;
        TrieNode* currentNode=root;
        int currentsuggest=0;
        string start;
        // TODO: Implement this function
        //yo
        //you u is end of word
        //your r is end of word
        //you're e is end of word
        
        for(int i=0;i<prefix.length();i++)
        {
            if(currentNode->children[prefix[i]-' ']==nullptr)
                return suggestions;
            start.push_back(prefix[i]);
            if(currentNode->isEndOfWord)
                suggestions.push_back(start);
            currentNode=currentNode->children[prefix[i]-' '];
        }
        for(int i=0;i<96;i++)
            autocomp(currentNode->children[i],start,i,suggestions);
        return suggestions;
    }
    void counter(TrieNode* root,int& cnt)
    {
        if(root==nullptr)
            return;
        if(root->isEndOfWord)
            cnt++;
        for(int i=0;i<96;i++)
            counter(root->children[i],cnt);  
        return;
    }
    void wordcount()
    {
        int count=0;
        counter(root,count);
        cout<<"Total words in Trie: "<<count<<endl;
    }
};

// Main function
// Input: none
// Output: integer return code
// Purpose: Program entry point, run tests and interactive demo
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
    // H  H
    // H

    vector<string> caseWords = {"hello", "Hello", "WORLD", "world"};
    for (const string &word : caseWords)
    {
        bool found = trie.search(word);
        cout << "Search '" << word << "': " << (found ? "FOUND" : "NOT FOUND") << endl;
    }
    
    cout << "\n=== ALL TESTS COMPLETED ===" << endl;
    cout << "\n=== BONUS ===" << endl;
    cout << "\n7. Testing words counter:" << endl;
    cout << "============================" << endl;
    trie.wordcount();
    cout << "\n=== BONUS COMPLETED ===" << endl;

    return 0;
}