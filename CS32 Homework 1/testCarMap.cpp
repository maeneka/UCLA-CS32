//
//  testCarMap.cpp
//  cs32homework1
//
//  Created by Maeneka Grewal on 1/22/18.
//  Copyright © 2018 Maeneka Grewal. All rights reserved.
//

#include "CarMap.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    CarMap m;  // maps strings to doubles
    if (m.fleetSize() == 0)
        cout << "the fleetSize thing is good" << endl;
    m.addCar("GABY");
    m.addCar("MAENEKA");
    m.addCar("HANNAH");
    m.addCar("EMMAK");
    m.addCar("EMMAP");
    m.addCar("CLAUDIA");
    m.addCar("MADDIE");
    m.addGas("GABY", 25.0);
    m.addGas("MAENEKA", 31.4);
    m.addGas("EMMAK", 29.2);
    m.addGas("EMMAP", 17.6);
    m.print();
    if(!m.addGas("DNE", 12.2))
        cout << "addGas is good" << endl;
    if (!m.addCar("MADDIE"))
        cout << "addCar is good" << endl;
    if (m.gas("MAENEKA") == 31.4 && m.gas("HANNAH") == 0)
        cout << "gas is good" << endl;
    if (!m.addGas("HANNAH", -5) && !m.addGas("DNE", 34.2))
        cout << "so far addGas is still good" << endl;
    m.addGas("MADDIE", 13.2);
    m.addGas("HANNAH", 5.4);
    m.print();
    if (!m.useGas("DINGUS", 12.0))
    {
        cout << "so far useGas is good" << endl;
    }
    if (!m.useGas("MADDIE", -2))
        cout << "useGas is still yee" << endl;
    if (!m.useGas("EMMAK", 34.2))
        cout << "useGas is still good" << endl;
    m.useGas("GABY", 12.2);
    m.print();
}

