/*
  ==============================================================================

    PlateReverb.h
    Created: 5 Mar 2021 8:05:48pm
    Author:  Rodolfo Ortiz

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "FractionalDelay.hpp"
#include "APF.h"
#include "LPF.h"

class PlateReverb {
public:
    struct DelayTimes {
        double preDelayTime = 0.185;
        
        double apf1DelayTime = 0.00476;
        double apf2DelayTime = 0.00359;
        double apf3DelayTime = 0.01271;
        double apf4DelayTime = 0.00929;
        double apf5DelayTime = 0.08912;
        double apf6DelayTime = 0.00604;
        
    } delayTimes;
    
    PlateReverb();
    ~PlateReverb();
    
    void prepareDelayValues(double _sampleRate);
    void preparePlateReverb(double _sampleRate);
    void prepareAllPassFilters(APF& apf, double& sampleRate, float& delay, float depth, float speed, float gain);
    
    void processPlateReverb(AudioBuffer<float>& buffer, float& depthValue);
    
    template <typename ProcessContext>
    void process (const ProcessContext& context) noexcept;

    void processMono (float* const samples, const int numSamples) noexcept;

    void processStereo (float* const left, float* const right, const int numSamples) noexcept;
    
private:
    double sampleRate = 48000;
    float preDelayDelay;
    float apf1Delay, apf2Delay, apf3Delay, apf4Delay, apf5Delay, apf6Delay;
    float g1{0.75f}, g2{0.625f}, g3{0.5f}, g4{0.7f}, g5{0.5f};
    
    FractionalDelay preDelay{0.0f, 0.0f, 0.0f};
    FirstOrderLPFfb lpf_1, lpf_2, lpf_3;
    APF apf_1, apf_2, apf_3, apf_4, apf_5, apf_6;
    
    
};
