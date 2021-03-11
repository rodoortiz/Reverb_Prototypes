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
    
    y = outDL1 + (feedbackGain * inDL1);
    
    fb1[channel] = outDL1;
    
    return y;

}

void APF::setSampleRate(double _sampleRate){
    this->sampleRate = _sampleRate;
    fractionalDelay.setSampleRate(_sampleRate);
}

void APF::setFeedbackGain(float feedbackGain) {
    this->feedbackGain = feedbackGain;
}

void APF::setDelayDepth(float depth){
    fractionalDelay.setDepth(depth);
}

void APF::setDelayTime(float delay) {
    fractionalDelay.setDelaySamples(delay);
}

void APF::setDelaySpeed(float speed) {
    fractionalDelay.setSpeed(speed);
}
