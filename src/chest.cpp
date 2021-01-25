#include "chest.h"

Chest::Chest(float x, float y, float z, dWorldID w, dSpaceID s)
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
    mModel.loadModel("uploads_files_1979146_chest.dae", 20);
    double scale = .2/ mModel.getNormalizedScale();

    mModel.setScale(scale*.5,scale*.5,scale*.5);
    mModel.setRotation(0,90.0,1,0,0);
}

void Chest::setPosition(float x, float y, float z)
{
    /* Setter method for position */
    this->x=x; this->y=y; this->z=z;
}

void Chest::draw(){
    /* Draw objects */
    const dReal* thePos = dBodyGetPosition(mBody);

    setPosition(thePos[0],thePos[1], thePos[2]);

if(gone == false){
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

    mModel.setPosition(x,y,z-.5);

    mModel.setRotation(1,pAngle,0,1,0);


    mModel.drawFaces();
}

    ofPopMatrix();
}

void Chest::disable(){
    dBodyDisable(mBody);
    dGeomDisable(mGeom);
    gone = true;
}
