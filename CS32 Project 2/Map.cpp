//
//  Map.cpp
//  cs32project2
//
//  Created by Maeneka Grewal on 1/27/18.
//  Copyright © 2018 Maeneka Grewal. All rights reserved.
//

#include "Map.h"
#include <iostream>
using namespace std;
//#include <cassert>

Map::Map()
// Create an empty map (i.e., one with no key/value pairs).
// Size is set to 0.
{
    m_size = 0;
}

Map::Map(const Map &src)
// Copy constructor. Size is set to the source size, and all the keys/values of
// the source are added into the new map.
{
    m_size = src.m_size;
    for (int i = 0; i < m_size; i++)
    {
        KeyType key;
        ValueType value;
        src.get(i, key, value);
        m_map.addToRear(key, value);
    }
}

Map& Map::operator=(const Map &src)
// Assignment operator. First, the left map is traversed through and nodes
// of the linked list are deleted. Then size is set to source size. Lastly,
// all of the nodes from the sources are added to the left map.
{
    // Deleting nodes in original map
    for (int i = 0; i < m_size; i++)
    {
        KeyType key;
        ValueType val;
        m_map.traverseTo(0,key,val);
        m_map.deleteItem(key);
    }
    // Setting size to source size
    m_size = src.m_size;
    // Getting nodes from source and adding them to the now 'empty' left map
    for (int i = 0; i < m_size; i++)
    {
        KeyType key;
        ValueType value;
        src.get(i, key, value);
        m_map.addToRear(key, value);
    }
    return (*this);
}

Map::~Map()
// Destructor. Automatically calls LinkedList destructor, no code necessary.
{
}

bool Map::empty() const
// Return true if the map is empty, otherwise false.
{
    if (m_size == 0)
        return true;
    else
        return false;
}

int Map::size() const
// Return the number of key/value pairs in the map.
{
    return m_size;
}

bool Map::insert(const KeyType& key, const ValueType& value)
// If key is not equal to any key currently in the map, and if the
// key/value pair can be added to the map, then do so and return true.
// Otherwise, make no change to the map and return false (indicating
// that either the key is already in the map, or the map has a fixed
// capacity and is full).
{
    // If the map doesn't already contain a key with the same name, add
    // it and increment size
    if (!m_map.findItem(key))
    {
        m_map.addToRear(key, value);
        m_size++;
        return true;
    }
    return false;
}

bool Map::update(const KeyType& key, const ValueType& value)
// If key is equal to a key currently in the map, then make that key no
// longer map to the value it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// Otherwise, make no change to the map and return false.
{
    return m_map.changeItem(key, value);
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
    // If map contains item with same key name, update value.
    if (m_map.findItem(key))
    {
        m_map.changeItem(key, value);
        return true;
    }
    // If map doesn't contain it, add and increment size.
    else
    {
        m_map.addToRear(key, value);
        m_size++;
    }
    return true;
}

bool Map::erase(const KeyType& key)
// If key is equal to a key currently in the map, remove the key/value
// pair with that key from the map and return true.  Otherwise, make
// no change to the map and return false.
{
    // If the map contains the key, delete and decrement size.
    if (m_map.findItem(key))
    {
        m_map.deleteItem(key);
        m_size--;
        return true;
    }
    return false;
}

bool Map::contains(const KeyType& key) const
// Return true if key is equal to a key currently in the map, otherwise
// false.
{
    return m_map.findItem(key);
}

bool Map::get(const KeyType& key, ValueType& value) const
// If key is equal to a key currently in the map, set value to the
// value in the map that that key maps to, and return true.  Otherwise,
// make no change to the value parameter of this function and return
// false.
{
    if (m_map.findItem(key))
    {
        m_map.getItem(key, value);
        return true;
    }
    return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
// If 0 <= i < size(), copy into the key and value parameters the
// key and value of one of the key/value pairs in the map and return
// true.  Otherwise, leave the key and value parameters unchanged and
// return false.  (See below for details about this function.)
{
    if (i >= 0 && i < m_size)
    {
        m_map.traverseTo(i, key, value);
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
    if (m_size == 0)
        cerr << "The array is empty!" << endl;
    else
        m_map.printItems();
}

bool combine(const Map &m1, const Map &m2, Map &result)
{
    // Create new map called 'combined' that is replica of m1.
    Map combined(m1);
    // cout << "m1 size: " << m1.size() << ", m2 size: " << m2.size() << endl;
    bool matching = true;
    // cout << "testing by printing a list that should match a: " << endl;
    combined.dump();
    
    // Traverse through the second map
    for (int i = 0; i < m2.size(); i++)
    {
        // Get key & values, and if the 'combined' map contains the same key enter if
        KeyType checkKey;
        ValueType checkVal;
        m2.get(i, checkKey, checkVal);
        if (combined.contains(checkKey))
        {
            // Check to see if the same key name has the same value. If they don't, set
            // matching to false and erase the key. Otherwise it can remain.
            ValueType checkVal2;
            combined.get(checkKey, checkVal2);
            if (checkVal != checkVal2)
            {
                matching = false;
                combined.erase(checkKey);
            }
        }
        // If map2 doesn't contain any keys in combine, add it to combine
        else
            combined.insert(checkKey, checkVal);
    }
    // cout << "Ok it should be combined now: " << endl;
    // combined.dump();
    // Swap result parameter and combined
    result.swap(combined);
    return matching;
}

void subtract(const Map &m1, const Map &m2, Map &result)
{
    // Create new map called 'subtracted' that is replica of m1
    Map subtracted(m1);
    //cout << "m1 size: " << m1.size() << ", m2 size: " << m2.size() << endl;
    //cout << "testing by printing a list that should match a: " << endl;
    subtracted.dump();
    
    // Traverse through subtracted to check keys/values
    for (int i = 0; i < subtracted.size(); i++)
    {
        KeyType checkKey;
        ValueType checkVal;
        // Get key from subtracted, and if it is also in m2 erase it
        subtracted.get(i,checkKey, checkVal);
        if (m2.contains(checkKey))
        {
            subtracted.erase(checkKey);
        }
    }
    //cout << "Ok it should be subtracted now: " << endl;
    // Swap result and subtracted
    // subtracted.dump();
    result.swap(subtracted);
}

