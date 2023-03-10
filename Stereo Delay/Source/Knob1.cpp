/*
  ==============================================================================

    Knob1.cpp
    Created: 9 Mar 2023 4:18:28pm
    Author:  Garret Newman

  ==============================================================================
*/

#include "Knob1.h"

void Knob1::drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                       const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&)
{
    auto radius = (float) juce::jmin (width / 2, height / 2) - 4.0f;
            auto centreX = (float) x + (float) width  * 0.5f;
            auto centreY = (float) y + (float) height * 0.5f;
            auto rx = centreX - radius;
            auto ry = centreY - radius;
            auto rw = radius * 2.0f;
            auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    
    // fill
           g.setColour (juce::Colours::orange);
           g.fillEllipse (rx, ry, rw, rw);
    
    // outline
           g.setColour (juce::Colours::red);
           g.drawEllipse (rx, ry, rw, rw, 1.0f);
};
