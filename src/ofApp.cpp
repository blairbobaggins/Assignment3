#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    //initiate program
	m_hand.load(ProjectConstants::IMG_PATH_SHIP);
	
    ofSetRectMode(OF_RECTMODE_CENTER); // center pivot point on all images.
    //setup window
    ofSetWindowShape(ProjectConstants::PROJ_WINDOW_RES_X, ProjectConstants::PROJ_WINDOW_RES_Y);
    //connect "this"'s leapUpdate function to m_device. This refers to this class.
    m_device.connectEventHandler(&ofApp::OnLeapFrame, this);
	Leap::Hand handcheck;


	//Initialing the box2d world
    box2d.init();
	box2d.enableEvents();
    box2d.setGravity(0.1, 0);
	box2d.setFPS(60.0);
	box2d.registerGrabbing();
	box2d.createBounds(0, 0, ProjectConstants::PROJ_WINDOW_RES_X, ProjectConstants::PROJ_WINDOW_RES_Y);
	
	//seting up the zombie
	zombie.setup(box2d);

	//initializing the score
	score = 0;

	//initializing the checks to see if the collision boxes have been created
	pinchcollisionboxcreated = false;
	grabcollisionboxcreated = false;

	
	

	//initializing the collision listener events
	ofAddListener(box2d.contactStartEvents, this, &ofApp::contactStart);
	ofAddListener(box2d.contactEndEvents, this, &ofApp::contactEnd);
	followpalm = false;
	letgo = false;
}

//--------------------------------------------------------------
void ofApp::update()
{
	//updates the box2d world
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

        //saves the pinch/grab strength to a variable
        m_pinchstrength = hand.pinchStrength();
        m_grabstrength = hand.grabStrength();

        
        //find some scaling that works to get across the screen
        m_palmPos.x *= 7.0f;
        m_palmPos.z *= 5.0f;

        m_palmPos.x = ofClamp(m_palmPos.x, -(float)ProjectConstants::PROJ_WINDOW_RES_X / 2.0f, (float)ProjectConstants::PROJ_WINDOW_RES_X / 2.0f);
        m_palmPos.z = ofClamp(m_palmPos.z, -(float)ProjectConstants::PROJ_WINDOW_RES_Y / 2.0f, (float)ProjectConstants::PROJ_WINDOW_RES_Y / 2.0f);

        m_palmPos.x += (float)ProjectConstants::PROJ_WINDOW_RES_X / 2.0f;
        m_palmPos.z += (float)ProjectConstants::PROJ_WINDOW_RES_Y / 2.0f;

		//checks to see if followpalm is turned on. Checks to see if the zombie is suppose to follow the hand
		if (followpalm )
		{
			//creates a joint between the pinch collision box and the zombies body
			m_joint.setup(box2d.getWorld(), pinchcollisioncircle.body, zombie.collisionbox.body, 1.0f, 0.5f, false);
			m_joint.setLength(5);
			zombie.isgrabbed = true;
		
		}
		//checks to see if the pinch/grab strength are less than a threshold to destroy the joint
		else if (letgo && m_pinchstrength <= 0.75 && m_grabstrength <= 0.75)
		{
			//makes sure the joint is alive before destroying it
			if (!m_joint.joint)
			{
				//destroys the join
				m_joint.destroy();
				zombie.isgrabbed = false;
			}
			
		}
        break; // if you only have 3 hands
    }
	
	//if the pinch strength is a certain threshold, create a collisionbox that follows the palms position
	if (m_pinchstrength >= 0.75 && m_grabstrength <= 0.20)
	{
		//makes sure the collision box isn't created, if it isn't create one, then no more
		if (!pinchcollisionboxcreated)
		{
			pinchcollisioncircle.setPhysics(10.0, 0.1, 1.5);
			pinchcollisioncircle.setup(box2d.getWorld(), 400, 500, 50, false);
			pinchcollisionboxcreated = true;
			m_hand.loadImage("Images/pinch.png");

		}
		//the collisionbox always follows the palms position
		pinchcollisioncircle.setRotation(0);
		pinchcollisioncircle.setPosition(m_palmPos.x, m_palmPos.z);
	}
	//checks the grab strength, if it's over a certain threshold, create a collision box
	else if (m_grabstrength >= 0.90&& m_pinchstrength <= 0.20)
	{
		//makes sure the collision box isn't created, if it isn't create one, then no more
		if (!grabcollisionboxcreated)
		{
			GrabcollisionBox.setPhysics(10.0, 5.0, 1.5);
			GrabcollisionBox.setup(box2d.getWorld(), 0, 0, 200, 200, false);
			grabcollisionboxcreated = true;
			m_hand.loadImage("Images/fist.png");
		}
		//the collisionbox always follows the palms position
		GrabcollisionBox.setPosition(m_palmPos.x, m_palmPos.z);

	}
	else
	{
		//if grab or pinch strength is below a threshold and either box has been created, destroy the box. If they aren't created
		//ignore. also swaps the hand sprites to neutral
		if (grabcollisionboxcreated)
		{
			GrabcollisionBox.destroy();
			grabcollisionboxcreated = false;
			m_hand.loadImage("Images/neutral.png");
		}
		
		if (pinchcollisionboxcreated)
		{
			pinchcollisioncircle.destroy();
			pinchcollisionboxcreated = false;
			m_hand.loadImage("Images/neutral.png");
		}
		zombie.isgrabbed = false;
		followpalm = false;
		letgo = true;
		
	}
	//update the zombie
	zombie.update();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	//draw the score
	ofPushMatrix();
		ofSetColor(0, 0, 0);
		ofDrawRectangle(10, 300, 150, 80);
		ofSetColor(255, 255, 255);
		ofDrawBitmapString("Score: " + ofToString(score), 10, 300);
	ofPopMatrix();
	//draw the hand
    ofPushMatrix();
        ofTranslate(m_palmPos.x, m_palmPos.z);
        ofRotateDeg(m_palmRot.y);
		ofScale(0.5);
		m_hand.draw(0, 0);
    ofPopMatrix();
	
	//pinchcollisioncircle.draw();
	//GrabcollisionBox.draw();
	//draw the zombie
	zombie.draw();
    
}

