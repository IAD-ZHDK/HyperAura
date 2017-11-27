//
//  mPlane.cpp
//  Madekalizzer
//
//  Created by Klaus on 21/05/15.
//
//

#include "mPlane.h"

mPlane::mPlane(float _x, float _y, float _dimX, float _dimY)
{
    
    pos[0] = _x;
    pos[1] = _y;
    dim[0] = _dimX;
    dim[1] = _dimY;
    
    //ofDisableArbTex();
    texture.loadImage("rio.jpg");
    source.set(0.f, 0.f, texture.getWidth(), texture.getHeight());
    texture.getTextureReference().setTextureWrap( GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER );
    plane.set(dim[0], dim[1], 2, 2);
    target.set(0.f, 0.f, plane.getWidth(), plane.getHeight());
    source.scaleTo(target,OF_SCALEMODE_FILL);
    plane.mapTexCoords((source.getWidth()-plane.getWidth())*0.5f, (source.getHeight()-plane.getHeight())*0.5f,(source.getWidth()+plane.getWidth())*0.5f, (source.getHeight()+plane.getHeight())*0.5f );
    plane.setPosition(pos[0], pos[1], 0);
}

void mPlane::urlResponse(ofHttpResponse & response){
    if(response.status==200 && response.request.name == "async_read"){
        texture.loadImage(response.data);
        source.set(ofGetWidth()*.5f, ofGetHeight()*.5f, texture.getWidth(), texture.getHeight());
        loading=false;
    }else{
        cout << response.status << " " << response.error << endl;
        if(response.status!=-1) loading=false;
    }
}

void mPlane::loadImg(string _URL) {
    texture.clear();
    ofLoadURLAsync(_URL,"async_read");
    loading =true;
}

void mPlane::update(){

}

void mPlane::draw(){
    texture.getTextureReference().bind();
    //plane.setPosition(ofGetWidth()*.5f, ofGetHeight()*.5f, 0);
    plane.draw();
    texture.getTextureReference().unbind();
}

void mPlane::resize(float _x, float _y, float _dimX, float _dimY)
{
    
    float newPos[2];
    float newdim[2];
    newPos[0] = _x;
    newPos[1] = _y;
    newdim[0] = _dimX;
    newdim[1] = _dimY;
    
    //ofDisableArbTex();
    plane.set(newdim[0], newdim[1], 2, 2);
    target.set(0.f, 0.f, plane.getWidth(), plane.getHeight());
    source.scaleTo(target,OF_SCALEMODE_FILL);
    plane.mapTexCoords((source.getWidth()-plane.getWidth())*0.5f, (source.getHeight()-plane.getHeight())*0.5f,(source.getWidth()+plane.getWidth())*0.5f, (source.getHeight()+plane.getHeight())*0.5f );
    plane.setPosition(newPos[0], newPos[1], 0);
}
