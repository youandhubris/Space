#include "ofPlanet.h"

ofPlanet::ofPlanet(float _x, float _y, int _nSatellites)
{
    
    x = _x;
    y = _y;
    nSatellites = _nSatellites;

    innerSphere.setPosition(x, y, 0);
    innerSphere.setResolution(1);
    innerSphere.setRadius(1);
    
    satelliteSphere.setMode(OF_PRIMITIVE_POINTS);
    for (int i = 0; i < nSatellites; i++) {
        float theta = ofRandom(0, TWO_PI);
        float delta = ofRandom(0, PI);
        int radius = ofRandom(2, 3);
        float xPos = x + cos(theta) * sin(delta) * radius;
        float yPos = y + sin(theta) * sin(delta) * radius;
        float zPos = 0 + cos(delta) * radius;
        ofVec3f pos(xPos, yPos, zPos);
        satelliteSphere.addVertex(pos);
        ofColor brilho;
        brilho.setBrightness(ofRandom(150, 255));
        satelliteSphere.addColor(brilho);
        satellitePosition.push_back(ofVec3f(ofRandom(0,100000), ofRandom(0,100000), ofRandom(0,100000)));
    }

}

//void ofPlanet::update(int _i, float _spectrum)
void ofPlanet::update(int _planetCounter, int _kinectPosition, float _spectrum)
{
    
    i = _planetCounter;
    kinectPosition = _kinectPosition;
    spectrum = _spectrum;
    
    float kinectPositionSmooth = ofLerp(prevKinectPosition[i], kinectPosition, 0.05f);

    ofVec3f spheresPosition = innerSphere.getPosition();
    innerSphere.setPosition(spheresPosition.x, spheresPosition.y, -kinectPositionSmooth + 800);
    
    for (int s = 0; s < nSatellites; s++) {
        ofVec3f updatePosition = satelliteSphere.getVertex(s);
    
        float time = ofGetElapsedTimef();
        float timeScale = 0.25;
        float displacementScale = 1;
        ofVec3f positionOffsets = satellitePosition[s];
    
        updatePosition.x += (ofSignedNoise(time*timeScale+positionOffsets.x)) * displacementScale;
        updatePosition.y += (ofSignedNoise(time*timeScale+positionOffsets.y)) * displacementScale;
        updatePosition.z = -kinectPositionSmooth + 800 + (ofSignedNoise(time*timeScale+positionOffsets.z)) * displacementScale;
    
        satelliteSphere.setVertex(s, updatePosition);
        ofColor brilho;
        brilho.setBrightness(spectrum * (i/16) * 255);
        satelliteSphere.setColor(s, brilho);
    }
    
    prevKinectPosition[i] = kinectPositionSmooth;
}

void ofPlanet::draw(){
    ofSetColor(255);
    innerSphere.draw();
    ofNoFill();
    satelliteSphere.draw();
}