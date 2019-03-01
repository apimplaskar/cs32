//
//  newActor.cpp
//  ZombieDash
//
//  Created by Aditya Pimplaskar on 2/23/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#include "Actor.h"
#include "StudentWorld.h"
#include "GameController.h"
#include "GameWorld.h" 
#include "Level.h"
#include <map>

using namespace std;
void Actor::setDead(){ //kills Actor
    m_life = false;
}

void Penelope::doSomething(){
    if(isPoisoned() && getPoisonCt() >= 500)
    {
        setDead(); //Lose a life if poison count exceeds 500
        return;
    }
    if(isPoisoned() && getPoisonCt() < 500){ addPoison(); } //Poison count will continue to iterate
    
    if(Actor::isAlive()){
        int ch;
        if(getWorld()->getKey(ch)){
            switch(ch){
                case KEY_PRESS_DOWN:
                    setDirection(270); //direction change
                    if(getWorld()->isAgentMovementBlockedAt(getX(), getY()-4, this)){ break; } //if actor can't go that way
                    moveTo(getX(), getY()-4); //move
                    break;
                case KEY_PRESS_UP:
                    setDirection(90);
                    if(getWorld()->isAgentMovementBlockedAt(getX(), getY()+4, this)){ break; }
                    moveTo(getX(), getY()+4);
                    break;
                case KEY_PRESS_LEFT:
                    setDirection(180);
                    if(getWorld()->isAgentMovementBlockedAt(getX()-4, getY(), this)){ break; }
                    moveTo(getX()-4, getY());
                    break;
                case KEY_PRESS_RIGHT:
                    setDirection(0);
                    if(getWorld()->isAgentMovementBlockedAt(getX()+4, getY(), this)){ break; }
                    moveTo(getX()+4, getY());
                    break;
                case KEY_PRESS_TAB:
                    if(n_landmine <= 0){ break; } //no landmines to drop
                    n_landmine--; //decrease number of landmines
                    getWorld()->addActor(new Landmine(getX(), getY(), getWorld())); //create new landmine
                    break;
                case KEY_PRESS_ENTER:
                    if(n_vacc <= 0){ break; } //no vaccines to use
                    if(n_vacc >0){ n_vacc--;} //vaccine count goes down no matter if you were poisoned or not
                    if(isPoisoned()){ curePoison(); } //if you were poisoned, you are cured
                    break;
                case KEY_PRESS_SPACE:
                    if(n_flame <= 0){ break; } //no flames to fire
                    n_flame--; //use a flame
                    getWorld()->playSound(SOUND_PLAYER_FIRE);
                    int dir = getDirection(); // direction to fire flame = direction you are facing
                    switch(dir){
                        case 0:
                            for(int i=1; i <= 3; i++){
                                if(getWorld() -> isFlameBlockedAt(getX()+i*SPRITE_WIDTH, getY(), this)){ //can flame go there? No
                                    //cerr << "Flame blocked. "<< endl;
                                    break; }
                                
                                else
                                    getWorld()->addActor(new Flame(getX()+ i*SPRITE_WIDTH, getY(), getWorld(), 0)); //flame can go there so we will create a new one there
                            }
                            break;
                        case 90:
                            for(int i=1; i <= 3; i++){
                                if(getWorld() -> isFlameBlockedAt(getX(), getY()+i*SPRITE_HEIGHT, this)){
                                    //cerr << "Flame blocked. "<< endl;
                                    break; }
                                else
                                    getWorld()->addActor(new Flame(getX(), getY()+i*SPRITE_HEIGHT, getWorld(), 0));
                            }

                            break;
                        case 180:
                            for(int i=1; i <= 3; i++){
                                if(getWorld() -> isFlameBlockedAt(getX()-i*SPRITE_WIDTH, getY(), this)){
                                    //cerr << "Flame blocked. "<< endl;
                                    break; }
                                else
                                    getWorld()->addActor(new Flame(getX()-i*SPRITE_WIDTH, getY(), getWorld(), 0));
                            }
                            break;
                        case 270:
                            for(int i=1; i <= 3; i++){
                                if(getWorld() -> isFlameBlockedAt(getX(), getY()-i*SPRITE_HEIGHT, this)){
                                    //cerr << "Flame blocked. "<< endl;
                                    break; }
                                else
                                    getWorld()->addActor(new Flame(getX(), getY()-i*SPRITE_HEIGHT, getWorld(), 0));
                            }
                            break;
                        default: break;
                    }
            }
        }
    }
}



