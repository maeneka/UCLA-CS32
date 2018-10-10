//
//  Map.hpp
//  cs32project2
//
//  Created by Maeneka Grewal on 1/27/18.
//  Copyright © 2018 Maeneka Grewal. All rights reserved.
//

#include <string>
#include <iostream>
using namespace std;
#ifndef Map_hpp
#define Map_hpp

using KeyType = std::string;
using ValueType = double;

class Map
{
public:
    
    Map();         // Create an empty map (i.e., one with no key/value pairs)
    
    Map(const Map &src);   //Copy constructor
    
    Map &operator=(const Map &src);     //Assignment operator
    
    ~Map();        // Destruct map
    
    bool empty() const;  // Return true if the map is empty, otherwise false.
    
    int size() const;    // Return the number of key/value pairs in the map.
    
    bool insert(const KeyType& key, const ValueType& value);
    // If key is not equal to any key currently in the map, and if the
    // key/value pair can be added to the map, then do so and return true.
    // Otherwise, make no change to the map and return false (indicating
    // that either the key is already in the map, or the map has a fixed
    // capacity and is full).
    
    bool update(const KeyType& key, const ValueType& value);
    // If key is equal to a key currently in the map, then make that key no
    // longer map to the value it currently maps to, but instead map to
    // the value of the second parameter; return true in this case.
    // Otherwise, make no change to the map and return false.
    
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    // If key is equal to a key currently in the map, then make that key no
    // longer map to the value it currently maps to, but instead map to
    // the value of the second parameter; return true in this case.
    // If key is not equal to any key currently in the map and if the
    // key/value pair can be added to the map, then do so and return true.
    // Otherwise, make no change to the map and return false (indicating
    // that the key is not already in the map and the map has a fixed
    // capacity and is full).
    
    bool erase(const KeyType& key);
    // If key is equal to a key currently in the map, remove the key/value
    // pair with that key from the map and return true.  Otherwise, make
    // no change to the map and return false.
    
    bool contains(const KeyType& key) const;
    // Return true if key is equal to a key currently in the map, otherwise
    // false.
    
    bool get(const KeyType& key, ValueType& value) const;
    // If key is equal to a key currently in the map, set value to the
    // value in the map that that key maps to, and return true.  Otherwise,
    // make no change to the value parameter of this function and return
    // false.
    
    bool get(int i, KeyType& key, ValueType& value) const;
    // If 0 <= i < size(), copy into the key and value parameters the
    // key and value of one of the key/value pairs in the map and return
    // true.  Otherwise, leave the key and value parameters unchanged and
    // return false.  (See below for details about this function.)
    
    void swap(Map& other);
    // Exchange the contents of this map with the other one.
    
    void dump() const;
    // Testing purposes.
    
private:
    
    struct Node
    {
        KeyType k;
        ValueType v;
        Node *next;
        Node *prev;
    };
    
    class LinkedList
    {
    public:
        LinkedList()
        {
            head = nullptr;
            tail = nullptr;
        }
        
        void addToFront(KeyType key, ValueType val)
        {
            Node *p;
            p = new Node;
            p->k = key;
            p->v = val;
            if (head == nullptr)
            {
                p->next = head;
                head = p;
                p->prev = tail;
                tail = p;
            }
            else
            {
                p->next = head;
                head = p;
                p->prev = nullptr;
                Node *n = p->next;
                n->prev = p;
            }
        }
        
        void addToRear(KeyType key, ValueType val)
        {
            if (head == nullptr)
                addToFront(key, val);
            else
            {
                Node *n = new Node;
                n->k = key;
                n->v = val;
                tail->next = n;
                n->next = nullptr;
                tail = n;
            }
        }
        
        void deleteItem(KeyType key)
        {
            if (head == nullptr)
                return;
            if (head->k == key)
            {
                Node *kill = head;
                head = kill->next;
                delete kill;
                if (head == nullptr)
                {
                    tail = nullptr;
                    return;
                }
                else
                {
                    head->prev = nullptr;
                    return;
                }
            }
            Node *p = head;
            while (p != nullptr)
            {
                if (p->next != nullptr && p->next->k == key)
                    break;
                p = p->next;
            }
            if (p != nullptr)
            {
                Node *kill = p->next;
                if (kill->next == nullptr)
                {
                    delete kill;
                    p->next = nullptr;
                    tail = p;
                }
                else
                {
                    Node *n = kill->next;
                    n->prev = p;
                    p->next = n;
                    delete kill;
                }
            }
        }
        
        bool findItem(KeyType key) const
        {
            Node *p = head;
            while (p != nullptr)
            {
                if (p->k == key)
                    return true;
                p = p->next;
            }
            return false;
        }
        
        bool changeItem(KeyType key, ValueType val)
        {
            Node *p = head;
            while (p != nullptr)
            {
                if (p->k == key)
                {
                    p->v = val;
                    return true;
                }
                p = p->next;
            }
            return false;
        }
        
        void getItem(const KeyType &key, ValueType &val) const
        {
            Node *p = head;
            while (p != nullptr)
            {
                if (p->k == key)
                {
                    val = p->v;
                    return;
                }
                p = p->next;
            }
        }
        
        bool traverseTo(int n, KeyType &key, ValueType &val) const
        {
            int x = 0;
            Node *p = head;
            while (p != nullptr)
            {
                if (x == n)
                {
                    key = p->k;
                    val = p->v;
                    return true;
                }
                p = p->next;
                x++;
            }
            return false;
        }
        
        void printItems() const
        {
            Node *p = head;
            while (p != nullptr)
            {
                cerr << "They key is " << p->k << " and the value is " << p->v << endl;
                p = p->next;
            }
        }
        
        ~LinkedList()
        {
            Node *p;
            p = head;
            while (p != nullptr)
            {
                Node *n = p->next;
                delete p;
                p = n;
            }
        }
        
    private:
        Node *head;
        Node *tail;
    };
    
    int m_size;
    LinkedList m_map;
};

bool combine(const Map &m1, const Map &m2, Map &result);
void subtract(const Map &m1, const Map &m2, Map &result);

#endif /* Map_hpp */

