/*
  ==============================================================================

    LPF.h
    Created: 8 Mar 2021 2:59:03pm
    Author:  Rodolfo Ortiz

  ==============================================================================
*/

#pragma once

class FirstOrderLPF {
public:
    float processSample(float x, int channel) {
        float y = (0.5f * x) + (0.5f * ff[channel]);
        ff[channel] = x;
        return y;
    }
    
private:
    float ff[2] = {0.f};
};
