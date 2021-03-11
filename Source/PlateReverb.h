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
        double convertionSR = 29800.0; //Sample rate value for conversion
        
        //Values in milliseconds
        double preDelayTime = 0.150;
        
        double apf1DelayTime = (142.0 / convertionSR);
        double apf2DelayTime = (107.0 / convertionSR);
        double apf3DelayTime = (379.0 / convertionSR);
        double apf4DelayTime = (277.0 / convertionSR);
        double apf5DelayTime = (2656.0 / convertionSR);
        double apf6DelayTime = (1800.0 / convertionSR);
        
        double modApf1DelayTime = (908.0 / convertionSR);
        double modApf2DelayTime = (672.0 / convertionSR);
        
        double delay1Time = (4217.0 / convertionSR);
        double delay2Time = (4453.0 / convertionSR);
        double delay3Time = (3136.0 / convertionSR);
        double delay4Time = (3720.0 / convertionSR);
        
    } delayTimes;
    
    struct DelayTaps {
        double convertionSR = 29800.0; //Sample rate value for conversion
        
        //Look name reference in Will Pirkle Book pg.476
        //Values in milliseconds
        double yL_a_1 = (266.0 / convertionSR);
        double yL_a_2 = (2974.0 / convertionSR);
        double yL_b = (1913.0 / convertionSR);
        double yL_c = (1996.0 / convertionSR);
        double yL_d = (1990.0 / convertionSR);
        double yL_e = (187.0 / convertionSR);
        double yL_f = (1066.0 / convertionSR);
        
        double yR_d_1 = (353.0 / convertionSR);
        double yR_d_2 = (3627.0 / convertionSR);
        double yR_e = (1228.0 / convertionSR);
        double yR_f = (2673.0 / convertionSR);
        double yR_a = (2111.0 / convertionSR);
        double yR_b = (335.0 / convertionSR);
        double yR_c = (121.0 / convertionSR);
        
    } delayTaps;
    
    PlateReverb();
    ~PlateReverb();
    
    void prepareDelayValues(double _sampleRate);
    void preparePlateReverb(double _sampleRate);
    void prepareAllPassFilters(APF& apf, double& sampleRate, int& delay, float depth, float speed, float gain);
    
    void processPlateReverb(AudioBuffer<float>& buffer, float& wetDryValue);
    
    template <typename ProcessContext>
    void process (const ProcessContext& context) noexcept;

    void processMono (float* const samples, const int numSamples) noexcept;
    void processStereo (float* const left, float* const right, const int numSamples) noexcept;
    
private:
    double sampleRate = 48000.0;
    
    float wetLevel = 0.0f;
    float dryLevel = 0.0f;
    
    //Delays in samples
    int preDelayDelay;
    int apf1Delay, apf2Delay, apf3Delay, apf4Delay, apf5Delay, apf6Delay;
    int modApf1Delay, modApf2Delay;
    int delay1Delay, delay2Delay, delay3Delay, delay4Delay;
    //Gains
    float g1{0.75f}, g2{0.625f}, g3{0.5f}, g4{-0.7f}, g5{0.3f};
    
    float outLeftTank{0.0f}, outRightTank{0.0f};
    
    //Modules
    FractionalDelay preDelay{0, 0.0f, 0.0f};
    FractionalDelay delay1{0, 0.0f, 0.0f}, delay2{0, 0.0f, 0.0f}, delay3{0, 0.0f, 0.0f}, delay4{0, 0.0f, 0.0f};
    FirstOrderLPFfb lpf_1, lpf_2, lpf_3;
    APF apf_1, apf_2, apf_3, apf_4, apf_5, apf_6;
    APF modApf_1, modApf_2;
};
