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
class StereoDelayAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                            public juce::ComboBox::Listener,
                                            public juce::Button::Listener,
                                            public juce::Slider::Listener
                                            
{
public:
    StereoDelayAudioProcessorEditor (StereoDelayAudioProcessor&);
    ~StereoDelayAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void comboBoxChanged(juce::ComboBox * comboBox) override;
    void buttonClicked(juce::Button * button) override;
    void sliderValueChanged(juce::Slider * slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    StereoDelayAudioProcessor& audioProcessor;
    
    juce::ComboBox leftSelector;
    juce::ComboBox rightSelector;
    juce::ToggleButton bypass;
    juce::Slider delayKnob;
    
    juce::LookAndFeel_V2 lookAndFeel2;
    juce::LookAndFeel_V4 otherLookAndFeel;
    juce::Slider gainKnobL;
    juce::Slider gainKnobR;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StereoDelayAudioProcessorEditor)
};
