#include "csAudio.h"

void csAudio::setup(){
    manager.setup();
    manager.toggleDebugUI();
    fm8.setup("Fm8");
    filter.setup("filter1");
    reverb.setup("reverb1");
    fm8.printParamChanges();

    manager.createChain(&chain)
        .link(&fm8)
        .to(&filter)
        .to(&reverb)
        .toMixer();

    chain.sendNoteOn("E3");

    ofAddListener(ofEvents().update, this, &csAudio::update);
    ofAddListener(ofEvents().draw, this, &csAudio::draw);
}

void csAudio::update(ofEventArgs &e){
    
}

void csAudio::draw(ofEventArgs &e){
    
}
