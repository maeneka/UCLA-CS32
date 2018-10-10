//
//  main.cpp
//  cs32hw3
//
//  Created by Maeneka Grewal on 2/11/18.
//  Copyright © 2018 Maeneka Grewal. All rights reserved.
//

//Your declarations and implementations would go here
class Investment
{
public:
    Investment(string n, int p)
    {
        label = n;
        price = p;
    }
    
    string name() const
    {
        return label;
    }
    
    int purchasePrice() const
    {
        return price;
    }
    
    virtual bool fungible() const = 0;
    
    virtual string description() const = 0;
    
    virtual ~Investment()
    {
    }
    
private:
    string label;
    int price;
};

class Painting: public Investment
{
public:
    Painting(string n, int p)
        :Investment(n, p)
    {
        descrip = "painting";
    }
    
    virtual bool fungible() const
    {
        return false;
    }
    
    virtual string description() const
    {
        return descrip;
    }
    
    virtual ~Painting()
    {
        cout << "Destroying " << name() << ", a " << description() << endl;
    }
    
private:
    string descrip;
};

class Stock: public Investment
{
public:
    Stock(string n, int p, string ticker)
    :Investment(n, p)
    {
        descrip = "stock";
        letters = ticker;
    }
    
    virtual bool fungible() const
    {
        return true;
    }
    
    virtual string description() const
    {
        return descrip + " trading as " + letters;
    }
    
    virtual ~Stock()
    {
        cout << "Destroying " << name() << ", a " << descrip << " holding" << endl;
    }

private:
    string letters;
    string descrip;
};

class House: public Investment
{
public:
    House(string n, int p)
    :Investment(n, p)
    {
        descrip = "house";
    }
    
    virtual bool fungible() const
    {
        return false;
    }
    
    virtual string description() const
    {
        return descrip;
    }
    virtual ~House()
    {
        cout << "Destroying the " << descrip << " " << name() << endl;
    }
    
private:
    string descrip;
};

