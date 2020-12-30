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
    float getX();
    float getY();
    float getZ();
    void draw();

    float x, y, z;
    bool debugDraw = true;
    const float c_len=1,c_wid=1,c_hei=0.1;

    /* ODE objects */
    dBodyID mBody;
    dMass   mMass;
    dGeomID mGeom;

    /* The 3D model */
    ofxAssimpModelLoader mModel;
    ofQuaternion mRotation;
};

#endif // PANDAPLAYER_H
