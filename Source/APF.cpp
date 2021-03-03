/*
  ==============================================================================

    APF.cpp
    Created: 2 Mar 2021 3:56:46pm
    Author:  Rodolfo Ortiz

  ==============================================================================
*/

#include "APF.h"

APF::APF(){
//    fractionalDelay1.setDelaySamples(1789.0f);
//    fractionalDelay2.setDelaySamples(2281.0f);
}

APF::APF(float delay, float speed) {
    fractionalDelay.setDelaySamples(delay);
    fractionalDelay.setSpeed(speed);
}

// Destructor
APF::~APF(){
}


float APF::processSample(float x, int channel){
    float y;
    
    float inDL1 = x + (-feedbackGain) * fb1[channel];
    
    float outDL1 = fractionalDelay.processSample(inDL1, channel);
    
    y = outDL1 + feedbackGain * inDL1; //Dividing by 2 because where are doubling signal in this point

    fb1[channel] = outDL1;
    
    return y;

}

void APF::setFs(float Fs){
    this->Fs = Fs;
    fractionalDelay.setFs(Fs);
}

void APF::setFeedbackGain(float feedbackGain) {
    this->feedbackGain = feedbackGain;
}

void APF::setDepth(float depth){

    this->depth = depth;
    fractionalDelay.setDepth(depth);
}
