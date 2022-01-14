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
    // Reverb Time Slider
    reverbTimeSlider = std::make_unique<Slider>();
    setSlider(reverbTimeSlider.get());
    timeAttach = std::make_unique<sliderAttachment>(processor.apvts, "TIME", *reverbTimeSlider);
    
    reverbTimeLabel = std::make_unique<Label>();
    reverbTimeLabel->attachToComponent(reverbTimeSlider.get(), false);
    setLabel(reverbTimeLabel.get(), "Time");

    // Modulation Slider
    modulationSlider = std::make_unique<Slider>();
    setSlider(modulationSlider.get());
    modAttach = std::make_unique<sliderAttachment>(processor.apvts, "MOD", *modulationSlider);

    modulationLabel = std::make_unique<Label>();
    modulationLabel->attachToComponent(modulationSlider.get(), false);
    setLabel(modulationLabel.get(), "Mod");
    
    // WetDry Slider
    wetDrySlider = std::make_unique<Slider>();
    setSlider(wetDrySlider.get());
    wetDryAttach = std::make_unique<sliderAttachment>(processor.apvts, "DRYWET", *wetDrySlider);

    wetDryLabel = std::make_unique<Label>();
    wetDryLabel->attachToComponent(wetDrySlider.get(), false);
    setLabel(wetDryLabel.get(), "Wet/Dry");

    // Predelay Slider
    predelaySlider = std::make_unique<Slider>();
    setSlider(predelaySlider.get());
    preDelayAttach = std::make_unique<sliderAttachment>(processor.apvts, "PREDELAY", *predelaySlider);

    predelayLabel = std::make_unique<Label>();
    predelayLabel->attachToComponent(predelaySlider.get(), false);
    setLabel(predelayLabel.get(), "PreDelay");
    
    // Diffusion Slider
    diffusionSlider = std::make_unique<Slider>();
    setSlider(diffusionSlider.get());
    diffusionAttach = std::make_unique<sliderAttachment>(processor.apvts, "DIFFUSION", *diffusionSlider);
    
    diffusionLabel = std::make_unique<Label>();
    diffusionLabel->attachToComponent(diffusionSlider.get(), false);
    setLabel(diffusionLabel.get(), "Diffusion");
    
    // LowPass Filter Slider
    lowPassFilterSlider = std::make_unique<Slider>();
    setSlider(lowPassFilterSlider.get());
    lpfAttach = std::make_unique<sliderAttachment>(processor.apvts, "LPF", *lowPassFilterSlider);
    
    lowPassFilterLabel = std::make_unique<Label>();
    lowPassFilterLabel->attachToComponent(lowPassFilterSlider.get(), false);
    setLabel(lowPassFilterLabel.get(), "LowPass");

    // Decay Slider
    decaySlider = std::make_unique<Slider>();
    setSlider(decaySlider.get());
    decayAttach = std::make_unique<sliderAttachment>(processor.apvts, "DECAY", *decaySlider);

    decayLabel = std::make_unique<Label>();
    decayLabel->attachToComponent(decaySlider.get(), false);
    setLabel(decayLabel.get(), "Decay");

    // Damping Slider
    dampingSlider = std::make_unique<Slider>();
    setSlider(dampingSlider.get());
    dampingAttach = std::make_unique<sliderAttachment>(processor.apvts, "DAMPING", *dampingSlider);
    
    dampingLabel = std::make_unique<Label>();
    dampingLabel->attachToComponent(dampingSlider.get(), false);
    setLabel(dampingLabel.get(), "Damping");
    
    // Bandwith Slider
    bandwidthSlider = std::make_unique<Slider>();
    setSlider(bandwidthSlider.get());
    bandwidthAttach = std::make_unique<sliderAttachment>(processor.apvts, "BANDWIDTH", *bandwidthSlider);
    
    bandwithLabel = std::make_unique<Label>();
    bandwithLabel->attachToComponent(bandwidthSlider.get(), false);
    setLabel(bandwithLabel.get(), "Bandwidth");

    setSize (500, 400);
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
    reverbTimeSlider->setBounds(50, 30, 100, 100);
    
    modulationSlider->setBounds(150, 30, 100, 100);
    
    wetDrySlider->setBounds(250, 30, 100, 100);
    
    predelaySlider->setBounds(50, 175, 100, 100);

    diffusionSlider->setBounds(150, 175, 100, 100);

    lowPassFilterSlider->setBounds(250, 175, 100, 100);

    decaySlider->setBounds(400, 30, 100, 100);

    dampingSlider->setBounds(400, 160, 100, 100);

    bandwidthSlider->setBounds(400, 290, 100, 100);
}

void AlgoReverbAudioProcessorEditor::setSlider(Slider* slider)
{
    slider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    slider->setTextBoxStyle(Slider::TextBoxBelow, false, 50, 30);
    addAndMakeVisible(slider);
}

void AlgoReverbAudioProcessorEditor::setLabel(Label* label, String labelText)
{
    label->setText(labelText, dontSendNotification);
    label->setJustificationType(Justification::centred);
    addAndMakeVisible(label);
}
