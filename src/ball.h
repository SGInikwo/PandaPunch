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

    void setPosition(float x, float y, float z);
    void draw();

    float x, y, z;
    //float offX=0.745,offY=0.4,offZ=1.2;
    bool debugDraw = false;
    const float c_len=1.2,c_wid=1,c_hei=0.7;

    /* ODE objects */
    dBodyID mBody;
    dMass   mMass;
    dGeomID mGeom;

    /* The 3D model */
    ofxAssimpModelLoader mModel;
    ofQuaternion mRotation;


};

#endif // BALL_H
