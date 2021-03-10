/*
  ==============================================================================

    FDN.cpp
    Created: 25 Feb 2021 9:05:40pm
    Author:  Rodolfo Ortiz

  ==============================================================================
*/

#include "FDN.h"

FDN::FDN(){
//    fractionalDelay1.setDelaySamples(1789.0f);
//    fractionalDelay2.setDelaySamples(2281.0f);
}

FDN::~FDN(){
}

float FDN::processSample(float x, int channel){
    float y;
    
    float inDL1 = x + fb1[channel];
    float inDL2 = x + fb2[channel];
    float inDL3 = x + fb3[channel];
    float inDL4 = x + fb4[channel];
    
    float outDL1 = fractionalDelay1.processSample(inDL1, channel);
    float outDL2 = fractionalDelay2.processSample(inDL2, channel);
    float outDL3 = fractionalDelay3.processSample(inDL3, channel);
    float outDL4 = fractionalDelay4.processSample(inDL4, channel);
    
    y = 0.25f * (outDL1 + outDL2 + outDL3 + outDL4); //Dividing by 2 because where are doubling signal in this point

    fb1[channel] = (-outDL2 + outDL3) * feebackGain;
    fb2[channel] = (outDL1 + outDL4) * feebackGain;
    fb3[channel] = (outDL1 + -outDL4) * feebackGain;
    fb4[channel] = (-outDL2 + -outDL3) * feebackGain;
    
    return y;

}

void FDN::setFs(float Fs){
    this->Fs = Fs;
    fractionalDelay1.setSampleRate(Fs);
    fractionalDelay2.setSampleRate(Fs);
}

void FDN::setTime(float timeValue){

    feebackGain = timeValue;
}

void FDN::setDepth(float depth){

    this->depth = depth;
    fractionalDelay1.setDepth(depth);
    fractionalDelay2.setDepth(depth);
    fractionalDelay3.setDepth(depth);
    fractionalDelay4.setDepth(depth);
}