void Exit::doSomething(){
    getWorld()->activateOnAppropriateActors(this); //activates itself on actors that can use exit
}

void Penelope::useExitIfAppropriate(){
    if((getWorld()->getCitizensLeft())== 0){ //can only leave if no live citizens remain
        setExit();
        getWorld()->finishLevel();
    }
}

void Citizen::useExitIfAppropriate(){ //can always exit
    getWorld()->recordCitizenGone(); //will decrement
    //cerr << "citizens left: " << getWorld()->getCitizensLeft();
    getWorld()->increaseScore(500); // we get points for saving citizen
    setDead(); //that citizen can be cleaned up now
}
    
void Exit::activateIfAppropriate(Actor *a){
    //a is the object that will/will not be exiting
    a->useExitIfAppropriate(); // not called anymore, overwritten
}
    
void Pit::doSomething(){
    getWorld()->activateOnAppropriateActors(this); //kills actor
    //killPlayer();
}

void Pit::activateIfAppropriate(Actor* a){
    //a is what it overlaps with
    a->dieByFallOrBurnIfAppropriate(); //kills anything that steps on it
}

void Goodie::activateIfAppropriate(Actor* a){
    //a is the object picking up the goodie
    a->pickUpGoodieIfAppropriate(this); //only penelope can do this!
}
void Penelope::pickUpGoodieIfAppropriate(Goodie* g){
    g->pickUp(this); //pickUp function is goodie specific
    getWorld()->playSound(SOUND_GOT_GOODIE);
    getWorld()->increaseScore(50); //points!
}

void Goodie::doSomething(){
    getWorld()->activateOnAppropriateActors(this);
}

void VaccineGoodie::doSomething(){
    getWorld()->activateOnAppropriateActors(this);
    if(dieBuffer > 0){ dieBuffer--; }
}

void VaccineGoodie::pickUp(Penelope *p){
    p->addNVacc(); //add a vaccine
    setDead(); //goodie can go now
}

void LandmineGoodie::pickUp(Penelope *p){
    p->addNMines(); //add mines
    setDead();
}

void GasCanGoodie::pickUp(Penelope *p){
    p->addNFlame(); //add flames
    setDead();
 }

void Flame:: doSomething(){
    getWorld()->activateOnAppropriateActors(this); //if it overlaps, it should kill things
    if(duration <= 0){ setDead();} //duration starts at 2 and goes down, if it is 0 the flame has been alive too long
    duration--; //duration decremented
}

void Flame::activateIfAppropriate(Actor *a){
    a->dieByFallOrBurnIfAppropriate(); //burn actor dead
    //a->setDead();
}

void Vomit::doSomething(){
    getWorld()->activateOnAppropriateActors(this); //if it overlaps, poison whatever it can
    if(duration <= 0){ setDead(); } //same concept as flame
    duration--;
}

void Vomit::activateIfAppropriate(Actor *a){
    a->beVomitedOnIfAppropriate(); //only humans can be vomited on
}

void Human::beVomitedOnIfAppropriate(){
    makePoison(); //sets poison status to true
}

void Agent::dieByFallOrBurnIfAppropriate(){
    setDead(); //kills in a general sense
}

//MAKE SEPARATE DIE BY FALL OR BURN IF APPROPRIATE FUNCTIONS:

