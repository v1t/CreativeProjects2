#pragma once

#include "ofMain.h"
#include "ofxOSC.h"
#define RECEIVEPORT 12000
#define SENDPORT 6448

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
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofArduino ard;
    void setupArd(const int &version);
    void analogPinChanged(const int & pinNum);
    void updateArduino();
    
    ofTrueTypeFont		font;
    
    
    //number of pins used
    int numPins = 6;
    
    //readings from arduino
    vector<int> analogValue;
    
    bool bSetupArduino;
    
    //osc objects
    ofxOscSender sender;
    ofxOscReceiver receiver;
    
    bool isTraining;
    bool isMessageSent;
    
    int numOutputs = 3;
    float rad = 1;
    float message = 1;
    
    ofVec2f bez[3];
    
private:
    
};
