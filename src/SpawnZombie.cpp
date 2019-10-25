#include "SpawnZombie.h"

SpawnZombie::SpawnZombie()
{


}
SpawnZombie::~SpawnZombie()
{

}
void SpawnZombie::setup(const ofxBox2d &worldref)
{
    m_ZombieImage.loadImage("Images/zombie2.png");
    m_ZombiePos.set(100, ofRandom(100, 500));
    endpoint.set(1000, m_ZombiePos.y);

	//collisionchecker = false;



    world = worldref;



    //temppos = world.toB2d(m_ZombiePos.x, m_ZombiePos.y);
	collisionbox.setPhysics(3.0, 0.1, 1.5);
    collisionbox.setup(world.getWorld(), 400, 500, 91.5f, 152.0f, 0.0f);
	

}

void SpawnZombie::update()
{
    ofVec2f ZombieToEnd = endpoint - collisionbox.getPosition();


	
	collisionbox.update();
	collisionbox.setRotation(0);
	m_ZombieImage.resize(collisionbox.getWidth(), collisionbox.getHeight());
	//cout << collisionbox.getVelocity() << endl;
}
void SpawnZombie::draw()
{
	collisionbox.draw();
    ofPushMatrix();
        
        //ofScale(0.3);
		//ofRotate(collisionbox.getRotation());
		ofTranslate(collisionbox.getPosition());
		m_ZombieImage.draw(0,0);
    ofPopMatrix();
	//cout << "Temp Pos " << temppos << endl;

}

