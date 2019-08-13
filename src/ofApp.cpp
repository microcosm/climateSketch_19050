#include "ofApp.h"

void ofApp::setup(){
    graphics.setup();
    audio.setup();
}

void ofApp::update(){
    if(ofGetFrameNum() == 0 || ofRandom(1) < 0.08){
        state = randomInt(0, 7);
        cout << "State: " << state << endl;
    }

    graphics.setState(state);
    audio.setState(state);
}

void ofApp::draw(){
    
}

int ofApp::randomInt(int min, int max){
    int val;
    val = (int) ofRandom(min, max + 1);
    val = val == max + 1 ? max : val;
    return val;
}
