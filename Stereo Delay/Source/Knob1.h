/*
  ==============================================================================

    Knob1.h
    Created: 9 Mar 2023 4:18:28pm
    Author:  Garret Newman

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Knob1 : public juce::LookAndFeel_V3
{
public:
    
    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                           const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&) override;
};
