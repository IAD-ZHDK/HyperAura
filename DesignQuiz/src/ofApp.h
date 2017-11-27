#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include "ofxFontStash.h"
#include "ofxOsc.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <algorithm>

// listen on port 12345
#define HOST "localhost"
#define PORT 12345
#define NUM_MSG_STRINGS 20

using namespace std;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        // Own Functions:

        string  getJsonContent(string key, int identifier);
        int getSerialContent();

        // Own Variables:

        string  content[5];
        float   theX = 30;
        float   theY = 30;
        int     timer = 1;
        bool    timerFlag = true;

        int     chosenAnswer = 1;
        bool    answerChosen = false;

        int aList[4] = {1, 2, 3, 4};

        // Own links:

        ofImage         bg;

        ofTrueTypeFont  helvetica30;
        ofxFontStash    font;

        ofxJSONElement  qContent;
        ofSerial        serial;

};
