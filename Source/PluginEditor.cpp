/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AlgoReverbAudioProcessorEditor::AlgoReverbAudioProcessorEditor (AlgoReverbAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    setSize (400, 300);
    
    //Reverb Time Slider
    reverbTimeSlider.addListener(this);
    reverbTimeSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    reverbTimeSlider.setBounds(50, 30, 100, 100);
    reverbTimeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 30);
    reverbTimeSlider.setRange(0.4f, 0.7f, 0.01f);
    reverbTimeSlider.setValue(0.5f);
    addAndMakeVisible(reverbTimeSlider);
    
    reverbTimeLabel.setText("Time", dontSendNotification);
    reverbTimeLabel.attachToComponent(&reverbTimeSlider, false);
    reverbTimeLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(reverbTimeLabel);
    
    //Modulation Slider
    modulationSlider.addListener(this);
    modulationSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    modulationSlider.setBounds(150, 30, 100, 100);
    modulationSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 30);
    modulationSlider.setRange(1.0f, 10.0f, 0.01f);
    modulationSlider.setValue(1.0f);
    addAndMakeVisible(modulationSlider);
    
    modulationLabel.setText("Mod", dontSendNotification);
    modulationLabel.attachToComponent(&modulationSlider, false);
    modulationLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(modulationLabel);
    
    //WetDry Slider
    wetDrySlider.addListener(this);
    wetDrySlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    wetDrySlider.setBounds(250, 30, 100, 100);
    wetDrySlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 30);
    wetDrySlider.setRange(0.0f, 1.0f, 0.01f);
    wetDrySlider.setValue(0.5f);
    addAndMakeVisible(wetDrySlider);
    
    wetDryLabel.setText("Wet/Dry", dontSendNotification);
    wetDryLabel.attachToComponent(&wetDrySlider, false);
    wetDryLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(wetDryLabel);
    
    //Predelay Slider
    predelaySlider.addListener(this);
    predelaySlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    predelaySlider.setBounds(50, 175, 100, 100);
    predelaySlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 30);
    predelaySlider.setRange(0.0f, 200.0f, 0.1f);
    predelaySlider.setValue(0.0f);
    addAndMakeVisible(predelaySlider);
    
    predelayLabel.setText("PreDelay", dontSendNotification);
    predelayLabel.attachToComponent(&predelaySlider, false);
    predelayLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(predelayLabel);
    
    //Diffusion Slider
    diffusionSlider.addListener(this);
    diffusionSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    diffusionSlider.setBounds(150, 175, 100, 100);
    diffusionSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 30);
    diffusionSlider.setRange(0.2f, 0.8f, 0.01f);
    diffusionSlider.setValue(0.5f);
    addAndMakeVisible(diffusionSlider);
    
    diffusionLabel.setText("Diffusion", dontSendNotification);
    diffusionLabel.attachToComponent(&diffusionSlider, false);
    diffusionLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(diffusionLabel);
    
    //LowPass Filter Slider
    lowPassFilterSlider.addListener(this);
    lowPassFilterSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    lowPassFilterSlider.setBounds(250, 175, 100, 100);
    lowPassFilterSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 30);
    lowPassFilterSlider.setRange(1000.0f, 20000.0f, 1.0f);
    lowPassFilterSlider.setValue(10000.0f);
    addAndMakeVisible(lowPassFilterSlider);
    
    lowPassFilterLabel.setText("LowPass", dontSendNotification);
    lowPassFilterLabel.attachToComponent(&lowPassFilterSlider, false);
    lowPassFilterLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(lowPassFilterLabel);
}

AlgoReverbAudioProcessorEditor::~AlgoReverbAudioProcessorEditor()
{
}

//==============================================================================
void AlgoReverbAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::black);

    g.setColour (Colours::white);
    g.setFont (15.0f);
}

void AlgoReverbAudioProcessorEditor::resized()
{
    
}

void AlgoReverbAudioProcessorEditor::sliderValueChanged(Slider* slider) {
    if (slider == &predelaySlider) {
        processor.predelayMS = predelaySlider.getValue();
    }
    
    if (slider == &wetDrySlider) {
        processor.wet = wetDrySlider.getValue();
    }
    
    if (slider == &reverbTimeSlider) {
        processor.timeValue = reverbTimeSlider.getValue();
    }
    
    if (slider == &modulationSlider) {
        processor.timeValue = modulationSlider.getValue();
    }
    
    if (slider == &diffusionSlider) {
        processor.diffusionValue = diffusionSlider.getValue();
    }
}
