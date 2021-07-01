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
    setSize (500, 300);
    
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
    lowPassFilterSlider.setRange(500.0f, 20000.0f, 1.0f);
    lowPassFilterSlider.setValue(10000.0f);
    addAndMakeVisible(lowPassFilterSlider);
    
    lowPassFilterLabel.setText("LowPass", dontSendNotification);
    lowPassFilterLabel.attachToComponent(&lowPassFilterSlider, false);
    lowPassFilterLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(lowPassFilterLabel);
    
    //Decay Slider
    decaySlider.addListener(this);
    decaySlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    decaySlider.setBounds(400, 0, 100, 100);
    decaySlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 30);
    decaySlider.setRange(0.0f, 0.99f, 0.01f);
    decaySlider.setValue(0.5f);
    addAndMakeVisible(decaySlider);
    
    decayLabel.setText("Decay", dontSendNotification);
    decayLabel.attachToComponent(&decaySlider, false);
    decayLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(decayLabel);
    
    //Damping Slider
    dampingSlider.addListener(this);
    dampingSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    dampingSlider.setBounds(400, 100, 100, 100);
    dampingSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 30);
    dampingSlider.setRange(0.0f, 0.99f, 0.01f);
    dampingSlider.setValue(0.5f);
    addAndMakeVisible(dampingSlider);
    
    dampingLabel.setText("Damping", dontSendNotification);
    dampingLabel.attachToComponent(&dampingSlider, false);
    dampingLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(dampingLabel);
    
    //Bandwith Slider
    bandwithSlider.addListener(this);
    bandwithSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    bandwithSlider.setBounds(400, 200, 100, 100);
    bandwithSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 30);
    bandwithSlider.setRange(0.0f, 0.99f, 0.01f);
    bandwithSlider.setValue(0.5f);
    addAndMakeVisible(bandwithSlider);
    
    bandwithLabel.setText("Bandwith", dontSendNotification);
    bandwithLabel.attachToComponent(&bandwithSlider, false);
    bandwithLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(bandwithLabel);
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
    if (slider == &predelaySlider)
        processor.predelayMS = predelaySlider.getValue();
    
    if (slider == &wetDrySlider)
        processor.wet = wetDrySlider.getValue();

    if (slider == &reverbTimeSlider)
        processor.timeValue = reverbTimeSlider.getValue();
    
    if (slider == &modulationSlider)
        processor.modValue = modulationSlider.getValue();
    
    if (slider == &diffusionSlider)
        processor.diffusionValue = diffusionSlider.getValue();
    
    if (slider == &lowPassFilterSlider)
        processor.lowpassValue = lowPassFilterSlider.getValue();
    
    if (slider == &decaySlider)
        processor.decayValue = decaySlider.getValue();
    
    if (slider == &dampingSlider)
        processor.dampingValue = dampingSlider.getValue();
    
    if (slider == &bandwithSlider)
        processor.bandwithValue = bandwithSlider.getValue();
}
