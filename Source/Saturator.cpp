#include "Saturator.h"

namespace ub::dsp
{

Saturator::Saturator()
{
    // delayLine.setDelay(1);
    // chosenSatAlgo = SaturatorBoutique::getSaturator(static_cast<SatType>((int) audioProcessor.getTreeState().getRawParameterValue(SATTYPE_PARAMETER)->load()));
    chosenSatAlgo = SaturatorBoutique::getSaturator(static_cast<SatType>((int) 1));
}

Saturator::~Saturator()
{
}

void Saturator::process(juce::dsp::AudioBlock<float> &inputBlock, const PluginParameters &params)
{
    const auto feedback = params.mix * 0.9f;
    const auto drive = 1.0f + params.drive * 40.0f;

    for (auto channel = 0; channel < numChannels; channel++)
    {
        auto *channelData = inputBlock.getChannelPointer(channel);

        for (auto sample = 0; sample < inputBlock.getNumSamples(); sample++)
        {
            // Our input is the next sample from the main buffer (writePointer of the respective channel)
            const auto in = channelData[sample];

            // The delay line output is the sample value that we stored in the delayLine at index readHead, which should always be the oldest sample in there.
            // const auto delayed = delayLine.popSample();

            // Outputting the sum of our input sample + g * the oldest sample stored in the delay line
            // y[n] = x[n] + g * y[n-5]
            out[channel] = in + feedback * out[channel];
            channelData[sample] = chosenSatAlgo(out[channel], drive);

            // delayLine.pushSample(out);
        }
    }
}
}