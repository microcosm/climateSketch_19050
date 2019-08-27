#pragma once

#include "ofxAudioUnitManager.h"
#include "aumUnit_Fm8.h"
#include "aumUnit_Massive.h"
#include "aumUnit_Kontakt6.h"
#include "aumUnit_AUMatrixReverb.h"
#include "aumUnit_AULowPassFilter.h"

//In 4/4 music there are 4 bars * 4 beats per bar (a.k.a. quarter notes)
//This makes 16 beats for every 4 bars
//I am calling 4 bars collectivaly a 'sequence'
//There are 60 ticks for each of the 16 beats in a sequence
//This makes 60 * 16 = 960 ticks per sequence
//And 60 * 4 = 240 ticks per bar
//The tick count value across the sequence is exposed as ofxBpm.countOfTick
const int ticksPerSequence = 960;
const int ticksPerBar = 240;
const int ticksPerHyperSequence = 3840;

const int barsPerSequence = 4;
const int sequencesPerHyperSequence = 4;

class csAudio{

public:
    void setup();
    void setState(int _state);
    void update(ofEventArgs &e);
    void draw(ofEventArgs &e);
    void beatEvent();

protected:
    void respondToStateChange();
    float mapBarProgress(float max);
    float mapBarProgress(float min, float max);
    float mapSequenceProgress(float max);
    float mapSequenceProgress(float min, float max);
    float mapHyperSequenceProgress(float max);
    float mapHyperSequenceProgress(float min, float max);

    int state;
    int sequenceIndex;
    ofxAudioUnitManager manager;
    aumAudioUnitChain chain1, chain2, chain3, chain4;
    aumUnit_Fm8 fm8;
    aumUnit_Massive massive;
    aumUnit_Kontakt6 kontakt1, kontakt2;
};
