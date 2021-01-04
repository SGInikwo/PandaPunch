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
    //ofQuaternion getQuat(float* odeRot);
    void draw();
    void setX(float speed);
    void setY(float speed);
    void setRotX (float pAngle);
    float getRotX ();
    //glm::quat
    void setZ(float z);
    void update();
    //void control(int key);
    float getX();
    float getY();
    float getZ();
    float rotationAmount;

    float x, y, z;
    float d[4];
    const dReal* odeRot;
    dReal pAngle = 0;
    dReal pElevation = 0;
    float speed;
    bool debugDraw = true;
    const dReal* oderot;
    const float c_len=1,c_wid=1,c_hei=0.01;



    /* ODE objects */
    dBodyID mBody;
    dMass   mMass;
    dGeomID mGeom;

    /* The 3D model */
    ofxAssimpModelLoader mModel;
    ofQuaternion mRotation;
    ofQuaternion rRotation;
    ofVec3f rotationAngle;
};

#endif // PANDAPLAYER_H
