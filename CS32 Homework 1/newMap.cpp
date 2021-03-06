//
//  newMap.cpp
//  cs32project1pt2
//
//  Created by Maeneka Grewal on 1/23/18.
//  Copyright © 2018 Maeneka Grewal. All rights reserved.
//

#include "newMap.h"

#include <iostream>
using namespace std;

Map::Map()        // Create an empty map (i.e., one with no key/value pairs)
{
    m_map = new pairs[DEFAULT_MAX_ITEMS];
    m_size = DEFAULT_MAX_ITEMS;
    m_occupied = 0;
}

Map::Map(int n)
{
    m_size = n;
    m_map = new pairs[m_size];
    m_occupied = 0;
}

Map::Map(const Map &src)
{
    m_size = src.m_size;
    m_map = new pairs[m_size];
    m_occupied = src.m_occupied;
    for (int i = 0; i < m_size; i++)
    {
        m_map[i] = src.m_map[i];
    }
}

Map& Map::operator=(const Map &src)
{
    delete []m_map;
    m_size = src.m_size;
    m_map = new pairs[m_size];
    m_occupied = src.m_occupied;
    for (int i = 0; i < m_size; i++)
    {
        m_map[i] = src.m_map[i];
    }
    return (*this);
}

Map::~Map()
{
    delete []m_map;
}

bool Map::empty() const // Return true if the map is empty, otherwise false.
{
    if (m_occupied == 0)
        return true;
    else
        return false;
}

int Map::size() const  // Return the number of key/value pairs in the map.
{
    return m_occupied;
}

bool Map::insert(const KeyType& key, const ValueType& value)
// If key is not equal to any key currently in the map, and if the
// key/value pair can be added to the map, then do so and return true.
// Otherwise, make no change to the map and return false (indicating
// that either the key is already in the map, or the map has a fixed
// capacity and is full).
{
    if (m_occupied == m_size)
        return false;
    for (int i = 0; i < m_occupied; i++)
    {
        if (m_map[i].k == key)
            return false;
    }
    m_map[m_occupied].k = key;
    m_map[m_occupied].v = value;
    m_occupied++;
    return true;
}

bool Map::update(const KeyType& key, const ValueType& value)
// If key is equal to a key currently in the map, then make that key no
// longer map to the value it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// Otherwise, make no change to the map and return false.
{
    for (int i = 0; i < m_occupied; i++)
    {
        if (m_map[i].k == key)
        {
            m_map[i].v = value;
            return true;
        }
    }
    return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
// If key is equal to a key currently in the map, then make that key no
// longer map to the value it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// If key is not equal to any key currently in the map and if the
// key/value pair can be added to the map, then do so and return true.
// Otherwise, make no change to the map and return false (indicating
// that the key is not already in the map and the map has a fixed
// capacity and is full).
{
    for (int i = 0; i < m_occupied; i++)
    {
        if (m_map[i].k == key)
        {
            m_map[i].v = value;
            return true;
        }
    }
    if (m_occupied == m_size)
        return false;
    else
    {
        m_map[m_occupied].k = key;
        m_map[m_occupied].v = value;
        m_occupied++;
        return true;
    }
}

bool Map::erase(const KeyType& key)
// If key is equal to a key currently in the map, remove the key/value
// pair with that key from the map and return true.  Otherwise, make
// no change to the map and return false.
{
    for (int i = 0; i < m_occupied; i++)
    {
        if (m_map[i].k == key)
        {
            if (m_occupied == 1)
            {
                m_occupied = 0;
                return true;
            }
            m_map[i] = m_map[m_occupied-1];
            m_occupied--;
            return true;
        }
    }
    return false;
}

bool Map::contains(const KeyType& key) const
// Return true if key is equal to a key currently in the map, otherwise
// false.
{
    for (int i = 0; i < m_occupied; i++)
    {
        if (m_map[i].k == key)
            return true;
    }
    return false;
}

bool Map::get(const KeyType& key, ValueType& value) const
// If key is equal to a key currently in the map, set value to the
// value in the map that that key maps to, and return true.  Otherwise,
// make no change to the value parameter of this function and return
// false.
{
    for (int i = 0; i < m_occupied; i++)
    {
        if (m_map[i].k == key)
        {
            value = m_map[i].v;
            return true;
        }
    }
    return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
// If 0 <= i < size(), copy into the key and value parameters the
// key and value of one of the key/value pairs in the map and return
// true.  Otherwise, leave the key and value parameters unchanged and
// return false.  (See below for details about this function.)
{
    if (i >= 0 && i < m_occupied)
    {
        key = m_map[i].k;
        value = m_map[i].v;
        return true;
    }
    return false;
}

void Map::swap(Map& other)
// Exchange the contents of this map with the other one.*/
{
    Map temp = other;
    other = *this;
    *this = temp;
}

void Map::dump() const
{
    if (m_occupied == 0)
        cerr << "The array is empty!" << endl;
    for (int i = 0; i < m_occupied; i++)
    {
        KeyType printK;
        ValueType printV;
        get(i, printK, printV);
        cerr << "The key is " << printK << " and the value is " << printV << endl;
    }
}


