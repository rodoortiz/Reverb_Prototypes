/*
  ==============================================================================

    FBCF.h
    Created: 2 Mar 2021 7:17:40pm
    Author:  Rodolfo Ortiz

  ==============================================================================
*/

#pragma once

#include "FractionalDelay.hpp"
#include "APF.h"
using namespace std;

//Feedback Comb Filter
class FBCF {
    
public:
    
    // Constructor function (special function - no return type, name = Class name)
    FBCF();
    
    FBCF(float delay, float speed);
    
    FBCF(float delay, float speed, float apfDelay, float apfSpeed);
    
    // Destructor
    ~FBCF();
    
    float processSample(float x, int channel);

    void setFs(float Fs);
    
    void setFeedbackGain(float feedbackGain);
    void setDepth(float depth);

    
private:
    
    float Fs = 48000.f;
    
    FractionalDelay fractionalDelay {240.f, 0.7f};
    
    float feedbackGain = 0.5f;
    
    //With feeback you need multiple channels
    float fb1[2] = {0.0f};
    
    float depth = 10.0f; // percentage of intensity, control amp of LFO
    
    class SimpleLPF {
    public:
        float processSample(float x, int channel) {
            float y = (0.5f * x) + (0.5f * ff[channel]);
            ff[channel] = x;
            return y;
        }
        
    private:
        float ff[2] = {0.f};
    };
    
    SimpleLPF lpf;
    APF apf;
};
