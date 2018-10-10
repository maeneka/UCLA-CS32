//
//  History.hpp
//  32 project1
//
//  Created by Maeneka Grewal on 1/15/18.
//  Copyright © 2018 Maeneka Grewal. All rights reserved.
//

#ifndef History_hpp
#define History_hpp

class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
    
private:
    int m_rows;
    int m_cols;
    int tally[20][30];
};

#endif /* History_hpp */
