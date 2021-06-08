/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class AlgoReverbAudioProcessorEditor  : public AudioProcessorEditor, public Slider::Listener
{
public:
    AlgoReverbAudioProcessorEditor (AlgoReverbAudioProcessor&);
    ~AlgoReverbAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    void sliderValueChanged(Slider* slider) override;
private:
    AlgoReverbAudioProcessor& processor;
    
    Slider reverbTimeSlider, modulationSlider, wetDrySlider;
    Slider predelaySlider, diffusionSlider, lowPassFilterSlider;
    Slider decaySlider, dampingSlider, bandwithSlider;
    
    Label reverbTimeLabel, modulationLabel, wetDryLabel;
    Label predelayLabel, diffusionLabel, lowPassFilterLabel;
    Label decayLabel, dampingLabel, bandwithLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AlgoReverbAudioProcessorEditor)
};