void DumbZombie::dieByFallOrBurnIfAppropriate(){
    int dropVaccine = randInt(1,10); //dumbZombie may drop a vaccine in which case you make a new one
    //cerr<< dropVaccine << "drop?" << endl;
    if(dropVaccine == 1){ //10% chance
        getWorld()->addActor(new VaccineGoodie(getX(), getY(), getWorld(),3));
    }
   
    setDead(); //zombie dies
    getWorld()->playSound(SOUND_ZOMBIE_DIE);
    getWorld()->increaseScore(1000); //points!
}

void SmartZombie::dieByFallOrBurnIfAppropriate(){
    setDead(); //zombie dies
    getWorld()->playSound(SOUND_ZOMBIE_DIE);
    getWorld()->increaseScore(2000); //points!
}
    

void Goodie::dieByFallOrBurnIfAppropriate(){
    setDead(); //goodie inactivated and gone
}

void VaccineGoodie::dieByFallOrBurnIfAppropriate(){
    if(dieBuffer == 0){ setDead(); }
}

void Landmine::doSomething(){
    if(isActive()){ getWorld() -> activateOnAppropriateActors(this); }
    if(safetyTicks > 0 && !isActive()){ //30 safety ticks before it blows up on overlap
        safetyTicks--; //nothing happens yet
        return;
    }
    else{
        setActive(); //safety ticks run out so it is active now
        getWorld() -> activateOnAppropriateActors(this); //if it overlaps
    }
}

void Landmine::activateIfAppropriate(Actor *a){
    if (!a->triggersOnlyActiveLandmines()) { return;}
    this->setDead(); //landmine gone
    getWorld()->playSound(SOUND_LANDMINE_EXPLODE);
    //getWorld()->addActor(new Flame(getX(), getY(), getWorld(),0));
    //Fill in flames in surrounding spots.
    for(int i = -1; i <=1; i++){
        for(int j = -1; j <=1; j++){
             getWorld()->addActor(new Flame(getX()+i*SPRITE_WIDTH, getY()+j*SPRITE_HEIGHT, getWorld(),90));
        }
    }
    
    getWorld()->addActor(new Pit(getX(), getY(), getWorld())); //leave a pit where it used to be
    
}

void Landmine::dieByFallOrBurnIfAppropriate(){
    setActive(); //automatically activates the landmine, despite tick counter
    getWorld()->activateOnAppropriateActors(this);
}

