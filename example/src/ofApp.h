#pragma once

#include "ofMain.h"
#include "ofxMultiDeviceSoundPlayer.h"
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
    
    
        ofxMultiDeviceSoundPlayer multiSpeakerPlayer1;
        ofxMultiDeviceSoundPlayer multiSpeakerPlayer2;
    

        string sound1str,sound2str;
        int sound1target,sound2target;
		
};
