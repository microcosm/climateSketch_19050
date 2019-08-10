#include "csAudio.h"

void csAudio::setup(){
    manager.setup();
    manager.toggleDebugUI();
    synth.setup("togu1", 'aumu', 'Nif8', '-NI-');
    filter.setup("filter1", kAudioUnitType_Effect, kAudioUnitSubType_LowPassFilter);
    reverb.setup("reverb1", kAudioUnitType_Effect, kAudioUnitSubType_MatrixReverb);

    manager.createChain(&chain)
        .link(&synth)
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
