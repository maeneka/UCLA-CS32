#include "provided.h"
#include <string>
#include <cctype>
#include <map>
using namespace std;

class TranslatorImpl
{
public:
    TranslatorImpl();
    ~TranslatorImpl();
    bool pushMapping(string ciphertext, string plaintext);
    bool popMapping();
    string getTranslation(const string& ciphertext) const;
private:
    vector<map<char, char>> m_maps;
    int m_numMaps;
    int m_pushed;
    int m_popped;
};

TranslatorImpl::TranslatorImpl()
{
    map<char,char> temp;
    for (int i = 0; i < 26; i++)
    {
        char c = 97 + i;
        temp[c] = '?';
    }
    m_maps.push_back(temp);
    m_numMaps = 1;
    m_pushed = 0;
    m_popped = 0;
}

TranslatorImpl::~TranslatorImpl()
{
    for (int i = 0; i < m_maps.size(); i ++)
    {
        m_maps[i].clear();
    }
    m_maps.clear();
}

bool TranslatorImpl::pushMapping(string ciphertext, string plaintext)
{
    if (ciphertext.length() != plaintext.length())
        return false;
    for (int i = 0; i < ciphertext.length(); i++)
    {
        char c = ciphertext[i];
        char p = plaintext[i];
        if (!isalpha(c))
            return false;
        if (!isalpha(p))
            return false;
        
        map<char, char>::iterator it;
        it = m_maps[m_numMaps-1].find(tolower(c));
        if (it->second != '?' && p != it->second)
            return false;
    }
    
    map<char,char> copy = m_maps[m_numMaps-1];
    for (int i = 0; i <ciphertext.length(); i++)
    {
        char c = ciphertext[i];
        char p = plaintext[i];
        copy[tolower(c)] = tolower(p);
    }
    m_maps.push_back(copy);
    m_numMaps++;
    m_pushed++;
    return true;
}

bool TranslatorImpl::popMapping()
{
    if (m_pushed == m_popped)
        return false;
    
    m_maps.pop_back();
    m_numMaps--;
    m_popped++;
    return true;
}

string TranslatorImpl::getTranslation(const string& ciphertext) const
{
    string trans = "";
    for (int i = 0; i < ciphertext.length(); i++)
    {
        char c = ciphertext[i];
        if (!isalpha(c))
            trans += c;
        else
        {
            map<char,char> temp = m_maps[m_numMaps-1];
            map<char, char>::const_iterator it;
            it = temp.find(tolower(c));
            if (isupper(c))
                trans += toupper(it->second);
            else
                trans += it->second;
        }
    }
    return trans;
}

//******************** Translator functions ************************************

// These functions simply delegate to TranslatorImpl's functions.
// You probably don't want to change any of this code.

Translator::Translator()
{
    m_impl = new TranslatorImpl;
}

Translator::~Translator()
{
    delete m_impl;
}

bool Translator::pushMapping(string ciphertext, string plaintext)
{
    return m_impl->pushMapping(ciphertext, plaintext);
}

bool Translator::popMapping()
{
    return m_impl->popMapping();
}

string Translator::getTranslation(const string& ciphertext) const
{
    return m_impl->getTranslation(ciphertext);
}

