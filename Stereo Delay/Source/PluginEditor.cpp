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
    
    delayKnob.addListener(this);
    delayKnob.setBounds(350, 90, 100, 80);
    delayKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delayKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    addAndMakeVisible(delayKnob);
    
    leftSelector.addListener(this);
    leftSelector.setBounds(35, 35, 75, 50);
    addAndMakeVisible(leftSelector);
}

StereoDelayAudioProcessorEditor::~StereoDelayAudioProcessorEditor()
{
}

//==============================================================================
void StereoDelayAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

 
    
    g.setColour (juce::Colours::darkgrey);
    g.fillRect(25, 25, 225, 300);
    
    g.setColour (juce::Colours::grey);
    g.fillRect(30, 30, 230, 305);
    
    g.setColour(juce::Colours::darkgrey);
    g.fillRect(550, 25, 225, 300);
    
    g.setColour (juce::Colours::grey);
    g.fillRect(540, 30, 230, 305);
    
    g.setColour (juce::Colours::darkgrey);
    g.setFont (20.0f);
    g.drawFittedText("Left Channel", 35, 35, 225, 300, juce::Justification::centredBottom, 1);
    
    g.setColour (juce::Colours::darkgrey);
    g.setFont (20.0f);
    g.drawFittedText("Right Channel", 550, 35, 225, 300, juce::Justification::centredBottom, 1);
    
    g.setColour (juce::Colours::ghostwhite);
    g.setFont (28.0f);
    g.drawFittedText ("Polyrhythmic Stereo Delay", getLocalBounds(), juce::Justification::centredTop, 1);
    
    g.setColour (juce::Colours::lightgrey);
    g.fillRoundedRectangle(300, 75, 200, 275, 10);
    
    
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
