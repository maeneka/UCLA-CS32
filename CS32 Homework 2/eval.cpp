//
//  eval.cpp
//  cs32hw2
//
//  Created by Maeneka Grewal on 2/5/18.
//  Copyright © 2018 Maeneka Grewal. All rights reserved.
//

#include "Map.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

bool checkSyntax(string infix);

bool checkMap(string postfix, const Map& values);

void toPostfix(string infix, string& postfix);

int evaluate(string infix, const Map& values, string& postfix, int& result)
// Evaluates an integer arithmetic expression
//   If infix is a syntactically valid infix integer expression whose
//   only operands are single lower case letters (whether or not they
//   appear in the values map), then postfix is set to the postfix
//   form of the expression; otherwise postfix may or may not be
//   changed, result is unchanged, and the function returns 1.  If
//   infix is syntactically valid but contains at least one lower
//   case letter operand that does not appear in the values map, then
//   result is unchanged and the function returns 2.  If infix is
//   syntactically valid and all its lower case operand letters
//   appear in the values map, then if evaluating the expression
//   (using for each letter in the expression the value in the map
//   that corresponds to it) attempts to divide by zero, then result
//   is unchanged and the function returns 3; otherwise, result is
//   set to the value of the expression and the function returns 0.
{
    if (checkSyntax(infix) == false)
        return 1;
    
    toPostfix(infix, postfix);
    
    if (checkMap(postfix, values) == false)
        return 2;
    
    stack <int> help;
    for (int i = 0; i < postfix.length(); i++)
    {
        char ch = postfix[i];
        if (islower(ch))
        {
            int n;
            values.get(ch,n);
            help.push(n);
        }
        else
        {
            int v2 = help.top();
            help.pop();
            if (help.empty())
                return 1;
            int v1 = help.top();
            help.pop();
            switch (ch)
            {
                case ('+'):
                    help.push(v1+v2);
                    break;
                case ('-'):
                    help.push(v1-v2);
                    break;
                case ('*'):
                    help.push(v1*v2);
                    break;
                case ('/'):
                    if (v2 == 0)
                    {
                        return 3;
                    }
                    else
                    {
                        help.push(v1/v2);
                    }
                    break;
            }
        }
    }
    result = help.top();
    return 0;
}

bool checkSyntax(string infix)
{
    if (infix == "")
        return false;
    int openPcount = 0;
    int closePcount = 0;
    
    for (int i = 0; i < infix.length(); i++)
    {
        char ch = infix[i];
        if (!(islower(ch)) && ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '(' && ch != ')' && ch != ' ')
            return false;
        
        if (islower(ch))
        {
            char prev = '$';
            if (i >= 1)
            {
                int x = i;
                while (x != 0)
                {
                    prev = infix[x-1];
                    if (prev == ' ')
                        x--;
                    else
                        break;
                }
            }
            if (islower(prev))
                return false;
        }
        
        if (ch == '*' || ch == '+' || ch == '/' || ch == '-')
        {
            char prev = '$';
            if (i >= 1)
            {
                int x = i;
                while (x != 0)
                {
                    prev = infix[x-1];
                    if (prev == ' ')
                        x--;
                    else
                        break;
                }
            }
            if (!islower(prev) && prev != ')')
                return false;
        }
        
        if (ch == ')')
        {
            closePcount++;
            char prev = '$';
            if (i >= 1)
            {
                int x = i;
                while (x != 0)
                {
                    prev = infix[x-1];
                    if (prev == ' ')
                        x--;
                    else
                        break;
                }
            }
            if (!islower(prev) && prev != ')')
                return false;
        }
        
        if (ch == '(')
        {
            openPcount++;
            char prev = '$';
            if (i >= 1)
            {
                int x = i;
                while (x != 0)
                {
                    prev = infix[x-1];
                    if (prev == ' ')
                        x--;
                    else
                        break;
                }
            }
            if (prev != '+' && prev != '-' && prev != '*' && prev != '/' && prev != '$' && prev != '(')
                return false;
            
            int x = i;
            bool foundClose = false;
            while (x != infix.length())
            {
                char parenth = infix[x];
                if (parenth == ')')
                {
                    foundClose = true;
                    break;
                }
                else
                    x++;
            }
            if (!foundClose)
                return false;
        }
    }
    if (openPcount != closePcount)
        return false;
    return true;
}

void toPostfix(string infix, string& postfix)
{
    postfix = "";
    stack <char> yeet;
    for (int i = 0; i < infix.length(); i++)
    {
        char ch = infix[i];
        switch (ch)
        {
            case ('a'):
            case ('b'):
            case ('c'):
            case ('d'):
            case ('e'):
            case ('f'):
            case ('g'):
            case ('h'):
            case ('i'):
            case ('j'):
            case ('k'):
            case ('l'):
            case ('m'):
            case ('n'):
            case ('o'):
            case ('p'):
            case ('q'):
            case ('r'):
            case ('s'):
            case ('t'):
            case ('u'):
            case ('v'):
            case ('w'):
            case ('x'):
            case ('y'):
            case ('z'):
                postfix += ch;
                break;
            case ('('):
                yeet.push(ch);
                break;
            case (')'):
                while (yeet.top() != '(')
                {
                    postfix += yeet.top();
                    yeet.pop();
                }
                yeet.pop();
                break;
            case ('+'):
            case ('-'):
            case ('*'):
            case ('/'):
                while (!yeet.empty() && yeet.top() != '(' )
                {
                    if (ch == '+' || ch == '-')
                    {
                        postfix += yeet.top();
                        yeet.pop();
                        continue;
                    }
                    else
                    {
                        if (yeet.top() == '/' || yeet.top() == '*')
                        {
                            postfix += yeet.top();
                            yeet.pop();
                            continue;
                        }
                        else
                            break;
                    }
                }
                yeet.push(ch);
                break;
        }
    }
    
    while (!yeet.empty())
    {
        postfix += yeet.top();
        yeet.pop();
    }
}

bool checkMap(string postfix, const Map& values)
{
    for (int i = 0; i < postfix.length(); i++)
    {
        char ch = postfix[i];
        if (islower(ch))
        {
            int n;
            if (values.get(ch, n) == false)
                return false;
        }
    }
    return true;
}


