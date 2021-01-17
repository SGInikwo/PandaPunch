#include "ofApp.h"

static const dVector3 yunit = { 0, 1, 0 }, zunit = { 0, 0, 1 };
//--------------------------------------------------------------
void ofApp::setup(){
    level1Setup();
    //end1Setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    level1Update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    level1Draw();
    //end1Draw();
}

//--------------------------------------------------------------
void ofApp::exit() {
    level1Exit();
}

//--------------------------------------------------------------
static void nearCallback (void *, dGeomID o1, dGeomID o2) {
    myApp->collide(o1,o2);
}

//--------------------------------------------------------------
void ofApp::collide(dGeomID o1, dGeomID o2)
{
    int i,n;

    for(auto x: canList){
        if(x->bGeom == o1 || x->bGeom == o2){
            //cout<< "Cannnnnnooooonnnn"<<endl;
            if(panda->mGeom == o1 || panda->mGeom == o2){
                //cout<< "hi there im a panda!!!!!"<<endl;
                if(loseHealth == true){
                    health-=3;
                    cout<<"My health " << health << endl;
                }
            }
//            if(o1 == ball->mGeom){
//                cout<< "!!!!!!hi there im a ballll!!!!!"<<endl;
//                //x->disable();
//                ballCol = true;
//            }
        }
        if(x->mGeom == o1 || x->mGeom == o2){
            if(loseHealth == true){
                toStart = true;
                health-=20;
            }
            return;
        }

    }

    /* Collision with chest and either panda and his punch */
    for(auto x: chests){
        if(o2 == x->mGeom){
            if( o1 == panda->mGeom){
                ///cout<< "hi there im a panda!!!!!"<<endl;
                move = true;
                if(loseHealth == true) {health-=1;}
                return;
            }
            if(fireBall == true){
                if(o1 == ball->mGeom){
                    //cout<< "!!!!!!hi there im a ballll!!!!!"<<endl;
                    x->disable();
                    float ranNum = ofRandom(0,12);
                    cout<<"Random number "<< ranNum <<endl;

                    if(ranNum < 0.3 && ranNum > 0){gotTrophy = true;}
                    if(ranNum < 3 &&ranNum  > 0.3){is2Point = true; points+=2;}
                    if(ranNum > 3 && ranNum < 6){isShield =true; shields++;}
                    if(ranNum > 6){isPoint =true; points++;}


                    //ofResetElapsedTimeCounter();
                    shieldTime = ofGetElapsedTimef();
                    point2Time = ofGetElapsedTimef();
                    pointTime = ofGetElapsedTimef();
                    ballCol = true;
                    return;
                }
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
        if(shields > 0){
            runShield = true;
            if(shieldPress == true){
                shields--;
            }
            healthTime = ofGetElapsedTimef();
            loseHealth = false;
            shieldPress = false;
            shieldEnd = true;
        }
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
    //cout << "my pos " << panda->getY() << endl;

    int i =0;
    for(auto x : canList){
        float ranX[3];
        ranX[0] = ofRandom(-21,-12);
        ranX[1] = ofRandom(-7,7);
        ranX[2] = ofRandom(12,21);
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

//--------------------------------------------------------------
void ofApp::level1Setup(){
    ofDisableArbTex();

    // panda = new PandaPlayer(0,0,5, world, space);
    for(unsigned int i=0; i<65536; i++) keys[i] = 0;
    bgImage.load("thunderstorm-3625405_1920.jpg");

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
    mGround.set(46,128);
    mGround.mapTexCoords(0,0,8,8);
    mGround.setResolution(128,128);

    if(!ofLoadImage(mGroundTex, "unnamed.png")) { std::cerr << "Failed to load ground texture." << std::endl; }
    mGroundTex.setTextureWrap(GL_REPEAT, GL_REPEAT);

    panda = new PandaPlayer(0,-64,1, world, space);
    //ball = new Ball(0,0,0,world,space);

    /* The light */
    light.setPointLight();
    light.setPosition(0,-70,10);
    light.lookAt(glm::vec3(panda->getX(),panda->getY(),panda->getZ()));
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

    ofVec3f upVector;
    upVector.set(0, 0, 1);
    camera.setAutoDistance(false);
    camera.setNearClip(0.01);
    camera.setPosition(panda->getX(),panda->getY()-5,3);
    camera.lookAt({panda->getX(),panda->getY(),panda->getZ()},upVector);
    camera.setUpAxis(upVector);

    float ranX[3];

    ranX[0] = ofRandom(-21,-12);
    ranX[1] = ofRandom(-7,7);
    ranX[2] = ofRandom(12,21);

    for(unsigned int p=0; p<10; p++) {
        chests.push_back(new Chest(ofRandom(-21,21),-20, 1, world, space) );
    }

    for(unsigned int p=0; p<3; p++) {
        canList.push_back((new Cannon(ranX[p], -2, 1.2, world, space)));
    }

    for(auto x : canList ){
        x->ballSetup(x->x,x->y-5,x->z+.6,world,space);
    }

    for(auto x : chests){
        if(x->y > -10 && x->y < 10){
            x->disable();
            cout<<"goodby"<<endl;
        }
    }

    shieldIm.load("shield.png");
    pointIm.load("bamboo.png");
    trophyIm.load("trophy.png");

    healthTex.load("vag.ttf",20);
    upTex.load("vag.ttf",20);
    shieldsTex.load("vag.ttf", 30);
    pointsTex.load("vag.ttf", 30);

    pointIm.resize(70,70);
    shieldIm.resize(100,100);
    trophyIm.resize(113,120);
}

void ofApp::level1Update(){
    for(auto x : chests){
        if(x->y > -10 && x->y < 10){
            x->disable();
        }
    }

    /* Handle the keys: */
    if (keys[OF_KEY_LEFT] || keys['a']){
        panda->setRotY(3);
    }
    if (keys[OF_KEY_RIGHT] || keys['d']){
        panda->setRotY(-3);
    }
    if (keys[OF_KEY_UP] || keys['w']){ panda->setSpeed(0.145); panda->mModel.playAllAnimations();
        panda->mModel.update();
    }
    if(keys[32]){
        panda->jump = true;
        if(panda->jump == true) {panda->setZ(.3);}
    }

    camera.setPosition(panda->getX(),panda->getY()-5,panda->getZ()+2);

    light.lookAt(glm::vec3(panda->getX(),panda->getY(),panda->getZ()));

    if(fireBall == true) {
        if(fireon == true){
            ball->setRotY(panda->pAngle);
            fireon = false;
        }
        ball->setSpeed(0.15);
        ball->update();

        if(((ball->y-panda->getY()) > 7) || ((ball->y-panda->getY()) < -7) || ((ball->x-panda->getX()) >7) || ((ball->x-panda->getX()) < -7) ){
            ball->~Ball();
            fireBall = false;
        }
    }

    if(move == true){
        panda->setPosition(panda->getX(),panda->getY()-20,panda->getZ());
        move =false;
    }if(toStart == true){
        panda->setPosition(0,-64,1);
        toStart = false;
    }
    if(ballCol == true){
        ball->setPosition(ball->x, ball->y,-40);
        ballCol = false;
    }

    if(panda->getY() > -60){
    for(auto x : canList){
        x->setSpeed(-.7);
    }
    cannonLogic();}



    if(panda->getY() >= 64){

    }

    if(runShield == true){
        if(ofGetElapsedTimef() - healthTime > 5){
            loseHealth = true;
            shieldPress = true;
            shieldEnd = false;
            runShield = false;
        }
    }


    dSpaceCollide (space,0,&nearCallback);
    dWorldStep (world,0.05);

    // remove all contact joints
    dJointGroupEmpty (contactgroup);
}

//--------------------------------------------------------------
void ofApp::level1Draw(){
    // draw the scene
    //ofBackground(20);
    bgImage.draw(0,0);
    ofSetColor(ofColor::white);
    healthTex.drawString("Health: " + ofToString(health) ,0,20);

    ofSetColor(ofColor::gray);

    ofSetColor(ofColor::black);
    ofFill();
    ofRect(0,30, 200, 20);
    ofSetColor(ofColor::green);
    ofFill();
    ofRect(0,30, health*2, 20);

    camera.begin();


    ofEnableDepthTest();

    ofPushMatrix();

    ofSetColor(ofColor::white);
    //ofDrawGrid(0.2f,100, false, false,false,true);
    mGroundTex.bind();
    mGround.draw();
    mGroundTex.unbind();

    //ofDrawAxis(10);


    panda->draw();
    if(seeBall) ball->draw();

    /* Draw the pallets */
    for(auto x: chests ) x->draw();


    for(auto x : canList){
        x->draw();
        x->drawBall();
    }

    ofSetColor(ofColor::white);
    ofDisableDepthTest();
    camera.end();

    if(((int) ofGetElapsedTimef() - shieldTime) > 1){
        if(isShield == true) {isShield = false;}
    }
    if(((int) ofGetElapsedTimef() - point2Time) > 1){
        if(is2Point == true) {is2Point = false;}
    }
    if(((int) ofGetElapsedTimef() - pointTime) > 1){
        if(isPoint == true) {isPoint = false;}
    }

    if(isShield == true){
        upTex.drawString("+1 Shield",10,360);
    }if(is2Point == true){
        upTex.drawString("+3 Point",10,330);
    }if(isPoint == true){
        upTex.drawString("+1 Point",10,300);
    }if(shieldEnd == true){
        upTex.drawString("Shield activated",10,250);
    }

    if(gotTrophy == true){
        trophyIm.draw(730,500);
    }
    pointIm.draw(749,620);
    pointsTex.drawString(ofToString(points), 770,668);
    shieldIm.draw(900,610);
    shieldsTex.drawString(ofToString(shields), 939,668);

    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::level1Exit(){
    for(auto x : canList){
        dGeomDestroy(x->mGeom);
        dGeomDestroy(x->bGeom);
    }
    for(auto x : chests){
        dGeomDestroy(x->mGeom);
    }
    dGeomDestroy(ball->mGeom);
    dGeomDestroy(panda->mGeom);
    dJointGroupDestroy (contactgroup);
    dSpaceDestroy (space);
    dWorldDestroy (world);
    dCloseODE();
}

void ofApp::end1Setup(){
    endTex.load("vag.ttf", 40);
}

void ofApp::end1Draw(){
    ofBackground(ofColor::black);

    endTex.drawString("You got " + ofToString(points), (ofGetWindowWidth()/2)-100,(ofGetWindowHeight()/2)-100);
}



