//
//  Decrypter.cpp
//  proj4
//
//  Created by Maeneka Grewal on 3/15/18.
//  Copyright © 2018 Maeneka Grewal. All rights reserved.
//
#include <string>
#include "WordList.cpp"
using namespace std;

class Decrypter
{
public:
    Decrypter()
    {
        
    }
    ~Decrypter()
    {
    }
    bool load(std::string filename)
    {
        return false;
    }
    std::vector<std::string> crack(const std::string& ciphertext)
    {
        vector<std::string> s;
        s.push_back("could not complete");
        return s;
    }
private:
    WordList wl;
};
