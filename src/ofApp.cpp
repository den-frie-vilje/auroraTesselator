#include "ofApp.h"

//TODO: Draw vertices as points

//TODO: interface for 'extruding' z axis randomly within min/max z
//TODO: lock the z axis of vertices

//TODO: ofparameters for settings that are in a group that saves to a json file.

//TODO: wrap to geometry...?

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableSmoothing();
    ofBackground(0);
    ofSetSmoothLighting(true);
    ofSetFrameRate(60);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    if(grabbedPointShouldBeDeleted){
        triangulation.removePointAtIndex(grabbedPointIndex);
        grabbedPointIndex = -1;
        grabbedPointShouldBeDeleted = false;
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofNoFill();
    ofSetColor(255, 255, 255);
    //ofEnableLighting();
    
    ofPushMatrix();
    //ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    //ofRotateYRad(ofGetElapsedTimef()/4);
    //ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
    triangulation.draw();
    //ofDrawBox(400, 400, 0, 200, 200, 200);
    
    if(grabbedPointIndex > -1){
        
        ofFill();
        ofSetColor(255, 255, 255, 100);
        ofDrawBox(grabbedPoint.x, grabbedPoint.y, 0, 10, 10,10);
        ofSetColor(255, 255, 255);
    }
    
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
    
    if(key == 'j'){
        std::cout << triangulation.getAsJson() << std::endl;
    }
    
    if(key == 's'){
        save();
    }
    
    if(key == 'l'){
        load();
    }
    
    if(key == 8){
        if(grabbedPointIndex > -1)
            grabbedPointShouldBeDeleted = true;
    }
    
}

void ofApp::mouseDragged( int x, int y, int button ){
    if(grabbedPointIndex > -1){
        grabbedPoint.x = x;
        grabbedPoint.y = y;
        triangulation.setPointAtIndex(grabbedPoint, grabbedPointIndex);
        grabbedPoint = triangulation.getPointNear(ofDefaultVec3(x,y,0), 30, grabbedPointIndex);
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    if(button == OF_MOUSE_BUTTON_LEFT){
        triangulation.addPoint(ofDefaultVec3(x,y,ofRandom(-20, 20)));
        triangulation.triangulate();
    }
    
    if(button == OF_MOUSE_BUTTON_RIGHT){
        grabbedPoint = triangulation.getPointNear(ofDefaultVec3(x,y,0), 30, grabbedPointIndex);
    }
    
}

void ofApp::save(string name){
    auto j = triangulation.getAsJson();
    //ofSerialize(j, pgRoot);
    ofSaveJson("settings/" + name + ".json", j);
}

void ofApp::load(string name){
    ofJson j = ofLoadJson("settings/" + name + ".json");
    triangulation.setFromJson(j);
}
