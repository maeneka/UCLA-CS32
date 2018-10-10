#include "provided.h"
#include <string>
#include <vector>
using namespace std;

class TokenizerImpl
{
public:
    TokenizerImpl(string separators);
    vector<string> tokenize(const string& s) const;
private:
    string sep;
};

TokenizerImpl::TokenizerImpl(string separators)
{
    sep = separators;
}

vector<string> TokenizerImpl::tokenize(const string& s) const
{
    vector<string> broken;
    string curr = "";
    for (int i = 0; i < s.length(); i++)
    {
        bool containsSep = false;
        for (int j = 0; j < sep.length(); j++)
        {
            if (s[i] == sep[j])
            {
                if (curr != "")
                    broken.push_back(curr);
                curr = "";
                containsSep = true;
            }
        }
        if (!containsSep)
        {
            curr += s[i];
        }
    }
    return broken;
}

//******************** Tokenizer functions ************************************

// These functions simply delegate to TokenizerImpl's functions.
// You probably don't want to change any of this code.

Tokenizer::Tokenizer(string separators)
{
    m_impl = new TokenizerImpl(separators);
}

Tokenizer::~Tokenizer()
{
    delete m_impl;
}

vector<string> Tokenizer::tokenize(const string& s) const
{
    return m_impl->tokenize(s);
}

