#ifndef _OF_PLANET
#define _OF_PLANET

#include "ofMain.h"

class ofPlanet {
    
public:
    
    void update(int planetCounter, int kinectPosition, float spectrum);
    void draw();
    
    // variables
    float x;
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
    
    ofPlanet(float x, float y, int nSatellites);
    
private:
    
};

#endif