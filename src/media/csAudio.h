#pragma once

#include "ofxAudioUnitManager.h"
#include "aumUnit_Fm8.h"
#include "aumUnit_AUMatrixReverb.h"
#include "aumUnit_AULowPassFilter.h"

class csAudio{

public:
    void setup();
    void setState(int _state);
    void update(ofEventArgs &e);
    void draw(ofEventArgs &e);

    int state;
    ofxAudioUnitManager manager;
    aumAudioUnitChain chain;
    aumUnit_Fm8 fm8;
    aumUnit_AUMatrixReverb reverb;
    aumUnit_AULowPassFilter filter;
};
