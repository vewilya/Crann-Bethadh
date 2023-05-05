#include "Saturator.h" 

namespace ub
{   

    void Saturator::applySaturation(
    juce::dsp::AudioBlock<float>& inputBlock, float drive, float mix) {
        for (int sample = 0; sample < inputBlock.getNumSamples(); sample++) {
                for (int channel = 0; channel < numChannels; channel++) {
                    
                    auto* channelData = inputBlock.getChannelPointer(channel);

                    const auto in = channelData[sample];
                    const auto sat = softClipper(in, drive);
                    const auto satMix = in * (1.0f - mix) + mix * sat;

                    channelData[sample] = satMix;
                }
            }
    }

    float Saturator::softClipper(float sample, float drive)
    {
        const auto sat = 2 / piDivisor * std::atanf(drive * sample) / drive;
            return sat;
    }
}