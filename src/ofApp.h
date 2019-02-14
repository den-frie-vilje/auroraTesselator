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

    ofxDelaunay triangulation;

    // GUI

    int grabbedPointIndex = -1;
    ofDefaultVec3 grabbedPoint;
    
    bool grabbedPointShouldBeDeleted = false;
    
    bool imGui();
    ofxImGui::Gui gui;
    string title = "Delaunay Editor for Aurora Project";
    bool mouseOverGui;
    int guiColumnWidth = 250;
    
    ImFont* gui_font_header;
    ImFont* gui_font_text;
    
    ofImage logo;
    GLuint logoID;
    
    void save(string name = "default");
    void load (string name = "default");

   
};
