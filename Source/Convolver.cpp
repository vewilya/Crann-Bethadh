#include "Convolver.h"

namespace ub 
{
    void Convolver::prepare(int sampleRate, int blockSize, int numChannels)
    {
        spec.sampleRate = sampleRate;
        spec.maximumBlockSize = blockSize;
        spec.numChannels = numChannels;

        convolutionEngine.reset();
        convolutionEngine.prepare(spec);

        dryGain.reset();
        dryGain.prepare(spec);

        wetGain.reset();
        wetGain.prepare(spec);
    }

    void Convolver::process(juce::dsp::AudioBlock<float>& dryBlock, juce::dsp::AudioBlock<float>& wetBlock, float dryAmount, float wetAmount)
    {
        if (convolutionEngine.getCurrentIRSize() > 0)
        {
            convolutionEngine.process(juce::dsp::ProcessContextReplacing<float>(wetBlock));
            
            for (auto channel = 0; channel < spec.numChannels; ++channel)
            {
                for (auto sample = 0; sample < spec.maximumBlockSize; ++sample)
                {
                    dryBlock.setSample(channel, sample, dryBlock.getSample(channel, sample) * dryAmount + wetBlock.getSample(channel, sample) * wetAmount);
                }
            }
        }
    }  

     void Convolver::loadIR(juce::File irFile)
     {
            convolutionEngine.loadImpulseResponse(irFile, juce::dsp::Convolution::Stereo::yes, juce::dsp::Convolution::Trim::yes, 0); // 0 to initialise the size of the loaded file dynamically!
            savedFile = irFile;
     }

}