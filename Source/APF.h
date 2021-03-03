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
    
    // Constructor function (special function - no return type, name = Class name)
    APF();
    
    APF(float delay, float speed);
    
    // Destructor
    ~APF();
    
    float processSample(float x, int channel);

    void setFs(float Fs);
    
    void setFeedbackGain(float feedbackGain);
    
    void setDepth(float depth);

    void setDelay(float delay) {
        fractionalDelay.setDelaySamples(delay);
    };
    
    void setSpeed(float speed) {
        fractionalDelay.setSpeed(speed);
    }
    
private:
    
    float Fs = 48000.f;
    
    FractionalDelay fractionalDelay {240.f, 0.7f};
    
    float feedbackGain = 0.5f;
    
    //With feeback you need multiple channels
    float fb1[2] = {0.0f};
    
//    float speed = 1.0f; // Hz, frequency of LFO
    float depth = 10.0f; // percentage of intensity, control amp of LFO
};

