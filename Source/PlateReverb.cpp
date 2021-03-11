/*
  ==============================================================================

    PlateReverb.cpp
    Created: 5 Mar 2021 8:05:48pm
    Author:  Rodolfo Ortiz

  ==============================================================================
*/

#include "PlateReverb.h"

PlateReverb::PlateReverb() {
}

PlateReverb::~PlateReverb() {
    
}

//Should be set before preparePlateReverb, converts delay in seconds to delay in samples
void PlateReverb::prepareDelayValues(double _sampleRate) {
    //PreDelay
    preDelayDelay = (int)(delayTimes.preDelayTime * _sampleRate);
    
    //AllPassFilters
    apf1Delay = (int)(delayTimes.apf1DelayTime * _sampleRate);
    apf2Delay = (int)(delayTimes.apf2DelayTime * _sampleRate);
    apf3Delay = (int)(delayTimes.apf3DelayTime * _sampleRate);
    apf4Delay = (int)(delayTimes.apf4DelayTime * _sampleRate);
    apf5Delay = (int)(delayTimes.apf5DelayTime * _sampleRate);
    apf6Delay = (int)(delayTimes.apf6DelayTime * _sampleRate);
    
    //ModAllPassFilters
    modApf1Delay = (int)(delayTimes.modApf1DelayTime * _sampleRate);
    modApf2Delay = (int)(delayTimes.modApf1DelayTime * _sampleRate);
    
    //Delays
    delay1Delay = (int)(delayTimes.delay1Time * _sampleRate);
    delay2Delay = (int)(delayTimes.delay2Time * _sampleRate);
    delay3Delay = (int)(delayTimes.delay3Time * _sampleRate);
    delay4Delay = (int)(delayTimes.delay4Time * _sampleRate);
}

void PlateReverb::preparePlateReverb(double _sampleRate) {
    sampleRate = _sampleRate;
    
    //PreDelay
    preDelay.setSampleRate(_sampleRate);
    preDelay.setDelaySamples(preDelayDelay);
    preDelay.setDepth(10.0f);
    preDelay.setSpeed(1.0f);
    
    //Prepare AllPassFilters
    prepareAllPassFilters(apf_1, sampleRate, apf1Delay, 8.0f, 0.5f, g1);
    prepareAllPassFilters(apf_2, sampleRate, apf2Delay, 6.0f, 0.9f, g1);
    prepareAllPassFilters(apf_3, sampleRate, apf3Delay, 9.0f, 0.6f, g2);
    prepareAllPassFilters(apf_4, sampleRate, apf4Delay, 10.0f, 0.3f, g2);
    prepareAllPassFilters(apf_5, sampleRate, apf5Delay, 0.0f, 0.0f, g3);
    prepareAllPassFilters(apf_6, sampleRate, apf6Delay, 0.0f, 0.0f, g3);
    
    //Prepare ModAllPassFilters
    prepareAllPassFilters(modApf_1, sampleRate, modApf1Delay, 10.0, 1.0f, g4);
    prepareAllPassFilters(modApf_2, sampleRate, modApf2Delay, 10.0, 1.0f, g4);
    
    //Prepare Delays in Tank
    delay1.setSampleRate(_sampleRate);
    delay1.setDelaySamples(delay1Delay);
    delay2.setSampleRate(_sampleRate);
    delay2.setDelaySamples(delay2Delay);
    delay3.setSampleRate(_sampleRate);
    delay3.setDelaySamples(delay3Delay);
    delay4.setSampleRate(_sampleRate);
    delay4.setDelaySamples(delay4Delay);
    
}

void PlateReverb::prepareAllPassFilters(APF& apf, double& sampleRate, int& delay, float depth, float speed, float gain) {
    apf.setSampleRate(sampleRate);
    apf.setDelayTime(delay);
    apf.setDelayDepth(depth);
    apf.setDelaySpeed(speed);
    apf.setFeedbackGain(gain);
}


