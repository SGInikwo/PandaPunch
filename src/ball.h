#include "ode/ode.h"
#include "ofApp.h"
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxAssimpAnimation.h"

#ifndef BALL_H
#define BALL_H


class Ball
{
public:
    Ball(float x, float y, float z, dWorldID w, dSpaceID s);

    /* ODE objects */
    dBodyID mBody;
    dMass   mMass;
    dGeomID mGeom;

    /* The 3D model */
    ofxAssimpModelLoader mModel;

    /* Attributes of this object */
    float x, y, z;
    ofQuaternion mRotation;

    void setPosition(float x, float y, float z);
    void draw();

    bool debugDraw = true;

    /* The length, width, height of the pallet */
    const float c_len=1,c_wid=1,c_hei=0.1;
};

#endif // BALL_H
