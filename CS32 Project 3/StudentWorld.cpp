#include "StudentWorld.h"
#include "GameConstants.h"
#include <vector>
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp
StudentWorld::StudentWorld(string assetDir)
: GameWorld(assetDir)
{
    shipsDestroyed = 0;
    shipsToDestroy = 6 + (4 * getLevel());
}

int StudentWorld::init()
{
    shipsDestroyed = 0; 
    for (int i = 0; i < 30; i++)
    {
        int randX = randInt(0, VIEW_WIDTH);
        int randY = randInt(0, VIEW_HEIGHT);
        double randSize = randInt(5, 50);
        Star* newStar = new Star(IID_STAR, randX, randY, 0, randSize, 3, this);
        newStar->setSize(randSize/100);
        actorVec.push_back(newStar);
    }
    
    player = new NachenBlaster(IID_NACHENBLASTER, 0, 128, 0, 1, 0, this);
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    player->doSomething();
    
    vector<Actor*>::iterator it;
    for (it = actorVec.begin(); it != actorVec.end(); it++)
    {
        (*it)->doSomething();
    }
    
    for (it = actorVec.begin(); it != actorVec.end(); )
    {
        if((*it)->checkLifeStat() == false)
        {
            delete *it;
            it = actorVec.erase(it);
        }
        else
            it++;
    }
    
    int maybeStar = randInt(1, 15);
    if (maybeStar == 1)
    {
        addStar();
    }
    
    addShip();
    
    int displayHealth = ((getPlayer()->getHitpoints())/50) * 100;
    int displayScore = getScore();
    int displayCab = ((getPlayer()->getCabbage())/30) * 100;
    int displayTorp = getPlayer()->getTorps();
    setGameStatText("Lives: " + to_string(getLives()) + " Health " + to_string(displayHealth) + "% Score " + to_string(displayScore) + " Level " + to_string(getLevel()) + " Cabbages " + to_string(displayCab) + "% Torpedoes " + to_string(displayTorp));
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    //decLives();
    //return GWSTATUS_PLAYER_DIED;
    
    if (!(player->checkLifeStat()))
    {
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
    if (shipsDestroyed >= shipsToDestroy)
        return GWSTATUS_FINISHED_LEVEL;
    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::anotherShipDown()
{
    shipsDestroyed+=1;
}
void StudentWorld::addToVec(Actor* a)
{
    actorVec.push_back(a);
}

NachenBlaster* StudentWorld::getPlayer()
{
    return player;
}

void StudentWorld::addStar()
{
    int randY = randInt(0, VIEW_HEIGHT);
    double randSize = randInt(5, 50);
    Star* newStar = new Star(IID_STAR, VIEW_WIDTH-1, randY, 0, 1, 3, this);
    newStar->setSize(randSize/100);
    actorVec.push_back(newStar);
}

void StudentWorld::addShip()
{
    int rem = shipsToDestroy - shipsDestroyed;
    int max = 4 + (.5 * getLevel());
    int curr = 0;
    vector<Actor*>::iterator it;
    for (it = actorVec.begin(); it != actorVec.end(); it++)
    {
        if ((*it)->getID() == IID_SMALLGON || (*it)->getID() == IID_SMOREGON || (*it)->getID() == IID_SMOREGON)
            curr++;
    }
    if (curr < min(max, rem))
    {
        int s1 = 60;
        int s2 = 20 + (getLevel() * 5);
        int s3 = 5 + (getLevel() * 10);
        int s = s1 + s2 + s3;
        int whichShip = randInt(1, s);
        int randY = randInt(0, VIEW_HEIGHT-1);
        if (whichShip <= s1)
        {
            Smallgon* newSmall = new Smallgon(IID_SMALLGON, VIEW_WIDTH-1, randY, 0, 1.5, 1, this);
            newSmall->setSize(1.5);
            actorVec.push_back(newSmall);
        }
        else if (whichShip <= (s1 + s2))
        {
            Smoregon* newSmore = new Smoregon(IID_SMOREGON, VIEW_WIDTH-1, randY, 0, 1.5, 1, this);
            newSmore->setSize(1.5);
            actorVec.push_back(newSmore);
        }
        else
        {
            Snagglegon* newSnag = new Snagglegon(IID_SNAGGLEGON, VIEW_WIDTH-1, randY, 0, 1.5, 1, this);
            newSnag->setSize(1.5);
            newSnag->setHitpoints(10 * (1 + (getLevel() - 1) * .1));
            newSnag->setDirection("downleft");
            actorVec.push_back(newSnag);
        }
    }
        
}

Actor* StudentWorld::getOneCollidingAlien(const Actor* a) const
{
    for (int i = 0; i < actorVec.size(); i++)
    {
        int actID = actorVec[i]->getID();
        if (actID == IID_SMALLGON || actID == IID_SMOREGON || actID == IID_SNAGGLEGON)
        {
            double actX = a->getX();
            double actY = a->getY();
            double actR = a->getRadius();
            
            double objX = actorVec[i]->getX();
            double objY = actorVec[i]->getY();
            double objR = actorVec[i]->getRadius();
            
            double x = actX - objX;
            double y = actY - objY;
            double dist = sqrt(pow(x, 2) + pow(y, 2));
            
            if (dist < (.75 * (actR + objR)))
                return actorVec[i];
        }
    }
    return nullptr;
}

NachenBlaster* StudentWorld::getCollidingPlayer(const Actor* a) const
{
    double actX = a->getX();
    double actY = a->getY();
    double actR = a->getRadius();
            
    double objX = player->getX();
    double objY = player->getY();
    double objR = player->getRadius();
            
    double x = actX - objX;
    double y = actY - objY;
    double dist = sqrt(pow(x, 2) + pow(y, 2));
    
    if (dist < (.75 * (actR + objR)))
        return player;
    
    return nullptr;
}

void StudentWorld::cleanUp()
{
    delete player;
    player = NULL;
    
    vector<Actor*>::iterator it;
    for (it = actorVec.begin(); it != actorVec.end(); it++)
    {
        delete *it;
    }
    actorVec.clear();
}

StudentWorld::~StudentWorld()
{
    this->cleanUp();
}
