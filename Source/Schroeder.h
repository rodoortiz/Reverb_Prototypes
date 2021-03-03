/*
  ==============================================================================

    Schroeder.h
    Created: 2 Mar 2021 7:27:52pm
    Author:  Rodolfo Ortiz

  ==============================================================================
*/

#pragma once

#include "FBCF.h"
#include "APF.h"
using namespace std;

class Schroeder {
    
public:
    
    // Constructor function (special function - no return type, name = Class name)
    Schroeder();
    
    // Destructor
    ~Schroeder();
    
    float processSample(float x, int channel);

    void setFs(float Fs);
    
    void setFeedbackGain(float feedbackGain);
    
    void setDiffusionGain(float diffusionGain);
    
    void setDepth(float depth);

    
private:
    
    float Fs = 48000.f;
    
    FBCF fbcf1 {1426.f, 0.723f};
    FBCF fbcf2 {1781.f, 1.257f};
    FBCF fbcf3 {1973.f, 0.893f};
    FBCF fbcf4 {2098.f, 1.111f};
    
    APF apf1{240.f, 0.8321f}, apf2{82.f, 0.964f};
    
    float feedbackGain = 0.5f;
    float diffusionGain = 0.5f;
    
    float depth = 10.0f; // percentage of intensity, control amp of LFO
};

