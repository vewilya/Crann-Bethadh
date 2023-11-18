#pragma once

#include <JuceHeader.h>
#include "DelayLine.h"
#include "SaturatorBoutique.h"
#include "PluginParameters.h"

namespace ub::dsp 
{

class Saturator 
{
public:
    Saturator();
    ~Saturator();

    // void setSaturator (SatType type);
    void process(juce::dsp::AudioBlock<float>& inputBlock, const PluginParameters &params); 

    void setSaturator (int satChoice)
    {
        // chosenSatAlgo = SaturatorBoutique::getSaturator(type);
        chosenSatAlgo = SaturatorBoutique::getSaturator(static_cast<SatType>((int) satChoice));
    }

private:
    float piDivisor = 2.0f / juce::MathConstants<float>::pi;
    float softClipper(float samples, float drive);
    
    int numChannels { 2 };
    double sampleRate { 44100 };
    int blockSize { 512 };

    std::array<float, 2> out { 0.0f, 0.0f };

    ub::dsp::DelayLine delayLine;
    
    SatFunc chosenSatAlgo;

};  
} // namespace ub
