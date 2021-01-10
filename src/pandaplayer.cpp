#include "pandaplayer.h"

PandaPlayer::PandaPlayer(float x, float y, float z, dWorldID w, dSpaceID s)
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
    mModel.loadModel("panda.dae", true);
    double scale = .5/ mModel.getNormalizedScale();

    mModel.setScale(scale,scale*.5,scale);
    mModel.setRotation(0,90.0,1,0,0);

    std::cout << " first x: " << x << std::endl;
    std::cout << " first Angle: " << pAngle << std::endl;
}

void PandaPlayer::setPosition(float x, float y, float z)
{
    /* Setter method for position */
    this->x=x; this->y=y; this->z=z;
    //dBodySetPosition(mBody, x, y, z);
    //dGeomSetBody (mGeom, mBody);
}

void PandaPlayer::setSpeed(float speed){
    x += sin(pAngle*0.0174532925) * -speed;
    y += cos(pAngle*0.0174532925) * speed;
    dBodySetPosition(mBody, x, y, z);

    const dReal* thePos = dBodyGetPosition(mBody);
    const dReal* oderot = dBodyGetQuaternion(mBody);

    setPosition(thePos[0],thePos[1], thePos[2]);

    //dGeomSetBody (mGeom, mBody);
    std::cout << "x: " << x << " y: " << y  << " z: " << z << std::endl;
}

void PandaPlayer::setZ(float z){
    this->z=z;
}

float PandaPlayer::getX(){
    return x;
}

float PandaPlayer::getY(){
    return y;
}

float PandaPlayer::getZ(){
    return z;
}



void PandaPlayer::setRotY (float pAngle){
    this->pAngle += pAngle;
}

float PandaPlayer::getRotX (){
    return pAngle;
}

void PandaPlayer::draw(){
    const dReal* thePos = dBodyGetPosition(mBody);
    const dReal* oderot = dBodyGetQuaternion(mBody);

    setPosition(thePos[0],thePos[1], thePos[2]);

    ofPushMatrix();

    mModel.setPosition(x,y,z-1);
    //dBodySetPosition(mBody, x, y, z);
    dGeomSetBody (mGeom, mBody);
    mModel.setRotation(1,pAngle,0,1,0);

    mModel.drawFaces();

    ofPopMatrix();

}


