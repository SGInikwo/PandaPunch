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
//        ground_box = dCreateBox (space,4,4,4);
//        dGeomSetPosition (ground_box,0,0,0);

    dAllocateODEDataForThread(dAllocateMaskAll);

    /* Graphics ground plane */
    mGround.set(32,128);
    mGround.mapTexCoords(0,0,8,8);
    mGround.setResolution(128,128);

    if(!ofLoadImage(mGroundTex, "unnamed.png")) { std::cerr << "Failed to load ground texture." << std::endl; }
    mGroundTex.setTextureWrap(GL_REPEAT, GL_REPEAT);

    panda = new PandaPlayer(10,-55,1, world, space);
    //ball = new Ball(0,0,0,world,space);

    /* The light */
    light.setPointLight();
    light.setPosition(0,-70,10);
    light.lookAt(glm::vec3(0,0,0));
    light.enable();

    /* The light */
    light2.setPointLight();
    light2.setPosition(0,70,10);
    light2.lookAt(glm::vec3(8,0,0));
    light2.enable();

    /* The light */
    light3.setPointLight();
    light3.setPosition(0,0,32);
    light3.lookAt(glm::vec3(0,8,0));
    light3.enable();

    /* The light */
//    light4.setPosition(0,-8,32);
//    light4.lookAt(glm::vec3(panda->getX(),panda->getY(),panda->getZ()));
//    light4.enable();

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
    camera.setPosition(panda->getX(),-60,3);
    //camera.setPosition(0,-4,3);
    camera.lookAt({panda->getX(),panda->getY(),panda->getZ()},upVector);
    camera.setUpAxis(upVector);

    //cannon = new Cannon(0, -2, 1.2, world, space);
    //cannon->ballSetup(cannon->x,cannon->y-5,cannon->z+.6,world,space);

    float ranX[3];

    ranX[0] = ofRandom(-12,-7);
    ranX[1] = ofRandom(-3,5);
    ranX[2] = ofRandom(9,13);

    for(unsigned int p=0; p<3; p++) {
        canList.push_back((new Cannon(ranX[p], -2, 1.2, world, space)));
    }

    for(auto x : canList ){
        x->ballSetup(x->x,x->y-5,x->z+.6,world,space);
    }

    for(unsigned int p=0; p<1; p++) {
        chests.push_back(new Chest(0, -9, 1, world, space) );
//        chests2.push_back(new Chest(ofRandom(-15,15), -20, 1, world, space) );
//        chests3.push_back(new Chest(ofRandom(-15,15), 0, 1, world, space) );
//        chests4.push_back(new Chest(ofRandom(-15,15), 10, 1, world, space) );
//        chests5.push_back(new Chest(ofRandom(-15,15), 15, 1, world, space) );
//        chests6.push_back(new Chest(ofRandom(-15,15), 30, 1, world, space) );
//        chests7.push_back(new Chest(ofRandom(-15,15), 40, 1, world, space) );
//        chests8.push_back(new Chest(ofRandom(-15,15), 50, 1, world, space) );

    }

    // panda = new PandaPlayer(0,0,5, world, space);
    for(unsigned int i=0; i<65536; i++) keys[i] = 0;
    bgImage.load("thunderstorm-3625405_1920.jpg");
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
    if(keys[32]){
        panda->jump = true;
        if(panda->jump == true) {panda->setZ(.3);}
    }

    //    panda->update();
    if(fireBall == true) {
        if(fireon == true){
            ball->setRotY(panda->pAngle);
            fireon = false;
        }
        ball->setSpeed(0.15);
        ball->update();

        if(((ball->y-panda->getY()) > 7) || ((ball->y-panda->getY()) < -7) || ((ball->x-panda->getX()) >7) || ((ball->x-panda->getX()) < -7) ){
//            ball->x = panda->getX();
//            ball->y = panda->getY();
            ball->~Ball();
            fireBall = false;
        }
    }

    if(move == true){
        panda->setPosition(panda->getX(),panda->getY()-20,panda->getZ());
        move =false;
    }
    if(ballCol == true){
        ball->setPosition(ball->x, ball->y,-40);
        ballCol = false;
    }


    //cannon->setSpeed(-.7);
    for(auto x : canList){
        x->setSpeed(-.7);
    }
    cannonLogic();





    camera.setPosition(panda->getX(),panda->getY()-5,panda->getZ()+2);

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

    ofSetColor(ofColor::white);
    //ofDrawGrid(0.2f,100, false, false,false,true);
    mGroundTex.bind();
    mGround.draw();
    mGroundTex.unbind();

    //ofDrawAxis(10);

    // ground box
