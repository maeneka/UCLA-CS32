#include "Actor.h"
#include "StudentWorld.h"
#include <vector>

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* sw)
    :GraphObject(imageID, startX, startY, dir, size, depth)
{
    typeAct = imageID;
    isAlive = true;
    m_world = sw;
}

bool Actor::checkLifeStat()
{
    return isAlive;
}

StudentWorld* Actor::getWorld()
{
    return m_world;
}

int Actor::getID()
{
    return typeAct;
}

void Actor::die()
{
    isAlive = false;
    //getWorld()->decLives();
}

void Actor::sufferDamage(int x)
{
}

Actor::~Actor()
{
}

Star::Star(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* sw)
    :Actor(imageID, startX, startY, dir, size, depth, sw)
{
}

void Star::doSomething()
{
    int currX = getX();
    int currY = getY();
    moveTo(currX-1,currY);
    
    int newX = getX();
    if (newX < 0)
        die();
}

Star::~Star()
{
}

NachenBlaster::NachenBlaster(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* sw)
    :Actor(imageID, startX, startY, dir, size, depth, sw)
{
    m_hitpoints = 50;
    m_cabbage = 30;
    m_torpedo = 0;
}

void NachenBlaster::setHitpoints(double h)
{
    m_hitpoints = h;
    
}

double NachenBlaster::getHitpoints()
{
    return m_hitpoints;
}

void NachenBlaster::setTorps(double t)
{
    m_torpedo = t;
}

double NachenBlaster::getTorps()
{
    return m_torpedo;
}

double NachenBlaster::getCabbage()
{
    return m_cabbage;
}

void NachenBlaster::sufferDamage(int x)
{
    setHitpoints(getHitpoints() -x);
    if (getHitpoints() <= 0)
        die();
    
    getWorld()->playSound(SOUND_BLAST);
}

void NachenBlaster::doSomething()
{
    if (this->checkLifeStat() == false)
        return;
    
    int ch;
    if (getWorld()->getKey(ch))
    {
        if (ch == KEY_PRESS_LEFT)
        {
            int currX = getX();
            int currY = getY();
            if (currX - 6 >= 0)
                this->moveTo(currX-6, currY);
            }
        if (ch == KEY_PRESS_RIGHT)
        {
            int currX = getX();
            int currY = getY();
            if (currX < VIEW_WIDTH)
                this->moveTo(currX+6, currY);
        }
        if (ch == KEY_PRESS_UP)
        {
            int currX = getX();
            int currY = getY();
            if (currY < VIEW_HEIGHT)
                this->moveTo(currX, currY+6);
        }
        if (ch == KEY_PRESS_DOWN)
        {
            int currX = getX();
            int currY = getY();
            if (currY >= 0)
                this->moveTo(currX, currY-6);
        }
        if (ch == KEY_PRESS_SPACE)
        {
            if (m_cabbage >= 5)
            {
                int nachX = getX();
                int nachY = getY();
                m_cabbage -= 5;
                Cabbage* newCab = new Cabbage(IID_CABBAGE, nachX+12, nachY, 0, 0.5, 1, getWorld());
                newCab->setSize(0.5);
                getWorld()->addToVec(newCab);
                getWorld()->playSound(SOUND_PLAYER_SHOOT);
            }
        }
        if (ch == KEY_PRESS_TAB)
        {
            if (m_torpedo > 0)
            {
                int nachX = getX();
                int nachY = getY();
                m_torpedo -= 1;
                FlatTorpedo* newTorp = new FlatTorpedo(IID_TORPEDO, nachX+12, nachY, 0, 0.5, 1, getWorld(), "nach");
                newTorp->setSize(0.5);
                getWorld()->addToVec(newTorp);
                getWorld()->playSound(SOUND_TORPEDO);
            }
        }
    }
    if (m_cabbage<=29)
        m_cabbage+=1;
}


NachenBlaster::~NachenBlaster()
{
}

Explosion::Explosion(int imageID, double startX, double startY, int dir, double size, int depth,StudentWorld* sw)
    :Actor(imageID, startX, startY, dir, size, depth, sw)
{
    m_ticks = 0;
}

