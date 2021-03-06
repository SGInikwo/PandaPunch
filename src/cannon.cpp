#include "cannon.h"

Cannon::Cannon(float x, float y, float z, dWorldID w, dSpaceID s)
{
    /* Set our x,y,z variables */
    this->x=x; this->y=y; this->z=z;

    mGeom = dCreateBox(s, c_len,c_wid,c_hei);
    dGeomSetPosition(mGeom,x,y,z);

    /* Set up graphics objects */
    mModel.loadModel("cannon.dae", 20);
    double scale = 1.5/ mModel.getNormalizedScale();

    mModel.setScale(scale,scale ,scale);
    mModel.setRotation(0,90.0,1,0,0);
    mModel.setRotation(1,180.0,0,1,0);
}


void Cannon::setPosition(float x, float y, float z)
{
    /* Setter method for position */
    this->x=x; this->y=y; this->z=z;
    dGeomSetPosition(mGeom, x, y, z);
}

void Cannon::draw()
{
    /* Draw objects */
    const dReal* thePos = dGeomGetPosition(mGeom);

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

    mModel.setPosition(x,y,z-(c_hei/2));

    mModel.drawFaces();
}
    ofPopMatrix();
}









void Cannon::ballSetup(float bX, float bY, float bZ, dWorldID w, dSpaceID s){
    /* Set our x,y,z variables */
    this->bX=bX; this->bY=bY; this->bZ=bZ;

    /* Set up physics objects */
    bBody = dBodyCreate(w);
    dBodySetPosition(bBody, bX, bY, bZ);
    dBodySetGravityMode(bBody,0);
    dMassSetSphere(&bMass,1,c_rad);
    dMassAdjust (&bMass,0.01);
    dBodySetMass (bBody,&bMass);
    bGeom = dCreateSphere(s,c_rad);
    dGeomSetBody (bGeom, bBody);
}

void Cannon::setBallPosition(float bX, float bY, float bZ){
    /* Setter method for position */
    this->bX=bX; this->bY=bY; this->bZ=bZ;
    dBodySetPosition(bBody, bX, bY, bZ);
}

void Cannon::drawBall(){
    const dReal* thePos = dBodyGetPosition(bBody);

    setBallPosition(thePos[0],thePos[1], thePos[2]);
if(gone == false){
    /* Save the current state of the graphics transform stack: */
    ofPushMatrix();

    ofSetColor(ofColor::blue);
    /* Translate to the correct position: */
    ofTranslate(bX,bY,bZ);

    ofDrawSphere(c_rad);
    ofSetColor(ofColor::white);
}

    /* Restore the graphics transform stack: */
    ofPopMatrix();
}

void Cannon::setSpeed(float speed){
    bY += speed;

    dBodySetPosition(bBody, bX, bY, bZ);

    const dReal* thePos = dBodyGetPosition(bBody);

    setBallPosition(thePos[0],thePos[1], thePos[2]);
}

void Cannon::disable(){
    dGeomDisable(mGeom);
    dGeomDisable(bGeom);
    gone = true;
}


