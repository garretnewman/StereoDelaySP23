/*
  ==============================================================================

    GainEffect.h
    Created: 21 Apr 2023 12:04:20pm
    Author:  Garret Newman

  ==============================================================================
*/

#pragma once

class GainEffect
{
public:
    
    float processSample(float x, const int c);
    
    void setGain(float newGain) {gain = newGain;}
    
private:
    
    float gain;
    
    float Fs = 44100;
};