void Explosion::doSomething()
{
    double currSize = getSize();
    setSize(currSize * 1.5);
    
    m_ticks++;
    
    if (m_ticks > 4)
        die();
}

Explosion::~Explosion()
{
}

Smallgon::Smallgon(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* sw)
:Actor(imageID, startX, startY, dir, size, depth, sw)
{
    m_hitpoints = 5*(1+(getWorld()->getLevel()-1)*.1);
    m_flight = 0;
    m_speed = 2.0;
    m_direction = "";
    m_chance = (20/getWorld()->getLevel())+5;
    m_damage = 5;
}

void Smallgon::setSpeed(double s)
{
    m_speed = s;
}

void Smallgon::setDirection(string d)
{
    m_direction = d;
}

void Smallgon::setDamage(int d)
{
    m_damage = d;
}


void Smallgon::setHitpoints(int h)
{
    m_hitpoints = h;
}

void Smallgon::setChance(double c)
{
    m_chance = c;
}

int Smallgon::getDamage()
{
    return m_damage;
}

int Smallgon::getHitpoints()
{
    return m_hitpoints;
}

double Smallgon::getChance()
{
    return m_chance;
}

void Smallgon::doSomething()
{
    if (this->checkLifeStat() == false)
        return;
    if (getX() < 0)
    {
        die();
        return;
    }
    
    if (doCollisions())
        return;
    
    if (getY() >= VIEW_HEIGHT-1)
        m_direction = "downleft";
    else if (getY() <= 0)
        m_direction = "upleft";
    else if (m_flight == 0)
    {
        int fl = randInt(1,3);
        if (fl == 1)
            m_direction = "left";
        if (fl == 2)
            m_direction = "downleft";
        else
            m_direction = "upleft";
        m_flight = randInt(1,32);
    }
    
    if (possiblyFire())
        return;
    
    if (m_direction == "upleft")
    {
        moveTo(getX() - m_speed, getY() + m_speed);
        m_flight--;
    }
    else if (m_direction == "downleft")
    {
        moveTo(getX() - m_speed, getY() - m_speed);
        m_flight--;
    }
    else
    {
        moveTo(getX() - m_speed, getY());
        m_flight--;
    }
    
    doCollisions();
    
}

bool Smallgon::possiblyFire()
{
    bool didItShoot = false;
    int alienX = getX();
    int nachX = getWorld()->getPlayer()->getX();
    if (alienX > nachX)
    {
        int alienY = getY();
        int nachY = getWorld()->getPlayer()->getY();
        if (std::abs(alienY - nachY) <= 4)
        {
            int rand = randInt(1,m_chance);  //1 in ((20/CurrentLevelNumber)+5)
            if (rand == 1)
                didItShoot = shoot();
        }
    }
    return didItShoot;
}

bool Smallgon::shoot()
{
    int alienX = getX();
    int alienY = getY();
    Turnip* newTurn = new Turnip(IID_TURNIP, alienX-12, alienY, 0, 0.5, 1, getWorld());
    newTurn->setSize(0.5);
    getWorld()->addToVec(newTurn);
    getWorld()->playSound(SOUND_ALIEN_SHOOT);
    return true;
}

bool Smallgon::doCollisions()
{
    NachenBlaster* player = getWorld()->getCollidingPlayer(this);
    if (player != nullptr)
    {
        player->sufferDamage(getDamage());
        alienDie();
        return true;
    }
    return false;
}

void Smallgon::setPlan(int p)
{
    m_flight = p;
}

void Smallgon::sufferDamage(int x)
{
    setHitpoints(getHitpoints()-x);
    
    if (getHitpoints() <= 0)
    {
        alienDie();
    }
    else
        getWorld()->playSound(SOUND_BLAST);
}

void Smallgon::alienDie()
{
    getWorld()->increaseScore(250);
    die();
    getWorld()->anotherShipDown();
    getWorld()->playSound(SOUND_DEATH);
    Explosion* newExp = new Explosion(IID_EXPLOSION, getX(), getY(), 0, 1, 0, getWorld());
    getWorld()->addToVec(newExp);
}

