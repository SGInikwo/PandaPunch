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
   ~Ball();

    void setPosition(float x, float y, float z);
    void setRotY (float pAngle);
    void setSpeed(float speed);
    void update();
    void draw();

    float x, y, z;
    //float offX=0.745,offY=0.4,offZ=1.2;
    bool debugDraw = true;
    const float c_rad=.085;

    /* ODE objects */
    dBodyID mBody;
    dMass   mMass;
    dGeomID mGeom;

    float speed;

    dReal pAngle = 0;

    /* The 3D model */
    ofxAssimpModelLoader mModel;
    ofQuaternion mRotation;
};

#endif // BALL_H
