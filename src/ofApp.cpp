#include "ofApp.h"

//TODO: Draw vertices as points
//TODO: Select a vertice by click
//TODO: Delete selected vertice
//TODO: Drag selected vertice individually in the xy plane

//TODO: interface for 'exploding' z axis randomly within min/max z
//TODO: lock the z axis of vertices

//TODO: save and load mesh and vertices (collada (.dae)/.ply ?)
//TODO: ofparameters for settings that are in a group that saves to a json file.

//TODO: wrap to geometry...?


//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableSmoothing();
    ofBackground(0);
    ofSetSmoothLighting(true);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofNoFill();
    //ofEnableLighting();
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofRotateYRad(ofGetElapsedTimef());
    ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
    triangulation.draw();
    ofDrawBox(400, 400, 0, 200, 200, 200);
    ofPopMatrix();
    ofDisableLighting();
    
    ofDrawBitmapString("'r' to reset", ofPoint(10,20));
    ofDrawBitmapString("FPS:" + ofToString(ofGetFrameRate()), ofPoint(10,40));
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'r'){
        triangulation.reset();
    }
    if(key == 'a'){
        for(int i = 0; i < ofRandom(20); i++){
            triangulation.addPoint(ofDefaultVec3(ofRandom(ofGetWidth()),ofRandom(ofGetHeight()),ofRandom(-20, 20)));
        }
        triangulation.triangulate();
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    triangulation.addPoint(ofDefaultVec3(x,y,0));
    triangulation.triangulate();
}
