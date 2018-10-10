//
//  Game.hpp
//  32 project1
//
//  Created by Maeneka Grewal on 1/12/18.
//  Copyright © 2018 Maeneka Grewal. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

//#include <stdio.h>
class City;

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nFlatulans);
    ~Game();
    
    // Mutators
    void play();
    
    //I put this here
    int decodeDirection(char dir);
    
private:
    City* m_city;
};

#endif /* Game_hpp */
