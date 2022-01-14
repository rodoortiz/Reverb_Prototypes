/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AlgoReverbAudioProcessor::AlgoReverbAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "Parameters", parameterLayout())
#endif
{
}

AlgoReverbAudioProcessor::~AlgoReverbAudioProcessor()
{
}

AudioProcessorValueTreeState::ParameterLayout AlgoReverbAudioProcessor::parameterLayout()
{
    AudioProcessorValueTreeState::ParameterLayout params;
    
    // TIME
    params.add(std::make_unique<juce::AudioParameterFloat>("TIME",
                                                           "Time",
                                                           NormalisableRange<float>(0.4f, 0.7f, 0.01f, 1.0f),
                                                           0.5f));
    
    // MODULATION
    params.add(std::make_unique<juce::AudioParameterFloat>("MOD",
                                                           "Modulation",
                                                           NormalisableRange<float>(1.0f, 10.0f, 0.01f, 1.0f),
                                                           1.0f));
    
    // DRYWET
    params.add(std::make_unique<juce::AudioParameterFloat>("DRYWET",
                                                           "Dry/Wet",
                                                           NormalisableRange<float>(0.0f, 1.0f, 0.01f, 1.0f),
                                                           0.5f));

    // PREDELAY
    params.add(std::make_unique<juce::AudioParameterFloat>("PREDELAY",
                                                           "PreDelay",
                                                           NormalisableRange<float>(0.0f, 200.0f, 0.1f, 1.0f),
                                                           0.0f));
    
    // DIFUSSION
    params.add(std::make_unique<juce::AudioParameterFloat>("DIFFUSION",
                                                           "Diffusion",
                                                           NormalisableRange<float>(0.2f, 0.8f, 0.01f, 1.0f),
                                                           0.5f));
    
    // LPF
    params.add(std::make_unique<juce::AudioParameterFloat>("LPF",
                                                           "Lpf",
                                                           NormalisableRange<float>(500.0f, 20000.0f, 1.0f, 1.0f),
                                                           10000.0f));
    
    // DECAY
    params.add(std::make_unique<juce::AudioParameterFloat>("DECAY",
                                                           "Decay",
                                                           NormalisableRange<float>(0.0f, 0.99f, 0.01f, 1.0f),
                                                           0.5f));
    
    // DAMPING
    params.add(std::make_unique<juce::AudioParameterFloat>("DAMPING",
                                                           "Damping",
                                                           NormalisableRange<float>(0.0f, 0.99f, 0.01f, 1.0f),
                                                           0.5f));
    
    // BANDWIDTH
    params.add(std::make_unique<juce::AudioParameterFloat>("BANDWIDTH",
                                                           "Bandwidth",
                                                           NormalisableRange<float>(0.0f, 0.99f, 0.01f, 1.0f),
                                                           0.5f));

    return params;
}

//==============================================================================
const String AlgoReverbAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AlgoReverbAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AlgoReverbAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AlgoReverbAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double AlgoReverbAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AlgoReverbAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AlgoReverbAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AlgoReverbAudioProcessor::setCurrentProgram (int index)
{
}

const String AlgoReverbAudioProcessor::getProgramName (int index)
{
    return {};
}

void AlgoReverbAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void AlgoReverbAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    
//    predelay.setFs(sampleRate);
//    predelay.setDelaySamples(0.0f);
////    fdn.setFs(sampleRate);
////    apf1.setFs(sampleRate);
////    apf2.setFs(sampleRate);
//    schroeder.setFs(sampleRate);
//    Fs = sampleRate;
    
    //PLATE REVERB
    plateReverb.prepareJuceDspModules(spec);
    plateReverb.prepareDelayValues(sampleRate);
    plateReverb.preparePlateReverb(sampleRate);
    
    //JUCE REVERB
    reverbJuce.prepare(spec);
    reverbJuceParameters.roomSize = 0.7f;
    
    if (sampleRate == 96000)
    {
        reverbJuceParameters.damping = 0.727;
    }
    
    //JUCE REVERB CUSTOM
    reverbJuceCustom.prepare(spec);
    
}

void AlgoReverbAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AlgoReverbAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void AlgoReverbAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
//    predelay.setDepth(0.0f);
//    predelay.setSpeed(0.0f);
//
//    float predelayInSec =  predelayMS * 0.001;
//    float predelayInSamples = predelayInSec * Fs;
//    predelay.setDelaySamples(predelayInSamples);
    
//    fdn.setTime(timeValue);
//    fdn.setDepth(modValue);
//    apf1.setDepth(modValue);
//    apf2.setDepth(modValue);
//    apf1.setFeedbackGain(diffusionValue);
//    apf2.setFeedbackGain(diffusionValue);
//    schroeder.setFeedbackGain(timeValue);
//    schroeder.setDiffusionGain(diffusionValue);
//    schroeder.setDepth(modValue);

//    for (int channel = 0; channel < totalNumInputChannels; ++channel)
//    {
//        for (int n = 0; n < buffer.getNumSamples(); ++n) {
//            float x = buffer.getWritePointer(channel)[n];
//
//            float verb = predelay.processSample(x, channel); //Pre Delay
////            verb = fdn.processSample(verb, channel); //Reverb block
////            verb = apf1.processSample(verb, channel);
////            verb = apf2.processSample(verb, channel);
//
//            verb = schroeder.processSample(verb, channel);
//
//            float y = ((1.f - wet) * x) + (wet * verb);
//
//            buffer.getWritePointer(channel)[n] = y;
//        }
//    } 
    
    // PLATE REVERB
    auto lowpassValue = apvts.getRawParameterValue("LPF")->load();
    plateReverb.setFiltersCutoffFreq(lowpassValue);
    
    auto wet  = apvts.getRawParameterValue("DRYWET")->load();
    auto bandwidthValue = apvts.getRawParameterValue("BANDWIDTH")->load();
    auto dampingValue = apvts.getRawParameterValue("DAMPING")->load();
    auto decayValue = apvts.getRawParameterValue("DECAY")->load();
    plateReverb.processPlateReverb(buffer, wet, bandwidthValue, dampingValue, decayValue);
    
    //JUCE REVERB
//    reverbJuceParameters.dryLevel = 1 - wet;
//    reverbJuceParameters.wetLevel = wet;
//    reverbJuce.setParameters(reverbJuceParameters);
//
//    auto audioBlock = juce::dsp::AudioBlock<float> (buffer);
//    auto context = juce::dsp::ProcessContextReplacing<float> (audioBlock);
//    reverbJuce.process(context);
    
    //JUCE REVERB CUSTOM
//    reverbJuceCustomParameters.dryLevel = 1 - wet;
//    reverbJuceCustomParameters.wetLevel = wet;
//    reverbJuceCustom.setParameters(reverbJuceCustomParameters);
//    reverbJuceCustom.setCutoffFreq(lowpassValue);
//
//    auto audioBlock = juce::dsp::AudioBlock<float> (buffer);
//    auto context = juce::dsp::ProcessContextReplacing<float> (audioBlock);
//    reverbJuceCustom.process(context);
}

//==============================================================================
bool AlgoReverbAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* AlgoReverbAudioProcessor::createEditor()
{
    return new AlgoReverbAudioProcessorEditor (*this);
}

//==============================================================================
void AlgoReverbAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void AlgoReverbAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AlgoReverbAudioProcessor();
}
