/*
  ==============================================================================

    PlateReverb.h
    Created: 5 Mar 2021 8:05:48pm
    Author:  Rodolfo Ortiz

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SimpleDelay.h"
#include "FractionalDelay.hpp"
#include "APF.h"
#include "LPF.h"

class PlateReverb {
public:
    struct DelayTimes {
        double convertionSR = 29800.0; //Sample rate value for conversion
        
        //Values in milliseconds
        double preDelayTime = 0.030;
        
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
    void prepareJuceDspModules(const dsp::ProcessSpec& spec);
    
    void processPlateReverb(AudioBuffer<float>& buffer, float& wetDryValue, float& bwValue, float& dampingValue, float& decayValue);
    
    template <typename ProcessContext>
    void process (const ProcessContext& context) noexcept;

    void processMono (float* const samples, const int numSamples) noexcept;
    void processStereo (float* const left, float* const right, const int numSamples) noexcept;
    
    void setFiltersCutoffFreq(float& cutOffValue);
    
private:
    double sampleRate = 48000.0;
    
    //PARAMETERS
    float wetLevel = 0.0f;
    float dryLevel = 0.0f;
    float bandwith = 0.5f;
    float damping = 0.5f;
    float decay = 0.5f;
    
    //DELAYS (IN SAMPLES)
    int preDelayDelay;
    //AllPass
    int apf1Delay;
    int apf2Delay;
    int apf3Delay;
    int apf4Delay;
    int apf5Delay;
    int apf6Delay;
    
    int modApf1Delay;
    int modApf2Delay;
    
    int delay1Delay;
    int delay2Delay;
    int delay3Delay;
    int delay4Delay;
    
    //GAINS
    float g1 {0.75f};
    float g2 {0.625f};
    float g3 {0.5f};
    float g4 {-0.7f};
    float g5 {0.3f};
    
    float outLeftTank {0.0f};
    float outRightTank {0.0f};
    
    //MODULES
    dsp::FirstOrderTPTFilter<float> lpf_bandwith; //Filter used instead of lpf_1, we can change cutoffFreq with this one
    
    //Delays
//    SimpleDelay preDelay_1{0};
    FractionalDelay preDelay{0, 0.0f, 0.0f};
    FractionalDelay delay1{0, 0.0f, 0.0f};
    FractionalDelay delay2{0, 0.0f, 0.0f};
    FractionalDelay delay3{0, 0.0f, 0.0f};
    FractionalDelay delay4{0, 0.0f, 0.0f};
    //LowPass Filters
    FirstOrderLPFfb lpf_1;
    FirstOrderLPFfb lpf_2;
    FirstOrderLPFfb lpf_3;
    //AllPass Filters
    APF apf_1;
    APF apf_2;
    APF apf_3;
    APF apf_4;
    APF apf_5;
    APF apf_6;
    //AllPass Filters Modulated
    APF modApf_1;
    APF modApf_2;
};
