#include "ofApp.h"

static const dVector3 yunit = { 0, 1, 0 }, zunit = { 0, 0, 1 };
//--------------------------------------------------------------
void ofApp::setup(){
    ofDisableArbTex();

    //ofSetFrameRate(60);

    // create world
    dInitODE2(0);
    world = dWorldCreate();
    space = dHashSpaceCreate (0);
    contactgroup = dJointGroupCreate (0);
    dWorldSetGravity (world,0,0,-0.5);
    ground = dCreatePlane (space,0,0,1,0);

    // environment
        ground_box = dCreateBox (space,4,4,4);
        dGeomSetPosition (ground_box,0,0,0);

    dAllocateODEDataForThread(dAllocateMaskAll);

    /* Graphics ground plane */
    mGround.set(64,128);
    mGround.mapTexCoords(0,0,8,8);
    mGround.setResolution(128,128);

    if(!ofLoadImage(mGroundTex, "unnamed.png")) { std::cerr << "Failed to load ground texture." << std::endl; }
    mGroundTex.setTextureWrap(GL_REPEAT, GL_REPEAT);

    panda = new PandaPlayer(0,-55,1, world, space);
    //ball = new Ball(0,0,0,world,space);

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
    light.lookAt(glm::vec3(panda->getX(),panda->getY(),panda->getZ()));
    light.enable();

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
    camera.setPosition(0,-60,3);
    camera.setPosition(0,-4,3);
    camera.lookAt({panda->getX(),panda->getY(),panda->getZ()},upVector);
    camera.setUpAxis(upVector);

    // panda = new PandaPlayer(0,0,5, world, space);
    for(unsigned int i=0; i<65536; i++) keys[i] = 0;
    bgImage.loadImage("thunderstorm-3625405_1920.jpg");
}

//--------------------------------------------------------------
void ofApp::update(){
    //float lastTime;
    //float currentTime = ofGetElapsedTimef();
    /* Handle the keys: */
    if (keys[OF_KEY_LEFT] || keys['a']){
        panda->setRotY(3);
    }
    if (keys[OF_KEY_RIGHT] || keys['d']){
        panda->setRotY(-3);
    }
    if (keys[OF_KEY_UP] || keys['w']){ panda->setSpeed(0.145); panda->mModel.playAllAnimations();
        //panda->mModel.update();
    }
    //if (keys[OF_KEY_DOWN] || keys['s']){ panda->setSpeed(-0.145); panda->mModel.playAllAnimations(); panda->mModel.update();}

//    panda->update();
    if(fireBall == true) {
        if(fireon == true){
            ball->setRotY(panda->pAngle);
            fireon = false;
        }
        ball->setSpeed(0.15);
        ball->update();

        if(((ball->y-panda->getY()) > 4) || ((ball->y-panda->getY()) < -4) || ((ball->x-panda->getX()) >4) || ((ball->x-panda->getX()) < -4) ){
            ball->x = panda->getX();
            ball->y = panda->getY();
            fireBall = false;
        }
    }

    //camera.setPosition(panda->getX(),panda->getY()-5,panda->getZ()+2);

    light.lookAt(glm::vec3(panda->getX(),panda->getY(),panda->getZ()));

    dSpaceCollide (space,0,&nearCallback);
    dWorldStep (world,0.05);

    // remove all contact joints
    dJointGroupEmpty (contactgroup);
}

//--------------------------------------------------------------
void ofApp::draw(){
    // draw the scene
    //ofBackground(20);
    bgImage.draw(0,0);

    camera.begin();

    ofEnableDepthTest();

    ofPushMatrix();

    ofSetColor(ofColor::lightGrey);
    //ofDrawGrid(0.2f,100, false, false,false,true);
    mGroundTex.bind();
    mGround.draw();
    mGroundTex.unbind();

    //ofDrawAxis(10);

    // ground box
        ofSetColor(ofColor::blue);
        dVector3 ss; dQuaternion r;
        dGeomBoxGetLengths (ground_box,ss);
        dGeomGetQuaternion(ground_box,r);
        drawBox(dGeomGetPosition(ground_box),r,ss);

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

void ofApp::drawBox(const dReal*pos_ode, const dQuaternion rot_ode, const dReal*sides_ode)
{
    ofBoxPrimitive b;
    // ofBox dimensions: 100 * 100 * 100
    // std::cout << b.getSize() << std::endl;

    // scale it to be unit w, h, d * the actual size:
    b.setScale(glm::vec3(0.01*sides_ode[0],0.01*sides_ode[1],0.01*sides_ode[2]));

    // Simply set the orientation based on ODE's quaternion. Since we are using glm::quat
    // this time, the ordering is the same as ODE:
    b.setGlobalOrientation(glm::quat(rot_ode[0],rot_ode[1],rot_ode[2],rot_ode[3]));

    // Now set the box's position according to ODE physics:
    b.setGlobalPosition(glm::vec3(pos_ode[0],pos_ode[1],pos_ode[2]));

    // Draw it:
    b.draw();
}

//--------------------------------------------------------------
void ofApp::collide(dGeomID o1, dGeomID o2)
{
    int i,n;

    // only collide things with the ground
    //int g1 = (o1 == ground);
    //int g2 = (o2 == ground );

//    if(ground == o1){
//      std::cout<< "hiiiiiii  02" << std::endl;
//    }else if(ground == o1){
//      std::cout << "hi 01" << std::endl;
//    }
    int g1 = (o1 == ground || o1 == ground_box);
    int g2 = (o2 == ground || o2 == ground_box);
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
        ball = new Ball(panda->getX()+.78,panda->getY()+(.47),panda->getZ()+.1,world,space);
        ball->setRotY(panda->pAngle);
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
