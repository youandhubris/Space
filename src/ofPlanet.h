#ifndef _OF_PLANET     // if this class hasn't been defined, the program can define it
#define _OF_PLANET    // by using this if statement you prevent the class to be called more
                    // than once which would confuse the compiler

#include "ofMain.h"

class ofPlanet {
    
public: // place public functions or variables declarations here
    
    // methods, equivalent to specific functions of your class objects
    //void update(int i, float spectrum);  // update method, used to refresh your objects properties
    void update(int planetCounter, int kinectPosition, float spectrum);
    void draw();    // draw method, this where you'll do the object's drawing
    
    // variables
    float x;      // position
    float y;
    int nSatellites;
    int i;
    float spectrum;
    int planetCounter;
    int kinectPosition;
    float prevKinectPosition[726];
    
    // primitives
    ofIcoSpherePrimitive innerSphere;
    ofIcoSpherePrimitive outterSphere;
    ofMesh satelliteSphere;
    vector<ofVec3f> satellitePosition;
    
    ofPlanet(float x, float y, int nSatellites); // constructor - used to initialize an object, if no properties are passed
    //               the program sets them to the default value
    
private: // place private functions or variables declarations here
    
}; // dont't forget the semicolon!!

#endif