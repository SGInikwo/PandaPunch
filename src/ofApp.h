#pragma once

#include "ofMain.h"
#include "ode/ode.h"
#include "pandaplayer.h"
#include "ball.h"

#include "ofxAssimpModelLoader.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void exit();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void collide (dGeomID o1, dGeomID o2);

    unsigned int keys[65536];

    /* These variables are straight from demo_buggy.cpp */
    dWorldID world;
    dSpaceID space;
    dJointGroupID contactgroup;
    dGeomID ground;

    ofEasyCam camera;
    ofCamera cam;
    ofPlanePrimitive mGround;
    ofTexture mGroundTex;
    ofLight light;

    /* A vector of pallets */
    PandaPlayer* panda;
    Ball* ball;

    bool seeBall = false;
    bool fireBall = false;
    bool fireon = true;

    float angle;


};

static void nearCallback (void *, dGeomID o1, dGeomID o2);
extern ofApp *myApp;
