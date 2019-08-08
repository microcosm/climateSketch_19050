#include "csAudio.h"

void csAudio::setup(){
    ofAddListener(ofEvents().update, this, &csAudio::update);
    ofAddListener(ofEvents().draw, this, &csAudio::draw);
}

void csAudio::update(ofEventArgs &e){
    
}

void csAudio::draw(ofEventArgs &e){
    
}
