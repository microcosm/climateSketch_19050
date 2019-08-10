#pragma once

#include "ofxAudioUnitManager.h"

class csAudio{

public:
    void setup();
    void update(ofEventArgs &e);
    void draw(ofEventArgs &e);

    ofxAudioUnitManager manager;
    aumAudioUnitChain chain;
    aumManagedAudioUnit synth, filter, reverb;
};
