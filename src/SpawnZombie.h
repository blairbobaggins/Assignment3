#pragma once
#include "ofxBox2D.h";
#include "ofMain.h";

class SpawnZombie : public ofBaseApp
{
public:
    SpawnZombie();
    ~SpawnZombie();
    void setup(const ofxBox2d &worldref);
    void update();
    void draw();


	ofxBox2dRect collisionbox;

	ofxBox2d world;
private:
    ofImage m_ZombieImage;
    ofVec2f m_ZombiePos;
    ofVec2f endpoint;

	
    
    b2Vec2 collisionboxpos;
   // ofxBox2dRect collisionbox;

	ofVec2f temppos;
};