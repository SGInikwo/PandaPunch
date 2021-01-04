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
    mModel.loadModel("pandaAnimation.dae", true);
    double scale = .5/ mModel.getNormalizedScale();

    mModel.setScale(scale,scale*.5,scale);
    mModel.setRotation(0,90.0,1,0,0);
    oderot = dBodyGetRotation(mBody);

    std::cout << "rotation w: " << oderot[0] << " x: " << oderot[1]<< " y: " << oderot[2] << " z: " << oderot[3] << std::endl;
}

void PandaPlayer::setPosition(float x, float y, float z)
{
    /* Setter method for position */
    this->x=x; this->y=y; this->z=z;
}

void PandaPlayer::setX(float speed){
    this->x+=speed;
}

void PandaPlayer::setY(float speed){
    this->y+=speed;
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
    //rRotation = ofQuaternion(odeRot[1], odeRot[2], odeRot[3], odeRot[0]);
    //odeRot = dQuaternion(odeRot[0],odeRot);
    dBodySetPosition(mBody, x, y, z);
    //std::cout << "rotation update w: " << oderot[0] << " x: " << oderot[1]<< " y: " << oderot[2] << " z: " << oderot[3] << std::endl;
    //dBodySetQuaternion(mBody)
    //draw();
}

/* Draw method collects latest data from ODE and draws the model at
 * that location/orientation.
 */
//void PandaPlayer::draw()
//{
//    /* Get data from ODE */
//    const dReal* thePos = dBodyGetPosition(mBody);
//    const dReal* odeRot = dBodyGetQuaternion(mBody);
//    //dBodySetPosition()
//    setPosition(thePos[0],thePos[1], thePos[2]);

//    /* Get ODEs rotation quaternion, convert it to an OF one,
//     * and then collect the angle and vector from that: */
//    mRotation = ofQuaternion(odeRot[1], odeRot[2], odeRot[3], odeRot[0]);
//    float rotationAmount;
//    ofVec3f rotationAngle;
//    mRotation.getRotate(rotationAmount, rotationAngle);
//    //std::cout << "amount " << rotationAmount << std::endl;

//    /* We can draw a transparent white box where the ODE object is, to
//     * make sure that our model is being drawn approximately correctly */
//    if(debugDraw) {
//        ofSetColor(ofColor::white,128);
//        ofPushMatrix();

//        ofTranslate(x,y,z+.5);

//        ofRotateDeg(1.8, rotationAngle.x, rotationAngle.y, rotationAngle.z);

//        /* Draw the box */
//        ofDrawBox(1,1,1.1);

//        ofPopMatrix();
//    }
//    /* Draw the model */
//    ofPushMatrix();

//    ofTranslate(x,y,z);

//    //ofRotateDeg(rotationAmount, rotationAngle.x, rotationAngle.y, rotationAngle.z);
//    //model.setPosition(pos_ode[0], pos_ode[1], pos_ode[2]);

//    mModel.drawFaces();

//    ofPopMatrix();
//}

void PandaPlayer::setRotX (float pAngle){
    this->pAngle += pAngle;
}

float PandaPlayer::getRotX (){
    return pAngle;
}

void PandaPlayer::draw(){
    const dReal* pos_ode = dBodyGetPosition(mBody);
    const dReal* rot_ode = dBodyGetQuaternion(mBody);

    ofQuaternion rot_of(rot_ode[1],rot_ode[2],rot_ode[3],rot_ode[0]);

    ofPushMatrix();
    dMatrix3 R2,R3,R4;

    dRFromAxisAndAngle(R2,0,0,1,pAngle);
    dRFromAxisAndAngle(R3,0,1,0,pElevation);
    dMultiply0(R4,R2,R3,3,3,3);


    //ofQuaternion rot(R2[1],R2[2],R2[3],R2[0]);
    x = pos_ode[0];
    y =pos_ode[1];
    z =pos_ode[2];

    //ofTranslate(x,y,z);

    ofRotateZDeg(pAngle);
    //ofRotateDeg(glm::quat(R2[1],R2[2],R2[3],R2[0]));
    //ofRotateDeg(rot[0],rot[1],rot[2],rot[3]);
    ofTranslate(x,y,z);

    //rot_of.getRotate(rotationAmount,rotationAngle);
    //ofRotate(rot_ode[1],rot_ode[2],rot_ode[3],rot_ode[0]);
    //ofRotateDeg(rotationAmount, rotationAngle.x, rotationAngle.y, rotationAngle.z);
    //mModel.setPosition(pos_ode[0],pos_ode[1],pos_ode[2]);
    //mModel.setRotation(rot_ode[1],rot_ode[2],rot_ode[3],rot_ode[0]);
    mModel.drawFaces();

    ofPopMatrix();

}


