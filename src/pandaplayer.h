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
    void draw();

    float getRotX ();
    float getX();
    float getY();
    float getZ();

    const float c_len=1.85,c_wid=1.2,c_hei=1.9;
    float x, y, z;
    float speed;

    bool debugDraw = true;
    bool jump = false;

    dReal pAngle = 0;
    dReal pElevation = 0;

    /* ODE objects */
    dBodyID mBody;
    dGeomID mGeom;
    dMass   mMass;

    /* The 3D model */
    ofxAssimpModelLoader mModel;
};

#endif // PANDAPLAYER_H
