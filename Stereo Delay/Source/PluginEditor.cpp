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
    
    delayKnob.setBounds(325, 110, 150, 150);
    delayKnob.setRange(50.0, 300, 1.0);
    delayKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delayKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    delayKnob.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::floralwhite);
    delayKnob.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::darkgreen.brighter(.85));
    delayKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::black);
    delayKnob.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::floralwhite);
    addAndMakeVisible(delayKnob);
    
    delayLabel.attachToComponent(&delayKnob, false);
    delayLabel.setText("Tempo", juce::dontSendNotification);
    delayLabel.setJustificationType(juce::Justification::centredTop);
    delayLabel.setFont(juce::Font("Arial Black", 25.0, juce::Font::bold));
    addAndMakeVisible(delayLabel);
    
    
    //==============================================================================
    // Left Channel
    
    gainKnobL.setBounds(30, 60, 95, 95);
    gainKnobL.setRange(0.0f, 1.0, 0.01f);
    gainKnobL.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainKnobL.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    gainKnobL.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::floralwhite);
    gainKnobL.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::red.brighter(.85));
    gainKnobL.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::black);
    gainKnobL.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::floralwhite);
    addAndMakeVisible(gainKnobL);
    
    feedbackKnobL.setBounds(160, 110, 95, 95);
    feedbackKnobL.setRange(0.0f, 1.0f, 0.1f);
    feedbackKnobL.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    feedbackKnobL.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    feedbackKnobL.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::floralwhite);
    feedbackKnobL.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::red.brighter(.85));
    feedbackKnobL.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::black);
    feedbackKnobL.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::floralwhite);
    addAndMakeVisible(feedbackKnobL);
    
    leftSelector.setBounds(40, 200, 110, 25); // pos x, pos y, width, height
    leftSelector.addItem("Sixteenth",1);
    leftSelector.addItem("Eighth",2);
    leftSelector.addItem("Dotted Eighth",3);
    leftSelector.addItem("Quarter",4);
    leftSelector.addItem("Fifth",6);
    leftSelector.addItem("Dotted Quarter",5);
    leftSelector.addItem("Seventh",7);
    leftSelector.addItem("Ninth",9);
    leftSelector.setText("Select Subdivision...");
    addAndMakeVisible(leftSelector);
    
    valueL.setBounds(40, 275, 210, 50);
    valueL.setRange(0.0f, 15.0f, 0.01f);
    valueL.setSliderStyle(juce::Slider::LinearHorizontal);
    valueL.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    valueL.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::floralwhite);
    valueL.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::red.brighter(.85));
    valueL.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::black);
    valueL.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::floralwhite);
    addAndMakeVisible(valueL);
    
    leftLevel.attachToComponent(&gainKnobL, false);
    leftLevel.setText("Level",juce::dontSendNotification);
    leftLevel.setJustificationType(juce::Justification::centredTop);
    leftLevel.setFont(juce::Font("Arial Black", 20.0, juce::Font::bold));
    addAndMakeVisible(leftLevel);
    
    feedbackLabelLeft.attachToComponent(&feedbackKnobL, false);
    feedbackLabelLeft.setText("Feedback",juce::dontSendNotification);
    feedbackLabelLeft.setJustificationType(juce::Justification::centredTop);
    feedbackLabelLeft.setFont(juce::Font("Arial Black", 20.0, juce::Font::bold));
    addAndMakeVisible(feedbackLabelLeft);
    
    customLeft.attachToComponent(&valueL, false);
    customLeft.setText("Custom...", juce::dontSendNotification);
    customLeft.setJustificationType(juce::Justification::topLeft);
    customLeft.setFont(juce::Font("Arial Black", 20.0,juce::Font::bold));
    addAndMakeVisible(customLeft);
    
    presetLeft.attachToComponent(&leftSelector, false);
    presetLeft.setText("Presets...", juce::dontSendNotification);
    presetLeft.setJustificationType(juce::Justification::topLeft);
    presetLeft.setFont(juce::Font("Arial Black", 20.0,juce::Font::bold));
    addAndMakeVisible(presetLeft);
    
    leftChannel.setText("Left Channel", juce::dontSendNotification);
    leftChannel.setJustificationType(juce::Justification::left);
    leftChannel.setBounds(130, 40, 250, 20);
    leftChannel.setFont(juce::Font("Arial Black", 23.0, juce::Font::bold));
    addAndMakeVisible(leftChannel);
    
    //==============================================================================
    // Right Channel
    
    gainKnobR.setBounds(540, 60, 95, 95);
    gainKnobR.setRange(0.0f, 1.0, 0.1f);
    gainKnobR.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainKnobR.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);;
    gainKnobR.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::floralwhite);
    gainKnobR.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::orange.brighter(.8));
    gainKnobR.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::black);
    gainKnobR.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::floralwhite);
    addAndMakeVisible(gainKnobR);
    
    feedbackKnobR.setBounds(670, 110, 95, 95);
    feedbackKnobR.setRange(0.0f, 1.0f, 0.01f);
    feedbackKnobR.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    feedbackKnobR.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    feedbackKnobR.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::floralwhite);
    feedbackKnobR.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::orange.brighter(.8));
    feedbackKnobR.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::black);
    feedbackKnobR.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::floralwhite);
    addAndMakeVisible(feedbackKnobR);
    
    rightSelector.setBounds(550, 200, 110, 25);
    rightSelector.addItem("Sixteenth",1);
    rightSelector.addItem("Eighth",2);
    rightSelector.addItem("Dotted Eighth",3);
    rightSelector.addItem("Quarter",4);
    rightSelector.addItem("Fifth",6);
    rightSelector.addItem("Dotted Quarter",5);
    rightSelector.addItem("Seventh",7);
    rightSelector.addItem("Ninth",9);
    rightSelector.setText("Select Subdivision...");
    addAndMakeVisible(rightSelector);
    
    valueR.setBounds(550, 275, 210, 50);
    valueR.setRange(0.0f, 15.0f, 0.01f);
    valueR.setSliderStyle(juce::Slider::LinearHorizontal);
    valueR.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    valueR.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::floralwhite);
    valueR.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::orange.brighter(.8));
    valueR.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::black);
    valueR.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::floralwhite);
    addAndMakeVisible(valueR);
    
    rightLevel.attachToComponent(&gainKnobR, false);
    rightLevel.setText("Level", juce::dontSendNotification);
    rightLevel.setJustificationType(juce::Justification::centredTop);
    rightLevel.setFont(juce::Font("Arial Black", 20.0, juce::Font::bold));
    addAndMakeVisible(rightLevel);
    
    feedbackLabelRight.attachToComponent(&feedbackKnobR, false);
    feedbackLabelRight.setText("Feedback",juce::dontSendNotification);
    feedbackLabelRight.setJustificationType(juce::Justification::centredTop);
    feedbackLabelRight.setFont(juce::Font("Arial Black", 20.0, juce::Font::bold));
    addAndMakeVisible(feedbackLabelRight);
    
    presetRight.attachToComponent(&rightSelector, false);
    presetRight.setText("Presets...", juce::dontSendNotification);
    presetRight.setJustificationType(juce::Justification::topLeft);
    presetRight.setFont(juce::Font("Arial Black", 20.0,juce::Font::bold));
    addAndMakeVisible(presetRight);
    
    customRight.attachToComponent(&valueR, false);
    customRight.setText("Custom...", juce::dontSendNotification);
    customRight.setJustificationType(juce::Justification::topLeft);
    customRight.setFont(juce::Font("Arial Black", 20.0,juce::Font::bold));
    addAndMakeVisible(customRight);
    
    rightChannel.setText("Right Channel", juce::dontSendNotification);
    rightChannel.setJustificationType(juce::Justification::left);
    rightChannel.setBounds(635, 40, 250, 20);
    rightChannel.setFont(juce::Font("Arial Black", 23.0, juce::Font::bold));
    addAndMakeVisible(rightChannel);

    
    title.setText("My Little Poly Stereo Delay", juce::dontSendNotification);
    title.setJustificationType(juce::Justification::centred);
    title.setBounds(275, 10, 250, 40);
    title.setFont(juce::Font("Arial Black", 32.0, juce::Font::italic));
    addAndMakeVisible(title);
    
    
    
    sliderAttachment.emplace_back(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state,"delayValue",delayKnob));
    sliderAttachment.emplace_back(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state,"gainValueL",gainKnobL));
    sliderAttachment.emplace_back(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state,"gainValueR",gainKnobR));
    boxAttachment.emplace_back(new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.state,"delayLeft",leftSelector));
    boxAttachment.emplace_back(new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.state,"delayRight",rightSelector));
    sliderAttachment.emplace_back(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state,"feedbackValueL",feedbackKnobL));
    sliderAttachment.emplace_back(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state,"customValueL",valueL));
    sliderAttachment.emplace_back(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state,"feedbackValue",feedbackKnobR));
    sliderAttachment.emplace_back(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state,"customValueR",valueR));
}

