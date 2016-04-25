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
	
    //if you want to set a different device id 
    soundStream.printDeviceList();
    soundStream.setDeviceID(2); //bear in mind the device id corresponds to all audio devices, including  input-only and output-only devices.
    bufferCounter = 0;
    newSound = false;

    // just so something is in there
    knob1=knob2=knob3=knob4=knob5=knob6=knob7=knob8=.5;

    // 0 out, 2 in, sr, buf size, latency (bufs)
	soundStream.setup(app, 0, 2, 11025, bufferSize, 4);

}

void MVP::update(){

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
		if(m.getAddress() == "/key/8") key8 = m.getArgAsInt32(0);
		
	}


}

void MVP::draw(){
    //ofSetColor(ofRandom(255),ofRandom(255),ofRandom(255));
    //ofDrawCircle(100, 100, 10);


}

//--------------------------------------------------------------
void MVP::audioIn(float * input, int bufferSize, int nChannels){	

// the regular
	for (int i = 0; i < bufferSize; i++){
		left[i]		= input[i*2]*0.5;
		right[i]	= input[i*2+1]*0.5;
        newSound = true;
	}


/*
    // every 4th buffer, grab the left (which is summing) and 
    // average it..., then set newSound flag to true
    // this will happen 44100 / 256 / 4 times a second
	for (int i = 0; i < bufferSize; i++){
		left[i]		+= input[i*2];
		right[i]	= input[i*2+1]*0.5;

	}
	if (bufferCounter >= 3){
	    for (int i = 0; i < bufferSize; i++){
		    leftavg[i] = left[i] / 4;
		    left[i] = 0;	
		    newSound = true;
		    bufferCounter = 0;
	    }	 
	}
		
	bufferCounter++;
*/	
}
