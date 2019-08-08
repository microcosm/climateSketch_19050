#pragma once

#include "ofMain.h"
#include "csGraphics.h"
#include "csAudio.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    csGraphics graphics;
    csAudio audio;
};
