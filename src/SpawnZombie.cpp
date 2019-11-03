#include "SpawnZombie.h"

SpawnZombie::SpawnZombie()
{


}
SpawnZombie::~SpawnZombie()
{

}
//sets up the zombies image
void SpawnZombie::setup(const ofxBox2d &worldref)
{
	//loads the image of the zombie
    m_ZombieImage.loadImage("Images/zombie.png");
	//sets the zombies position
    m_ZombiePos.set(100, ofRandom(100, 500));
	//initializes the cooldown timer
	cooldowntimer = 0;
	
	//saves a copy of the world for initializing collision boxes
    world = worldref;



    //creates the zombies collision box
	collisionbox.setPhysics(3.0, 0.1, 1.5);
    collisionbox.setup(world.getWorld(), 100, ofRandom(100, 500), 91.5f, 152.0f, 0.0f);
	endpoint.set(1000, 1000);
	

}

void SpawnZombie::update()
{
	//if the zombie is not dead, update the collision box and keep the image on the zombie
	if (!isdead)
	{
		collisionbox.update();
		collisionbox.setRotation(0);
		m_ZombieImage.resize(collisionbox.getWidth(), collisionbox.getHeight());
	}
	//if the zombie is dead, move the collision box off screen and wait for respond
	if (isdead)
	{
		m_ZombieImage.resize(collisionbox.getWidth(), collisionbox.getHeight());
		collisionbox.setPosition(-1000, -1000);
	}
	//respawn timer
	if (cooldowntimer > 0)
	{
		cooldowntimer--;
	}
	//when the respawn timer is done, respawn the zombie
	else if (cooldowntimer <= 0 && isdead)
	{
		isdead = false;
		collisionbox.setPosition(ofRandom(100, 500), ofRandom(100, 500));
		collisionbox.setVelocity(0, 0);
		SwapSprite();
	}
}
void SpawnZombie::draw()
{
	//collisionbox.draw();
	//if the zombie is alive, move the image with the collision box
	if (!isdead)
	{
		ofPushMatrix();
			ofTranslate(collisionbox.getPosition());
			m_ZombieImage.draw(0, 0);
		ofPopMatrix();
	}
	//if the zombie is dead, draw the zombie at the place it died and wait to respawn
	if (isdead)
	{
		ofPushMatrix();

			m_ZombieImage.draw(tempx, tempy);
		ofPopMatrix();
	}
}
//swaps a sprite depending on if the zombie is alive or dead
void SpawnZombie::SwapSprite()
{
	tempx = collisionbox.getPosition().x;
	tempy = collisionbox.getPosition().y;
	if (isdead)
	{
		m_ZombieImage.loadImage("Images/Empty.png");
	}
	if (!isdead)
	{
		m_ZombieImage.loadImage("Images/zombie.png");
	}
}