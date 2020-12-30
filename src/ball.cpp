#include "ball.h"
#include "ode/ode.h"

Ball::Ball(float x, float y, float z, dWorldID w, dSpaceID s)
{
    /* Set our x,y,z variables */
    this->x=x; this->y=y; this->z=z;

    /* Set up physics objects */
    mBody = dBodyCreate(w);
    dBodySetPosition(mBody, x, y, z);
    dMassSetBox (&mMass,1,c_len,c_wid,c_hei);
    dMassAdjust (&mMass,1);
    dBodySetMass (mBody,&mMass);
    mGeom = dCreateBox(s, c_len,c_wid,c_hei);
    dGeomSetBody (mGeom, mBody);

    /* Set up graphics objects */
    mModel.loadModel("pandaAnimation.dae", 20);
    double scale = .5/ mModel.getNormalizedScale();

    mModel.setScale(scale,scale*.5,scale);
    mModel.setRotation(0,90.0,1,0,0);
}

void Ball::setPosition(float x, float y, float z)
{
    /* Setter method for position */
    this->x=x; this->y=y; this->z=z;
}

/* Draw method collects latest data from ODE and draws the model at
 * that location/orientation.
 */
void Ball::draw()
{
    /* Get data from ODE */
    const dReal* thePos = dBodyGetPosition(mBody);
    const dReal* oderot = dBodyGetQuaternion(mBody);

    setPosition(thePos[0],thePos[1], thePos[2]);

    /* Get ODEs rotation quaternion, convert it to an OF one,
     * and then collect the angle and vector from that: */
    mRotation = ofQuaternion(oderot[1], oderot[2], oderot[3], oderot[0]);
    float rotationAmount;
    ofVec3f rotationAngle;
    mRotation.getRotate(rotationAmount, rotationAngle);

    /* We can draw a transparent white box where the ODE object is, to
     * make sure that our model is being drawn approximately correctly */
    if(debugDraw) {
        ofSetColor(ofColor::white,128);
        ofPushMatrix();

        ofTranslate(x,y,z+.5);

        //ofRotateDeg(rotationAmount, rotationAngle.x, rotationAngle.y, rotationAngle.z);

        /* Draw the box */
        ofDrawBox(1,1,1.1);
        ofDrawCylinder(1,1);

        ofPopMatrix();
    }
    /* Draw the model */
    ofPushMatrix();

    ofTranslate(x,y,z);

    //ofRotateDeg(rotationAmount, rotationAngle.x, rotationAngle.y, rotationAngle.z);
   //model.setPosition(pos_ode[0], pos_ode[1], pos_ode[2]);

    mModel.drawFaces();

    ofPopMatrix();
}
