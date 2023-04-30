/*
  ==============================================================================

    DelayEffect.cpp
    Created: 20 Apr 2023 12:37:48pm
    Author:  Garret Newman

  ==============================================================================
*/

#include "DelayEffect.h"

float DelayEffect::processSample(float x, const int c){
   
     fbd = delayBuffer[r[c]][c];
    float y = (x + fbd) * (fbdValue);
    delayBuffer[w[c]][c] = y;
    
    // Increment Index
    w[c]++;
    if (w[c] >= SIZE){
        w[c] = 0; // circular indexing
    }
    
    // Increment Index
    r[c]++;
    if (r[c] >= SIZE){
        r[c] = 0; // circular indexing
    }
    return y;
    
}


void DelayEffect::setDelayMS(float delayMS){
    
    float delaySec = delayMS / 1000.f;
    //smoothDelay = 0.98f * smoothDelay + 0.02f * delayMS;
    delaySamples = delaySec * Fs;
    delaySamples = juce::jmin(delaySamples,95999);
    r[0] = w[0] - delaySamples;
    if (r[0] < 0){
        r[0] += SIZE;
    }
    r[1] = w[1] - delaySamples;
    if (r[1] < 0){
        r[1] += SIZE;
    }
}


float EchoEffect::processSample(float x, const int c){
    
    float v = delay.processSample(x, c);
    
    smoothWet = 0.99f * smoothWet + 0.01f * wet;
    float y = (1.f - smoothWet) * x + smoothWet * v;
    
    return y;
}


void EchoEffect::processBlock(juce::AudioBuffer<float> &buffer)
{
    const int numChannels = buffer.getNumChannels();
    const int numSamples = buffer.getNumSamples();
    
    for (int c = 0; c < numChannels ; ++c){
        
        for (int n = 0; n < numSamples ; ++n){
            
            float x = buffer.getWritePointer(c) [n];
            
            x = processSample(x,c);
            
            buffer.getWritePointer(c) [n] = x;
        }
        
    }
}

void EchoEffect::processInPlace(float * buffer, const int numSamples, const int c){
    
    for (int n = 0 ; n < numSamples; ++n){
        float x = (*buffer); // de-reference current value
        
        x = processSample(x,c);
        
        *buffer = x; // over-write current value
        
        ++buffer; // move pointer to the next sample
    }
    
}
