#ifndef _OF_STAR     // if this class hasn't been defined, the program can define it
#define _OF_STAR    // by using this if statement you prevent the class to be called more
                    // than once which would confuse the compiler

#include "ofMain.h"

class ofStar {
    
public: // place public functions or variables declarations here
    
    // methods, equivalent to specific functions of your class objects
    void update(int i, float spectrum);  // update method, used to refresh your objects properties
    void draw();    // draw method, this where you'll do the object's drawing
    
    // variables
    int minRadius;
    int maxRadius;
    int i;
    // primitives
    ofMesh starSphere;
    
    ofStar(int minRadius, int maxRadius); // constructor - used to initialize an object, if no properties are passed
    //               the program sets them to the default value
    
private: // place private functions or variables declarations here
    
}; // dont't forget the semicolon!!

#endif