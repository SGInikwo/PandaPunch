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
    mModel.loadModel("fianalPanda.dae", 20);
    double scale = .5/ mModel.getNormalizedScale();

    mModel.setScale(scale,scale,scale);
    mModel.setRotation(0,90.0,1,0,0);
}

void PandaPlayer::setPosition(float x, float y, float z)
{
    /* Setter method for position */
    this->x=x; this->y=y; this->z=z;
    dBodySetPosition(mBody, x, y, z);
}

void PandaPlayer::setSpeed(float speed){
    /* Set speed movement of the panda */
    x += sin(pAngle*0.0174532925) * -speed;
    y += cos(pAngle*0.0174532925) * speed;

    dBodySetPosition(mBody, x, y, z);

    const dReal* thePos = dBodyGetPosition(mBody);


    setPosition(thePos[0],thePos[1], thePos[2]);
}

void PandaPlayer::setZ(float up){
    /* The jump of the panda */
    if(jump == true && z < 3){
    z+=up;

    dBodySetPosition(mBody, x, y, z);

    const dReal* thePos = dBodyGetPosition(mBody);

    setPosition(thePos[0],thePos[1], thePos[2]);}
}

/* Getter and Setters */
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
    /* Draw objects */
    const dReal* thePos = dBodyGetPosition(mBody);

    setPosition(thePos[0],thePos[1], thePos[2]);

    if(!debugDraw) {
        /* Draw geom body */
        dVector3 ss; dQuaternion r;
        dGeomBoxGetLengths (mGeom,ss);
        dGeomGetQuaternion(mGeom,r);
        const dReal* f = dGeomGetPosition(mGeom);

        ofSetColor(ofColor::white,128);
        ofPushMatrix();

        ofTranslate(f[0],f[1],f[2]);
        ofDrawBox(ss[0],ss[1],ss[2]);

        ofPopMatrix();
    }

    /* Draw 3d Model */
    ofPushMatrix();

    mModel.setPosition(x,y,z-(c_hei/2));

    mModel.setRotation(1,pAngle,0,1,0);

    mModel.drawFaces();

    ofPopMatrix();
}


