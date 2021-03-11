//
//  FractionalDelay.cpp
//
//  Created by Eric Tarr on 2/6/20.
//  Copyright © 2020 Eric Tarr. All rights reserved.
//

#include "FractionalDelay.hpp"


FractionalDelay::FractionalDelay(){
}

FractionalDelay::FractionalDelay(int _delay, float _speed){
    this->delay = _delay;
    this->speed = _speed;
}

FractionalDelay::FractionalDelay(int _delay, float _speed, float _depth){
    this->delay = _delay;
    this->speed = _speed;
    this->depth = _depth;
}

// Destructor
FractionalDelay::~FractionalDelay(){
}


float FractionalDelay::processSample(float x, int channel){
    
    if (delay < 1.f){
        return x;
    }
    else{
        float lfo;
        
        lfo = depth * sin(currentAngle[channel]);
        
        currentAngle[channel] += angleChange;
        if (currentAngle[channel] > 2.f * M_PI){
            currentAngle[channel] -= 2.f * M_PI;
        }
        
        // Delay Buffer
        // "delay" can be fraction
        int d1 = floor(delay+lfo);
        int d2 = d1 + 1;
        float g2 = (float)delay + lfo - (float)d1;
        float g1 = 1.0f - g2;
        
        indexD1 = index[channel] - d1;
        if (indexD1 < 0){
            indexD1 += MAX_BUFFER_SIZE;
        }
        
        indexD2 = index[channel] - d2;
        if (indexD2 < 0){
            indexD2 += MAX_BUFFER_SIZE;
        }
        
        float y = g1 * delayBuffer[indexD1][channel] + g2 * delayBuffer[indexD2][channel];
        
        delayBuffer[index[channel]][channel] = x;
        
        if (index[channel] < MAX_BUFFER_SIZE - 1){
            index[channel]++;
        }
        else{
            index[channel] = 0;
        }
        
        return y;
    }
}

void FractionalDelay::setSampleRate(double _sampleRate){
    this->sampleRate = _sampleRate;
}


void FractionalDelay::setDelaySamples(int delay){
    if (delay >= 1.f){
        this->delay = delay;
    }
    else{
        this->delay = 0.f;
    }
}


void FractionalDelay::setSpeed(float speed){
    if (speed >= 0.1f && speed <= 10.0f){
        this->speed = speed;
        angleChange = speed * (1.f/(float)sampleRate) * 2 * M_PI;
    }
}

void FractionalDelay::setDepth(float depth){

    this->depth = depth;
}

float FractionalDelay::getDelaySampleAtMiliSec(double delaySampleAtMiliSec) {
    int delaySamplePos = delaySampleAtMiliSec * sampleRate; //Convert from mili seconds to samples and give sample position to obtain
    
}
