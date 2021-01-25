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

    /* Methods */
    void setPosition(float x, float y, float z);
    void setRotY (float pAngle);
    void setSpeed(float speed);
    void update();
    void draw();

    /* ODE objects */
    dReal pAngle = 0;
    dBodyID mBody;
    dMass   mMass;
    dGeomID mGeom;

    /* The 3D model */
    ofxAssimpModelLoader mModel;
    ofQuaternion mRotation;

    bool debugDraw = true;

    const float c_rad=.2194;
    float x, y, z;
    float speed;
};

#endif // BALL_H
