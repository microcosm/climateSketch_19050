#include "csAudio.h"

void csAudio::setup(){
    manager.setup();
    manager.toggleDebugUI();
    fm8.setup("Fm8");
    filter.setup("filter1");
    reverb.setup("reverb1");
    state = 0;
    sequenceIndex = -1;

    manager.createChain(&chain)
        .link(&fm8)
        .to(&filter)
        .to(&reverb)
        .toMixer();

    ofAddListener(ofEvents().update, this, &csAudio::update);
    ofAddListener(ofEvents().draw, this, &csAudio::draw);
    ofAddListener(manager.bpm.beatEvent, this, &csAudio::beatEvent);
    
    manager.bpm.setBpm(60);
    manager.bpm.start();
    chain.sendNoteOn("E3");
}

void csAudio::setState(int _state){
    bool changed = state == _state;
    state = _state;
    if(changed) respondToStateChange();
}

void csAudio::update(ofEventArgs &e){
    float progress = cos(mapHyperSequenceProgress(TWO_PI));
    cout << progress << endl;
    fm8.set(fm8.op_x_frequency_ratiobr, ofMap(progress, -1, 1, 0.035, 0.05));
}

void csAudio::draw(ofEventArgs &e){
    
}

void csAudio::beatEvent(void){
    if(manager.bpm.barIndex == 0) {
        sequenceIndex++;
        if(sequenceIndex >= sequencesPerHyperSequence){
            sequenceIndex = 0;
        }
    }

    cout << "============> SEQUENCE: " << sequenceIndex + 1 << " BAR: " << manager.bpm.barIndex + 1 << endl;
}

void csAudio::respondToStateChange(){
    
}

float csAudio::mapBarProgress(float max){
    return mapBarProgress(0, max);
}
    
float csAudio::mapBarProgress(float min, float max){
    return ofMap(manager.bpm.countOfTick % ticksPerBar, 0, ticksPerBar, min, max);
}

float csAudio::mapSequenceProgress(float max){
    return mapSequenceProgress(0, max);
}

float csAudio::mapSequenceProgress(float min, float max){
    return ofMap(manager.bpm.countOfTick % ticksPerSequence, 0, ticksPerSequence, min, max);
}

float csAudio::mapHyperSequenceProgress(float max){
    return mapHyperSequenceProgress(0, max);
}

float csAudio::mapHyperSequenceProgress(float min, float max){
    int ticksFromPreviousSequences = sequenceIndex * ticksPerSequence;
    int ticks = ticksFromPreviousSequences + manager.bpm.countOfTick;
    return ofMap(ticks % ticksPerHyperSequence, 0, ticksPerHyperSequence, min, max);
}
