#pragma once

#include "ofxTexturePlane.h"
#include "ofxLayerMask.h"

enum csLoadingMode {
    LOAD_INCREMENTAL,
    LOAD_IDENTICAL
};

class csGraphics{

public:
    void setup();
    void initializeSkylines();
    void loadFiles(string baseFilename, int count, vector<ofxTexturePlane>& collection, csLoadingMode mode=LOAD_INCREMENTAL);
    void update(ofEventArgs &e);
    void updateBackgrounds();
    void updateSkylines();
    void draw(ofEventArgs &e);
    void keyPressed(int key);

    ofxTexturePlane blankSlate;
    vector<ofxTexturePlane> rockLayers;
    vector<ofxTexturePlane> rockMasks;
    vector<ofxTexturePlane> skylineLayers;
    vector<ofxTexturePlane> skylineMasks;
    ofxLayerMask masker;
    int colorFlashCount;
    int skylineNumber;
    bool manualSkyline;
    float skylinePositionIncrement, skylineOpacity;
    int renderNumber;
};
