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
class AlgoReverbAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    AlgoReverbAudioProcessorEditor (AlgoReverbAudioProcessor&);
    ~AlgoReverbAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    void setSlider(Slider* slider);
    void setLabel(Label* label, String labelText);
    
private:
    AlgoReverbAudioProcessor& processor;
    
    std::unique_ptr<Slider> reverbTimeSlider;
    std::unique_ptr<Slider> modulationSlider;
    std::unique_ptr<Slider> wetDrySlider;
    
    std::unique_ptr<Slider> predelaySlider;
    std::unique_ptr<Slider> diffusionSlider;
    std::unique_ptr<Slider> lowPassFilterSlider;
    
    std::unique_ptr<Slider> decaySlider;
    std::unique_ptr<Slider> dampingSlider;
    std::unique_ptr<Slider> bandwidthSlider;
    
    std::unique_ptr<Label> reverbTimeLabel;
    std::unique_ptr<Label> modulationLabel;
    std::unique_ptr<Label> wetDryLabel;

    std::unique_ptr<Label> predelayLabel;
    std::unique_ptr<Label> diffusionLabel;
    std::unique_ptr<Label> lowPassFilterLabel;
    
    std::unique_ptr<Label> decayLabel;
    std::unique_ptr<Label> dampingLabel;
    std::unique_ptr<Label> bandwithLabel;
    
    using sliderAttachment = AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<sliderAttachment> timeAttach;
    std::unique_ptr<sliderAttachment> modAttach;
    std::unique_ptr<sliderAttachment> wetDryAttach;

    std::unique_ptr<sliderAttachment> preDelayAttach;
    std::unique_ptr<sliderAttachment> diffusionAttach;
    std::unique_ptr<sliderAttachment> lpfAttach;

    std::unique_ptr<sliderAttachment> decayAttach;
    std::unique_ptr<sliderAttachment> dampingAttach;
    std::unique_ptr<sliderAttachment> bandwidthAttach;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AlgoReverbAudioProcessorEditor)
};
