#include "ofStar.h"

ofStar::ofStar(int _minRadius, int _maxRadius)
{
    minRadius = _minRadius;
    maxRadius = _maxRadius;
    starSphere.setMode(OF_PRIMITIVE_POINTS);
    
    float theta = ofRandom(0, TWO_PI);
    float delta = ofRandom(0, PI);
    int radius = ofRandom(minRadius, maxRadius);
    float xPos = cos(theta) * sin(delta) * radius;
    float yPos = sin(theta) * sin(delta) * radius;
    float zPos = cos(delta) * radius;
    ofVec3f pos(xPos, yPos, zPos);
    starSphere.addVertex(pos);
    
    ofColor brilho;
    brilho.setBrightness(ofRandom(200, 255));
    starSphere.addColor(brilho);
    
}

void ofStar::update(int _i, float _spectrum){
    
    i = _i;
    float spectrum = _spectrum;
    
}

void ofStar::draw(){
    starSphere.draw();
}