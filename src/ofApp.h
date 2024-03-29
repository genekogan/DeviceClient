#pragma once

#include "ofMain.h"

#include "ofxOsc.h"
#include "ofxLibwebsockets.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofxLibwebsockets::Client client;
    
    // websocket methods
    void onConnect( ofxLibwebsockets::Event& args );
    void onOpen( ofxLibwebsockets::Event& args );
    void onClose( ofxLibwebsockets::Event& args );
    void onIdle( ofxLibwebsockets::Event& args );
    void onMessage( ofxLibwebsockets::Event& args );
    void onBroadcast( ofxLibwebsockets::Event& args );
    
    ofxOscSender osc;
    
    bool isRegistered = false;
    bool toRegister = true;
    int nValues = 0;
    void registerClient() {
        ofxOscMessage msg;
        msg.setAddress("/register");
        msg.addStringArg("TheServer");
        cout << "RIGSTER WITH " << nValues << endl;
        msg.addIntArg(nValues);
        isRegistered = true;
        cout << "REGISTR!!!" << endl;
        osc.sendMessage(msg);
    }
};

