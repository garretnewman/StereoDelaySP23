/*
  ==============================================================================

    GainEffect.cpp
    Created: 21 Apr 2023 12:04:20pm
    Author:  Garret Newman

  ==============================================================================
*/

#include "GainEffect.h"

float GainEffect::processSample(float x, const int c){
    
    float newVar = Fs/1000.f;
    
    return gain * x;
}
