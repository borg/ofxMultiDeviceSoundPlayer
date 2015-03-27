#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    //playerOpenAL.
    //playerFmod
    
    sound1target = 0;
    sound2target = 2;
    
   // multiSpeakerPlayer1.setMultiPlay(true);
    //multiSpeakerPlayer2.setMultiPlay(true);
    
    sound1str = "Four Tet - Rivers Become Oceans.wav";
    sound2str = "Miles Davis - Freddie Freeloader.wav";
    
    
    //ofMultiDeviceSoundPlayer::initializeFmodWithTargetDevice(0);
    //ofMultiDeviceSoundPlayer::initializeFmodWithTargetDevice(3);
    
    
    
    multiSpeakerPlayer1.loadSoundWithTarget(sound1str,sound1target);
    multiSpeakerPlayer2.loadSoundWithTarget(sound2str,sound2target);
   // multiSpeakerPlayer1.playTo(sound1target);
    //multiSpeakerPlayer2.playTo(sound2target);//normal head phones...mostly L
    
    
    multiSpeakerPlayer1.play();
    multiSpeakerPlayer1.setLoop(true);
    multiSpeakerPlayer2.play();
    multiSpeakerPlayer2.setLoop(true);
    
}

//--------------------------------------------------------------
void ofApp::update(){

    
}

//--------------------------------------------------------------
void ofApp::draw(){

    
    stringstream str;
    str<<"Sound device one: "<<sound1target<<" - press z x to change\n";
    str<<"Sound device two: "<<sound2target<<" - press , . to change\n";
    ofDrawBitmapString(str.str(), 30,30);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    
    if(key =='.'){
        sound2target++;
    }
    if(key ==','){
        sound2target--;
        if(sound2target<0){
            sound2target = 0;
        }
    }
    
    
    
    if(key =='x'){
        sound1target++;
    }
    if(key =='z'){
        sound1target--;
        if(sound1target<0){
            sound1target = 0;
        }
    }
    
    //multiSpeakerPlayer1.playTo(sound1target);
    //multiSpeakerPlayer2.playTo(sound2target);
    
    multiSpeakerPlayer1.loadSoundWithTarget(sound1str,sound1target);
    multiSpeakerPlayer2.loadSoundWithTarget(sound2str,sound2target);
    // multiSpeakerPlayer1.playTo(sound1target);
    //multiSpeakerPlayer2.playTo(sound2target);//normal head phones...mostly L
    
    
    multiSpeakerPlayer1.play();
    multiSpeakerPlayer1.setLoop(true);
    multiSpeakerPlayer2.play();
    multiSpeakerPlayer2.setLoop(true);
    
    
    cout<<"sound1target "<<sound1target<<" sound2target "<<sound2target<<endl;
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