Smallgon::~Smallgon()
{
}

Smoregon::Smoregon(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* sw)
:Smallgon(imageID, startX, startY, dir, size, depth, sw)
{
}

bool Smoregon::possiblyFire()
{
    if (Smallgon::possiblyFire())
        return true;
    
    int alienX = getX();
    int nachX = getWorld()->getPlayer()->getX();
    if (alienX > nachX)
    {
        int alienY = getY();
        int nachY = getWorld()->getPlayer()->getY();
        if (alienY > nachY)
        {
            if (alienY - 4 <= nachY)
            {
                int rand = randInt(1,getChance());  //1 in ((20/CurrentLevelNumber)+5)
                if (rand == 1)
                {
                    setDirection("left");
                    setPlan(VIEW_WIDTH);
                    setSpeed(5.0);
                }
            }
        }
        if (alienY < nachY)
        {
            if (alienY + 4 >= nachY)
            {
                int rand = randInt(1,getChance());  //1 in ((20/CurrentLevelNumber)+5)
                if (rand == 1)
                {
                    setDirection("left");
                    setPlan(VIEW_WIDTH);
                    setSpeed(5.0);
                }
            }
        }
    }
    return false;
}

void Smoregon::alienDie()
{
    getWorld()->increaseScore(250);
    die();
    getWorld()->anotherShipDown();
    getWorld()->playSound(SOUND_DEATH);
    Explosion* newExp = new Explosion(IID_EXPLOSION, getX(), getY(), 0, 1, 0, getWorld());
    getWorld()->addToVec(newExp);
    
    int rand1 = randInt(1, 3);
    if (rand1 == 1)
    {
        int rand2 = randInt(1 ,2);
        if (rand2 == 2)
        {
            RepGoodie* newRep = new RepGoodie(IID_REPAIR_GOODIE, getX(), getY(), 0, 0.5, 1, getWorld());
            getWorld()->addToVec(newRep);
        }
        else
        {
            FlatGoodie* newFlGoodie = new FlatGoodie(IID_TORPEDO_GOODIE, getX(), getY(), 0, 0.5, 1, getWorld());
            getWorld()->addToVec(newFlGoodie);
        }
    }
}

Smoregon::~Smoregon()
{
}

Snagglegon::Snagglegon(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* sw)
:Smallgon(imageID, startX, startY, dir, size, depth, sw)
{
    int lvl = getWorld()->getLevel();
    setChance((15/lvl)+10);
}

bool Snagglegon::shoot()
{
    int alienX = getX();
    int alienY = getY();
    FlatTorpedo* newFlTorp = new FlatTorpedo(IID_TORPEDO, alienX-14, alienY, 180, 0.5, 1, getWorld(), "snag");
    newFlTorp->setSize(0.5);
    getWorld()->addToVec(newFlTorp);
    getWorld()->playSound(SOUND_TORPEDO);
    return true;
}

void Snagglegon::alienDie()
{
    getWorld()->increaseScore(1000);
    die();
    getWorld()->anotherShipDown();
    getWorld()->playSound(SOUND_DEATH);
    Explosion* newExp = new Explosion(IID_EXPLOSION, getX(), getY(), 0, 1, 0, getWorld());
    getWorld()->addToVec(newExp);
    
    int rand1 = randInt(1, 6);
    if (rand1 == 1)
    {
        int rand2 = randInt(1 ,2);
        if (rand2 == 2)
        {
            ELGoodie* newEL = new ELGoodie(IID_LIFE_GOODIE, getX(), getY(), 0, 0.5, 1, getWorld());
            getWorld()->addToVec(newEL);
        }
    }
    
}

Snagglegon::~Snagglegon()
{
}

Cabbage::Cabbage(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* sw)
:Actor(imageID, startX, startY, dir, size, depth, sw)
{
    moveAmt = 8;
    rotAmt = 20;
}

void Cabbage::setMoveRot(int m, int r)
{
    moveAmt = m;
    rotAmt = r;
}

