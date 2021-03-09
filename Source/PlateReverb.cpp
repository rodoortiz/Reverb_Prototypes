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
    preDelayDelay = (float)(delayTimes.preDelay * _sampleRate);
}

void PlateReverb::preparePlateReverb(double _sampleRate) {
    sampleRate = _sampleRate;
    preDelay.setSampleRate(_sampleRate);
    preDelay.setDelaySamples(preDelayDelay);
    preDelay.setDepth(0.0f);
    preDelay.setSpeed(0.0f);
}

void PlateReverb::processPlateReverb(AudioBuffer<float>& buffer) {
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
        const float out = preDelay.processSample(input, 1);
    
        left[i] = (out * 0.5) + (left[i] * 0.5) ;
        right[i] = (out * 0.5) + (right[i] * 0.5);
    }
}