void Citizen::doSomething(){
    
    if(!isAlive()){ return; } //make sure citizen is alive
    if(getParalysisStatus()){ //The dead turn
        swapParalysis();
        return;
    }
    //If poisoned, either dies or poison count increments.
    if(isPoisoned() && getPoisonCt() >= 500)
    {
        setDead();
        getWorld()->recordCitizenGone();
        getWorld() -> increaseScore(-1000);
        
        //If died due to poison, they become a zombie
        //70% chance dumb so that corresponds to numbers 4-10
        //30% chance smart so that is number 1-3
        int zType = randInt(1,10);
        if(zType <= 3){
        getWorld()->addActor(new SmartZombie(getX(), getY(), getWorld(),getDirection()));
        }
        else{
            getWorld()->addActor(new DumbZombie(getX(), getY(), getWorld(),getDirection()));
        }
        return;
    }
    
    if(isPoisoned() && getPoisonCt() < 500){
        //cerr << "is poisoned. count = " << getPoisonCt()<< endl;
        addPoison(); }
    
    //Find out closest item and how far away it is
    double o_x, o_y, dist;
    bool threat;
    bool trigger = getWorld()->locateNearestCitizenTrigger(getX(), getY(), o_x, o_y, dist, threat);
    //cerr << "dist: " << dist << "threat: " << threat << endl;
    
    
    if((!threat) && dist < 6400){
        //cerr << "towards penelope" << endl;
        //If the closest trigger object is Penelope
    //if(getWorld()->getDistToP(this) < 6400) {
        //cout << "Player nearby at " << getWorld()->getDistToP(this) << endl;
        
        //If Penelope and the citizen are at same X value, move in Y direction towards Penelope
        if(getX() == getWorld()->getPlayer()->getX()){
            
            if(getY() < getWorld()->getPlayer()->getY()){
               
                if(!(getWorld()->isAgentMovementBlockedAt(getX(), getY()+2, this))){
                    setDirection(90);
                    moveTo(getX(), getY()+2);
                }
                
            }
            else{
               
                if(!(getWorld()->isAgentMovementBlockedAt(getX(), getY()-2, this))){
                    setDirection(270);
                    moveTo(getX(), getY()-2);
                }
            }
        }
        //If Penelope and citizen have same Y value, move in X direction towards Penelope
        else if(getY() == getWorld()->getPlayer()->getY()){
            if(getX() < getWorld()->getPlayer()->getX()){
                
                if(!getWorld()->isAgentMovementBlockedAt(getX()+2, getY(), this)){
                    setDirection(0);
                    moveTo(getX()+2, getY());
                }
            }
            else{
                if(!getWorld()->isAgentMovementBlockedAt(getX()-2, getY(), this)){
                    setDirection(180);
                    moveTo(getX()-2, getY());
                }
            }
        }
        else{
           //Not in the same X or Y, randomly chooses an X or Y direction to go towards Penelope
            //Must check motion before moving
            int randomMove = randInt(1,2);
            if (randomMove == 1){ //random decision as to whether to move in X or in Y
                if(getWorld()->getPlayer()->getX() > getX()){
                    if(!getWorld()->isAgentMovementBlockedAt(getX()+2, getY(), this)){
                        setDirection(0);
                        moveTo(getX()+2, getY());
                    }
                }
                else{
                   
                    if(!getWorld()->isAgentMovementBlockedAt(getX()-2, getY(), this)){
                         setDirection(180);
                        moveTo(getX()-2, getY());
                    }
                }
            }
            else{
                if(getWorld()->getPlayer()->getY() > getY()){
                    if(!(getWorld()->isAgentMovementBlockedAt(getX(), getY()+2, this))){
                        setDirection(90);
                        moveTo(getX(), getY()+2);
                    }
                }
                else{
                    if(!(getWorld()->isAgentMovementBlockedAt(getX(), getY()-2, this))){
                        setDirection(270);
                        moveTo(getX(), getY()-2);
                    }
                }
            }
        }
    }
    else if(threat && dist < 6400){
        //cerr << "away from threat" << endl;
        //Closest trigger object is zombie.
        double n_zombie_x, n_zombie_y, n_zombie_dist;
        getWorld()->locateNearestCitizenThreat(getX(), getY(), n_zombie_x, n_zombie_y, n_zombie_dist);
        //We know that this returns true because of the else if condition
        
        //Find direction that citizen should move to maximize distance from zombie
        double dist_up, dist_down, dist_right, dist_left;
        getWorld()->locateNearestCitizenThreat(getX()+2, getY(), n_zombie_x, n_zombie_y, dist_right); //check R
        getWorld()->locateNearestCitizenThreat(getX()-2, getY(), n_zombie_x, n_zombie_y, dist_left); //check L
        getWorld()->locateNearestCitizenThreat(getX(), getY()+2, n_zombie_x, n_zombie_y, dist_up); //check U
        getWorld()->locateNearestCitizenThreat(getX(), getY()-2, n_zombie_x, n_zombie_y, dist_down); //check D
        
        //Find the minimum distance and go there. If not, go to the next one.
        map<double, int> distVDir;
        distVDir[dist_right] = 0;
        distVDir[dist_left] = 180;
        distVDir[dist_up] = 90;
        distVDir[dist_down] = 270;
        //Map will store the distances in ascending order so now we just look from the back of the map.
        //Scan forward and if we move, then we are done.
        
        map<double, int>::iterator map_it = distVDir.end();
        map_it--;
        bool madeMoveFromZombie = false;
        do{
            int directionToScan = (*map_it).second;
            switch(directionToScan){
                case 0: //moves R
                    if(!(getWorld()->isAgentMovementBlockedAt(getX()+2, getY(), this))){
                        setDirection(0);
                        moveTo(getX()+2, getY());
                        madeMoveFromZombie = true;
                    }
                    break;
                case 90:
                    if(!(getWorld()->isAgentMovementBlockedAt(getX(), getY()+2, this))){
                        setDirection(90);
                        moveTo(getX(), getY()+2);
                        madeMoveFromZombie = true;
                    }
                    break;
                case 180:
                    if(!(getWorld()->isAgentMovementBlockedAt(getX()-2, getY(), this))){
                        setDirection(180);
                        moveTo(getX()-2, getY());
                        madeMoveFromZombie = true;
                    }
                    break;
                case 270:
                    if(!(getWorld()->isAgentMovementBlockedAt(getX(), getY()-2, this))){
                        setDirection(270);
                        moveTo(getX(), getY()-2);
                        madeMoveFromZombie = true;
                    }
                    break;
                default: break;
            }
            if(madeMoveFromZombie){ break;}
            map_it--;
        }while(map_it != distVDir.begin());
        
        //Check if motion is blocked
        //If not move
        
    }
    swapParalysis(); //next tick it will be paralyzed
}


