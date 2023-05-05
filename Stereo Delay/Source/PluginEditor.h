/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class StereoDelayAudioProcessorEditor  : public juce::AudioProcessorEditor//,
                                            //public juce::ComboBox::Listener,
                                            //public juce::Button::Listener,
                                            //public juce::Slider::Listener
                                            
{
public:
    StereoDelayAudioProcessorEditor (StereoDelayAudioProcessor&);
    ~StereoDelayAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    


private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    StereoDelayAudioProcessor& audioProcessor;
    
    juce::ComboBox leftSelector;
    juce::ComboBox rightSelector;
    juce::Slider delayKnob;
    
    juce::LookAndFeel_V2 lookAndFeel2;
    juce::LookAndFeel_V4 otherLookAndFeel;
    juce::Slider gainKnobL;
    juce::Slider gainKnobR;
    juce::Slider feedbackL;
    juce::Slider feedbackR;
    juce::Slider valueL;
    juce::Slider valueR;
    
    juce::Label delayLabel;
    juce::Label leftLevel;
    juce::Label rightLevel;
    juce::Label feedbackLabelLeft;
    juce::Label feedbackLabelRight;
    juce::Label title;
    juce::Label leftChannel;
    juce::Label rightChannel;
    juce::Label customLeft;
    juce::Label customRight;
    juce::Label presetLeft;
    juce::Label presetRight;
public:
    
    std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>> sliderAttachment;
    std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment>> boxAttachment;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StereoDelayAudioProcessorEditor)
};


