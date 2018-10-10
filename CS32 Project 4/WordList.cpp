#include "provided.h"
#include "MyHash.h"
#include <string>
#include <vector>
#include <cctype>
#include <functional>
#include <iostream>
#include <fstream>

using namespace std;

class WordListImpl
{
public:
    WordListImpl()
    {
    }
    
    ~WordListImpl()
    {
    }
    
    bool loadWordList(string filename);
    bool contains(string word) const;
    vector<string> findCandidates(string cipherWord, string currTranslation) const;
private:
    MyHash<string, vector<string>> m_hasher;
    string patternize(string& a) const;
    
};

bool WordListImpl::loadWordList(string filename)
{
    m_hasher.reset();
    ifstream infile(filename);    // infile is a name of our choosing
    if ( ! infile )                // Did opening the file fail?
    {
        cerr << "Error: Cannot open data.txt!" << endl;
        return false;
    }
    string s;
    while (getline(infile, s))
    {
        string pattern = patternize(s);
        if (pattern == "INVALID")
            return false;
        const vector<string>* v = m_hasher.find(pattern);
        if (v != nullptr)
        {
            vector<string> z;
            for (vector<string>::const_iterator it = v->begin(); it != v->end(); it++)
            {
                z.push_back(*it);
            }
            z.push_back(s);
            m_hasher.associate(pattern, z);
        }
        else
        {
            vector<string> z;
            z.push_back(s);
            m_hasher.associate(pattern, z);
        }
    }
    return true;
}

string WordListImpl::patternize(string& s) const
{
    string pattern = "";
    string lettersUsed = "";
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int countUnique = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (!(isalpha(s[i])) && s[i] != '\'')
            return "INVALID";
        else
        {
            bool contained = false;
            for (int j = 0; j < lettersUsed.length(); j++)
            {
                if (tolower(s[i]) == tolower(lettersUsed[j]))
                {
                    pattern += pattern[j];
                    lettersUsed += tolower(s[i]);
                    contained = true;
                    break;
                }
            }
            if (!contained)
            {
                pattern += alphabet[countUnique];
                lettersUsed += tolower(s[i]);
                countUnique++;
            }
        }
    }
    s = lettersUsed;
    return pattern;
}


bool WordListImpl::contains(string word) const
{
    string pattern = patternize(word);
    const vector<string>* v = m_hasher.find(pattern);
    if (v != nullptr)
    {
        for (vector<string>::const_iterator it = v->begin(); it != v->end(); it++)
        {
            string x = *it;
            if (x == word)
                return true;
        }
    }
    return false;
}

vector<string> WordListImpl::findCandidates(string cipherWord, string currTranslation) const
{
    string ciphPattern = patternize(cipherWord);
    const vector<string> *v = m_hasher.find(ciphPattern);
    vector<string> cands;
    if (v != nullptr)
    {
        for (vector<string>::const_iterator it = v->begin(); it != v->end(); it++)
        {
            string x = *it;
            bool matches = true;
            for (int i = 0; i < currTranslation.length(); i++)
            {
                if (currTranslation[i] != '?')
                {
                    if (currTranslation[i] != x[i])
                        matches = false;
                }
            }
            if (matches)
                cands.push_back(x);
        }
    }
    return cands;  // This compiles, but may not be correct
}

//***** hash functions for string, int, and char *****

unsigned int hash(const std::string& s)
{
    return std::hash<std::string>()(s);
}

unsigned int hash(const int& i)
{
    return std::hash<int>()(i);
}

unsigned int hash(const char& c)
{
    return std::hash<char>()(c);
}

//******************** WordList functions ************************************

// These functions simply delegate to WordListImpl's functions.
// You probably don't want to change any of this code.

WordList::WordList()
{
    m_impl = new WordListImpl;
}

WordList::~WordList()
{
    delete m_impl;
}

bool WordList::loadWordList(string filename)
{
    return m_impl->loadWordList(filename);
}

bool WordList::contains(string word) const
{
    return m_impl->contains(word);
}

vector<string> WordList::findCandidates(string cipherWord, string currTranslation) const
{
    return m_impl->findCandidates(cipherWord, currTranslation);
}
