#include "ode/ode.h"
#include "ofApp.h"
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxAssimpAnimation.h"
#include "ball.h"

#ifndef CHEST_H
#define CHEST_H


class Chest
{
public:
    Chest(float x, float y, float z, dWorldID w, dSpaceID s);

    /* Methods */
    void setPosition(float x, float y, float z);
    void disable();
    void draw();

    /* ODE objects */
    dReal pElevation = 0;
    dReal pAngle = 0;
    dBodyID mBody;
    dGeomID mGeom;
    dMass   mMass;

    /* The 3D model */
    ofxAssimpModelLoader mModel;

    bool debugDraw = true;
    bool hit = false;
    bool gone = false;

    const float c_len=1.5,c_wid=1,c_hei=1;
    float x, y, z;
    float speed;
};

#endif // CHEST_H
