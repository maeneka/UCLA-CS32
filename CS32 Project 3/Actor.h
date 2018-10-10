#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"
#include <string>
using namespace std;

class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor: public GraphObject
{
public:
    Actor(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* sw);
    virtual void doSomething() = 0;
    bool checkLifeStat();
    virtual void sufferDamage(int x);
    StudentWorld* getWorld();
    int getID();
    void die();
    virtual ~Actor();
private:
    int typeAct;
    bool isAlive;
    StudentWorld* m_world;
};

class Star: public Actor
{
public:
    Star(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* sw);
    virtual void doSomething();
    virtual ~Star();
};

class NachenBlaster: public Actor
{
public:
    NachenBlaster(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* sw);
    virtual void doSomething();
    void setHitpoints(double h);
    double getHitpoints();
    double getTorps();
    double getCabbage();
    void setTorps(double t);
    virtual void sufferDamage(int x);
    virtual ~NachenBlaster();
private:
    double m_hitpoints;
    double m_cabbage;
    double m_torpedo;
};

class Explosion: public Actor
{
public:
    Explosion(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* sw);
    void doSomething();
    virtual ~Explosion();
private:
    int m_ticks;
};

class Smallgon: public Actor
{
public:
    Smallgon(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* sw);
    virtual void doSomething();
    void setSpeed(double s);
    void setHitpoints(int h);
    void setPlan(int p);
    void setChance(double c);
    void setDirection(string d);
    void setDamage(int d);
    double getChance();
    int getDamage();
    int getHitpoints();
    void sufferDamage(int x);
    virtual void alienDie();
    virtual bool doCollisions();
    virtual bool possiblyFire();
    virtual bool shoot();
    virtual ~Smallgon();
private:
    int m_hitpoints;
    int m_flight;
    double m_speed;
    string m_direction;
    double m_chance;
    int m_damage;
    
};

class Smoregon: public Smallgon
{
public:
    Smoregon(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* sw);
    virtual bool possiblyFire();
    virtual void alienDie();
    virtual ~Smoregon();
};

class Snagglegon: public Smallgon
{
public:
    Snagglegon(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* sw);
    virtual bool shoot();
    virtual void alienDie();
    virtual ~Snagglegon();
};

class Cabbage: public Actor
{
public:
    Cabbage(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* sw);
    void doSomething();
    virtual bool checkOnScreen();
    virtual bool doCollisions();
    void setMoveRot(int m, int r);
    virtual ~Cabbage();
private:
    int moveAmt;
    int rotAmt;
};

class Turnip: public Cabbage
{
public:
    Turnip(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* sw);
    bool checkOnScreen();
    bool doCollisions();
    virtual ~Turnip();
};

class FlatTorpedo: public Cabbage
{
public:
    FlatTorpedo(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* sw, string launcher);
    bool checkOnScreen();
    bool doCollisions();
    virtual ~FlatTorpedo();
private:
    string firedBy;
};

class ELGoodie: public Actor
{
public:
    ELGoodie(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* sw);
    bool checkOnScreen();
    void setType(string t);
    bool doCollisions();
    virtual void doSomething();
    virtual ~ELGoodie();
private:
    string m_type;
};

class RepGoodie: public ELGoodie
{
public:
    RepGoodie(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* sw);
    virtual ~RepGoodie();
};

class FlatGoodie: public ELGoodie
{
public:
    FlatGoodie(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* sw);
    virtual ~FlatGoodie();
};

#endif // ACTOR_H_
