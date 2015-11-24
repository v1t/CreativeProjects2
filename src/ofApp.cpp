#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    cout << "listening for osc messages on port " << RECEIVEPORT << "\n";
    sender.setup("localhost", SENDPORT);
    receiver.setup(RECEIVEPORT);

    
    //reserve space for AnalogValue array.
    analogValue.reserve(numPins);
    
    font.load("franklinGothic.otf", 20);
    
//    for( auto & pv : potValue ){
//        pv = "analog pin:";
//    }

    
    //using stadard firmata example/library
    //default baud rate is 57600
    //use terminal comand: ls /dev/tty.*    to find hardware address

    ard.connect("/dev/tty.usbmodem1421", 57600);
    
    /*this second line of code adds the listener to oF. It checks every frame to see if an event called EInitialized has fired. It also needs to know what object the event should be attached to. The keyword - this - in programming is a pointer to the current object, in this case, the ofApp instance. Next, it wants to know what function to run when the event occurs. We tell it to fire the function setupArd in the ofApp class.*/
    
    ofAddListener(ard.EInitialized, this, &ofApp::setupArd);
    isMessageSent = false;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    updateArduino();
    
    //SEND TO WEKINATOR
    ofxOscMessage toWeki;
    toWeki.setAddress("/wek/inputs");
    toWeki.addFloatArg(analogValue[0]);
    toWeki.addFloatArg(analogValue[1]);
    
    sender.sendMessage(toWeki);
    isMessageSent = true;
    
    //RECEIVE FROM WEKINATOR
        while(receiver.hasWaitingMessages()){
            // get the next message
            ofxOscMessage toWeki;
            receiver.getNextMessage(&toWeki);
    
            if(toWeki.getAddress() == "/wek/outputs"){
                message = toWeki.getArgAsFloat(0);
                rad = message;
            }
}
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);
    ofSetColor(0);
    ofFill();
    

    for(int i = 0 ; i < numPins; i++){
        font.drawString("AnalogPin num:"+ofToString(i)+" - "+ofToString(analogValue[i]), 0, 100+100*i);
    }
        ofPushMatrix();
        ofTranslate(ofGetWidth()-200, ofGetHeight()/2);
    
        //ofSetColor(20, 200, 200);
        ofNoFill();
        ofDrawBezier(-550, 0,  -256, -500*rad, 256, 110*rad, 550, 0);
    
        ofSetColor(255, 255, 255);
        ofDrawBitmapString(rad, 0, 0);
        ofPopMatrix();

    
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
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
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

void ofApp::setupArd(const int &version)
{

    for(int i = 0; i < numPins; i++){
        
            ard.sendAnalogPinReporting(i, ARD_ANALOG);
        }
    
    
    // Listen for changes on analog pins
    ofAddListener(ard.EAnalogPinChanged, this, &ofApp::analogPinChanged);
    
}

//--------------------------------------------------------------
void ofApp::updateArduino(){
    
    // update the arduino, get any data or messages.
    // the call to ard.update() is required
    ard.update();
}

//--------------------------------------------------------------
void ofApp::analogPinChanged(const int & pinNum) {
    // do something with the analog input. here we're simply going to print the pin number and
    // value to the screen each time it changes
    for(int i=0; i<numPins; i++){
        analogValue[i] = ard.getAnalog(i);
    }
    
}

