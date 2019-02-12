//
//  main.cpp
//  hw3-landmark
//
//  Created by Aditya Pimplaskar on 2/5/19.
//  Copyright © 2019 Aditya Pimplaskar. All rights reserved.
//
#include <iostream>
#include <string>
using namespace std;

//Your declarations and implementations would go here

class Landmark{
public:
    Landmark(string s){ m_name = s; }
    virtual ~Landmark(){}
    virtual string color() const { return "yellow"; } //it is going to be yellow for all but hotel
        // in turn, we can leave it as this in the base class and only provide a new implementation in the hotel subclass
    virtual string icon() const = 0;
    //this is going to differ across every subclass and every subclass that is defined must have one: pure virtual
    virtual string name() const{ return m_name; } //m_name is a member of the base class
private:
    //string m_color //UNNECESSARY
    //string m_icon;
    string m_name;
};

class Hotel: public Landmark{
public:
    Hotel(string s): Landmark(s){}
    ~Hotel(){ cout << "Destroying the hotel " << Landmark::name() << "." << endl; }
    virtual string icon() const { return "bed"; }
};

class Restaurant : public Landmark{
public:
    Restaurant(string s, int capacity): Landmark(s){
        m_cap = capacity;
    }
    ~Restaurant(){ cout << "Destroying the restaurant " << Landmark::name() << "." << endl; }
    virtual string icon() const{
        if (m_cap >= 40) { return "large knife/fork";}
        else { return "small knife/fork"; }
    }
    
private:
    int m_cap;
};

class Hospital: public Landmark{
public:
    Hospital(string s): Landmark(s){}
    ~Hospital(){ cout << "Destroying the hospital " << Landmark::name() << "." << endl;; }
    virtual string color() const{ return "blue"; }
    virtual string icon() const{ return "H"; }
};

void display(const Landmark* lm)
{
    cout << "Display a " << lm->color() << " " << lm->icon() << " icon for "
    << lm->name() << "." << endl;
}

int main()
{
    Landmark* landmarks[4];
    landmarks[0] = new Hotel("Westwood Rest Good");
    // Restaurants have a name and seating capacity.  Restaurants with a
    // capacity under 40 have a small knife/fork icon; those with a capacity
    // 40 or over have a large knife/fork icon.
    landmarks[1] = new Restaurant("Bruin Bite", 30);
    landmarks[2] = new Restaurant("La Morsure de l'Ours", 100);
    landmarks[3] = new Hospital("UCLA Medical Center");
    
    Landmark* test[2];
    test[0] = new Restaurant("Bruin Bite",30);
    //test[1] = new Landmark("This fails");
    
    cout << "Here are the landmarks." << endl;
    for (int k = 0; k < 4; k++)
        display(landmarks[k]);
    
    // Clean up the landmarks before exiting
    cout << "Cleaning up." << endl;
    for (int k = 0; k < 4; k++)
        delete landmarks[k];
}
