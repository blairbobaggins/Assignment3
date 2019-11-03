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
	void SwapSprite();
	float Lerp(float start, float end, float percent);
	ofxBox2dRect collisionbox;

	ofxBox2d world;

	int cooldowntimer;
	bool isdead;

	bool isgrabbed;

private:
    ofImage m_ZombieImage;
    ofVec2f m_ZombiePos;
    ofVec2f endpoint;

	int tempx;
	int tempy;
    
    b2Vec2 collisionboxpos;
   // ofxBox2dRect collisionbox;

	ofVec2f temppos;
};