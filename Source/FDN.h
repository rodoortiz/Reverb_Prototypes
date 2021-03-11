/*
  ==============================================================================

    FDN.h
    Created: 25 Feb 2021 9:05:40pm
    Author:  Rodolfo Ortiz

  ==============================================================================
*/

#pragma once

#include "FractionalDelay.hpp"
using namespace std;

//Fractional Delay Network
class FDN {
    
public:
    
    // Constructor function (special function - no return type, name = Class name)
    FDN();
    
    FDN(float delay, float speed);
    
    // Destructor
    ~FDN();
    
    float processSample(float x,int channel);

    void setFs(float Fs);
    
    void setTime(float timeValue);
    void setDepth(float depth);

    
private:
    
    double Fs = 48000.0;
    
    FractionalDelay fractionalDelay1 {1571, 0.7f};
    FractionalDelay fractionalDelay2 {2053, 0.9f};
    FractionalDelay fractionalDelay3 {2719, 1.1f};
    FractionalDelay fractionalDelay4 {3463, 1.3f};
    
//    float g11 = -1.0f;
//    float g12 = 1.0f;
//    float g21 = 1.0f;
//    float g22 = -1.0f;
    
    float feebackGain = 0.5f;
    
    //With feeback you need multiple channels
    float fb1[2] = {0.0f};
    float fb2[2] = {0.0f};
    float fb3[2] = {0.0f};
    float fb4[2] = {0.0f};
    
//    float speed = 1.0f; // Hz, frequency of LFO
    float depth = 10.0f; // percentage of intensity, control amp of LFO
};
