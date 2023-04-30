/*
  ==============================================================================

    DelayEffect.h
    Created: 20 Apr 2023 12:37:48pm
    Author:  Garret Newman

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class DelayEffect {
 
public:
    
    float processSample(float x, const int c);
    
    void setDelayMS(float delayMS);
    
    void prepareToPlay(double sampleRate, int bufferSize){
        Fs = (float) sampleRate;
        r[0] = w[0] - delaySamples;
        r[1] = w[1] - delaySamples;
    }
    
private:
    
    // One sample of delay
    static const int SIZE = 96000;
    float delayBuffer[SIZE][2] = {0.f}; // left and right channels
    int w[2] = {SIZE-1}; // write index for buffer (input), initialize to end of buffer
    int r[2] = {0}; // read index for buffer (output)
    
    int delaySamples = 10000;
    float Fs = 48000.f;
    float fbd = 0.f;
    float fbdValue = 0.45f;
    float smoothDelay = 0.f;
};


class EchoEffect {

public:
    
    float processSample(float x, const int c);
    
    void processBlock(juce::AudioBuffer<float> &buffer);
    
    void processInPlace(float * buffer, const int numSamples, const int c);
    
    void setWet(float newWet) {wet = newWet;}
    
    void prepareToPlay(double sampleRate, int bufferSize){
        delay.prepareToPlay(sampleRate, bufferSize);
    }
    
    void setDelayMS(float delayMS){
        delay.setDelayMS(delayMS);
    }
    
private:
    DelayEffect delay;
    
    float wet = 0.5f;
    float smoothWet = 0.f;
    
    
    
};