void ofApp::OnLeapFrame(Leap::Frame frame)
{
    m_frame = frame;
}
void ofApp::contactStart(ofxBox2dContactArgs &e)
{
	//makes sure both objects that collided are not null
	if (e.a != NULL && e.b != NULL)
	{
		//checks to see if the zombie collided with the palm. The zombie being the polygon and the palm being the circle
		if (e.a->GetType() == b2Shape::e_polygon && e.b->GetType() == b2Shape::e_circle &&
			m_pinchstrength >= 0.75)
		{
			followpalm = true;
			letgo = false;
		}
		//checks to see if the zombie collides witht he grab, or fist
		else if (e.a->GetType() == b2Shape::e_polygon && e.b->GetType() == b2Shape::e_polygon &&
			letgo, !zombie.isdead, !zombie.isgrabbed && m_grabstrength >= 0.75)
		{
			//can sometimes cause a null ref if the leap motion jitters and stops detecting the hand.I'm unsure as to how we'd
			//go about fixing it
			if (!GrabcollisionBox.body)
			{
				zombie.collisionbox.addRepulsionForce(GrabcollisionBox.getVelocity(), 100.0f);
			}
		}
		//checks to see if the zombies collides with an edge and it's not being held
		if (e.a->GetType() == b2Shape::e_edge && e.b->GetType() == b2Shape::e_polygon &&
			letgo && !zombie.isdead  && m_pinchstrength <= 0.75)
		{
			//makes the zombie "dead" 
			zombie.isgrabbed = false;
			score++;
			zombie.isdead = true;
			zombie.SwapSprite();
			zombie.cooldowntimer = 100;
		}
		
	}
}
void ofApp::contactEnd(ofxBox2dContactArgs &e)
{
	if (e.a != NULL && e.b != NULL)
	{
		//when the zombie stops colliding with the pinch, do this
		if (followpalm && !letgo)
		{
			followpalm = false;
			letgo = true;			
		}
		
	}
}
