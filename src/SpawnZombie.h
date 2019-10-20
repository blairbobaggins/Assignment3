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
	void contactStart(ofxBox2dContactArgs &e);
	void contactEnd(ofxBox2dContactArgs &e);


    void CollisionDetection(ofxBox2dRect other);

private:
    ofImage m_ZombieImage;
    ofVec2f m_ZombiePos;
    ofVec2f endpoint;

	
    ofxBox2d world;
    b2Vec2 collisionboxpos;
    ofxBox2dRect collisionbox;

	ofVec2f temppos;
};