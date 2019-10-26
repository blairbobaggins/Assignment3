#pragma once

#include "ofMain.h"
#include "ofxLeapC.h"
#include "ProjectConstants.h"
#include "SpawnZombie.h"
#include "ofxBox2d.h"
class ofApp : public ofBaseApp {

public:
    void setup();
    void update();
    void draw();

	void contactStart(ofxBox2dContactArgs &e);
	void contactEnd(ofxBox2dContactArgs &e);

    SpawnZombie zombie;

	ofVec2f Positionsetup;

	bool followpalm;
	bool letgo;

	ofxBox2dRect handcollisionbox;



    ofxLeapC::Device            m_device;
    Leap::Frame                 m_frame;

    void OnLeapFrame(Leap::Frame frame); // this is where Leap updates all Leap data.
	ofxBox2dJoint				m_joint;
    ofImage                     m_ship;
    ofVec3f                     m_palmPos;
    ofVec3f                     m_palmRot;
    float                       m_pinchstrength;
    float                       m_grabstrength;
    float m_fingers;


    //box2d setup
    ofxBox2d box2d; //box 2d world


};
