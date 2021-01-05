#include "ball.h"

Ball::Ball(float x, float y, float z, dWorldID w, dSpaceID s)
{
    /* Set our x,y,z variables */
    this->x=x; this->y=y; this->z=z;

    /* Set up physics objects */
    mBody = dBodyCreate(w);
    dBodySetPosition(mBody, x, y, z);
    //dMassSetBox (&mMass,0.01,c_len,c_wid,c_hei);
    //dMassAdjust (&mMass,0.01);
    //dBodySetMass (mBody,&mMass);
    mGeom = dCreateCylinder(s,c_wid,c_len);
    dGeomSetBody (mGeom, mBody);

    /* Set up graphics objects */
    mModel.loadModel("ball.dae", true);
    double scale = .5/ mModel.getNormalizedScale();

    mModel.setScale(scale,scale*.5,scale);
    mModel.setRotation(0,90.0,1,0,0);
}

void Ball::setSpeed(float speed){
    x += sin(pAngle*0.0174532925) * -speed;
    y += cos(pAngle*0.0174532925) * speed;
}

void Ball::setRotY (float pAngle){
    this->pAngle += pAngle;
}

void Ball::setPosition(float x, float y, float z)
{
    /* Setter method for position */
    this->x=x; this->y=y; this->z=z;
}

void Ball::update(){
    dBodySetPosition(mBody, x, y, z);
}


/* Draw method collects latest data from ODE and draws the model at
 * that location/orientation.
 */
void Ball::draw()
{
    ofPushMatrix();

    mModel.setPosition(x,y,z);
    //mModel.setRotation(1,pAngle,0,1,0);

    mModel.drawFaces();

    ofPopMatrix();
}
