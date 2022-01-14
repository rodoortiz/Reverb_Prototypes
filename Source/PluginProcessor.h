/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "FractionalDelay.hpp"
#include "FDN.h"
#include "APF.h"
#include "Schroeder.h"
#include "PlateReverb.h"
#include "ReverbCustom.h"

//==============================================================================
/**
*/
class AlgoReverbAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    AlgoReverbAudioProcessor();
    ~AlgoReverbAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //AudioProcessorValueTreeState
    AudioProcessorValueTreeState apvts;
    static AudioProcessorValueTreeState::ParameterLayout parameterLayout();
    
private:
//    FractionalDelay predelay;
////    FDN fdn;
////    APF apf1{240.f, 0.8321f}, apf2{82.f, 0.964f};
//    Schroeder schroeder;
//
//    float Fs;
    
    //PLATE REVERB
    PlateReverb plateReverb;
    APF apf;
    
    //JUCE REVERB
    dsp::Reverb reverbJuce;
    dsp::Reverb::Parameters reverbJuceParameters;
    
    //JUCE REVERB CUSTOM
    ReverbCustom reverbJuceCustom;
    ReverbCustom::Parameters reverbJuceCustomParameters;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AlgoReverbAudioProcessor)
};
