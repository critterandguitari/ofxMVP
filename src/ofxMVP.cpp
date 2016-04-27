#include "ofxMVP.h"

MVP::MVP(){
}

void MVP::setup(ofBaseApp * app){
	// listen on the given port
	cout << "listening for osc messages on port " << PORT << "\n";
	receiver.setup(PORT);
   
	int bufferSize = 256;
	
	left.assign(bufferSize, 0.0);
	leftavg.assign(bufferSize, 0.0);
	right.assign(bufferSize, 0.0);
	
    smoothedVol     = 0.0;
	scaledVol		= 0.0;
	bufferCounter	= 0;

    //if you want to set a different device id 
    soundStream.printDeviceList();
    soundStream.setDeviceID(2); //bear in mind the device id corresponds to all audio devices, including  input-only and output-only devices.
    bufferCounter = 0;
    newSound = false;

    // just so something is in there
    knob1=knob2=knob3=knob4=knob5=knob6=knob7=knob8=.5;

    // 0 out, 2 in, sr, buf size, latency (bufs)
	soundStream.setup(app, 0, 2, 11025, bufferSize, 2);

}

void MVP::update(){
	//lets scale the vol up to a 0-1 range 
	scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);


	// check for waiting messages
	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(m);
        if(m.getAddress() == "/pot/1") knob1 = m.getArgAsFloat(0);
		if(m.getAddress() == "/pot/2") knob2 = m.getArgAsFloat(0);
		if(m.getAddress() == "/pot/3") knob3 = m.getArgAsFloat(0);
		if(m.getAddress() == "/pot/4") knob4 = m.getArgAsFloat(0);
		if(m.getAddress() == "/pot/5") knob5 = m.getArgAsFloat(0);
		if(m.getAddress() == "/pot/6") knob6 = m.getArgAsFloat(0);
		if(m.getAddress() == "/pot/7") knob7 = m.getArgAsFloat(0);
		if(m.getAddress() == "/pot/8") knob8 = m.getArgAsFloat(0);
		
        if(m.getAddress() == "/key/1") key1 = m.getArgAsInt32(0);
		if(m.getAddress() == "/key/2") key2 = m.getArgAsInt32(0);
		if(m.getAddress() == "/key/3") key3 = m.getArgAsInt32(0);
		if(m.getAddress() == "/key/4") key4 = m.getArgAsInt32(0);
		if(m.getAddress() == "/key/5") key5 = m.getArgAsInt32(0);
		if(m.getAddress() == "/key/6") key6 = m.getArgAsInt32(0);
		if(m.getAddress() == "/key/7") key7 = m.getArgAsInt32(0);
		if(m.getAddress() == "/key/8") {
            if ( m.getArgAsInt32(0) ) {  // only if pressed
                img.grabScreen(0,0,ofGetWidth(),ofGetHeight());
                string fileName = "snapshot_"+ofToString(10000+snapCounter)+".png";
                cout << "saving " + fileName + "...";
                img.save("/media/pi/ORGANELLE/Grabs/" + fileName);
                //img.save("/home/pi/" + fileName);
                cout << "saved\n";
                snapCounter++;
            }
        }
	}
}

void MVP::draw(){
    //ofSetColor(ofRandom(255),ofRandom(255),ofRandom(255));
    //ofDrawCircle(100, 100, 10);


}

//--------------------------------------------------------------
void MVP::audioIn(float * input, int bufferSize, int nChannels){	
	
    float curVol = 0.0;
	
	// samples are "interleaved"
	int numCounted = 0;	

	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume	
	for (int i = 0; i < bufferSize; i++){
		left[i]		= input[i*2]*0.5;
		right[i]	= input[i*2+1]*0.5;

        newSound = true;
		
        curVol += left[i] * left[i];
		curVol += right[i] * right[i];
		numCounted+=2;
	}
	
	//this is how we get the mean of rms :) 
	curVol /= (float)numCounted;
	
	// this is how we get the root of rms :) 
	curVol = sqrt( curVol );
	
	smoothedVol *= 0.93;
	smoothedVol += 0.07 * curVol;
	
	bufferCounter++;
}
