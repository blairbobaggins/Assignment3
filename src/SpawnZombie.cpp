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
    


    world = worldref;

	collisionbox.setPhysics(3.0, 0.1, 1.5);
    collisionbox.setup(world.getWorld(), ofRandom(10, 100), ofRandom(100, 600), 91.5f, 152.0f, 0.0f);
	collisionbox.setLinearDamping(1.0f);
	endpoint.set(2400, collisionbox.getPosition().y);
}

void SpawnZombie::update()
{
    ofVec2f ZombieToEnd = endpoint - collisionbox.getPosition();

	
	collisionbox.update();
	collisionbox.setRotation(0);
	m_ZombieImage.resize(collisionbox.getWidth(), collisionbox.getHeight());
	collisionbox.setPosition(Lerp(collisionbox.getPosition().x, ZombieToEnd.x, 0.0003f),
		Lerp(collisionbox.getPosition().y, ZombieToEnd.y, 0.0003f));
}
void SpawnZombie::draw()
{
	collisionbox.draw();
    ofPushMatrix();
		ofTranslate(collisionbox.getPosition());
		m_ZombieImage.draw(0,0);
    ofPopMatrix();
	//cout << "Temp Pos " << temppos << endl;

}
float SpawnZombie::Lerp(float start, float end, float percent)
{
	return(start + percent * (end - start));
}
