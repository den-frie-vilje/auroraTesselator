#pragma once

#include "ofMain.h"
#include "ofxDelaunay.h"
#include "ofxImGui.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    void selectPoint();
    void deletePoint();

    void save(string name);
    void load (string name);
    ofxDelaunay triangulation;

    ofDefaultVec3 pointGrabbed;
    
   
};
