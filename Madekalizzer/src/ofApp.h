#pragma once

#include "ofMain.h"
#include "mPlane.h"

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
        void resizePlane(float w, float h);
    
    private:
    
        mPlane **myPlane;
        int nPlanes;
        float planeDimX = 300.0f;
        float planeDimY = 200.0f;
        float gap = 5.0f;
		
};
