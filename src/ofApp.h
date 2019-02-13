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
    void mouseDragged( int x, int y, int button );
    void deletePoint();

    void save(string name = "default");
    void load (string name = "default");
    ofxDelaunay triangulation;

    int grabbedPointIndex = -1;
    ofDefaultVec3 grabbedPoint;
    
    bool grabbedPointShouldBeDeleted = false;
   
};
