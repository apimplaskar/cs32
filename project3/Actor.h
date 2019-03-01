//
//  newActor.h
//  ZombieDash
//
//  Created by Aditya Pimplaskar on 2/23/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#ifndef newActor_h
#define newActor_h

#include "GraphObject.h"
class StudentWorld;
class Penelope;
class Goodie;

////////////////////////

class Actor: public GraphObject{
public:
    Actor(int imageID, double startX, double startY, Direction dir, int depth, StudentWorld* worldptr):
    GraphObject(imageID, startX, startY, dir, depth, 1.0), m_world(worldptr){
        m_life = true;
    }
    virtual void doSomething() = 0;
    //In subclasses, this will call StudentWorld's activate on appropriate actors with itself as the parameter
    StudentWorld* getWorld() const{ return m_world; }
    virtual ~Actor(){}
    
    virtual void setDead();
    // Does this object block agent movement?
   
    
    // BOOL checkers
    bool isAlive() const{ return m_life; }
    virtual bool blocksMovement() const { return false; }
    // Does this object block flames?
    virtual bool blocksFlame() const {return false;}
    // Does this object trigger landmines only when they're active?
    virtual bool triggersOnlyActiveLandmines() const{ return false; } //Live objects
    // Can this object cause a zombie to vomit?
    virtual bool triggersZombieVomit() const { return false; } //true for Humans
    // Is this object a threat to citizens?
    virtual bool threatensCitizens() const { return false; } //true in Zombie case
    // Does this object trigger citizens to follow it or flee it?
    virtual bool triggersCitizens() const{ return false; } //true for Zombies + Penelope
    
    
    virtual void activateIfAppropriate(Actor* a){}
    // Called in StudentWorld on subclasses to perform specific function (a in this case is the object that IS AFFECTED)
    // If this object uses exits, use the exit.
    
    virtual void useExitIfAppropriate(){}
    // If this object can die by falling into a pit or burning, die.
    
    // If this object can pick up goodies, pick up g
    virtual void pickUpGoodieIfAppropriate(Goodie* g){}
    
    virtual void dieByFallOrBurnIfAppropriate(){} //Agents + Goodies
    
    // If this object can be infected by vomit, get infected.
    virtual void beVomitedOnIfAppropriate(){}
    
   
    
private:
    StudentWorld* m_world;
    bool m_life=true;
};

/////////////////////////

class Wall: public Actor{
public:
    Wall(double startX, double startY, StudentWorld* worldptr):Actor(IID_WALL, startX, startY, 0, 0, worldptr){}
    void doSomething(){}
    bool blocksMovement() const { return true; }
    bool blocksFlame() const{ return true; }
};

/////////////////////////


class ActivatingObject: public Actor{
public:
    ActivatingObject(int imageID, double startX, double startY, Direction dir, int depth, StudentWorld* worldptr):Actor(imageID, startX, startY, dir, depth, worldptr){}
    virtual void doSomething()=0;
    virtual ~ActivatingObject(){}
    //virtual void killPlayer();
    //virtual bool blocksMovement(){ return false; }

};

class Exit: public ActivatingObject{
public:
    Exit(double startX, double startY, StudentWorld* worldptr): ActivatingObject(IID_EXIT, startX, startY, 0, 1, worldptr){}
    void doSomething();
    bool blocksFlame() const{ return true; }
    void activateIfAppropriate(Actor *a);
};


class Pit: public ActivatingObject{
public:
    Pit(double startX, double startY, StudentWorld* worldptr): ActivatingObject(IID_PIT, startX, startY, 0, 1, worldptr){}
    void doSomething();
    void activateIfAppropriate(Actor *a);
};

class Landmine : public ActivatingObject
{
public:
    Landmine(double startX, double startY, StudentWorld* worldptr): ActivatingObject(IID_LANDMINE, startX, startY, 0, 1, worldptr){
        safetyTicks = 30;
        active = false;
    }
    
    virtual void doSomething();
    virtual void activateIfAppropriate(Actor* a);
    virtual void dieByFallOrBurnIfAppropriate();
    
    int getSafetyTicks() const{ return safetyTicks; }
    bool isActive() const{ return active; }
    void setActive() { active = true; }
    
private:
    int safetyTicks;
    bool active;
};


class Goodie: public ActivatingObject{
public:
    Goodie(double startX, double startY, StudentWorld* worldptr, int IID): ActivatingObject(IID, startX, startY, 0, 1, worldptr){}
    virtual void doSomething();
    virtual void pickUp(Penelope* p) = 0;
    void activateIfAppropriate(Actor* a);
    void dieByFallOrBurnIfAppropriate(); //firing at landmiens leads to explosion be careful
    virtual ~Goodie(){}
};

class VaccineGoodie: public Goodie{
public:
    VaccineGoodie(double startX, double startY, StudentWorld* worldptr, int durTilDie):Goodie(startX, startY, worldptr, IID_VACCINE_GOODIE){
        //std::cerr << "dropped vaccine.";
        dieBuffer = durTilDie;
    }
    void doSomething();
    void pickUp(Penelope* p);
    void dieByFallOrBurnIfAppropriate();
private:
    int dieBuffer;
};
    
class LandmineGoodie: public Goodie{
public:
    LandmineGoodie(double startX, double startY, StudentWorld* worldptr):Goodie(startX, startY, worldptr, IID_LANDMINE_GOODIE){}
    void pickUp(Penelope *p);
};
    
