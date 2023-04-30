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
    
    otherLookAndFeel.setColour(juce::Slider::thumbColourId, juce::Colours::darkred);
    juce::LookAndFeel::setDefaultLookAndFeel(&otherLookAndFeel);
    
    delayKnob.setBounds(350, 90, 100, 80);
    delayKnob.setRange(50.0, 300, 1.0);
    delayKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delayKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    addAndMakeVisible(delayKnob);
    
    leftSelector.setBounds(35, 35, 75, 50);
    leftSelector.addItem("Sixteenth",1);
    leftSelector.addItem("Eighth",2);
    leftSelector.addItem("Dotted Eighth",3);
    leftSelector.addItem("Quater",4);
    leftSelector.addItem("Dotted Quarter",6);
    leftSelector.addItem("Fifth",5);
    leftSelector.addItem("Seventh",7);
    leftSelector.addItem("Ninth",9);
    leftSelector.setText("Select Subdivision...");
    addAndMakeVisible(leftSelector);
    
    rightSelector.setBounds(690, 35, 75, 50);
    rightSelector.addItem("Sixteenth",1);
    rightSelector.addItem("Eighth",2);
    rightSelector.addItem("Dotted Eighth",3);
    rightSelector.addItem("Quater",4);
    rightSelector.addItem("Dotted Quarter",6);
    rightSelector.addItem("Fifth",5);
    rightSelector.addItem("Seventh",7);
    rightSelector.addItem("Ninth",9);
    rightSelector.setText("Select Subdivision...");
    addAndMakeVisible(rightSelector);
    
    gainKnobL.setBounds(105, 150, 75, 75);
    gainKnobL.setRange(0.0f, 1.0, 0.1f);
    gainKnobL.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainKnobL.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    gainKnobL.setLookAndFeel(&otherLookAndFeel);
    addAndMakeVisible(gainKnobL);
    
    gainKnobR.setBounds(615, 150, 75, 75);
    gainKnobR.setRange(0.0f, 1.0, 0.1f);
    gainKnobR.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainKnobR.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    gainKnobR.setLookAndFeel(&otherLookAndFeel);
    addAndMakeVisible(gainKnobR);
    
    sliderAttachment.emplace_back(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state,"delayValue",delayKnob));
    sliderAttachment.emplace_back(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state,"gainValueL",gainKnobL));
    sliderAttachment.emplace_back(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state,"gainValueR",gainKnobR));
    boxAttachment.emplace_back(new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.state,"delayLeft",leftSelector));
    boxAttachment.emplace_back(new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.state,"delayRight",rightSelector));
    
}

StereoDelayAudioProcessorEditor::~StereoDelayAudioProcessorEditor()
{
}

//==============================================================================
void StereoDelayAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

 
    g.setColour(juce::Colours::steelblue);
    g.drawRect(0, 0, 800, 350);
    
    g.setColour (juce::Colours::darkgrey);
    g.fillRect(25, 25, 225, 300);
    
    g.setColour (juce::Colours::floralwhite);
    g.fillRect(30, 30, 230, 305);
    
    g.setColour(juce::Colours::darkgrey);
    g.fillRect(550, 25, 225, 300);
    
    g.setColour (juce::Colours::floralwhite);
    g.fillRect(540, 30, 230, 305);
    
    g.setColour (juce::Colours::darkgrey);
    g.setFont (20.0f);
    g.drawFittedText("Left Channel", 35, 35, 225, 300, juce::Justification::centredBottom, 1);
    
    g.setColour (juce::Colours::black);
    g.setFont (20.0f);
    g.drawFittedText("Wet", 105, 175, 75, 75, juce::Justification::centredBottom, 1);
    
    g.setColour (juce::Colours::darkgrey);
    g.setFont (20.0f);
    g.drawFittedText("Right Channel", 550, 35, 225, 300, juce::Justification::centredBottom, 1);
    
    g.setColour (juce::Colours::black);
    g.setFont (20.0f);
    g.drawFittedText("Wet", 615, 175, 75, 75, juce::Justification::centredBottom, 1);
    
    g.setColour (juce::Colours::ghostwhite);
    g.setFont (28.f);
    g.drawFittedText ("My Little Poly Stereo Delay", getLocalBounds(), juce::Justification::centredTop, 1);
    
    g.setColour (juce::Colours::lightgrey);
    g.fillRoundedRectangle(300, 75, 200, 275, 10);
    
    g.setColour (juce::Colours::grey);
    g.fillRoundedRectangle(350, 85, 100, 100, 10);
    
    g.setColour (juce::Colours::darkgrey);
    g.setFont (20.0f);
    g.drawFittedText("Tempo", 350, 125, 100, 80, juce::Justification::centredBottom, 1);
    
    g.setColour (juce::Colours::darkgrey);
    g.fillRoundedRectangle(105, 150, 75, 75, 5);

    g.setColour (juce::Colours::darkgrey);
    g.fillRoundedRectangle(615, 150, 75, 75, 5);
    
    
}

void StereoDelayAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}



