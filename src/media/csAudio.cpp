#include "csAudio.h"

void csAudio::setup(){
    manager.setup();
    manager.toggleDebugUI();

    fm8.setup("Fm8");
    massive.setup("Massive");
    kontakt1.setup("Kontakt1");
    kontakt2.setup("Kontakt2");

    state = 0;
    sequenceIndex = -1;

    manager.createChain(&chain1)
        .link(&fm8)
        .toMixer();
    
    manager.createChain(&chain2)
        .link(&kontakt1)
        .toMixer();
    
    manager.createChain(&chain3)
    .link(&kontakt2)
    .toMixer();
    
    manager.createChain(&chain4)
    .link(&massive)
    .toMixer();

    ofAddListener(ofEvents().update, this, &csAudio::update);
    ofAddListener(ofEvents().draw, this, &csAudio::draw);
    ofAddListener(manager.bpm.beatEvent, this, &csAudio::beatEvent);
    
    manager.bpm.setBpm(60);
    manager.bpm.start();
    chain1.sendNoteOn("E3");
    chain2.sendNoteOn("E3");
    chain3.sendNoteOn("E0");

    chain4.sendNoteOn("E3");
    chain4.sendNoteOn("F#3");
    chain4.sendNoteOn("A4");
}

void csAudio::setState(int _state){
    bool changed = state == _state;
    state = _state;
    if(changed) respondToStateChange();
}

void csAudio::update(ofEventArgs &e){
    float progress = cos(mapHyperSequenceProgress(TWO_PI));
    //fm8.set(fm8.op_x_frequency_ratiobr, ofMap(progress, -1, 1, 0.005, 0.05));
    
    //fm8.set(fm8.master_volume, 0);
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
