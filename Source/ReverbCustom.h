/*
  ==============================================================================

    ReverbCustom.h
    Created: 28 Jun 2021 7:16:41pm
    Author:  Rodolfo Ortiz

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ReverbProcessorCustom.h"

class ReverbCustom
{
public:
    //==============================================================================
    /** Creates an uninitialised Reverb processor. Call prepare() before first use. */
    ReverbCustom() = default;

    //==============================================================================
    using Parameters = ReverbProcessorCustom::Parameters;

    /** Returns the reverb's current parameters. */
    const Parameters& getParameters() const noexcept    { return reverb.getParameters(); }

    /** Applies a new set of parameters to the reverb.
        Note that this doesn't attempt to lock the reverb, so if you call this in parallel with
        the process method, you may get artifacts.
    */
    void setParameters (const Parameters& newParams)    { reverb.setParameters (newParams); }

    /** Returns true if the reverb is enabled. */
    bool isEnabled() const noexcept                     { return enabled; }

    /** Enables/disables the reverb. */
    void setEnabled (bool newValue) noexcept            { enabled = newValue; }

    //==============================================================================
    /** Initialises the reverb. */
    void prepare (const juce::dsp::ProcessSpec& spec)
    {
        reverb.setSampleRate (spec.sampleRate);
        reverb.setLPF(spec);
    }

    /** Resets the reverb's internal state. */
    void reset() noexcept
    {
        reverb.reset();
    }
    
    void setCutoffFreq (float& cutoffFreqValue)
    {
        reverb.setLPFCutoffFreq(cutoffFreqValue);
    }

    //==============================================================================
    /** Applies the reverb to a mono or stereo buffer. */
    template <typename ProcessContext>
    void process (const ProcessContext& context) noexcept
    {
        const auto& inputBlock = context.getInputBlock();
        auto& outputBlock = context.getOutputBlock();
        const auto numInChannels = inputBlock.getNumChannels();
        const auto numOutChannels = outputBlock.getNumChannels();
        const auto numSamples = outputBlock.getNumSamples();

        jassert (inputBlock.getNumSamples() == numSamples);

        outputBlock.copyFrom (inputBlock);

        if (! enabled || context.isBypassed)
            return;

        if (numInChannels == 1 && numOutChannels == 1)
        {
            reverb.processMono (outputBlock.getChannelPointer (0), (int) numSamples);
        }
        else if (numInChannels == 2 && numOutChannels == 2)
        {
            reverb.processStereo (outputBlock.getChannelPointer (0),
                                  outputBlock.getChannelPointer (1),
                                  (int) numSamples);
        }
        else
        {
            jassertfalse;   // invalid channel configuration
        }
    }

private:
    //==============================================================================
    ReverbProcessorCustom reverb;
    bool enabled = true;
};
