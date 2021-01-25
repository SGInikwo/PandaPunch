#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    /* Start screen */
    ofSetFrameRate(60);
    if(switchLev == 0) startSetup();
}

//--------------------------------------------------------------
void ofApp::update(){
    /* Making sure the setup is called once */
    if(switchLev == 1){
        if(lvl1ON == true){
            lvl1ON = false;
            level1Setup();
        }
        level1Update();
    }

    if(switchLev == 11){
        if(lvl11ON){
            lvl11ON = false;
            end1Setup();
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    /* Which screen to draw */
    if(switchLev == 0) startDraw();
    if(switchLev == 1) level1Draw();
    if(switchLev == 11){
        end1Draw();
    }
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

    /* Collision of first row of cannon with either panda and his punch */
    for(auto x: canList){
        if(x->bGeom == o1 || x->bGeom == o2){
            for(auto y : chests){
                if(y->mGeom == o1 || y->mGeom == o2){
                    return;
                }
            }
            if(panda->mGeom == o1 || panda->mGeom == o2){
                if(loseHealth == true){
                    health-=5;
                    cout<<"ball1 My health " << health << endl;
                    move = true;
                    return;
                }
                return;
            }if(fireBall == true){
                if(ball->mGeom == o1|| ball->mGeom == o2){
                    return;
                }
            }
        }
        if(x->mGeom == o1 || x->mGeom == o2){
            if(panda->mGeom == o1 || panda->mGeom == o2){
                if(loseHealth == true){
                    toStart = true;
                    health-=20;
                    cout<<"cannon1 My health " << health << endl;
                    return;
                }
            }
            if(fireBall == true){
                if(ball->mGeom == o1|| ball->mGeom == o2){
                    x->disable();
                    points+=5;
                    isCPoints = true;

                    cPointTime = ofGetElapsedTimef();
                    ballCol = true;
                    return;
                }
            }
        }
    }

    /* Collision of second row cannons with either panda and his punch */
    for(auto x: canList2){
        if(x->bGeom == o1 || x->bGeom == o2){
            for(auto y : chests){
                if(y->mGeom == o1 || y->mGeom == o2){
                    return;
                }
            }
            if(panda->mGeom == o1 || panda->mGeom == o2){
                if(loseHealth == true){
                    health-=5;
                    cout<<"Ball2 My health " << health << endl;
                    move = true;
                    return;
                }
                return;
            }if(fireBall == true){
                if(ball->mGeom == o1|| ball->mGeom == o2){
                    return;
                }
            }
        }
        if(x->mGeom == o1 || x->mGeom == o2){
            if(panda->mGeom == o1 || panda->mGeom == o2){
                if(loseHealth == true){
                    toStart = true;
                    health-=20;
                    cout<<"cannon 2 My health " << health << endl;
                    return;
                }
            }
            if(fireBall == true){
                if(ball->mGeom == o1|| ball->mGeom == o2){
                    cout<< "!!!!!!hi there im a tha cannon2!!!!!"<<endl;
                    x->disable();
                    points+=5;
                    isCPoints = true;

                    cPointTime = ofGetElapsedTimef();
                    ballCol = true;
                    return;
                }
            }
        }

    }


    /* Collision of chest with either panda and his punch */
    for(auto x: chests){
        if(x->mGeom == o1 || x->mGeom == o2){
            if( panda->mGeom == o1 || panda->mGeom == o2){
                move = true;
                if(loseHealth == true) {health-=1; cout<<"chest My health " << health << endl;}
                return;
            }
            if(fireBall == true){
                if(ball->mGeom == o1 || ball->mGeom == o2){
                    x->disable();
                    float ranNum = ofRandom(0,12);
                    cout<<"Random number "<< ranNum <<endl;

                    if(ranNum < 0.3 && ranNum > 0){gotTrophy = true; points+=20;}
                    if(ranNum < 3 &&ranNum  > 0.3){is2Point = true; points+=2;}
                    if(ranNum > 3 && ranNum < 6){isShield =true; shields++;}
                    if(ranNum > 6){isPoint =true; points++;}

                    shieldTime = ofGetElapsedTimef();
                    point2Time = ofGetElapsedTimef();
                    pointTime = ofGetElapsedTimef();
                    ballCol = true;
                    return;
                }
            }
        }
    }

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
    if(switchLev == 1){
        keys[key] = 1;
        switch(key) {
        case 'k': case 'K':
            ball = new Ball(panda->getX()+.78,panda->getY()+(.47),panda->getZ()+.1,world,space);
            seeBall = true;
            fireBall = true;
            fireon =true;
            break;
        case 'j': case 'J':
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
            break;
        case 'p':  case 'P':
            cheat = true;
            cout<<"Cheats activated"<<endl;
            break;
        case 'o':  case 'O':
            cheat = false;
            cout<<"Cheats Deactivated"<<endl;
            break;
        case 'q':  case 'Q':
            ofExit();
            break;
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(switchLev == 1){
        keys[key] = 0;
        if(keys[32]){
            panda->jump=false;
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    if(switchLev == 0){
        if(x > (ofGetWindowWidth()/2) -200 && x < 720 && y > ((ofGetWindowHeight()/2) - 130) && y < (ofGetWindowHeight()/2) -10){
            if(mEntered == true){
                startSound.play();
                startBTN = ofColor::gray;
                mEntered = false;
            }
        }else{mEntered = true; startBTN = ofColor::white;}

        if(x > (ofGetWindowWidth()/2) -200 && x < 720 && y > ((ofGetWindowHeight()/2)) && y < (ofGetWindowHeight()/2) +120){
            if(mQuit == true){
                startSound.play();
                quitBTN = ofColor::gray;
                mQuit = false;
            }
        }else{mQuit = true; quitBTN = ofColor::white;}
    }

    if(switchLev == 11){
        if(x > 300 && x < 370 && y > 550 && y < 620){
            if(endE == true){
                startSound.play();
                endSBTN = ofColor::gray;
                endE = false;
            }

        }else{endE = true; endSBTN = ofColor::white;}

        if(x > 550 && x < 755 && y > 550 && y < 610){
            if(endQ == true){
                startSound.play();
                endQBTN = ofColor::gray;
                endQ = false;
            }
        }else{endQ = true; endQBTN = ofColor::white;}

    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if(switchLev == 0){
        if(button == 0){
            if(mouseX > (ofGetWindowWidth()/2) -200 && mouseX < 720 && mouseY > ((ofGetWindowHeight()/2) - 130) && mouseY < (ofGetWindowHeight()/2) -10){
                switchLev = 1;
            }if(mouseX > (ofGetWindowWidth()/2) -200 && mouseX < 720 && mouseY > ((ofGetWindowHeight()/2)) && mouseY < (ofGetWindowHeight()/2) +120){
                ofExit();
            }
        }
    }

    if(switchLev == 11){
        if(button == 0){
            if(mouseX > 300 && mouseX < 370 && mouseY > 550 && mouseY < 620){
                shields = 0;
                points = 0;
                health = 100;
                switchLev =1;
                canList.clear();
                canList2.clear();
                chests.clear();
                hasDied = false;
                gotTrophy = false;
                lvl11ON = true;

            }if(mouseX > 550 && mouseX < 755 && mouseY > 550 && mouseY < 610){
                ofExit();
            }
        }
    }

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
    /* First row of cannon logic their movement */
    int i =0;
    for(auto x : canList){
        float ranX[3];
        ranX[0] = ofRandom(-21,-12);
        ranX[1] = ofRandom(-7,7);
        ranX[2] = ofRandom(12,21);
        if(panda->getY() > x->y){
            //cout << "don't shoot....pls" << endl;
        }
        if( x->bY < (panda->getY()-20) && ( fabs((x->y) - (panda->getY())) ) < 20 ) {
            x->setPosition(ranX[i],-2,1.2);
            x->setBallPosition(x->x,x->y-10,x->z+.6);
        }
         if( ( x->bY < (panda->getY()-5) && ( fabs((x->y) - (panda->getY())) ) > 20 ) ) {
            x->setPosition(ranX[i],-2,1.2);
            x->setBallPosition(x->x,x->y-10,x->z+.6);
        }
        i++;
    }
}

void ofApp::cannonLogic2(){
    /* Second row of cannon logic their movement */
    int j =0;
    for(auto x : canList2){
        float ranX[3];
        ranX[0] = ofRandom(-21,-12);
        ranX[1] = ofRandom(-7,7);
        ranX[2] = ofRandom(12,21);
        if(panda->getY() > x->y){
            //cout << "don't shoot....pls" << endl;
        }else if( x->bY < (panda->getY()-20) && ( fabs((x->y) - (panda->getY())) ) < 20 ) {
            x->setPosition(ranX[j],50,1.2);
            x->setBallPosition(x->x,x->y-10,x->z+.6);
        }
        else if( ( x->bY < (panda->getY()-5) && ( fabs((x->y) - (panda->getY())) ) > 20 ) ) {
            x->setPosition(ranX[j],50,1.2);
            x->setBallPosition(x->x,x->y-10,x->z+.6);
        }
        j++;
    }
}

//--------------------------------------------------------------
void ofApp::level1Setup(){
    ofResetElapsedTimeCounter();
    ofDisableArbTex();

    for(unsigned int i=0; i<65536; i++) keys[i] = 0;
    bgImage.load("thunderstorm-3625405_1920.jpg");

    // create world
    dInitODE2(0);
    world = dWorldCreate();
    space = dHashSpaceCreate (0);
    contactgroup = dJointGroupCreate (0);
    dWorldSetGravity (world,0,0,-0.5);
    ground = dCreatePlane (space,0,0,1,0);

    dAllocateODEDataForThread(dAllocateMaskAll);

    /* Graphics ground plane */
    mGround.set(128,256);
    mGround.mapTexCoords(0,0,8,8);
    mGround.setResolution(128,128);

    if(!ofLoadImage(mGroundTex, "unnamed.png")) { std::cerr << "Failed to load ground texture." << std::endl; }
    mGroundTex.setTextureWrap(GL_REPEAT, GL_REPEAT);

    panda = new PandaPlayer(0,-64,1, world, space);

    /* Boundaries */
    lGroundln = dCreateBox(space,1,256,1);
    dGeomSetPosition (lGroundln,-23,0,-.49);
    rGroundln = dCreateBox(space,1,256,1);
    dGeomSetPosition (rGroundln,23,0,-.49);
    finishln = dCreateBox(space,46,1,1);
    dGeomSetPosition(finishln,0,66,-.49);

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

    /* camera */
    ofVec3f upVector;
    upVector.set(0, 0, 1);
    camera.setAutoDistance(false);
    camera.setNearClip(0.01);
    camera.setPosition(panda->getX(),panda->getY()-5,panda->getZ()+2);
    camera.lookAt({panda->getX(),panda->getY(),panda->getZ()},upVector);
    camera.setUpAxis(upVector);
    camera.disableMouseInput();
    camera.disableMouseMiddleButton();

    /* Setting random positions */
    float ranX[3];

    ranX[0] = ofRandom(-21,-12);
    ranX[1] = ofRandom(-7,7);
    ranX[2] = ofRandom(12,21);

    float ranX2[3];

    ranX2[0] = ofRandom(-21,-12);
    ranX2[1] = ofRandom(-7,7);
    ranX2[2] = ofRandom(12,21);


    for(unsigned int p=0; p<40; p++) {
        chests.push_back(new Chest(ofRandom(-21,21),ofRandom(-55,55), 1, world, space) );
    }

    for(unsigned int p=0; p<3; p++) {
        canList.push_back((new Cannon(ranX[p], -2, 1.2, world, space)));
    }

    for(unsigned int p=0; p<3; p++) {
        canList2.push_back((new Cannon(ranX2[p], 50, 1.2, world, space)));
    }

    /* Setting the positions of the ball of the cannons */
    for(auto x : canList ){
        x->ballSetup(x->x,x->y-5,x->z+.6,world,space);
    }

    for(auto x : canList2 ){
        x->ballSetup(x->x,x->y-5,x->z+.6,world,space);
    }

    /* Loading sound, images and font */
    gameSound.load("FunkFromTheTrunk-FULL.mp3");
    gameSound.setLoop(true);
    gameSound.play();

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
    ofResetElapsedTimeCounter();
}

void ofApp::level1Update(){
    removeChest();

    /* When you get to the end or die go to ending screen */
    if(health <= 0){
        switchLev = 11;
        hasDied = true;
        lvl1ON = true;
        finalScore = ofGetElapsedTimef();
        cout<< "My Score " <<finalScore<<endl;
    }

    if(panda->getY() > 66){
        switchLev = 11;
        lvl1ON = true;
        finalScore = ofGetElapsedTimef();
        cout<<"My score " << finalScore<<endl;
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

    /* What to do when the ball is in the world */
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

    /* Resetting the panda or ball */
    if(move == true){
        panda->setPosition(ofRandom(panda->getX()-5,panda->getX()+5),panda->getY()-10,panda->getZ());
        move =false;
    }if(toStart == true){
        panda->setPosition(0,-64,1);
        toStart = false;
    }
    if(ballCol == true){
        ball->setPosition(ball->x, ball->y,-40);
        ballCol = false;
    }

    /* Cannon shoot when the panda is past a specific point */
    if(panda->getY() > -60){
        for(auto x : canList){
            x->setSpeed(-.5);
        }

        cannonLogic();
    }
    if(panda->getY() > 2){
        for(auto x : canList2){
            x->setSpeed(-.5);
        }
        cannonLogic2();
    }

    /* Panda's boundaries */
    if(cheat == false){
        if(panda->getX() >= 23){
            toStart = true;
        }if( panda->getX() < -23){
            toStart = true;
        }
    }
    if(panda->getY() < -70){
        toStart = true;
    }

    /* Shield logic */
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
    /* Draw the scene */
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

    mGroundTex.bind();
    mGround.draw();
    mGroundTex.unbind();

    /* Boundaries */
    const dReal* llP = dGeomGetPosition(lGroundln);
    const dReal* rrP = dGeomGetPosition(rGroundln);
    const dReal* fnP = dGeomGetPosition(finishln);
    dVector3 ll; dVector3 rr; dVector3 ff;
    dGeomBoxGetLengths (lGroundln,ll);
    dGeomBoxGetLengths (rGroundln,rr);
    dGeomBoxGetLengths(finishln,ff);

    /* Left side line */
    ofPushMatrix();
    ofSetColor(ofColor::red);
    ofTranslate(llP[0],llP[1],llP[2]);
    ofDrawBox(ll[0],ll[1],ll[2]);
    ofPopMatrix();
    /* Rightside line */
    ofPushMatrix();
    ofSetColor(ofColor::red);
    ofTranslate(rrP[0],rrP[1],rrP[2]);
    ofDrawBox(rr[0],rr[1],rr[2]);
    ofPopMatrix();
    /* Finish line */
    ofPushMatrix();
    ofSetColor(ofColor::red);
    ofTranslate(fnP[0],fnP[1],fnP[2]);
    ofDrawBox(ff[0],ff[1],ff[2]);
    ofPopMatrix();

    /* Draw panda ball chests cannons */
    ofSetColor(ofColor::white);
    panda->draw();
    if(seeBall) ball->draw();

    for(auto x: chests ) x->draw();


    for(auto x : canList){
        x->draw();
        x->drawBall();
    }

    for(auto x : canList2){
        x->draw();
        x->drawBall();
    }

    ofSetColor(ofColor::white);
    ofDisableDepthTest();
    camera.end();

    /* The text you see pop up on the screen */
    if(((int) ofGetElapsedTimef() - shieldTime) > 1){
        if(isShield == true) {isShield = false;}
    }
    if(((int) ofGetElapsedTimef() - point2Time) > 1){
        if(is2Point == true) {is2Point = false;}
    }
    if(((int) ofGetElapsedTimef() - pointTime) > 1){
        if(isPoint == true) {isPoint = false;}
    }
    if(((int) ofGetElapsedTimef() - cPointTime) > 1){
        if(isCPoints == true) {isCPoints = false;}
    }

    if(isShield == true){
        upTex.drawString("+1 Shield",10,360);
    }if(is2Point == true){
        upTex.drawString("+3 Points",10,330);
    }if(isPoint == true){
        upTex.drawString("+1 Points",10,300);
    }if(shieldEnd == true){
        upTex.drawString("Shield activated",10,250);
    }if(isCPoints == true){
        upTex.drawString("+5 Points",10,390);
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
void ofApp::startSetup(){
    /* Start screen */
    startBg.load("planet-2120004_1920.jpg");
    startSt.load("Start_BTN.png");
    startEn.load("Exit_BTN.png");

    startSound.load("zapsplat_multimedia_game_zap_laser_006_24951.mp3");
}

void ofApp::startDraw(){
    startBg.draw(0,0);
    ofSetColor(startBTN);
    startSt.draw((ofGetWindowWidth()/2)-200,ofGetWindowHeight()/2 -130);
    ofSetColor(quitBTN);
    startEn.draw((ofGetWindowWidth()/2)-200,(ofGetWindowHeight()/2));
    ofSetColor(ofColor::white);
}

//--------------------------------------------------------------
void ofApp::level1Exit(){
    /* What to do at exit */
    for(auto x : canList){
        dGeomDestroy(x->mGeom);
        dGeomDestroy(x->bGeom);
    }

    for(auto x : canList2){
            dGeomDestroy(x->mGeom);
            dGeomDestroy(x->bGeom);
     }
    for(auto x : chests){
        dGeomDestroy(x->mGeom);
    }
    canList.clear();
    canList2.clear();
    chests.clear();
    dGeomDestroy(panda->mGeom);
    if(fireBall) dGeomDestroy(ball->mGeom);
    dJointGroupDestroy (contactgroup);
    dSpaceDestroy (space);
    dWorldDestroy (world);
    dCloseODE();
}

//--------------------------------------------------------------
void ofApp::end1Setup(){
    /* Ending screen */
    ofSetColor(ofColor::white);
    endBg.load("planet-2120004_1920.jpg");
    endRe.load("Replay_BTN.png");
    endEx.load("Exit_BTN.png");
    endTex.load("vag.ttf", 40);
    endRe.resize(70,70);
    endEx.resize(205,60);
    ofSetColor(ofColor::white);
}

void ofApp::end1Draw(){
    ofSetColor(ofColor::white);
    endBg.draw(0,0);

    endSBTN = ofColor::white;
    endRe.draw(300, 550);
    endQBTN = ofColor::white;
    endEx.draw(550,550);

    float score = (float) points/finalScore;
    float endScore = (float) score*100;
    int theScore = (int) endScore;
    ofSetColor(ofColor::white);

    ofSetColor(255,122,220);
    if(points >= 20 && hasDied == false){
        endTex.drawString("Congrats, \nYou got a score of \n" + ofToString(theScore), (ofGetWindowWidth()/2)-250,(ofGetWindowHeight()/2)-100);
    }
    if(points < 20 && hasDied == false){
        endTex.drawString("Unfortunately \nyou didn't make it, \nYou got a score of \n" + ofToString(theScore), (ofGetWindowWidth()/2)-250,(ofGetWindowHeight()/2)-100);
    } if(hasDied == true){
        endTex.drawString("You died, \nYou got a score of \n" + ofToString(theScore), (ofGetWindowWidth()/2)-250,(ofGetWindowHeight()/2)-100);
    }
}

void ofApp::removeChest(){
    /* This removes the chests at specific locations */
    for(auto x : chests){
        if(x->y > -7 && x->y < 3){
            x->disable();
            cout<<"goodby 10"<<endl;
        }
        if(x->y > 50 ){
            x->disable();
            cout<<"goodby 50"<<endl;
        }
        if(x->x > 25 || x->x < -25){
            x->disable();
            cout<<"goodby 25"<<endl;
        }
    }
}