void PlateReverb::processPlateReverb(AudioBuffer<float>& buffer, float& depthValue) {
    auto audioBlock = dsp::AudioBlock<float> (buffer);
    auto context = dsp::ProcessContextReplacing<float>(audioBlock);
    process(context);
}

/** Applies the reverb to a mono or stereo buffer. */
template <typename ProcessContext>
void PlateReverb::process (const ProcessContext& context) noexcept
{
    const auto& inputBlock = context.getInputBlock();
    auto& outputBlock = context.getOutputBlock();
    const auto numInChannels = inputBlock.getNumChannels();
    const auto numOutChannels = outputBlock.getNumChannels();
    const auto numSamples = outputBlock.getNumSamples();

    jassert (inputBlock.getNumSamples() == numSamples);

    outputBlock.copyFrom (inputBlock);

//    if (! enabled || context.isBypassed)
//        return;

    if (numInChannels == 1 && numOutChannels == 1)
    {
        processMono (outputBlock.getChannelPointer (0), (int) numSamples);
    }
    else if (numInChannels == 2 && numOutChannels == 2)
    {
        processStereo (outputBlock.getChannelPointer (0),
                              outputBlock.getChannelPointer (1),
                              (int) numSamples);
    }
    else
    {
        jassertfalse;   // invalid channel configuration
    }
}

/** Applies the reverb to a single mono channel of audio data. */
void PlateReverb::processMono (float* const samples, const int numSamples) noexcept
{
    jassert (samples != nullptr);

    for (int i = 0; i < numSamples; ++i)
    {
        const float input = samples[i];
        const float out = preDelay.processSample(input, 1);
        
        samples[i] = (out * 0.5) + (samples[i] * 0.5);
    }
}

/** Applies the reverb to two stereo channels of audio data. */
void PlateReverb::processStereo (float* const left, float* const right, const int numSamples) noexcept
{
    jassert (left != nullptr && right != nullptr);

    for (int i = 0; i < numSamples; ++i)
    {
        //Make mono
        const float input = (left[i] * 0.5f) + (right[i] * 0.5f);
        
        //Pre Delay
        float outPreDelay = preDelay.processSample(input, 1);
        float outDiffusion = lpf_1.processSample(outPreDelay, 1);

        //Diffusion stage
        outDiffusion = apf_1.processSample(outDiffusion, 1);
        outDiffusion = apf_2.processSample(outDiffusion, 1);
        outDiffusion = apf_3.processSample(outDiffusion, 1);
        outDiffusion = apf_4.processSample(outDiffusion, 1);
        
        //Input to Reverb Tanks
        float inLeftTank = outDiffusion + outRightTank;
        float inRightTank = outDiffusion + outLeftTank;
        
        //Left Tank Process
        float tempOutLeftTank = modApf_1.processSample(inLeftTank, 1);
        tempOutLeftTank = delay1.processSample(tempOutLeftTank, 1);
        tempOutLeftTank = lpf_2.processSample(tempOutLeftTank, 1);
        tempOutLeftTank = apf_5.processSample(tempOutLeftTank, 1);
        tempOutLeftTank = delay2.processSample(tempOutLeftTank, 1);
        outLeftTank = tempOutLeftTank * g5;
        
        //Right Tank Process
        float tempOutRightTank = modApf_2.processSample(inRightTank, 1);
        tempOutRightTank = delay3.processSample(tempOutRightTank, 1);
        tempOutRightTank = lpf_3.processSample(tempOutRightTank, 1);
        tempOutRightTank = apf_6.processSample(tempOutRightTank, 1);
        tempOutRightTank = delay4.processSample(tempOutRightTank, 1);
        outRightTank = tempOutRightTank * g5;
        
        //Output taps
        
        
        //Output
        left[i] = (outDiffusion * 0.5) + (left[i] * 0.5) ;
        right[i] = (outDiffusion * 0.5) + (right[i] * 0.5);
    }
}
