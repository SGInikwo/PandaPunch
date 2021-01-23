#include "ball.h"

Ball::Ball(float x, float y, float z, dWorldID w, dSpaceID s)
{
    /* Set our x,y,z variables */
    this->x=x; this->y=y; this->z=z;

    /* Set up physics objects */
    mBody = dBodyCreate(w);
    dBodySetPosition(mBody, x, y, z);
    dBodySetGravityMode(mBody,0);
    dMassSetSphere(&mMass,1,c_rad);
    dMassAdjust (&mMass,0.01);
    dBodySetMass (mBody,&mMass);
    mGeom = dCreateSphere(s,c_rad);
    dGeomSetBody (mGeom, mBody);

    /* Set up graphics objects */
    mModel.loadModel("ball.dae", 20);
    double scale = .5/ mModel.getNormalizedScale();

    mModel.setScale(scale,scale*.5,scale);
    mModel.setRotation(0,90.0,1,0,0);
}

void Ball::setSpeed(float speed){
    x += sin(pAngle*0.0174532925) * -speed;
    y += cos(pAngle*0.0174532925) * speed;

    dBodySetPosition(mBody, x, y, z);

    const dReal* thePos = dBodyGetPosition(mBody);

    setPosition(thePos[0],thePos[1], thePos[2]);
}

void Ball::setRotY (float pAngle){
    this->pAngle += pAngle;
}

void Ball::setPosition(float x, float y, float z)
{
    /* Setter method for position */
    this->x=x; this->y=y; this->z=z;
    dBodySetPosition(mBody, x, y, z);
}

void Ball::update(){
    dBodySetPosition(mBody, x, y, z);
}


void Ball::draw()
{

    const dReal* thePos = dBodyGetPosition(mBody);

    setPosition(thePos[0],thePos[1], thePos[2]);

    if(!debugDraw) {
        ofSetColor(ofColor::white,128);
        /* Save the current state of the graphics transform stack: */
        ofPushMatrix();

        /* Translate to the correct position: */
        ofTranslate(x,y,z);

        ofDrawSphere(c_rad);

        /* Restore the graphics transform stack: */
        ofPopMatrix();
    }
    ofPushMatrix();

    mModel.setPosition(x,y,z);

    mModel.drawFaces();

    ofPopMatrix();
}

Ball::~Ball(){
    dBodyDisable(mBody);
    dGeomDisable(mGeom);
}
