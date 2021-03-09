/*
  ==============================================================================

    FBCF.cpp
    Created: 2 Mar 2021 7:17:40pm
    Author:  Rodolfo Ortiz

  ==============================================================================
*/

#include "FBCF.h"

FBCF::FBCF(){
}

FBCF::FBCF(float delay, float speed) {
    fractionalDelay.setDelaySamples(delay);
    fractionalDelay.setSpeed(speed);
}

FBCF::FBCF(float delay, float speed, float apfDelay, float apfSpeed) {
    fractionalDelay.setDelaySamples(delay);
    fractionalDelay.setSpeed(speed);
    apf.setDelay(apfDelay);
    apf.setSpeed(apfSpeed);
    apf.setFeedbackGain(0.2f);
    apf.setDepth(3.0f);
}

// Destructor
FBCF::~FBCF(){
}


float FBCF::processSample(float x, int channel){
    float y;
    
    float inDL1 = x + (-feedbackGain) * fb1[channel];
    
    float outDL1 = fractionalDelay.processSample(inDL1, channel);
    
    y = outDL1; //Dividing by 2 because where are doubling signal in this point

//    fb1[channel] = lpf.processSample(outDL1, channel);
    fb1[channel] = apf.processSample(outDL1, channel);
    
    return y;

}

void FBCF::setFs(float Fs){
    this->Fs = Fs;
    fractionalDelay.setSampleRate(Fs);
    apf.setFs(Fs);
}

void FBCF::setFeedbackGain(float feedbackGain) {
    this->feedbackGain = feedbackGain;
}

void FBCF::setDepth(float depth){

    this->depth = depth;
    fractionalDelay.setDepth(depth);
}