void Citizen::dieByFallOrBurnIfAppropriate(){ //kill citizen
    //cerr << "citizen burning. "<< endl;
    getWorld()->recordCitizenGone(); //decrement live citizens
    setDead();
    getWorld()->playSound(SOUND_CITIZEN_DIE);
    //cerr << "citizens left: " << getWorld()->getCitizensLeft();
    getWorld()->increaseScore(-1000); //failed to save citizen, lose points
}

void DumbZombie::doSomething(){
    if(!isAlive()){ return; }
    if(getParalysisStatus()){ //The dead turn
        swapParalysis();
        return;
    }
    
    int dirFacing = getDirection();
    int toShoot; //if toShoot == 1, we will shoot. if not no vomit shot
    bool justShot = false;
    switch(dirFacing){
        case 0: //Check right
            if(getWorld()->isZombieVomitTriggerAt(getX()+SPRITE_WIDTH, getY(), this)){ //if there is something to vomit on
                toShoot = randInt(1,3); // 1 in 3 chance it vomits
                if(toShoot == 1){
                    getWorld()->playSound(SOUND_ZOMBIE_VOMIT);
                    getWorld()->addActor(new Vomit(getX()+SPRITE_WIDTH, getY(), getWorld()));
                    justShot = true;
                }
                //fire vomit there
            }
            break;
        case 90: //Check up
            if(getWorld()->isZombieVomitTriggerAt(getX(), getY()+SPRITE_HEIGHT, this)){
                toShoot = randInt(1,3);
                if(toShoot == 1){
                    getWorld()->playSound(SOUND_ZOMBIE_VOMIT);
                    getWorld()->addActor(new Vomit(getX(), getY()+SPRITE_WIDTH, getWorld()));
                    justShot = true;
                }
                //fire vomit there
            }
            break;
        case 180: //Check left
            if(getWorld()->isZombieVomitTriggerAt(getX()-SPRITE_WIDTH, getY(), this)){
                toShoot = randInt(1,3);
                if(toShoot == 1){
                    getWorld()->playSound(SOUND_ZOMBIE_VOMIT);
                    getWorld()->addActor(new Vomit(getX()-SPRITE_WIDTH, getY(), getWorld()));
                    justShot = true;
                }
                //fire vomit there
            }
            break;
        case 270: //Check down
            if(getWorld()->isZombieVomitTriggerAt(getX(), getY()-SPRITE_HEIGHT, this)){
                toShoot = randInt(1,3);
                if(toShoot == 1){
                    getWorld()->playSound(SOUND_ZOMBIE_VOMIT);
                    getWorld()->addActor(new Vomit(getX(), getY()-SPRITE_WIDTH, getWorld()));
                    justShot = true;
                }
                //fire vomit there
            }
            break;
        default:
            break;
    }
    if (justShot){ return; } //if it shot, thats all the zombie does this tick
    
    if(dumbDistance == 0){ // set a new random direction and distance to travel
        dumbDistance = randInt(3,10);
        dumbDir = randInt(1,4);
        switch(dumbDir){
            case 1: dumbDir = 0;
                break;
            case 2: dumbDir = 90;
                break;
            case 3: dumbDir = 180;
                break;
            case 4: dumbDir = 270;
                break;
            default:
                break;
        }
    }
    
    switch(dumbDir){ //move according to movement plan
        case 0:
            if(getWorld()->isAgentMovementBlockedAt(getX()+1, getY(), this)){ //have to reset our plan again
                dumbDistance = 0;
            }
            else{
                setDirection(0); //can move in this direction according to plan, REPEAT THESE STEPS for all cases
                moveTo(getX()+1, getY());
                dumbDistance--;
            }
            break;
        case 90:
            if(getWorld()->isAgentMovementBlockedAt(getX(), getY()+1, this)){
                dumbDistance = 0;
            }
            else{
                setDirection(90);
                moveTo(getX(), getY()+1);
                dumbDistance--;
            }
            break;
        case 180:
            if(getWorld()->isAgentMovementBlockedAt(getX()-1, getY(), this)){
                dumbDistance = 0;
            }
            else{
                setDirection(180);
                moveTo(getX()-1, getY());
                dumbDistance--;
            }
            break;
        case 270:
            if(getWorld()->isAgentMovementBlockedAt(getX(), getY()-1, this)){
                dumbDistance = 0;
            }
            else{
                setDirection(280);
                moveTo(getX(), getY()-1);
                dumbDistance--;
            }
            break;
    }
    
    swapParalysis(); //if we were not paralyzed last tick, be paralyzed this tick
}

