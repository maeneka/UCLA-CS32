//
//  mazestack.cpp
//  cs32hw2
//
//  Created by Maeneka Grewal on 2/4/18.
//  Copyright © 2018 Maeneka Grewal. All rights reserved.
//

#include <string>
#include <iostream>
#include <stack>
using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
{
    stack <Coord> coordStack;
    coordStack.push(Coord(sr, sc));
    maze[sr].replace(sc, 1, "#");
    
    while (!(coordStack.empty()))
    {
        Coord temp = coordStack.top();
        coordStack.pop();
        if (temp.r() == er && temp.c() == ec)
        {
            return true;
        }
        
        if (temp.c() !=  nCols)
        {
            //checking east
            if ((maze[temp.r()].substr(temp.c()+1, 1)) == ".")
            {
                coordStack.push(Coord(temp.r(), temp.c()+1));
                maze[temp.r()].replace(temp.c()+1, 1, "#");
            }
        }
        
        if (temp.r() != nRows)
        {
            //checking south
            if ((maze[temp.r()+1].substr(temp.c(), 1)) == ".")
            {
                coordStack.push(Coord(temp.r()+1, temp.c()));
                maze[temp.r()+1].replace(temp.c(), 1, "#");
            }
        }
        
        if (temp.c() != 0)
        {
            //checking west
            if ((maze[temp.r()].substr(temp.c()-1, 1)) == ".")
            {
                coordStack.push(Coord(temp.r(), temp.c()-1));
                maze[temp.r()].replace(temp.c()-1, 1, "#");
            }
        }
        
        if (temp.r() != 0)
        {
            //checking north
            if ((maze[temp.r()-1].substr(temp.c(),1) == "."))
            {
                coordStack.push(Coord(temp.r()-1, temp.c()));
                maze[temp.r()-1].replace(temp.c(), 1, "#");
            }
        }
        
        for (int i = 0; i < nRows; i++)
            cout << maze[i] << endl;
        cout << endl;
    }
    return false;
}
 