class GasCanGoodie: public Goodie{
public:
    GasCanGoodie(double startX, double startY, StudentWorld* worldptr): Goodie(startX, startY, worldptr, IID_GAS_CAN_GOODIE){}
    void pickUp(Penelope *p);
};


class Flame: public ActivatingObject{
public:
    Flame(double startX, double startY, StudentWorld* worldptr, Direction dir): ActivatingObject(IID_FLAME, startX, startY, dir, 0, worldptr){
        duration = 2;
    }
    void doSomething();
    void activateIfAppropriate(Actor* a);
    bool triggersOnlyActiveLandmines() const{ return true; }
private:
    int duration;
    
};


class Vomit: public ActivatingObject{
public:
    Vomit(double startX, double startY, StudentWorld* worldptr): ActivatingObject(IID_VOMIT, startX, startY, 0, 0, worldptr){
        duration = 2;
    }
    void doSomething();
    void activateIfAppropriate(Actor* a);
private:
    int duration;
};
 

//////////////////////
    
class Agent: public Actor{
public:
    Agent(int imageID, double startX, double startY, Direction dir, int depth, StudentWorld* worldptr):Actor(imageID, startX, startY, dir, depth, worldptr){}
    virtual void doSomething() = 0;
    virtual ~Agent(){}
    bool blocksMovement() const { return true; }
    void dieByFallOrBurnIfAppropriate();
    bool blocksFlame() const { return false; }
    bool triggersOnlyActiveLandmines() const{ return true; }
    void swapParalysis(){ paralyzed = !paralyzed; }
    bool getParalysisStatus() { return paralyzed; }
private:
    bool paralyzed = false;
};
    
class Human: public Agent{
public:
    Human(int imageID, double startX, double startY, Direction dir, int depth, StudentWorld* worldptr): Agent(imageID, startX, startY, dir, depth, worldptr){
        poisonCounter = 0;
        poisonStatus = false;
    }
    virtual void doSomething() =0;
    virtual ~Human(){}
    void curePoison(){
        poisonStatus = false;
        poisonCounter = 0;
    }
    void makePoison(){ poisonStatus = true; }
    void setExit(){ canExit = true; }
    bool getExit() const{ return canExit; }
    void beVomitedOnIfAppropriate();
   
    //virtual void useExitIfAppropriate(){}
    
    //BOOL checkers
    bool isPoisoned() const { return poisonStatus; }
    bool triggersZombieVomit() const { return true; }
    bool triggersOnlyActiveLandmines() const{ return true; }
    int getPoisonCt() { return poisonCounter; }
    void addPoison(){ poisonCounter++; }
    bool threatensCitizen() const{ return false; }
    

    
private:
    bool poisonStatus = false;
    bool canExit = false;
    int poisonCounter = 0;
};
    
class Penelope: public Human{
public:
    Penelope(double startX, double startY, StudentWorld* worldptr): Human(IID_PLAYER, startX, startY, 0, 0, worldptr){
        n_vacc = n_flame = n_landmine = 0;
    }
    void doSomething();
    //void fire();
    void addNVacc(){ n_vacc++; }
    void addNFlame() { n_flame +=5; }
    void addNMines(){ n_landmine++; }
    void pickUpGoodieIfAppropriate(Goodie* g);
    void useExitIfAppropriate();
    
    //Checkers
    bool triggersCitizens() const{ return true; }
    int getNVacc() const{ return n_vacc; }
    int getNFlame() const { return n_flame; }
    int getNMines() const { return n_landmine; }
   
    
private:
    int n_vacc;
    int n_flame;
    int n_landmine;
};
    

class Citizen: public Human{
 public:
    Citizen(double startX, double startY, StudentWorld* worldptr): Human(IID_CITIZEN, startX, startY, 0, 0, worldptr){}
    void doSomething();
    void dieByFallOrBurnIfAppropriate();
    void useExitIfAppropriate();
    
private:

    //int dist_p; //distance to Penelope
    //int dist_z; //distance to nearest Zombie
};



class Zombie: public Agent{
 public:
    Zombie(double startX, double startY, StudentWorld* worldptr, Direction dir): Agent(IID_ZOMBIE, startX, startY, dir, 0, worldptr){}
    virtual void doSomething() = 0;
    virtual bool threatensCitizens() const { return true; } //true in Zombie case + Penelope + Projectiles
    // Does this object trigger citizens to follow it or flee it?
    virtual bool triggersCitizens() const{ return true; } //true for Zombies + Penelope
    
};

class DumbZombie: public Zombie{
public:
    DumbZombie(double startX, double startY, StudentWorld* worldptr, Direction dir): Zombie(startX, startY, worldptr, dir){
        dumbDistance = 0;
    }
    void doSomething();
    void dieByFallOrBurnIfAppropriate();
private:
    int dumbDistance;
    Direction dumbDir;
    
    
};
    
class SmartZombie: public Zombie{
 public:
    SmartZombie(double startX, double startY, StudentWorld* worldptr, Direction dir): Zombie(startX, startY, worldptr, dir){
        planDist = 0;
    }
    void doSomething();
    void dieByFallOrBurnIfAppropriate();
private:
    int planDist;
    int planDir; 
};

    



#include <stdio.h>

#endif /* newActor_h */
