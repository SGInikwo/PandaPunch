#include "pandaplayer.h"

PandaPlayer::PandaPlayer(float x, float y, float z, dWorldID w, dSpaceID s)
{
    /* Set our x,y,z variables */
    this->x=x; this->y=y; this->z=z;

    /* Set up physics objects */
    mBody = dBodyCreate(w);
    dBodySetPosition(mBody, x, y, z);
    dMassSetBox (&mMass,1,c_len,c_wid,c_hei);
    dBodySetLinearVel(mBody,x*speed,0,0);
    dMassAdjust (&mMass,1);
    dBodySetMass (mBody,&mMass);
    mGeom = dCreateBox(s, c_len,c_wid,c_hei);
    dGeomSetBody (mGeom, mBody);

    /* Set up graphics objects */
    mModel.loadModel("panda.dae", true);
    double scale = .5/ mModel.getNormalizedScale();

    mModel.setScale(scale,scale*.5,scale);
    mModel.setRotation(0,90.0,1,0,0);
    oderot = dBodyGetRotation(mBody);

    geometry.setPosition(x,y,z+.5);
    geometry.setScale(scale*5,scale*5,scale*5);
    material.setDiffuseColor(ofFloatColor::green);


    std::cout << "rotation w: " << oderot[0] << " x: " << oderot[1]<< " y: " << oderot[2] << " z: " << oderot[3] << std::endl;
    std::cout << " first x: " << x << std::endl;
    std::cout << " first Angle: " << pAngle << std::endl;
}

void PandaPlayer::setPosition(float x, float y, float z)
{
    /* Setter method for position */
    this->x=x; this->y=y; this->z=z;
}

void PandaPlayer::setSpeed(float speed){
    x += sin(pAngle*0.0174532925) * -speed;
    y += cos(pAngle*0.0174532925) * speed;
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

void PandaPlayer::update(){
    dBodySetPosition(mBody, x, y, z);
}

void PandaPlayer::setRotY (float pAngle){
    this->pAngle += pAngle;
}

float PandaPlayer::getRotX (){
    return pAngle;
}

void PandaPlayer::draw(){

    ofPushMatrix();

    mModel.setPosition(x,y,z);
    mModel.setRotation(1,pAngle,0,1,0);

    mModel.drawFaces();

    ofPopMatrix();

}


