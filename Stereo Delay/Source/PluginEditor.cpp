/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "JuceHeader.h"

//==============================================================================
StereoDelayAudioProcessorEditor::StereoDelayAudioProcessorEditor (StereoDelayAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 350);
}

StereoDelayAudioProcessorEditor::~StereoDelayAudioProcessorEditor()
{
}

//==============================================================================
void StereoDelayAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::ghostwhite);
    g.setFont (28.0f);
    g.drawFittedText ("Polyrhythmic Stereo Delay", getLocalBounds(), juce::Justification::centredBottom, 1);
    
    g.setColour (juce::Colours::darkgrey);
    g.drawRect(25, 25, 225, 300);
    
    g.setColour(juce::Colours::darkgrey);
    g.drawRect(550, 25, 225, 300);
}

void StereoDelayAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void StereoDelayAudioProcessorEditor::comboBoxChanged(juce::ComboBox * comboBox)
{
    // Implement functionality later
}

void StereoDelayAudioProcessorEditor::buttonClicked(juce::Button * button)
{
    // Implement functionality later
}

void StereoDelayAudioProcessorEditor::sliderValueChanged(juce::Slider * slider)
{
    // Implement functionality later
}
