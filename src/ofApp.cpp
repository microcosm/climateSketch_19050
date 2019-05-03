#include "ofApp.h"

void ofApp::setup(){
    ofToggleFullscreen();
    //ofSetWindowShape(960, 540);
    ofSetBackgroundAuto(false);

    loadFiles("rocks", 3, rockLayers);
    loadFiles("rocks-mask", 2, rockMasks, LOAD_IDENTICAL);
    loadFiles("week4skyline", 6, skylineLayers);
    loadFiles("week4skyline", 6, skylineMasks);

    rockLayers[1].incrementTextureOffsetX(-0.04);
    rockLayers[2].incrementTextureScale(0.2);
    rockLayers[2].incrementTextureOffsetY(0.2);
    rockLayers[2].flipTexture(TEXTURE_FLIP_HORIZONTAL);

    initializeSkylines();
    masker.setup(7);

    manualSkyline = false;
    colorFlashCount = 0;
    skylineNumber = 0;
    renderNumber = 0;
}

void ofApp::initializeSkylines(){
    for(int i = 0; i < 6; i ++){
        skylineLayers[i].setTextureOffset(TEXTURE_OFFSET_TOP_CENTER);
        skylineMasks[i].setTextureOffset(TEXTURE_OFFSET_TOP_CENTER);
    }

    skylinePositionIncrement = 0;
    skylineOpacity = 255;
}

void ofApp::loadFiles(string baseFilename, int count, vector<ofxTexturePlane>& collection, csLoadingMode mode){
    string fileIndex;
    for(int i = 1; i <= count; i++){
        fileIndex = mode == LOAD_INCREMENTAL ? ofToString(i) : "";
        collection.push_back(blankSlate);
        collection.back().setup(baseFilename + fileIndex + ".jpg");
    }
}

void ofApp::update(){
    updateBackgrounds();
    updateSkylines();
    if(ofRandom(1) < 0.08){
        renderNumber = ofRandom(0, 7);
        cout << "Render number: " << renderNumber << endl;
    }
}

void ofApp::updateBackgrounds(){
    rockLayers[0].incrementTextureOffsetY(0.002);
    rockLayers[1].incrementTextureOffsetY(-0.004);
    rockLayers[2].incrementTextureOffsetX(-0.001);

    rockMasks[0].incrementTextureOffsetY(0.002);
    rockMasks[1].incrementTextureOffsetY(-0.002);
}

void ofApp::updateSkylines(){
    if(!manualSkyline && ofRandom(1) < 0.05){
        skylineNumber = ofRandom(6);
        initializeSkylines();

        if(ofRandom(1) < 0.6){
            skylinePositionIncrement = ofRandom(0.001, 0.005);
            //skylinePositionIncrement = ofRandom(1) < 0.5 ? skylinePositionIncrement : -skylinePositionIncrement;
            skylineOpacity = ofRandom(30, 120);
        }
    }

    skylineLayers[skylineNumber].incrementTextureOffsetY(skylinePositionIncrement);
    skylineMasks[skylineNumber].incrementTextureOffsetY(skylinePositionIncrement);
}

void ofApp::draw(){
    //Layer 1
    masker.beginLayer(0);
    {
        ofSetColor(ofColor::black);
        if(colorFlashCount > 0) {
            ofSetColor(ofColor::red, colorFlashCount);
            colorFlashCount -= 24;
        } else if(ofRandom(1) < 0.015){
            ofSetColor(ofColor::red);
            colorFlashCount = ofRandom(255);
        }
        else if(ofRandom(1) < 0.025) ofSetColor(ofColor::white);
        rockLayers[1].draw();
    }
    masker.endLayer(0);
    
    //Layer 2
    masker.beginLayer(1);
    {
        ofSetColor(255, 0, 0);
        rockLayers[2].draw();
    }
    masker.endLayer(1);
    
    masker.beginMask(1);
    {
        rockMasks[0].draw();
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        rockMasks[1].draw();
        ofDisableBlendMode();
        ofSetColor(ofColor::black);
        ofDrawRectangle(0, 0, masker.getWidth() * 0.5, masker.getHeight());
    }
    masker.endMask(1);

    //Layer 3
    masker.beginLayer(2);
    {
        ofSetColor(ofColor::red);
        rockLayers[2].flipTexture(TEXTURE_FLIP_VERTICAL);
        rockLayers[2].draw();
        rockLayers[2].flipTexture(TEXTURE_FLIP_VERTICAL);
    }
    masker.endLayer(2);
    
    masker.beginMask(2);
    {
        rockMasks[0].draw();
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        rockMasks[1].draw();
        ofDisableBlendMode();
        ofSetColor(ofColor::black);
        ofDrawRectangle(masker.getWidth() * 0.5, 0, masker.getWidth(), masker.getHeight());
    }
    masker.endMask(2);

    if(skylineNumber >= 0 && skylineNumber <= 5){
        masker.beginLayer(3);
        {
            ofSetColor(ofColor(ofColor::white, skylineOpacity));
            skylineLayers[skylineNumber].draw();
        }
        masker.endLayer(3);

        masker.beginMask(3);
        {
            ofSetColor(ofColor(ofColor::white, skylineOpacity));
            skylineLayers[skylineNumber].draw();
        }
        masker.endMask(3);

        masker.beginLayer(4);
        {
            ofEnableAlphaBlending();
            masker.drawLayer(3);
            ofDisableAlphaBlending();
        }
        masker.endLayer(4);
        
        masker.beginLayer(5);
        {
            ofSetColor(ofColor(ofColor::white, skylineOpacity * 3));
            skylineLayers[skylineNumber % 2].draw();
        }
        masker.endLayer(5);
        
        masker.beginMask(5);
        {
            ofSetColor(ofColor(ofColor::white));
            skylineLayers[skylineNumber % 2].draw();
        }
        masker.endMask(5);
        
        masker.beginLayer(6);
        {
            masker.drawLayers(0, 2);
        }
        masker.endLayer(6);
        
        masker.beginMask(6);
        {
            masker.drawLayers(3, 5);
        }
        masker.endMask(6);
    }

    //Draw it
    //masker.draw();
    if(renderNumber >= 0 && renderNumber <= 2){
        masker.drawLayers(0, 5);
    }else if(renderNumber >= 3 && renderNumber <= 5){
        masker.drawMask(6);
    }else if(renderNumber == 6){
        ofBackground(255, 0, 0, 30);
        masker.drawLayer(6);
    }
    
    masker.drawOverlay();
}

void ofApp::keyPressed(int key){
    if(key == ' '){
        masker.toggleOverlay();
    }else{
        cout << key - 49 << endl;
        skylineNumber = key - 49;
        manualSkyline = skylineNumber >= 0 && skylineNumber <= 5;
    }
}
