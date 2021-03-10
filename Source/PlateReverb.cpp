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
    preDelayDelay = (float)(delayTimes.preDelayTime * _sampleRate);
    
    //AllPassFilters
    apf1Delay = (float)(delayTimes.apf1DelayTime * _sampleRate);
    apf2Delay = (float)(delayTimes.apf2DelayTime * _sampleRate);
    apf3Delay = (float)(delayTimes.apf3DelayTime * _sampleRate);
    apf4Delay = (float)(delayTimes.apf4DelayTime * _sampleRate);
}

void PlateReverb::preparePlateReverb(double _sampleRate) {
    sampleRate = _sampleRate;
    
    //PreDelay
    preDelay.setSampleRate(_sampleRate);
    preDelay.setDelaySamples(preDelayDelay);
    preDelay.setDepth(10.0f);
    preDelay.setSpeed(1.0f);
    
    //Prepare AllPassFilters
    prepareAllPassFilters(apf_1, sampleRate, apf1Delay, 8.0f, 0.0f, g1);
    prepareAllPassFilters(apf_2, sampleRate, apf2Delay, 6.0f, 0.0f, g1);
    prepareAllPassFilters(apf_3, sampleRate, apf3Delay, 9.0f, 0.0f, g2);
    prepareAllPassFilters(apf_4, sampleRate, apf4Delay, 10.0f, 0.0f, g2);
    
}

void PlateReverb::prepareAllPassFilters(APF& apf, double& sampleRate, float& delay, float depth, float speed, float gain) {
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
        const float input = (left[i] * 0.5f) + (right[i] * 0.5f);
        
        //Pre Delay
        float out = preDelay.processSample(input, 1);
        out = lpf_1.processSample(out, 1);

        //Diffusion stage
        out = apf_1.processSample(out, 1);
        out = apf_2.processSample(out, 1);
        out = apf_3.processSample(out, 1);
        out = apf_4.processSample(out, 1);
        
        left[i] = (out * 0.5) + (left[i] * 0.5) ;
        right[i] = (out * 0.5) + (right[i] * 0.5);
    }
}
