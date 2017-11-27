#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include "ofQTKitPlayer.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <string>

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        string jsonUrl = "https://medienarchiv.zhdk.ch/api/media-entries/?collection_id=ffa90881-9388-42ba-be18-b30e97f24b5c&public_get_metadata_and_previews=true&me_get_full_size=true&page=";
        //string downloadUrl = "http://medienarchiv.zhdk.ch/download?id=";
        string downloadUrl ="https://medienarchiv.zhdk.ch/api/media-files/";
        string moviesPath = "movs/";
        string hypausername = "USER";
        string hypapass = "PASSWORD";

        void getContent(ofxJSONElement &oldJson, ofxJSONElement &newJson);
        void deleteOldContent(ofxJSONElement &oldJson, ofxJSONElement &newJson);
        void updateContent();
        void loadMovie ();
        void updateMovie ();
        void updateContentEveryHour ();
        ofxJSONElement madekSetIdsToJson();

        ofxJSONElement      oldJson;
        ofxJSONElement      tempJson;
        ofxJSONElement      newJson;
        ofBuffer            inBuffer;
        ofBuffer            outBuffer;
        ofFile              file;
        ofDirectory         movieFolder;

        //instead of using ofVideoPlayer we use the ofQTKitPlayer directly
        ofQTKitPlayer moviePlayer;
        ofQTKitDecodeMode decodeMode = OF_QTKIT_DECODE_TEXTURE_ONLY;
        bool frameByframe;
        bool updatingFiles = false;
        bool playerLoaded = false;
        bool playerLoading = true;
        bool isImage = false;
        bool downloadingContent = true;
        bool firstDraw = false;
        bool updateNoticeDrawn = false;
        bool updateNow = false;
        int currentMovie = 0;
        int movieLength = 0;
        int pastHour = 0;
        float oldTime = 0.0f;
        float delayTime = 15.0f;
};
