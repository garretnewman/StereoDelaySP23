/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include"JuceHeader.h"



//==============================================================================
StereoDelayAudioProcessor::StereoDelayAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), state(*this, nullptr,"DelayParams",createParameterLayout())
#endif
{
}

StereoDelayAudioProcessor::~StereoDelayAudioProcessor()
{
}

juce::AudioProcessorValueTreeState::ParameterLayout StereoDelayAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterFloat>  (juce::ParameterID("delayValue", 1),
                                                                  "Tempo",
                                                                  juce::NormalisableRange<float> (50.f, 300.f),
                                                                  50.f
                                                                  )  );
    
    params.push_back(std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("gainValueL", 2),
                                                                  "Wet Left",
                                                                  juce::NormalisableRange<float> (0.0f, 1.0),
                                                                  0.0f
                                                                  )  );
    
    params.push_back(std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("gainValueR", 3),
                                                                  "Wet Right",
                                                                  juce::NormalisableRange<float> (0.0f, 1.0),
                                                                  0.0f
                                                                  )  );
    
    params.push_back(std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("delayLeft", 4),
                                                                  "Left Subdivision",
                                                                  juce::NormalisableRange<float> (1.f, 9.f),
                                                                  1.f
                                                                  )  );
    
    params.push_back(std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("delayRight", 5),
                                                                  "Right Subdivision",
                                                                  juce::NormalisableRange<float> (1.f, 9.f),
                                                                  1.f
                                                                  )  );
    

    return {params.begin() , params.end()};
    
}

//==============================================================================
const juce::String StereoDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool StereoDelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool StereoDelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool StereoDelayAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double StereoDelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int StereoDelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int StereoDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void StereoDelayAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String StereoDelayAudioProcessor::getProgramName (int index)
{
    return {};
}

void StereoDelayAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void StereoDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    delayL.prepareToPlay(sampleRate, samplesPerBlock);
    //delayR.prepareToPlay(sampleRate, samplesPerBlock);
}

void StereoDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool StereoDelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void StereoDelayAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    
    //float wet = 0.6f;
//    delayL.setWet (gainValueL);
//    gain.setGain(gainValueL);
//    delayR.setWet(gainValueR);
//    delayL.setDelayMS(delayValue);
//    delayR.setDelayMS(delayValue);
    
    float delayValue = *state.getRawParameterValue("delayValue");
    int delayRight = *state.getRawParameterValue("delayRight");
    int delayLeft = *state.getRawParameterValue("delayLeft");
    float gainValueL = *state.getRawParameterValue("gainValueL");
    float gainValueR = *state.getRawParameterValue("gainValueR");
    
    delayL.setWet(gainValueL);
    delayR.setWet(gainValueR);
    
    if(delayLeft == 1)
    {
        delayL.setDelayMS(delayValue);
    }
    else if (delayLeft == 2)
    {
        delayL.setDelayMS(delayValue * 2);
    }
    else if(delayLeft == 3)
    {
        delayL.setDelayMS(delayValue * 3);
    }
    else if(delayLeft == 4)
    {
        delayL.setDelayMS(delayValue * 4);
    }
    else if(delayLeft ==5)
    {
        delayL.setDelayMS(delayValue * 5);
    }
    else if(delayLeft == 6)
    {
        delayL.setDelayMS(delayValue * 6);
    }
    else if(delayLeft == 7)
    {
        delayL.setDelayMS(delayValue * 7);
    }
    else if(delayLeft == 9)
    {
        delayL.setDelayMS(delayValue * 9);
    }
  
    
    if(delayRight == 1)
    {
        delayR.setDelayMS(delayValue);
    }
    else if (delayRight == 2)
    {
        delayR.setDelayMS(delayValue * 2);
    }
    else if(delayRight == 3)
    {
        delayR.setDelayMS(delayValue * 3);
    }
    else if(delayRight == 4)
    {
        delayR.setDelayMS(delayValue * 4);
    }
    else if(delayRight ==5)
    {
        delayR.setDelayMS(delayValue * 5);
    }
    else if(delayRight == 6)
    {
        delayR.setDelayMS(delayValue * 6);
    }
    else if(delayRight == 7)
    {
        delayR.setDelayMS(delayValue * 7);
    }
    else if(delayRight == 9)
    {
        delayR.setDelayMS(delayValue * 9);
    }
    int numSamples = buffer.getNumSamples();
    
    
    
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        if(channel == 0)
        {
            delayL.processInPlace(channelData, numSamples, channel);
        }
        
        if(channel == 1)
        {
            delayR.processInPlace(channelData, numSamples, channel);
        }
      

    }
}

//==============================================================================
bool StereoDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* StereoDelayAudioProcessor::createEditor()
{
    return new StereoDelayAudioProcessorEditor (*this);
}

//==============================================================================
void StereoDelayAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void StereoDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new StereoDelayAudioProcessor();
}

