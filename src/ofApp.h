#pragma once

#include "ofMain.h"
#include "csGraphics.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    csGraphics graphics;
};
