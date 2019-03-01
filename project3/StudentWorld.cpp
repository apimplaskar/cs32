#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <list>
#include <cmath>
#include <iostream> // defines the overloads of the << operator
#include <sstream>  // defines the type std::ostringstream
#include <iomanip>
#include <climits>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
}

StudentWorld::~StudentWorld(){
    cleanUp();
}

int StudentWorld::init()
{
    
    //levelJumpForTest(3);
    playerNowAlive();
    Level::LoadResult res;
    buildLevel(levelCt, res);
    if(res == Level::load_fail_file_not_found) { return GWSTATUS_PLAYER_WON; }
    else if(res == Level::load_fail_bad_format) { return GWSTATUS_LEVEL_ERROR; }
    if (levelCt > 99){ return GWSTATUS_PLAYER_WON; }
    levelFinished = false;
    //cerr << "citizens left: " << getCitizensLeft() << endl;
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    clearDeadItems();
    if (!m_p->isAlive()){
        decLives();
        liveCitizens = 0;
        playSound(SOUND_PLAYER_DIE);
        return GWSTATUS_PLAYER_DIED;
    }

    writeToSS();
    m_p->doSomething();
    list<Actor*>::iterator it = m_actors.begin();
    while(it != m_actors.end()){
        (*it)->doSomething();
        it++;
    }
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    
    if(levelFinished == true){
        levelCt++;
        playSound(SOUND_LEVEL_FINISHED);
        //cerr<< "Finish" << endl;
        return GWSTATUS_FINISHED_LEVEL;
    }
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    if (m_p == nullptr){ return; }
    delete m_p; //delete player
    m_p = nullptr; //flag
    list<Actor*>::iterator it = m_actors.begin(); //Loop over actors to delete
    while(it != m_actors.end()){
        delete *it;
        it = m_actors.erase(it);
    }
}

void StudentWorld::clearDeadItems(){ //loop over the container and delete any memory allocated to objects that have died in this tick
    std::list<Actor*>::iterator it = m_actors.begin();
    while(it != m_actors.end()){
        if(!((*it)->isAlive())){
            delete (*it);
            it = m_actors.erase(it);
        }
        it++;
    }
}
void StudentWorld::addActor(Actor* a){
    m_actors.push_back(a);
}

void StudentWorld::recordCitizenGone(){
    if(liveCitizens >= 1){liveCitizens--;} //called if citizen dies or exits
}

/*
void StudentWorld::recordLevelFinishedIfAllCitizensGone(){
    if(liveCitizens == 0){ levelFinished = true; }
}
*/





bool StudentWorld::isAgentMovementBlockedAt(double x, double y, Actor* ptr){
    //corners of bounding box
    int x_hi = x+SPRITE_WIDTH-1;
    int y_hi = y+SPRITE_HEIGHT-1;
    
    if(m_p != ptr){
    
    int highCol = m_p->getX() + SPRITE_WIDTH - 1;
    int lowCol = m_p->getX();
    //int lowCol = (*it)->getX() - SPRITE_WIDTH+1;
    int highRow = m_p->getY() + SPRITE_HEIGHT - 1;
    int lowRow = m_p->getY();
    //int lowRow = (*it)->getY() -SPRITE_HEIGHT+1;
    
    if((x >= lowCol && x <= highCol) && (y >= lowRow && y <= highRow)){ //bottom left
        return true; }
    else if((x >= lowCol && x <= highCol) && (y_hi >= lowRow && y_hi <= highRow)){ return true; } //bottom right
    else if((x_hi >= lowCol && x_hi<= highCol) && (y >= lowRow && y <= highRow)) { return true; } //top left
    else if((x_hi >= lowCol && x_hi<= highCol) && (y_hi >= lowRow && y_hi <= highRow)) { return true; }
    }
    
    std::list<Actor*>::iterator it = m_actors.begin();
    while(it != m_actors.end()){
        //conditions
        if((*it)->blocksMovement() && (*it) != ptr){ //check to make sure that it doesn't block itself
        
            int highCol = (*it)->getX() + SPRITE_WIDTH - 1;
            int lowCol = (*it)->getX();
            //int lowCol = (*it)->getX() - SPRITE_WIDTH+1;
            int highRow = (*it)->getY() + SPRITE_HEIGHT - 1;
            int lowRow = (*it)->getY();
            //int lowRow = (*it)->getY() -SPRITE_HEIGHT+1;
            
            if((x >= lowCol && x <= highCol) && (y >= lowRow && y <= highRow)){ //bottom left
                //cerr << (*it)->getX() << " " << (*it)->getY() << endl;
                return true; }
            else if((x >= lowCol && x <= highCol) && (y_hi >= lowRow && y_hi <= highRow)){ return true; } //bottom right
            else if((x_hi >= lowCol && x_hi<= highCol) && (y >= lowRow && y <= highRow)) { return true; } //top left
            else if((x_hi >= lowCol && x_hi<= highCol) && (y_hi >= lowRow && y_hi <= highRow)) { return true; } //top right
            
        }
        it++;
    }
    return false; //no overlap
}

