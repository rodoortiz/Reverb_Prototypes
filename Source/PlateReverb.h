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
        //Values in milliseconds
        double preDelayTime = 0.185;
        
        double apf1DelayTime = 0.00476;
        double apf2DelayTime = 0.00359;
        double apf3DelayTime = 0.01271;
        double apf4DelayTime = 0.00929;
        double apf5DelayTime = 0.08912;
        double apf6DelayTime = 0.00604;
        
        double modApf1DelayTime = 0.03046;
        double modApf2DelayTime = 0.02255;
        
        double delay1Time = 0.14151;
        double delay2Time = 0.14942;
        double delay3Time = 0.10523;
        double delay4Time = 0.12483;
        
    } delayTimes;
    
    struct DelayTaps {
        //Look name reference in Will Pirkle Book pg.476
        //Values in milliseconds
        double yL_a_1 = 0.00892;
        double yL_a_2 = 0.09979;
        double yL_b = 0.06419;
        double yL_c = 0.06697;
        double yL_d = 0.06677;
        double yL_e = 0.00627;
        double yL_f = 0.03577;
        
        double yR_d_1 = 0.01184;
        double yR_d_2 = 0.12171;
        double yR_e = 0.04120;
        double yR_f = 0.08969;
        double yR_a = 0.07083;
        double yR_b = 0.01124;
        double yR_c = 0.00406;
        
    } delayTaps;
    
    PlateReverb();
    ~PlateReverb();
    
    void prepareDelayValues(double _sampleRate);
    void preparePlateReverb(double _sampleRate);
    void prepareAllPassFilters(APF& apf, double& sampleRate, int& delay, float depth, float speed, float gain);
    
    void processPlateReverb(AudioBuffer<float>& buffer, float& depthValue);
    
    template <typename ProcessContext>
    void process (const ProcessContext& context) noexcept;

    void processMono (float* const samples, const int numSamples) noexcept;
    void processStereo (float* const left, float* const right, const int numSamples) noexcept;
    
private:
    double sampleRate = 48000;
    
    //Delays in samples
    int preDelayDelay;
    int apf1Delay, apf2Delay, apf3Delay, apf4Delay, apf5Delay, apf6Delay;
    int modApf1Delay, modApf2Delay;
    int delay1Delay, delay2Delay, delay3Delay, delay4Delay;
    //Gains
    float g1{0.75f}, g2{0.625f}, g3{0.5f}, g4{-0.7f}, g5{0.5f};
    
    float outLeftTank{0.0f}, outRightTank{0.0f};
    
    //Modules
    FractionalDelay preDelay{0, 0.0f, 0.0f};
    FractionalDelay delay1{0, 0.0f, 0.0f}, delay2{0, 0.0f, 0.0f}, delay3{0, 0.0f, 0.0f}, delay4{0, 0.0f, 0.0f};
    FirstOrderLPFfb lpf_1, lpf_2, lpf_3;
    APF apf_1, apf_2, apf_3, apf_4, apf_5, apf_6;
    APF modApf_1, modApf_2;
};
