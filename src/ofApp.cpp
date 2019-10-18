#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    //initiate program
    m_ship.load(ProjectConstants::IMG_PATH_SHIP);
    ofSetRectMode(OF_RECTMODE_CENTER); // center pivot point on all images.
    //setup window
    ofSetWindowShape(ProjectConstants::PROJ_WINDOW_RES_X, ProjectConstants::PROJ_WINDOW_RES_Y);
    //connect "this"'s leapUpdate function to m_device. This refers to this class.
    m_device.connectEventHandler(&ofApp::OnLeapFrame, this);

    box2d.init();

    box2d.setGravity(0, 10);
  

    zombie.setup(box2d);
    zombie2.setup(box2d);



}

//--------------------------------------------------------------
void ofApp::update()
{
    box2d.update();

    m_device.update(); //update Leap device.

    // get an array of hands that are in frame. 
    const Leap::HandList &hands = m_frame.hands();

    //loop through hands and get palm position
    for (int i = 0; i < hands.count(); i++)
    {
        const Leap::Hand & hand = hands[i]; //Get out hand (a reference to our hands
        const Leap::Vector palmPos = hand.palmPosition(); //get our palm position
        const ofVec3f ofPalmPos = ofxLeapC::toVec3(palmPos); //convert to OF
        m_palmRot = ofVec3f(ofRadToDeg(hand.direction().pitch()), //rotate x
            ofRadToDeg(hand.direction().yaw())), // rotate y
            ofRadToDeg(hand.direction().roll()); // rotate z
        m_palmPos = ofPalmPos;
        cout << hand.pinchStrength() << endl;
        m_pinchstrength = hand.pinchStrength();
        m_grabstrength = hand.grabStrength();

        //m_fingers = hand.fingers().fingerType(LEAP_VE
        //find some scaling that works to get across the screen
        m_palmPos.x *= 7.0f;
        m_palmPos.z *= 5.0f;

        m_palmPos.x = ofClamp(m_palmPos.x, -(float)ProjectConstants::PROJ_WINDOW_RES_X / 2.0f, (float)ProjectConstants::PROJ_WINDOW_RES_X / 2.0f);
        m_palmPos.z = ofClamp(m_palmPos.z, -(float)ProjectConstants::PROJ_WINDOW_RES_Y / 2.0f, (float)ProjectConstants::PROJ_WINDOW_RES_Y / 2.0f);

        m_palmPos.x += (float)ProjectConstants::PROJ_WINDOW_RES_X / 2.0f;
        m_palmPos.z += (float)ProjectConstants::PROJ_WINDOW_RES_Y / 2.0f;


        break; // if you only
    }

    zombie.update();
    zombie2.update();


}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofClear(ofFloatColor(m_grabstrength, 0.0f, 0.0f));
    ofPushMatrix();
        ofTranslate(m_palmPos.x, m_palmPos.z);
        ofRotateDeg(m_palmRot.y);
        ofScale(m_pinchstrength + 0.5f, m_pinchstrength + 0.5f, m_pinchstrength + 0.5f);
        m_ship.draw(0, 0);
    ofPopMatrix();

    zombie.draw();
    zombie2.draw();

}

void ofApp::OnLeapFrame(Leap::Frame frame)
{
    m_frame = frame;
}