void Cabbage::doSomething()
{
    if (checkLifeStat() == false)
        return;
    
    if (checkOnScreen() == false)
    {
        die();
        return;
    }
    
    if (doCollisions())
        return;
    
    moveTo(getX() + moveAmt, getY());
    setDirection(getDirection() + rotAmt);
    
    if (doCollisions())
        return;
}

bool Cabbage::doCollisions()
{
    Actor* alien = getWorld()->getOneCollidingAlien(this);
    if (alien != nullptr)
    {
        alien->sufferDamage(2);
        die();
        return true;
    }
    return false;
}

bool Cabbage::checkOnScreen()
{
    if (getX() >= VIEW_WIDTH)
        return false;
    else
        return true;
}

Cabbage::~Cabbage()
{
}

Turnip::Turnip(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* sw)
:Cabbage(imageID, startX, startY, dir, size, depth, sw)
{
    setMoveRot(-6, 20);
}

bool Turnip::checkOnScreen()
{
    if (getX() < 0)
        return false;
    else
        return true;
}

bool Turnip::doCollisions()
{
    NachenBlaster* player = getWorld()->getCollidingPlayer(this);
    if (player != nullptr)
    {
        player->sufferDamage(2);
        die();
        return true;
    }
    return false;
}

Turnip::~Turnip()
{
}

FlatTorpedo::FlatTorpedo(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* sw, string launcher)
:Cabbage(imageID, startX, startY, dir, size, depth, sw)
{
    firedBy = launcher;
    if (launcher == "nach")
        setMoveRot(8, 0);
    else
        setMoveRot(-8, 0);
}

bool FlatTorpedo::checkOnScreen()
{
    if (getX() < 0 || getX() >= VIEW_WIDTH)
        return false;
    else
        return true;
}

bool FlatTorpedo::doCollisions()
{
    if (firedBy == "nach")
    {
        Actor* alien = getWorld()->getOneCollidingAlien(this);
        if (alien != nullptr)
        {
            alien->sufferDamage(8);
            die();
            return true;
        }
        return false;
    }
    else
    {
        NachenBlaster* player = getWorld()->getCollidingPlayer(this);
        if (player != nullptr)
        {
            player->sufferDamage(8);
            die();
            return true;
        }
        return false;
    }
}

FlatTorpedo::~FlatTorpedo()
{
}

ELGoodie::ELGoodie(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* sw)
:Actor(imageID, startX, startY, dir, size, depth, sw)
{
    m_type = "EL";
}

bool ELGoodie::checkOnScreen()
{
    if ((getX() < 0) || (getY() < 0))
        return false;
    else
        return true;
}

void ELGoodie::setType(string t)
{
    m_type = t;
}

void ELGoodie::doSomething()
{
    if (checkLifeStat() == false)
        return;
    
    if (checkOnScreen() == false)
    {
        die();
        return;
    }
    
    if(doCollisions())
        return;
    
    moveTo(getX() - 0.75, getY() - 0.75);
    
    doCollisions();
    
}

bool ELGoodie::doCollisions()
{
    NachenBlaster* player = getWorld()->getCollidingPlayer(this);
    if (player != nullptr)
    {
        getWorld()->increaseScore(100);
        //getWorld()->incLives();
        if (m_type == "rep")
        {
            int playerpts = player->getHitpoints();
            if (playerpts + 10 >= 50)
                player->setHitpoints(50);
            else
                player->setHitpoints(playerpts+10);
        }
        if (m_type == "flat")
        {
            int playertorps = player->getTorps();
            player->setTorps(playertorps+5);
        }
        die();
        getWorld()->playSound(SOUND_GOODIE);
        return true;
    }
    return false;
}

ELGoodie::~ELGoodie()
{
}

RepGoodie::RepGoodie(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* sw)
:ELGoodie(imageID, startX, startY, dir, size, depth, sw)
{
    setType("rep");
}

RepGoodie::~RepGoodie()
{
}

FlatGoodie::FlatGoodie(int imageID, double startX, double startY, int dir, double size, int depth, StudentWorld* sw)
:ELGoodie(imageID, startX, startY, dir, size, depth, sw)
{
}

FlatGoodie::~FlatGoodie()
{
}


