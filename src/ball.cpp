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
}

void Ball::update(){
    dBodySetPosition(mBody, x, y, z);
}


/* Draw method collects latest data from ODE and draws the model at
 * that location/orientation.
 */
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

            /* Rotate by the correct amount: */
            //ofRotateDeg(rotationAmount, rotationAngle.x, rotationAngle.y, rotationAngle.z);

            /* Draw the box */
            ofDrawSphere(c_rad);

            /* Restore the graphics transform stack: */
            ofPopMatrix();
        }
    ofPushMatrix();

    //const dReal* thePos = dBodyGetPosition(mBody);

    //setPosition(thePos[0],thePos[1], thePos[2]);

    std::cout << "x: " << x << " y: " << y  << " z: " << z << std::endl;
    mModel.setPosition(x,y,z);
    //mModel.setRotation(1,pAngle,0,1,0);

    mModel.drawFaces();

    ofPopMatrix();
}
