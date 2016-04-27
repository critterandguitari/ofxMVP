#ifndef _MVP 
#define _MVP 

#include "ofMain.h" 
#include "ofxOsc.h"

//#define PORT 12345
#define PORT 4000

class MVP {

    public: 

    void setup(ofBaseApp * app);  
    void update(); 
    void draw();    
    void audioIn(float * input, int bufferSize, int nChannels); 
		
    ofxOscReceiver receiver;
	ofSoundStream soundStream;
    float knob1;
    float knob2;
    float knob3;
    float knob4;
    float knob5;
    float knob6;
    float knob7;
    float knob8;
    int key1;
    int key2;
    int key3;
    int key4;
    int key5;
    int key6;
    int key7;
    int key8;
	
		vector <float> left;
		vector <float> right;
		vector <float> leftavg;

    unsigned int bufferCounter;
    bool newSound;
			
	int 				snapCounter;
	string 				snapString;
	ofImage 			img;
	
    float smoothedVol;
    float scaledVol;
	
    MVP();
    private:
}; 
#endif