StereoDelayAudioProcessorEditor::~StereoDelayAudioProcessorEditor()
{
}

//==============================================================================
void StereoDelayAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    
    
    g.fillAll(juce::Colours::steelblue.brighter(0.9));
    
    g.setColour (juce::Colours::floralwhite);
    g.drawRoundedRectangle(30, 30, 230, 305, 10, 5); // pos x, pos y, width, height, corner size, thickness
    
    g.drawRoundedRectangle(30, 30, 95, 135, 10, 4); //level box left
    
    g.drawRoundedRectangle(670, 80, 100, 135, 10, 4); // feedback box left
    
    g.drawRoundedRectangle(30, 165, 130, 85, 10, 4); // combo box left
    
    g.drawRoundedRectangle(30, 250, 230, 85, 10, 4); // slider box left
    
    g.setColour (juce::Colours::floralwhite);
    g.drawRoundedRectangle(540, 30, 230, 305, 10, 5);
    
    g.drawRoundedRectangle(540, 30, 95, 135, 10, 4); // level box right

    g.drawRoundedRectangle(160, 80, 100, 135, 10, 4); //feedback box right
    
    g.drawRoundedRectangle(540, 165, 130, 85, 10, 4); // combo box right
    
    g.drawRoundedRectangle(540, 250, 230, 85, 10, 4); //slider box right

    
    
    g.setColour (juce::Colours::floralwhite);
    g.drawRoundedRectangle(300, 75, 200, 230, 10, 5);
    
    
}

void StereoDelayAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