void StudentWorld::activateOnAppropriateActors(Actor *a){
    //Checks overlap between an item and all other actors
    //If there is overlap, calls functions in Actor that will proceed
    if(doesOverlap(m_p,a)){ //have to call separately on penelope because she is not in the actors container
        a->activateIfAppropriate(m_p);
    }
    std::list<Actor*>::iterator it = m_actors.begin();
    while(it != m_actors.end()){
        if((*it)!= a && doesOverlap((*it), a) && (*it)->isAlive() && a->isAlive()){ //loop over container
            //make sure it does not activate on itself, and that the actor and thing being acted on are alive
            a->activateIfAppropriate(*it);
        }
        it++;
    }
}

bool StudentWorld::isFlameBlockedAt(double x, double y, Actor* ptr){ //similar to ifAgentMovement is blocked
    //don't need to check penelope as she does not block flames
    int x_hi = x+SPRITE_WIDTH-1;
    int y_hi = y+SPRITE_HEIGHT-1;
    std::list<Actor*>::iterator it = m_actors.begin();
    while(it != m_actors.end()){
        //conditions
        if((*it)->blocksFlame() && (*it) != ptr){ //condition that is checked here: make sure it is not comparing with itself and make sure that the element is flame resistant
            
            int highCol = (*it)->getX() + SPRITE_WIDTH - 1;
            int lowCol = (*it)->getX();
            //int lowCol = (*it)->getX() - SPRITE_WIDTH+1;
            int highRow = (*it)->getY() + SPRITE_HEIGHT - 1;
            int lowRow = (*it)->getY();
            //int lowRow = (*it)->getY() -SPRITE_HEIGHT+1;
            
            if((x >= lowCol && x <= highCol) && (y >= lowRow && y <= highRow)){ //bottom left
                //cerr << (*it)->getX() << " " << (*it)->getY() << endl;
                return true; }
            else if((x >= lowCol && x <= highCol) && (y_hi >= lowRow && y_hi <= highRow)){ return true; } //bottom right
            else if((x_hi >= lowCol && x_hi<= highCol) && (y >= lowRow && y <= highRow)) { return true; } //top left
            else if((x_hi >= lowCol && x_hi<= highCol) && (y_hi >= lowRow && y_hi <= highRow)) { return true; } //top right
            
        }
        it++;
    }
    return false;
    
    
}

/////////////

