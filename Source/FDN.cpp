/*
  ==============================================================================

    FDN.cpp
    Created: 25 Feb 2021 9:05:40pm
    Author:  Rodolfo Ortiz

  ==============================================================================
*/

#include "FDN.h"

FDN::FDN(){
    fractionalDelay1.setDelaySamples(1789.0f);
    fractionalDelay2.setDelaySamples(2281.0f);
}

// Destructor
FDN::~FDN(){
}


float FDN::processSample(float x, int channel){
    float y;
    
    float inDL1 = x + fb1[channel] + fb3[channel];
    float inDL2 = x + fb2[channel] + fb4[channel];
    
    float outDL1 = fractionalDelay1.processSample(inDL1, channel);
    float outDL2 = fractionalDelay2.processSample(inDL2, channel);
    
    y = 0.5f * (outDL1 + outDL2); //Dividing by 2 because where are doubling signal in this point

    fb1[channel] = outDL1 * g11 * feebackGain;
    fb2[channel] = outDL1 * g12 * feebackGain;
    fb3[channel] = outDL2 * g21 * feebackGain;
    fb4[channel] = outDL2 * g22 * feebackGain;
    
    return y;

}

void FDN::setFs(float Fs){
    this->Fs = Fs;
    fractionalDelay1.setFs(Fs);
    fractionalDelay2.setFs(Fs);
}

void FDN::setTime(float timeValue){

    feebackGain = timeValue;
}

void FDN::setDepth(float depth){

    this->depth = depth;
}
