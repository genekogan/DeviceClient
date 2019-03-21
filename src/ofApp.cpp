#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetLogLevel(OF_LOG_VERBOSE);
    // basic connection:
    
    //    client.connect("dry-castle-73011.herokuapp.com", true);
    
    
    // OR optionally use SSL
    //     client.connect("echo.websocket.org", true);
    
    // 1 - get default options
    ofxLibwebsockets::ClientOptions options = ofxLibwebsockets::defaultClientOptions();
    
    // 2 - set basic params
    
    //options.host = "dry-castle-73011.herokuapp.com";
    options.host = "device-xyz.herokuapp.com";
    
    // advanced: set keep-alive timeouts for events like
    // loss of internet
    
    // 3 - set keep alive params
    // BIG GOTCHA: on BSD systems, e.g. Mac OS X, these time params are system-wide
    // ...so ka_time just says "check if alive when you want" instead of "check if
    // alive after X seconds"
    options.ka_time     = 1;
    options.ka_probes   = 1;
    options.ka_interval = 1;
    options.bUseSSL = false;
    options.port = 80;
    
    // 4 - connect
    client.connect(options);
    
    ofSetLogLevel(OF_LOG_ERROR);
    
    client.addListener(this);
    ofSetFrameRate(60);
    
    
    osc.setup("127.0.0.1", 12001);
    
    toRegister = false;
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofDrawBitmapString("Type anywhere to send 'hello' to your server\nCheck the console for output!", 10,20);
    ofDrawBitmapString(client.isConnected() ? "Client is connected" : "Client disconnected :(", 10,50);
}

//--------------------------------------------------------------
void ofApp::onConnect( ofxLibwebsockets::Event& args ){
    cout<<"on connected"<<endl;
}

//--------------------------------------------------------------
void ofApp::onOpen( ofxLibwebsockets::Event& args ){
    cout<<"on open"<<endl;
}

//--------------------------------------------------------------
void ofApp::onClose( ofxLibwebsockets::Event& args ){
    cout<<"on close"<<endl;
}

//--------------------------------------------------------------
void ofApp::onIdle( ofxLibwebsockets::Event& args ){
    cout<<"on idle"<<endl;
}

//--------------------------------------------------------------
void ofApp::onMessage( ofxLibwebsockets::Event& args ){
    //cout<<"got message "<<args.message<<endl;
    ofJson json = args.json;
    cout << json << endl;
    
    //return;
    ofxOscMessage msg;
    msg.setAddress("/shady/TheServer");
    
    nValues = 0;
    
    for (auto const &e1 : json["users"]) {
        ofJson s = e1;

        float x = ofMap(s["deviceData"]["x"], -180, 180, 0, 1);
        float y = ofMap(s["deviceData"]["y"], -90, 90, 0, 1);
        float z = ofMap(s["deviceData"]["z"], 0, 360, 0, 1);
        
        msg.addFloatArg(x);
        msg.addFloatArg(y);
        msg.addFloatArg(z);

        nValues += 3;
    }

    
    if (toRegister) {
        isRegistered = false;
        registerClient();
        toRegister = false;
    }
    
    if (isRegistered) {
        osc.sendMessage(msg);
    }
    
    
    
    return;
    
    int n = json["users"].size();
    for (int i=0; i<n; i++) {
        string id = json["users"][i]["id"];
        ofJson device = json["users"][i]["deviceData"];
        float x = ofMap(device["x"], -180, 180, 0, 1);
        float y = ofMap(device["y"], -90, 90, 0, 1);
        float z = ofMap(device["z"], 0, 360, 0, 1);
        
        msg.addFloatArg(x);
        msg.addFloatArg(y);
        msg.addFloatArg(z);
        
        nValues += 3;
    }
    
}

//--------------------------------------------------------------
void ofApp::onBroadcast( ofxLibwebsockets::Event& args ){
    cout<<"got broadcast "<<args.message<<endl;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    //client.send("Hello");
    //cout << "sending hello" <<endl;
    if (key=='r') {
        toRegister = true;
    }
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