//        ofSetColor(ofColor::blue);
//        dVector3 ss; dQuaternion r;
//        dGeomBoxGetLengths (ground_box,ss);
//        dGeomGetQuaternion(ground_box,r);
//        drawBox(dGeomGetPosition(ground_box),r,ss);

    /* Draw the pallets */
    for(auto x: chests ) x->draw();
//    for(auto x: chests2 ) x->draw();
//    for(auto x: chests3 ) x->draw();
//    for(auto x: chests4 ) x->draw();
//    for(auto x: chests5 ) x->draw();
//    for(auto x: chests6 ) x->draw();
//    for(auto x: chests7) x->draw();
//    for(auto x: chests8 ) x->draw();
    panda->draw();

    for(auto x : canList){
        x->draw();
        x->drawBall();
    }
    //cannon->draw();


    //cannon->drawBall();



    if(seeBall) ball->draw();

    ofSetColor(ofColor::white);
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

//    if(ball->mGeom == o1){
//      std::cout<< "hiiiiiii  02" << std::endl;
//    }else if(ball->mGeom == o1){
//      std::cout << "hi 01" << std::endl;
//    }

    /* cannon ball collision with panda */
//    if(o1 == cannon->bGeom){
//        //cout<< "hi there and die!!" << endl;
//        if(o2 == panda->mGeom){
//            cout<<"noooo pandaaaa!!"<< endl;
//        }
//    }
    //std::cout << "Before "<< o1 << " and " << o2 << std::endl;
    for(auto x: canList){
        if(o2 == x->bGeom){
            cout<< "Cannnnnnooooonnnn"<<endl;
//            if( o1 == panda->mGeom){
//                cout<< "hi there im a panda!!!!!"<<endl;
//                move = true;
//                return;
//            }
//            if(o1 == ball->mGeom){
//                cout<< "!!!!!!hi there im a ballll!!!!!"<<endl;
//                //x->disable();
//                ballCol = true;
//            }
        }
    }

    /* Collision with chest and either panda and his punch */
    for(auto x: chests){
        if(o2 == x->mGeom){
            if( o1 == panda->mGeom){
                cout<< "hi there im a panda!!!!!"<<endl;
                move = true;
                return;
            }
            if(o1 == ball->mGeom){
                cout<< "!!!!!!hi there im a ballll!!!!!"<<endl;
                x->disable();
                ballCol = true;
            }
        }
    }

    //int g1 = (o1 == ground || o1 == ground_box);
    //int g2 = (o2 == ground || o2 == ground_box);
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
        seeBall = true;
        fireBall = true;
        fireon =true;
        break;
    case 'f':
        //cannon->ballSetup(cannon->x,cannon->y-5,cannon->z+.6,world,space);
        //shoot =true;
        break;
    case 'q':
        ofExit();
        break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    keys[key] = 0;
    if(keys[32]){
        panda->jump=false;
    }
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

void ofApp::cannonLogic(){
    cout << "my pos " << panda->getY() << endl;

    int i =0;
    for(auto x : canList){
        float ranX[3];
        ranX[0] = ofRandom(-12,-5);
        ranX[1] = ofRandom(-3,6);
        ranX[2] = ofRandom(9,13);
        if(panda->getY() > x->y){
            cout << "don't shoot....pls" << endl;
        }else if( x->bY < (panda->getY()-20) && ( fabs((x->y) - (panda->getY())) ) < 20 ) {
            x->setPosition(ranX[i],-2,1.2);
            x->ballSetup(x->x,x->y-10,x->z+.6,world,space);
        }
        else if( ( x->bY < (panda->getY()-5) && ( fabs((x->y) - (panda->getY())) ) > 20 ) ) {
            x->setPosition(ranX[i],-2,1.2);
            x->ballSetup(x->x,x->y-10,x->z+.6,world,space);
        }
        i++;
    }
}
