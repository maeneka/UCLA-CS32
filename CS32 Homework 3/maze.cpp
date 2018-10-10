//
//  maze.cpp
//  cs32hw3
//
//  Created by Maeneka Grewal on 2/14/18.
//  Copyright © 2018 Maeneka Grewal. All rights reserved.
//

#include <string>
#include <iostream>
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
    if (sr == er && sc == ec)
        return true;
    
    maze[sr].replace(sc, 1, "#");
    
    if (sc != nCols)
    {
        //checking east
        if ((maze[sr].substr(sc+1, 1)) == ".")
        {
            if (pathExists(maze, nRows, nCols, sr, sc+1, er, ec))
                return true;
        }
    }
    
    if (sr != nCols)
    {
        //checking south
        if ((maze[sr+1].substr(sc, 1)) == ".")
        {
            if (pathExists(maze, nRows, nCols, sr+1, sc, er, ec))
                return true;
        }
    }
    
    if (sc != 0)
    {
        //checking west
        if ((maze[sr].substr(sc-1, 1)) == ".")
        {
            if (pathExists(maze, nRows, nCols, sr, sc-1, er, ec))
                return true;
        }
    }
    
    if (sr != 0)
    {
        //checking north
        if ((maze[sr-1].substr(sc, 1)) == ".")
        {
            if (pathExists(maze, nRows, nCols, sr-1, sc, er, ec))
                return true;
        }
    }
    
    for (int i = 0; i < nRows; i++)
        cerr << maze[i] << endl;
    cerr << endl;
    
    return false;
}

/*int main()
{
    string maze[10] = {
        "XXXXXXXXXX",
        "X...X..X.X",
        "X..XX....X",
        "X.X.XXXX.X",
        "XXX......X",
        "X...X.XX.X",
        "X.X.X..X.X",
        "X.XXXX.X.X",
        "X..X...X.X",
        "XXXXXXXXXX"
    };
    
    if (pathExists(maze, 10,10, 4,3, 1,8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}*/
