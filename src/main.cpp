#include "ofMain.h"
#include "ofApp.h"
#include "ode/ode.h"

ofApp *myApp;

//========================================================================
int main( ){
    myApp = new ofApp();
    ofSetupOpenGL(1024,768,OF_WINDOW);
    ofRunApp(myApp);
}
