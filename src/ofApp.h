#pragma once

#include "ofMain.h"
#include "ode/ode.h"
#include "pandaplayer.h"
#include "ball.h"
#include "chest.h"
#include "cannon.h"

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

    void level1Setup();
    void level1Update();
    void level1Draw();
    void level1Exit();

    void end1Setup();
    void end1Draw();

    void cannonLogic();

    unsigned int keys[65536];

    /* These variables are straight from demo_buggy.cpp */
    dWorldID world;
    dSpaceID space;
    dJointGroupID contactgroup ;
    dGeomID ground;

    ofEasyCam camera;
    ofCamera cam;
    ofPlanePrimitive mGround;
    ofTexture mGroundTex;
    ofLight light;
    ofLight light2;
    ofLight light3;
    ofLight light4;
    ofLight light5;
    ofImage bgImage;
    ofImage shieldIm;
    ofImage pointIm;
    ofImage trophyIm;
    ofTrueTypeFont healthTex;
    ofTrueTypeFont upTex;
    ofTrueTypeFont shieldsTex;
    ofTrueTypeFont pointsTex;
    ofTrueTypeFont endTex;

    dGeomID ground_box;

    /* A vector of pallets */
    PandaPlayer* panda;
    Ball* ball;
    //Cannon* cannon;

    vector<Cannon*> canList;
    vector<Chest*> chests;

    bool seeBall = false;
    bool fireBall = false;
    bool fireon = true;
    bool move = false;
    bool ballCol = false;
    bool shoot = false;
    bool there = false;
    bool already = false;
    bool travel = true;
    bool isShield = false;
    bool isPoint = false;
    bool is2Point = false;
    bool gotTrophy = false;
    bool loseHealth = true;
    bool shieldPress = true;
    bool shieldEnd = false;
    bool runShield = false;
    bool toStart = false;

    int health = 100;
    int points = 0;
    int shields = 0;
    int pointTime;
    int point2Time;
    int shieldTime;
    int healthTime;

    //loat lastTime;
    float currentTime;
};

static void nearCallback (void *, dGeomID o1, dGeomID o2);
extern ofApp *myApp;
