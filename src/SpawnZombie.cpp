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
    endpoint.set(2400, m_ZombiePos.y);

    b2Vec2 temppos;



    world = worldref;

    temppos = world.toB2d(m_ZombiePos.x, m_ZombiePos.y);

    collisionbox.setup(world.getWorld(), temppos.x, temppos.y, 183.0f, 304.0f, 0.0f);

}

void SpawnZombie::update()
{
    ofVec2f ZombieToEnd = endpoint - m_ZombiePos;

    collisionboxpos = world.toB2d(m_ZombiePos.x, m_ZombiePos.y);

    m_ZombiePos.x = Lerp(m_ZombiePos.x, ZombieToEnd.x, 0.003f);
    m_ZombiePos.y = Lerp(m_ZombiePos.y, ZombieToEnd.y, 0.003f);

    collisionbox.addAttractionPoint(collisionboxpos.x, collisionboxpos.y, 100);

}
void SpawnZombie::draw()
{

    ofTranslate(m_ZombiePos);
    ofScale(0.3);
    collisionbox.draw();
    m_ZombieImage.draw(0, 0);
}
float SpawnZombie::Lerp(float start, float end, float percent)
{
    return(start + percent * (end - start));
}
void SpawnZombie::CollisionDetection(ofxBox2dRect other)
{

}