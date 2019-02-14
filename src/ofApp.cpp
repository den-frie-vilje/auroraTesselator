#include "ofApp.h"
#include "ImGuiUtils.h"

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
    
    ofSetWindowTitle(title);

    
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    gui_font_text = io.Fonts->AddFontFromFileTTF(ofToDataPath("fonts/OpenSans-Regular.ttf").c_str(), 16.0f);
    gui_font_header = io.Fonts->AddFontFromFileTTF(ofToDataPath("fonts/OpenSans-Regular.ttf").c_str(), 22.0f);
    
    gui.setup();
    
    logo.load("images/logo.png");
    logoID = gui.loadImage(logo);
    
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowPadding = ImVec2(14.,14.);
    style.WindowRounding = 4.0f;
    style.ChildWindowRounding = 4.;
    style.FramePadding = ImVec2(8, 4);
    style.FrameRounding = 4;
    style.ItemSpacing = ImVec2(6, 5);
    style.ItemInnerSpacing = ImVec2(7, 4);
    style.IndentSpacing = 18;
    style.ScrollbarRounding = 2;
    
    style.Colors[ImGuiCol_Text]                  = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
    style.Colors[ImGuiCol_TextDisabled]          = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    style.Colors[ImGuiCol_WindowBg]              = ImVec4(0.025f, 0.025f, 0.025f, 0.85f);
    style.Colors[ImGuiCol_ChildWindowBg]         = ImVec4(0.00f, 0.00f, 0.00f, 0.22f);
    style.Colors[ImGuiCol_PopupBg]               = ImVec4(0.05f, 0.05f, 0.05f, 0.90f);
    style.Colors[ImGuiCol_Border]                = ImVec4(0.70f, 0.70f, 0.70f, 0.29f);
    style.Colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_FrameBg]               = ImVec4(0.07f, 0.09f, 0.10f, 0.40f);
    style.Colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.00f, 0.45f, 0.78f, 0.39f);
    style.Colors[ImGuiCol_FrameBgActive]         = ImVec4(0.65f, 0.74f, 0.81f, 0.33f);
    style.Colors[ImGuiCol_TitleBg]               = ImVec4(0.11f, 0.13f, 0.15f, 1.00f);
    style.Colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(0.11f, 0.13f, 0.15f, 1.00f);
    style.Colors[ImGuiCol_TitleBgActive]         = ImVec4(0.24f, 0.29f, 0.32f, 1.00f);
    style.Colors[ImGuiCol_MenuBarBg]             = ImVec4(0.11f, 0.13f, 0.15f, 0.80f);
    style.Colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.05f, 0.07f, 0.08f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.21f, 0.24f, 0.26f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.31f, 0.34f, 0.36f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.11f, 0.13f, 0.15f, 1.00f);
    style.Colors[ImGuiCol_ComboBg]               = ImVec4(0.04f, 0.04f, 0.05f, 1.00f);
    style.Colors[ImGuiCol_CheckMark]             = ImVec4(0.90f, 0.90f, 0.90f, 0.57f);
    style.Colors[ImGuiCol_SliderGrab]            = ImVec4(1.00f, 1.00f, 1.00f, 0.13f);
    style.Colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.00f, 0.45f, 0.78f, 1.00f);
    style.Colors[ImGuiCol_Button]                = ImVec4(0.24f, 0.30f, 0.35f, 0.18f);
    style.Colors[ImGuiCol_ButtonHovered]         = ImVec4(0.00f, 0.45f, 0.78f, 0.39f);
    style.Colors[ImGuiCol_ButtonActive]          = ImVec4(0.00f, 0.45f, 0.78f, 1.00f);
    style.Colors[ImGuiCol_Header]                = ImVec4(0.24f, 0.30f, 0.35f, 0.18f);
    style.Colors[ImGuiCol_HeaderHovered]         = ImVec4(0.00f, 0.45f, 0.78f, 0.39f);
    style.Colors[ImGuiCol_HeaderActive]          = ImVec4(0.00f, 0.45f, 0.78f, 1.00f);
    style.Colors[ImGuiCol_Column]                = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    style.Colors[ImGuiCol_ColumnHovered]         = ImVec4(0.70f, 0.60f, 0.60f, 1.00f);
    style.Colors[ImGuiCol_ColumnActive]          = ImVec4(0.90f, 0.70f, 0.70f, 1.00f);
    style.Colors[ImGuiCol_ResizeGrip]            = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
    style.Colors[ImGuiCol_ResizeGripHovered]     = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
    style.Colors[ImGuiCol_ResizeGripActive]      = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
    style.Colors[ImGuiCol_CloseButton]           = ImVec4(0.00f, 0.00f, 0.00f, 0.50f);
    style.Colors[ImGuiCol_CloseButtonHovered]    = ImVec4(0.00f, 0.45f, 0.78f, 0.39f);
    style.Colors[ImGuiCol_CloseButtonActive]     = ImVec4(0.70f, 0.70f, 0.70f, 1.00f);
    style.Colors[ImGuiCol_PlotLines]             = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_PlotLinesHovered]      = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogram]         = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.00f, 0.56f, 1.00f, 0.35f);
    style.Colors[ImGuiCol_ModalWindowDarkening]  = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
    
    // PARAMETERS
    
    load("default");

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
    
    
    // GUI
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofFill();
    ofSetColor(255,255);
    this->mouseOverGui = this->imGui();
    if (this->mouseOverGui) {
//        cam.disableMouseInput();
    } else {
//        cam.enableMouseInput();
    }
    
   
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
        if(!mouseOverGui){
           triangulation.addPoint(ofDefaultVec3(x,y,ofRandom(-20, 20)));
            triangulation.triangulate();
        }
    }
    
    if(button == OF_MOUSE_BUTTON_RIGHT){
        if(!mouseOverGui){
        grabbedPoint = triangulation.getPointNear(ofDefaultVec3(x,y,0), 30, grabbedPointIndex);
        }
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


bool ofApp::imGui()
{
    //TODO: Merge GUI code from Ole
    
    auto mainSettings = ofxImGui::Settings();
    
    ofDisableDepthTest();
    
    this->gui.begin();
    {
        ImGui::PushFont(gui_font_text);
        
        ImGuiWindowFlags window_flags = 0;
        window_flags |= ImGuiWindowFlags_NoCollapse;
        
        if (ofxImGui::BeginWindow(title.c_str(), mainSettings, window_flags)){
            
            // DFV Header
            
            ImGui::Columns(2, "TitleColumns", false);
            ImGui::PushFont(gui_font_header);
            ImGui::TextUnformatted(title.c_str());
            ImGui::PopFont();
            ImGui::TextUnformatted("(c) den frie vilje 2019");
            ImGui::Text("FPS %.3f", ofGetFrameRate());
            int logoSize = 60;
            ImGui::SetColumnOffset(1, ImGui::GetWindowContentRegionMax().x - (logoSize + 7));
            ImGui::NextColumn();
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.8);
            ImGui::Image((ImTextureID)(uintptr_t)logoID, {static_cast<float>(logoSize),static_cast<float>(logoSize)});
            ImGui::PopStyleVar();
            ImGui::Columns(1);
            
/*
            if(!selection){
                ImGui::Separator();
                ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "CONNECT CAMERA AND RESTART APP");
            }
  */
            ImGui::Separator();
            
            if(ImGui::Button("Load")){
                load("default");
            } ImGui::SameLine();
            if(ImGui::Button("Save")){
                save("default");
            }
            
            //*
             static bool guiShowTest;
             ImGui::Checkbox("Show Test Window", &guiShowTest);
             if(guiShowTest)
             ImGui::ShowTestWindow();
             //*/
            
            ImGui::Separator();
            
            int columnOffset = 200;
            
            /*
            if(ofxImGui::BeginTree("Head Tracker OSC", mainSettings)){
                
                ImGui::Columns(2, "HeadTrackerOSCColumns", false);
                
                string strHost = pOscTrackingRemoteHost.get();
                if(ImGui::InputTextFromString("Remote Host", strHost, ImGuiInputTextFlags_CharsNoBlank)){
                    pOscTrackingRemoteHost.set(strHost);
                }
                
                ImGui::SetColumnOffset(1, ImGui::GetWindowContentRegionMax().x - columnOffset);
                
                ImGui::NextColumn();
                
                string strPort = ofToString(pOscTrackingRemotePort.get());
                if(ImGui::InputTextFromString("Remote Port", strPort, ImGuiInputTextFlags_CharsDecimal)){
                    pOscTrackingRemotePort.set(ofToInt(string(strPort)));
                }
                
                ImGui::Columns(1);
                
                ofxImGui::EndTree(mainSettings);
            }
            
            if(ofxImGui::BeginTree("qLab OSC", mainSettings)){
                
                ImGui::Columns(2, "qLabOscColumns", false);
                
                string strHost = pOscQlabRemoteHost.get();
                if(ImGui::InputTextFromString("Remote Host", strHost, ImGuiInputTextFlags_CharsNoBlank)){
                    pOscQlabRemoteHost.set(strHost);
                }
                
                ImGui::SetColumnOffset(1, ImGui::GetWindowContentRegionMax().x - columnOffset);
                
                ImGui::NextColumn();
                
                string strPort = ofToString(pOscQlabRemotePort.get());
                if(ImGui::InputTextFromString("Remote Port", strPort, ImGuiInputTextFlags_CharsDecimal)){
                    pOscQlabRemotePort.set(ofToInt(string(strPort)));
                }
                
                ImGui::Columns(1);
                
                ImGui::Columns(2, "qLabOscRemote", false);
                
                ImGui::SetColumnOffset(1, ImGui::GetWindowContentRegionMax().x - columnOffset);
                
                ImGui::NextColumn();
                
                string strPortReply = ofToString(pOscQlabReplyPort.get());
                if(ImGui::InputTextFromString("Reply Port", strPortReply, ImGuiInputTextFlags_CharsDecimal)){
                    pOscQlabReplyPort.set(ofToInt(string(strPortReply)));
                }
                
                ImGui::Columns(1);
                
                ofxImGui::EndTree(mainSettings);
            }
            */
            
            /*
             for (auto pg : pgRoot){
             ofxImGui::AddGroup(pg->castGroup(), mainSettings);
             }
             */
            
//            ofxImGui::AddGroup(pgTracking, mainSettings);
            
            ofxImGui::EndWindow(mainSettings);
        }
        
    }
    
    ImGui::PopFont();
    
    this->gui.end();
    
    return mainSettings.mouseOverGui;
}
