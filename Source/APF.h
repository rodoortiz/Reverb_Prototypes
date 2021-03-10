/*
  ==============================================================================

    APF.h
    Created: 2 Mar 2021 3:56:46pm
    Author:  Rodolfo Ortiz

  ==============================================================================
*/

#pragma once

#include "FractionalDelay.hpp"
using namespace std;

//All Pass Filter
class APF {
    
public:
    APF();
    APF(float delay, float speed);
    
    ~APF();
    
    float processSample(float x, int channel);

    void setSampleRate(float _sampleRate);
    void setFeedbackGain(float feedbackGain);
    void setDelayDepth(float depth);
    void setDelayTime(float delay);
    void setDelaySpeed(float speed);
    
private:
    float sampleRate = 48000.f;
    
//    FractionalDelay fractionalDelay {240.f, 0.7f};
    FractionalDelay fractionalDelay {0.0f, 0.0f};
    
    float feedbackGain = 0.5f;
    
    //With feeback you need multiple channels
    float fb1[2] = {0.0f};
};

