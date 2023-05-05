#include <JuceHeader.h>

namespace ub
{
class Convolver 
{
public:
    void prepare(int sampleRate, int blockSize, int numChannels);
    void process(juce::dsp::AudioBlock<float>& dryBlock, juce::dsp::AudioBlock<float>& wetBlock, float dryAmount, float wetAmount);    
    
    void loadIR(juce::File irFile);


    juce::File& getSavedFile() {
        return savedFile;
    }

    juce::File& getRoot() {
        return root;
    }

    juce::dsp::Convolution& getConvolutionEngine() {
        return convolutionEngine;
    }


private:
    juce::dsp::ProcessSpec spec;

    juce::File root, savedFile;
    juce::dsp::Convolution convolutionEngine;

    juce::dsp::Gain<float> dryGain;
    juce::dsp::Gain<float> wetGain;
};

}