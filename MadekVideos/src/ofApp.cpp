#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetFrameRate(30);
    ofSetVerticalSync(true);

    updateContent();

    ofBackground(0,0,0);

    frameByframe = false;
    moviePlayer.setPixelFormat(OF_PIXELS_RGB);
    moviePlayer.setSynchronousSeeking(false);
    // moviePlayer.getIsMovieDone();

    // ofHideCursor();


}

//--------------------------------------------------------------
void ofApp::update(){


    if (!updatingFiles) {
        if (!moviePlayer.getIsMovieDone() && playerLoaded){
            moviePlayer.update();
            if (isImage) {
                ofLogNotice("ofApp::image");
                if (ofGetElapsedTimef() > (oldTime + delayTime)) {
                    moviePlayer.setLoopState(OF_LOOP_NONE);
                    isImage = false;
                }
            }
        } else {
            ofLogNotice("ofApp::UpdateLoop, Loading");
            updateContentEveryHour();
            if (updateNoticeDrawn) {
                ofLogNotice("ofApp::UpdateLoop, Updating");
                updateContent();
                updateNoticeDrawn = false;
                updateNow = false;
            } else if (!downloadingContent){
                loadMovie();
            }
        }
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetHexColor(0xFFFFFF);



    if (moviePlayer.isLoaded())
    {
        //ofLogNotice("ofApp::Draw");
        moviePlayer.draw(0, 0);
    } else {
        ofLogNotice("ofApp::Draw Not loaded");
    }



    if (updateNow) {
        ofLogNotice("ofApp::Draw update");
        ofSetColor(0, 0, 0, 100);
        ofDrawPlane(ofGetWidth()*0.5, ofGetHeight()*0.5, ofGetWidth(), ofGetHeight());
        ofSetColor(255, 255, 255, 255);
        ofDrawBitmapString("Updating Files", ofGetWidth()*0.5f-10.0f, ofGetHeight()*0.5f);
        updateNoticeDrawn = true;
    }

}

//--------------------------------------------------------------
void ofApp::getContent(ofxJSONElement &oldeJson, ofxJSONElement &neweJson){

    for(unsigned int i = 0; i < neweJson["media-entries"].size(); ++i)
    {
        bool notFound = false;
        string newUuid = neweJson["media-entries"][i]["id"].asString();
        if (oldeJson["media-entries"].size() > 0) {
            for(unsigned int i = 0; i < oldeJson["media-entries"].size(); ++i)
            {
                string oldUuid = oldeJson["media-entries"][i]["id"].asString();
                if (oldUuid == newUuid) {
                    notFound = false;
                    break;
                } else {
                    notFound = true;
                }
            }
        } else {
            notFound = true;
        }

        if (notFound) {
        std::string url = downloadUrl+newUuid+"/data-stream";
        std::string filename = moviesPath+newUuid+".mov";
        ofSaveURLToAuth(url, filename, hypausername, hypapass);
        }
    }
}

//--------------------------------------------------------------
void ofApp::deleteOldContent(ofxJSONElement &oldeJson, ofxJSONElement &neweJson){

    for(unsigned int i = 0; i < oldeJson["media-entries"].size(); ++i)
    {
        bool notFound = false;
        string oldUuid = oldeJson["media-entries"][i]["id"].asString();
        if (neweJson["media-entries"].size() > 0) {
            for(unsigned int i = 0; i < neweJson["media-entries"].size(); ++i)
            {
                string newUuid = neweJson["media-entries"][i]["id"].asString();
                if (oldUuid == newUuid) {
                    ofLogNotice("ofApp::oldUUID") << oldUuid;
                    notFound = false;
                    break;
                } else {
                    ofLogNotice("ofApp::Not Found") << true;
                    notFound = true;
                }
            }
        } else {
            notFound = true;
        }

        if (notFound) {
            std::string filename = moviesPath+oldUuid+".mov";
            file.removeFile(filename);
        }
    }
}

//--------------------------------------------------------------

ofxJSONElement ofApp::madekSetIdsToJson() {

    ofxJSONElement returnJSON;
    ofxJSONElement mediaEntry;

    int page = 0;
    bool hasEntries = true;

    stringstream paginatedJsonUrl;

    paginatedJsonUrl << jsonUrl << page;

    std::stringstream tempUuidsToJson;

    tempUuidsToJson << "{";
    tempUuidsToJson << "\"media-entries\": [";

    bool newParsingSuccessful = returnJSON.openRemote(paginatedJsonUrl.str(), hypausername, hypapass);

    if (newParsingSuccessful){

        //ofLogNotice("ofApp::setup") << returnJSON.getRawString();

        for(unsigned int i = 0; hasEntries; i++){
            for(unsigned int i = 0; i < returnJSON["media-entries"].size(); ++i)
            {
                string uuid = returnJSON["media-entries"][i]["id"].asString();
                if (mediaEntry.openRemote("https://medienarchiv.zhdk.ch/api/media-entries/"+uuid)) {
                    uuid = mediaEntry["_json-roa"]["relations"]["media-file"]["href"].asString();
                    uuid = uuid.erase(0, 17);
                    ofLogNotice("uuid") << uuid;
                    tempUuidsToJson << "{ \"id\":" << "\"" << uuid << "\"" << "}";
                }
                if (!(returnJSON["media-entries"].size() < 10 && i == returnJSON["media-entries"].size() -1)) {
                    tempUuidsToJson << ",";
                }
            }
            page++;
            paginatedJsonUrl.str(std::string());
            paginatedJsonUrl << jsonUrl << page;
            newParsingSuccessful = returnJSON.openRemote(paginatedJsonUrl.str(), hypausername, hypapass);
            hasEntries = returnJSON["media-entries"].size() > 0;
            ofLogNotice("ofApp::arraySize") << returnJSON["media-entries"].size();
        }
    }

    tempUuidsToJson << "]";
    tempUuidsToJson << "}";

    returnJSON.parse(tempUuidsToJson.str());

    return returnJSON;
}

//--------------------------------------------------------------

void ofApp::updateContent() {

    ofLogNotice("ofApp::UpdateContent");

    updatingFiles = true;
    downloadingContent = true;

    movieFolder.close();

    // JSON Setup
    bool oldParsingSuccessful = oldJson.open("old_resources.json");

    if (!oldParsingSuccessful) {
        // Save new Empty Json
        string emptyString = "{}";
        oldJson.parse(emptyString);
        if (oldJson.save("old_resources.json")) {
            ofLogNotice("Saving OK");
        } else {
            ofLogNotice("Error Saving or parsing old JSON");
        }
    }

/*
    int page = 0;
    bool hasEntries = true;

    stringstream paginatedJsonUrl;

    paginatedJsonUrl << jsonUrl << page;

    std::stringstream uuidsToJson;

    uuidsToJson << "{";
    uuidsToJson << "\"media-entries\": [";

    // JSON Setup
    bool oldParsingSuccessful = oldJson.open("old_resources.json");

    if (!oldParsingSuccessful) {
        // Save new Empty Json
        string emptyString = "{}";
        oldJson.parse(emptyString);
        if (oldJson.save("old_resources.json")) {
            ofLogNotice("Saving OK");
        } else {
            ofLogNotice("Error Saving or parsing old JSON");
        }
    }

    bool newParsingSuccessful = tempJson.openRemote(paginatedJsonUrl.str());

    if (oldParsingSuccessful)
    {
        if (newParsingSuccessful){

            ofLogNotice("ofApp::setup") << newJson.getRawString();

            for(unsigned int i = 0; hasEntries; i++){
                for(unsigned int i = 0; i < tempJson["media-entries"].size(); ++i)
                {
                    string uuid = tempJson["media-entries"][i]["id"].asString();
                    uuidsToJson << "{ \"id\":" << "\"" << uuid << "\"" << "}";
                    if (!(tempJson["media-entries"].size() < 10 && i == tempJson["media-entries"].size() -1)) {
                        uuidsToJson << ",";
                    }
                    ofLogNotice("ofApp::Single ID") << uuid;
                }
                page++;
                paginatedJsonUrl.str(std::string());
                paginatedJsonUrl << jsonUrl << page;
                newParsingSuccessful = tempJson.openRemote(paginatedJsonUrl.str());
                hasEntries = tempJson["media-entries"].size() > 0;
                ofLogNotice("ofApp::arraySize") << tempJson["media-entries"].size();
            }
        }
    }


    uuidsToJson << "]";
    uuidsToJson << "}";

    ofLogNotice(uuidsToJson.str());

    newJson.parse(uuidsToJson.str());

 */
    newJson = madekSetIdsToJson();

    bool saveOK = newJson.save("new_resources.json", true);

    if (saveOK) {
        getContent(oldJson, newJson);
        deleteOldContent(oldJson, newJson);
    }

    oldJson = newJson;
    oldJson.save("old_resources.json", true);

    //ofSaveURLTo(jsonUrl,"old_resources.json");

    movieFolder.open(moviesPath);
    movieFolder.allowExt("mov");
    movieFolder.listDir();

    if (movieFolder.numFiles() == 0) {
        ofLogNotice("ofApp::Exit1 (No Files to Play");
        ofExit();
    }

    currentMovie = 0;
    downloadingContent = false;
    updateNow = false;
    updatingFiles = false;

}

//--------------------------------------------------------------

void ofApp::loadMovie() {

    int catcher = 0;

    playerLoaded = false;

reLoad:
    ofLogNotice("ofApp::Loading Movies");

    ofLogNotice("ofApp::Num") << currentMovie;
    ofLogNotice("ofApp::Max") << movieFolder.numFiles();
    string movPath = movieFolder.getPath(currentMovie);
    ofLogNotice("ofApp::Path") << movPath;

    moviePlayer.stop();
    moviePlayer.close();
    playerLoading = true;
    moviePlayer.loadMovie(movPath, decodeMode);
    currentMovie += 1;
    currentMovie %= movieFolder.numFiles();
 //   moviePlayer.play();
 //   moviePlayer.update();

//    while (!(moviePlayer.getHeight() > 3230 && moviePlayer.getWidth() > 1900)) {
//        moviePlayer.close();
//        currentMovie += 1;
//        currentMovie %= movieFolder.numFiles();
//        string movPath = movieFolder.getPath(currentMovie);
//        moviePlayer.loadMovie(movPath, decodeMode);
//   //     moviePlayer.play();
//   //     moviePlayer.update();
//        catcher += 1;
//
//        if (catcher > 4) {
//            ofLogNotice("ofApp::Exit (No Files to Play");
//            ofExit();
//        }
//
//    }

    playerLoading = false;
    if (true) {
        movieLength = (int)moviePlayer.getDuration();
        moviePlayer.play();
        moviePlayer.update();
        moviePlayer.draw(0, 0);
       // ofLogNotice("ofApp::Start Playback") << moviePlayer.getWidth();
        if (movieLength < 2) {
            oldTime = ofGetElapsedTimef();
            moviePlayer.setLoopState(OF_LOOP_NORMAL);
            isImage = true;
        } else {
            isImage = false;
            moviePlayer.setLoopState(OF_LOOP_NONE);
        }
        moviePlayer.setVolume(0.0f);
    }

    catcher += 1;
    if (!(moviePlayer.getWidth() > 3230 && moviePlayer.getHeight() > 1900)) {
        if (catcher > 4) {
            ofLogNotice("ofApp::Exit (No Files to Play");
            ofExit();
        }
        goto reLoad;
    }
    ofLogNotice("ofApp::Loading_Done");
    playerLoaded = moviePlayer.isLoaded();

}
//--------------------------------------------------------------

void ofApp::updateMovie() {

    moviePlayer.update();
    if (isImage) {
        if (ofGetElapsedTimef() > (oldTime + delayTime)) {
            moviePlayer.setLoopState(OF_LOOP_NONE);
            isImage = false;
        }
    }
}

//--------------------------------------------------------------

void ofApp::updateContentEveryHour () {
    if (!(pastHour == ofGetHours())) {
        ofLogNotice("ofApp::PastHour") << ofGetHours();
        bool oldParsingSuccessful = oldJson.open("old_resources.json");
        newJson = madekSetIdsToJson();
        if (oldParsingSuccessful)
        {
            if (true){
                ofLogNotice("ofApp::JsonCompare") << oldJson.operator!=(newJson);
                if (oldJson.operator!=(newJson)){
                    ofLogNotice("ofApp::true");
                    updateNow = true;
                }
            }
        }
        pastHour = ofGetHours();
        ofLogNotice("ofApp::PastHour") << pastHour;
    }

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

void ofApp::exit() {
//    moviePlayer.stop();
//    moviePlayer.close();
//    ofShowCursor();
}
