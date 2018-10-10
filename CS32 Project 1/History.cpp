//
//  History.cpp
//  32 project1
//
//  Created by Maeneka Grewal on 1/15/18.
//  Copyright © 2018 Maeneka Grewal. All rights reserved.
//

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

#include "History.h"
#include "City.h"

History::History(int nRows, int nCols)
{
    m_rows = nRows;
    m_cols = nCols;
    for (int r = 0; r < nRows; r++)
        for (int c = 0; c < m_cols; c++)
            tally[r][c] = 0;
}

bool History::record(int r, int c)
{
    if (r < 1 || r > m_rows || c < 1 || c > m_cols)
        return false;
    tally[r-1][c-1] += 1;
    return true;
    
}

void History::display() const
{
    // Position (row,col) in the city coordinate system is represented in
    // the array element grid[row-1][col-1]
    char grid[MAXROWS][MAXCOLS];
    int r, c;
    string alphabet = ".ABCDEFGHIJKLMNOPQRSTUVWXWYZ";
    // Fill the grid with dots
    for (r = 0; r < m_rows; r++)
    {
        for (c = 0; c < m_cols; c++)
        {
            int a = tally[r][c];
            if (a >= 26)
                grid[r][c] = 'Z';
            else
                grid[r][c] = alphabet[a];
        }
    }
    
    // Draw the grid
    clearScreen();
    for (r = 0; r < m_rows; r++)
    {
        for (c = 0; c < m_cols; c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;

}
