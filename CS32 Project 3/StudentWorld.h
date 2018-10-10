#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "Actor.h"
#include "GameWorld.h"
#include <vector>
#include <string>
using namespace std;

class Actor;
class NachenBlaster;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld();
    StudentWorld(std::string assetDir);
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    void addToVec(Actor* a);
    NachenBlaster* getPlayer();
    void addStar();
    void addShip();
    void anotherShipDown();
    Actor* getOneCollidingAlien(const Actor* a) const;
    NachenBlaster* getCollidingPlayer(const Actor* a) const;
    virtual ~StudentWorld();

private:
    vector<Actor*> actorVec;
    NachenBlaster* player;
    int shipsDestroyed;
    int shipsToDestroy;
};

#endif // STUDENTWORLD_H_
