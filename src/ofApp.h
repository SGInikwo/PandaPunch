#pragma once

#include "ofMain.h"
#include "ode/ode.h"
#include "pandaplayer.h"

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

    ofEasyCam cam;

    /* These variables are straight from demo_buggy.cpp */
    dWorldID world;
    dSpaceID space;
    dJointGroupID contactgroup;
    dGeomID ground;

    void collide (dGeomID o1, dGeomID o2);

    /* A ground plane in graphics */
    ofPlanePrimitive mGround;

    /* A texture for it */
    ofTexture mGroundTex;

    /* A light */
    ofLight light;

    /* A vector of pallets */
    PandaPlayer* panda;

};

static void nearCallback (void *, dGeomID o1, dGeomID o2);
extern ofApp *myApp;
