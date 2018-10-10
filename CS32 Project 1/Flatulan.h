//
//  Flatulan.hpp
//  32 project1
//
//  Created by Maeneka Grewal on 1/11/18.
//  Copyright © 2018 Maeneka Grewal. All rights reserved.
//

#ifndef Flatulan_hpp
#define Flatulan_hpp

//#include <stdio.h>
class City;

class Flatulan
{
public:
    // Constructor
    Flatulan(City* cp, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    
    // Mutators
    void move();
    bool possiblyGetConverted();
    
private:
    City* m_city;
    int   m_row;
    int   m_col;
};

#endif /* Flatulan_hpp */
