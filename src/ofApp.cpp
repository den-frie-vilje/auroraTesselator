#include "ofApp.h"

//TODO: Draw vertices as points
//TODO: Select a vertice by click
//TODO: Delete selected vertice
//TODO: Drag selected vertice individually in the xy plane

//TODO: interface for 'extruding' z axis randomly within min/max z
//TODO: lock the z axis of vertices

//TODO: save and load mesh and vertices (collada (.dae)/.ply ?)
//TODO: ofparameters for settings that are in a group that saves to a json file.

//TODO: wrap to geometry...?

int numOfPoints;
XYZI pointGrabbed;


//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableSmoothing();
    ofBackground(0);
    ofSetSmoothLighting(true);
    ofSetFrameRate(60);
    
}

//--------------------------------------------------------------
void ofApp::update(){
   
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
    selectPoint();
    
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
    
    if(key == 8){
        
        deletePoint();
      
  
    }
    

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
   
    if(button == 0){
        triangulation.addPoint(ofDefaultVec3(x,y,ofRandom(-20, 20)));
    triangulation.triangulate();
     //cout << triangulation.getNumPoints();
    }
    
    if(button == 2){
        
    

    }
    
}

void ofApp::selectPoint(){
  
    
    if(ofGetMousePressed(OF_MOUSE_BUTTON_RIGHT)){
        
        
        numOfPoints = triangulation.getNumPoints();
        
        pointGrabbed = triangulation.getPointNear(ofDefaultVec3(ofGetMouseX(),ofGetMouseY(),0), 30, numOfPoints);
        //ofSetRectMode(OF_RECTMODE_CENTER);
        ofFill();
        ofSetColor(255, 255, 255, 100);
        ofDrawBox(pointGrabbed.x, pointGrabbed.y, 0, 10, 10,10);
        ofSetColor(255, 255, 255);
        
        
        // cout << ", nearest point: " << pointGrabbed.x << ", " << pointGrabbed.y << ", " << pointGrabbed.z << ". "
        // << "at index: " << pointGrabbed.i << ". ";
        
    }
    
}

void ofApp::deletePoint(){
    
    numOfPoints = triangulation.getNumPoints();
    //cout << numOfPoints;
    
    if (numOfPoints > 3){
        pointGrabbed = triangulation.getPointNear(ofDefaultVec3(ofGetMouseX(),ofGetMouseY(),0), 25, numOfPoints);
        triangulation.removePointAtIndex(pointGrabbed.i);
        //triangulation.triangulate();
        //cout << "point deleted";
    }
    
}



void ofApp::save(string name){
    ofJson j;
    //ofSerialize(j, pgRoot);
    ofSaveJson("settings/" + name + ".json", j);
}

void ofApp::load(string name){
    ofJson j = ofLoadJson("settings/" + name + ".json");
   // ofDeserialize(j, pgRoot);
}
