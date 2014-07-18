#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // OSC
    // listen on the given port
	//cout << "listening for osc messages on port " << PORT << "\n";
	receiver.setup(PORT);
    
	current_msg_string = 0;
	camX = -6000;
	camZ = 0;
    
    ofBackground(0, 0, 0);
    cam.setPosition(camX, 0, camZ);
    cam.lookAt(ofVec3f(0, 0, 0));
    
    // KINECT
    ofSetLogLevel(OF_LOG_VERBOSE);
    kinect.setRegistration(true);
    kinect.init();
    
    // SOUND
    sound.loadSound( "Monneista.wav" );
    sound.setLoop(false);
    
    //Set spectrum values to 0
    for (int i=0; i<N; i++) {
        spectrum[i] = 0.0f;
    }
    
    ofEnableDepthTest();
	glEnable(GL_POINT_SMOOTH); // use circular points instead of square points
	glPointSize(4);
    
    // LIGHTS
    ofSetSmoothLighting(true);
    pointLight.setDiffuseColor( ofFloatColor(.85, .85, .85) );
    pointLight.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
    pointLight.setPosition(1000, 400, 1000);
    
    // POST-PROCESSING
    post.init(ofGetWidth(), ofGetHeight());
    post.createPass<BloomPass>()->setEnabled(true);
    post.createPass<BloomPass>()->setEnabled(true);
    post.createPass<GodRaysPass>()->setEnabled(true);
    
    //post.createPass<FxaaPass>()->setEnabled(true);
    post.createPass<DofPass>()->setEnabled(true);
    post.createPass<VerticalTiltShifPass>()->setEnabled(true);
    
    // PLANETS
    nPlanets = 726;
    myPlanet = new ofPlanet*[nPlanets]; // an array of pointers for the objects
    nSatellites = 2;
    for (float y = -165; y < 165; y += 10) {
        for (float x = -110; x < 110; x += 10) {
            myPlanet[planetCounter] = new ofPlanet(x, y, nSatellites);  // create each object from the array
            planetCounter++;
        }
    }
    
    // STARS
    nStars = 200;
    myStar = new ofStar*[nStars];
    int minRadius = 600;
    int maxRadius = 1800;
    for (int i = 0; i < nStars; i++) {
        myStar[i] = new ofStar(minRadius, maxRadius);
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    // OSC
    // hide old messages
	for(int i = 0; i < NUM_MSG_STRINGS; i++){
		if(timers[i] < ofGetElapsedTimef()){
			msg_strings[i] = "";
		}
	}
    
	// check for waiting messages
	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        
		// check for mouse moved message
		if(m.getAddress() == "/camPosition"){
			// both the arguments are int32's
			camZ = m.getArgAsFloat(0);
			camX = m.getArgAsFloat(1);
		}
        
	}
    
    
    cam.setPosition(camX, 0, camZ);
    cam.lookAt(ofVec3f(0, 0, 0));
    
    
    // KINECT
    kinect.update();
    
    // SOUND
    ofSoundUpdate();   //Get current spectrum with N bands
    float *val = ofSoundGetSpectrum(N);
    //We should not release memory of val,
    //because it is managed by sound engine
    //Update our smoothed spectrum,
    //by slowly decreasing its values and getting maximum with val
    //So we will have slowly falling peaks in spectrum
    planetCounter = 0;
    int step = 5;
    for(int y = 157; y < kinect.height - 158; y += step) {
        for(int x = 265; x < kinect.width - 265; x += step) {
            int iSpectrum = planetCounter / 16;
            spectrum[iSpectrum] *= 0.99;    //Slow decreasing
            spectrum[iSpectrum] = max(spectrum[iSpectrum], val[iSpectrum]);
            if (kinect.getDistanceAt(x, y) > 500 && kinect.getDistanceAt(x, y) <= 800) {
                myPlanet[planetCounter]->update(planetCounter, kinect.getDistanceAt(x, y), spectrum[iSpectrum]);
            } else {
                myPlanet[planetCounter]->update(planetCounter, 800, spectrum[iSpectrum]);
            }
            planetCounter++;
        }
    }
    
    for (int i = 0; i < nStars; i++) {
        spectrum[i] *= 0.99;    //Slow decreasing
        spectrum[i] = max(spectrum[i], val[i]);
        myStar[i]->update(i, spectrum[i]);
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    glPushAttrib(GL_ENABLE_BIT); // copy enable part of gl state
    // setup gl state
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    
    post.begin(cam); // begin scene to post process
    ofPushMatrix();
    ofScale(1, -1, 1);
    //ofRotateY(90);
    //    rotY += 0.5;
    //    ofRotateX(rotX);
    //    rotX += 0.5;
    //    ofRotateZ(rotZ);
    //    rotZ += 0.5;
    //ofEnableLighting();
    //pointLight.enable();
    
    for (int i = 0; i < nPlanets; i++) {
        myPlanet[i]->draw();
    }
    
    for (int i = 0; i < nStars; i++) {
        myStar[i]->draw();
    }

    ofPopMatrix();
    post.end(); // end scene and draw
    
    // set gl state back to original
    glPopAttrib();
}

//--------------------------------------------------------------
void ofApp::exit(){
    
    kinect.close();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    sound.play();
    ofSetWindowTitle("START");
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}