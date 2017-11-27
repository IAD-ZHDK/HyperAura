#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);
    ofBackground(0);
    //ofDisableArbTex();
    float nOfPlanesX = floor(ofGetWidth()/planeDimX);
    float nOfPlanesY = floor(ofGetHeight()/planeDimY);
    float restX = ((ofGetWidth()-(planeDimX*nOfPlanesX))/nOfPlanesX)-(gap-(gap/nOfPlanesX));
    float restY = ((ofGetHeight()-(planeDimY*nOfPlanesY))/nOfPlanesY)-(gap-(gap/nOfPlanesY));
    float newPlaneDimX = planeDimX + restX;
    float newPlaneDimY = planeDimY + restY;
    nPlanes = (int)(nOfPlanesX*nOfPlanesY);
    
    ofLogNotice("ofApp::setup") << newPlaneDimX <<" "<< newPlaneDimY <<" "<<nPlanes;
    
    myPlane = new mPlane*[nPlanes];
    
    float theX = 0;
    float theY = 0;
    int theIndex = 0;
    
    
    for (int i = 0; i < (int)nOfPlanesX; i++){
        for (int j = 0; j < (int)nOfPlanesY; j++) {
            theX = ((i*(newPlaneDimX+gap))+(newPlaneDimX*0.5f));
            theY = ((j*(newPlaneDimY+gap))+(newPlaneDimY*0.5f));
            ofLogNotice("ofApp::setup1") << theX <<" "<< theY <<" "<< theIndex;
            
            myPlane[theIndex] = new mPlane(theX,theY,newPlaneDimX,newPlaneDimY);  // create each object from the array
            theIndex += 1;
        }
    }
    

}

//--------------------------------------------------------------
void ofApp::update(){
    
   // resizePlane(ofGetWidth(), ofGetHeight());

}

//--------------------------------------------------------------
void ofApp::draw(){
    for (int i = 0; i < nPlanes; i++){
        myPlane[i]->draw();
    }
    string info = ofToString(ofGetFrameRate(), 0)+" fps\n";
    ofDrawBitmapString(info, 15, 20);
}

//--------------------------------------------------------------
void ofApp::resizePlane(float w, float h){
    
    float nOfPlanesX = floor(w/planeDimX);
    float nOfPlanesY = floor(h/planeDimY);
    float restX = ((w-(planeDimX*nOfPlanesX))/nOfPlanesX)-(gap-(gap/nOfPlanesX));
    float restY = ((h-(planeDimY*nOfPlanesY))/nOfPlanesY)-(gap-(gap/nOfPlanesY));
    float newPlaneDimX = planeDimX + restX;
    float newPlaneDimY = planeDimY + restY;
    nPlanes = (int)(nOfPlanesX*nOfPlanesY);
    
    ofLogNotice("ofApp::resize") << w <<" "<< h <<" "<<nPlanes;
    
    
    float theX = 0.f;
    float theY = 0.f;
    int theIndex = 0;
    
    
    for (int i = 0; i < (int)nOfPlanesX; i++){
        for (int j = 0; j < (int)nOfPlanesY; j++) {
            theX = ((i*(newPlaneDimX+gap))+(newPlaneDimX*0.5f));
            theY = ((j*(newPlaneDimY+gap))+(newPlaneDimY*0.5f));
            //ofLogNotice("ofApp::setup1") << theX <<" "<< theY <<" "<< theIndex;
            
            myPlane[theIndex]->resize(theX,theY,newPlaneDimX,newPlaneDimY);  // create each object from the array
            theIndex += 1;
        }
    }

}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    switch(key) {
        case 'f':
            ofToggleFullscreen();
            break;
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
void ofApp::windowResized(int w, int h){
  
    /*
    float nOfPlanesX = floor(w/planeDimX);
    float nOfPlanesY = floor(h/planeDimY);
    float restX = ((w-(planeDimX*nOfPlanesX))/nOfPlanesX)-(gap-(gap/nOfPlanesX));
    float restY = ((h-(planeDimY*nOfPlanesY))/nOfPlanesY)-(gap-(gap/nOfPlanesY));
    float newPlaneDimX = planeDimX + restX;
    float newPlaneDimY = planeDimY + restY;
    nPlanes = (int)(nOfPlanesX*nOfPlanesY);
    
    ofLogNotice("ofApp::resize") << w <<" "<< h <<" "<<nPlanes;
    
    
    float theX = 0.f;
    float theY = 0.f;
    int theIndex = 0;
    
    
    for (int i = 0; i < (int)nOfPlanesX; i++){
        for (int j = 0; j < (int)nOfPlanesY; j++) {
            theX = ((i*(newPlaneDimX+gap))+(newPlaneDimX*0.5f));
            theY = ((j*(newPlaneDimY+gap))+(newPlaneDimY*0.5f));
            //ofLogNotice("ofApp::setup1") << theX <<" "<< theY <<" "<< theIndex;
            
            myPlane[theIndex]->resize(theX,theY,newPlaneDimX,newPlaneDimY);  // create each object from the array
            theIndex += 1;
        }
    }
     */

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
