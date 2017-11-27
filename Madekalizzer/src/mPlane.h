//
//  mPlane.h
//  Madekalizzer
//
//  Created by Klaus on 21/05/15.
//
//

#ifndef __Madekalizzer__mPlane__
#define __Madekalizzer__mPlane__

#include <stdio.h>
#include "ofMain.h"
#include "ofURLFileLoader.h"

class mPlane {
    
public: // place public functions or variables declarations here
    
    // methods, equivalent to specific functions of your class objects
    void update();  // update method, used to refresh your objects properties
    void draw();    // draw method, this where you'll do the object's drawing
    void urlResponse(ofHttpResponse & response);
    void loadImg(string URL);
    void resize(float x, float y, float dimX, float dimY);
    
    // variables
    float pos[2];
    float dim[2];
    bool loading;
    
    mPlane(float x, float y, float dimX, float dimY);
    
private: // place private functions or variables declarations here
    ofPlanePrimitive plane;
    ofImage texture;
    ofRectangle target, source;
    
}; // dont't forget the semicolon!!

#endif /* defined(__Madekalizzer__mPlane__) */
