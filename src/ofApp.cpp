#include "ofApp.h"

static const dVector3 yunit = { 0, 1, 0 }, zunit = { 0, 0, 1 };
//--------------------------------------------------------------
void ofApp::setup(){
    ofDisableArbTex();
    ofSetFrameRate(60);

    // create world
    dInitODE2(0);
    world = dWorldCreate();
    space = dHashSpaceCreate (0);
    contactgroup = dJointGroupCreate (0);
    dWorldSetGravity (world,0,0,-0.5);
    ground = dCreatePlane (space,0,0,1,0);

    dAllocateODEDataForThread(dAllocateMaskAll);

    /* Graphics ground plane */
    mGround.set(8,8);
    mGround.mapTexCoords(0,0,4,4);
    mGround.setResolution(128,128);

    if(!ofLoadImage(mGroundTex, "dirt2.jpg")) { std::cerr << "Failed to load ground texture." << std::endl; }
    mGroundTex.setTextureWrap(GL_REPEAT, GL_REPEAT);

    /* The light */
    light.setPosition(-8,0,32);
    light.lookAt(glm::vec3(0,0,0));
    light.enable();

    /* The light */
    light.setPosition(8,0,32);
    light.lookAt(glm::vec3(0,0,0));
    light.enable();

    /* The light */
    light.setPosition(0,8,32);
    light.lookAt(glm::vec3(0,0,0));
    light.enable();

    /* The light */
    light.setPosition(0,-8,32);
    light.lookAt(glm::vec3(0,0,0));
    light.enable();

    panda = new PandaPlayer(0,0,0, world, space);


    // Set up the OpenFrameworks camera
    //camera.setAutoDistance(true);
//    ofVec3f upVector;
//    upVector.set(0, 1, 0);
//    camera.setNearClip(0.01);
//    camera.setPosition(panda->getX(),panda->getY()-4,panda->getZ()+2);
//    camera.lookAt({panda->getX(),panda->getY(),panda->getZ()},upVector);
//    camera.setTarget(panda->mModel.getPosition());
    //camera.setUpAxis(upVector);

    ofVec3f upVector;
    upVector.set(0, 0, 1);
    camera.setAutoDistance(false);
    camera.setNearClip(0.01);
    camera.setPosition(0,-4,6);
    camera.lookAt({0,0,0},upVector);
    camera.setUpAxis(upVector);

    for(unsigned int i=0; i<65536; i++) keys[i] = 0;
}

//--------------------------------------------------------------
void ofApp::update(){

    /* Handle the keys: */
    if (keys[OF_KEY_LEFT]){
        panda->setRotY(3);

    }
    if (keys[OF_KEY_RIGHT]){

        panda->setRotY(-3);

    }
    if (keys[OF_KEY_UP]){ panda->setSpeed(0.025); panda->mModel.playAllAnimations(); panda->mModel.update();}
    if (keys[OF_KEY_DOWN]){ panda->setSpeed(-0.025); panda->mModel.playAllAnimations(); panda->mModel.update();}

    panda->update();
    if(fireBall == true) {
        if(fireon == true){
            ball->setRotY(panda->pAngle);
            fireon = false;
        }
        ball->setSpeed(0.25);
        ball->update();

    }
    //camera.setPosition(panda->getX(),panda->getY()-4,panda->getZ()+2);

    dSpaceCollide (space,0,&nearCallback);
    dWorldStep (world,5);

    // remove all contact joints
    dJointGroupEmpty (contactgroup);
}

//--------------------------------------------------------------
void ofApp::draw(){
    // draw the scene
    ofBackground(20);

    camera.begin();

    ofEnableDepthTest();

    ofPushMatrix();

    ofSetColor(ofColor::lightGrey);
    //ofDrawGrid(0.2f,100, false, false,false,true);
    mGroundTex.bind();
    mGround.draw();
    mGroundTex.unbind();

    ofDrawAxis(10);

    /* Draw the pallets */
    panda->draw();
    if(seeBall) ball->draw();

    ofDisableDepthTest();
    camera.end();

    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::exit() {
    dJointGroupDestroy (contactgroup);
    dSpaceDestroy (space);
    dWorldDestroy (world);
    dCloseODE();
}

//--------------------------------------------------------------
static void nearCallback (void *, dGeomID o1, dGeomID o2) {
    myApp->collide(o1,o2);
}

//--------------------------------------------------------------
void ofApp::collide(dGeomID o1, dGeomID o2)
{
  int i,n;

  // only collide things with the ground
  //int g1 = (o1 == ground);
  int g2 = (o2 == ground );
  //if (!(g1 ^ g2)) return;

  const int N = 10;
  dContact contact[N];
  n = dCollide (o1,o2,N,&contact[0].geom,sizeof(dContact));
  if (n > 0) {
    for (i=0; i<n; i++) {
      contact[i].surface.mode = dContactSlip1 | dContactSlip2 |
        dContactSoftERP | dContactSoftCFM | dContactApprox1;
      contact[i].surface.mu = dInfinity;
      contact[i].surface.slip1 = 0.1;
      contact[i].surface.slip2 = 0.1;
      contact[i].surface.soft_erp = 0.5;
      contact[i].surface.soft_cfm = 0.3;
      dJointID c = dJointCreateContact (world,contactgroup,&contact[i]);
      dJointAttach (c,
                    dGeomGetBody(contact[i].geom.g1),
                    dGeomGetBody(contact[i].geom.g2));
    }
  }
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    keys[key] = 1;
    switch(key) {
    case 'r':
        ball = new Ball(panda->getX()+.78,panda->getY()+(.25),panda->getZ()+.6,world,space);
        seeBall = true;
        fireBall = true;
        fireon =true;
        break;
    case 'q':
        ofExit();
        break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    keys[key] = 0;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
