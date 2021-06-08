/*
  ==============================================================================

    LPF.h
    Created: 8 Mar 2021 2:59:03pm
    Author:  Rodolfo Ortiz

  ==============================================================================
*/

#pragma once

//Feed-Forward
class FirstOrderLPFff {
public:
    float processSample(float input, int channel)
    {
        float output = (0.5f * input) + (0.5f * feedForward[channel]); //Differential equation
        feedForward[channel] = input;
        return output;
    }
    
private:
    float feedForward[2] = {0.0f}; //Previous input value into feed-froward
};

//Feedback
class FirstOrderLPFfb {
public:
    float processSample(float input, int channel)
        {
        float output = (gain * input) + ((1 - gain) * feedBack[channel]); //Differential equation
        feedBack[channel] = output;
        return output;
    }
    
    void setGain(float newGain)
    {
        this->gain = newGain;
    }

private:
    float feedBack[2] = {0.0f}; //Previous output value into feedback
    float gain;
};
