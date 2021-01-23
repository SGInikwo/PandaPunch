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
    void disable();

    void setPosition(float x, float y, float z);

    void draw();

    const float c_len=1.5,c_wid=1,c_hei=1;
    float x, y, z;
    float speed;

    bool debugDraw = true;
    bool hit = false;
    bool gone = false;

    dReal pAngle = 0;
    dReal pElevation = 0;

    /* ODE objects */
    dBodyID mBody;
    dGeomID mGeom;
    dMass   mMass;

    /* The 3D model */
    ofxAssimpModelLoader mModel;
};

#endif // CHEST_H
