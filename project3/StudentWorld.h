#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>
#include "Level.h"
#include <list>

class Actor;
class Penelope;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    virtual ~StudentWorld();
    
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    void clearDeadItems();
    
    void buildLevel(int level, Level::LoadResult& res);
    
    // Add an actor to the world.
    void addActor(Actor* a);
    
    // Record that one more citizen on the current level is gone (exited,
    // died, or turned into a zombie).
    void recordCitizenGone();
    
    // Indicate that the player has finished the level if all citizens
    // are gone.
    //void recordLevelFinishedIfAllCitizensGone();
    
    // For each actor overlapping a, activate a if appropriate.
    void activateOnAppropriateActors(Actor* a);
    
    // Is an agent blocked from moving to the indicated location?
    bool isAgentMovementBlockedAt(double x, double y, Actor* ptr);
    
    // Is creation of a flame blocked at the indicated location?
    bool isFlameBlockedAt(double x, double y, Actor* ptr);
    
    // Is there something at the indicated location that might cause a
    // zombie to vomit (i.e., a human)?
    bool isZombieVomitTriggerAt(double x, double y, Actor* ptr) const;
    
    // Return true if a human is within the smart zombie distance for
    // sensing a human to pursue, otherwise false.  If true, otherX and
    // otherY will be set to the nearest human's location.
    bool locateClosestNearbyVomitTrigger(double x, double y, double& otherX, double& otherY);
    
    // Return true if there is a living zombie or Penelope, otherwise false.
    // If true, otherX, otherY, and distance will be set to the location and
    // distance of the one nearest to (x,y), and isThreat will be set to true
    // if it's a zombie, false if a Penelope.
    bool locateNearestCitizenTrigger(double x, double y, double& otherX, double& otherY, double& distance, bool& isThreat) const;
    
    // Return true if there is a living zombie, false otherwise.  If true,
    // otherX, otherY and distance will be set to the location and distance
    // of the one nearest to (x,y).
    bool locateNearestCitizenThreat(double x, double y, double& otherX, double& otherY, double& distance) const;
    

    int getCitizensLeft() const { return liveCitizens; }
    void playerDied(){ playerAlive = false; }
    void playerNowAlive() { playerAlive = true;}
    bool getPlayerLife() const{ return playerAlive; }
    void finishLevel() {levelFinished = true; }

    Penelope* getPlayer(){ return m_p; }
    
    // Checking overlap
    int euclidian(Actor *a1, Actor *a2);
    int euclidian2(double x1, double y1, double x2, double y2)const ;
    bool doesOverlap(Actor *a1, Actor *a2);
    
    //For stringstream
    void writeToSS();
    
    // For testing
    void levelJumpForTest(int lvl){ levelCt = lvl; }
    /*
    int getDistToP(Actor* a);
    int getDistToZ(Actor* a);
     */
    
private:
    std::list<Actor*> m_actors;
    Penelope* m_p = nullptr;
    int levelCt = 1;
    int liveCitizens = 0; //increment when we init citizens
    int fireDurationP = 0;
    bool levelFinished;
    bool playerAlive = true; 
};


#endif // STUDENTWORLD_H_
