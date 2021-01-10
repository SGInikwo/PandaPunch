#include "ode/ode.h"
#include "ofApp.h"
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxAssimpAnimation.h"
#include "ball.h"

#ifndef PANDAPLAYER_H
#define PANDAPLAYER_H


class PandaPlayer
{
public:
    PandaPlayer(float x, float y, float z, dWorldID w, dSpaceID s);

    void setPosition(float x, float y, float z);
    void setRotY (float pAngle);
    void setSpeed(float speed);
    void setZ(float z);
    //void update();
    void draw();
    float getRotX ();
    float getX();
    float getY();
    float getZ();


    const float c_len=2,c_wid=2,c_hei=2;
    bool debugDraw = true;
    float x, y, z;
    float speed;

    dReal pAngle = 0;
    dReal pElevation = 0;


    /* ODE objects */
    dBodyID mBody;
    dMass   mMass;
    dGeomID mGeom;

    /* The 3D model */
    ofxAssimpModelLoader mModel;

};

#endif // PANDAPLAYER_H
