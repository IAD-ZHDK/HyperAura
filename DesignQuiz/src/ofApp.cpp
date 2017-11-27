#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // Drawing Content Setup:
    
    ofBackground(54, 54, 54, 255);
    bg.loadImage("images/bg.jpg");
    bg.resize(ofGetWidth(), ofGetHeight());
    
    // Font Setup
    ofTrueTypeFont::setGlobalDpi(72);
    
    helvetica30.loadFont("HelveticaNeue.ttf", 30, true, true);
    helvetica30.setLetterSpacing(1.037);
    helvetica30.setEncoding(OF_ENCODING_UTF8);
    
    font.setup("Vera.ttf", 1.0, 1024, false, 8);
    
    // JSON Setup
    std::string file = "quizQnA.json";
    bool parsingSuccessful = qContent.open(file);
    
    if (parsingSuccessful)
    {
        ofLogNotice("ofApp::setup") << qContent.getRawString();
    }
    
    // Serial Setup
    serial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    int baud = 9600;
	serial.setup(0, baud); //open the first device
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    int serialByte = 0;
    
    if (ofGetSeconds()%10 == 0 && timerFlag == true) {
        timer += 1;
        timerFlag = false;
        answerChosen = false;
        random_shuffle(&aList[0], &aList[3]);
        for (int i=0; i<5; i++) {
            content[i] = getJsonContent(ofToString(timer), i);
        }
        
    } else if (ofGetSeconds()%10 == 1) {
        timerFlag = true;
    }
    
    if (timer > 25)
        timer = 1;
   
    
    serialByte = getSerialContent();
    
    if (serialByte > 0) {
    
        printf("I Received: %d", serialByte);
        chosenAnswer = serialByte;
        answerChosen = true;
        
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(255);
 //   bg.draw(0, 0);
    
    theY = 30;
    
    int numLines = 0;
    bool wordsWereCropped;
    
    //string s = "aslkdjaskljd lakhds aklshd  askjd alkshd  hjaskldhalk sd";
    
    ofRectangle column =  font.drawMultiLineColumn(content[0],
                                                   30,
                                                   theX, theY,
                                                   (ofGetWidth()-50),
                                                   numLines,
                                                   false,
                                                   4,
                                                   true,
                                                   &wordsWereCropped);
    
    theY += column.height + 25;
 
    
    for (int i = 1; i < 5; i++) {
  
        if (answerChosen && i == chosenAnswer){
            if (aList[i] == 1) {
            ofSetColor(50, 255, 50);
            }
            else {
            ofSetColor(255, 50, 50);
            }
        }
        else {
            ofSetColor(255);
        }
   
        int cnt = aList[i-1];
        
        ofRectangle column =  font.drawMultiLineColumn(content[cnt],
                                                       30,
                                                       theX, theY,
                                                       (ofGetWidth()-50),
                                                       numLines,
                                                       false,
                                                       4,
                                                       true,
                                                       &wordsWereCropped);
        
        theY += column.height + 25;
        
        
    }
   
   
    
    /*
    
    for (int i = 0; i < 5; i++) {
    
    string content = getJsonContent(ofToString(timer), i);
    
    //string s = "aslkdjaskljd lakhds aklshd  askjd alkshd  hjaskldhalk sd";
    
    ofRectangle column =  font.drawMultiLineColumn(content,
                                                   30,
                                                   theX, theY,
                                                   (ofGetWidth()-50),
                                                   numLines,
                                                   false,
                                                   4,
                                                   true,
                                                   &wordsWereCropped);
    
    theY += column.height + 25;
        
    }
     
     */
    
    /*
    
    content = getJsonContent("2", 1);
    
    column = font.drawMultiLineColumn(content,
                                      30,
                                      theX, theY,
                                      (ofGetWidth()-30),
                                      numLines,
                                      false,
                                      4,
                                      true,
                                      &wordsWereCropped);
     
     */
    
    //helvetica30.drawString(getJsonContent("2", 0), 30, 30);
    //helvetica30.drawString(getJsonContent("2", 1), 30, 60);
    //helvetica30.drawString(getJsonContent("2", 2), 30, 90);
    //helvetica30.drawString(getJsonContent("2", 3), 30, 120);
    //helvetica30.drawString(getJsonContent("2", 4), 30, 150);

}

//--------------------------------------------------------------
string ofApp::getJsonContent(string key, int identifier){
    string content;
    
    if (identifier == 1) {
    
        content = qContent[key]["Richtige Antwort"].asString();
        
    } else if (identifier == 2){
        
        content = qContent[key]["Falsche Antwort 1"].asString();
    
    } else if (identifier == 3){
        
        content = qContent[key]["Falsche Antwort 2"].asString();
    
    } else if (identifier == 4) {
        
        content = qContent[key]["Falsche Antwort 3"].asString();
    
    } else if (identifier == 0) {
    
        content = qContent[key]["Vertiefungsspezifische Frage"].asString();
    }
    
    return content;
}

//--------------------------------------------------------------
int ofApp::getSerialContent(){
    
    int myByte = 0;
    int out = 0;
    
    if(serial.available() > 0) {

        myByte = serial.readByte();
        if ( myByte == OF_SERIAL_NO_DATA ) {
            printf("no data was read");
        }
        else if ( myByte == OF_SERIAL_ERROR ) {
            printf("an error occurred");
        }
        else {
        //    printf("myByte is %d", myByte);
            serial.drain();
            out = myByte;
        }
    }
    
    return out;
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