void SmartZombie::doSomething(){
    if(!isAlive()){ return; }
    if(getParalysisStatus()){ //The dead turn
        swapParalysis();
        return;
    }
    int dirFacing = getDirection();
    int toShoot = randInt(1,3); //if toShoot == 1, we will shoot. if not no vomit shot
    bool justShot = false;
    switch(dirFacing){
        case 0: //Check right
            if(getWorld()->isZombieVomitTriggerAt(getX()+SPRITE_WIDTH, getY(), this)){ //is there something to vomit on?
                if(toShoot == 1){
                    getWorld()->playSound(SOUND_ZOMBIE_VOMIT);
                    getWorld()->addActor(new Vomit(getX()+SPRITE_WIDTH, getY(), getWorld()));
                    justShot = true;
                }
                //fire vomit there
            }
            break;
        case 90: //Check up
            if(getWorld()->isZombieVomitTriggerAt(getX(), getY()+SPRITE_HEIGHT, this)){
                if(toShoot == 1){
                    getWorld()->playSound(SOUND_ZOMBIE_VOMIT);
                    getWorld()->addActor(new Vomit(getX(), getY()+SPRITE_HEIGHT, getWorld()));
                    justShot = true;
                }
                //fire vomit there
            }
            break;
        case 180: //Check left
            if(getWorld()->isZombieVomitTriggerAt(getX()-SPRITE_WIDTH, getY(), this)){
                if(toShoot == 1){
                    getWorld()->playSound(SOUND_ZOMBIE_VOMIT);
                    getWorld()->addActor(new Vomit(getX()-SPRITE_WIDTH, getY(), getWorld()));
                    justShot = true;
                }
                //fire vomit there
            }
            break;
        case 270: //Check down
            if(getWorld()->isZombieVomitTriggerAt(getX(), getY()-SPRITE_HEIGHT, this)){
                if(toShoot == 1){
                    getWorld()->playSound(SOUND_ZOMBIE_VOMIT);
                    getWorld()->addActor(new Vomit(getX(), getY()-SPRITE_HEIGHT, getWorld()));
                    justShot = true;
                }
                //fire vomit there
            }
            break;
        default:
            break;
    }
    if (justShot){ return; } //if the zombie shoots, that is all that the zombie does this tick
    
    if(planDist == 0){ //if our plan distance runs out, we have to come up with a new plan
        planDist = randInt(3,10); //new plan distance
        
        double v_trig_x, v_trig_y;
        bool loc_trig = getWorld()->locateClosestNearbyVomitTrigger(getX(), getY(), v_trig_x, v_trig_y);
        //if true: locates nearest human
        //if false: there is no vomit trigger nearby (this should never be the case when penelope is alive)
        //in turn this should never be false, but we will check for it nonetheless.
        
        if(loc_trig){
            //cerr << "loc_trg = " << v_trig_x << " " << v_trig_y << endl;
            if(getWorld()->euclidian2(getX(), getY(), v_trig_x, v_trig_y) > 6400){ //over 80 pixels away
                planDir = randInt(1,4); // direction chosen randomly
                switch(planDir){
                    case 1: planDir = 0;
                        break;
                    case 2: planDir = 90;
                        break;
                    case 3: planDir = 180;
                        break;
                    case 4: planDir = 270;
                        break;
                    default:
                        break;
                }
            }
            else{
                //we want to move closer to v_trig_x and v_trig_y
                if(getX() == v_trig_x){ // same x value, want to move in the y direction of the trigger
                    if(getY() < v_trig_y){ planDir = 90; }
                    else{ planDir = 270;}
                }
                else if(getY() == v_trig_y){
                    if (getX() < v_trig_x){ planDir = 0; }
                    else{ planDir = 180; }
                }
                else{
                    //Not in the same X or Y, randomly chooses an X or Y direction to go towards v_trig_x, v_trig_y
                    //Must check motion before moving
                    int randomMove = randInt(1,2); //do we move in X or in Y
                    if (randomMove == 1){
                        if(getX()< v_trig_x){ planDir = 0;}
                        else{ planDir = 180;}
                    }
                    else{
                        if(getY() < v_trig_y){ planDir =90;}
                        else{ planDir = 270; }
                    }
                }
            }
        }
        //cerr << "Smart zombie will move " << planDist << " steps in the " << planDir << " direction." << endl;
    }
        //Now movement. Must check if accessible before moving.
        switch(planDir){ //move according to movement plan
            case 0:
                if(getWorld()->isAgentMovementBlockedAt(getX()+1, getY(), this)){
                    planDist = 0;
                }
                else{
                    setDirection(0);
                    moveTo(getX()+1, getY());
                    planDist--;
                }
                break;
            case 90:
                if(getWorld()->isAgentMovementBlockedAt(getX(), getY()+1, this)){
                    planDist = 0;
                }
                else{
                    setDirection(90);
                    moveTo(getX(), getY()+1);
                    planDist--;
                }
                break;
            case 180:
                if(getWorld()->isAgentMovementBlockedAt(getX()-1, getY(), this)){
                    planDist = 0;
                }
                else{
                    setDirection(180);
                    moveTo(getX()-1, getY());
                    planDist--;
                }
                break;
            case 270:
                if(getWorld()->isAgentMovementBlockedAt(getX(), getY()-1, this)){
                    planDist = 0;
                }
                else{
                    setDirection(280);
                    moveTo(getX(), getY()-1);
                    planDist--;
                }
                break;
        }
    
    swapParalysis(); //paralyzed next ticks
}
