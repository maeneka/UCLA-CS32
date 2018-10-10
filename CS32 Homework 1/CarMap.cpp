//
//  CarMap.cpp
//  cs32homework1
//
//  Created by Maeneka Grewal on 1/21/18.
//  Copyright © 2018 Maeneka Grewal. All rights reserved.
//

#include "CarMap.h"
#include <iostream>
using namespace std;

CarMap::CarMap()      // Create an empty car map.
{
}

bool CarMap::addCar(std::string license)
// If a car with the given license plate is not currently in the map,
// and there is room in the map, add an entry for that car recording
// that it has 0 gallons of gas in it, and return true.  Otherwise,
// make no change to the map and return false.
{
    return m_cars.insert(license, 0);
}

double CarMap::gas(std::string license) const
// If a car with the given license plate is in the map, return the
// number of gallons of gas in its tank; otherwise, return -1.
{
    double gallons;
    if (m_cars.get(license, gallons))
        return gallons;
    else
        return -1;
}

bool CarMap::addGas(std::string license, double gallons)
// If no car with the given license plate is in the map or if
// gallons is negative, make no change to the map and return
// false.  Otherwise, increase the number of gallons of gas in the
// indicated car by the gallons parameter and return true.
{
    double currentGal;
    if (m_cars.get(license, currentGal))
    {
        if (gallons < 0)
            return false;
        else
        {
            gallons += currentGal;
            m_cars.update(license, gallons);
            return true;
        }
    }
    return false;
}

bool CarMap::useGas(std::string license, double gallons)
// If no car with the given license plate is in the map or if
// gallons is negative or if gallons > gas(), make no change to the
// map and return false.  Otherwise, decrease the number of gallons
// of gas in the indicated car by the gallons parameter and return
// true.*
{
    double currentGal;
    if (m_cars.get(license, currentGal))
    {
        if (gallons < 0 || gallons > gas(license))
            return false;
        else
        {
            currentGal -= gallons;
            m_cars.update(license, currentGal);
            return true;
        }
    }
    return false;
}

int CarMap::fleetSize() const  // Return the number of cars in the CarMap.
{
    return m_cars.size();
}

void CarMap::print() const
// Write to cout one line for every car in the map.  Each line
// consists of the car's license plate, followed by one space,
// followed by the number of gallons in that car's tank.  Write
// no other text.
{
    for (int i = 0; i < fleetSize(); i++)
    {
        KeyType license;
        ValueType gallons;
        m_cars.get(i, license, gallons);
        cout << license << " " << gallons << endl;
    }
}

