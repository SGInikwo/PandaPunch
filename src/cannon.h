#include "ode/ode.h"
#include "ofApp.h"
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxAssimpAnimation.h"

#ifndef CANNON_H
#define CANNON_H


class Cannon
{
public:
    Cannon(float x, float y, float z, dWorldID w, dSpaceID s);

    void setPosition(float x, float y, float z);
    void setBallPosition(float bX, float bY, float bZ);
    void setSpeed(float speed);
    void draw();
    void drawBall();
    void ballSetup(float x, float y, float z, dWorldID w, dSpaceID s);
    void disable();

    const float c_len=2.5,c_wid=2.5,c_hei=2.3;
    const float c_rad=.4;
    float x, y, z;
    float bX, bY, bZ;
    float speed;

    bool debugDraw = true;
    bool hit = false;
    bool ball = false;
    bool gone = false;

    dReal pAngle = 0;
    dReal pElevation = 0;

    /* ODE objects */
    dBodyID mBody;
    dBodyID bBody;
    dGeomID mGeom;
    dGeomID bGeom;
    dMass   mMass;
    dMass   bMass;

    /* The 3D model */
    ofxAssimpModelLoader mModel;
};

#endif // CANNON_H
