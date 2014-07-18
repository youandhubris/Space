#pragma once

#include "ofMain.h"
#include "ofxPostProcessing.h"
#include "ofxKinect.h"
#include "ofxOsc.h"

#define PORT 57120
#define NUM_MSG_STRINGS 20

// Objects
#include "ofPlanet.h"
#include "ofStar.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void drawPoint(float x, float y, float noiseFactor);
    
    // Post
    ofxPostProcessing post;
    ofCamera cam;
    float rotY, rotX, rotZ;
    ofLight pointLight;
    
    // Sound
    ofSoundPlayer sound;    //Sound sample
    const int N = 726;      //Number of bands in spectrum
    float spectrum[726];      //Smoothed spectrum values
    
    // Kinect
    ofxKinect kinect;
    
    // OSC
    ofxOscReceiver receiver;
    
    int current_msg_string;
    string msg_strings[NUM_MSG_STRINGS];
    float timers[NUM_MSG_STRINGS];
    
    float camX, camZ;
    string mouseButtonState;
    
    // Objects
private:
    ofPlanet** myPlanet;
    int planetCounter, nPlanets, nSatellites;
    
    ofStar** myStar;
    int nStars;
};
