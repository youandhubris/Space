#ifndef _OF_STAR
#define _OF_STAR

#include "ofMain.h"

class ofStar {
    
public:
    
    void update(int i, float spectrum);
    void draw();
    
    // variables
    int minRadius;
    int maxRadius;
    int i;
    // primitives
    ofMesh starSphere;
    
    ofStar(int minRadius, int maxRadius);
    
private:
    
};

#endif