void StudentWorld::buildLevel(int level, Level::LoadResult& res){ // builds level according to text file that it reads in
    //pass in res as a reference so that we can figure out how to progress accordingly in init
    //pass in level count which we will keep track of
    string levelFile;
    switch(level){
        case(1):
            levelFile = "level01.txt";
            break;
        case(2):
            levelFile = "level02.txt";
            break;
        case(3):
            levelFile = "level03.txt";
            break;
        case(4):
            levelFile = "level04.txt";
            break;
        case(5):
            levelFile = "level05.txt";
            break;
        case(6):
            levelFile = "level06.txt";
            break;
        default:
            levelFile = "NO FILE";
            //cerr << "Not a valid level.";
            break;
    }
    cerr << levelFile;
    Level lev(assetPath());
    Level::LoadResult result = lev.loadLevel(levelFile);
    if (result == Level::load_fail_file_not_found){
        res = Level::load_fail_file_not_found;
        cerr << "Cannot find data file" << endl;
    }
    else if (result == Level::load_fail_bad_format){
        res = Level::load_fail_bad_format;
        cerr << "Your level was improperly formatted" << endl;
    }
    else if (result == Level::load_success)
    {
        res = Level::load_success;
        cerr << "Successfully loaded level" << endl;
        for (int i = 0; i < LEVEL_HEIGHT; i++){
            for(int j = 0; j < LEVEL_WIDTH; j++){
                Level::MazeEntry ge = lev.getContentsOf(i,j); // level_x=5, level_y=10
                switch (ge) // so x=80 and y=160 //Follow template from spec, but instead of writing locations, we will assign new objects
                {
                    case Level::empty:
                        //cerr << i*LEVEL_WIDTH<< "  "<< j*LEVEL_HEIGHT << " Location is empty" << endl;
                        break;
                        
                    case Level::smart_zombie:
                        m_actors.push_back(new SmartZombie(i*LEVEL_WIDTH, j*LEVEL_HEIGHT, this,0));
                        break;
                        //cout << "Location 80,160 starts with a smart zombie" << endl;
                        //break;
                    case Level::dumb_zombie:
                        m_actors.push_back(new DumbZombie(i*LEVEL_WIDTH, j*LEVEL_HEIGHT, this,0));
                        break;
                        
                    case Level::player: //Allocate Penelope
                        //cerr << i*LEVEL_WIDTH << "  " << j*LEVEL_HEIGHT << " Location is where Penelope starts" << endl;
                        m_p = new Penelope(i*LEVEL_WIDTH,j*LEVEL_HEIGHT, this);
                        break;
                        
                    case Level::exit:
                        //cerr <<  i*LEVEL_WIDTH << "  " << j*LEVEL_HEIGHT << " Location is where an exit is" << endl;
                        m_actors.push_back(new Exit(i*LEVEL_WIDTH, j*LEVEL_HEIGHT, this));
                        break;
                        
                    case Level::wall: //Allocate Wall (must be pushed onto actor list)
                        //cerr << i*LEVEL_WIDTH<< "  " << j*LEVEL_HEIGHT << " Location holds a Wall" << endl;
                        m_actors.push_back(new Wall(i*LEVEL_WIDTH, j*LEVEL_HEIGHT, this));
                        break;
                    
                    case Level::pit:
                        //cerr << i*LEVEL_WIDTH<< "  " << j*LEVEL_HEIGHT << " Location holds a Pit" << endl;
                        m_actors.push_back(new Pit(i*LEVEL_WIDTH, j*LEVEL_HEIGHT, this));
                        break;
                
                    case Level::gas_can_goodie:
                        m_actors.push_back(new GasCanGoodie(i*LEVEL_WIDTH, j*LEVEL_HEIGHT, this));
                        break;
                        
                    case Level::landmine_goodie:
                        m_actors.push_back(new LandmineGoodie(i*LEVEL_WIDTH, j*LEVEL_HEIGHT, this));
                        break;
                        
                    case Level::vaccine_goodie:
                        m_actors.push_back(new VaccineGoodie(i*LEVEL_WIDTH, j*LEVEL_HEIGHT, this, 0));
                        break;
                        
                    case Level::citizen:
                        m_actors.push_back(new Citizen(i*LEVEL_WIDTH, j*LEVEL_HEIGHT, this));
                        liveCitizens++;
                        break;

                        
                        // etc…
                }
            }
        }
    }
}

int StudentWorld::euclidian(Actor *a1, Actor *a2){ //calculates euclidian distance given two actors
    //cerr << "a1 X: " << a1->getX()  << " a2 X: " << a2->getX() << endl;
    //cerr << "a1 Y: " << a1->getY()  << " a2 Y: " << a2->getY() << endl;
    
    int xd = (a1->getX()) - (a2->getX());
    int yd = (a1->getY()) - (a2->getY());
    return (xd*xd)+(yd*yd); //avoid sq roots
}

int StudentWorld::euclidian2(double x1, double y1, double x2, double y2) const{ //calculates euclidian distance given two sets of coords
    int xd = (x1-x2);
    int yd = (y1-y2);
    return (xd*xd)+(yd*yd); //avoid sq roots
}

bool StudentWorld::doesOverlap(Actor *a1, Actor *a2){ //if euclidian distance <= 10 (we used 100 to avoid square roots)
    if (euclidian(a1, a2) <= 100) { return true; }
    else{ return false; }
}


//LOOP OVER M_ACTORS + PENELOPE

