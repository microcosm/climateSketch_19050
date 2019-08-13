#pragma once

#include "ofxAudioUnitManager.h"
#include "aumUnit_Fm8.h"
#include "aumUnit_AUMatrixReverb.h"
#include "aumUnit_AULowPassFilter.h"

class csAudio{

public:
    void setup();
    void update(ofEventArgs &e);
    void draw(ofEventArgs &e);

    ofxAudioUnitManager manager;
    aumAudioUnitChain chain;
    aumUnit_Fm8 fm8;
    aumUnit_AUMatrixReverb reverb;
    aumUnit_AULowPassFilter filter;
};
