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
        double preDelay = 0.500;
    } delayTimes;
    
    PlateReverb();
    ~PlateReverb();
    
    void preparePlateReverb(double _sampleRate);
    void prepareDelayValues(double _sampleRate);
    
    void processPlateReverb(AudioBuffer<float>& buffer);
    
    template <typename ProcessContext>
    void process (const ProcessContext& context) noexcept;

    void processMono (float* const samples, const int numSamples) noexcept;

    void processStereo (float* const left, float* const right, const int numSamples) noexcept;
    
private:
    double sampleRate = 48000;
    float preDelayDelay;
    FractionalDelay preDelay{0.0f, 0.0f, 0.0f};
    
};