//Find minimum Euclidian distance
bool StudentWorld::locateNearestCitizenTrigger(double x, double y, double &otherX, double &otherY, double &distance, bool &isThreat) const{
    
    //Check with Penelope
    otherX = m_p->getX();
    otherY = m_p->getY();
    int min = euclidian2(x, y, otherX, otherY);
    isThreat = false;
    distance = min;
    
    //cerr << "penelope at " << otherX << " " << otherY << endl;
    
    double threat_x, threat_y, threat_dist;
    bool threat = locateNearestCitizenThreat(x, y, threat_x, threat_y, threat_dist); //loop is done within this function
    if (threat && threat_dist < min){
        otherX = threat_x;
        otherY = threat_y;
        isThreat = true;
        min = threat_dist;
        distance = min;
    }
    
    return true; //should never return false so long as the game is getting played
}

bool StudentWorld::locateNearestCitizenThreat(double x, double y, double &otherX, double &otherY, double &distance) const{
    int minInt = INT_MAX;
    double min = minInt;
    bool flag = false;
    list<Actor*>::const_iterator it= m_actors.begin();
    while(it != m_actors.end()){ //loop over all elements and find zombies
        if((*it)->threatensCitizens() && (*it)->getX() != x && (*it)->getY() != y) {
        if(euclidian2(x, y,(*it)->getX(), (*it)->getY()) < min){
            min = euclidian2(x, y,(*it)->getX(), (*it)->getY());
            otherX = (*it)->getX();
            otherY = (*it)->getY();
            distance = min;
            flag = true;
        }
        }
        it++;
    }
    //cerr << "threat at " << otherX << " " << otherY << "true or not " << flag << endl;
    return flag; // if we don't even find a threat, this will be false (meaning all zombies are dead)
}

bool StudentWorld::isZombieVomitTriggerAt(double x, double y, Actor* ptr) const{
    //scan elements at a particualr coordinate point and checks if they are susceptible to vomit
    //check penelope separately as she is not in the actors container
    if(x == m_p ->getX() && y == m_p -> getY()){ return true; }
    
    list<Actor*>::const_iterator it= m_actors.begin();
    while(it != m_actors.end()){
        if((*it)->triggersZombieVomit() && (*it)->getX() == x && (*it)->getY() == y && (*it)!=ptr){
            return true;
        }
        it++;
    }
    return false;
}


bool StudentWorld::locateClosestNearbyVomitTrigger(double x, double y, double &otherX, double &otherY){
    //this will be used in smart zombie
    //locate nearest human to the zombie we are searching for
    //body is very similar to locateNearestCitizenThreat as it does the same general thing
    otherX = m_p->getX();
    otherY = m_p->getY();
    int min = euclidian2(x, y, otherX, otherY);
    bool flag = true;
    
    list<Actor*>::const_iterator it= m_actors.begin();
    while(it != m_actors.end()){
        if(euclidian2(x, y,(*it)->getX(), (*it)->getY()) < min && (*it)->triggersZombieVomit() && (*it)->getX() != x && (*it)->getY() != y){
            min = euclidian2(x, y,(*it)->getX(), (*it)->getY());
            otherX = (*it)->getX();
            otherY = (*it)->getY();
            flag = true;
        }
        it++;
    }
    return flag;
}


/*
int StudentWorld::getDistToP(Actor* a){
    return euclidian(a, m_p);
}


int StudentWorld::getDistToZ(Actor* a){
    double x_o, y_o;
    return 0;
}
*/

void StudentWorld::writeToSS(){
    //String stream printer
    // SAMPLE
    //Score: 004500  Level: 27  Lives: 3  Vaccines: 2  Flames: 16  Mines: 1  Infected: 0
    ostringstream oss;
    oss << "Score: ";
    
    if(getScore()>=0){ //this we want six spots here to look something like 001080
        oss.fill('0');
        oss << std::setw(6) << getScore();
    }
    else{ //we want negative sign at front so really only filling five spots -01080
        oss.fill('0');
        oss<< '-' << std::setw(5) << (-1)*getScore();
    }
    oss << "  Level: ";
    oss << getLevel(); //from gameworld
    oss << "  Lives: ";
    oss << getLives(); //from gameworld
    oss << "  Vaccines: ";
    oss << m_p->getNVacc(); //func returns num vaccines
    oss << "  Flames: ";
    oss << m_p->getNFlame(); //func returns num flames
    oss << "  Mines: ";
    oss << m_p -> getNMines(); //function returns num mines
    oss << "  Infected: ";
    oss << m_p ->getPoisonCt(); //function that returns infection countvomit)
    
    string ss = oss.str();
    setGameStatText(ss);
    
}

